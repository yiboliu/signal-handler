/*
 * Name: Yibo Liu
 * cs login: yibol
 * section: 001
 * email: yibol@cs.wisc.edu
 */
#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <signal.h>
#include "string.h"
#include <stdlib.h>

// This is the counter of how many operatoins successfully completed.
static int count = 0;

/*
 * This is the handler of SIGFPE.
 * It prints out the proper message if an integer is divided by 0
 * Then prints out the sucessful operation completed.
 * Then exits the whole program gracefully.
 */
void handlerfpe (int sig) {
    // print the error message if dividing 0 occurs.
    printf("Error: a division by 0 operation was attempted.\n");
    printf("Total number of operations completed: %i\n", count);
    printf("The program will be stopped.\n");
    exit(0);
}

/*
 * This is the handler of SIGINT.
 * It prints out the proper message if control-c is entered.
 * Prints out the number of successful operations completed.
 * Then it exits the whole program. 
 */
void handlerint (int sig) {
    // print the message if the program is halted by control-c.
    printf("Total number of operations completed: %i\n", count);
    printf("\nThe program will be halted.\n");
    exit(0);
}

int main(int argc, const char * argv[]) {
    // put the whole code in this while loop to enable run repeatedly.
    while (1) {
        // prompt of the first integer.
        printf("Enter first integer: ");
        
        char fstInt[100];
        
        fgets(fstInt, 100, stdin);
        
        // part of the code to execute if a control-c is entered.
        struct sigaction actint;
        
        memset(&actint, 0, sizeof(actint));
        
        actint.sa_flags = SA_RESTART;
        
        actint.sa_handler = handlerint;
        
        sigaction(SIGINT, &actint, NULL);
        
        // prompt of the second integer.
        printf("Enter second integer: ");
        
        char sndInt[100];
        
        fgets(sndInt, 100, stdin);
        
        int intone = atoi(fstInt);
        int inttwo = atoi(sndInt);
        
        // if the civider is 0, then it is handled with the signal handler.
        if (inttwo == 0) {
            struct sigaction actfpe;
            
            memset(&actfpe, 0, sizeof(actfpe));
            
            actfpe.sa_flags = SA_RESTART;
            
            actfpe.sa_handler = handlerfpe;
            
            sigaction(SIGFPE, &actfpe, NULL);
        }
        else {
            count++;
        }
        
        // if all the arguments of the calculation are proper, then a division is performed.
        int quotient = intone / inttwo;
        int remainder = intone % inttwo;
        
        // print out the result of the division. 
        printf("%i / %i is %i with a remainder of %i\n", intone, inttwo, quotient, remainder);
    }
    
    return 0;
}
