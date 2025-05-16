#ifndef TYPES_H
#define TYPES_H

typedef double Number;

typedef unsigned char OperationSign;

typedef struct expression_type *Expression;

typedef struct level_type {
  Number n1, n2;
  OperationSign os1, os2;
  unsigned int n_count, os_count;
  struct level_type *prev;
} *Level;

#endif
