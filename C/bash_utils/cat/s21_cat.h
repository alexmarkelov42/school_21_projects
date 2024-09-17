#ifndef SRC_CAT_S21_CAT_H_
#define SRC_CAT_S21_CAT_H_

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

struct flags {
  bool b;
  bool v;
  bool e;
  bool n;
  bool s;
  bool t;
};

void print_files(int argc, char *argv[], struct flags my_flags);
void print_char(int ch, struct flags my_flags);
int process_flags(int argc, char *argv[], struct flags *my_flags);
bool is_short_opt(char *str);
bool is_long_opt(char *str);
int process_short_opt(char *str, struct flags *my_flags);
int process_long_opt(char *str, struct flags *my_flags);
void print_result(FILE *fp, struct flags my_flags, int *line_num);
void print_line_num(char ch, char ch_f, struct flags my_flags, int *line_num);
void squeeze_lines(char *ch, char *ch_f, char *ch_f_2, struct flags my_flags,
                   FILE *fp);
void print_end_of_string(char ch, struct flags my_flags);
void squeeze_start_of_file(char *ch, char *ch_f, char *ch_f_2,
                           struct flags my_flags, FILE *fp);

#endif  //  SRC_CAT_S21_CAT_H_
