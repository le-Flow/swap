#include <unistd.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/sem.h>

#define KUNDEN_MAX_DRINNEN 15
#define KUNDEN_MAX 75

struct sembuf semaphore;
int semid;

void *warten_im_haus(void *args) {
    pthread_t pt = pthread_self();

    semaphore.sem_op = -1;
    semaphore.sem_flg = SEM_UNDO;
    semop(semid, &semaphore, 1);

    printf("%lu: Im Haus\n", pt);
    sleep((rand() % 5) + 1);

    semaphore.sem_op = 1;
    semaphore.sem_flg = SEM_UNDO;
    semop(semid, &semaphore, 1);

    printf("%lu: Verlasse\n", pt);
    return NULL;
}

int main(void) {
    srand(time(NULL));
    pthread_t threads[KUNDEN_MAX];

    semid = semget(IPC_PRIVATE, 1, IPC_CREAT | 0777);
    semctl(semid, 0, SETVAL, KUNDEN_MAX_DRINNEN);

    int kunden = 0;
    int k = 0;
    while (1) {
        k = rand() % 21;
        for (int h = 0; h < k; ++h) {
            if (kunden < KUNDEN_MAX) {
                pthread_create(&threads[kunden], NULL, warten_im_haus, NULL);
                kunden++;
            }
            else {
                goto exitl;
            }
        }
        sleep(1);
    }
exitl:
    // for (int k = 0; k < KUNDEN_MAX; ++k) {
    //     pthread_create(&threads[k], NULL, warten_im_haus, NULL);
    // }

    for (int k = 0; k < KUNDEN_MAX; ++k) {
        pthread_join(threads[k], NULL);
    }

    return 0;
}
