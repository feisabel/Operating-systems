#include <cstdio>       //printf
#include <cstring>      //memset
#include <cstdlib>      //exit
#include <netinet/in.h> //htons
#include <arpa/inet.h>  //inet_addr
#include <sys/socket.h> //socket
#include <unistd.h>     //close
#include <thread>
#include <iostream>
#include <vector>
using namespace std;
 
#define PORTNUM 4325
 
class Mensagem {
    public:
        int pot, bot, luz;
        Mensagem();
};

Mensagem::Mensagem(){}

int n = 20, m = 20;
bool jump = false;
bool arm = false;
bool running = true;
int atual = 2048;

void draw() {
    if(!arm) {
        if(!jump) {
            cout << "\r" << endl << endl << endl << endl << endl << endl << endl;
            string s1 = "";
            string s2 = "";
            for(int i = 0; i < n; i++) {
                s1 += " ";
            }
            for(int i = 0; i < m; i++) {
                s2 += " ";
            }
            cout << s1 << " o " << s2 << endl << s1 << "`|´" << s2 << endl << s1 << " ^ " << s2 << endl;
        }
        else {
            cout << "\r" << endl << endl << endl << endl;
            string s1 = "";
            string s2 = "";
            for(int i = 0; i < n; i++) {
                s1 += " ";
            }
            for(int i = 0; i < m; i++) {
                s2 += " ";
            }
            cout << s1 << " o " << s2 << endl << s1 << "`|´" << s2 << endl << s1 << " ^ " << s2 << endl;
            cout << endl << endl << endl;
        }
    }
    else {
        if(!jump) {
            cout << "\r" << endl << endl << endl << endl << endl << endl << endl;
            string s1 = "";
            string s2 = "";
            for(int i = 0; i < n; i++) {
                s1 += " ";
            }
            for(int i = 0; i < m; i++) {
                s2 += " ";
            }
            cout << s1 << " o " << s2 << endl << s1 << "`|," << s2 << endl << s1 << " ^ " << s2 << endl;
        }
        else {
            cout << "\r" << endl << endl << endl << endl;
            string s1 = "";
            string s2 = "";
            for(int i = 0; i < n; i++) {
                s1 += " ";
            }
            for(int i = 0; i < m; i++) {
                s2 += " ";
            }
            cout << s1 << " o " << s2 << endl << s1 << "`|," << s2 << endl << s1 << " ^ " << s2 << endl;
            cout << endl << endl << endl;
        }
    }
}
 
 
void socketHandler(int socketDescriptor,Mensagem mensagem)
{
    int byteslidos;
 
    //Verificando erros
    if ( socketDescriptor == -1)
    {
        printf("Falha ao executar accept()");
        exit(EXIT_FAILURE);
    }
 
    //receber uma msg do cliente
    //printf("Servidor vai ficar esperando uma mensagem\n");
    byteslidos = ::recv(socketDescriptor,&mensagem,sizeof(mensagem),0);
 
    if (byteslidos == -1)
    {
        printf("Falha ao executar recv()");
        exit(EXIT_FAILURE);
    }
    if(mensagem.pot > atual + 10) {
        atual = mensagem.pot;
        if (n > 0) {
            n--;
            m++;
        }
    }
    else if (mensagem.pot  < atual - 10){
        atual = mensagem.pot;
        if (m > 0) {
            m--;
            n++;
        }
    }
    if (mensagem.bot == 1){
        jump = true;
    }
    if(mensagem.luz < 1000) {
        arm = true;
    }
    system("clear");
    draw();
    usleep(1500000);
    jump = false;
    arm = false;
    system("clear");
    draw();

    close(socketDescriptor);
}
 
 
int main(int argc, char *argv[])
{
    //variáveis do servidor
    struct sockaddr_in endereco;
    int socketId;
 
    //variáveis relacionadas com as conexões clientes
    struct sockaddr_in enderecoCliente;
    socklen_t tamanhoEnderecoCliente = sizeof(struct sockaddr);
    int conexaoClienteId;
 
    //mensagem enviada pelo cliente
    Mensagem mensagem;
 
    /*
     * Configurações do endereço
    */
    memset(&endereco, 0, sizeof(endereco));
    endereco.sin_family = AF_INET;
    endereco.sin_port = htons(PORTNUM);
    //endereco.sin_addr.s_addr = INADDR_ANY;
    endereco.sin_addr.s_addr = inet_addr("127.0.0.1");
 
    /*
     * Criando o Socket
     *
     * PARAM1: AF_INET ou AF_INET6 (IPV4 ou IPV6)
     * PARAM2: SOCK_STREAM ou SOCK_DGRAM
     * PARAM3: protocolo (IP, UDP, TCP, etc). Valor 0 escolhe automaticamente
    */
    socketId = socket(AF_INET, SOCK_STREAM, 0);
 
    //Verificar erros
    if (socketId == -1) {
        printf("Falha ao executar socket()\n");
        exit(EXIT_FAILURE);
    }
 
    //Conectando o socket a uma porta. Executado apenas no lado servidor
    if (::bind(socketId, (struct sockaddr *)&endereco, sizeof(struct sockaddr)) == -1 ) {
        printf("Falha ao executar bind()\n");
        exit(EXIT_FAILURE);
    }
 
    //Habilitando o servidor a receber conexoes do cliente
    if ( ::listen( socketId, 10 ) == -1) {
        printf("Falha ao executar listen()\n");
        exit(EXIT_FAILURE);
    }
 
    //servidor ficar em um loop infinito
    while(1) { 
        //Servidor fica bloqueado esperando uma conexão do cliente
        conexaoClienteId = ::accept( socketId,(struct sockaddr *) &enderecoCliente,&tamanhoEnderecoCliente );
 
        //disparar a thread
        thread t(socketHandler,conexaoClienteId,mensagem);
        t.detach();
    }
 
    return 0;
}