
#define _XOPEN_SOURCE 700
#include <sys/types.h>
       #include <sys/stat.h>
       #define _GNU_SOURCE
       #include <fcntl.h>
       #include <stdio.h>
       #include <stdbool.h>
       #include <inttypes.h>
#include <unistd.h>
#include <errno.h>
#include <stdlib.h>
#include <ftw.h>
#include <math.h>
#include <time.h>
#include <string.h>
#include <utime.h>
#include <limits.h>
#include <sys/types.h>
       #include <pwd.h>
#define SEC_PER_DAY (3600*24)
#define BUF_SIZE (4096)
#define osAssert(cond,msg) osErrorFatal(cond,msg,__FILE__,__LINE__)
void osErrorFatal(bool cond,const char *msg, const char *fname,int line){

    if(!cond){
        perror(msg);
        fprintf(stderr,"%s:%d\n",fname,line);
        exit(EXIT_FAILURE);
    }

}
// int nftw(const char *dirpath,int typeflag, struct FTW *ftwbuf), int nopenfd, int flags);

static int os_Days=0;
static time_t os_CurrentTime=0;
int osProcessFile(const char *fpath,const struct stat *sb,int typeflag, struct FTW *ftwbuf){
    if(S_ISREG(sb->st_mode))
    {
       time_t diffInSecs=os_CurrentTime - sb->st_ctime;
       int diffInDays=(int)((float)(diffInSecs)/SEC_PER_DAY);
       if(diffInDays<os_Days){
           printf("Putanja : %s Pre koliko dana : %d \n",fpath,diffInDays);
       }
;    }
    return 0;
}
int main(int argc, char** argv){

    osAssert(3==argc,"Upotreba: ./chmod putanja prava");
    os_CurrentTime=time(NULL);
    os_Days=atoi(argv[2]);
    
osAssert(-1!=nftw(argv[1],osProcessFile,50,FTW_PHYS),"obilazak nije uspeo");
     
    return 0;
}