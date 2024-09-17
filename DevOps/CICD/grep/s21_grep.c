#include "s21_grep.h"

int main(int argc, char *argv[]) {
  if (argc <= 2) {
    exit(0);
  }
  struct flags my_flags = {
      false, false, false, false, false, false, false,
      false, false, false, true,  true,  true,
  };
  char regex_string[4096] = {0};
  int start_index = 1;
  int error;
  error = process_opt(argc, argv, &my_flags, regex_string, &start_index);
  if (error == OK) {
    print_result(argc, argv, my_flags, regex_string, start_index);
  }
  return 0;
}

int process_opt(int argc, char *argv[], struct flags *my_flags, char *regex_str,
                int *start_index) {
  /* my_flags->is_first_pattern = true; */
  /* my_flags->is_count_file = false; */
  int error = OK;
  int num_of_files = 0;
  bool go_to_next_opt = false;
  my_flags->is_count_file = false;
  for (int i = 1; i < argc && (error != ERROR); i++) {
    go_to_next_opt = false;
    my_flags->is_count_file = false;
    if (argv[i][0] == '-') {
      for (size_t j = 1;
           j < strlen(argv[i]) && (error != ERROR) && (go_to_next_opt != true);
           j++) {
        int ch = argv[i][j];
        switch (ch) {
          case 'e':
            my_flags->is_e_f = true;
            process_e_flag(my_flags, argv, i, j, regex_str);
            go_to_next_opt = true;
            break;
          case 'f':
            my_flags->is_e_f = true;
            // is_count_file = true;// inside process_f_flag
            process_f_flag(my_flags, argv, i, j, regex_str);
            go_to_next_opt = true;
            break;
          case 'i':
            my_flags->i = true;
            break;
          case 'v':
            my_flags->v = true;
            break;
          case 'c':
            my_flags->c = true;
            break;
          case 'l':
            my_flags->l = true;
            break;
          case 'n':
            my_flags->n = true;
            break;
          case 'h':
            my_flags->h = true;
            break;
          case 's':
            my_flags->s = true;
            break;
          case 'o':
            my_flags->o = true;
            break;
          default:
            error = ERROR;
            fprintf(stderr, "grep: invalid option -- %c\n", ch);
        }
        if (my_flags->is_count_file == true) {
          i += 1;
        }
      }
    } else {
      num_of_files += 1;
    }
  }
  if (my_flags->is_e_f == false) {
    int i = 1;
    num_of_files -= 1;
    while ((argv[i][0] == '-') && (i <= argc)) {
      i += 1;
    }
    strcat(regex_str, argv[i]);
    *start_index = i + 1;
  }
  if (num_of_files > 1) {
    my_flags->is_mult_file = true;
  }
  return error;
}

void print_result(int argc, char *argv[], struct flags my_flags,
                  char *regex_str, int start_index) {
  regex_t regexpr;
  int reg_compiled;
  // printf("regex_str - %s\n", regex_str);
  if (my_flags.i == true) {
    reg_compiled = regcomp(&regexpr, regex_str, REG_ICASE | REG_EXTENDED);
  } else {
    reg_compiled = regcomp(&regexpr, regex_str, REG_EXTENDED);
  }
  if (reg_compiled == 0) {
    for (int i = start_index; i < argc; i++) {
      if (argv[i][0] != '-') {
        FILE *fp = fopen(argv[i], "r");
        if (fp != NULL) {
          if (my_flags.l == true) {
            print_filenames(fp, argv[i], regexpr, my_flags);
          } else if (my_flags.c == true) {
            count_lines(fp, argv[i], regexpr, my_flags);
          } else if (my_flags.o == true) {
            print_o_pattern(fp, my_flags, regexpr, argv[i]);
          } else {
            normal_print(fp, my_flags, regexpr, argv[i]);
          }
          fclose(fp);
        } else {
          if (my_flags.s == false) {
            fprintf(stderr, "could not open file %s\n", argv[i]);
          }
        }
      } else {
        size_t s = strlen(argv[i]);
        if ((argv[i][s - 1] == 'e') || (argv[i][s - 1] == 'f')) {
          i += 1;
        }
      }
    }
  } else {
    if (my_flags.s == false) {
      fprintf(stderr, "Error, could not compile regular expression\n");
    }
  }
  regfree(&regexpr);
}

void print_line(char *line, struct flags my_flags, int ret_val, int line_num,
                char *filename) {
  int ind = 0;
  if ((ret_val == 0) && (my_flags.v != true)) {
    if ((my_flags.is_mult_file == true) && (my_flags.h != true)) {
      printf("%s:", filename);
    }
    if (my_flags.n == true) {
      printf("%d:", line_num);
    }
    while ((line[ind] != '\n') && (line[ind] != '\0')) {
      printf("%c", line[ind]);
      ind += 1;
    }
    printf("\n");
  }
  if ((ret_val != 0) && (my_flags.v == true)) {
    if ((my_flags.is_mult_file == true) && (my_flags.h != true)) {
      printf("%s:", filename);
    }
    if (my_flags.n == true) {
      printf("%d:", line_num);
    }
    while ((line[ind] != '\n') && (line[ind] != '\0')) {
      printf("%c", line[ind]);
      ind += 1;
    }
    printf("\n");
  }
}

