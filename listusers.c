
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
#include <limits.h>
#include <sys/types.h>
       #include <pwd.h>

#define BUF_SIZE (4096)
#define osAssert(cond,msg) osErrorFatal(cond,msg,__FILE__,__LINE__)
void osErrorFatal(bool cond,const char *msg, const char *fname,int line){

    if(!cond){
        perror(msg);
        fprintf(stderr,"%s:%d\n",fname,line);
        exit(EXIT_FAILURE);
    }

}
void osPrintUserInfo(const struct passwd *pUserInfo){
     printf("%s \n %jd \n %jd \n %s \n %s \n %s\n",pUserInfo->pw_name,(intmax_t)pUserInfo->pw_uid,(intmax_t)pUserInfo->pw_gid,pUserInfo->pw_dir,
   pUserInfo->pw_gecos,pUserInfo->pw_shell);
   printf("_______________________________________________");
}
 

int main(int argc, char** argv){

    osAssert(1==argc,"Upotreba: ./fsize putanja");
    setpwent();

    struct passwd *pUserInfo=NULL;
    while((pUserInfo=getpwent())!=NULL){
        osPrintUserInfo(pUserInfo);
    }
    osAssert(0==errno,"Dohvatanje sledeceg nije uspelo");
    getpwent();
    return 0;
}