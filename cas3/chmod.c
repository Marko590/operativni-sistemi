
#define _XOPEN_SOURCE 700
#include <sys/types.h>
       #include <sys/stat.h>
       #include <fcntl.h>
       #include <stdio.h>
       #include <stdbool.h>
       #include <inttypes.h>
#include <unistd.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <utime.h>
#include <limits.h>
#include <sys/types.h>
       #include <pwd.h>
#include <dirent.h>
#define BUF_SIZE (4096)
#define osAssert(cond,msg) osErrorFatal(cond,msg,__FILE__,__LINE__)
void osErrorFatal(bool cond,const char *msg, const char *fname,int line){

    if(!cond){
        perror(msg);
        fprintf(stderr,"%s:%d\n",fname,line);
        exit(EXIT_FAILURE);
    }

}
void osTraverseDir(const char *fpath,unsigned *pSize){

    fprintf(stderr,"putanja %s\n",fpath);
    struct stat finfo;
    osAssert(-1!=lstat(fpath,&finfo),"dohvatanje inf o tekucem fajlu nije uspelo");

    *pSize+=finfo.st_size;

    if(S_ISDIR(finfo.st_mode)){
        DIR *pDir=opendir(fpath);
        osAssert(NULL!=pDir,"otv dir. nije uspelo");
        struct dirent *pEntry=NULL;
        while((pEntry=readdir(pDir))!=NULL){
            if(!strcmp(".",pEntry->d_name)||!strcmp("..",pEntry->d_name))
                continue;
            char *newPath=calloc(strlen(fpath)+1+strlen(pEntry->d_name)+1,1);
            osAssert(NULL!=newPath,"aloc nije uspelo");
            sprintf(newPath,"%s/%s",fpath,pEntry->d_name);
            osTraverseDir(newPath,pSize);
        }
        osAssert(0==errno,"doslo je do greske prilikom izlistavanja");
        closedir(pDir);
    }
    else{

        return;
    }

}


int main(int argc, char** argv){

    osAssert(2==argc,"Upotreba: ./obilazak putanja");

    struct stat finfo;
    osAssert(-1!=lstat(argv[1],&finfo),"Dohvatanje inf o prvom dir nije uspelo");
    
    osAssert(S_ISDIR(finfo.st_mode),"Prosledjena putanja ne ukazuje na direktorijum");
    unsigned size=0U;
    osTraverseDir(argv[1],&size);
    printf("Ukupna vel je %u",size);
    return 0;
}