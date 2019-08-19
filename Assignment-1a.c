/*
Assignment 1(a):-
Write a C program to create a child process using the system call fork( ). From the child process, display
the PID and PPID and then call again the fork( ) to create a grandchild and engage him to display your roll
no. From parent display the PID and PPID of all the processes and display the count of total no. of child
processes created also the number of grandchild processes created. Demonstrate the use of exit(0) and
exit(1). 
*/

//need to set up a shared memory
#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<unistd.h>
#include<sys/wait.h>

int main(){
    printf("i am the parent with pid: %d\n",(int) getpid());
    pid_t pid=fork();
    
    if (pid<0){
        perror("Fork Failed\n");
        exit(1);
    }
    else if(pid ==0){
        printf("\nI am the child \n Pid : %d\n PPID : %d\n",(int)getpid(),(int)getppid());
        pid_t pid_grand=fork();
        if (pid_grand<0){
            perror("Fork Failed\n");
            exit(1);
        }
        else if(pid_grand==0){
            printf("I am the Grand-child with Pid :%d\n",(int)getpid());
            printf("Pid:%d::My Roll-No is : CSB17017\n",(int)getpid());
            printf("\nExiting process with Pid:%d\n",(int)getpid());
            exit(0);
        }
        wait(NULL);
        printf("\nExiting process with Pid:%d\n",(int)getpid());
        int temp=(int)pid_grand;
        exit(temp);
        }
     
    // printf("\nFrom the parent:\n");
    // printf("\n For parent PID:%d\n", (int) getpid());
    // printf("\n For child PID:%d and PPID:%d\n",(int)pid,(int) getpid());
    // printf("\n For grandchild PID:%d and PPID:%d\n",grand,pid);
    // //printf("\n count child:%d  grandchild:%d \n",a.count_child,a.count_grand);
    // printf("\nExiting process with Pid:%d\n",(int)getpid());
     return 0;
}