#include "s21_string.h"
#include <check.h>
#include <stdio.h>
#include <string.h>

START_TEST(STRLENTest1) {
  char str[] = "Hello";
  ck_assert_msg(s21_strlen(str) == strlen(str), "Failed on 5");
}
END_TEST

START_TEST(STRLENTest2) {
  char str[] = "Hegd    llo";
  ck_assert_msg(s21_strlen(str) == strlen(str), "Failed on 11");
}
END_TEST

START_TEST(STRLENTest3) {
  char str[] = "";
  ck_assert_msg(s21_strlen(str) == strlen(str), "Failed on 0");
}
END_TEST

START_TEST(STRLENTest4) {
  char str[] = "lorem\\tipsum\\tdolor\\nsit\\namet\\n";
  ck_assert_msg(s21_strlen(str) == strlen(str), "Failed on 32");
}
END_TEST
START_TEST(STRLENTest5) {
  char str[] = "\n\n\f\r\t";
  ck_assert_msg(s21_strlen(str) == strlen(str), "Failed on 5");
}
END_TEST
START_TEST(STRLENTest6) {
  char str[] = "     ";
  ck_assert_msg(s21_strlen(str) == strlen(str), "Failed on 5");
}
END_TEST

// MARK: - STRCHR 6

START_TEST(STRCHRTest1) {
  char str[] = "Hello world";
  int ch = 'w';
  ck_assert_str_eq(s21_strchr(str, ch), strchr(str, ch));
}
END_TEST

START_TEST(STRCHRTest2) {
  char str[] = "Hello world";
  int ch = 'o';
  ck_assert_str_eq(s21_strchr(str, ch), strchr(str, ch));
}
END_TEST

START_TEST(STRCHRTest3) {
  char str[] = "Hello world";
  int ch = 'c';
  ck_assert_ptr_eq(s21_strchr(str, ch), strchr(str, ch));
}
END_TEST

START_TEST(STRCHRTest4) {
  char str[] = "Hello world";
  int ch = 'H';
  ck_assert_str_eq(s21_strchr(str, ch), strchr(str, ch));
}
END_TEST

START_TEST(STRCHRTest5) {
  char str[] = "Hello world";
  int ch = '\0';
  ck_assert_str_eq(s21_strchr(str, ch), strchr(str, ch));
}
END_TEST

START_TEST(STRCHRTest6) {
  char str[] = "";
  int ch = '\0';
  ck_assert_str_eq(s21_strchr(str, ch), strchr(str, ch));
}
END_TEST

// MARK:- STRSPN 8

START_TEST(STRSPNTest1) {
  char *str1 = "12345";
  char *str2 = "123";
  ck_assert_msg(s21_strspn(str1, str2) == strspn(str1, str2), "Failed on 3");
}
END_TEST

START_TEST(STRSPNTest2) {
  char *str1 = "12345";
  char *str2 = "12sd34";
  ck_assert_msg(s21_strspn(str1, str2) == strspn(str1, str2), "Failed on 4");
}
END_TEST

START_TEST(STRSPNTest3) {
  char *str1 = "12345";
  char *str2 = "12sdf4";
  ck_assert_msg(s21_strspn(str1, str2) == strspn(str1, str2), "Failed on 2");
}
END_TEST

START_TEST(STRSPNTest4) {
  char *str1 = "12345";
  char *str2 = "kbf";
  ck_assert_msg(s21_strspn(str1, str2) == strspn(str1, str2), "Failed on 0");
}
END_TEST

START_TEST(STRSPNTest5) {
  char *str1 = "12345";
  char *str2 = "54321";
  ck_assert_msg(s21_strspn(str1, str2) == strspn(str1, str2), "Failed on 5");
}
END_TEST

START_TEST(STRSPNTest6) {
  char *str1 = "12345";
  char *str2 = "5qw4w3qwe2qweqw1";
  ck_assert_msg(s21_strspn(str1, str2) == strspn(str1, str2), "Failed on 5");
}
END_TEST

START_TEST(STRSPNTest7) {
  char *str1 = "12345";
  char *str2 = " ";
  ck_assert_msg(s21_strspn(str1, str2) == strspn(str1, str2), "Failed on 0");
}
END_TEST

START_TEST(STRSPNTest8) {
  char *str1 = "12345";
  char *str2 = " 1";
  ck_assert_msg(s21_strspn(str1, str2) == strspn(str1, str2), "Failed on 1");
}
END_TEST

// MARK: - STRCSPN 6

START_TEST(STRCSPNTest1) {
  char *src = "0123456789";
  char *str = "54";
  ck_assert_msg(s21_strcspn(src, str) == strcspn(src, str), "Failed on 4");
}
END_TEST

START_TEST(STRCSPNTest2) {
  char *src = "0123456789";
  char *str = "e";
  ck_assert_msg(s21_strcspn(src, str) == strcspn(src, str), "Failed on 0");
}
END_TEST

START_TEST(STRCSPNTest3) {
  char *src = "46";
  char *str = "123";
  ck_assert_msg(s21_strcspn(src, str) == strcspn(src, str), "Failed on 2");
}
END_TEST

START_TEST(STRCSPNTest4) {
  char *src = "HELLO";
  char *str = "HELLO";
  ck_assert_msg(s21_strcspn(src, str) == strcspn(src, str), "Failed on 0");
}
END_TEST

START_TEST(STRCSPNTest5) {
  char *src = "";
  char *str = "hi";
  ck_assert_msg(s21_strcspn(src, str) == strcspn(src, str), "Failed on 0");
}
END_TEST
START_TEST(STRCSPNTest6) {
  char *src = "\0";
  char *str = "\0";
  ck_assert_msg(s21_strcspn(src, str) == strcspn(src, str), "Failed on 0");
}
END_TEST

// MARK:- MEMCPY 5

START_TEST(MEMCPYTest1) {
  char *src = "HELLO WORLD";
  char dest[15];
  char dest2[15];
  ck_assert_mem_eq(s21_memcpy(dest, src, 11), memcpy(dest2, src, 11), 11);
}
END_TEST

START_TEST(MEMCPYTest2) {
  char *src = "HELLO";
  char dest[5];
  char dest2[5];
  ck_assert_mem_eq(s21_memcpy(dest, src, 5), memcpy(dest2, src, 5), 5);
}
END_TEST

START_TEST(MEMCPYTest3) {
  char *src = "HELLO";
  char dest[5];
  char dest2[5];
  ck_assert_mem_eq(s21_memcpy(dest, src, 5), memcpy(dest2, src, 5), 0);
}
END_TEST

START_TEST(MEMCPYTest4) {
  char *src = "zy\0xw";
  char dest[5];
  char dest2[5];
  ck_assert_mem_eq(s21_memcpy(dest, src, 5), memcpy(dest2, src, 5), 0);
}
END_TEST
START_TEST(MEMCPYTest5) {
  char *src = "zy\0xw";
  char dest[5];
  char dest2[5];
  ck_assert_mem_eq(s21_memcpy(dest, src, 5), memcpy(dest2, src, 5), 0);
}
END_TEST
// MARK:- STRCAT 5
START_TEST(STRCATTest1) {
  char app[1024] = "вторая строка ";
  char dst[1024] = "первая строка ";
  ck_assert_str_eq(s21_strcat(dst, app), strcat(dst, app));
}
END_TEST

START_TEST(STRCATTest2) {
  char app[1024] = " ";
  char dst[1024] = "   ";
  ck_assert_str_eq(s21_strcat(dst, app), strcat(dst, app));
}
END_TEST

START_TEST(STRCATTest3) {
  char app[1024] = "s s d";
  char dst[1024] = " s  s  s  sd aff   ";
  ck_assert_str_eq(s21_strcat(dst, app), strcat(dst, app));
}
END_TEST

START_TEST(STRCATTest4) {
  char app[1024] = "sdddadasdsa";
  char dst[1024] = "s                              ";
  ck_assert_str_eq(s21_strcat(dst, app), strcat(dst, app));
}
END_TEST

START_TEST(STRCATTest5) {
  char app[1024] = "\0";
  char dst[1024] = "\n\0";
  ck_assert_str_eq(s21_strcat(dst, app), strcat(dst, app));
}
END_TEST

