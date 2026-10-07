#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>

struct asgn1_stats {
    int open_count;
    int write_count;
    int read_count;
    int buffer_len;
    int last_write_size;
};

#define ASGN1_GET_STATS _IOR('a', 2, struct asgn1_stats)

int main(void)
{
    int fd;
    struct asgn1_stats stats;

    fd = open("/dev/asgn1", O_RDWR);

    if (fd < 0) {
        perror("open");
        return 1;
    }

    if (ioctl(fd, ASGN1_GET_STATS, &stats) < 0) {
        perror("ioctl");
        close(fd);
        return 1;
    }

    printf("open_count      = %d\n", stats.open_count);
    printf("write_count     = %d\n", stats.write_count);
    printf("read_count      = %d\n", stats.read_count);
    printf("buffer_len      = %d\n", stats.buffer_len);
    printf("last_write_size = %d\n", stats.last_write_size);

    close(fd);

    return 0;
}

