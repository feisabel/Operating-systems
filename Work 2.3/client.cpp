#include <cstdio>       //printf
#include <cstring>      //memset
#include <cstdlib>      //exit
#include <netinet/in.h> //htons
#include <arpa/inet.h>  //inet_addr
#include <sys/socket.h> //socket
#include <unistd.h>     //close
#include <thread>
#include <pthread.h>
#include <vector>
#include <iostream>
#include "../Utils/api_gpio/pmap.h"
#include "../Utils/api_gpio/pin.h"
#include "../Utils/utils.h"
#include <string>

using namespace std;

#define PORTNUM 4325
#define PORT_POT 1 //potentiometer
#define DISCONNECT 1
#define CONNECT 1
#define TURN_ON_TRAINS 2
#define TURN_OFF_TRAINS 3
#define TURN_ON_TRAIN 4
#define TURN_OFF_TRAIN 5
#define CHANGE_SPEED 6
#define QUIT 7
#define NB_TRAINS 7

class Mensagem {
    public:
        int command;
        int train;
        int speed;
        Mensagem() {};
        Mensagem (int c, int t, int s) : command{c}, train{t}, speed{s} {}
};

void mainMenu(int selected, bool connected) {
    system("clear");
    if(connected) {
      cout << (selected== DISCONNECT ? "> Desconectar do servidor\n" : "  Desconectar do servidor\n");
      cout << (selected== TURN_ON_TRAINS ? "> Ligar todos os trens\n" : "  Ligar todos os trens\n");
      cout << (selected== TURN_OFF_TRAINS ? "> Desligar todos os trens\n" : "  Desligar todos os trens\n");
      cout << (selected== TURN_ON_TRAIN ? "> Ligar um trem específico\n" : "  Ligar um trem específico\n");
      cout << (selected== TURN_OFF_TRAIN ? "> Desligar um trem específico\n" : "  Desligar um trem específico\n");
      cout << (selected== CHANGE_SPEED ? "> Alterar a velocidade de um trem específico\n" : "  Alterar a velocidade de um trem específico\n");
    } else {
      cout << (selected== CONNECT ? "> Conectar ao servidor\n" : "  Conectar ao servidor\n");
    }
    cout << (selected== QUIT ? "> Quit\n" : "  Quit\n");
}

int chooseSpeed(Pin play) {
    float v;
    int pot;
    while(true) {
        if(play.getValue()) {
            usleep(200000);
            return v;
        }
        else {
            usleep(200000);
            pot = readAnalog(PORT_POT);
            v = (pot / 4096.0 * 290) + 10;
            system("clear");
            cout << (int)v << endl;
        }
    }
}

void trainMenu(int selected) {
    system("clear");
    for(int i = 1; i <= NB_TRAINS; i++){
      if(selected == i){
        cout << "> ";
      }
      else {
        cout << "  ";
      }
      cout << i << endl;
    }
}

int chooseTrain(Pin up, Pin down, Pin play) {
    int selected = 1;
    trainMenu(selected);
    while(true){
        if(up.getValue()) {
            usleep(200000);
            if(selected > 1) {
                selected--;
                trainMenu(selected);
            }
        }
        else if(down.getValue()) {
            usleep(200000);
            if(selected < 7) {
                selected++;
                trainMenu(selected);
            }
        }
        else if(play.getValue()) {
            usleep(200000);
            return selected - 1;
        }

    }
}

int main(int argc, char *argv[]) {
    struct sockaddr_in endereco;
    int socketId;

    init();
    Pin up ("P9_27", Direction::IN, Value::LOW);
    Pin down ("P9_41", Direction::IN, Value::LOW);
    Pin play ("P9_42", Direction::IN, Value::LOW);

    //Configurações do endereço
    memset(&endereco, 0, sizeof(endereco));
    endereco.sin_family = AF_INET;
    endereco.sin_port = htons(PORTNUM);
    endereco.sin_addr.s_addr = inet_addr("127.0.0.1");

    socketId = ::socket(AF_INET, SOCK_STREAM, 0);

    Mensagem msg;
    msg.train = 0;
    msg.speed = 100;

    int bytesenviados;

    //Verificar erros
    if (socketId == -1) {
        printf("Falha ao executar socket()\n");
        exit(EXIT_FAILURE);
    }

    int selected = 1;
    bool connected = false;
    bool quit = false;
    mainMenu(selected, connected);
    while(!quit){
        if(up.getValue()) {
            usleep(200000);
            if(connected) {
                if(selected > 1) {
                    selected--;
                    mainMenu(selected, connected);
                }
            }
            else {
                if(selected == 7) {
                    selected = 1;
                    mainMenu(selected, connected);
                }
            }
        }
        else if(down.getValue()) {
            usleep(200000);
            if(connected) {
                if(selected < 7) {
                    selected++;
                    mainMenu(selected, connected);
                }
            }
            else {
                if(selected == 1) {
                    selected = 7;
                    mainMenu(selected, connected);
                }
            }
        }
        else if(play.getValue()) {
            usleep(200000);
            if(selected == 1) {
                if(connected) {
                    connected = false;
                    close(socketId);
                }
                else {
                    connected = true;
                    if ( ::connect (socketId, (struct sockaddr *)&endereco, sizeof(struct sockaddr)) == -1 ) {
                        printf("Falha ao executar connect()\n");
                        exit(EXIT_FAILURE);
                    }
                }
                mainMenu(selected, connected);
            }
            else {
              msg.command = selected;
              if(selected == TURN_ON_TRAIN || selected == TURN_OFF_TRAIN) {
                  msg.train = chooseTrain(up, down, play);
                  mainMenu(selected, connected);
              } else if (selected == CHANGE_SPEED){
                msg.train = chooseTrain(up, down, play);
                msg.speed = chooseSpeed(play);
                mainMenu(selected, connected);
              } else if (selected == QUIT){
                quit = true;
              }

              if(connected && selected > 1 && selected < 7) {
                  bytesenviados = ::send(socketId,&msg,sizeof(msg),0);
                  if (bytesenviados == -1) {
                      printf("Falha ao executar send()");
                      exit(EXIT_FAILURE);
                  }
              }
            }
        }
    }
    return 0;
}
