#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>

#define ASGN1_RESET_BUFFER _IO('a', 1)

int main(void)
{
    int fd;

    fd = open("/dev/asgn1", O_RDWR);

    if (fd < 0) {
        perror("open");
        return 1;
    }

    if (ioctl(fd, ASGN1_RESET_BUFFER) < 0) {
        perror("ioctl");
        close(fd);
        return 1;
    }

    printf("Buffer reset successfully\n");

    close(fd);

    return 0;
}
