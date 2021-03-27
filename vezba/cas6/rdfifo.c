
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
    srand(time(NULL));
    osAssert(2==argc,"Upotreba: ./fifo_writer putanja_do_fifa");

    int fifoFd=open(argv[1],O_RDONLY);

    osAssert(-1!=fifoFd,"Otvaranje pipe nije uspelo");
    int bytesRead=0;
    int num=0;
    while(bytesRead=read(fifoFd,&num,sizeof num)>0){
        printf("Citamo broj :%d\n",num);

    }
    osAssert(bytesRead!=-1,"Citanje nije uspelo");
    
fprintf(stderr,"Pisemo u fifo fajl\n");
    
   close(fifoFd);

    return 0;
}