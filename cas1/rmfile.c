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

    osAssert(3==argc,"Upotreba: ./rmfile opcija (-d,-f) putanja");
    int fd=0;
    const char *option=argv[1];
    const char *fpath =argv[2];
    if(!strcmp(option,"-f")){
            osAssert(unlink(fpath),"brisanje reg fajla nije uspelo");
    }
    else if(!strcmp(option,"-d")){
        osAssert(-1!=rmdir(fpath),"brisanje praznog direktorijuma nije uspelo");

    }
    else{
        osAssert(false,"Neispravna opcija");
    }
    printf("Fajl je uspesno kreiran/otvoren \n");
    return 0;
}