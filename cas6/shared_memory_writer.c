
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
#include <limits.h>
#include <sys/types.h>
#include <signal.h>
#include <sys/wait.h>
 #include <time.h>
       #include <pwd.h>
       #include <sys/mman.h>
       #include <sys/stat.h>        /* For mode constants */
       #include <fcntl.h>  
#define IS_CHILD(pid) (pid==0)
#define BUF_SIZE (4096)
#define RD_END (0)
#define WR_END (1)
#define MAX_LINE (4096)
#define osAssert(cond,msg) osErrorFatal(cond,msg,__FILE__,__LINE__)
void osErrorFatal(bool cond,const char *msg, const char *fname,int line){

    if(!cond){
        perror(msg);
        fprintf(stderr,"%s:%d\n",fname,line);
        exit(EXIT_FAILURE);
    }

}





int main(int argc, char** argv){
    osAssert(3==argc,"./shared_memory_writer /mem_name broj_elemenata");
    srand(time(NULL));


    int shmFd=shm_open(argv[1],O_RDWR|O_CREAT,0666);
    osAssert(-1!=shmFd,"Pravljenje fd nije uspelo");
    int n=atoi(argv[2]);

    int memTotal=n*sizeof(float);

    osAssert(-1!=ftruncate(shmFd,memTotal),"Postavlajnje velicine deljene mem nije uspelo");
    //void *mmap(void *addr, size_t length, int prot, int flags,int fd, off_t offset);

    float*sharedArray=mmap(NULL,memTotal,PROT_READ|PROT_WRITE,MAP_SHARED,shmFd,0);
    osAssert(MAP_FAILED!=sharedArray,"Mapiranje mem u adresni prostor nie uspelo");
    for(int i=0;i<n;++i){
        sharedArray[i]=rand()/(float)RAND_MAX;
        printf("Pisemo:%g\n",sharedArray[i]);
    }

    osAssert(-1!=munmap(sharedArray,memTotal),"oslobadjanje nie uspelo");
    return 0;
}