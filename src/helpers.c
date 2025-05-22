#include <stdlib.h>
#include <math.h>
#include "helpers.h"

#define DEF_VNAME_LEN 10

#define IS_OPERATOR(ch) ((ch) == '+' || (ch) == '-' \
                        || (ch) == '*' || ch == '/')
#define IS_POW(ch) ((ch) == '^')
#define IS_SQRT(ch) ((ch) == sroot)
#define IS_START_BRACKET(ch) ((ch) == '(')
#define IS_END_BRACKET(ch) ((ch) == ')')
#define IS_BRACKET(ch) (IS_START_BRACKET(ch) || IS_END_BRACKET(ch))
#define IS_SYNTAX(ch) (IS_OPERATOR(ch) || IS_POW(ch) \
                      || IS_SQRT(ch) || IS_BRACKET(ch))

wchar_t sroot;

Input create_input_expression(void) {
  Input user_input = new_input();
  if (user_input == NULL) {
    set_error("Not enough memory to store a new input.\n");
    return NULL;
  }

  // Store user's initial input
  read_input(user_input, stdin);
  wint_t ch;

  FILE *tmp = tmpfile();
  if (tmp == NULL) {
    set_error("Not enough memory to process input.\n");
    delete_input(user_input);
    return NULL;
  }

  /* Write updated version of user input in tmp file.
     Replace variables by their values, except for the variable
     that the expression will define. */

  // Write the variable to define unchanged
  if (search_variable_as_result(user_input) != NULL) {
    reset(user_input);
    do {
      ch = get_next_char(user_input);
      fputc(ch, tmp);
    } while (ch != '=');
  }

  while(!end_of_input(user_input)) {
    Number n = get_next_number(user_input);
    if (isnan(n)) {
      ch = get_next_char(user_input);
      if (IS_SYNTAX(ch) || isspace(ch)) {
        // If syntax or space character, let character unchanged.
        fputwc(ch, tmp);
      } else if (isalpha(ch)) {
        // Check for existing variable and replace it by its value.
        char *var = handle_variable_name(user_input, ch);
        n = get_variable(var);
        if (isnan(n)) {
          set_error("\"%s\" isn't defined.\n", var);
          delete_input(user_input);
          return NULL;
        } else fprintf(tmp, "%lf", n);
        free(var);
      } else {
        // Invalid character (not a space, not syntax and not alphabetical)
        set_error("Invalid character in expression: %lc\n", ch);
        delete_input(user_input);
        return NULL;
      }
    } else fprintf(tmp, "%lf", n);
  }
  // Release space taken by original input and prepare tmp file for reading
  delete_input(user_input);
  rewind(tmp);

  Input expression_input = new_input();
  if (expression_input == NULL) {
    set_error("Not enough memory to store expression\n");
    return expression_input;
  }
  // Store updated expression in final input
  read_input(expression_input, tmp);
  return expression_input;
}

wint_t handle_character(Expression e, Input ip, wchar_t ch) {
  if (IS_OPERATOR(ch)) {
    if(push_operator(e, ch) == -1) {
      set_error("Error with '%lc' operator. "
                "Check that it is used correctly (between two numbers)\n");
      return -1;
    } else return ch;
  }
  Level lvl = get_current_level(e);
  if (IS_SQRT(ch)) {
    Number n = square_root(get_next_number(ip));
    if (n < 0) {
      set_error("Can't compute the square root of a negative number.\n");
    } else if (isnan(handle_number(e, ip, n))) {
      set_error("Error with square root number. "
                "Check that it is used correctly "
                "(separated from other numbers by operators) "
                "and in the correct format.\n");
    } else return ch;
    return -1;
  }

  switch (ch) {
    case '(':
      add_level(e);
      break;
    case ')':
      if (level_count(e) == 1) {
        set_error("Unexpected ')' character. No nested level to close. "
                  "Make sure to use an open bracket before a close bracket.\n");
        return -1;
      }
      Number lvl_result;
      
      // Compute level value, release its memory and add result to prev level
      lvl_result = resolve_level(lvl);
      delete_current_level(e);
      if (isnan(handle_number(e, ip, lvl_result))) {
        set_error("Error when computing expression between square brackets. "
                  "Check that the expression's syntax is "
                  "valid and non-empty.\n");
        return -1;
      }
      break;
    default:
      if (isspace(ch)) break;
      set_error("Unexpected character: %lc\n", ch);
      return -1;
  }

  return ch;
}

