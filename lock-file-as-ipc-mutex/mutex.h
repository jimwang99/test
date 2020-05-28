#ifndef __MUTEX_H__
#define __MUTEX_H__

// @brief   acquire file mutex
// @return  0=successful, non-zero=linux system error
int mutex_acquire(char fpath[], unsigned int timeout_ms, unsigned int wait_interval_ms);

// @brief   release file mutex
// @return  0=successful, non-zero=linux system error
int mutex_release(char fpath[]);

#endif
