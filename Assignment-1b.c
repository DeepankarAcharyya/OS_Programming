/*
Assignment 1(b):-
Write a C program like the assignment 1(a). But here use the system call wait() system to synchronize the
execution of parent program in your program until child process finishes. Now write a function to print to
find out who is logging in the local machine that is partially equivalent to the cmd "w" or "who" and engage
the grandchild to print the output into the stdout. 
*/

#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<unistd.h>
#include<sys/wait.h>
#include<utmp.h>

//function to find out who is logging in the local machine
void current_users(){
    
    return;
}


int main(){
    printf("i am the parent with pid: %d\n",(int) getpid());
    pid_t pid=fork();
    
    if (pid<0){
        perror("Fork Failed\n");
    }
    else if(pid ==0){
        printf("\nI am the child \n Pid : %d\n PPID : %d\n",(int)getpid(),(int)getppid());
        pid_t pid_grandchild=fork();

        if (pid_grandchild<0){
            perror("Fork Failed\n");
        }
        else if(pid_grandchild==0){
            printf("\nI am the Grand-child with Pid :%d\n",(int)getpid());
            printf("Pid:%d::calling function\n",(int)getpid());
            current_users();
            printf("\nExiting process with Pid:%d\n",(int)getpid());
            exit(1);
        }
        printf("\nPid:%d waiting for its child process to end!\n",(int)getpid());
        wait(NULL);
        printf("\nExiting process with Pid:%d\n",(int)getpid());
        exit(0);
    }  

        printf("\nPid:%d waiting for its child process to end!\n",(int)getpid());
        wait(NULL);
    printf("\nExiting process with Pid:%d\n",(int)getpid());
    return 0;
}