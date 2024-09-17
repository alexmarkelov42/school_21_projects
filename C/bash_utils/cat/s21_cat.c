#include "s21_cat.h"

int main(int argc, char *argv[]) {
  if (argc <= 1) {
    exit(0);
  }
  struct flags my_flags = {
      false, false, false, false, false, false,
  };
  int err = process_flags(argc, argv, &my_flags);
  if (err == 0) {
    print_files(argc, argv, my_flags);
  } else {
    fprintf(stderr, "Error occured\n");
  }
  return err;
}

bool is_short_opt(char *str) {
  bool res = false;
  if (strlen(str) < 2) {
    res = false;
  } else {
    if ((str[0] == '-') && (str[1] != '-')) {
      res = true;
    }
  }
  return res;
}

bool is_long_opt(char *str) {
  bool res = false;
  if (strlen(str) < 3) {
    res = false;
  } else {
    if ((str[0] == '-') && (str[1] == '-')) {
      res = true;
    }
  }
  return res;
}

int process_flags(int argc, char *argv[], struct flags *my_flags) {
  int error = 0;
  for (int i = 1; (i < argc) && (error == 0); i++) {
    if (is_short_opt(argv[i])) {
      error = process_short_opt(argv[i], my_flags);
    } else if (is_long_opt(argv[i])) {
      error = process_long_opt(argv[i], my_flags);
    }
  }
  return error;
}

int process_short_opt(char *str, struct flags *my_flags) {
  int error = 0;
  for (size_t i = 1; i < strlen(str); i++) {
    switch (str[i]) {
      case 'b':
        my_flags->b = true;
        my_flags->n = false;
        break;
      case 'v':
        my_flags->v = true;
        break;
      case 'e':
        my_flags->e = true;
        my_flags->v = true;
        break;
      case 'n':
        if (my_flags->b != true) {
          my_flags->n = true;
        }
        break;
      case 's':
        my_flags->s = true;
        break;
      case 't':
        my_flags->t = true;
        my_flags->v = true;
        break;
      case 'E':
        my_flags->e = true;
        break;
      case 'T':
        my_flags->t = true;
        break;
      default:
        error = 1;
    }
  }
  return error;
}

int process_long_opt(char *str, struct flags *my_flags) {
  int error = 0;
  if (strcmp(str, "--number-nonblank") == 0) {
    my_flags->b = true;
    my_flags->n = false;
  } else if (strcmp(str, "--number") == 0) {
    if (my_flags->b != true) {
      my_flags->n = true;
    }
  } else if (strcmp(str, "--squeeze-blank") == 0) {
    my_flags->s = true;
  } else {
    printf("error unknown option \"%s\"\n", str);
    error = 1;
  }
  return error;
}

void print_files(int argc, char *argv[], struct flags my_flags) {
  int line_num = 1;
  for (int i = 1; i < argc; i++) {
    if (argv[i][0] != '-') {
      FILE *fp = fopen(argv[i], "r");
      if (fp == NULL) {
        fprintf(stderr, "Error. %s - no such file or directory\n", argv[i]);
      } else {
        print_result(fp, my_flags, &line_num);
      }
    }
  }
}

void print_result(FILE *fp, struct flags my_flags, int *line_num) {
  char ch = fgetc(fp);
  char ch_f = fgetc(fp);
  char ch_f_2 = fgetc(fp);
  if (my_flags.n == true) {
    printf("%6d\t", *line_num);
    *line_num += 1;
  } else if ((my_flags.b == true) && (ch != '\n')) {
    printf("%6d\t", *line_num);
    *line_num += 1;
  }
  squeeze_start_of_file(&ch, &ch_f, &ch_f_2, my_flags, fp);
  while (ch_f != EOF) {
    squeeze_lines(&ch, &ch_f, &ch_f_2, my_flags, fp);
    print_end_of_string(ch, my_flags);
    print_char(ch, my_flags);
    print_line_num(ch, ch_f, my_flags, line_num);
    ch = ch_f;
    ch_f = ch_f_2;
    ch_f_2 = fgetc(fp);
  }
  print_end_of_string(ch, my_flags);
  printf("\n");
}
void print_char(int ch, struct flags my_flags) {
  if (my_flags.v == true) {
    if (ch < -96) {
      printf("M-^%c", ch + 192);
    } else if (ch < 0) {
      printf("M-%c", ch + 128);
    } else if ((ch == 10) || (ch == 9)) {
      if ((ch == '\t') && (my_flags.t == true)) {
        printf("^I");
      } else {
        printf("%c", ch);
      }
    } else if (ch < 32) {
      printf("^%c", ch);
    } else if (ch < 127) {
      printf("%c", ch);
    } else {
      printf("^?");
    }
  } else {
    if ((ch == '\t') && (my_flags.t == true)) {
      printf("^I");
    } else {
      printf("%c", ch);
    }
  }
}

void print_line_num(char ch, char ch_f, struct flags my_flags, int *line_num) {
  if (ch == '\n') {
    if (my_flags.n == true) {
      printf("%6d\t", *line_num);
      *line_num += 1;
    } else if (my_flags.b == true) {
      if (ch_f != '\n') {
        printf("%6d\t", *line_num);
        *line_num += 1;
      }
    }
  }
}

void print_end_of_string(char ch, struct flags my_flags) {
  if (ch == '\n') {
    if (my_flags.e == true) {
      printf("$");
    }
  }
}

void squeeze_lines(char *ch, char *ch_f, char *ch_f_2, struct flags my_flags,
                   FILE *fp) {
  if (my_flags.s == true) {
    if ((*ch == '\n') && (*ch_f == '\n') && (*ch_f_2 == '\n')) {
      while (*ch_f_2 == '\n') {
        *ch_f_2 = fgetc(fp);
      }
    }
  }
}

void squeeze_start_of_file(char *ch, char *ch_f, char *ch_f_2,
                           struct flags my_flags, FILE *fp) {
  if (my_flags.s == true) {
    if ((*ch == '\n') && (*ch_f == '\n')) {
      while (*ch_f == '\n') {
        *ch_f = *ch_f_2;
        *ch_f_2 = fgetc(fp);
      }
    }
  }
}
