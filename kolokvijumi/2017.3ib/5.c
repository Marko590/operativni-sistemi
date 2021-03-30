#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>
#include <errno.h>
#include <dirent.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#define BYTES_PER_KB (1024)
#define KB_PER_MB (BYTES_PER_KB * 1024)
#define MB_PER_GB (KB_PER_MB * 1024)
#define BUF_SIZE (4096)
#define osAssert(cond, msg) osErrorFatal(cond, msg, __FILE__, __LINE__)
void osErrorFatal(bool cond, const char *msg, const char *fname, int line)
{

    if (!cond)
    {
        perror(msg);
        fprintf(stderr, "%s:%d\n", fname, line);
        exit(EXIT_FAILURE);
    }
}
static int numFiles;
void osTraverseDir(const char *fpath,const char *ext){


    osAssert(NULL != dir, "Opening of the directory was unsuccessful.");
    struct stat finfo;
    osAssert(-1!=lstat(fpath,&finfo),"dohvatanje inf o tekucem fajlu nije uspelo");

    
    
    if(S_ISDIR(finfo.st_mode)){
        DIR *dir = opendir(fpath);
        osAssert(NULL!=dir,"Directory opening was unsucessful");
        struct dirent * dirEnt;
    while((dirEnt=readdir(dir))!=NULL){
        if(!strcmp(".",dirEnt->d_name)||!strcmp("..",dirEnt->d_name))
                continue;

        if(strcmp(strrchr(dirEnt->d_name,'.'),ext)==0){
            numFiles++;
        }
        char *newPath=calloc(strlen(fpath)+1+strlen(dirEnt->d_name)+1,1);
            osAssert(NULL!=newPath,"aloc nije uspelo");
            sprintf(newPath,"%s/%s",fpath,dirEnt->d_name);
            osTraverseDir(newPath,ext);
    }
    closedir(dir);
    }
    else{
        return;
    }
}

int main(int argc, char **argv)
{

    osAssert(3 == argc, "Upotreba: ./cpfile odakle gde");
    numFiles=0;
    osTraverseDir(argv[1],argv[2]);
    printf("%d",numFiles);
    return 0;
}