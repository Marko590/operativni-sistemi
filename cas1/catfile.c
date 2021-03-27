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

    osAssert(2==argc,"Upotreba: ./catfile putanja ");
    
    int fd=open(argv[1],O_RDONLY);
    osAssert(-1!=fd,"Otvaranje nije uspelo");
    //ssize_t read(int fd, void *buf, size_t count);
    char buf[BUF_SIZE];

    int bytesRead=0;
    while((bytesRead=read(fd,buf,sizeof buf))>0)
    {
        osAssert(-1!=write(STDOUT_FILENO,buf,bytesRead),"Pisanje nije uspelo");

    }
    osAssert(-1!=bytesRead,"doslo je do greske prilikom citanja");
    close(fd);
    return 0;
}