#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include "asgn1_ioctl.h"

static void usage(const char *p)
{
    fprintf(stderr,
        "Usage: %s <dev> stats | reset | version | mode <0|1> | invalid\n", p);
    exit(1);
}

int main(int argc, char **argv)
{
    int fd, ret = 0;

    if (argc < 3)
        usage(argv[0]);

    fd = open(argv[1], O_RDWR);
    if (fd < 0) {
        perror("open");
        return 1;
    }

    if (strcmp(argv[2], "reset") == 0) {
        ret = ioctl(fd, ASGN1_RESET_BUFFER);
        if (ret == 0)
            printf("OK\n");

    } else if (strcmp(argv[2], "stats") == 0) {
        struct asgn1_stats st;
        memset(&st, 0, sizeof(st));
        ret = ioctl(fd, ASGN1_GET_STATS, &st);
        if (ret == 0) {
            printf("open_count=%d\n",       st.open_count);
            printf("write_count=%d\n",      st.write_count);
            printf("read_count=%d\n",       st.read_count);
            printf("buffer_len=%d\n",       st.buffer_len);
            printf("last_write_size=%d\n",  st.last_write_size);
            printf("mode=%d\n",             st.mode);
        }

    } else if (strcmp(argv[2], "mode") == 0) {
        int m;
        if (argc < 4)
            usage(argv[0]);
        m = atoi(argv[3]);
        ret = ioctl(fd, ASGN1_SET_MODE, &m);
        if (ret == 0)
            printf("OK\n");

    } else if (strcmp(argv[2], "version") == 0) {
        char ver[ASGN1_VERSION_LEN];
        memset(ver, 0, sizeof(ver));
        ret = ioctl(fd, ASGN1_GET_VERSION, ver);
        if (ret == 0) {
            ver[ASGN1_VERSION_LEN - 1] = '\0';
            printf("%s\n", ver);
        }

    } else if (strcmp(argv[2], "invalid") == 0) {
        /* Command không tồn tại, dùng để kiểm tra -ENOTTY */
        ret = ioctl(fd, _IO(ASGN1_IOC_MAGIC, 0x7f));

    } else {
        usage(argv[0]);
    }

    if (ret < 0)
        printf("ERR errno=%d (%s)\n", errno, strerror(errno));

    close(fd);
    return ret < 0 ? 1 : 0;
}