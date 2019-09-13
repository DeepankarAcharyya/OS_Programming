/*
Assignment-2b:
Write a C program which will take the Process ID and signal ID as 
input to demonstrate the use of kill( ) system call. 
*/

#include<stdio.h>
#include<signal.h>
#include<sys/types.h>
#include<unistd.h>
#include<stdlib.h>

int main(int argc,char* argv[]){
    printf("\nMain Program\nProgram Started\n");
    if(argc<2){
        printf("\nInsufficient Inputs\n");
        exit(1);
    }
    pid_t process=atoi(argv[1]);
    int signal=atoi(argv[2]);
    printf("\nKilling the process with pid=%d\n",process);
    kill(process,signal);
    printf("\nProcess Killed\nExiting main()\n");
    return 0;
}