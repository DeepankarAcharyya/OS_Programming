/*
Assignment 3a:
Write a C program to handle the reception of INTERRUPT FROM THE
KEYBOARD signal by executing a particular (user) function, which function is
responsible for creating a child process by using fork() system call. Also, the child
process will take an input N (N is the no. of terms to generate the Fibonacci series)
from the user and generate the Fibonacci series up to N terms. Then the child
process will send the Fibonacci series terms one by one to the parent process by
using pipe() system call and the parent process will read the Fibonacci series terms
one by one and will display it.
(N.B. – Before sending the Fibonacci terms one by one from the child
process, first you send the Process ID of the child process to the parent process and
read and display it in the parent process. Again after sending the terms one by one
from the child process to the parent process, from the child process you send the
Signal ID for which handler function has been generated and read and display it in
the parent process.)
*/

#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<signal.h>
#include<stdlib.h>
#include<sys/wait.h>

void user_defined_function_3a(){
    int pipe_des[2];
    int k=pipe(pipe_des);
    if(k==-1){
        printf("\nError in creating pipe!!!\n");
    }

    pid_t childpid;
    childpid=fork();
    
    if(childpid==0){
        int n;
        int a=0,b=1,i=0,c;
        
        //send back the pid via pipe
        close(pipe_des[0]);
        c=(int) getpid();
        printf("\nFrom child:%d\n",c);
        write(pipe_des[1],&c,sizeof(int));
        //close(pipe_des[1]);
        
        sleep(1);

        //get the value of N
        printf("\nEnter the value of N:");
        scanf("%d",&n);
        
        //generate the N fibonnaci terms
        
        //write the terms to the pipe
        while(i<n){
            c=a+b;
            close(pipe_des[0]);
            write(pipe_des[1],&a,sizeof(int));
            //printf("\nFrom CHild: %d\n",b);
            a=b;
            b=c;
            i++;
            sleep(1);
        }
        //write the termination signal
        c=-1;
        close(pipe_des[0]);
        write(pipe_des[1],&c,sizeof(int));
        //close(pipe_des[1]);
            
        exit(0);
    }
    int m;
    while(1){
        close(pipe_des[1]);
        read(pipe_des[0],&m,sizeof(int));
        //close(pipe_des[0]);
        printf("\nFrom Parent\t%d\n",m);
        if(m==-1)
            exit(0);
        sleep(1);
        
    }

}

int main(){
    signal(SIGINT,user_defined_function_3a);
    while(1){
        sleep(1);
        printf("\nTic-Tok\n");
    }
    return 0;
}