void count_lines(FILE *fp, char *filename, regex_t regexpr,
                 struct flags my_flags) {
  size_t line_cap = 0;
  ssize_t line_len = 1;
  char *line = NULL;
  int ret_val = 0;
  int num_of_lines = 0;
  line_len = getline(&line, &line_cap, fp);
  do {
    ret_val = regexec(&regexpr, line, 0, NULL, 0);
    if (my_flags.v != true) {
      if (ret_val == 0) {
        num_of_lines += 1;
      }
    } else {
      if (ret_val != 0) {
        num_of_lines += 1;
      }
    }
    line_len = getline(&line, &line_cap, fp);
  } while (line_len != -1);
  if ((my_flags.is_mult_file == true) && (my_flags.h != true)) {
    printf("%s:", filename);
  }
  printf("%d\n", num_of_lines);  // TODO filename
  free(line);
}

void print_filenames(FILE *fp, char *filename, regex_t regexpr,
                     struct flags my_flags) {
  bool file_match = false;
  int ret_val = 0;
  size_t line_cap = 0;
  ssize_t line_len = 1;
  char *line = NULL;
  line_len = getline(&line, &line_cap, fp);
  do {
    ret_val = regexec(&regexpr, line, 0, NULL, 0);
    if ((ret_val == 0) && (my_flags.v != true)) {
      file_match = true;
      printf("%s\n", filename);
    }
    if ((ret_val != 0) && (my_flags.v == true)) {
      file_match = true;
      printf("%s\n", filename);
    }
    line_len = getline(&line, &line_cap, fp);
  } while ((file_match == false) && (line_len != -1));
  free(line);
}

void normal_print(FILE *fp, struct flags my_flags, regex_t regexpr,
                  char *filename) {
  int ret_val = 0;
  int line_num = 0;
  size_t line_cap = 0;
  ssize_t line_len = 1;
  char *line = NULL;
  line_len = getline(&line, &line_cap, fp);
  do {
    ret_val = regexec(&regexpr, line, 0, NULL, 0);
    line_num += 1;
    print_line(line, my_flags, ret_val, line_num, filename);
    line_len = getline(&line, &line_cap, fp);
  } while (line_len != -1);
  free(line);
}

void print_o_pattern(FILE *fp, struct flags my_flags, regex_t regexpr,
                     char *filename) {
  regmatch_t pm;
  char *line = NULL;
  int offset = 0;
  size_t line_cap = 0;
  ssize_t line_len;
  int error = 0;
  int line_num = 1;
  line_len = getline(&line, &line_cap, fp);
  do {
    error = regexec(&regexpr, line, 1, &pm, 0);
    while ((error == 0) && (my_flags.v == false)) {
      if ((my_flags.is_mult_file == true) && (my_flags.h != true)) {
        printf("%s:", filename);
      }
      if (my_flags.n == true) {
        printf("%d:", line_num);
      }
      if (pm.rm_eo + offset <= line_len) {
        for (int i = pm.rm_so + offset; i < pm.rm_eo + offset; i++) {
          printf("%c", line[i]);
        }
        printf("\n");
        offset += pm.rm_eo;
      }
      error = regexec(&regexpr, line + offset, 1, &pm, 0);
    }
    offset = 0;
    line_num += 1;
    line_len = getline(&line, &line_cap, fp);
  } while (line_len != -1);
  free(line);
}

void process_e_flag(struct flags *my_flags, char *argv[], int i, size_t j,
                    char *regex_str) {
  if (my_flags->is_first_pattern == true) {
    my_flags->is_first_pattern = false;
  } else {
    strcat(regex_str, "|");
  }
  if (strlen(argv[i]) == (j + 1)) {  // grep -ce kappa file1.txt j = 2
    strcat(regex_str, argv[i + 1]);
    my_flags->is_count_file = true;
  } else {
    strcat(regex_str, argv[i] + j + 1);
  }
}

void process_f_flag(struct flags *my_flags, char *argv[], int i, size_t j,
                    char *regex_str) {
  size_t line_cap = 0;
  char *line = NULL;
  ssize_t line_len = 0;
  FILE *fp;
  if (strlen(argv[i]) == 2) {
    fp = fopen(argv[i + 1], "r");
  } else {
    fp = fopen(argv[i] + j + 1, "r");
  }
  if (fp == NULL) {
    fprintf(stderr, "Error. %s - no such file or directory\n", argv[i + 1]);
  } else {
    my_flags->is_e_f = true;
    my_flags->is_count_file = true;
    line_len = getline(&line, &line_cap, fp);
    while (line_len > 0) {
      if (my_flags->is_first_pattern == true) {
        my_flags->is_first_pattern = false;
        if (line[line_len - 1] == '\n') {
          strncat(regex_str, line, line_len - 1);
        } else {
          strcat(regex_str, line);
        }
      } else {
        strcat(regex_str, "|");
        if (line[line_len - 1] == '\n') {
          strncat(regex_str, line, line_len - 1);
        } else {
          strcat(regex_str, line);
        }
        // strcat(regex_str, line);
      }
      line_len = getline(&line, &line_cap, fp);
    }
    fclose(fp);
  }
  free(line);
}
