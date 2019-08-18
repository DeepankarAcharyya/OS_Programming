/*
Assignment 1(c):-
Write a C program like the assignment 1(b) and overlay a user designed program into the address space of
the child process using execv() system call. Again use wait() system call to synchronize the execution of
parent process in your program until child process finishes. Here use the macro WIFEXITED to capture
the returned status of the child in parent process. Also demonstrate the use of argument vector to print the
program name by the child process.
*/

#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<unistd.h>
#include<sys/wait.h>
#include<utmp.h>

int main(){
    printf("i am the parent with pid: %d\n",(int) getpid());
    pid_t pid=fork();
    
    if (pid<0){
        perror("Fork Failed\n");
    }
    else if(pid ==0){
        printf("\nI am the child \n Pid : %d\n PPID : %d\n Going to execute the program.\n",(int)getpid(),(int)getppid());
        execv("./userdesignedprogram",NULL);
        printf("\nExiting process with Pid:%d\n",(int)getpid());
        exit(0);
    }  

        printf("\nPid:%d waiting for its child process to end!\n",(int)getpid());
        wait(NULL);
    printf("\nExiting process with Pid:%d\n",(int)getpid());
    return 0;
}