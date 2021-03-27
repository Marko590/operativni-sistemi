
#define _XOPEN_SOURCE 700
#include <sys/types.h>
       #include <sys/stat.h>
       #include <fcntl.h>
       #include <stdio.h>
       #include <stdbool.h>
       #include <inttypes.h>
#include <unistd.h>
#include <ctype.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <utime.h>
#include <limits.h>
#include <sys/types.h>
#include <sys/wait.h>
 #include <time.h>
       #include <pwd.h>
#define IS_CHILD(pid) (pid==0)
#define BUF_SIZE (4096)
#define RD_END (0)
#define WR_END (1)
#define MAX_LINE (4096)
#define osAssert(cond,msg) osErrorFatal(cond,msg,__FILE__,__LINE__)
void osErrorFatal(bool cond,const char *msg, const char *fname,int line){

    if(!cond){
        perror(msg);
        fprintf(stderr,"%s:%d\n",fname,line);
        exit(EXIT_FAILURE);
    }

}






int main(int argc, char** argv){

    osAssert(2==argc,"Upotreba: ./fifo_writer putanja_do_fifa");

   

    fprintf(stderr,"Otvaramo fifo fajl za citanje\n");

    int fifoFd=open(argv[1],O_RDONLY);

    osAssert(-1!=fifoFd,"Otvaranje fifo fajla nije uspelo");

    srand(time(NULL));
fprintf(stderr,"Citamo iz fifo fajla\n");
    int num=0;
    int bytesRead=0;
    int totalBytesRead=0;
    while((bytesRead=read(fifoFd,&num,sizeof num))>0){
        

        fprintf(stderr,"Procitali smo : %d\n",num);
    }
    osAssert(-1!=bytesRead,"doslo je do greske prilikom citanja iz fifa");

fprintf(stderr,"Pisanje je gotovo\n");
    close(fifoFd);
    return 0;
} 