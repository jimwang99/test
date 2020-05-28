#ifndef __MESSAGE_H__
#define __MESSAGE_H__

// @brief   send message (blocking)
// @return  0=successful, non-zero=linux system error
int message_tx(char fpath[], const char msg[], unsigned int size, unsigned int timeout_ms, unsigned int wait_interval_ms);

// @brief   receive message (blocking)
// @return  0=successful, non-zero=linux system error
int message_rx(char fpath[], char msg[], unsigned int * p_size, unsigned int timeout_ms, unsigned int wait_interval_ms);

#endif
