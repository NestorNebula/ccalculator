#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "error.h"

#define DEF_LEN 10

struct error {
  bool status;
  char *description;
} Error = { false, NULL };

char *set_error (const char *err, ...) {
  Error.status = true;
  unsigned int length = DEF_LEN;
  va_list ap;
  do {
    length *= 2;
    Error.description = realloc(Error.description, length + 1);
    va_start(ap, err);
    if (Error.description == NULL) return Error.description;
    va_end(ap);
  } while (vsnprintf(Error.description, length + 1, err, ap) > length); 
  return Error.description;
}

char *clear_error(void) {
  Error.status = false;
  Error.description = realloc(Error.description, 1);
  *Error.description = '\0';
  return Error.description;
}

bool has_error(void) {
  return Error.status;
}

void print_error(FILE *stream) {
  fputs(Error.description, stream);
}

void exit_with_error(FILE *stream, const char *err, ...) {
  va_list ap;
  va_start(ap, err);
  vfprintf(stream, err, ap);
  va_end(ap);
  exit(EXIT_FAILURE);
}
