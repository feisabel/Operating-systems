#ifndef _INFO_
#define _INFO_

#define PORTNUM 4325
#define NB_TRAINS 7

#define DISCONNECT 1
#define CONNECT 1
#define TURN_ON_TRAINS 2
#define TURN_OFF_TRAINS 3
#define TURN_ON_TRAIN 4
#define TURN_OFF_TRAIN 5
#define CHANGE_SPEED 6
#define QUIT 7
#define IP "192.168.7.1"

class Mensagem {
    public:
        int command;
        int train;
        int speed;
        Mensagem() {}
        Mensagem (int c, int t, int s) : command{c}, train{t}, speed{s} {}
};

#endif
