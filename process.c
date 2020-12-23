#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>

int phi(int n){ 
    int ans = n; 
    for (int p = 2; p * p <= n; ++p) { 
        if (n % p == 0) { 
            while (n % p == 0) 
                n /= p; 
            ans -= ans / p; 
        } 
    } 
    if (n > 1) 
        ans -= ans / n; 
    return ans; 
} 

int main(){
    char input [256];
    char output [256];
    int fd1 = open("./mario", O_RDONLY);
    int fd2 = open("./luigi", O_WRONLY);
    int fd3 = open("hi.txt", O_WRONLY);
    
    while(1){
        // read number from mario
        read(fd1, input, 256);
        // find phi(n)
        int a = atoi(input);
        int ans = phi(a);
        // convert to char array
        sprintf(output, "%d", ans); 
        // write to luigi so prompt.c can read it
        write(fd2, output, sizeof(output));
        write(fd3, output, sizeof(output));
    }
    close(fd1);
    close(fd2);
    return 0;
}