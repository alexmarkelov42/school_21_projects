#include <string.h>
#include <wchar.h>

#include "s21_string.h"

#test strncmp
char *test1 = "1234567890";
char *test2 = "1234567890";
ck_assert_msg(s21_strncmp(test1, test2, 12), strncmp(test1, test2, 12));
char *test1 = "1236567890";
char *test2 = "1234567890";
ck_assert_msg(s21_strncmp(test1, test2, 12), strncmp(test1, test2, 12));
char *test1 = "1234567890";
char *test2 = "1234567890";
ck_assert_msg(s21_strncmp(test1, test2, 4), strncmp(test1, test2, 4));
ck_assert_msg(s21_strncmp(test1, test2, 3), strncmp(test1, test2, 3));
ck_assert_msg(s21_strncmp(test1, test2, 3), strncmp(test1, test2, 3));
ck_assert_msg(s21_strncmp(test1, test2, 2), strncmp(test1, test2, 2));
ck_assert_msg(s21_strncmp(test1, test2, 2), strncmp(test1, test2 2));


# checkmk clean_mode = 1 teststrcmp.c > testtest.c
