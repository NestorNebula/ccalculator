#ifndef VARIABLE_H
#define VARIABLE_H

#include "types.h"

/*
 * add_variable:
 * Creates a new variable named with name with a value of n.
 * Returns n if no error occurred, NaN otherwise.
 */
Number add_variable(const char *name, Number n);

/*
 * get_variable:
 * Searches variable named name in stored variables.
 * If found, returns the value of name, else returns NaN.
 */
Number get_variable(const char *name);

/*
 * update_variable:
 * Sets the value of variable named name with n.
 * Returns n if variable found and updated, NaN otherwise.
 */
Number update_variable(const char *name, Number n);

/*
 * delete_variable:
 * Deletes the variable named name.
 * Returns the value of name if it could be found and deleted, NaN otherwise.
 */
Number delete_variable(const char *name);

#endif
