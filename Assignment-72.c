//Assignment 7.1
/*
Open a file -> read the contents
*/

#include <stdio.h>
#include <sys/sem.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <sys/ipc.h>
//compile with -lrt

#define key 0x111

struct sembuf p = { 0, -1, SEM_UNDO}; //semwait
struct sembuf v = { 0, +1, SEM_UNDO}; //semsignal

int main(){
    FILE* fd;
    char string[25];
    struct sembuf sem_op;
    
    //create a semaphore and initialize its value with 1
    int semid=semget(key,1,IPC_CREAT | 0660);
    if (semid == -1) {
        perror("\nsemget");
        exit(1);
    }
    
    //shared memory
    key_t keysh = ftok("shmfile",69);  
    int shmid = shmget(key,1024,0666|IPC_CREAT);  
    int *str = (int*) shmat(shmid,(void*)0,0); 

    int count=*str;
    
    //entering into loop
    int i=0;
    while(i<count){
    //wait
    semop(semid, &p, 1);

    //open the file
    fd=fopen("Assignment7.txt","r");
    if(fd){
        fscanf(fd,"%s",string);
        printf("\nIteration:%d :: %s",i+1,string);
        fclose(fd);
    }

    //signal
    semop(semid, &v, 1);
    i++;
    }

    //destroying the shared memory and semaphores
    printf("\nDestroying Shared Memory");
    shmctl(shmid,IPC_RMID,NULL);
    shmctl(semid,IPC_RMID,NULL);
    printf("\nDestroyed Semaphores\n");
    
    return 0;
}

/*
Functions :
--------semget(key_t key, int nsems, int oflag)
--------semop(int semid, struct sembuf *opsptr, size_t nops) 
--------semctl(int semid, int semnum, int cmd, arguments) 

--------sem_wait(sem_t *sem)-->lock / wait
--------sem_post(sem_t *sem)-->release/signal 
--------sem_init()-->for processes or threads 
--------sem_open()-->for IPC

struct sembuf {
                ushort  sem_num;         semaphore index in array 
                short   sem_op;          semaphore operation 
                short   sem_flg;         operation flags 
        };
*/