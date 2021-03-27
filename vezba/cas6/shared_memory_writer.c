
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
#include <sys/mman.h>
#include <sys/stat.h> /* For mode constants */
#include <fcntl.h>
#include <limits.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>
#include <pwd.h>
#define IS_CHILD(pid) (pid == 0)
#define BUF_SIZE (4096)
#define RD_END (0)
#define WR_END (1)
#define MAX_LINE (4096)
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

int main(int argc, char **argv)
{
    srand(time(NULL));
    osAssert(3 == argc, "Upotreba: ./fifo_writer putanja_do_fifa");

    int shmFd = shm_open(argv[1], O_RDWR | O_CREAT, 0666);

    osAssert(-1 != shmFd, "Pravljenje deljene memorije nije uspelo");

    int n = atoi(argv[2]);

    int memTotal = n * sizeof(float);
    osAssert(-1!=ftruncate(shmFd,memTotal),"Postavljanje velicine deljene memorije nije uspelo");
    float *sharedArray = mmap(NULL, memTotal, PROT_READ | PROT_WRITE, MAP_SHARED, shmFd, 0);
    osAssert(MAP_FAILED != sharedArray, "Mapiranje mem u adresni prostor nie uspelo");

    for (int i = 0; i < atoi(argv[2]); ++i)
    {
        float num = rand() / (float)RAND_MAX;
        sharedArray[i] = num;
        fprintf(stderr, "Upisujemo %g", num);
    }

    osAssert(-1 != munmap(sharedArray, atoi(argv[2]) * sizeof(float)), "Dealokacija nije uspela");
    

    return 0;
}