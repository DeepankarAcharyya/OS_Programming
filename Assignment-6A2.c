//Assignment 6 A2
/*
Demonstrate the concept of shared memory
prog1--> responsible for writing its process id
prog2--> responsible for reading the contents (the process id of process 1)
        and remove the shared memory segment.
*/
#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdlib.h>
#include <unistd.h>

int main(){
    //creating the key  
    key_t key=ftok("shared_memory_Assignment6",105);
    //process ID
    pid_t p=getpid();
    //creating the shared memory
    int shared_memory_id=shmget(key,sizeof(p),0666|IPC_CREAT);
    printf("\nShared Memory Created!!");
    //attaching to the shared memory
    int *str = (int *) shmat(shared_memory_id,NULL,0);
    printf("\nShared Memory Attached!!");
    //reading from the shared memory
    printf("\nData read from the shared memory: %d\n",*str); 
    //detaching from shared memory
    shmdt(str);
    //removing the shared memory
    shmctl(shared_memory_id,IPC_RMID,NULL);
    return 0;
}