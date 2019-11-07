// Assignment 6 A1
/*
Demonstrate the concept of shared memory
prog1--> responsible for writing its process id
prog2--> responsible for reading the contents (the process id of process 1)
        and remove the shared memory segment.
*/

#include <stdio.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <sys/shm.h>
#include <stdlib.h>
#include <string.h>
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
    //writing to the shared memory
    *str=(int)p;
    printf("\nWritten to the shared memory pid=%d\n",(int)p);
    return 0;
}

/*
Create the shared memory segment or use an already created shared memory segment (shmget())
Attach the process to the already created shared memory segment (shmat())
Detach the process from the already attached shared memory segment (shmdt())
Control operations on the shared memory segment (shmctl())
*/