/*
Write a C program to create a user level thread using system call pthread_create( )
 and assign the thread to display the “HELLO WORLD” . Use pthread_exit() in your 
 program (if possible) for terminating the thread. 
 */
#include <stdio.h> 
#include <stdlib.h>  
#include <pthread.h> 

void *ThreadFunction() { 
    printf("\nHello World!\n"); 
    pthread_exit(NULL); 
} 
   
int main(){ 
    pthread_t thread_id; 
    printf("Before Thread\n"); 
    pthread_create(&thread_id, NULL,ThreadFunction, NULL); //user level threads because the arguments are NULL
    printf("Thread Ended\n"); 
    return 0; 
}