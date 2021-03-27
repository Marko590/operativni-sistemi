
#define _XOPEN_SOURCE 700
#include <sys/types.h>
       #include <sys/stat.h>
       #include <fcntl.h>
       #include <stdio.h>
       #include <stdbool.h>
       #include <inttypes.h>
#include <unistd.h>
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
#define osAssert(cond,msg) osErrorFatal(cond,msg,__FILE__,__LINE__)
void osErrorFatal(bool cond,const char *msg, const char *fname,int line){

    if(!cond){
        perror(msg);
        fprintf(stderr,"%s:%d\n",fname,line);
        exit(EXIT_FAILURE);
    }

}

pid_t osCreateProcess(char ** args){
pid_t childPid=fork();
osAssert(-1!=childPid,"Fork nije uspeo");
if(0==childPid){
    osAssert(-1!=execvp(args[0],args),"Exec komanda nije uspela.");

}
else{
    return childPid;
}


}
int main(int argc, char** argv){

    
    osAssert(argc>1,"Upotreba: ./create_process program argument1 argument2...");
   
   pid_t pid=osCreateProcess(argv+1);
   osAssert(-1!=waitpid(pid,NULL,0|WNOHANG),"Cekanje na proces nije zavrseno");
    return 0;
}