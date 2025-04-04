#include <sys/stat.h>
#include <stdlib.h>
#include <errno.h>

// Linker variable that marks the end of the static data segment
extern char _end;

// Current end of heap
static char* heap_end;

// Function to handle out-of-memory situations
caddr_t _sbrk(int incr) {
    if (heap_end == 0) {
        heap_end = &_end;
    }
    char *prev_heap_end = heap_end;
    heap_end += incr;

    // Ensure we do not collide with the stack
    extern char _estack; // Assuming `_estack` is defined by the linker script
    if (heap_end >= (char *)&_estack) {
        errno = ENOMEM;
        return (caddr_t)-1;
    }
    return (caddr_t)prev_heap_end;
}

// Minimal implementation of _write for semi-hosting
int _write(int file, char *ptr, int len) {
    // Implement your actual I/O handling here, for example, sending to a UART
    return len;
}

// Minimal implementation of _close
int _close(int file) {
    return -1;
}

// Minimal implementation of _fstat
int _fstat(int file, struct stat *st) {
    st->st_mode = S_IFCHR;
    return 0;
}

// Minimal implementation of _isatty
int _isatty(int file) {
    return 1;
}

// Minimal implementation of _lseek
int _lseek(int file, int ptr, int dir) {
    return 0;
}

// Minimal implementation of _read
int _read(int file, char *ptr, int len) {
    return 0;
}

// Minimal implementation of _exit
void _exit(int status) {
    while (1) {
        // Infinite loop, effectively halting the program
    }
}

// Minimal implementation of _kill
int _kill(int pid, int sig) {
    errno = EINVAL;
    return -1;
}

// Minimal implementation of _getpid
int _getpid(void) {
    return 1;
}
