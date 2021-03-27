
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

    struct statfinfo;
    osAssert(-1!=lstat(argv[1],&finfo),"dohvatanje inf nije uspelo");
    struct utimbuf oldTimes;
    oldTimes.actime=finfo.st_atime;
    oldTimes.modtime=finfo.st_mtime;
    osAssert(-1!=utime(argv[1],&oldTimes),"Vracanje vremena na staro nije uspelo");
    return 0;
}