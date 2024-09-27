#include <sys/ipc.h>
#include <sys/shm.h>

int main(void) {
    int shmid = shmget(1, 20, 0666);
    if (shmid == -1) {
        return 1;
    }
    shmctl(shmid, IPC_RMID, 0);


    return 0;
}