// MARK: MEMCMP 10
START_TEST(MEMCMPTest1) {
  char str1[] = "Hello";
  char str2[] = "Hello";
  int n = 6;
  ck_assert_int_eq(s21_memcmp(str1, str2, n), memcmp(str1, str2, n));
}
END_TEST
START_TEST(MEMCMPTest2) {
  char str1[] = "Hello";
  char str2[] = "Help";
  int n = 4;
  ck_assert_int_eq(s21_memcmp(str1, str2, n), memcmp(str1, str2, n));
}
END_TEST
START_TEST(MEMCMPTest3) {
  char str1[] = "Help";
  char str2[] = "Hello";
  int n = 4;
  ck_assert_int_eq(s21_memcmp(str1, str2, n), memcmp(str1, str2, n));
}
END_TEST
START_TEST(MEMCMPTest4) {
  char str1[] = "Help";
  char str2[] = "Hello";
  int n = 3;
  ck_assert_int_eq(s21_memcmp(str1, str2, n), memcmp(str1, str2, n));
}
END_TEST
START_TEST(MEMCMPTest5) {
  char str1[6] = "Hello";
  char str2[6] = "";
  int n = 4;
  ck_assert_int_eq(s21_memcmp(str1, str2, n), memcmp(str1, str2, n));
}
END_TEST
START_TEST(MEMCMPTest6) {
  char str1[4] = "";
  char str2[4] = "";
  int n = 4;
  ck_assert_int_eq(s21_memcmp(str1, str2, n), memcmp(str1, str2, n));
}
END_TEST
START_TEST(MEMCMPTest7) {
  char str1[] = "gsafh";
  char str2[] = "dhkjfhs";
  int n = 0;
  ck_assert_int_eq(s21_memcmp(str1, str2, n), memcmp(str1, str2, n));
}
END_TEST
//  START_TEST(MEMCMPTest8) {
//      char str1[] = "test\0test";
//      char str2[] = "test";
//      int n = 10;
//      ck_assert_int_eq(s21_memcmp(str1, str2, n), memcmp(str1, str2, n));
//  }
//  END_TEST
START_TEST(MEMCMPTest9) {
  char str1[] = "test";
  char str2[] = "teSt";
  int n = 4;
  ck_assert_int_eq(s21_memcmp(str1, str2, n), memcmp(str1, str2, n));
}
END_TEST
START_TEST(MEMCMPTest10) {
  char str1[] = "t\200";
  char str2[] = "t\0";
  int n = 2;
  ck_assert_int_eq(s21_memcmp(str1, str2, n), memcmp(str1, str2, n));
}
END_TEST

// MARK: STRNCAT 5
START_TEST(STRNCATTest1) {
  char str1[1024] = "Hello";
  char str2[] = " World";
  int n = 6;
  ck_assert_str_eq(s21_strncat(str1, str2, n), strncat(str1, str2, n));
}
END_TEST
START_TEST(STRNCATTest2) {
  char str1[1024] = "Hello";
  char str2[] = " World";
  int n = 4;
  ck_assert_str_eq(s21_strncat(str1, str2, n), strncat(str1, str2, n));
}
END_TEST
START_TEST(STRNCATTest3) {
  char str1[1024] = "";
  char str2[] = " HELLO";
  int n = 5;
  ck_assert_str_eq(s21_strncat(str1, str2, n), strncat(str1, str2, n));
}
END_TEST
START_TEST(STRNCATTest4) {
  char str1[1024] = "HI, ";
  char str2[] = "HELL\0O";
  int n = 5;
  ck_assert_str_eq(s21_strncat(str1, str2, n), strncat(str1, str2, n));
}
END_TEST
START_TEST(STRNCATTest5) {
  char str1[1024] = "\0";
  char str2[] = "H";
  int n = 5;
  ck_assert_str_eq(s21_strncat(str1, str2, n), strncat(str1, str2, n));
}
END_TEST

// MARK: STRNCPY 5

START_TEST(STRNCPYTest1) {
  char str1[1024] = "Hello";
  char str2[] = " World";
  int n = 6;
  ck_assert_str_eq(s21_strncpy(str1, str2, n), strncpy(str1, str2, n));
}
END_TEST
START_TEST(STRNCPYTest2) {
  char str1[1024] = "Hello";
  char str2[] = " World";
  int n = 4;
  ck_assert_str_eq(s21_strncpy(str1, str2, n), strncpy(str1, str2, n));
}
END_TEST
START_TEST(STRNCPYTest3) {
  char str1[1024] = "";
  char str2[] = " HELLO";
  int n = 5;
  ck_assert_str_eq(s21_strncpy(str1, str2, n), strncpy(str1, str2, n));
}
END_TEST
START_TEST(STRNCPYTest4) {
  char str1[1024] = "HI, ";
  char str2[] = " HELL\0O";
  int n = 5;
  ck_assert_str_eq(s21_strncpy(str1, str2, n), strncpy(str1, str2, n));
}
END_TEST
START_TEST(STRNCPYTest5) {
  char str1[1024] = "HI, ";
  char str2[] = " HELLO";
  int n = 20;
  ck_assert_str_eq(s21_strncpy(str1, str2, n), strncpy(str1, str2, n));
}
END_TEST

// MARK: - STRRCHR 5
START_TEST(STRRCHRTest1) {
  char str1[] = "Hello, Mel";
  int c = 'e';
  ck_assert_ptr_eq(s21_strrchr(str1, c), strrchr(str1, c));
}
END_TEST
START_TEST(STRRCHRTest2) {
  char str1[] = "Hello, Mel";
  int c = 'p';
  ck_assert_ptr_eq(s21_strrchr(str1, c), strrchr(str1, c));
}
END_TEST
START_TEST(STRRCHRTest3) {
  char str1[] = "";
  int c = 'l';
  ck_assert_ptr_eq(s21_strrchr(str1, c), strrchr(str1, c));
}
END_TEST
START_TEST(STRRCHRTest4) {
  char str1[] = "Hello";
  int c = 0;
  ck_assert_ptr_eq(s21_strrchr(str1, c), strrchr(str1, c));
}
END_TEST
START_TEST(STRRCHRTest5) {
  char str1[] = "Hello";
  int c = 'o';
  ck_assert_ptr_eq(s21_strrchr(str1, c), strrchr(str1, c));
}
END_TEST

// MARK:MEMMOVE 4

START_TEST(MEMMOVETest1) {
  char dest1[10] = "fd";
  char dest2[10] = "fd";
  char src[5] = "hello";
  ck_assert_mem_eq(s21_memmove(dest1 + 2, src + 2, 3),
                   memmove(dest2, src + 2, 3), 5);
}
END_TEST

START_TEST(MEMMOVETest2) {
  char dest1[10] = "fd";
  char dest2[10] = "fd";
  char src[5] = "hello";
  ck_assert_mem_eq(s21_memmove(dest1, src, 0), memmove(dest2, src, 0), 0);
}
END_TEST

//  START_TEST(MEMMOVETest3) {
//      char dest1[10] = "fd";
//      char dest2[10] = "fd";
//      char src[5] = "hello";
//      ck_assert_mem_eq(s21_memmove(dest1, src, 10), memmove(dest2, src, 10),
//      0);
//  }
//  END_TEST
//  START_TEST(MEMMOVETest4) {
//      char dest1[10] = "";
//      char dest2[10] = "";
//      char src[5] = "so\0";
//      ck_assert_mem_eq(s21_memmove(dest1, src, 10), memmove(dest2, src, 10),
//      0);
//  }
//  END_TEST

// MARK:STRSTR 5

START_TEST(STRSTRTest1) {
  char str1[10] = "hello";
  char str2[10] = "he";
  ck_assert_msg(s21_strstr(str1, str2) == strstr(str1, str2), "failed");
}
END_TEST

START_TEST(STRSTRTest2) {
  char str1[10] = "hello";
  char str2[10] = "";
  ck_assert_msg(s21_strstr(str1, str2) == strstr(str1, str2), "failed");
}
END_TEST

START_TEST(STRSTRTest3) {
  char str1[10] = "hello";
  char str2[10] = "qw";
  ck_assert_msg(s21_strstr(str1, str2) == strstr(str1, str2), "failed");
}
END_TEST

START_TEST(STRSTRTest4) {
  char str1[10] = "hello";
  char str2[10] = "hellp";
  ck_assert_msg(s21_strstr(str1, str2) == strstr(str1, str2), "failed");
}
END_TEST

START_TEST(STRSTRTest5) {
  char str1[1024] = "hello sweet hello";
  char str2[10] = "hello";
  ck_assert_msg(s21_strstr(str1, str2) == strstr(str1, str2), "failed");
}
END_TEST

// MARK: STRCMP 6

START_TEST(STRCMPTest1) {
  char str1[10] = "hello";
  char str2[10] = "hello";
  ck_assert_msg(s21_strcmp(str1, str2) == strcmp(str1, str2), "failed");
}
END_TEST

