cd src
gcc drive.c -c
cd ..
gcc -lwiringPi src/directdrive.c src/drive.o -o directdrive.out
gcc -lwiringPi src/client.c src/drive.o -o client.out
gcc src/server.c -o server.out
gcc src/driveserver.c -o driveserver.out