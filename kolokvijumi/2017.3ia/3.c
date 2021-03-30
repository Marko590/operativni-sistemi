
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



int main(int argc, char **argv)
{    
    osAssert(4 == argc, "Usage: ./1 path_to_file path_to_dest\n");
    


    
    mode_t mode=strtol(argv[3],NULL,8);
    
    if(strcmp("-f",argv[1])==0){
        int regFd=open(argv[2],O_CREAT);
        osAssert(-1!=regFd,"Creating the file was unsuccessful.");
    }

    else if(strcmp("-d",argv[1])==0){
        osAssert(-1!=mkdir(argv[2],mode),"Creating the directory was unsuccessful");
    }
    return 0;
}