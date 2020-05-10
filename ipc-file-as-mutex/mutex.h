#ifndef __MUTEX_H__
#define __MUTEX_H__

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>

// @brief   acquire file mutex
// @return  0=successful, 1=failed due to timeout, -1=failed due to errno
int mutex_acquire(char fpath[], unsigned int timeout_ms, unsigned int wait_interval_ms);

// @brief   release file mutex
// @return  0=successful, -1=failed due to errno
int mutex_release(char fpath[]);

#endif
