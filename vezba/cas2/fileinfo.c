#include <stdio.h>
#include <stdbool.h>
#include <errno.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <pwd.h>
#include <inttypes.h>
#include <grp.h>
#define BUF_SIZE 4096

#define osAssert(cond, msg) osErrorFatal(cond, msg, __FILE__, __LINE__)

void osErrorFatal(bool cond, char *msg, char *file, int line)
{
    if (!cond)
    {
        perror(msg);
        fprintf(stderr, "%s:%d\n", file, line);
        exit(EXIT_FAILURE);
    }
}

int main(int argc, char **argv)
{
    osAssert(2 == argc, "Upotreba: ./fileinfo ime");
    struct stat finfo;
    osAssert(-1 != stat(argv[1], &finfo), "Citanje fajla nije uspelo");
    char buf[11] = {0};

    if (S_ISREG(finfo.st_mode))
    {
        buf[0] = '-';
    }
    else if (S_ISDIR(finfo.st_mode))
    {
        buf[0] = 'd';
    }
    else if (S_ISCHR(finfo.st_mode))
    {
        buf[0] = 'c';
    }
    else if (S_ISLNK(finfo.st_mode))
    {
        buf[0] = 'l';
    }
    else if (S_ISFIFO(finfo.st_mode))
    {
        buf[0] = 'p';
    }
    else if (S_ISSOCK(finfo.st_mode))
    {
        buf[0] = 's';
    }
    else if (S_ISBLK(finfo.st_mode))
    {
        buf[0] = 'b';
    }

    buf[1] = finfo.st_mode & S_IRUSR ? 'r' : '-';
    buf[2] = finfo.st_mode & S_IWUSR ? 'w' : '-';
    buf[3] = finfo.st_mode & S_IXUSR ? 'x' : '-';

    buf[4] = finfo.st_mode & S_IRGRP ? 'r' : '-';
    buf[5] = finfo.st_mode & S_IWGRP ? 'w' : '-';
    buf[6] = finfo.st_mode & S_IXGRP ? 'x' : '-';

    buf[7] = finfo.st_mode & S_IROTH ? 'r' : '-';
    buf[8] = finfo.st_mode & S_IWOTH ? 'w' : '-';
    buf[9] = finfo.st_mode & S_IXOTH ? 'x' : '-';

    struct passwd *pUserInfo = getpwuid(finfo.st_uid);
    struct group *pGroupInfo = getgrgid(finfo.st_gid);
    osAssert(pUserInfo != NULL, "Dohvatanje podatka o vlasniku nije uspelo");
    osAssert(pGroupInfo != NULL, "Dohvatanje podataka o grupi nije uspelo");

    char *mtimeStr = ctime(&finfo.st_mtime);
    printf("%s %jd %s %s %jd %s", buf, (intmax_t)finfo.st_nlink, pUserInfo->pw_name, pGroupInfo->gr_name, (intmax_t)finfo.st_size, mtimeStr);
}