#include <locale.h>
#include <stdlib.h>
#include <math.h>
#include "operations.h"
#include "expression.h"
#include "input.h"
#include "error.h"
#include "variable.h"

#define DEF_VNAME_LEN 10

wchar_t sroot;

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

int main(void) {
  setlocale(LC_ALL, "en_US.UTF-8");
  mbtowc(&sroot, "\xe2\x88\x9a", 3);

  printf("\nThis programs prints the result of mathematical expressions.\n"
         "The characters allowed apart from numbers and parentheses are: "
         "'+', '-', '*' and '/' for mathematical operations, '^' for power "
         "in the format \"p^n\" where p and n are numbers (not expressions) "
         "and '%lc' for square root of n in format \"%lcn\" "
         "where n is a number (not an expression).\n\n",
         sroot, sroot);

  for (;;) {
    Expression e = new_expression();
    if (e == NULL) {
      printf("Not enough memory to store a new expression.\n");
      break;
    }
    Input ip = new_input();
    if (ip == NULL) {
      printf("Not enough memory to store a new input.\n");
      delete_expression(e);
      break;
    }

    clear_error();

    printf("Enter an expression: ");
    read_input(ip, stdin);

    char *variable_name = search_variable_as_result(ip);

    while (!end_of_input(ip)) {
      Number n = get_next_number(ip);
      if (isnan(n)) {
        wint_t ch = get_next_char(ip);
        if (handle_character(e, ip, ch) == -1) {
          set_error("Error around character '%lc'.\n", ch);
          break;
        }
      } else {   
        if (isnan(handle_number(e, ip, n))) {
          set_error("Error around number %g.\n", n);
          break;
        }
      }
    }

    if (!has_error()) {
      Number result = resolve_level(get_current_level(e));
      if (isnan(result) || level_count(e) != 1) {
        fprintf(stderr, "Error during final calculation. "
                "Please check the expression's syntax.\n");
      } else if (!variable_name) {
        printf("Expression's result: %g\n", result);
      } else if (!isnan(get_variable(variable_name))) {
        update_variable(variable_name, result);
      } else {
        printf("Expression's result (%g) couldn't be set as %s.\n",
               result, variable_name);
      }
    } else {
      print_error(stderr);
    }
    
    delete_expression(e);
    delete_input(ip);
  }
}

wint_t handle_character(Expression e, Input ip, wchar_t ch) {
  if (ch == '+' || ch == '-' || ch == '*' || ch == '/') {
    return push_operator(e, ch);
  }
  Level lvl = get_current_level(e);
  if (ch == sroot) {
    Number n;
    if (isdigit(hint_next_char(ip))) {
      n = get_next_number(ip);
    } else {
      char *variable_name = handle_variable_name(ip, '\0');
      n = get_variable(variable_name);
    }
    if (isnan(n)) return -1;
    n = square_root(n);
    if (n < 0 || isnan(handle_number(e, ip, n))) return -1;
    else return ch;
  }

  switch (ch) {
    case '(':
      add_level(e);
      break;
    case ')':
      if (level_count(e) == 1) return -1;
      Number lvl_result;
      lvl_result = resolve_level(lvl);
      delete_current_level(e);
      if (isnan(handle_number(e, ip, lvl_result))) return -1;
      break;
    case ' ':
      break;
    default:
      if (isalpha(ch)) {
        char *variable_name = handle_variable_name(ip, ch);
        if (variable_name != NULL) {
          Number n = get_variable(variable_name);
          if (!isnan(n)) {
            handle_number(e, ip, n);
            return n;
          } 
        }
      }
      return -1;
  }

  return ch;
}

char *handle_variable_name(Input ip, char first_char) {
  char *variable_name = malloc(DEF_VNAME_LEN+1);
  if (variable_name == NULL) return variable_name;
  unsigned int size = DEF_VNAME_LEN, length = 0;
  if (iswalpha(first_char)) {
    variable_name[length++] = first_char;
  } 
  while (iswalpha(hint_next_char(ip))) {
    char next_char = get_next_char(ip);
    if (length == size) {
      variable_name = realloc(variable_name, size * 2);
      if (variable_name == NULL) return variable_name;
      size *= 2;
    }
    variable_name[length++] = next_char;
  }
  variable_name[length] = '\0';
  return variable_name;
}

Number handle_number(Expression e, Input ip, Number n) {
  if (hint_next_char(ip) == '^') {
    get_next_char(ip);
    Number p;
    if (isdigit(hint_next_char(ip))) p = get_next_number(ip);
    else {
      char *variable_name = handle_variable_name(ip, '\0');
      p = get_variable(variable_name);
    }
    if (isnan(p)) return NAN;
    n = power(n, p);
  }
  if (current_level_full(e)) {
    Level lvl = get_current_level(e);
    Number result;
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
  } else {
    return push_number(e, n);
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
  if (!lvl->n_count) return 0;
  if (lvl->n_count == 1) {
    if (lvl->os_count) return NAN;
    return lvl->numbers[0];
  }
  if (lvl->os_count != 1) return NAN;
  return handle_operation(lvl->op_signs[0], lvl->numbers[0], lvl->numbers[1]);
}

char *search_variable_as_result(Input ip) {
  wint_t ch;
  while (isspace(ch = get_next_char(ip)));
  if (isalpha(ch)) {
    char *variable_name = handle_variable_name(ip, ch);
    if (variable_name == NULL) return variable_name;
    while (isspace(ch = get_next_char(ip)));
    if (ch == '=') {
      if (isnan(get_variable(variable_name))) add_variable(variable_name, 0);
      return variable_name;
    }
  }
  reset(ip);
  return NULL;
}
