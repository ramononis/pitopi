#ifndef DRIVE_H
#define DRIVEH
#ifndef DEFAULT_MILLIS
#define DEFAULT_MILLIS 1000
#endif //DEFAULT_MILLIS
#define PWMA 0
#define AIN1 2
#define AIN2 7
#define PWMB 4
#define BIN1 5
#define BIN2 6
#define STBY 3
void setup();
void forward(int millis);
void reverse(int millis);
void forward_left(int millis);
void left(int millis);
void forward_right(int millis);
void right(int millis);
void off();
#endif //DRIVE_H
