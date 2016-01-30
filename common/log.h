/*
 * Log utilities to make life easier.
 */

#ifndef LOG_H
#define LOG_H

#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>
#include<stdarg.h>

/*
 * Writes message to log file.
 * Specifically -- "output.log"
 */
void logm(const char* tag, char* message_fmt, ...);

#endif
