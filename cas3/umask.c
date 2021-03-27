
#define _XOPEN_SOURCE 700
#include <sys/types.h>
       #include <sys/stat.h>
       #include <fcntl.h>
       #include <stdio.h>
       #include <stdbool.h>
       #include <inttypes.h>
#include <unistd.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <utime.h>
#include <limits.h>
#include <sys/types.h>
       #include <pwd.h>

#define BUF_SIZE (4096)
#define osAssert(cond,msg) osErrorFatal(cond,msg,__FILE__,__LINE__)
void osErrorFatal(bool cond,const char *msg, const char *fname,int line){

    if(!cond){
        perror(msg);
        fprintf(stderr,"%s:%d\n",fname,line);
        exit(EXIT_FAILURE);
    }

}


int main(int argc, char** argv){

    osAssert(3==argc,"Upotreba: ./umask_demo putanja prava");

    const char *fpath=argv[1];
    const char *accessStr=argv[2];
    mode_t accessMode= (mode_t)strtol(accessStr,NULL,8);
    mode_t oldMask=umask(0);
    int fd=open(fpath,O_CREAT,accessMode);
    osAssert(-1!=fd,"Kreiranje fajla nije uspelo");

    close(fd);
    umask(oldMask);
    return 0;
}