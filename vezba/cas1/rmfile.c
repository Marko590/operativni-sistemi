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
    osAssert(3==argc,"Upotreba: ./rmfile ime opcija");

    char* ime=argv[1];
    char* opcija=argv[2];

    if(!strcmp("-d",opcija)){
        osAssert(rmdir(ime)!=-1,"Brisanje direktorijuma nije uspesno");
    }
    else if(!strcmp("-f",opcija)){
        osAssert(unlink(ime)!=-1,"Brisanje fajla nije uspesno");

    }
    else{
        osAssert(false,"Pogresna opcija");
    }

}