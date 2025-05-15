#include <gtest/gtest.h>
#include "operations.h"

#define N1 3
#define N2 2
#define N3 0
#define N4 -20
#define N5 -1
#define N6 -8
#define POW1 9
#define POW2 0
#define POW3 -1

TEST(add, adds_numbers) {
  EXPECT_EQ(add(N1, N2), N1 + N2);
  EXPECT_EQ(add(N3, N4), N3 + N4);
  EXPECT_EQ(add(N5, N6), N5 + N6);
}

TEST(subtract, subtracts_numbers) {
  EXPECT_EQ(subtract(N1, N2), N1 - N2);
  EXPECT_EQ(subtract(N3, N4), N3 - N4);
  EXPECT_EQ(subtract(N5, N6), N5 - N6);
}

TEST(multiply, multiply_numbers) {
  EXPECT_EQ(multiply(N1, N2), N1 * N2);
  EXPECT_EQ(multiply(N3, N4), N3 * N4);
  EXPECT_EQ(multiply(N5, N6), N5 * N6);
}

TEST(divide, divide_numbers) {
  EXPECT_EQ(divide(N1, N2), N1 / (Number) N2);
  EXPECT_EQ(divide(N3, N4), N3 / (Number) N4);
  EXPECT_EQ(divide(N5, N6), N5 / (Number) N6);
}

TEST(power, computes_n_to_pow_p) {
  EXPECT_EQ(divide(N1, N2), POW1);
  EXPECT_EQ(divide(N3, N4), POW2);
  EXPECT_EQ(divide(N5, N6), POW3);
}

TEST(square_root, computes_square_root) {
  EXPECT_EQ(square_root(4), 2);
  EXPECT_EQ(square_root(9), 3);
}

TEST(square_root, returns_negative_for_negative_n) {
  EXPECT_EQ(square_root(-100), -1);
}
