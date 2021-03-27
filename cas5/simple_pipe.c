
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
#include <sys/wait.h>
       #include <pwd.h>
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

    int pipefd[2];
    osAssert(-1!=pipe(pipefd),"Pravljenje PIPE nije uspelo!");

    pid_t childPid=fork();
    osAssert(-1!=childPid,"Pravljenje dete procesa nije uspelo");

    if(0==childPid){
        close(pipefd[WR_END]);
        char lineBuf[MAX_LINE]={0};
        osAssert(-1!=read(pipefd[RD_END],lineBuf,sizeof lineBuf),"Citanje linije nije uspelo");
        char *pChar=lineBuf;
        while(*pChar!='\0'){
            *pChar=toupper(*pChar);
            pChar+=1;
        }
        printf("%s",lineBuf);
        close(pipefd[RD_END]);
        exit(0);

    }
    else{
        close(pipefd[RD_END]);
        char *line=NULL;
        size_t n=0;
        osAssert(-1!=getline(&line,&n,stdin),"Citanje linije sa stdin nije uspelo!");
        osAssert(-1!=write(pipefd[WR_END],line,n),"Pisanje u pipe nije uspelo.");
        close(pipefd[WR_END]);
        free(line);
        osAssert(-1!=wait(NULL),"Cekanje na dete proces nije uspelo.");
    }
  //0. napravimo pipe
  //1. pravimo dete proces
  //2. citamo liniju sa stdin u roditeljskom procesu
  //3. saljemo procitano dete procesu
  //4. ispisemo procitano iz dete procesa sa malom obradom(sva mala slova u velika)
    return 0;
}