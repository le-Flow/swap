#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

#include "isPrime.h"
#include "time_measurement.h"

#define RANGE_START 1
#define RANGE_STOP 100000000
#define THREADS 4

unsigned int count = 0;
    pthread_mutex_t mutex;

struct range{
    unsigned long min;
    unsigned long max;
};

void *check_range(void *ptr) {
    struct range *r = (struct range *) ptr;

    for (unsigned long k = r->min; k < r->max; ++k) {
        if (isPrime(k)) {
            pthread_mutex_lock(&mutex);
            ++count;
            pthread_mutex_unlock(&mutex);
        }
    }

    return NULL;
}

int main(void) {
    pthread_mutex_init(&mutex, NULL);

    struct range range[THREADS];
    pthread_t thread_id[THREADS];
    unsigned long part = (RANGE_STOP - RANGE_START) / THREADS;

    Measurement m = startMeasurement();
    for (int k = 0; k < THREADS; ++k) {
        range[k].min = RANGE_START + k * part + k;
        range[k].max = range[k].min + part;
        pthread_create(&thread_id[k], NULL, check_range, &range[k]);
    }

    for (int k = 0; k < THREADS; ++k) {
        pthread_join(thread_id[k], NULL);
    }
    printf("Primes: %u\n", count);
    printf("Time: %fs\n", stopMeasurement(m)/ 1000);

    pthread_mutex_destroy(&mutex);

    return 0;
}
