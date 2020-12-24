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
    int pipe;
    
    while(1){
        // read number from mario
        pipe = open("mario", O_RDONLY);
        read(pipe, input, 256);
        close(pipe);
        // find phi(n)
        int a = atoi(input);
        int ans = phi(a);
        // write answer to char array
        
        sprintf(output, "%d", ans); 

        // write to luigi so prompt.c can read it
        open("luigi", O_WRONLY);
        write(pipe, input, sizeof(input));
        printf("output: %s written to luigi\n", output);
        close(pipe);
    }
    return 0;
}