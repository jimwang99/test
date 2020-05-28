#include <assert.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "mutex.h"

int mutex_acquire(char fpath[], unsigned int timeout_ms, unsigned int wait_interval_ms) {
    assert(timeout_ms >= wait_interval_ms);

    int fd;
    for (;;) {
        fd = open(fpath, O_CREAT | O_EXCL | O_RDWR, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
        if (fd == -1) {
            // if ((errno == EEXIST) || (errno == EACCES)) {
            if (errno == EEXIST) {
                fprintf(stderr, "INFO: mutex file exists\n");
                if (timeout_ms < wait_interval_ms) {
                    fprintf(stderr, "ERROR: timeout\n");
                    return ETIMEDOUT;
                }
                usleep(wait_interval_ms * 1000);
                timeout_ms -= wait_interval_ms;
                continue;
            } else {
                fprintf(stderr, "ERROR: open mutex file=%s failed with errno=%s\n", fpath, strerror(errno));
                return errno;
            }
        } else {
            fprintf(stderr, "INFO: mutex file is created\n");
            close(fd);
            break;
        }
    }
    return 0;
}

int mutex_release(char fpath[]) {
    if (unlink(fpath) == -1) {
        fprintf(stderr, "ERROR: unlink mutex file=%s failed with errno=%s\n", fpath, strerror(errno));
        return errno;
    }
    fprintf(stderr, "INFO: mutex file is removed\n");
    return 0;
}
