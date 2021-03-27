#include <sys/types.h>
       #include <sys/stat.h>
       #include <fcntl.h>
       #include <stdio.h>
       #include <stdbool.h>
#include <unistd.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>

#define osAssert(cond,msg) osErrorFatal(cond,msg,__FILE__,__LINE__)
void osErrorFatal(bool cond,const char *msg, const char *fname,int line){

    if(!cond){
        perror(msg);
        fprintf(stderr,"%s:%d\n",fname,line);
        exit(EXIT_FAILURE);
    }

}

int main(int argc, char** argv){

    osAssert(2==argc,"Upotreba: ./mkdir putanja ");
    int fd=0;
    mode_t accessMode=0777;
    osAssert(-1!=mkdir(argv[1],accessMode),"Pravljenje direktorijuma nije uspelo");
    printf("Fajl je uspesno kreiran/otvoren \n");
    return 0;
}