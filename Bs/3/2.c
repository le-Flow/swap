#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <pthread.h>

#define ROWS 3
#define COLS 3

int m1[ROWS][COLS];
int m2[ROWS][COLS];
int m3[ROWS][COLS];

void matrix_init(int m[ROWS][COLS]) {
    for (int y = 0; y < ROWS; ++y) {
        for (int x = 0; x < COLS; ++x) {
            m[y][x] = rand() % 6;
        }
    }
}

void matrix_print(int m[ROWS][COLS]) {
    for (int y = 0; y < ROWS; ++y) {
        for (int x = 0; x < COLS; ++x) {
            printf("%d ", m[y][x]);
        }
        puts("");
    }
    puts("");
}

void *multi_row(void *r) {
    int sum;
    int i;
    int row = *((int *) r);

    for (int k = 0; k < COLS; ++k) {
        sum = 0;
        for (i = 0; i < COLS; ++i) {
            sum += m1[row][i] * m2[i][k];
        }
        m3[row][k] = sum;
    }

    printf("%lu done\n", pthread_self());
    return NULL;
}

int main(void) {
    srand(time(NULL));

    matrix_init(m1);
    matrix_init(m2);

    matrix_print(m1);
    matrix_print(m2);

    pthread_t threads[ROWS] = {0};
    int rows[ROWS];

    for (int k = 0; k < ROWS; ++k) {
        rows[k] = k;
        pthread_create(&threads[k], NULL, multi_row, &rows[k]);
        printf("New thread: %lu\n", threads[k]);
    }

    for (int k = 0; k < ROWS; ++k) {
        pthread_join(threads[k], NULL);
    }

    matrix_print(m3);

    return 0;
}
