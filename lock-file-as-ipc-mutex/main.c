
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "mutex.h"

int main(int argc, char *argv[]) {
    char    name [64];
    char    fpath_mutex [256];

    strlcpy(name, argv[1], sizeof(name));
    strlcpy(fpath_mutex, argv[2], sizeof(fpath_mutex));

    fprintf(stderr, "** %s start\n", name);
    fprintf(stderr, "  mutex file path = %s\n", fpath_mutex);

    // prepare

    // work
    for (int ii=0; ii<10; ++ii) {
        // 1. acquire mutex
        fprintf(stderr, "%s: acquire mutex %s\n", name, fpath_mutex);
        if (mutex_acquire(fpath_mutex, 10000, 300) != 0) {
            fprintf(stderr, "%s: fail to acquire mutex %s\n", name, fpath_mutex);
            exit(1);
        }

        // 2. work
        fprintf(stderr, "%s: start to work\n", name);
        sleep(2);
        fprintf(stderr, "%s: finish work\n", name);

        // 3. release mutex
        fprintf(stderr, "%s: release mutex\n", name);
        if (mutex_release(fpath_mutex) != 0) {
            fprintf(stderr, "%s: fail to release mutex\n", name);
            exit(1);
        }

        // 4. do something else, so that others can get the mutex
        sleep(1);
    }

    // cleanup

    fprintf(stderr, "** %s exit\n", name);
    exit(0);
}
