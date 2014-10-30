#include "drive.h"
#include <wiringPi.h>
#include <stdlib.h>
#include <stdio.h>
int main(int argc, char *argv[]) {
    wiringPiSetup();
    setup();
    if(argc > 1) {
        system("/bin/stty raw");
    }
    char input;
    while((input = fgetc(stdin))) {
        if(input == 'w') {
            forward(-1);
        } else if(input == 's') {
            reverse(-1);
        } else if(input == 'a') {
            left(-1);
        } else if(input == 'd') {
            right(-1);
        } else if(input == ' ') {
            off();
        } else if(input == 'x') {
            break;
        }
    }
    off();
    if(argc > 1) {
        system("/bin/stty cooked");
    }
    return 0;
}
