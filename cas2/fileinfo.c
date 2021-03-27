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

int main(int argc, char** argv){

    osAssert(2==argc,"Upotreba: ./fileinfo putanja do fajla");
    struct stat fileInfo;
    osAssert(-1!=stat(argv[1]))
 
    return 0;
}