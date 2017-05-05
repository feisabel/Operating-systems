#include <cstdio>       //printf
#include <cstring>      //memset
#include <cstdlib>      //exit
#include <netinet/in.h> //htons
#include <arpa/inet.h>  //inet_addr
#include <sys/socket.h> //socket
#include <unistd.h>     //close
#include <thread>
#include <pthread.h>
#include <iostream>
#include "../Utils/api_gpio/pmap.h"
#include "../Utils/api_gpio/pin.h"
#include "../Utils/utils.h"
#include <string>
 
using namespace std;

#define PORTNUM 4325
#define PORT_LDR 4 //Light Dependent Resistor
#define PORT_POT 1 //potentiometer
 
class Mensagem {
    public:
        int pot;
        int bot;
        int luz;
        Mensagem();
};

Mensagem::Mensagem(){}

Mensagem mensagem;
string msg;

bool running = true;

void socketHandler(int socketId) {
    //Enviar uma msg para o cliente que se conectou
    int bytesenviados;
    msg = "" + to_string(mensagem.pot) + "," + to_string(mensagem.bot) + "," + to_string(mensagem.luz);
    cout << "Cliente vai enviar uma mensagem : " <<  msg << endl;
    bytesenviados = ::send(socketId,msg.data(),msg.size()+1,0);
    if (bytesenviados == -1) {
        printf("Falha ao executar send()");
        exit(EXIT_FAILURE);
    }
    close(socketId);
}
 
void read_pot(){
    while(running) {
        mensagem.pot = readAnalog(PORT_POT);
        std::this_thread::sleep_for( std::chrono::milliseconds(300) );
    }

}

void read_botao(){
    init();
    Pin btn ("P9_27", Direction::IN, Value::LOW);
    int btnValue;
    while(running){
        mensagem.bot = btn.getValue();
        std::this_thread::sleep_for( std::chrono::milliseconds(300) );
    }

}

void read_luz(){
    while (running){
        mensagem.luz = readAnalog(PORT_LDR);
        std::this_thread::sleep_for( std::chrono::milliseconds(300) );
    }

}
 
int main(int argc, char *argv[])
{
    struct sockaddr_in endereco;
    int socketId;
 
    /*
     * Configurações do endereço
    */
    memset(&endereco, 0, sizeof(endereco));
    endereco.sin_family = AF_INET;
    endereco.sin_port = htons(PORTNUM);
    endereco.sin_addr.s_addr = inet_addr("192.168.0.12");
    /*mensagem.bot = 1;
    mensagem.pot = 2;
    mensagem.luz = 3;*/
    /*
     * Criando o Socket
     *
     * PARAM1: AF_INET ou AF_INET6 (IPV4 ou IPV6)
     * PARAM2: SOCK_STREAM ou SOCK_DGRAM
     * PARAM3: protocolo (IP, UDP, TCP, etc). Valor 0 escolhe automaticamente
    */
    /*socketId = ::socket(AF_INET, SOCK_STREAM, 0);
 
    //Verificar erros
    if (socketId == -1) {
        printf("Falha ao executar socket()\n");
        exit(EXIT_FAILURE);
    }*/
    std::thread pot(read_pot);
    std::thread botao(read_botao);
    std::thread luz(read_luz);
    struct sched_param param1;
    struct sched_param param2;
    struct sched_param param3;
    param1.sched_priority = sched_get_priority_max(SCHED_RR);
    param3.sched_priority = sched_get_priority_min(SCHED_RR);
    param2.sched_priority = sched_get_priority_max(SCHED_RR)/2;
    pthread_setschedparam(pot.native_handle(), SCHED_RR, &param1);
    pthread_setschedparam(luz.native_handle(), SCHED_RR, &param2);
    pthread_setschedparam(botao.native_handle(), SCHED_RR, &param3);
    /*if ( ::connect (socketId, (struct sockaddr *)&endereco, sizeof(struct sockaddr)) == -1 ) {
        printf("Falha ao executar connect()\n");
        exit(EXIT_FAILURE);
    }*/
    while(1) {
        socketId = ::socket(AF_INET, SOCK_STREAM, 0);
 
        //Verificar erros
        if (socketId == -1) {
            printf("Falha ao executar socket()\n");
            exit(EXIT_FAILURE);
        }
        if ( ::connect (socketId, (struct sockaddr *)&endereco, sizeof(struct sockaddr)) == -1 ) {
            printf("Falha ao executar connect()\n");
            exit(EXIT_FAILURE);
        }
        //Conectando o socket cliente ao socket servidor
        thread t(socketHandler,socketId);
        t.detach();
        usleep(1500000);
    }
    running = false;
    
 
    return 0;
}