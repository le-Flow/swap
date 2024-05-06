#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

#include "isPrime.h"
#include "time_measurement.h"

#define RANGE_START 1
#define RANGE_STOP 100000000
#define THREADS 4

struct range{
    unsigned long min;
    unsigned long max;
    unsigned int count;
};

void *check_range(void *ptr) {
    struct range *r = (struct range *) ptr;
    unsigned int c = 0;

    for (unsigned long k = r->min; k < r->max; ++k) {
        if (isPrime(k)) {
            ++c;
        }
    }
    r->count = c;

    return NULL;
}

int main(void) {
    struct range range[THREADS];
    pthread_t thread_id[THREADS];
    unsigned long part = (RANGE_STOP - RANGE_START) / THREADS;

    Measurement m = startMeasurement();
    for (int k = 0; k < THREADS; ++k) {
        range[k].count = 0;
        range[k].min = RANGE_START + k * part + k;
        range[k].max = range[k].min + part;
        pthread_create(&thread_id[k], NULL, check_range, &range[k]);
    }

    unsigned int count_total = 0;
    for (int k = 0; k < THREADS; ++k) {
        pthread_join(thread_id[k], NULL);
        count_total += range[k].count;
    }
    printf("Primes: %u\n", count_total);
    printf("Time: %fs\n", stopMeasurement(m)/ 1000);

    return 0;
}
