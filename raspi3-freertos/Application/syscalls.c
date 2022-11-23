#include <errno.h>
#include "syscalls.h"
#include "hwaccess.h"


double __trunctfdf2(long double A)
{
    (void)A;

    return -1;
}

double __extenddftf2(long double A)
{
    (void)A;

    return -1;
}

caddr_t _sbrk(int32_t incr)
{
    extern uintptr_t __heap_start;
    extern uintptr_t __heap_end;
    static uintptr_t heap = 0;
    uintptr_t        prev = 0;

    if (0 == heap)
    {
        heap = (uintptr_t)&__heap_start;
    }

    if (((heap + incr) < (uintptr_t)&__heap_start)
    || ((heap + incr) > (uintptr_t)&__heap_end)
    || (0 == heap))
    {
        errno = ENOMEM;
        return (caddr_t)-1;
    }

    prev  = heap;
    heap += incr;
    return (caddr_t)((void*)prev);
}

void _exit(int code)
{
    (void)code;

    while (1);
}

int _close(void *reent, int fd)
{
    (void)reent;
    (void)fd;

    return 0;
}

int _fstat(void *reent, int fd, struct stat *pstat)
{
    (void)reent;

    if ((STDIN_FILENO == fd)
    || (STDOUT_FILENO == fd)
    || (STDERR_FILENO == fd))
    {
        pstat->st_mode = S_IFCHR;
        return 0;
    }

    errno = EBADF;
    return -1;
}

off_t _lseek(void *reent, int fd, off_t pos, int whence)
{
    (void)reent;
    (void)pos;
    (void)whence;

    if ((STDIN_FILENO == fd)
    || (STDOUT_FILENO == fd)
    || (STDERR_FILENO == fd))
    {
        return 0;
    }

    errno = EBADF;
    return -1;
}

int _read(int file, char* ptr, int len)
{
    if (STDIN_FILENO == file)
    {
        int32_t n = 0;

        while (0 < len)
        {
            uint8_t ch = hw_uart_getc();

            *ptr = ch;
            len--;
            ptr++;
            n++;

            if ('\n' == ch)
            {
                hw_uart_puts("\r\n");
                break;
            }

            hw_uart_putc(ch);
        }

        return n;
    }

    errno = EBADF;
    return -1;
}

int _write(int file, char* ptr, int len)
{
    if ((STDIN_FILENO == file)
    || (STDOUT_FILENO == file)
    || (STDERR_FILENO == file))
    {
        hw_uart_write((uint8_t*)ptr, len);
        return len;
    }

    errno = EBADF;
    return -1;
}

int _isatty(int file)
{
    if ((STDIN_FILENO == file)
    || (STDOUT_FILENO == file)
    || (STDERR_FILENO == file))
    {
        return 1;
    }

    return 0;
}

int _getpid(void)
{
    return 1;
}

void _kill(int pid, int sig)
{
    (void)pid;
    (void)sig;

    return;
}
