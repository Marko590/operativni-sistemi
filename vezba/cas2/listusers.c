#include <stdio.h>
#include <stdbool.h>
#include <errno.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <pwd.h> 
#include <inttypes.h>

#define BUF_SIZE 4096

#define osAssert(cond, msg) osErrorFatal(cond, msg, __FILE__, __LINE__)

void osErrorFatal(bool cond, char *msg, char *file, int line)
{
    if (!cond)
    {
        perror(msg);
         fprintf(stderr,"%s:%d\n",file,line);
        exit(EXIT_FAILURE);
    }
}
void osPrintUserInfo(struct passwd* pUserInfo){
    printf("%s %jd %jd %s %s %s\n",pUserInfo->pw_name,(intmax_t)pUserInfo->pw_uid,(intmax_t)pUserInfo->pw_gid,pUserInfo->pw_gecos,pUserInfo->pw_dir,pUserInfo->pw_shell);
    return;
}

int main(int argc, char **argv)
{
    osAssert(1==argc,"Upotreba: ./catfile ime");

    setpwent();
    struct passwd* pUserInfo=NULL;
    
    while(NULL!=(pUserInfo=getpwent())){
        osPrintUserInfo(pUserInfo);
    }
    

    
    endpwent();
}