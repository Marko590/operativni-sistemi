
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
#include <sys/mman.h>
#include <sys/stat.h> /* For mode constants */
#include <fcntl.h>
#include <limits.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>
#include <pwd.h>
#define IS_CHILD(pid) (pid == 0)
#define BUF_SIZE (4096)
#define RD_END (0)
#define WR_END (1)
#define MAX_LINE (4096)
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


typedef struct Message{
    int32_t numBytes;
    char *messageContent;
} Message;

int main(int argc, char **argv)
{
    osAssert(2==argc,"Usage: ./shm_start path_to_shm");

    
   

    int shmFd=shm_open(argv[1],O_RDONLY,0666);
    osAssert(-1!=shmFd,"Couldn't make the shm file at the designated path\n");
    
    struct stat shmInfo;
    osAssert(-1!=fstat(shmFd,&shmInfo),"Fetching of the file info was unsucessful.");


     size_t totalMessageSize=shmInfo.st_size;
     int numMessages=totalMessageSize/sizeof(Message);
    Message * messageArray=mmap(NULL,totalMessageSize,PROT_READ,MAP_SHARED,shmFd,0);
    osAssert(MAP_FAILED!=messageArray,"Memory allocation of the message array has failed");
    
    for(int i=1;i<numMessages;++i){
        
        Message currentMessage=messageArray[i];
        int32_t numBytes=currentMessage.numBytes;
        fprintf(stderr,"%d",numBytes);
        
        char* messageContent=currentMessage.messageContent;
        
        fprintf(stderr,"Message %s , with a length of %d bytes.",messageContent,numBytes);
        
    }

    
    osAssert(-1!=munmap(messageArray,totalMessageSize),"Deallocation of the memory array has failed.");
    osAssert(-1!=shm_unlink(argv[1]),"Unlinking of the shared memory file is unsucessful.");

    return 0;
}