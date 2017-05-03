#include <cstdio>       //printf
#include <cstring>      //memset
#include <cstdlib>      //exit
#include <netinet/in.h> //htons
#include <arpa/inet.h>  //inet_addr
#include <sys/socket.h> //socket
#include <unistd.h>     //close
 
#define MAXMSG 1024
#define MAXNAME 100
#define PORTNUM 4325
 
class Mensagem {
    public:
        char msg[MAXMSG];
        Mensagem();
};
 
 
int main(int argc, char *argv[])
{
    struct sockaddr_in endereco;
    int socketId;
 
    Mensagem mensagem;
    strcpy(mensagem.msg,"Olá, tudo bem?");
    int bytesenviados;
 
    /*
     * Configurações do endereço
    */
    memset(&endereco, 0, sizeof(endereco));
    endereco.sin_family = AF_INET;
    endereco.sin_port = htons(PORTNUM);
    endereco.sin_addr.s_addr = inet_addr("10.51.66.39");
 
    /*
     * Criando o Socket
     *
     * PARAM1: AF_INET ou AF_INET6 (IPV4 ou IPV6)
     * PARAM2: SOCK_STREAM ou SOCK_DGRAM
     * PARAM3: protocolo (IP, UDP, TCP, etc). Valor 0 escolhe automaticamente
    */
    socketId = socket(AF_INET, SOCK_STREAM, 0);
 
    //Verificar erros
    if (socketId == -1)
    {
        printf("Falha ao executar socket()\n");
        exit(EXIT_FAILURE);
    }
 
    //Conectando o socket cliente ao socket servidor
    if ( connect (socketId, (struct sockaddr *)&endereco, sizeof(struct sockaddr)) == -1 )
    {
        printf("Falha ao executar connect()\n");
        exit(EXIT_FAILURE);
    }
    printf ("Cliente conectado ao servidor\n");
 
    //Enviar uma msg para o cliente que se conectou
    printf("Cliente vai enviar uma mensagem\n");
    bytesenviados = send(socketId,&mensagem,sizeof(mensagem),0);
 
    if (bytesenviados == -1)
    {
        printf("Falha ao executar send()");
        exit(EXIT_FAILURE);
    }
    printf("Cliente enviou a seguinte msg (%d bytes) para o servidor: %s \n",bytesenviados,mensagem.msg);
 
    close(socketId);
 
    return 0;
}