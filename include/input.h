#ifndef INPUT_H
#define INPUT_H

#include <stdbool.h>
#include <wchar.h>
#include "types.h"

typedef struct input_type *Input;

/*
 * new_input:
 * Creates a new input and returns a pointer to it.
 * Returns a null pointer if an error occurred during memory allocation.
 */
Input new_input(void);

/*
 * delete_input:
 * Releases memory taken by ip.
 */
void delete_input(Input ip);

/*
 * read_input:
 * Reads from stream until a new line of the end of file is reached.
 * Stores the string read inside ip for other functions calls.
 * Returns the number of characters read or -1 if an error occurred.
 */
int read_input(Input ip, FILE * stream);

/*
 * get_next_number:
 * Returns the first Number in the input stored in ip. The search starts
 * where the last search left off and stops if it meets a non-digit character.
 * This function assumes that Number is of type double.
 * If no Number could be read, returns NaN.
 */
Number get_next_number(Input ip);

/*
 * get_next_char:
 * Returns the first character in the input stored in ip. The search starts
 * where the last search left off.
 * If no character could be read, returns WEOF.
 */
wint_t get_next_char(Input ip);

/*
 * hint_next_char:
 * Same as get_next_char but doesn't advance to the 
 * next character after reading. Thus, the next searching function call
 * will restart at the same location.
 */
wint_t hint_next_char(Input ip);

/*
 * end_of_input:
 * Returns true if the end of the input stored in ip was reached by a call
 * of any search function, false otherwise.
 */
bool end_of_input(Input ip);

#endif
