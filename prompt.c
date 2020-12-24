#include <fcntl.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>

int main(){
    char input [256];
    char output [256];
    mkfifo("mario", 0666);
    mkfifo("luigi", 0666);
    int pipe;
    while(1){
        // recieve input
        printf("Please enter a positive integer: ");
        fgets(input, 256, stdin);
        *strchr(input, '\n') = 0;
        pipe = open("mario", O_WRONLY);
        // write input to mario to be read by process.c
        
        write(pipe, input, sizeof(input));
        close(pipe);
        // recieve output from process.c that was written to luigi and print it
        pipe = open("luigi", O_RDONLY);
        read(pipe, output, sizeof(output));
        printf("phi(n): %s\n", output);
        close (pipe);
    }
    return 0;
}
