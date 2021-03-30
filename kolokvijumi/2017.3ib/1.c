#include <sys/types.h>
       #include <sys/stat.h>
       #include <fcntl.h>
       #include <stdio.h>
       #include <stdbool.h>
#include <unistd.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#define SECS_PER_DAY (3600*24)
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

    osAssert(2==argc,"Upotreba: ./cpfile odakle gde");
    struct stat finfo;
    osAssert(-1!=lstat(argv[1],&finfo),"Fetching of the fileinfo was unsuccessful.");

    if(S_ISREG(finfo.st_mode)){
        time_t diffSecs=abs(finfo.st_atim.tv_sec-finfo.st_ctim.tv_sec);
        printf("Atim:%ld ctim:%ld\n",finfo.st_atim.tv_sec,finfo.st_ctim.tv_sec);
        int diffDays=(int)(diffSecs/(float)SECS_PER_DAY);
        printf("%d",diffDays);
        return 0;
    }
    
    return 1;
}