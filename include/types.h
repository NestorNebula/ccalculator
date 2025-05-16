#ifndef TYPES_H
#define TYPES_H

#define MAX_NUM_PER_LVL 2
#define MAX_OS_PER_LVL 2

typedef double Number;

typedef unsigned char OperationSign;

typedef struct expression_type *Expression;

typedef struct level_type {
  Number numbers[MAX_NUM_PER_LVL];
  OperationSign op_signs[MAX_OS_PER_LVL];
  unsigned int n_count, os_count;
  struct level_type *prev;
} *Level;

#endif
