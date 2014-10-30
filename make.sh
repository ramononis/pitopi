cd src
gcc drive.c -c
cd ..
gcc -lwiringPi src/directdrive.c src/drive.o -o directdrive.out
