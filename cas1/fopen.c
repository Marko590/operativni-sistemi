#include <sys/types.h>
       #include <sys/stat.h>
       #include <fcntl.h>
       #include <stdio.h>
       #include <stdbool.h>
#include <unistd.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
bool osOpenFile(const char *fpath, const char *mode, int *pFd){
     int flags=0;
     mode_t access_mode=0666;
    if(!strcmp(mode,"r")){
        flags |=O_RDONLY;
    }
    if(!strcmp(mode,"w")){
        flags |=O_WRONLY;
        flags |=O_TRUNC;
        flags |=O_CREAT;
    }
    if(!strcmp(mode,"a")){
        flags |=O_WRONLY;
        flags |=O_APPEND;
        flags |=O_CREAT;
    }
    if(!strcmp(mode,"r+")){
        flags |=O_RDWR;
        
    }
    if(!strcmp(mode,"w+")){
        flags|=O_RDWR;
    }
    if(!strcmp(mode,"a+")){
        flags|=O_APPEND;
    }
    *pFd=open(fpath,flags,access_mode);
    return *pFd!=-1;
}

#define osAssert(cond,msg) osErrorFatal(cond,msg,__FILE__,__LINE__)
void osErrorFatal(bool cond,const char *msg, const char *fname,int line){

    if(!cond){
        perror(msg);
        fprintf(stderr,"%s:%d\n",fname,line);
        exit(EXIT_FAILURE);
    }

}

int main(int argc, char** argv){

    osAssert(3==argc,"Upotreba: ./mkfile putanja mod (r,w,r+,a..)");
    int fd=0;
    osAssert(osOpenFile(argv[1],argv[2],&fd),"Otvaranje nije uspelo");
    printf("Fajl je uspesno kreiran/otvoren \n");
    return 0;
}