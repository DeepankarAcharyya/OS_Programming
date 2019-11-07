/*Assignment 4
Problem Statement:
Write a C program which will be able to read a file using read()
system call. Now you provide a mechanism to set a lock by using fcntl()
system call and to release the lock by using the same fcntl() system call.
For setting up and releasing out a lock, you have to fill up a structure flock
(struct flock) with proper values.
Now you run the program from two different terminals simultaneously and
demonstrate that if one process has got the lock, then that process only can read
the file. But the other one is not permitted to read the file until the lock is
released by the first process. That means, only one process who acquires the
lock can read the file at any instant of time. 
*/
//import files
#include <fcntl.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>

int main(){
    int fd;
    //declaring the structure of the flock and setting up its members:
    struct flock f1;
    f1.l_type=F_RDLCK;
    f1.l_whence=SEEK_SET;
    f1.l_start=0;
    f1.l_len=0;
    f1.l_pid=getpid();
    //opening the file
    if ((fd = open("demo.txt", O_RDWR)) == -1) {
    		perror("\nError in opening the file!\n");
    		exit(1);
    	}
    //check and set the lock
    if (fcntl(fd, F_SETLK, &f1) == -1) {
    		perror("\nerror in fcntl-lock");
    		exit(1);
    	}
    else 
        printf("\nApplied Read Lock!\n");
    //read the file
    char read_string[200];
    int last_index=read(fd,read_string,sizeof(read_string));
    read_string[last_index]='\0';
    puts(read_string);
    //write to the file
    strcpy(read_string,"\nRead Lock Applied!");
    last_index=write(fd,read_string,sizeof(read_string));
    
    //release the lock
    f1.l_type = F_UNLCK;
    printf("\nPress <RETURN> to unlock the file!\n");
    getchar();
    if (fcntl(fd, F_SETLK, &f1) == -1) {
            close(fd);
    		perror("\nerror in fcntl-release!");
    		exit(1);
    	}
    printf("\nUnlocked.\n");

    //setting read lock
    f1.l_type = F_WRLCK;
    printf("\nPress <RETURN> to write lock the file!\n");
    getchar();
    if (fcntl(fd, F_SETLK, &f1) == -1) {
    		perror("\nerror in fcntl-write lock!");
    		exit(1);
    	}
    else
    {
            printf("\nApplied Write Lock!\n");
    }
    //read the file
    char read_string_1[200];
    lseek (fd, 0, SEEK_SET); 
    last_index=read(fd,read_string_1,sizeof(read_string_1));
    read_string[last_index]='\0';
    puts(read_string_1);

    //write to the file
    strcpy(read_string_1,"\nWrite Lock Applied!");
    last_index=write(fd,read_string_1,sizeof(read_string_1));
    
    
    f1.l_type = F_UNLCK;
    printf("\nPress <RETURN> to unlock the file!\n");
    getchar();
    if (fcntl(fd, F_SETLK, &f1) == -1) {
    		perror("\nerror in fcntl-release!");
    		exit(1);
    	}
    printf("\nUnlocked.\n");


    close(fd);
    return 0;
}