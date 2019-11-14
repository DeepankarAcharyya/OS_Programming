/*
Write a C program to get the process submission time & termination time of a process. For this
assignment your C program will create a child process and writes the submission and termination
time of the child process into a file. Learn about times() system call. Also learn about use of
gettimeofday() system call. 
*/
/*
SYSTEM CALLS:
        -times()
        -sysconf(_SC_CLK_TCK)
        -gettimeofday()
*/

/* 
STEPS:
-create a child and mark the time--> the submission time
-wait until the child process finishes
-mark the end time as termination time 
-write to the file the termination and the submission time
*/ 

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<time.h>
#include <sys/wait.h>

// struct tms {
// clock_t tms_utime;  /* user time */
// clock_t tms_stime;  /* system time */
// clock_t tms_cutime; /* user time of children */
// clock_t tms_cstime; /* system time of children */
// };

/*
struct timeval {
               time_t      tv_sec;     
               suseconds_t tv_usec; 
           };
*/

int main(){
    //structure to store the time
    time_t before,after;
    //define the frequency --- system dependent
    unsigned long freq=sysconf(_SC_CLK_TCK);
    //start the time
	before=time(NULL);
        int f=fork();
        if(f==0){
            printf("\nHey!This is the child! ");
            printf("\nChild's Pid=%d\nGoing to sleep for 10 secs",(int)getpid());
            sleep(10);
            printf("\nExiting the child!\n");
            exit(0);
        }
        wait(NULL);
	
    //stop the timer
    after=time(NULL);
    //open the file 
    FILE *fd=fopen("Assignment6B.txt","w");
    //write to the file 
    fprintf(fd,"Submission time: %s \n", ctime(&before));
	fprintf(fd,"termition time: %s \n", ctime(&after));
    
    //close the file
    fclose(fd);
    return 0;
}