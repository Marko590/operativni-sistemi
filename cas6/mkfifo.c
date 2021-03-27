
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

    fprintf(stderr,"Pravimo fifo fajl za pisanje\n");

    osAssert(-1!=mkfifo(argv[1],0666),"Pravljenje fifo fajla nije uspelo");
    
    fprintf(stderr,"Otvaramo fifo fajl za pisanje\n");

    int fifoFd=open(argv[1],O_WRONLY);

    osAssert(-1!=fifoFd,"Otvaranje fifo fajla nije uspelo");

    srand(time(NULL));
fprintf(stderr,"Pisemo u fifo fajl\n");
    
    for(int i=0;i<10;i++){
        int num=rand();
    
        osAssert(-1!=write(fifoFd,&num,sizeof num),"Pisanje u fifo nije uspelo");
        fprintf(stderr,"Upisujemo broj: %d\n", num);
        sleep(1);
    }
fprintf(stderr,"Pisanje je gotovo\n");
    close(fifoFd);
    return 0;
}