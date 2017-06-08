#include <cstdio>       //printf
#include <cstring>      //memset
#include <cstdlib>      //exit
#include <netinet/in.h> //htons
#include <arpa/inet.h>  //inet_addr
#include <sys/socket.h> //socket
#include <unistd.h>     //close
#include <iostream>
#include <vector>
#include <thread>

using namespace std;

#define PORTNUM 4325

class Mensagem {
    public:
        int command;
        int train;
        int speed;
        Mensagem() {}
        Mensagem (int c, int t, int s) : command{c}, train{t}, speed{s} {}
};

void socketHandler(int socketDescriptor,Mensagem mensagem) {
    int byteslidos = 1;

    //Verificando erros
    if ( socketDescriptor == -1) {
        printf("Falha ao executar accept()");
        exit(EXIT_FAILURE);
    }

    while(byteslidos != 0) {

        //receber uma msg do cliente
        byteslidos = recv(socketDescriptor,&mensagem,sizeof(mensagem),0);
        if (byteslidos == -1) {
            printf("Falha ao executar recv()");
            exit(EXIT_FAILURE);
        }
        else if(byteslidos == 0)
            break;
        cout << "Servidor recebeu a seguinte msg do cliente: " << mensagem.command << endl;

    }
    close(socketDescriptor);
}

int main(int argc, char *argv[]) {
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
        printf("Servidor: recebeu conexão de %s\n", inet_ntoa(enderecoCliente.sin_addr));

        //disparar a thread
        thread t(socketHandler,conexaoClienteId,mensagem);
        t.detach();
    }
}
