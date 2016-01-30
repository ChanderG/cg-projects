/*
 * Log utilities to make life easier.
 */

#include "log.h"

/*
 * Writes message to log file.
 * Specifically -- "output.log"
 */
void logm(const char* tag, char* message_fmt, ...){
  FILE *fp;
  time_t now;

  fp = fopen("output.log", "a");

  time(&now);
  fprintf(fp, "%s [%s]: ", strtok(ctime(&now), "\n"), tag);
  va_list argptr;
  va_start(argptr, message_fmt);
  vfprintf(fp, message_fmt, argptr);
  va_end(argptr);
  fprintf(fp, "\n");

  fclose(fp);
}
