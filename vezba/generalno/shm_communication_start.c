
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
    osAssert(3==argc,"Usage: ./shm_start path_to_shm");

    int numMessages=atoi(argv[2]);
    size_t totalMessageSize=numMessages*sizeof(Message);

    int shmFd=shm_open(argv[1],O_CREAT|O_RDWR,0666);
    osAssert(-1!=shmFd,"Couldn't make the shm file at the designated path\n");

    osAssert(-1!=ftruncate(shmFd,totalMessageSize),"Truncating the file to the desired length was unsucessful");


    Message * messageArray=mmap(NULL,totalMessageSize,PROT_READ|PROT_WRITE,MAP_SHARED,shmFd,0);
    osAssert(MAP_FAILED!=messageArray,"Memory allocation of the message array has failed");
    int bytesRead=0;
    for(int i=0;i<numMessages;i++){
        char *lineBuf;

        int32_t lineSize=getline(&lineBuf,&bytesRead,stdin);
        osAssert(-1!=lineSize,"Error while loading in the next line.");
        
         fprintf(stderr,"Poruka je %s, velicine %d\n",lineBuf,lineSize);
        messageArray[i].numBytes=lineSize;
        strcpy(messageArray[i].messageContent,lineBuf);

        fprintf(stderr,"Poruka je %s, velicine %d\n\n",messageArray[i].messageContent,messageArray[i].numBytes);
        
        
    }

    osAssert(NULL!=messageArray,"Loading the message array has failed");

    osAssert(-1!=munmap(messageArray,totalMessageSize),"Deallocation of the memory array has failed.");
    

    return 0;
}