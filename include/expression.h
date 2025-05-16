#ifndef EXPRESSION_H
#define EXPRESSION_H

#include <stdbool.h>
#include "types.h"

/*
 * new_expression:
 * Creates a new expression and returns a pointer to it.
 * Returns a null pointer if an error occurred during memory allocation.
 */
Expression new_expression(void);

/*
 * delete_expression:
 * Releases the memory pointed to by e.
 */
void delete_expression(Expression e);

/*
 * push_number:
 * Pushes n to the numbers stored in the current level of e.
 * Returns n if it was correctly pushed, NaN otherwise. 
 */
Number push_number(Expression e, Number n);

/*
 * push_operator:
 * Pushes os to the operator signs stored in the current level of e.
 * Returns os if it was correctly pushed, -1 if an error occurred.
 */
int push_operator(Expression e, OperatorSign op);

/*
 * add_level:
 * Creates a new level and sets it as e's current level.
 * Returns a pointer to the new level if no error occurred,
 * else, returns a null pointer.
 */
Level add_level(Expression e);

/*
 * get_current_level:
 * Returns a pointer to the current level of e.
 */
Level get_current_level(Expression e);

/*
 * current_level_full:
 * Returns true if e's current level is full, false otherwise.
 */
bool current_level_full(Expression e);

/*
 * delete_current_level:
 * If it isn't the last level, 
 * releases the memory taken by e's current level and
 * sets e's current level to the previous one.
 * Else, clears values stored inside the current level.
 */
void delete_current_level(Expression e);

/*
 * level_count:
 * Returns number of nested levels in e.
 */
unsigned int level_count(Expression e);

#endif
