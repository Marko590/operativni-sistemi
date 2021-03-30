#include <sys/types.h>
       #include <sys/stat.h>
       #include <fcntl.h>
       #include <stdio.h>
       #include <stdbool.h>
#include <unistd.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#define BYTES_PER_KB (1024)
#define KB_PER_MB (BYTES_PER_KB*1024)
#define MB_PER_GB (KB_PER_MB*1024)
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

    osAssert(3==argc,"Upotreba: ./cpfile odakle gde");
    struct stat finfo;
    osAssert(-1!=lstat(argv[1],&finfo),"Fetching of the fileinfo was unsuccessful.");
    int size;
    off_t size_in_bytes=finfo.st_size;

    if(strcmp(argv[2],"KB")==0){
        size=ceil(size_in_bytes/(float)BYTES_PER_KB);
        printf("%s %d",argv[1],size);
    }
    
    
    else if(strcmp(argv[2],"MB")==0){
        size=ceil(size_in_bytes/(float)KB_PER_MB);
        printf("%s %d",argv[1],size);
    }
    
    else if(strcmp(argv[2],"GB")==0){
        size=ceil(size_in_bytes/(float)MB_PER_GB);
        printf("%s %d",argv[1],size);
    }
    return 0;
}