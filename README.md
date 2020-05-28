Testing different tools and ideas

## lock-file-as-ipc-mutex
use `open` with `O_CREAT | O_EXCL` flag to create file act as a lock of mutex

## file-as-ipc-message
use flock to lock a file for message passing between 2 programs:
- 1st byte: boolean, valid
- 2nd byte: unsigned int, size of message
- 3rd byte and onward: message (file path to content file)
use request/acknowledge as handshaking protocol
- tx
    - prepare message
    - set valid = 1
    - looping to check valid == 0
    - move on
- rx
    - looping to check valid == 1
    - process message
    - set valid = 0
    - move on
