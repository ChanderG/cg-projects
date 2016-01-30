/*
 * Log utilities to make life easier.
 */

#include "log.h"

/*
 * Writes message to log file.
 * Specifically -- "output.log"
 */
void logm(const char* tag, const char* message){
  FILE *fp;
  time_t now;

  fp = fopen("output.log", "a");

  time(&now);
  fprintf(fp, "%s [%s]: %s\n", strtok(ctime(&now), "\n"), tag, message);

  fclose(fp);
}
