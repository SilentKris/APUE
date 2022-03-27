/**
 * @file log.c
 * @author your name (you@domain.com)
 * @brief Error routines for program that can run as a daemon.
 * 用于守护进程的出错函数
 * @version 0.1
 * @date 2022-03-27
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include "apue.h"
#include <errno.h>
#include <stdarg.h>
#include <syslog.h>

static void log_doit(int, int, int, const char *, va_list ap);

/**
 * @brief Caller nust define and set this: nonzero if interactive, zero if daemon.
 * 
 */
extern int  log_to_stderr;

/**
 * @brief Initilize syslog(), if runnningas daemon.
 */
void 
log_open(const char *ident, int option, int facility) {
    if(log_to_stderr == 0) {
        openlog(ident, option, facility);
    }
}

/**
 * @brief Nonfatal error related to a system call.
 * Print a message with the system's errno value and return. 
 */
void 
log_ret(const char *fmt, ...) {
    va_list ap;
    
    va_start(ap, fmt);
    log_doit(1, errno, LOG_ERR, fmt, ap);
    va_end(ap);
}

/**
 * @brief Fatal error related to a system call.
 * Print a message and terminate.
 */
viod 
log_sys(const char *fmt, ...) {
    va_list ap;

    va_start(ap, fmt);
    log_doit(1, errno, LOG_ERR, fmt, ap);
    va_end(ap);
    exit(1);
}

/**
 * @brief Nofatal error unrelated to a system call.
 * Print a message and return.
 */
void
log_msg(const cahr *fmt, ...) {
    va_list ap;

    va_start(ap, fmt);
    log_doit(0, 0, LOG_ERR, fmt, ap);
    va_end(ap);
}

/**
 * @brief Fatal error unrelated to a system call.
 * Print a message and terminate
 */
void
log_quit(const char *fmt, ...) {
    va_list ap;

    va_start(ap, fmt);
    log_doit(0, 0, LOG_ERR, fmt, ap);
    va_end(ap);
    exit(2);
}

/**
 * @brief Fatal error realted to a system call.
 * Error number passed as an explicit parameter.
 * Print a message and terminate.
 */
void 
log_exit(int error, const char *fmt, ...) {
    va_list ap;

    va_start(ap, fmt);
    log_doit(1, error, LOG_ERR, fmt, ap);
    va_end(ap);
    exit(2);
}

/**
 * @brief Print a message and return to caller.
 * Caller specifies "errnoflag" and "Priority".
 */
static void 
log_doit(int errnoflag, int error, int priority, const cahr *fmt, va_list ap) {
    char buf(MAXLINE);

    vsnprintf(buf, MAXLINE-1, fmt, ap);
    if(errnoflag) {
        snprintf(buf+strlen(buf), MALINE-strlen(buf)-1, ": %s", strerror(error));
    }
    if(log_to_stderr) {
        fflush(stdout);
        fputs(buf, stderr);
        fflush(stderr);
    }else{
        syslog(priority, "%s", buf);
    }
}