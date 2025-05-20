#include <gtest/gtest.h>
#include <gmock/gmock.h>

extern "C" {
  #include "variable.h"
}

#define NUM1 1
#define NUM2 2
#define NUM3 3
#define NAME1 "VAR"
#define NAME2 "VAR2"

TEST(add_variable, returns_value_after_adding_variable) {
  EXPECT_EQ(add_variable(NAME1, NUM1), NUM1);
  delete_variable(NAME1);
}

TEST(add_variable, returns_nan_for_existing_variable) {
  add_variable(NAME1, NUM1);
  EXPECT_THAT(add_variable(NAME1, NUM2), ::testing::IsNan());
  delete_variable(NAME1);
}

TEST(get_variable, returns_variable_value) {
  add_variable(NAME1, NUM1);
  EXPECT_EQ(get_variable(NAME1), NUM1);
  delete_variable(NAME1);
}

TEST(get_variable, returns_nan_for_nonexistent_variable) {
  EXPECT_THAT(get_variable(NAME1), ::testing::IsNan());
  add_variable(NAME1, NUM1);
  EXPECT_THAT(get_variable(NAME2), ::testing::IsNan());
  delete_variable(NAME1);
}

TEST(update_variable, returns_updated_value) {
  add_variable(NAME1, NUM1);
  EXPECT_EQ(update_variable(NAME1, NUM2), NUM2);
  delete_variable(NAME1);
}

TEST(update_variable, returns_nan_for_nonexistent_variable) {
  EXPECT_THAT(update_variable(NAME1, NUM1), ::testing::IsNan());
  add_variable(NAME1, NUM1);
  EXPECT_THAT(update_variable(NAME2, NUM2), ::testing::IsNan());
  delete_variable(NAME1);
}

TEST(delete_variable, returns_deleted_variable_value) {
  add_variable(NAME1, NUM1);
  EXPECT_EQ(delete_variable(NAME1), NUM1);
}

TEST(delete_variable, returns_nan_for_nonexistent_variable) {
  EXPECT_THAT(delete_variable(NAME1), ::testing::IsNan());
  add_variable(NAME1, NUM1);
  EXPECT_THAT(delete_variable(NAME2), ::testing::IsNan());
  delete_variable(NAME1);
}
