#include <sys/file.h>

#include "message.h"

int __message_write_byte(int fd, uint8_t byte) {
    if (write(fd, &byte, 1) != 1) {
        fprintf(stderr, "ERROR: write() size=1 errno=%s\n", strerror(errno));
        return errno;
    }
    return 0;
}

int __message_read_byte(int fd, uint8_t * p_byte) {
    if (read(fd, p_byte, 1) != 1) {
        fprintf(stderr, "ERROR: read() size=1 errno=%s\n", strerror(errno));
        return errno;
    }
    return 0;
}

int __message_write_valid(int fd, uint8_t valid) {
    if (lseek(fd, 0, SEEK_SET) != 0) {
        fprintf(stderr, "ERROR: lseek() errno=%s\n", strerror(errno));
        return errno;
    }

    return __message_write_byte(fd, valid);
}

int __message_read_valid(int fd, uint8_t * p_valid) {
    if (lseek(fd, 0, SEEK_SET) != 0) {
        fprintf(stderr, "ERROR: lseek() errno=%s\n", strerror(errno));
        return errno;
    }

    return __message_read_byte(fd, p_valid);
}

int __message_lock_and_unlock(int fd, int operation,
        unsigned int timeout_ms, unsigned int wait_interval_ms) {
    while (flock(fd, LOCK_EX | LOCK_NB) == -1) {
        if (errno == EWOULDBLOCK) {
            fprintf(stderr, "INFO: file %s is locked\n", fpath);
            if (timeout_ms < wait_interval_ms) {
                fprintf(stderr, "ERROR: timeout\n");
                return ETIMEDOUT;
            }
            usleep(wait_interval_ms * 1000);
            timeout_ms -= wait_interval_ms;
            continue;
        } else {
            fprintf(stderr, "ERROR: flock() errno=%s\n", strerror(errno));
            return errno;
        }
    }

}

int message_tx(const char *fpath, const char *msg, unsigned int size,
        unsigned int timeout_ms, unsigned int wait_interval_ms) {
    assert(size < 256);

    int fd,     // file descriptor
        rtn;    // return value

    //------------------------------------------------------
    // write message

    // open file for write
    fd = open(fpath, O_CREAT | O_WRONLY);
    if (fd == -1) {
        fprintf(stderr, "ERROR: open() errno=%s\n", strerror(errno));
        return errno;
    }

    // lock file
    rtn = __message_lock_and_unlock(fd, 1, timeout_ms, wait_interval_ms);
    if (rtn != 0) { return rtn; };

    // write valid=0
    rtn = __message_write_valid(0);
    if (rtn != 0) { return rtn; }

    // write size
    rtn = __message_write_byte(fd, (uint8_t)size);
    if (rtn != 0) { return rtn; }

    // write message
    if (write(fd, msg, size) != size) {
        fprintf(stderr, "ERROR: write() size=%d errno=%s\n", size, strerror(errno));
        return errno;
    }

    // write valid=1
    rtn = __message_write_valid(1);
    if (rtn != 0) { return rtn; }

    // unlock file
    rtn = __message_lock_and_unlock(fd, 0, timeout_ms, wait_interval_ms);
    if (rtn != 0) { return rtn; }

    // close file
    close(fd);

    fprintf(stderr, "INFO: tx: message sent\n")

    //------------------------------------------------------
    // check message has been received

    // open file for read
    fd = open(fpath, O_RDONLY);
    if (fd == -1) {
        fprintf(stderr, "ERROR: open() errno=%s\n", strerror(errno));
        return errno;
    }

    uint8_t valid, check_timeout_ms = timeout_ms;
    wait_interval_ms *= 2;
    for (;;) {
        // lock file
        rtn = __message_lock_and_unlock(fd, 1, timeout_ms, wait_interval_ms);
        if (rtn != 0) { return rtn; }

        // read valid
        rtn = __message_read_valid(fd, &valid);
        if (rtn != 0) { return rtn; }

        // unlock file
        rtn = __message_lock_and_unlock(fd, 0, timeout_ms, wait_interval_ms);
        if (rtn != 0) { return rtn; }

        // check
        if (valid == 0) {
            fprintf(stderr, "INFO: tx: message received\n")
            break;
        } else {
            fprintf(stderr, "INFO: tx: wait for valid to become 0\n")
            if (check_timeout_ms < wait_interval_ms) {
                fprintf(stderr, "ERROR: timeout\n");
                return ETIMEDOUT;
            }
            usleep(wait_interval_ms * 1000);
            check_timeout_ms -= wait_interval_ms;
            continue;
        }
    }

    return 0;
}

int message_rx(const char *fpath, char *msg, unsigned int *p_size,
        unsigned int timeout_ms, unsigned int wait_interval_ms) {
    int fd,     // file descriptor
        rtn;    // return value
}
