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
    osAssert(3==argc,"Upotreba: ./catfile src dest");
    int fdSrc = open(argv[1],O_RDONLY);
    int fdDest= open(argv[2],O_CREAT|O_WRONLY);
    osAssert(-1!=fdSrc,"Otvaranje prvog fajla nije uspesno.");
    osAssert(-1!=fdDest,"Otvaranje drugog fajla nije uspesno.");
    char *buf[BUF_SIZE];
    int bytesread=0;
    while((bytesread=read(fdSrc,buf,sizeof buf))>0){
        osAssert(-1!=write(fdDest,buf,bytesread),"Pisanje nije uspelo");
    }


    close(fdSrc);
    close(fdDest);
}