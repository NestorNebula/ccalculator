#ifndef ERROR_H
#define ERROR_H

#include <stdbool.h>

/*
 * set_error:
 * Sets error status to active and error description to err.
 * Returns a pointer to the error's description.
 */
char *set_error(const char *err);

/*
 * clear_error:
 * Sets error status to inactive and clears actual error description.
 * Returns a pointer to the new description.
 */
char *clear_error(void);

/*
 * has_error:
 * Returns true if error status is active, false otherwise.
 */
bool has_error(void);

/*
 * print_error:
 * Prints the actual error description to stream.
 */
void print_error(FILE *stream);

/*
 * exit_with_error:
 * A shortcut for set_error(err), print_error() and exit(EXIT_FAILURE).
 * Prints err to stream before exiting the program.
 */
void exit_with_error(const char *err, FILE *stream);

#endif
