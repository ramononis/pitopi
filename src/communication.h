#ifndef H_COMMUNICATION
#define H_COMMUNICATION
#define FORWARD 1
#define RIGHT 2
#define LEFT 3
#define REVERSE 4
#define FORWARD_RIGHT 5
#define FORWARD_LEFT 6
#define OFF 7
#define T_DIRECTION 1
#define T_GO_SCAN 2
#define T_SCAN_RESULT 3
#define T_SCAN_DONE 5
#define T_ACK 4
#define N_SCANS 7
struct message {
    int type;
    int arg1;
    int arg2;
    int arg3;
    int arg4;
    int id;
};

#endif //H_COMMUNICATION
