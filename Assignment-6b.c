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
#include<sys/times.h>
#include <sys/wait.h>

// struct tms {
// clock_t tms_utime;  /* user time */
// clock_t tms_stime;  /* system time */
// clock_t tms_cutime; /* user time of children */
// clock_t tms_cstime; /* system time of children */
// };

int main(){
    //structure to store the time
    struct tms before,after;
    //define the frequency --- system dependent
    unsigned long freq=sysconf(_SC_CLK_TCK);
    //start the time
    time_t start;
	if ((start = times(&before))!=-1) {
        int f=fork();
        if(f==0){
            printf("\nHey!This is the child! ");
            printf("\nChild's Pid=%d\nGoing to sleep for 10 secs",(int)getpid());
            sleep(10);
            printf("\nExiting the child!\n");
            exit(0);
        }
        wait(NULL);
	}
    //stop the timer
    time_t end;
    end = times(&after);
    //open the file 
    FILE *fd=fopen("Assignment6B.txt","w");
    //write to the file 
    // fprintf(fd,"Submission time: %lf seconds\n", (double)(t1.tms_stime));
	// fprintf(fd,"termition time: %lf seconds\n", (double)(t2.tms_utime)/freq);
    printf("\n%ld",start);
    printf("\n%ld",end);
    printf("\n%ld",after);
    printf("\n%ld",before);
    printf("\n%ld",(end-start)/freq);
    printf("\n%ld\n",(end-start));
    
    //close the file
    fclose(fd);
    return 0;
}