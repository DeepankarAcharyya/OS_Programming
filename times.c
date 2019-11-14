#include<stdio.h>
#include<sys/times.h>
#include<sys/types.h>
#include<unistd.h>

int main(){
    struct tms t1;
    times(&t1);
    printf("\n %ld",t1.tms_cutime);
    printf("\n %ld",t1.tms_cstime);
    printf("\n %ld",t1.tms_stime);
    printf("\n %ld",t1.tms_utime);

    sleep(5);
    times(&t1);
    printf("\n %ld",t1.tms_cutime);
    printf("\n %ld",t1.tms_cstime);
    printf("\n %ld",t1.tms_stime);
    printf("\n %ld",t1.tms_utime);

}