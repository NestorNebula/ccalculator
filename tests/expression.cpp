#include <gtest/gtest.h>

extern "C" {
  #include "expression.h"
}

#define N1 100
#define N2 3
#define N3 -1
#define OS1 '+'
#define OS2 '-'
#define OS3 '*'


TEST(new_expression, creates_expression) {
  Expression e = new_expression();
  EXPECT_THAT(e, NotNull());
  delete_expression(e);
}

TEST(push_number, returns_pushed_number) {
  Expression e = new_expression();
  EXPECT_EQ(push_number(e, N1), N1);
  delete_expression(e);
}

TEST(push_operator, returns_pushed_operator) {
  Expression e = new_expression();
  push_number(e, N1);
  EXPECT_EQ(push_operator(e, OS1), OS1);
  delete_expression(e);
}

TEST(push_number, returns_nan_on_error) {
  Expression e = new_expression();
  push_number(e, N1);
  EXPECT_THAT(push_number(e, N2), isNaN());
  push_operator(e, OP1);
  EXPECT_THAT(push_number(e, N2);
  EXPECT_THAT(push_number(e, N3), !isNaN());
  delete_expression(e);
}

TEST(push_operator, returns_minus_one_on_error) {
  Expression e = new_expression();
  push_number(e, N1);
  push_operator(e, OS1);
  EXPECT_EQ(push_operator(e, OS2), -1);
  push_number(e, N2);
  EXPECT_EQ(push_operator(e, OS2), OS2);
  EXPECT_EQ(push_operator(e, OS3), -1);
  delete_expression(e);
}

TEST(add_level, creates_level) {
  Expression e = new_expression();
  Level l = add_level(e);
  EXPECT_THAT(ex, NotNull());
  delete_expression(e);
}

TEST(get_current_level, returns_level) {
  Expression e = new_expression();
  Level l = get_current_level(e);
  EXPECT_THAT(*l, A<struct level_type>());
  delete_expression(e);
}

TEST(current_level_full, returns_false_when_level_not_full) {
  Expression e = new_expression();
  EXPECT_FALSE(current_level_full());
  delete_expression(e);
}

TEST(current_level_full, returns_true_when_level_is_full) {
  Expression e = new_expression();
  push_number(e, N1);
  push_operator(e, OS1);
  push_number(e, N2);
  push_operator(e, OS2);
  EXPECT_TRUE(current_level_full());
  delete_expression(e);
}

TEST(delete_current_level, sets_prev_level_as_current_level) {
  Expression e = new_expression();
  push_number(e, N1);
  add_level(e);
  push_number(e, N2);
  delete_current_level(e);
  Level l = get_current_level(e);
  EXPECT_EQ(l->numbers[0], N1);
  delete_expression(e);
}

TEST(delete_current_level, clears_only_level) {
  Expression e = new_expression();
  push_number(e, N1);
  delete_current_level;
  Level l = get_current_level(e);
  EXPECT_EQ(l->n_count, 0);
  delete_expression(e);
}

TEST(level_count, returns_number_of_levels) {
  Expression e = new_expression();
  for (int i = 0; i <= 10; i++) {
    EXPECT_EQ(level_countt(), i);
    add_level(e);
  }
  delete_expression(e);
}
