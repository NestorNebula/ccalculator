#include <stdlib.h>
#include <math.h>
#include "expression.h"

struct expression_type {
  Level current_level;
};

static Level init_level(Level prev) {
  Level lvl = malloc(sizeof(struct level_type));
  if (lvl == NULL) return lvl;
  lvl->n_count = lvl->os_count = 0;
  lvl->prev = prev;
  return lvl;
}


Expression new_expression(void) {
   Expression e = malloc(sizeof(struct expression_type));
   if (e == NULL) return e;
   e->current_level = init_level(NULL);
   if (e->current_level == NULL) {
     free(e);
     return NULL;
   }
   return e;
}

void delete_expression(Expression e) {
  for (Level tmp = e->current_level; tmp != NULL; tmp = e->current_level) {
    e->current_level = tmp->prev;
    free(tmp);
  }
  free(e);
}


Number push_number(Expression e, Number n) {
  if (current_level_full(e)) return NAN;
  if (e->current_level->n_count != e->current_level->os_count) return NAN;
  e->current_level->numbers[e->current_level->n_count] = n;
  e->current_level->n_count++;
  return n;
}


int push_operator(Expression e, OperationSign os) {
  if (current_level_full(e)) return -1;
  if (e->current_level->n_count == e->current_level->os_count) return -1;
  e->current_level->op_signs[e->current_level->os_count] = os;
  e->current_level->os_count++;
  return os;
}

Level add_level(Expression e) {
  Level lvl = init_level(e->current_level);
  if (lvl == NULL) return lvl;
  e->current_level = lvl;
  return lvl;
}

Level get_current_level(Expression e) {
  return e->current_level;
}

bool current_level_full(Expression e) {
  return e->current_level->n_count == MAX_NUM_PER_LVL
         && e->current_level->os_count == MAX_OS_PER_LVL;
}

void delete_current_level(Expression e) {
  if (level_count(e) == 1) {
    e->current_level->n_count = e->current_level->os_count = 0;
  } else {
    Level tmp = e->current_level;
    e->current_level = e->current_level->prev;
    free(tmp);
  }
}

unsigned int level_count(Expression e) {
  unsigned int count = 0;
  for (Level tmp = e->current_level; tmp != NULL; tmp = tmp->prev) {
    count++;
  }
  return count;
}
