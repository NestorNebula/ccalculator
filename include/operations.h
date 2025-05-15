#ifndef OPERATIONS_H
#define OPERATIONS_H

typedef double Number;

/*
 * add:
 * Adds n1 and n2 and returns the sum.
 */
Number add(Number n1, Number n2);

/*
 * subtract:
 * Subtracts n1 and n2 and returns the difference.
 */
Number subtract(Number n1, Number n2);

/*
 * multiply:
 * Multiplies n1 and n2 and returns the product.
 */
Number multiply(Number n1, Number n2);

/*
 * divide:
 * Divides n1 and n2 and returns the quotient.
 */
Number divide(Number n1, Number n2);

/*
 * power:
 * Returns n to the power of p.
 */
Number power(Number n, Number p);

/*
 * square_root:
 * Returns the square root of n or -1 if n is negative.
 */
Number square_root(Number n);

#endif
