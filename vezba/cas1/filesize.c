#include <stdio.h>
#include <stdbool.h>
#include <errno.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <inttypes.h>
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
    osAssert(2==argc,"Upotreba: ./filesize ime");
    int fd=open(argv[1],O_RDONLY);
    osAssert(-1!=fd,"Otvaranje fajla nije uspesno");
    
    off_t fsize=lseek(fd,0,SEEK_END);
    osAssert(-1!=fsize,"Greska u citanju fajla");

    printf("Velicina fajla je : %jd",(intmax_t)fsize);

}