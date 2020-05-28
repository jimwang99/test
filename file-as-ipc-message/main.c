
#include <sys/file.h>
#include <fcntl.h>
#include <errno.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

typedef enum {
    PRODUCER,
    CONSUMER
} role_t;


int main(int argc, char *argv[]) {
    char        name [64];
    char        fpath_msg [256];

    strlcpy(name, argv[1], sizeof(name));
    strlcpy(fpath_msg, argv[2], sizeof(fpath_msg));

    role_t  role;
    if (strcmp(name, "producer") == 0) {
        role = PRODUCER;
        fprintf(stderr, "** producer start\n");
    } else if (strcmp(name, "consumer") == 0) {
        role = CONSUMER;
        fprintf(stderr, "** consumer start\n");
    } else {
        exit(EINVAL);
    }
    fprintf(stderr, "  message file path = %s\n", fpath_msg);

    // prepare
    srand(time(0));
    unsigned int timeout_ms = 10000;
    unsigned int wait_interval_ms = 100;
    char msg[8] = "NULL";
    unsigned int msg_size;


    // work
    for (int ii=0; ii<10; ++ii) {
        fprintf(stderr, "%s: start to work\n", name);

        // producer: write random numbers as message
        if (role == PRODUCER) {
            sprintf(msg, "%d", rand() % 100);
            msg_size = sizeof(msg);
            message_tx(fpath_msg, msg, msg_size, timeout_ms, wait_interval_ms);
            fprintf(stderr, "%s: sent message (%s)\n", name, msg);
        }
        // consumer: read content and print them out
        if (role == CONSUMER) {
            message_rx(fpath_msg, msg, &msg_size, timeout_ms, wait_interval_ms);
            fprintf(stderr, "%s: recieved message (%s)\n", name, msg);
        }

        fprintf(stderr, "%s: finish work\n", name);
    }

    fprintf(stderr, "** %s done\n", name);
    exit(0);
}
