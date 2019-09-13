/*
Assignment 2a:
Write a C program using signal() system call to handle the reception of SIGINT signal
 which allows to execute a designated (user) function. Here the function is responsible 
 for creating a child process by using fork() system call and then you have to display 
 the PROCESS ID and PARENT PROCESS ID from the parent process as well as from the child process. 
*/

#include<stdio.h>
#include<signal.h>
#include<sys/types.h>
#include<unistd.h>
#include<stdlib.h>

void  sighandler(){
	pid_t child=fork();
	if (child==0){	
			printf("\nThis is the Child with Pid=%d and PPID = %d\n",getpid(),getppid());
			exit(0);
		}
	else if(child>0){
			printf("\nThis is the parent  with Pid = %d,and my child's Pid = %d\n",getpid(),child);
	  	}
		exit(0);
}	

int main(){
	printf("\nMain Program\nProgram Started\n");
	signal(SIGINT,sighandler);

	while(1)
		sleep(1);

    return 0;
}