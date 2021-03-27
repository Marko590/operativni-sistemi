
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


int main(int argc, char** argv){

   pid_t childPID=fork();
   osAssert(-1!=childPID,"Fork nije uspeo");
   printf("PID je: %jd\n",(intmax_t)childPID);
   if(IS_CHILD(childPID))//dete proces
   {
       printf("Hello iz potomka\n");
       char *pnull=NULL;
       pnull[5]='a';
        exit(17);
   }
   else// roditeljski proces
   {
       printf("Zdravo iz roditelja\n");

   }
    int status=0;
    osAssert(-1!=wait(&status),"Cekanje na dete nije uspelo");

    if(WIFEXITED(status)){
        printf("Exit code deteta je: %d,",WEXITSTATUS(status));
    }
    else if(WIFSIGNALED(status)){
        printf("Signal koji je ubio program: %d (%s)", WTERMSIG(status),strsignal(WTERMSIG(status)));
    }
    return 0;
}