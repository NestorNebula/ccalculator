#ifndef HELPERS_H
#define HELPERS_H

#include "operations.h"
#include "expression.h"
#include "input.h"
#include "error.h"
#include "variable.h"

/*
 * create_input_expression:
 * Reads user input and convert it into an Input corresponding 
 * to a valid expression.
 * Returns a pointer to an Input if no error occurred, else
 * sets an error and returns a null pointer.
 */
Input create_input_expression(void);

/*
 * handle_character:
 * Updates e based on the value of ch.
 * Returns ch if character could be handled without error, -1 otherwise.
 */
wint_t handle_character(Expression e, Input ip, wchar_t ch);

/*
 * handle_variable_name
 * Reads variable name from input. Stops at first non-alphabetical character.
 * If first_char is alphabetical, adds it to the beginning of the string.
 * Returns a pointer to the name string if no error occurred, 
 * else returns a null pointer.
 */
char *handle_variable_name(Input ip, char first_char);

/*
 * handle_number:
 * Updates e based on the value of n.
 * Returns n if number could be handled without error, NaN otherwise.
 */
Number handle_number(Expression e, Input ip, Number n);

/*
 * handle_operation:
 * Performs an operation on n1 and n2 based on os.
 * Exits program prematurely if os isn't a valid operation sign.
 * Returns the result of the operation.
 */
Number handle_operation(OperationSign os, Number n1, Number n2);

/*
 * resolve_level:
 * Computes the result of the expression stored in e's current level.
 * Returns the result if it could be computed, NaN otherwise.
 */
Number resolve_level(Level lvl);

/*
 * search_variable_as_result:
 * Checks if ip sets expression's result as a variable.
 * If so, creates or gets the variable and returns a pointer to its name,
 * else, returns a null pointer.
 */
char *search_variable_as_result(Input ip);

#endif
