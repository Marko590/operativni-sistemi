
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
#include <ftw.h>
#include <sys/mman.h>
#include <sys/stat.h> /* For mode constants */
#include <fcntl.h>
#include <limits.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>
#include <pwd.h>
#define IS_CHILD(pid) (pid == 0)
#define BUF_SIZE (4096)
#define RD_END (0)
#define WR_END (1)
#define MAX_LINE (4096)
#define SECS_PER_DAY (3600 * 24)
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

bool osIsPublicFile(const char *fpath)
{
    struct stat finfo;
    osAssert(-1 != stat(fpath, &finfo), "File info fetching was unsucessful.");

    if ((S_IROTH & finfo.st_mode) && (S_IWOTH & finfo.st_mode))
    {
        fprintf(stdout, "true");
    }
    else
    {
        fprintf(stdout, "false");
    }
}

void osMakePublicDir(const char *dname)
{

    osAssert(-1 != mkdir(dname, 0777), "Making of directory was unsucessful.");
}

static time_t osCurrentTime;

unsigned osNumOfDaysFileModified(const char *fpath)
{

    struct stat finfo;
    osAssert(-1 != stat(fpath, &finfo), "File info fetching was unsucessful");
    unsigned dayDifference = (unsigned)((osCurrentTime - finfo.st_mtim.tv_sec) / (float)SECS_PER_DAY);
    return dayDifference;
}

void osMoveFile(const char *srcPath, const char *destPath)
{
    osAssert(-1 != rename(srcPath, destPath), "Moving the file was unsucessful");
}

static const char *pathToBackup;

int osProcessFile(const char *fpath, const struct stat *sb, int typeflag, struct FTW *ftwbuf)
{
    char backPath[100] = "";
    const char *fname = fpath + ftwbuf->base;

    int level = ftwbuf->level;
    strcpy(backPath, "../");


        

    if (S_ISREG(sb->st_mode) && osIsPublicFile(fpath))
    {
        fprintf(stderr, "Currently processing file %s at path %s\n", fname, fpath);
        unsigned numDays = osNumOfDaysFileModified(fpath);

        char help[100];
        if (numDays < 30)
        {
            while (level > 0)
                strcpy(help, strcat("../", backPath));
            level--;
        }
        strcpy(backPath, help);
        strcat(backPath, pathToBackup);
        printf("PUTANJA DO BEKAPA OD %s JE %s", fpath, backPath);
    }

    else
    {
        printf("Brisem %s",fname);
        osAssert(-1 != unlink(fname), "File deletion was unsucessful\n");
    }
    return 0;
        
}

//int (*fn) (const char *fpath, const struct stat *sb,
//      int typeflag, struct FTW *ftwbuf)
//int rename(const char *oldpath, const char *newpath);
int main(int argc, char **argv)
{

    osCurrentTime = time(NULL);
    osAssert(3 == argc, "Usage: ./1 path_to_file path_to_dest\n");
    char *pathToDirectory = argv[1];
    pathToBackup = argv[2];
    char path[1024];
    strcpy(path, "../");
    strcat(path, pathToBackup);
    osMakePublicDir(path);

    osAssert(-1 != nftw(pathToDirectory, osProcessFile, 50, 0), "File tree walk was unsucessful.\n");
    return 0;
}