char *handle_variable_name(Input ip, char first_char) {
  char *variable_name = malloc(DEF_VNAME_LEN+1);
  if (variable_name == NULL) return variable_name;
  unsigned int size = DEF_VNAME_LEN, length = 0;

  // Add first char to name if alphabetical
  if (iswalpha(first_char)) {
    variable_name[length++] = first_char;
  } 

  // Add characters while they are alphabetical, increase size accordingly
  while (iswalpha(hint_next_char(ip))) {
    char next_char = get_next_char(ip);
    if (length == size) {
      variable_name = realloc(variable_name, size * 2 + 1);
      if (variable_name == NULL) return variable_name;
      size *= 2;
    }
    variable_name[length++] = next_char;
  }
  variable_name[length] = '\0';
  return variable_name;
}

Number handle_number(Expression e, Input ip, Number n) {
  // Compute n^p if n followed by '^'
  if (IS_POW(hint_next_char(ip))) {
    get_next_char(ip);
    Number p;
    if (isdigit(hint_next_char(ip))) p = get_next_number(ip);
    else {
      // Replace variable by its value
      char *variable_name = handle_variable_name(ip, '\0');
      p = get_variable(variable_name);
    }
    if (isnan(p)) {
      set_error("Invalid value after '^' symbol. "
                "The correct syntax is n^p where p is a number.\n");
      return NAN;
    }
    n = power(n, p);
  }
  
  // Resolve one of the current level's operations before storing number
  if (current_level_full(e)) {
    Level lvl = get_current_level(e);
    Number result;

    // Resolve second operation if it has precedence, first operation otherwise
    if ((lvl->op_signs[1] == '*' || lvl -> op_signs[1] == '/') && 
        (lvl->op_signs[0] == '+' || lvl->op_signs[0] == '-')) {
      result = handle_operation(lvl->op_signs[1], lvl->numbers[1], n);
      lvl->numbers[1] = result;
    } else {
      result = 
        handle_operation(lvl->op_signs[0], lvl->numbers[0], lvl->numbers[1]);
      lvl->numbers[0] = result;
      lvl->op_signs[0] = lvl->op_signs[1];
      lvl->numbers[1] = n;
    }
    lvl->os_count--;
    return n;
  } else if (isnan(push_number(e, n))) {
    set_error("Error with number %g. "
              "Make sure that it is used correctly "
              "(separated from other numbers by operators).\n", n);
    return NAN;
  } else {
    return n;
  }
}
  
Number handle_operation(OperationSign os, Number n1, Number n2) {
  switch (os) {
    case '+':
      return add(n1, n2);
    case '-':
      return subtract(n1, n2);
    case '*':
      return multiply(n1, n2);
    case '/':
      return divide(n1, n2);
    default:
      exit_with_error(stderr, "Invalid operation sign: %c\n", os);
      return NAN;
  }
}

Number resolve_level(Level lvl) {
  if (!lvl->n_count) {
    set_error("No number in expression.\n");
    return NAN;
  }
  
  // Avoid resolving level if there are too much operators
  if (lvl->n_count == 1) {
    if (lvl->os_count) {
      set_error("Not enough numbers in expression.\n");
      return NAN;
    }
    return lvl->numbers[0];
  }
  if (lvl->os_count != 1) {
    set_error("Not enough numbers in expression.\n");
    return NAN;
  }

  return handle_operation(lvl->op_signs[0], lvl->numbers[0], lvl->numbers[1]);
}

char *search_variable_as_result(Input ip) {
  wint_t ch;
  
  // Skip spaces before variable name
  while (isspace(ch = get_next_char(ip)));
  if (isalpha(ch)) {
    char *variable_name = handle_variable_name(ip, ch);
    if (variable_name == NULL) return variable_name;

    // Skip spaces between variable name and next non-space character
    while (isspace(ch = get_next_char(ip)));
    if (ch == '=') {
      // Init variable to NaN if it doesn't already exist
      if (isnan(get_variable(variable_name))) add_variable(variable_name, NAN);
      return variable_name;
    }
  }
  // Reset to the beginning of input if no variable was found
  reset(ip);
  return NULL;
}
