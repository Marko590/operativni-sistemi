#include <sys/types.h>
       #include <sys/stat.h>
       #include <fcntl.h>
       #include <stdio.h>
       #include <stdbool.h>
#include <unistd.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
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
    
    int fdSrc=open(argv[1],O_RDONLY);
    osAssert(-1!=fdSrc,"Ne postoji source");
    int fdDest=open(argv[2],O_WRONLY|O_TRUNC|O_CREAT,0666);
    osAssert(-1!=fdDest,"Ne postoji destinacija");
    //ssize_t read(int fd, void *buf, size_t count);
    char buf[BUF_SIZE];

    int bytesRead=0;
    while((bytesRead=read(fdSrc,buf,sizeof buf))>0)
    {
        osAssert(-1!=write(fdDest,buf,bytesRead),"Pisanje nije uspelo");

    }
    osAssert(-1!=bytesRead,"doslo je do greske prilikom citanja");
    close(fdDest);
    close(fdSrc);
    return 0;
}