START_TEST(STRCMPTest2) {
  char str1[10] = "hello";
  char str2[10] = "hellq";
  ck_assert_msg(s21_strcmp(str1, str2) == strcmp(str1, str2), "failed");
}
END_TEST

START_TEST(STRCMPTest3) {
  char str1[10] = "hello";
  char str2[10] = "helle";
  ck_assert_msg(s21_strcmp(str1, str2) == strcmp(str1, str2), "failed");
}
END_TEST

START_TEST(STRCMPTest4) {
  char str1[10] = "hello";
  char str2[10] = "";
  ck_assert_msg(s21_strcmp(str1, str2) == strcmp(str1, str2), "failed");
}
END_TEST

START_TEST(STRCMPTest5) {
  char str1[10] = "";
  char str2[10] = "hello";
  ck_assert_msg(s21_strcmp(str1, str2) == strcmp(str1, str2), "failed");
}
END_TEST

START_TEST(STRCMPTest6) {
  char str1[10] = "";
  char str2[10] = "";
  ck_assert_msg(s21_strcmp(str1, str2) == strcmp(str1, str2), "failed");
}
END_TEST

// MARK: - MEMCHR 5

START_TEST(MEMCHRTest1) {
  char str1[10] = "Hello";
  ck_assert_mem_eq(s21_memchr(str1, 'H', 5), memchr(str1, 'H', 5), 5);
}
END_TEST

START_TEST(MEMCHRTest2) {
  char str1[10] = "Hello";
  ck_assert_msg(s21_memchr(str1, 'h', 5) == NULL, "Failed: Str == NULL");
}
END_TEST

START_TEST(MEMCHRTest3) {
  char str1[10] = "Hellosdsfq";
  ck_assert_msg(s21_memchr(str1, 'h', 5) == NULL, "Failed: Str == NULL");
}
END_TEST

START_TEST(MEMCHRTest4) {
  char str1[10] = "Hellosdsfq";
  ck_assert_mem_eq(s21_memchr(str1, 'l', 5), memchr(str1, 'l', 5), 3);
}
END_TEST

START_TEST(MEMCHRTest5) {
  char str1[10] = "Hellosdsfq";
  ck_assert_mem_eq(s21_memchr(str1, 'l', 0), memchr(str1, 'l', 0), 0);
}
END_TEST

START_TEST(MEMCHRTest6) {
  char str1[10] = "lol";
  ck_assert_mem_eq(s21_memchr(str1, '\0', 4), memchr(str1, '\0', 4), 4);
}
END_TEST

// MARK: - STRCPY 4

