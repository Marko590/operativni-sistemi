
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
    osAssert(2==argc,"./shared_memory_reader /mem_name ");
    srand(time(NULL));


    int shmFd=shm_open(argv[1],O_RDONLY,0);
    osAssert(-1!=shmFd,"Pravljenje fd nije uspelo");
   

    struct stat shmInfo;
    osAssert(-1!=fstat(shmFd,&shmInfo),"Dohvatanje inf o deljenoj mem nije uspelo");


    //void *mmap(void *addr, size_t length, int prot, int flags,int fd, off_t offset);
    int n=shmInfo.st_size/sizeof(float);
    float*sharedArray=mmap(NULL,shmInfo.st_size,PROT_READ,MAP_SHARED,shmFd,0);
    osAssert(MAP_FAILED!=sharedArray,"Mapiranje mem u adresni prostor nie uspelo");
    for(int i=0;i<n;++i){
       
        printf("Citamo: %g\n",sharedArray[i]);
    }

    osAssert(-1!=munmap(sharedArray,shmInfo.st_size),"oslobadjanje nie uspelo");
    osAssert(-1!=shm_unlink(argv[1]),"Brisanje nie us-pelo");
    return 0;
}