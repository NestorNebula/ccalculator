#include <gtest/gtest.h>
#include <gmock/gmock.h>

extern "C" {
  #include <stdlib.h>
  #include "error.h"
}

TEST(set_error, returns_pointer_to_error_description) {
  EXPECT_STREQ("Error", set_error("Error"));
}

TEST(clear_error, returns_pointer_to_empty_description) {
  EXPECT_STREQ("", clear_error());
}

TEST(has_error, returns_false_when_error_status_is_inactive) {
  clear_error();
  EXPECT_FALSE(has_error());
}

TEST(has_error, returns_true_when_error_status_is_active) {
  set_error("Error");
  EXPECT_TRUE(has_error());
}

TEST(print_error, prints_error_description_in_stream) {
  FILE *stream = tmpfile();
  char err[] = "Error";
  char err_cpy[sizeof(err)];
  set_error(err);

  print_error(stream);
  rewind(stream);
  fgets(err_cpy, sizeof(err_cpy), stream);
  EXPECT_STREQ(err, err_cpy);
}

TEST(exit_with_error, prints_error_description_in_stream) {
  FILE *stream = tmpfile();
  char err[] = "Error";
  char err_cpy[sizeof(err)];

  EXPECT_EXIT(exit_with_error(err, stream),
              ::testing::ExitedWithCode(EXIT_FAILURE), "");
  rewind(stream);
  fgets(err_cpy, sizeof(err_cpy), stream);
  EXPECT_STREQ(err, err_cpy);
}
