#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc,char* argv[]){
    char input_string[200];
    //setting the pathname-->fifo name
    char* path="my_fifo_1";
    //accept the input string as cmd line argument
    if(argc<2){
        printf("\nInsufficient arguments!\n");
        exit(0);
    }
    else{
        strcpy(input_string,argv[1]);
    }
    //open the fifo
    int fd=open(path,O_RDWR);
    //send the input string
    write(fd,input_string,strlen(input_string));
    //sleep-->for synchronization purpose
    sleep(3);
    //wait for acknowledgement-->read from the fifo
    int last_index=read(fd,input_string,sizeof(input_string));
    input_string[last_index]='\0';
    //display the acknowledgement mssg and display it
    printf("\nReceived String from Program 1:%s\n",input_string);
    //exit the program
    return 0;
}