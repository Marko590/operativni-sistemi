
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
#include <ftw.h>

#include <string.h>
#include <utime.h>
#include <limits.h>
#include <sys/types.h>
#include <pwd.h>

#define BUF_SIZE (4096)
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
// int nftw(const char *dirpath,int typeflag, struct FTW *ftwbuf), int nopenfd, int flags);

static const char *os_Extension = NULL;
int osProcessFile(const char *fpath, const struct stat *sb, int typeflag, struct FTW *ftwbuf)
{
    if (S_ISREG(sb->st_mode))
    {
        const char *fname = fpath + ftwbuf->base;
        const char *lastDot = strrchr(fname, '.');
        if (NULL != lastDot && !strcmp(lastDot, os_Extension))
        {
            printf("Putanja %s", fpath);
        }
    }
    return 0;
}
int main(int argc, char **argv)
{

    osAssert(3 == argc, "Upotreba: ./chmod putanja prava");

    mode_t accessMode = (mode_t)strtol(argv[2], NULL, 8);
    os_Extension = argv[2];
    osAssert(-1 != chmod(argv[1], accessMode), "Menjanje permisija nije uspelo");
    osAssert(-1 != nftw(argv[1], osProcessFile, 50, 0), "obilazak nije uspeo");

    return 0;
}