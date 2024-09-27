#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

int main(void) {
    fork();
    fork();
    fork();
    fork();

    printf("%d ", getpid());
    return EXIT_SUCCESS;
}
