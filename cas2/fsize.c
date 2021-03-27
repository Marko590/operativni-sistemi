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
#include <limits.h>
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

    osAssert(2==argc,"Upotreba: ./fsize putanja");
    
    int fd=open(argv[1],O_RDONLY);
    osAssert(-1!=fd,"Ne postoji source");
    off_t endOfFilePos=lseek(fd,0,SEEK_END);
    osAssert(-1!=endOfFilePos,"Pomeranje nije uspelo");
    printf("Velicina fajla je: %ld", (intmax_t)endOfFilePos);
    return 0;
}