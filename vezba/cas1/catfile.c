#include <stdio.h>
#include <stdbool.h>
#include <errno.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#define BUF_SIZE 4096

#define osAssert(cond, msg) osErrorFatal(cond, msg, __FILE__, __LINE__)

void osErrorFatal(bool cond, char *msg, char *file, int line)
{
    if (!cond)
    {
        perror(msg);
         fprintf(stderr,"%s:%d\n",file,line);
        exit(EXIT_FAILURE);
    }
}

int main(int argc, char **argv)
{
    osAssert(2==argc,"Upotreba: ./catfile putanja");
    int fd = open(argv[1],O_RDONLY);
    osAssert(-1!=fd,"Uspevanje fajla nije uspesno.");
    char *buf[BUF_SIZE];
    int bytesread=0;
    while((bytesread=read(fd,buf,sizeof buf))>0){
        osAssert(-1!=write(STDOUT_FILENO,buf,bytesread),"Pisanje nije uspelo");
    }


    close(fd);
}