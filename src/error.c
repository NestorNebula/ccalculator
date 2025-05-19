#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "error.h"

struct error {
  bool status;
  char *description;
} Error = { false, NULL };

char *set_error (const char *err) {
  Error.status = true;
  Error.description = realloc(Error.description, strlen(err) + 1);
  if (Error.description == NULL) return Error.description;
  strcpy(Error.description, err);
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

void exit_with_error(const char *err, FILE *stream) {
  fputs(err, stream);
  exit(EXIT_FAILURE);
}
