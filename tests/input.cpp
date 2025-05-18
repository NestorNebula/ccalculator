#include <gtest/gtest.h>
#include <gmock/gmock.h>

extern "C" {
  #include <stdio.h>
  #include <string.h>
  #include "input.h"
}

TEST(new_input, returns_pointer_to_new_input) {
  Input ip = new_input();
  EXPECT_THAT(ip, ::testing::NotNull());
  delete_input(ip);
}

TEST(read_input, returns_number_of_characters_read) {
  FILE *stream = tmpfile();
  char test_str[] = "Test string";
  fputs(test_str, stream);
  rewind(stream);

  Input ip = new_input();
  EXPECT_EQ(read_input(ip, stream), strlen(test_str));
  delete_input(ip);
}

TEST(get_next_number, returns_next_number) {
  FILE *stream = tmpfile();
  char test_str[] = "1 23 456";
  fputs(test_str, stream);
  rewind(stream);

  Input ip = new_input();
  read_input(ip, stream);
  EXPECT_EQ(get_next_number(ip), 1);
  EXPECT_EQ(get_next_number(ip), 23);
  EXPECT_EQ(get_next_number(ip), 456);
  delete_input(ip);
}

TEST(get_next_number, returns_nan_if_no_number) {
  FILE *stream = tmpfile();
  char test_str[] = "Test 123";
  fputs(test_str, stream);
  rewind(stream);

  Input ip = new_input();
  read_input(ip, stream);
  EXPECT_THAT(get_next_number(ip), ::testing::IsNan());
  delete_input(ip);
}

TEST(get_next_char, returns_next_char) {
  FILE *stream = tmpfile();
  char test_str[] =  "Test";
  fputs(test_str, stream);
  rewind(stream);

  Input ip = new_input();
  read_input(ip, stream);
  EXPECT_EQ(get_next_char(ip), 'T');
  EXPECT_EQ(get_next_char(ip), 'e');
  EXPECT_EQ(get_next_char(ip), 's');
  EXPECT_EQ(get_next_char(ip), 't');
  delete_input(ip);
}

TEST(get_next_char, returns_weof_if_no_character_found) {
  FILE *stream = tmpfile();

  Input ip = new_input();
  read_input(ip, stream);
  EXPECT_EQ(get_next_char(ip), WEOF);
  delete_input(ip);
}

TEST(end_of_input, returns_false_while_input_not_fully_read) {
  FILE *stream = tmpfile();
  char test_str[] = "Test";
  fputs(test_str, stream);
  rewind(stream);

  Input ip = new_input();
  read_input(ip, stream);
  get_next_char(ip);
  EXPECT_THAT(end_of_input(ip), ::testing::IsFalse());
  delete_input(ip);
}

TEST(end_of_input, returns_true_when_input_fully_read) {
  FILE *stream = tmpfile();
  char test_str[] = "123f";
  fputs(test_str, stream);
  rewind(stream);

  Input ip = new_input();
  read_input(ip, stream);
  get_next_number(ip);
  get_next_char(ip);
  EXPECT_THAT(end_of_input(ip), ::testing::IsTrue());
  delete_input(ip);
}
