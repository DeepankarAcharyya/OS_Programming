#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

int main(){
    char input_string[200];
    //setting the pathname-->fifo name
    char* path="my_fifo_1";
    //creating the named pipe/fifo
    mknod(path, S_IFIFO | 0640,0);
    //opening the fifo
    int fd=open(path,O_RDWR);
    //wait-->sleep
    sleep(3);
    //read from the fifo
    int last_index=read(fd,input_string,sizeof(input_string));
    input_string[last_index]='\0';
    //display the content
    printf("\nReceived String from Program 2:%s\n",input_string);
    //send acknowledgement mssg
    write(fd,"ACK",strlen("ACK"));
    return 0;
}