
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



int main(int argc, char **argv)
{    
    osAssert(2 == argc, "Usage: ./1 path_to_file path_to_dest\n");
    struct stat finfo;

    osAssert(-1!=lstat(argv[1],&finfo),"File information fetching was unsuccessful.");
    char permBuf[10];
    
    if(S_ISREG(finfo.st_mode)){
    permBuf[0]='-';

    }

    else if(S_ISDIR(finfo.st_mode)){
        permBuf[0]='d';
    }
    else if(S_ISSOCK(finfo.st_mode)){
        permBuf[0]='s';
    }
    else if(S_ISLNK(finfo.st_mode)){
        permBuf[0]='l';
    }
    else if(S_ISFIFO(finfo.st_mode)){
        permBuf[0]='p';
    }
    else if(S_ISBLK(finfo.st_mode)){
        permBuf[0]='b';
    }
    else if(S_ISCHR(finfo.st_mode)){
        permBuf[0]='c';
    }
    
    permBuf[1]=S_IRUSR&finfo.st_mode?'r':'-';
    permBuf[2]=S_IWUSR&finfo.st_mode?'w':'-';
    permBuf[3]=S_IXUSR&finfo.st_mode?'x':'-';

    permBuf[4]=S_IRGRP&finfo.st_mode?'r':'-';
    permBuf[5]=S_IWGRP&finfo.st_mode?'w':'-';
    permBuf[6]=S_IXGRP&finfo.st_mode?'x':'-';

    permBuf[7]=S_IROTH&finfo.st_mode?'r':'-';
    permBuf[8]=S_IWOTH&finfo.st_mode?'w':'-';
    permBuf[9]=S_IXOTH&finfo.st_mode?'x':'-';


    printf("%s",permBuf);
    return 0;
}