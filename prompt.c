#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main(){
    char input [256];
    char output [256];
    int inpipe = mkfifo("./mario", 0644);
    int outpipe = mkfifo("./luigi", 0664);
    int fd1 = open("./mario", O_WRONLY);
    int fd2 = open("./luigi", O_RDONLY);
    while(1){
        // recieve input
        printf("Please enter a number: ");
        fgets(input, 256, stdin);

        // write input to mario to be read by process.c
        
        write(fd1, input, sizeof(input));

        // recieve output from process.c that was written to luigi and print it
        
        read(fd2, output, sizeof(output));

        printf("phi(n): %s\n", output);
    }
    close(fd1);
    close(fd2);
    return 0;
}