
/**
 * @file err.c
 * @author your name (you@domain.com)
 * @brief 输出至标准错误的出错函数
 * @version 0.1
 * @date 2022-03-27
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include "apue.h"
#include <errno.h>      /* for definition of errno*/
#include <stdarg.h>     /* ISO C variable aruments*/

static void err_doit(int, int, cost char *, va_list);

/**
 * @brief Nofatal error related to a system call.
 * Print a message and return.
 * 
 */
void
err_ret(const char *fmt, ...) {
    va_list ap;

    va_start(ap, fmt);
    err_doit(1, errno, fmt, ap);
    va_end(ap);
}

/**
 * @brief Fatal error related to a system call.
 * Print a message and terminate.
 * 
 */
void 
err_sys(const char *fmt, ...) {
    va_list ap;

    va_start(ap, fmt);
    err_doit(1, errno, fmt, ap);
    va_end(ap);
    exit(1);
}

/**
 * @brief Nonfatal error unrelated to a system call.
 * Error code passed as explict parameter.
 * Print a message and return.
 * 
 */
void
err_cont(int error, const char *fmt, ...) {
    va_list ap;

    va_start(ap, fmt);
    err_doit(1, error, fmt, ap);
    va_end(ap);
}

/**
 * @brief Fatal error unrelated to a system call.
 * Error code apssed as explict parameter. 
 * Print a messgae and terminate
 * 
 */
void err_exit(int error, const char *fmt, ...) {
    va_list ap;

    va_start(ap, fmt);
    err_doit(1, error, fmt, ap);
    va_end(ap);
    exit(1);
}

/**
 * @brief Fatal error related to a system call.
 * Print a message , dump core, and terminate.
 * 
 */
void 
err_dump(const char *fmt, ...) {
    va_list ap;

    va_start(ap, fmt);
    err_doit(1, errno, fmt, ap);
    va_end(ap);
    abort();        /* dump core and terminate */
    exit(1);
}

/**
 * @brief Nonfatal error unrelated to a system call. 
 * Print a message and return.
 * 
 */
void
err_msg(const char *fmt, ...) {
    va_list ap;

    va_start(ap, fmt);
    err_doit(0, 0, fmt, ap);
    va_end(ap);
}

/**
 * @brief Fatal error unrelated toa system call.
 * Print a message and terminate.
 */
void 
err_quit(const char *fmt, ...) {
    va_list ap;

    va_start(ap, fmt);
    err_doit(0, 0, fmt, ap);
    va_end(ap);
    exit(1);
}

/**
 * @brief Print a message and return to caller.
 * caller specifies "errnoflag"
 * 
 */
static void 
error_diot(int errnoflag, int error, cost char *fmt, va_list ap) {
    char buf[MAXLINE];

    vsnprintf(buf, MAXLINE-1, fmt, ap);
    if (errnoflag)
        snprintf(buf+strlen(buf), MAXLINE-strlen(buf) - 1, ": %s", strerror(error));
    strcat(buf, "\n");
    fflush(stdout);     /* in case stdout and stderr are the same */
    fputs(buf, stderr);
    fflush(NULL);       /* fflushes all stdio output streams */
}


