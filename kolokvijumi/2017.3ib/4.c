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

    osAssert(4==argc,"Upotreba: ./cpfile odakle gde");
    int fd=open(argv[1],O_RDONLY);
    osAssert(-1!=fd,"Opening of the file was unsuccessful.");

    osAssert(-1!=lseek(fd,atoi(argv[2]),SEEK_SET),"Setting of the offset wasnt successful");

    int bytesRead=0;

    char buf[1024];
    osAssert(-1!=read(fd,buf,atoi(argv[3])),"Reading was unsuccessful");
        printf("%s",buf);
    

    return 0;
}