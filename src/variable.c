#include <math.h>
#include <string.h>
#include <stdlib.h>
#include "variable.h"

struct variable {
  char *name;
  Number value;
  struct variable *next;
} *first = NULL;

Number add_variable(const char *name, Number n) {
  // Create variable only if it doesn't exist
  if (isnan(get_variable(name))) {
    struct variable *prev = NULL, *next = first;

    // Order variable alphabetically
    while (next != NULL && strcmp(name, next->name) > 0) {
      prev = next;
      next = next->next;
    }
    struct variable *var = malloc(sizeof(struct variable));
    if (var == NULL) return NAN;
    var->name = malloc(strlen(name) + 1);
    if (var->name == NULL) return NAN;
    strcpy(var->name, name);
    var->value = n;
    var->next = next;
    if (prev) prev->next = var;
    else first = var;
    return n;
  } else return NAN;
}

Number get_variable(const char *name) {
  struct variable *var = first;
  while (var != NULL) {
    int cmp = strcmp(name, var->name);
    if (!cmp) return var->value;
    
    // Stop if var would have been before current variable (alphabetically)
    if (cmp < 0) break;

    var = var->next;
  }
  return NAN;
}

Number update_variable(const char *name, Number n) {
  struct variable *var = first;
  while (var != NULL) {
    int cmp = strcmp(name, var->name);
    if (!cmp) {
      var->value = n;
      return n;
    }

    // Stop if var would have been before current variable (alphabetically)
    if (cmp < 0) break;

    var = var->next;
  }
  return NAN;
}

Number delete_variable(const char *name) {
  struct variable *prev = NULL, *var = first;
  while (var != NULL) {
    int cmp = strcmp(name, var->name); 
    if (!cmp) {
      Number n = var->value;
      if (prev) {
        prev->next = var->next;
      } else {
        first = var->next;
      }
      free(var);
      return n;
    }

    // Stop if var would have been before current variable (alphabetically)
    if (cmp < 0) break;

    prev = var;
    var = var->next;
  }
  return NAN;
}
