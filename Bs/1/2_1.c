#include <string.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char **argv) {
    if (argc < 3) {
        return 1;
    }

    int f = open(argv[1], O_WRONLY | O_CREAT | O_APPEND, 0640);

    if (f == -1) {
        return 1;
    }

    write(f, argv[2], strlen(argv[2]));
    write(f, "\n", 1);

    close(f);

    return 0;
}
