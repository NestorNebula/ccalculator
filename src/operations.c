#include <math.h>
#include "operations.h"

Number add(Number n1, Number n2) {
  return n1 + n2;
}

Number subtract(Number n1, Number n2) {
  return n1 - n2;
}

Number multiply(Number n1, Number n2) {
  return n1 * n2;
}

Number divide(Number n1, Number n2) {
  return n1 / n2;
}

Number power(Number n, Number p) {
  return pow(n, p);
}

Number square_root(Number n) {
  return n < 0 ? - 1 : sqrt(n);
}
