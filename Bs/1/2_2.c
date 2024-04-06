#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>

#define BUFF_LEN 1024

int main(int argc, char **argv) {
    if (argc < 2) {
        return 1;
    }

    char buff[BUFF_LEN];

    int f = open(argv[1], O_RDONLY);
    if (f == -1) {
        return 1;
    }

    int c;
    do {
        c = read(f, buff, BUFF_LEN);
        write(STDOUT_FILENO, buff, c);
    } while (c);

    close(f);

    return 0;
}
