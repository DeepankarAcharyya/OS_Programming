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
#include<sys/ipc.h>
#include<sys/shm.h>

struct ids1{
    int count_child;
    int count_grandchild;
    int parent;
    int child;
    int grandchild;
};

int main(){
    struct ids1 a;
    printf("i am the parent with pid: %d\n",(int) getpid());
    a.parent = (int)getpid();
    pid_t pid=fork();
    a.count_child=1;
    a.count_grandchild=1;
    // ftok to generate unique key
    key_t key = 17017;
    // shmget returns an identifier in shmid
    int shmid = shmget(key, sizeof(struct ids1), 0666 | IPC_CREAT);
    // shmat to attach to shared memory
    char *str = (char *)shmat(shmid, (void *)0, 0);

    if (pid<0){
        perror("Fork Failed\n");
        exit(1);
    }
    else if(pid ==0){
        printf("\nI am the child \n Pid : %d\n PPID : %d\n",(int)getpid(),(int)getppid());
        a.child=(int)getpid();
        a.count_child=a.count_child+1;
        pid_t pid_grandchild=fork();

        if (pid_grandchild<0){
            perror("Fork Failed\n");
            exit(1);
        }
        else if(pid_grandchild==0){
            a.grandchild = (int)getpid();
            a.count_grandchild = a.count_grandchild + 1;
            printf("I am the Grand-child with Pid :%d\n",(int)getpid());
            printf("Pid:%d::My Roll-No is : CSB17017\n",(int)getpid());
            printf("\nExiting process with Pid:%d\n",(int)getpid());
            exit(0);
        }
        printf("\nExiting process with Pid:%d\n",(int)getpid());
        exit(0);}
    printf("\nFrom the parent:\n");
    printf("\n For parent PID:%d\n", a.parent);
    printf("\n For child PID:%d and PPID:%d\n",a.child,a.parent);
    printf("\n For grandchild PID:%d and PPID:%d\n", a.grandchild, a.child);
    printf("\n count child:%d  grandchild:%d \n",a.count_child,a.count_grandchild);
    printf("\nExiting process with Pid:%d\n",(int)getpid());
    //detach from shared memory
    shmdt(str);
    // destroy the sharsed memory
    shmctl(shmid, IPC_RMID, NULL);
    return 0;
}