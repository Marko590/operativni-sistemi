
#define _DEFAULT_SOURCE
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
#include <signal.h>

#include <sys/wait.h>
 #include <time.h>
       #include <pwd.h>
       #include <sys/mman.h>
       #include <sys/stat.h>        /* For mode constants */
       #include <fcntl.h>  
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

static int os_WhichSignal=-1;
void onSignalInterrupt(int signum){
    os_WhichSignal=signum;
}



int main(int argc, char** argv){
    fprintf(stderr,"%jd",(intmax_t)getpid());
    osAssert(SIG_ERR!=signal(SIGINT,onSignalInterrupt),"Postavljanje hendlera za SIGINT nije uspelo");

    while(1){
        fprintf(stderr,"Idalje smo u petlji");
        pause();
        

    }

    
    return 0;
}