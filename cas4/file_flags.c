
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
#include <ftw.h>
#include <time.h>
#include <string.h>
#include <utime.h>
#include <limits.h>
#include <sys/time.h>
#include <sys/types.h>
       #include <pwd.h>

#define BUF_SIZE (1024)
#define osAssert(cond,msg) osErrorFatal(cond,msg,__FILE__,__LINE__)
void osErrorFatal(bool cond,const char *msg, const char *fname,int line){

    if(!cond){
        perror(msg);
        fprintf(stderr,"%s:%d\n",fname,line);
        exit(EXIT_FAILURE);
    }

}
// int nftw(const char *dirpath,int typeflag, struct FTW *ftwbuf), int nopenfd, int flags);



int main(int argc, char** argv){

    osAssert(3==argc,"Upotreba: ./chmod putanja prava");
    
    return 0;
}