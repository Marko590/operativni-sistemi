
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
    osAssert(3 == argc, "Usage: ./1 path_to_file path_to_dest\n");
    int fd;
    if(strcmp("-r",argv[1])==0){
        fd=open(argv[2],O_RDONLY);
        osAssert(-1!=fd,"Opening of the file for reading was unsuccessful.");

        char buf[BUF_SIZE];

        int bytesRead=0;
        while((bytesRead=read(fd,buf,sizeof buf))>0)
        {
        printf("%s",buf);

        }
        
    }
    else if(strcmp("-w",argv[1])==0){
        fd=open(argv[2],O_WRONLY);
        if(-1==fd){
            fd=open(argv[2],O_WRONLY|O_CREAT);
        }
        size_t n;
        char *linebuf;
        printf("%s",linebuf);
        osAssert(-1!=getline(&linebuf,&n,stdin),"Input from stdin was unsuccessful.");
        int bytesRead=0;
        while(bytesRead<n)
        {
        bytesRead=write(fd,linebuf,MAX_LINE);
        osAssert(-1!=bytesRead,"Pisanje nije uspelo");

        }
    }
    else if(strcmp("-a",argv[1])==0){
        fd=open(argv[2],O_APPEND);
        osAssert(-1!=fd,"Opening of the file for reading was unsuccessful.");

        size_t n;
        char *linebuf;
        osAssert(-1!=getline(&linebuf,&n,stdin),"Input from stdin was unsuccessful.");
        printf("%s",linebuf);
        int bytesWritten=0;
        while((bytesWritten=write(fd,linebuf,MAX_LINE))>0){

        }
    }
    return 0;
}