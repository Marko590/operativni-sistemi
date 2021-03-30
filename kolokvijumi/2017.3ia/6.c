
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




int main(int argc, char **argv)
{    
    osAssert(3 == argc, "Usage: ./1 path_to_file path_to_dest\n");
    

    
    osAssert(-1!=rename(argv[1],argv[2]),"Moving of the file was unsuccessful.");

    
   
    
    
    return 0;
}