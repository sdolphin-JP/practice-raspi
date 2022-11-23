#ifndef __SYSCALLS_H__
#define __SYSCALLS_H__


#include <stdint.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/unistd.h>


double  __trunctfdf2(long double A);
double  __extenddftf2(long double A);
caddr_t _sbrk(int incr);
void    _exit(int code);
int     _close(void *reent, int fd);
int     _fstat(void *reent, int fd, struct stat *pstat);
off_t   _lseek(void *reent, int fd, off_t pos, int whence);
int     _read(int file, char* ptr, int len);
int     _write(int file, char* ptr, int len);
int     _isatty(int file);
int     _getpid(void);
void    _kill(int pid, int sig);


#endif /* #ifndef __SYSCALLS_H__ */
