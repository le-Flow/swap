#include <unistd.h>
#include <fcntl.h>

#define BUFF_LEN 1024

int main(int argc, char **argv) {
    char buff[BUFF_LEN];

    if (argc < 3) {
        return 1;
    }

    int src = open(argv[1], O_RDONLY);
    int dst = open(argv[2], O_WRONLY | O_CREAT, 0666);

    if (src == -1 || dst == -1) {
        return 1;
    }

    int c;
    do {
        c = read(src, buff, BUFF_LEN);
        write(dst, buff, c);

    } while (c);

    unlink(argv[1]);

    return 0;
}
