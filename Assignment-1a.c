/*
Assignment 1(a):-
Write a C program to create a child process using the system call fork( ). From the child process, display
the PID and PPID and then call again the fork( ) to create a grandchild and engage him to display your roll
no. From parent display the PID and PPID of all the processes and display the count of total no. of child
processes created also the number of grandchild processes created. Demonstrate the use of exit(0) and
exit(1). 
*/
#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<unistd.h>
#include<sys/wait.h>

int main(){
    //using pipes to share the info between the processes
    int shared_pid_data[2],shared_count_child[2],shared_count_grand[2];
    int count_child,count_grand,pid_g;
    
    //creating the pipes
    int return_status1=pipe(shared_pid_data);
    int return_status2=pipe(shared_count_child);
    int return_status3=pipe(shared_count_grand);

    if(return_status1<0 || return_status2<0 || return_status3<0 ){
        printf("\nFailed to create pipe(s)!\n");
        exit(1);
    }
    printf("\nPipes Created!\n");
    int z=0;
    write(shared_count_child[1],&z,sizeof(z));
    write(shared_count_grand[1],&z,sizeof(z));
        
    printf("i am the parent with pid: %d\n",(int) getpid());
    pid_t pid=fork();
    
    if (pid<0){
        perror("Fork Failed\n");
        exit(1);
    }
    else if(pid ==0){
         printf("\nI am the child \n Pid : %d\n PPID : %d\n",(int)getpid(),(int)getppid());
        
         read(shared_count_child[0],&z,sizeof(z));
         z++;
         write(shared_count_child[1],&z,sizeof(z));

        pid_t pid_grand=fork();
        if (pid_grand<0){
            perror("Fork Failed\n");
            exit(1);
        }
        else if(pid_grand==0){

             read(shared_count_grand[0],&z,sizeof(z));
             z++;
             write(shared_count_grand[1],&z,sizeof(z));
            
            int add=(int)getpid();
            write(shared_pid_data[1],&add,sizeof(int));
            
            printf("\nI am the Grand-child with Pid :%d\n and PPid:%d\n",(int)getpid(),(int)getppid());
            printf("\nPid:%d::My Roll-No is : CSB17017\n",(int)getpid());
            printf("\nExiting process with Pid:%d\n",(int)getpid());
            
            exit(0);
        }

        wait(NULL);
        printf("\nExiting process with Pid:%d\n",(int)getpid());
        int temp=(int)pid_grand;
        exit(temp);
        
        }

     wait(NULL);
     
     read(shared_count_grand[0],&count_grand,sizeof(count_grand));
     read(shared_count_child[0],&count_child,sizeof(count_child));
     read(shared_pid_data[0],&pid_g,sizeof(pid_g));
     
     printf("\n For parent PID:%d\n", (int) getpid());
     printf("\n For child PID:%d and PPID:%d\n",(int)pid,(int) getpid());
     printf("\n For grandchild PID:%d and PPID:%d\n",pid_g,(int)pid);
     printf("\n count child:%d  grandchild:%d \n",count_child,count_grand);

     printf("\nExiting process with Pid:%d\n",(int)getpid());
     return 0;
}