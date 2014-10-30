#include "drive.h"
#include <wiringPi.h>
#include <unistd.h>

void setup() {
    pinMode(AIN1, OUTPUT);
    pinMode(AIN2, OUTPUT);
    pinMode(BIN1, OUTPUT);
    pinMode(BIN2, OUTPUT);
    pinMode(STBY, OUTPUT);
    pinMode(PWMA, OUTPUT);
    pinMode(PWMB, OUTPUT);
    off();
}
void timedoff(int millis) {
    if(millis == 0) {
        millis = DEFAULT_MILLIS;
    }
    if(millis > 0) {
        usleep(millis * 1000);
        off();
    }
} 
//when millis=0, the default value DEFAULT_MILLIS.
//when millis<0, the function doesn't turn it off.
//when millis>0, the functions turns it off after the specified time in ms.
void forward(int millis) {
    digitalWrite(AIN1, 1);
    digitalWrite(AIN2, 0);
    digitalWrite(BIN1, 1);
    digitalWrite(BIN2, 0);
    digitalWrite(STBY, 1);
    digitalWrite(PWMA, 1);
    digitalWrite(PWMB, 1);
    timedoff(millis);
}
void reverse(int millis) {
    digitalWrite(AIN1, 0);
    digitalWrite(AIN2, 1);
    digitalWrite(BIN1, 0);
    digitalWrite(BIN2, 1);
    digitalWrite(STBY, 1);
    digitalWrite(PWMA, 1);
    digitalWrite(PWMB, 1);
    timedoff(millis);
}
void forward_left(int millis) {
    digitalWrite(AIN1, 1);
    digitalWrite(AIN2, 0);
    digitalWrite(BIN1, 0);
    digitalWrite(BIN2, 0);
    digitalWrite(STBY, 1);
    digitalWrite(PWMA, 1);
    digitalWrite(PWMB, 0);
    timedoff(millis);
}
void forward_right(int millis) {
    digitalWrite(AIN1, 0);
    digitalWrite(AIN2, 0);
    digitalWrite(BIN1, 1);
    digitalWrite(BIN2, 0);
    digitalWrite(STBY, 1);
    digitalWrite(PWMA, 0);
    digitalWrite(PWMB, 1);
    timedoff(millis);
}
void left(int millis) {
    digitalWrite(AIN1, 1);
    digitalWrite(AIN2, 0);
    digitalWrite(BIN1, 0);
    digitalWrite(BIN2, 1);
    digitalWrite(STBY, 1);
    digitalWrite(PWMA, 1);
    digitalWrite(PWMB, 1);
    timedoff(millis);
}
void right(int millis) {
    digitalWrite(AIN1, 0);
    digitalWrite(AIN2, 1);
    digitalWrite(BIN1, 1);
    digitalWrite(BIN2, 0);
    digitalWrite(STBY, 1);
    digitalWrite(PWMA, 1);
    digitalWrite(PWMB, 1);
    timedoff(millis);
}
void off() {
    digitalWrite(AIN1, 0);
    digitalWrite(AIN2, 0);
    digitalWrite(BIN1, 0);
    digitalWrite(BIN2, 0);
    digitalWrite(STBY, 0);
    digitalWrite(PWMA, 0);
    digitalWrite(PWMB, 0);
}

