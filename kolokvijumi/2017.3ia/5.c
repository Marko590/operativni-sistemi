
#define _XOPEN_SOURCE 700
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdbool.h>
#include <inttypes.h>
#include <unistd.h>
#include <ctype.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <utime.h>
#include <ftw.h>
#include <sys/mman.h>
#include <sys/stat.h> /* For mode constants */
#include <fcntl.h>
#include <limits.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/types.h>
#include <grp.h>
#include <sys/wait.h>
#include <time.h>
#include <pwd.h>
#define IS_CHILD(pid) (pid == 0)
#define BUF_SIZE (4096)
#define RD_END (0)
#define WR_END (1)
#define MAX_LINE (4096)
#define SECS_PER_DAY (3600 * 24)
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


static int osNumReg;
static int osNumDir;
static int osNumChar;
static int osNumBlk;
static int osNumLnk;
static int osNumSock;
static int osNumFifo;


//int (*fn) (const char *fpath, const struct stat *sb,int typeflag, struct FTW *ftwbuf)

int osProccessFile(const char *fpath,const struct stat *sb,int typeflag,struct FTW *ftwbuf){


    fprintf(stderr,"%s",fpath);
    if(S_ISREG(sb->st_mode)){
        osNumReg++;
    }
    else if(S_ISDIR(sb->st_mode)){
        osNumDir++;
    }
    else if(S_ISSOCK(sb->st_mode)){
        osNumSock++;
    }
    else if(S_ISBLK(sb->st_mode)){
        osNumBlk++;
    }
    else if(S_ISCHR(sb->st_mode)){
         osNumChar++;
    }
    else if(S_ISLNK(sb->st_mode)){
        osNumLnk++;
    }
    else if(S_ISFIFO(sb->st_mode)){
        osNumFifo++;
    }
    return 0;


}
int main(int argc, char **argv)
{    
    osAssert(2 == argc, "Usage: ./1 path_to_file path_to_dest\n");
    
    osNumReg=0;
    osNumDir=0;
    osNumSock=0;
    osNumBlk=0;
    osNumChar=0;
    osNumFifo=0;
    osNumLnk=0;
    osAssert(-1!=nftw(argv[1],osProccessFile,60,FTW_PHYS),"FTW was unsucessful.");

    
    printf("%d %d %d %d %d %d %d %d",osNumReg,osNumDir,osNumChar,osNumBlk,osNumLnk,osNumFifo,osNumSock,osNumReg+osNumDir+osNumChar+osNumBlk+osNumLnk+osNumFifo+osNumSock);
    
    
    return 0;
}