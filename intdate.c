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
/*
 * This is the handler of SIGALRM
 * It prints out the current time and send the next alarm signal to interrupt the infinite loop in 3 seconds.
 */
void handleralm (int sig) {
    // print out the time message if alarm is received.
    time_t sec;
    sec = time(NULL);
    printf("current time is %s", ctime(&sec));
    // send the next alarm signal, to interrupt the infinite loop later.
    alarm(3);
    return;
}

/*
 * This is the handler of the SIGINT
 * It prints out how many times of control-c to enter for left
 * Once it reaches the final control-c, it exits the program.
 */
void handlerint (int sig) {
    // count down from 4 to 0.
    static int count = 4;
    // print the message if it can still take control-c.
    if (count > 0) {
        printf("\nControl-c caught. %i more before program ends.\n", count);
        count--;
    }
    // print the message if the final control-c is entered.
    else {
        printf("\nFinal control-c caught. Exiting. \n");
        exit(0);
    }
}

int main(int argc, const char * argv[]) {
    // insert code here...
    printf("Date will be printed every 3 seconds\n");
    printf("Enter ^C 5 times to end the program:\n");
    
    // declare the sigaction for alarm
    struct sigaction actalm;
    // initialize the sigaction for alarm
    memset (&actalm, 0, sizeof(actalm));
    // assign the handler of alarm to this sigaction
    actalm.sa_handler = handleralm;
    // install the handler of alarm
    sigaction(SIGALRM, &actalm, NULL);
    
    // declare the sigaction for int
    struct sigaction actint;
    // initialize the sigaction for int
    memset(&actint, 0, sizeof(actint));
    // assign the handler of int to this sigaction
    actint.sa_handler = handlerint;
    // install the handler of int
    sigaction(SIGINT, &actint, NULL);
    
    // first send the signal of alarm, to be received in 3 seconds.
    alarm(3);
    // the infinite loop, will be interrupted by signals.
    while (1) {
        ;
    }
    return 0;
}
