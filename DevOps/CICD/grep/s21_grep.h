#ifndef SRC_GREP_S21_GREP_H_
#define SRC_GREP_S21_GREP_H_
#include <regex.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define OK 0
#define ERROR 1

struct flags {
  bool i;
  bool v;
  bool c;
  bool l;
  bool n;
  bool h;
  bool s;
  bool o;
  bool is_e_f;
  bool is_mult_file;
  bool is_count_file;
  bool is_first_pattern;
  bool is_count_zero;
};

int process_opt(int argc, char *argv[], struct flags *my_flags, char *regex_str,
                int *start_index);
void print_result(int argc, char *argv[], struct flags my_flags,
                  char *regex_str, int start_index);
void print_line(char *line, struct flags my_flags, int ret_val, int line_num,
                char *filename);
void count_lines(FILE *fp, char *filename, regex_t regexpr,
                 struct flags my_flags);
void print_filenames(FILE *fp, char *filename, regex_t regexpr,
                     struct flags my_flags);
void normal_print(FILE *fp, struct flags my_flags, regex_t regexpr,
                  char *filename);
void print_o_pattern(FILE *fp, struct flags my_flags, regex_t regexpr,
                     char *filename);
void process_e_flag(struct flags *my_flags, char *argv[], int i, size_t j,
                    char *regex_str);
void process_f_flag(struct flags *my_flags, char *argv[], int i, size_t j,
                    char *regex_str);
#endif  //  SRC_GREP_S21_GREP_H_
