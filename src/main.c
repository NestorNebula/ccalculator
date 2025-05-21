#include <locale.h>
#include <stdlib.h>
#include <math.h>
#include "helpers.h"

extern wchar_t sroot;

int main(void) {
  setlocale(LC_ALL, "en_US.UTF-8");
  mbtowc(&sroot, "\xe2\x88\x9a", 3);

  printf("\nThis programs prints the result of mathematical expressions.\n"
         "The characters allowed inside expressions apart from numbers "
         "and parentheses are: '+', '-', '*' and '/' operation signs, "
         "'^' for power in the format \"p^n\" where p and n are numbers "
         "(not expressions) and '%lc' for square root of n in format \"%lcn\" "
         "where n is a number (not an expression).\n\n"
         "In the case of a \"normal\" expression, the result will be printed. "
         "You can decide to redirect it and to assign its value to a "
         "variable, you'll then be able to use that variable in other "
         "expressions.\n"
         "Example:\n\n//Prints 9\n3^2\n\n//Assigns 9 to x\nx = 3^2\n\n"
         "//Prints 3\n%lcx\n",
         sroot, sroot, sroot);

  for (;;) {
    Expression e = new_expression();
    if (e == NULL) {
      printf("Not enough memory to store a new expression.\n");
      break;
    }

    clear_error();

    printf("\nEnter an expression: ");
    Input ip = create_input_expression();
    if (ip == NULL) {
      print_error(stderr);
      delete_expression(e);
      continue;
    }

    char *variable_name = search_variable_as_result(ip);

    while (!end_of_input(ip)) {
      Number n = get_next_number(ip);
      if (isnan(n)) {
        wint_t ch = get_next_char(ip);
        if (handle_character(e, ip, ch) == -1) break;
      } else if (isnan(handle_number(e, ip, n))) break;
    }

    if (!has_error()) {
      Number result = resolve_level(get_current_level(e));
      if (isnan(result)) {
        if (variable_name) {
          set_error("No expression, delete %s\n", variable_name);
        } else break;
        if (variable_name) delete_variable(variable_name);
      } else if (level_count(e) != 1) {
        set_error("Too many nested levels. "
                  "Make sure to complete each open bracket "
                  "by a close bracket.\n");
      } else if (!variable_name) {
        printf("%g\n", result);
      } else if (isnan(update_variable(variable_name, result))) {
        set_error("Expression's result (%g) couldn't be set as %s.\n",
               result, variable_name);
      }
    }

    if (has_error()) {
      print_error(stderr);
      if (variable_name) delete_variable(variable_name);
    }
    
    delete_expression(e);
    delete_input(ip);
  }
}
