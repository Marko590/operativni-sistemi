
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


pid_t osCreateProcess(char **args){
    pid_t childPid=fork();
    osAssert(-1!=childPid,"Pravljenje procesa nije uspelo");
    if(childPid==0){

        osAssert(-1!=execvp(args[0],args),"Izvrsavanje programa nije uspelo.");

    }
    else{

        return childPid;
    }



}

int main(int argc, char** argv){

    osAssert(argc>1,"Invalid arg count");
    
    pid_t childPid=osCreateProcess(argv+1);
    osAssert(waitpid(childPid,NULL,0),"Cekanje na dete proces nije uspelo");
  //0. napravimo pipe
  //1. pravimo dete proces
  //2. citamo liniju sa stdin u roditeljskom procesu
  //3. saljemo procitano dete procesu
  //4. ispisemo procitano iz dete procesa sa malom obradom(sva mala slova u velika)
  printf("Ovo ce se ispisati");
    return 0;
}