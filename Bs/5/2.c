#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>

int main(void) {
    int shmid = shmget(1, 20, 0666);
    if (shmid == -1) {
        return 1;
    }

    char *mem = shmat(shmid, 0, 0);

    for (int k = 0; k < 20; ++k) {
        putchar(mem[k]);
    }

    return 0;
}
