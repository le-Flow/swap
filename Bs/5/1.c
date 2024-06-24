#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>

int main(void) {
    int shmid = shmget(1, 20, IPC_CREAT | 0666);
    char *mem = shmat(shmid, 0, 0);

    for (int k = 0; k < 20; ++k) {
        mem[k] = 'X';
    }
    getchar();
    shmdt(mem);

    return 0;
}