START_TEST(STRCPYTest1) {
  char str[] = "Hello";
  char str1[15] = "";
  char str2[15] = "";
  s21_strcpy(str, str1);
  strcpy(str, str2);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(STRCPYTest2) {
  char str[] = "";
  char str1[15] = "";
  char str2[15] = "";
  s21_strcpy(str1, str);
  strcpy(str2, str);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(STRCPYTest3) {
  char str[15] = "";
  char str1[15] = "test";
  char str2[15] = "test";
  s21_strcpy(str1, str);
  strcpy(str2, str);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(STRCPYTest4) {
  char str[] = "Test";
  char str1[1024] = "";
  char str2[1024] = "";
  s21_strcpy(str, str1);
  strcpy(str, str2);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(STRCPYTest5) {
  char str[] = "Test";
  char str1[1024] = "Test";
  char str2[1024] = "Test";
  s21_strcpy(str, str1);
  strcpy(str, str2);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(STRCPYTest6) {
  char str[] = "lolkek";
  char str1[1024] = "Test";
  char str2[1024] = "Test";
  s21_strcpy(str, str1);
  strcpy(str, str2);
  ck_assert_str_eq(str1, str2);
}
END_TEST

// MARK: - STRPBRK 4

START_TEST(STRPBRKTest1) {
  char *str = "this is a test";
  char *str1 = "this is a test";
  str1 = strpbrk(str1, "this");
  str = s21_strpbrk(str, "this");
  ck_assert_str_eq(str, str1);
}
END_TEST

START_TEST(STRPBRKTest2) {
  char *str = "this is a test";
  char *str1 = "this is a test";
  str1 = strpbrk(str1, " ");
  str = s21_strpbrk(str, " ");
  ck_assert_str_eq(str, str1);
}
END_TEST

START_TEST(STRPBRKTest3) {
  char *str = "this is a test, this is ...";
  char *str1 = "this is a test, this is ...";
  str1 = strpbrk(str1, "this");
  str = s21_strpbrk(str, "this");
  ck_assert_str_eq(str, str1);
}
END_TEST

START_TEST(STRPBRKTest4) {
  char *str = "this is a test, this is ...";
  char *str1 = "this is a test, this is ...";
  ck_assert_ptr_eq(s21_strpbrk(str, "prom"), strpbrk(str1, "prom"));
}
END_TEST

// MARK: - STRNCMP 8

START_TEST(STRNCMPTest1) {
  char *str1 = "1234567890";
  char *str2 = "1234567890";
  ck_assert_msg(s21_strncmp(str1, str2, 5) == strncmp(str1, str2, 5),
                "Failed on 1");
}
END_TEST

START_TEST(STRNCMPTest2) {
  char *str1 = "1234567890";
  char *str2 = "1224567890";
  ck_assert_msg(s21_strncmp(str1, str2, 5) == strncmp(str1, str2, 5),
                "Failed on 2");
}
END_TEST

START_TEST(STRNCMPTest3) {
  char *str1 = "1224567890";
  char *str2 = "1234567890";
  ck_assert_msg(s21_strncmp(str1, str2, 5) == strncmp(str1, str2, 5),
                "Failed on 3");
}
END_TEST

START_TEST(STRNCMPTest4) {
  char *str1 = "";
  char *str2 = "";
  ck_assert_msg(s21_strncmp(str1, str2, 5) == strncmp(str1, str2, 5),
                "Failed on 4");
}
END_TEST

START_TEST(STRNCMPTest5) {
  char *str1 = "1224567890";
  char *str2 = "";
  ck_assert_msg(s21_strncmp(str1, str2, 5) == strncmp(str1, str2, 5),
                "Failed on 5");
}
END_TEST

START_TEST(STRNCMPTest6) {
  char *str1 = "122";
  char *str2 = "345";
  ck_assert_msg(s21_strncmp(str1, str2, 5) == strncmp(str1, str2, 5),
                "Failed on 6");
}
END_TEST

START_TEST(STRNCMPTest7) {
  char *str1 = "test\0abc";
  char *str2 = "test\0";
  ck_assert_msg(s21_strncmp(str1, str2, 6) == strncmp(str1, str2, 6),
                "Failed on 7");
}
END_TEST
START_TEST(STRNCMPTest8) {
  char *str1 = "1224567890";
  char *str2 = "02";
  ck_assert_msg(s21_strncmp(str1, str2, 0) == strncmp(str1, str2, 0),
                "Failed on 8");
}
END_TEST

// MARK: - MEMSET 7

START_TEST(MEMSETTest1) {
  char str1[15] = "1234567890";
  char str2[15] = "1234567890";
  int c = '1';
  int n = 10;
  s21_memset(str1, c, n);
  memset(str2, c, n);
  ck_assert_mem_eq(str1, str2, 10);
}
END_TEST

START_TEST(MEMSETTest2) {
  char str1[15] = "1234567890";
  char str2[15] = "5432167890";
  int c = '1';
  int n = 10;
  s21_memset(str1, c, n);
  memset(str2, c, n);
  ck_assert_mem_eq(str1, str2, 10);
}
END_TEST

START_TEST(MEMSETTest3) {
  char str1[15] = "1234567890";
  char str2[15] = "5432167890";
  int c = 'q';
  int n = 10;
  s21_memset(str1, c, n);
  memset(str2, c, n);
  ck_assert_mem_eq(str1, str2, 10);
}
END_TEST

START_TEST(MEMSETTest4) {
  char str1[15] = "1234567890";
  char str2[15] = "5432167890";
  int c = '1';
  int n = 5;
  s21_memset(str1, c, n);
  memset(str2, c, n);
  ck_assert_mem_eq(str1, str2, 5);
}
END_TEST

START_TEST(MEMSETTest5) {
  char str1[15] = "qweqweqweqwe";
  char str2[15] = "ewqewqewqewq";
  int c = '1';
  int n = 10;
  s21_memset(str1, c, n);
  memset(str2, c, n);
  ck_assert_mem_eq(str1, str2, 10);
}
END_TEST

START_TEST(MEMSETTest6) {
  char str1[15] = "qweqweqweqwe";
  char str2[15] = "qweqweqweqwe";
  int c = '\0';
  int n = 5;
  s21_memset(str1, c, n);
  memset(str2, c, n);
  ck_assert_mem_eq(str1, str2, 10);
}
END_TEST

START_TEST(MEMSETTest7) {
  char str1[15] = "qweqweqweqwe";
  char str2[15] = "qweqweqweqwe";
  int c = '\n';
  int n = 5;
  s21_memset(str1, c, n);
  memset(str2, c, n);
  ck_assert_mem_eq(str1, str2, 10);
}
END_TEST

// MARK: -STRTOK 6

START_TEST(STRTOKTest1) {
  char str[30] = "test1/test2/test3/test4";
  char st2[30] = "test1/test2/test3/test4";
  char *delim = "/";
  ck_assert_pstr_eq(NULL, NULL);
  ck_assert_pstr_eq(s21_strtok(str, delim), strtok(st2, delim));
  ck_assert_pstr_eq(s21_strtok(NULL, delim), strtok(NULL, delim));
  ck_assert_pstr_eq(s21_strtok(NULL, delim), strtok(NULL, delim));
  ck_assert_pstr_eq(s21_strtok(NULL, delim), strtok(NULL, delim));
  ck_assert_pstr_eq(s21_strtok(NULL, delim), strtok(NULL, delim));
  ck_assert_pstr_eq(s21_strtok(NULL, delim), strtok(NULL, delim));
  ck_assert_pstr_eq(s21_strtok(NULL, delim), strtok(NULL, delim));
  ck_assert_pstr_eq(s21_strtok(NULL, delim), strtok(NULL, delim));
}
END_TEST

START_TEST(STRTOKTest2) {
  char str[30] = "test1/test2/test3/test4";
  char st2[30] = "test1/test2/test3/test4";
  char *delim = ",";
  ck_assert_pstr_eq(s21_strtok(str, delim), strtok(st2, delim));
  ck_assert_pstr_eq(s21_strtok(NULL, delim), strtok(NULL, delim));
  ck_assert_pstr_eq(s21_strtok(NULL, delim), strtok(NULL, delim));
  ck_assert_pstr_eq(s21_strtok(NULL, delim), strtok(NULL, delim));
  ck_assert_pstr_eq(s21_strtok(NULL, delim), strtok(NULL, delim));
  ck_assert_pstr_eq(s21_strtok(NULL, delim), strtok(NULL, delim));
  ck_assert_pstr_eq(s21_strtok(NULL, delim), strtok(NULL, delim));
  ck_assert_pstr_eq(s21_strtok(NULL, delim), strtok(NULL, delim));
}
END_TEST

START_TEST(STRTOKTest3) {
  char str[30] = "test1/test2/test3/test4";
  char st2[30] = "test1/test2/test3/test4";
  char *delim = "e";
  ck_assert_pstr_eq(s21_strtok(str, delim), strtok(st2, delim));
  ck_assert_pstr_eq(s21_strtok(NULL, delim), strtok(NULL, delim));
  ck_assert_pstr_eq(s21_strtok(NULL, delim), strtok(NULL, delim));
  ck_assert_pstr_eq(s21_strtok(NULL, delim), strtok(NULL, delim));
  ck_assert_pstr_eq(s21_strtok(NULL, delim), strtok(NULL, delim));
  ck_assert_pstr_eq(s21_strtok(NULL, delim), strtok(NULL, delim));
  ck_assert_pstr_eq(s21_strtok(NULL, delim), strtok(NULL, delim));
  ck_assert_pstr_eq(s21_strtok(NULL, delim), strtok(NULL, delim));
}
END_TEST

START_TEST(STRTOKTest4) {
  char str[30] = "AadacAdxa";
  char st2[30] = "AadacAdxa";
  char *delim = "a";
  ck_assert_pstr_eq(s21_strtok(str, delim), strtok(st2, delim));
  ck_assert_pstr_eq(s21_strtok(NULL, delim), strtok(NULL, delim));
  ck_assert_pstr_eq(s21_strtok(NULL, delim), strtok(NULL, delim));
  ck_assert_pstr_eq(s21_strtok(NULL, delim), strtok(NULL, delim));
  ck_assert_pstr_eq(s21_strtok(NULL, delim), strtok(NULL, delim));
  ck_assert_pstr_eq(s21_strtok(NULL, delim), strtok(NULL, delim));
  ck_assert_pstr_eq(s21_strtok(NULL, delim), strtok(NULL, delim));
  ck_assert_pstr_eq(s21_strtok(NULL, delim), strtok(NULL, delim));
}
END_TEST

START_TEST(STRTOKTest5) {
  char str[30] = "ased dse c sze wsew";
  char st2[30] = "ased dse c sze wsew";
  char *delim = "e";
  ck_assert_pstr_eq(s21_strtok(str, delim), strtok(st2, delim));
  ck_assert_pstr_eq(s21_strtok(NULL, delim), strtok(NULL, delim));
  ck_assert_pstr_eq(s21_strtok(NULL, delim), strtok(NULL, delim));
  ck_assert_pstr_eq(s21_strtok(NULL, delim), strtok(NULL, delim));
  ck_assert_pstr_eq(s21_strtok(NULL, delim), strtok(NULL, delim));
  ck_assert_pstr_eq(s21_strtok(NULL, delim), strtok(NULL, delim));
  ck_assert_pstr_eq(s21_strtok(NULL, delim), strtok(NULL, delim));
  ck_assert_pstr_eq(s21_strtok(NULL, delim), strtok(NULL, delim));
}
END_TEST

START_TEST(STRTOKTest6) {
  char str[30] = "test1,test2/test3.test4";
  char st2[30] = "test1,test2/test3.test4";
  char delim[] = ",/.";
  ck_assert_pstr_eq(s21_strtok(str, delim), strtok(st2, delim));
  ck_assert_pstr_eq(s21_strtok(NULL, delim), strtok(NULL, delim));
  ck_assert_pstr_eq(s21_strtok(NULL, delim), strtok(NULL, delim));
  ck_assert_pstr_eq(s21_strtok(NULL, delim), strtok(NULL, delim));
  ck_assert_pstr_eq(s21_strtok(NULL, delim), strtok(NULL, delim));
  ck_assert_pstr_eq(s21_strtok(NULL, delim), strtok(NULL, delim));
  ck_assert_pstr_eq(s21_strtok(NULL, delim), strtok(NULL, delim));
  ck_assert_pstr_eq(s21_strtok(NULL, delim), strtok(NULL, delim));
}
END_TEST
START_TEST(STRTOKTest7) {
  char str[30] = "test1/test2/test3/test4";
  char st2[30] = "test1/test2/test3/test4";
  char delim[] = ",/.";
  ck_assert_pstr_eq(s21_strtok(str, delim), strtok(st2, delim));
  ck_assert_pstr_eq(s21_strtok(NULL, delim), strtok(NULL, delim));
  ck_assert_pstr_eq(s21_strtok(NULL, delim), strtok(NULL, delim));
  ck_assert_pstr_eq(s21_strtok(NULL, delim), strtok(NULL, delim));
  ck_assert_pstr_eq(s21_strtok(NULL, delim), strtok(NULL, delim));
  ck_assert_pstr_eq(s21_strtok(NULL, delim), strtok(NULL, delim));
  ck_assert_pstr_eq(s21_strtok(NULL, delim), strtok(NULL, delim));
  ck_assert_pstr_eq(s21_strtok(NULL, delim), strtok(NULL, delim));
}
END_TEST
START_TEST(STRTOKTest8) {
  char str[10] = "AadacAdxa";
  char s21_str[10] = "AadacAdxa";
  char delim[2] = "a";
  char *part = strtok(str, delim);
  char *s21_part = s21_strtok(s21_str, delim);
  ck_assert_str_eq(part, s21_part);
  while (part != NULL) {
    part = strtok(NULL, delim);
    s21_part = s21_strtok(NULL, delim);
    if (part != NULL) {
      ck_assert_str_eq(part, s21_part);
    } else {
      ck_assert_ptr_null(s21_part);
    }
  }
}
END_TEST
START_TEST(STRTOKTest9) {
  char str[30] = "test1/test2/test3/test4";
  char s21_str[30] = "test1/test2/test3/test4";
  char delim[2] = "/";
  char *part = strtok(str, delim);
  char *s21_part = s21_strtok(s21_str, delim);
  ck_assert_str_eq(part, s21_part);
  while (part != NULL) {
    part = strtok(NULL, delim);
    s21_part = s21_strtok(NULL, delim);
    if (part != NULL) {
      ck_assert_str_eq(part, s21_part);
    } else {
      ck_assert_ptr_null(s21_part);
    }
  }
}
END_TEST

START_TEST(STRTOKTest10) {
  char str[15] = "12|34*56|78m90";
  char s21_str[15] = "12|34*56|78m90";
  char delim[4] = "*m|";
  char *part = strtok(str, delim);
  char *s21_part = s21_strtok(s21_str, delim);
  ck_assert_str_eq(part, s21_part);
  while (part != NULL) {
    part = strtok(NULL, delim);
    s21_part = s21_strtok(NULL, delim);
    if (part != NULL) {
      ck_assert_str_eq(part, s21_part);
    } else {
      ck_assert_ptr_null(s21_part);
    }
  }
}
END_TEST

// MARK: - STRERROR 3
START_TEST(STRERRORTest1) {
  for (int i = -123; i < 0; i++) {
    ck_assert_str_eq(s21_strerror(i), strerror(i));
  }
}
END_TEST

START_TEST(STRERRORTest2) {
  for (int i = 0; i < 136; i++) {
    ck_assert_str_eq(s21_strerror(i), strerror(i));
  }
}
END_TEST

START_TEST(STRERRORTest3) {
  for (int i = 107; i <= 234; i++) {
    ck_assert_str_eq(s21_strerror(i), strerror(i));
  }
}
END_TEST

// MARK: - to_upper 7
/*region TOUPPER*/
START_TEST(TOUPPERTest1) {
  char str[4] = "abc";
  char *str1 = (char *)s21_to_upper(str);
  ck_assert_str_eq(str1, "ABC");
  free(str1);
}
END_TEST

START_TEST(TOUPPERTest2) {
  char str[12] = "Hello World";
  char *str1 = (char *)s21_to_upper(str);
  ck_assert_str_eq(str1, "HELLO WORLD");
  free(str1);
}
END_TEST

START_TEST(TOUPPERTest3) {
  char str[1] = "";
  char *str1 = (char *)s21_to_upper(str);
  ck_assert_str_eq(str1, "");
  free(str1);
}
END_TEST

START_TEST(TOUPPERTest4) {
  char str[4] = "ABC";
  char *str1 = (char *)s21_to_upper(str);
  ck_assert_str_eq(str1, "ABC");
  free(str1);
}
END_TEST

START_TEST(TOUPPERTest5) {
  char str[6] = "1234a";
  char *str1 = (char *)s21_to_upper(str);
  ck_assert_str_eq(str1, "1234A");
  free(str1);
}
END_TEST

START_TEST(TOUPPERTest6) {
  char *str = NULL;
  char *str1 = (char *)s21_to_upper(str);
  ck_assert_ptr_eq(str1, NULL);
  free(str1);
}
END_TEST

START_TEST(TOUPPERTest7) {
  char str[12] = "abc\0hello";
  char *str1 = (char *)s21_to_upper(str);
  ck_assert_str_eq(str1, "ABC");
  free(str1);
}
END_TEST
/*endregion*/

// MARK: - insert 7
/*region INSERT*/
START_TEST(INSERTTest1) {
  char str1[4] = "abc";
  char str2[5] = "1234";
  char *str3 = (char *)s21_insert(str1, str2, 2);
  ck_assert_str_eq(str3, "ab1234c");
  free(str3);
}
END_TEST

START_TEST(INSERTTest2) {
  char str1[1] = "";
  char str2[5] = "1234";
  char *str3 = (char *)s21_insert(str1, str2, 1);
  ck_assert_ptr_eq(str3, NULL);
  free(str3);
}
END_TEST

START_TEST(INSERTTest3) {
  char str1[2] = " ";
  char str2[5] = "1234";
  char *str3 = (char *)s21_insert(str1, str2, 1);
  ck_assert_str_eq(str3, " 1234");
  free(str3);
}
END_TEST

START_TEST(INSERTTest4) {
  char str1[4] = "abc";
  char str2[2] = " ";
  char *str3 = (char *)s21_insert(str1, str2, 2);
  ck_assert_str_eq(str3, "ab c");
  free(str3);
}
END_TEST

START_TEST(INSERTTest5) {
  char str1[4] = "abc";
  char str2[5] = "1234";
  char *str3 = (char *)s21_insert(str1, str2, -1);
  ck_assert_ptr_eq(str3, NULL);
  free(str3);
}
END_TEST

START_TEST(INSERTTest6) {
  char str1[4] = "abc";
  char str2[5] = "1234";
  char *str3 = (char *)s21_insert(str1, str2, 0);
  ck_assert_str_eq(str3, "1234abc");
  free(str3);
}
END_TEST

START_TEST(INSERTTest7) {
  char *str1 = NULL;
  char str2[5] = "1234";
  char *str3 = (char *)s21_insert(str1, str2, 0);
  ck_assert_ptr_eq(str3, NULL);
  free(str3);
}
END_TEST
/*endregion*/

// MARK: - to_lower 7
/*region TOLOWER*/
START_TEST(TOLOWERTest1) {
  char str[4] = "abc";
  char *str2 = (char *)s21_to_lower(str);
  ck_assert_str_eq(str2, "abc");
  free(str2);
}
END_TEST

START_TEST(TOLOWERTest2) {
  char str[12] = "Hello World";
  char *str2 = (char *)s21_to_lower(str);
  ck_assert_str_eq(str2, "hello world");
  free(str2);
}
END_TEST

START_TEST(TOLOWERTest3) {
  char str[1] = "";
  char *str2 = (char *)s21_to_lower(str);
  ck_assert_str_eq(str2, "");
  free(str2);
}
END_TEST

START_TEST(TOLOWERTest4) {
  char str[4] = "ABC";
  char *str2 = (char *)s21_to_lower(str);
  ck_assert_str_eq(str2, "abc");
  free(str2);
}
END_TEST

START_TEST(TOLOWERTest5) {
  char str[6] = "1234a";
  char *str2 = (char *)s21_to_lower(str);
  ck_assert_str_eq(str2, "1234a");
  free(str2);
}
END_TEST

START_TEST(TOLOWERTest6) {
  char *str = NULL;
  char *str2 = (char *)s21_to_lower(str);
  ck_assert_ptr_eq(str2, NULL);
  free(str2);
}
END_TEST

START_TEST(TOLOWERTest7) {
  char *str = "WoW\0, I love it!";
  char *str2 = (char *)s21_to_lower(str);
  ck_assert_str_eq(str2, "wow");
  free(str2);
}
END_TEST
/*endregion*/

// MARK: - trim 13
/*region TRIM*/
START_TEST(TRIMTest1) {
  char *str = "WoW\0, I love it!";
  char *str2 = "W";
  char *str3 = (char *)s21_trim(str, str2);
  ck_assert_str_eq(str3, "o");
  free(str3);
}
END_TEST

START_TEST(TRIMTest2) {
  char *str = "WoW, I love it!";
  char *str2 = "W";
  char *str3 = (char *)s21_trim(str, str2);
  ck_assert_str_eq(str3, "oW, I love it!");
  free(str3);
}
END_TEST

START_TEST(TRIMTest3) {
  char *str = "WoW, I love it!";
  char *str2 = "Wo!";
  char *str3 = (char *)s21_trim(str, str2);
  ck_assert_str_eq(str3, ", I love it");
  free(str3);
}
END_TEST

START_TEST(TRIMTest4) {
  char *str = "WoW, I love it!";
  char *str2 = "P";
  char *str3 = (char *)s21_trim(str, str2);
  ck_assert_str_eq(str3, "WoW, I love it!");
  free(str3);
}
END_TEST
START_TEST(TRIMTest5) {
  char *str = "abc";
  char *str2 = "abc";
  char *str3 = (char *)s21_trim(str, str2);
  ck_assert_str_eq(str3, "");
  free(str3);
}
END_TEST
START_TEST(TRIMTest6) {
  char *str = "WoW, I love it!";
  char *str2 = NULL;
  char *str3 = (char *)s21_trim(str, str2);
  ck_assert_str_eq(str3, "WoW, I love it!");
  free(str3);
}
END_TEST

START_TEST(TRIMTest7) {
  char *str = "       WoW, I love     it!             ";
  char *str2 = NULL;
  char *str3 = (char *)s21_trim(str, str2);
  ck_assert_str_eq(str3, "WoW, I love     it!");
  free(str3);
}
END_TEST

START_TEST(TRIMTest8) {
  char *str = "";
  char *str2 = NULL;
  char *str3 = (char *)s21_trim(str, str2);
  ck_assert_str_eq(str3, "");
  free(str3);
}
END_TEST
START_TEST(TRIMTest9) {
  char *str = "          ";
  char *str2 = NULL;
  char *str3 = (char *)s21_trim(str, str2);
  ck_assert_str_eq(str3, "");
  free(str3);
}
END_TEST

START_TEST(TRIMTest10) {
  char *str = NULL;
  char *str2 = NULL;
  char *str3 = (char *)s21_trim(str, str2);
  ck_assert_ptr_eq(str3, NULL);
  free(str3);
}
END_TEST

START_TEST(TRIMTest11) {
  char *str = "            1";
  char *str2 = NULL;
  char *str3 = (char *)s21_trim(str, str2);
  ck_assert_str_eq(str3, "1");
  free(str3);
}
END_TEST

START_TEST(TRIMTest12) {
  char *str = "\t       \t";
  char *str2 = NULL;
  char *str3 = (char *)s21_trim(str, str2);
  ck_assert_str_eq(str3, "");
  free(str3);
}
END_TEST

START_TEST(TRIMTest13) {
  char *str = "     HELLO    ";
  char *str2 = "";
  char *str3 = (char *)s21_trim(str, str2);
  ck_assert_str_eq(str3, "HELLO");
  free(str3);
}
END_TEST
START_TEST(test_1) {
  char s21[100];
  char original[100];
  char format[] = "test: |%d|";
  int number = 21;
  s21_sprintf(s21, format, number);
  sprintf(original, format, number);
  ck_assert_str_eq(s21, original);
}
END_TEST

START_TEST(test_2) {
  char s21[100];
  char original[100];
  char format[] = "test: |%21d|";
  int number = 21;
  s21_sprintf(s21, format, number);
  sprintf(original, format, number);
  ck_assert_str_eq(s21, original);
}
END_TEST

START_TEST(test_3) {
  char s21[100];
  char original[100];
  char format[] = "test: |%-ld|";
  long long int number = LLONG_MIN;
  s21_sprintf(s21, format, number);
  sprintf(original, format, number);
  ck_assert_str_eq(s21, original);
}
END_TEST

START_TEST(test_4) {
  char s21[100];
  char original[100];
  char format[] = "test: |%+d|";
  int number = 0;
  s21_sprintf(s21, format, number);
  sprintf(original, format, number);
  ck_assert_str_eq(s21, original);
}
END_TEST

START_TEST(test_5) {
  char s21[100];
  char original[100];
  char format[] = "test: |% d|";
  int number = -21;
  s21_sprintf(s21, format, number);
  sprintf(original, format, number);
  ck_assert_str_eq(s21, original);
}
END_TEST

START_TEST(test_6) {
  char s21[100];
  char original[100];
  char format[] = "test: |%f|";
  float number = 2.1;
  s21_sprintf(s21, format, number);
  sprintf(original, format, number);
  ck_assert_str_eq(s21, original);
}
END_TEST

START_TEST(test_7) {
  char s21[100];
  char original[100];
  char format[] = "test: |%21f|";
  double number = 0.21;
  s21_sprintf(s21, format, number);
  sprintf(original, format, number);
  ck_assert_str_eq(s21, original);
}
END_TEST

START_TEST(test_8) {
  char s21[100];
  char original[100];
  char format[] = "test: |%-f|";
  double number = 21.21;
  s21_sprintf(s21, format, number);
  sprintf(original, format, number);
  ck_assert_str_eq(s21, original);
}
END_TEST

START_TEST(test_9) {
  char s21[100];
  char original[100];
  char format[] = "test: |%+f|";
  double number = 21.21;
  s21_sprintf(s21, format, number);
  sprintf(original, format, number);
  ck_assert_str_eq(s21, original);
}
END_TEST

START_TEST(test_10) {
  char s21[100];
  char original[100];
  char format[] = "test: |% f|";
  double number = -21.21;
  s21_sprintf(s21, format, number);
  sprintf(original, format, number);
  ck_assert_str_eq(s21, original);
}
END_TEST

START_TEST(test_11) {
  char s21[100];
  char original[100];
  char format[] = "test: |%i|";
  int number = 21;
  s21_sprintf(s21, format, number);
  sprintf(original, format, number);
  ck_assert_str_eq(s21, original);
  //
}
END_TEST

START_TEST(test_12) {
  char s21[100];
  char original[100];
  char format[] = "test: |%i|";
  int number = 21;
  s21_sprintf(s21, format, number);
  sprintf(original, format, number);
  ck_assert_str_eq(s21, original);
  //
}
END_TEST

START_TEST(test_13) {
  char s21[100];
  char original[100];
  char format[] = "test: |%e|";
  double number = 21.21e+21;
  s21_sprintf(s21, format, number);
  sprintf(original, format, number);
  ck_assert_str_eq(s21, original);
  //
}
END_TEST

START_TEST(test_14) {
  char s21[100];
  char original[100];
  char format[] = "test: |%g|";
  double number = 123456.0;
  s21_sprintf(s21, format, number);
  sprintf(original, format, number);
  ck_assert_str_eq(s21, original);
  //
}
END_TEST

START_TEST(test_15) {
  char s21[100];
  char original[100];
  char format[] = "test: |%G|";
  double number = 123456.0;
  s21_sprintf(s21, format, number);
  sprintf(original, format, number);
  ck_assert_str_eq(s21, original);
  //
}
END_TEST

START_TEST(test_16) {
  char s21[100];
  char original[100];
  char format[] = "test: |%o|";
  int number = 21;
  s21_sprintf(s21, format, number);
  sprintf(original, format, number);
  ck_assert_str_eq(s21, original);
  //
}
END_TEST

START_TEST(test_17) {
  char s21[100];
  char original[100];
  char format[] = "test: |%s|";
  char string[] = "->test string<-";
  s21_sprintf(s21, format, string);
  sprintf(original, format, string);
  ck_assert_str_eq(s21, original);
  //
}
END_TEST

START_TEST(test_18) {
  char s21[100];
  char original[100];
  char format[] = "test: |%u|";
  unsigned int number = 21;
  s21_sprintf(s21, format, number);
  sprintf(original, format, number);
  ck_assert_str_eq(s21, original);
  //
}
END_TEST

START_TEST(test_19) {
  char s21[100];
  char original[100];
  char format[] = "test: |%x|";
  int number = 21;
  s21_sprintf(s21, format, number);
  sprintf(original, format, number);
  ck_assert_str_eq(s21, original);
  //
}
END_TEST

START_TEST(test_20) {
  char s21[100];
  char original[100];
  char format[] = "test: |%X|";
  int number = 21;
  s21_sprintf(s21, format, number);
  sprintf(original, format, number);
  ck_assert_str_eq(s21, original);
  //
}
END_TEST

START_TEST(test_21) {
  char s21[100];
  char original[100];
  char format[] = "test: |%p|";
  int number = 21;
  s21_sprintf(s21, format, number);
  sprintf(original, format, number);
  ck_assert_str_eq(s21, original);
  //
}
END_TEST

START_TEST(test_22) {
  char s21[100];
  char original[100];
  char format[] = "test: |%E|";
  double number = 21.21E+21;
  s21_sprintf(s21, format, number);
  sprintf(original, format, number);
  ck_assert_str_eq(s21, original);
  //
}
END_TEST
/*

START_TEST(test_23) {
    char s21[100];
    char original[100];
    char format[] = "test: |%%|";
    s21_sprintf(s21, format);
    sprintf(original, format);
    ck_assert_str_eq(s21, original);
//
}
END_TEST
*/

START_TEST(test_24) {
  char s21[100];
  char original[100];
  char format[] = "test: |%21.21f|";
  double number = 21.21;
  s21_sprintf(s21, format, number);
  sprintf(original, format, number);
  ck_assert_str_eq(s21, original);
  //
}
END_TEST

START_TEST(test_25) {
  char s21[100];
  char original[100];
  char format[] = "test: |%c|";
  int c = 'A';
  s21_sprintf(s21, format, c);
  sprintf(original, format, c);
  ck_assert_str_eq(s21, original);
  //
}
END_TEST

START_TEST(test_26) {
  char s21[100];
  char original[100];
  char format[] = "test: |%lc|";
  wchar_t c = L'A';
  s21_sprintf(s21, format, c);
  sprintf(original, format, c);
  ck_assert_str_eq(s21, original);
  //
}
END_TEST

START_TEST(test_27) {
  char s21[100];
  char original[100];
  char format[] = "test: |% Lf|";
  long double number = 212121.212121;
  s21_sprintf(s21, format, number);
  sprintf(original, format, number);
  ck_assert_str_eq(s21, original);
}
END_TEST

START_TEST(test_28) {
  char s21[100];
  char original[100];
  char format[] = "test: |%ld|";
  long int number = INT_MAX;
  s21_sprintf(s21, format, number);
  sprintf(original, format, number);
  ck_assert_str_eq(s21, original);
}
END_TEST

START_TEST(test_29) {
  char s21[100];
  char original[100];
  char format[] = "test: |%10ld|";
  long int number = INT_MIN;
  s21_sprintf(s21, format, number);
  sprintf(original, format, number);
  ck_assert_str_eq(s21, original);
}
END_TEST

START_TEST(test_30) {
  char s21[100];
  char original[100];
  char format[] = "test: |%lu|";
  long unsigned int number = ULLONG_MAX;
  s21_sprintf(s21, format, number);
  sprintf(original, format, number);
  ck_assert_str_eq(s21, original);
}
END_TEST

START_TEST(test_31) {
  char s21[100];
  char original[100];
  char format[] = "test: |%hd|";
  short int number = 21;
  s21_sprintf(s21, format, number);
  sprintf(original, format, number);
  ck_assert_str_eq(s21, original);
}
END_TEST

START_TEST(test_32) {
  char s21[100];
  char original[100];
  char format[] = "test: |%ls|";
  wchar_t string[] = L"->test string<-";
  s21_sprintf(s21, format, string);
  sprintf(original, format, string);
  ck_assert_str_eq(s21, original);
}
END_TEST

START_TEST(test_33) {
  char s21[100];
  char original[100];
  char format[] = "test: |%f|";
  s21_sprintf(s21, format, NAN);
  sprintf(original, format, NAN);
  ck_assert_str_eq(s21, original);
}
END_TEST
START_TEST(test_34) {
  char s21[100];
  char original[100];
  char format[] = "test: |%f|";
  s21_sprintf(s21, format, INFINITY);
  sprintf(original, format, INFINITY);
  ck_assert_str_eq(s21, original);
}
END_TEST
START_TEST(test_35) {
  char s21[100];
  char original[100];
  char format[] = "test: |%21.21f|";
  double number = 0.0000000000000000010;
  s21_sprintf(s21, format, number);
  sprintf(original, format, number);
  ck_assert_str_eq(s21, original);
}
END_TEST
Suite *f_example_suite_create() {
  Suite *s1 = suite_create("Test_string");
  TCase *StrLenTest = tcase_create("STRLEN");
  TCase *StrChrTest = tcase_create("STRCHR");
  TCase *StrSpnTest = tcase_create("STRSPN");
  TCase *StrcSpnTest = tcase_create("STRСSPN");
  TCase *MemCpyTest = tcase_create("MEMCPY");
  TCase *StrCatTest = tcase_create("STRCAT");
  TCase *MemcmpTest = tcase_create("MEMCMP");
  TCase *StrncatTest = tcase_create("STRNCAT");
  TCase *StrncpyTest = tcase_create("STRNCPY");
  TCase *StrrchrTest = tcase_create("STRRCHR");
  TCase *memmovetest = tcase_create("MEMMOVE");
  TCase *strstrtest = tcase_create("STRSTR");
  TCase *strcmptest = tcase_create("STRCMP");
  TCase *memchrtest = tcase_create("MEMCHR");
  TCase *strcpytest = tcase_create("STRCPY");
  TCase *strpbrktest = tcase_create("STRPBRK");
  TCase *StrnCmpTest = tcase_create("STRNCMP");
  TCase *MemSetTest = tcase_create("MEMSET");
  TCase *StrTokTest = tcase_create("STRTOK");
  TCase *strerrortest = tcase_create("STRERROR");
  TCase *to_uppertest = tcase_create("TOUPPER");
  TCase *inserttest = tcase_create("INSERT");
  TCase *to_lowertest = tcase_create("TOLOWER");
  TCase *trimtest = tcase_create("TRIM");
  TCase *tc1_1 = tcase_create("Core");
  suite_add_tcase(s1, StrLenTest);
  tcase_add_test(StrLenTest, STRLENTest1);
  tcase_add_test(StrLenTest, STRLENTest2);
  tcase_add_test(StrLenTest, STRLENTest3);
  tcase_add_test(StrLenTest, STRLENTest4);
  tcase_add_test(StrLenTest, STRLENTest5);
  tcase_add_test(StrLenTest, STRLENTest6);
  suite_add_tcase(s1, StrChrTest);
  tcase_add_test(StrChrTest, STRCHRTest1);
  tcase_add_test(StrChrTest, STRCHRTest2);
  tcase_add_test(StrChrTest, STRCHRTest3);
  tcase_add_test(StrChrTest, STRCHRTest4);
  tcase_add_test(StrChrTest, STRCHRTest5);
  tcase_add_test(StrChrTest, STRCHRTest6);
  suite_add_tcase(s1, StrSpnTest);
  tcase_add_test(StrSpnTest, STRSPNTest1);
  tcase_add_test(StrSpnTest, STRSPNTest2);
  tcase_add_test(StrSpnTest, STRSPNTest3);
  tcase_add_test(StrSpnTest, STRSPNTest4);
  tcase_add_test(StrSpnTest, STRSPNTest5);
  tcase_add_test(StrSpnTest, STRSPNTest6);
  tcase_add_test(StrSpnTest, STRSPNTest7);
  tcase_add_test(StrSpnTest, STRSPNTest8);
  suite_add_tcase(s1, StrcSpnTest);
  tcase_add_test(StrcSpnTest, STRCSPNTest1);
  tcase_add_test(StrcSpnTest, STRCSPNTest2);
  tcase_add_test(StrcSpnTest, STRCSPNTest3);
  tcase_add_test(StrcSpnTest, STRCSPNTest4);
  tcase_add_test(StrcSpnTest, STRCSPNTest5);
  tcase_add_test(StrcSpnTest, STRCSPNTest6);
  suite_add_tcase(s1, MemCpyTest);
  tcase_add_test(MemCpyTest, MEMCPYTest1);
  tcase_add_test(MemCpyTest, MEMCPYTest2);
  tcase_add_test(MemCpyTest, MEMCPYTest3);
  tcase_add_test(MemCpyTest, MEMCPYTest4);
  tcase_add_test(MemCpyTest, MEMCPYTest5);
  suite_add_tcase(s1, StrCatTest);
  tcase_add_test(StrCatTest, STRCATTest1);
  tcase_add_test(StrCatTest, STRCATTest2);
  tcase_add_test(StrCatTest, STRCATTest3);
  tcase_add_test(StrCatTest, STRCATTest4);
  tcase_add_test(StrCatTest, STRCATTest5);
  suite_add_tcase(s1, MemcmpTest);
  tcase_add_test(MemcmpTest, MEMCMPTest1);
  tcase_add_test(MemcmpTest, MEMCMPTest2);
  tcase_add_test(MemcmpTest, MEMCMPTest3);
  tcase_add_test(MemcmpTest, MEMCMPTest4);
  tcase_add_test(MemcmpTest, MEMCMPTest5);
  tcase_add_test(MemcmpTest, MEMCMPTest6);
  tcase_add_test(MemcmpTest, MEMCMPTest7);
  //    tcase_add_test(MemcmpTest, MEMCMPTest8);
  tcase_add_test(MemcmpTest, MEMCMPTest9);
  tcase_add_test(MemcmpTest, MEMCMPTest10);
  suite_add_tcase(s1, StrncatTest);
  tcase_add_test(StrncatTest, STRNCATTest1);
  tcase_add_test(StrncatTest, STRNCATTest2);
  tcase_add_test(StrncatTest, STRNCATTest3);
  tcase_add_test(StrncatTest, STRNCATTest4);
  tcase_add_test(StrncatTest, STRNCATTest5);
  suite_add_tcase(s1, StrncpyTest);
  tcase_add_test(StrncpyTest, STRNCPYTest1);
  tcase_add_test(StrncpyTest, STRNCPYTest2);
  tcase_add_test(StrncpyTest, STRNCPYTest3);
  tcase_add_test(StrncpyTest, STRNCPYTest4);
  tcase_add_test(StrncpyTest, STRNCPYTest5);
  suite_add_tcase(s1, StrrchrTest);
  tcase_add_test(StrrchrTest, STRRCHRTest1);
  tcase_add_test(StrrchrTest, STRRCHRTest2);
  tcase_add_test(StrrchrTest, STRRCHRTest3);
  tcase_add_test(StrrchrTest, STRRCHRTest4);
  tcase_add_test(StrrchrTest, STRRCHRTest5);
  suite_add_tcase(s1, memmovetest);
  tcase_add_test(memmovetest, MEMMOVETest1);
  tcase_add_test(memmovetest, MEMMOVETest2);
  //    tcase_add_test(memmovetest, MEMMOVETest3);
  //    tcase_add_test(memmovetest, MEMMOVETest4);
  suite_add_tcase(s1, strstrtest);
  tcase_add_test(strstrtest, STRSTRTest1);
  tcase_add_test(strstrtest, STRSTRTest2);
  tcase_add_test(strstrtest, STRSTRTest3);
  tcase_add_test(strstrtest, STRSTRTest4);
  tcase_add_test(strstrtest, STRSTRTest5);
  suite_add_tcase(s1, strcmptest);
  tcase_add_test(strcmptest, STRCMPTest1);
  tcase_add_test(strcmptest, STRCMPTest2);
  tcase_add_test(strcmptest, STRCMPTest3);
  tcase_add_test(strcmptest, STRCMPTest4);
  tcase_add_test(strcmptest, STRCMPTest5);
  tcase_add_test(strcmptest, STRCMPTest6);
  suite_add_tcase(s1, memchrtest);
  tcase_add_test(memchrtest, MEMCHRTest1);
  tcase_add_test(memchrtest, MEMCHRTest2);
  tcase_add_test(memchrtest, MEMCHRTest3);
  tcase_add_test(memchrtest, MEMCHRTest4);
  tcase_add_test(memchrtest, MEMCHRTest5);
  tcase_add_test(memchrtest, MEMCHRTest6);
  suite_add_tcase(s1, strcpytest);
  tcase_add_test(strcpytest, STRCPYTest1);
  tcase_add_test(strcpytest, STRCPYTest2);
  tcase_add_test(strcpytest, STRCPYTest3);
  tcase_add_test(strcpytest, STRCPYTest4);
  tcase_add_test(strcpytest, STRCPYTest5);
  tcase_add_test(strcpytest, STRCPYTest6);
  suite_add_tcase(s1, strpbrktest);
  tcase_add_test(strpbrktest, STRPBRKTest1);
  tcase_add_test(strpbrktest, STRPBRKTest2);
  tcase_add_test(strpbrktest, STRPBRKTest3);
  tcase_add_test(strpbrktest, STRPBRKTest4);
  suite_add_tcase(s1, StrnCmpTest);
  tcase_add_test(StrnCmpTest, STRNCMPTest1);
  tcase_add_test(StrnCmpTest, STRNCMPTest2);
  tcase_add_test(StrnCmpTest, STRNCMPTest3);
  tcase_add_test(StrnCmpTest, STRNCMPTest4);
  tcase_add_test(StrnCmpTest, STRNCMPTest5);
  tcase_add_test(StrnCmpTest, STRNCMPTest6);
  tcase_add_test(StrnCmpTest, STRNCMPTest7);
  tcase_add_test(StrnCmpTest, STRNCMPTest8);
  suite_add_tcase(s1, MemSetTest);
  tcase_add_test(MemSetTest, MEMSETTest1);
  tcase_add_test(MemSetTest, MEMSETTest2);
  tcase_add_test(MemSetTest, MEMSETTest3);
  tcase_add_test(MemSetTest, MEMSETTest4);
  tcase_add_test(MemSetTest, MEMSETTest5);
  tcase_add_test(MemSetTest, MEMSETTest6);
  tcase_add_test(MemSetTest, MEMSETTest7);
  suite_add_tcase(s1, StrTokTest);
  tcase_add_test(StrTokTest, STRTOKTest1);
  tcase_add_test(StrTokTest, STRTOKTest2);
  tcase_add_test(StrTokTest, STRTOKTest3);
  tcase_add_test(StrTokTest, STRTOKTest4);
  tcase_add_test(StrTokTest, STRTOKTest5);
  tcase_add_test(StrTokTest, STRTOKTest6);
  tcase_add_test(StrTokTest, STRTOKTest7);
  tcase_add_test(StrTokTest, STRTOKTest8);
  tcase_add_test(StrTokTest, STRTOKTest9);
  tcase_add_test(StrTokTest, STRTOKTest10);
  suite_add_tcase(s1, strerrortest);
  tcase_add_test(strerrortest, STRERRORTest1);
  tcase_add_test(strerrortest, STRERRORTest2);
  tcase_add_test(strerrortest, STRERRORTest3);
  suite_add_tcase(s1, to_uppertest);
  tcase_add_test(to_uppertest, TOUPPERTest1);
  tcase_add_test(to_uppertest, TOUPPERTest2);
  tcase_add_test(to_uppertest, TOUPPERTest3);
  tcase_add_test(to_uppertest, TOUPPERTest4);
  tcase_add_test(to_uppertest, TOUPPERTest5);
  tcase_add_test(to_uppertest, TOUPPERTest6);
  tcase_add_test(to_uppertest, TOUPPERTest7);
  suite_add_tcase(s1, inserttest);
  tcase_add_test(inserttest, INSERTTest1);
  tcase_add_test(inserttest, INSERTTest2);
  tcase_add_test(inserttest, INSERTTest3);
  tcase_add_test(inserttest, INSERTTest4);
  tcase_add_test(inserttest, INSERTTest5);
  tcase_add_test(inserttest, INSERTTest6);
  tcase_add_test(inserttest, INSERTTest7);
  suite_add_tcase(s1, to_lowertest);
  tcase_add_test(to_lowertest, TOLOWERTest1);
  tcase_add_test(to_lowertest, TOLOWERTest2);
  tcase_add_test(to_lowertest, TOLOWERTest3);
  tcase_add_test(to_lowertest, TOLOWERTest4);
  tcase_add_test(to_lowertest, TOLOWERTest5);
  tcase_add_test(to_lowertest, TOLOWERTest6);
  tcase_add_test(to_lowertest, TOLOWERTest7);
  suite_add_tcase(s1, trimtest);
  tcase_add_test(trimtest, TRIMTest1);
  tcase_add_test(trimtest, TRIMTest2);
  tcase_add_test(trimtest, TRIMTest3);
  tcase_add_test(trimtest, TRIMTest4);
  tcase_add_test(trimtest, TRIMTest5);
  tcase_add_test(trimtest, TRIMTest6);
  tcase_add_test(trimtest, TRIMTest7);
  tcase_add_test(trimtest, TRIMTest8);
  tcase_add_test(trimtest, TRIMTest9);
  tcase_add_test(trimtest, TRIMTest10);
  tcase_add_test(trimtest, TRIMTest11);
  tcase_add_test(trimtest, TRIMTest12);
  tcase_add_test(trimtest, TRIMTest13);
  suite_add_tcase(s1, tc1_1);
  tcase_add_test(tc1_1, test_1);
  tcase_add_test(tc1_1, test_2);
  tcase_add_test(tc1_1, test_3);
  tcase_add_test(tc1_1, test_4);
  tcase_add_test(tc1_1, test_5);
  tcase_add_test(tc1_1, test_6);
  tcase_add_test(tc1_1, test_7);
  tcase_add_test(tc1_1, test_8);
  tcase_add_test(tc1_1, test_9);
  tcase_add_test(tc1_1, test_10);
  tcase_add_test(tc1_1, test_11);
  tcase_add_test(tc1_1, test_12);
  tcase_add_test(tc1_1, test_13);
  tcase_add_test(tc1_1, test_14);
  tcase_add_test(tc1_1, test_15);
  tcase_add_test(tc1_1, test_16);
  tcase_add_test(tc1_1, test_17);
  tcase_add_test(tc1_1, test_18);
  tcase_add_test(tc1_1, test_19);
  tcase_add_test(tc1_1, test_20);
  tcase_add_test(tc1_1, test_21);
  tcase_add_test(tc1_1, test_22);
  //  tcase_add_test(tc1_1, test_23);
  tcase_add_test(tc1_1, test_24);
  tcase_add_test(tc1_1, test_25);
  tcase_add_test(tc1_1, test_26);
  tcase_add_test(tc1_1, test_27);
  tcase_add_test(tc1_1, test_28);
  tcase_add_test(tc1_1, test_29);
  tcase_add_test(tc1_1, test_30);
  tcase_add_test(tc1_1, test_31);
  tcase_add_test(tc1_1, test_32);
  tcase_add_test(tc1_1, test_33);
  tcase_add_test(tc1_1, test_34);
  tcase_add_test(tc1_1, test_35);
  return s1;
}

int main() {
  Suite *s1 = f_example_suite_create();
  // Runner
  SRunner *runner = srunner_create(s1);
  int number_failed;
  srunner_run_all(runner, CK_NORMAL);
  number_failed = srunner_ntests_failed(runner);
  srunner_free(runner);
  return number_failed == 0 ? 0 : 1;
}
