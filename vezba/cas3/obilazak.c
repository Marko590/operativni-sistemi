
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
       #include <dirent.h>
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

int main(int argc, char** argv){
    osAssert(3==argc,"Upotreba: ./obilazak putanja datum");
    
    DIR *dirStruct=opendir(argv[1]);
    osAssert(NULL!=dirStruct,"Otvaranje dir. nije uspelo");

    struct dirent *dirEntry=NULL;

    while((dirEntry=readdir(dirStruct)!=NULL)){

        struct stat *statbuf=NULL;
        osAssert(-1!=stat(dirEntry,&statbuf),"Dohvatanje inf o tekucem fajlu nije uspelo");

        

    }


    osAssert(3==argc,"Upotreba: ./chmod putanja prava");
    
     
    return 0;
}