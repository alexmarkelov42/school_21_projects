#include "smart_calc_1_0.h"

int convert_to_rpn(char *input, s21_stack *rpn_stack) {
  int error = 0;
  if (strlen(input) >= MAX_SIZE) {
    error = STRING_TOO_BIG;
  } else {
    s21_stack op_stack = {0};
    op_stack.size = 0;
    char *token = calloc(20, sizeof(char));
    char *tmp = calloc(20, sizeof(char));
    size_t i = 0;
    int token_code = 0;
    int err_stack = OK;
    int prev_token_code = TOKEN_EMPTY;
    int is_unary = 0;
    while ((i <= strlen(input) - 1) && (error == OK)) {
      token_code = parse_token(input, &i, token);
      switch (token_code) {
        case IS_SPACE:
          break;
        case NUMBER_OVERFLOW:
          error = NUMBER_OVERFLOW;
          break;
        case IS_FUNCTION:
          s21_push(&op_stack, token);
          break;
        case IS_DIGIT:
          s21_push(rpn_stack, token);
          break;
        case IS_OPEN_BRACKET:
          s21_push(&op_stack, token);
          break;
        case IS_CLOSE_BRACKET:
          err_stack = s21_pop(&op_stack, tmp);
          while ((err_stack == OK) && (strcmp(tmp, "(") != 0)) {
            s21_push(rpn_stack, tmp);
            err_stack = s21_pop(&op_stack, tmp);
          }
          if (err_stack == STACK_EMPTY) {
            error = BRACKET_MISSMATCH;
          }
          break;
        case IS_OPERATOR:
          if ((prev_token_code == IS_DIGIT) ||
              prev_token_code == IS_CLOSE_BRACKET ||
              (prev_token_code == IS_X)) {
            is_unary = 0;
            push_operator(&op_stack, rpn_stack, token);
          } else {
            if ((strcmp(token, "+") == 0)) {
              if (is_unary == 1) {
                error = INVALID_EXPRESSION;
              } else {
                is_unary = 1;
              }
            } else if (strcmp(token, "-") == 0) {
              if (is_unary == 1) {
                error = INVALID_EXPRESSION;
              } else {
                is_unary = 1;
                s21_push(&op_stack, "~");
              }
            } else {
              error = PARSE_ERROR;
            }
          }
          break;
        case IS_X:
          if (prev_token_code == IS_X) {
            error = PARSE_ERROR;
          } else {
            s21_push(rpn_stack, token);
          }
          break;
        case PARSE_ERROR:
          error = PARSE_ERROR;
          break;
        default:
          error = PARSE_ERROR;
          break;
      }
      if (token_code != IS_SPACE) {
        prev_token_code = token_code;
      }
    }
    while ((op_stack.size != 0) && (error == OK)) {
      s21_pop(&op_stack, tmp);
      if (strcmp(tmp, "(") == 0) {
        error = BRACKET_MISSMATCH;
        continue;
      }
      s21_push(rpn_stack, tmp);
    }
    s21_clear_stack(&op_stack);
    free(token);
    free(tmp);
  }
  return error;
}

int eval_expr(s21_stack rpn, double x, double *res) {
  int error = OK;
  double tmp = 0;
  double_stack result = {0};
  if (rpn.size < 1) {
    error = INVALID_EXPRESSION;
  }
  for (int i = 0; (i < rpn.size) && (error == OK); i++) {
    if ((strcmp(rpn.data[i], "x") == 0) || (strcmp(rpn.data[i], "X") == 0)) {
      s21_double_push(&result, x);
    } else if (s21_is_number(rpn.data[i]) == 1) {
      tmp = strtod(rpn.data[i], NULL);
      s21_double_push(&result, tmp);
    } else {
      if (is_2_operand(rpn.data[i]) == 1) {
        if (result.size < 2) {
          error = INVALID_EXPRESSION;
        } else {
          error = eval_operator(rpn.data[i], &result);
        }
      } else {
        error = eval_function(rpn.data[i], &result);
      }
    }
  }
  if (error == OK) {
    if (result.size > 1) {
      error = INVALID_EXPRESSION;
    } else {
      error = s21_double_pop(&result, res);
    }
  }
  return error;
}

int s21_pop(s21_stack *stack, char *res) {
  int err = OK;
  if (stack->size == 0) {
    err = STACK_EMPTY;
  } else {
    strcpy(res, stack->data[stack->size - 1]);
    free(stack->data[stack->size - 1]);
    stack->size -= 1;
  }
  return err;
}

int s21_push(s21_stack *stack, char *val) {
  int err = OK;
  if (stack->size >= MAX_SIZE) {
    err = STACK_FULL;
  } else {
    stack->data[stack->size] = calloc(20, sizeof(char));
    strcpy(stack->data[stack->size], val);
    stack->size += 1;
  }
  return err;
}

void s21_clear_stack(s21_stack *stack) {
  for (int i = stack->size - 1; i >= 0; i--) {
    free(stack->data[i]);
    stack->size -= 1;
  }
}

void s21_peek(s21_stack *stack, char *res) {
  if (stack->size != 0) {
    strcpy(res, stack->data[stack->size - 1]);
  } else {
    strcpy(res, "");
  }
}

int parse_token(char *input, size_t *i, char *token) {
  int ans = PARSE_ERROR;
  if ((input[*i] == '+') || (input[*i] == '-') || (input[*i] == '*') ||
      (input[*i] == '/') || (input[*i] == '^')) {
    ans = IS_OPERATOR;
    memcpy(token, &input[*i], sizeof(char) * 1);
    token[1] = '\0';
    *i += 1;
  } else if (input[*i] == '(') {
    ans = IS_OPEN_BRACKET;
    memcpy(token, &input[*i], sizeof(char) * 1);
    token[1] = '\0';
    *i += 1;
  } else if (input[*i] == ')') {
    ans = IS_CLOSE_BRACKET;
    memcpy(token, &input[*i], sizeof(char) * 1);
    token[1] = '\0';
    *i += 1;
  } else if ((input[*i] == 'x') || (input[*i] == 'X')) {
    ans = IS_X;
    memcpy(token, &input[*i], sizeof(char) * 1);
    token[1] = '\0';
    *i += 1;
  } else if (is_digit(input[*i])) {
    int ind = *i;
    int ret = parse_number(input, i);
    if (ret == OK) {
      memcpy(token, &input[ind], sizeof(char) * (*i - ind) + 1);
      token[*i - ind + 1] = '\0';
      *i += 1;
      ans = IS_DIGIT;
    } else {
      ans = ret;
    }
  } else if (is_char(input[*i])) {
    int len = is_function(input, *i);
    if (len != 0) {
      ans = IS_FUNCTION;
      memcpy(token, &input[*i], sizeof(char) * len);
      token[len] = '\0';
      *i += len;
    }
  } else if (input[*i] == ' ') {
    *i += 1;
    ans = IS_SPACE;
  } else {
    ans = PARSE_ERROR;
  }
  return ans;
}

int is_digit(char ch) { return ((ch >= 48) && (ch <= 57)); }

int is_function(char *input, int i) {
  int len = 0;
  char *functions[10] = {"cos",  "sin",  "tan", "acos", "asin",
                         "atan", "sqrt", "ln",  "log",  "mod"};
  for (int j = 0; j < 10; j++) {
    if (strncmp(&input[i], functions[j], strlen(functions[j])) == 0) {
      len = strlen(functions[j]);
    }
  }
  return len;
}

int get_priority(char *token) {
  /*     ~ (negate)  = 6    */
  /*     sin,cos,... = 5    */
  /*     ^           = 4    */
  /*     *,/         = 3    */
  /*     +,-         = 2    */
  /*     (           = 1    */
  int res = 0;
  if (strcmp(token, "(") == 0) {
    res = 1;
  } else if ((strcmp(token, "+") == 0) || (strcmp(token, "-") == 0)) {
    res = 2;
  } else if ((strcmp(token, "*") == 0) || (strcmp(token, "/") == 0)) {
    res = 3;
  } else if (strcmp(token, "^") == 0) {
    res = 4;
  } else if (strcmp(token, "~") == 0) {
    res = 6;
  } else {
    res = 5;
  }
  return res;
}

void push_operator(s21_stack *op_stack, s21_stack *rpn_stack, char *token) {
  int token_prior = 0;
  int op_stack_prior = 0;
  char *top_operator = calloc(20, sizeof(char));
  if (op_stack->size == 0) {
    s21_push(op_stack, token);
  } else {
    token_prior = get_priority(token);
    s21_peek(op_stack, top_operator);
    op_stack_prior = get_priority(top_operator);
    if (op_stack_prior >= token_prior) {
      if ((strcmp(top_operator, "^") == 0) && (strcmp(token, "^") == 0)) {
        s21_push(op_stack, top_operator);
      } else {
        while ((op_stack_prior >= token_prior) && (op_stack->size != 0)) {
          if (strcmp(top_operator, "(") != 0) {
            s21_push(rpn_stack, top_operator);
            s21_discard(op_stack);
            s21_peek(op_stack, top_operator);
            op_stack_prior = get_priority(top_operator);
          }
        }
        s21_push(op_stack, token);
      }
    } else {
      s21_push(op_stack, token);
    }
  }
  free(top_operator);
}

int s21_discard(s21_stack *stack) {
  int err = OK;
  if (stack->size == 0) {
    err = STACK_EMPTY;
  } else {
    free(stack->data[stack->size - 1]);
    stack->size -= 1;
  }
  return err;
}

int is_char(char ch) { return ((ch >= 97) && (ch <= 122)); }

int parse_number(char *input, size_t *i) {
  int is_end = 0;
  int ans = OK;
  int is_dot = 0;
  size_t len = strlen(input);
  while ((*i + 1 < len) && (is_end == 0)) {
    if (is_digit(input[*i + 1])) {
      *i = *i + 1;
    } else if (input[*i + 1] == '.') {
      if (is_dot == 0) {
        is_dot = 1;
        *i = *i + 1;
      } else {
        is_end = 1;
        ans = PARSE_ERROR;
      }
    } else {
      is_end = 1;
    }
  }
  if (input[*i] == '.') {
    ans = PARSE_ERROR;
  }
  return ans;
}

int s21_double_push(double_stack *stack, double val) {
  int ans = OK;
  if (stack->size > MAX_SIZE) {
    ans = STACK_FULL;
  } else {
    stack->data[stack->size] = val;
    stack->size += 1;
  }
  return ans;
}

int s21_double_pop(double_stack *stack, double *res) {
  int ans = OK;
  if (stack->size == 0) {
    ans = STACK_EMPTY;
  } else {
    *res = stack->data[stack->size - 1];
    stack->data[stack->size - 1] = 0;
    stack->size -= 1;
  }
  return ans;
}

int s21_is_number(char *str) {
  int ans = 1;
  for (size_t i = 0; (i < strlen(str)) && (ans == 1); i++) {
    if (is_digit(str[i]) == 0) {
      if (str[i] != '.') {
        ans = 0;
      }
    }
  }
  return ans;
}

int is_2_operand(char *str) {
  int ans = 0;
  if ((strcmp(str, "+") == 0) || (strcmp(str, "-") == 0) ||
      (strcmp(str, "*") == 0) || (strcmp(str, "/") == 0) ||
      (strcmp(str, "mod") == 0) || (strcmp(str, "^") == 0)) {
    ans = 1;
  }
  return ans;
}

int eval_operator(char *op, double_stack *result) {
  int ans = OK;
  int err = OK;
  double op2 = 0;
  double op1 = 0;
  double res = 0;
  err = s21_double_pop(result, &op2);
  if (err == STACK_EMPTY) {
    ans = INVALID_EXPRESSION;
  }
  err = s21_double_pop(result, &op1);
  if (err == STACK_EMPTY) {
    ans = INVALID_EXPRESSION;
  }
  if (strcmp(op, "+") == 0) {
    res = op1 + op2;
  } else if (strcmp(op, "-") == 0) {
    res = op1 - op2;
  } else if (strcmp(op, "*") == 0) {
    res = op1 * op2;
  } else if (strcmp(op, "/") == 0) {
    if (op2 < 1e-7) {
      ans = DIV_BY_ZERO;
    } else {
      res = op1 / op2;
    }
  } else if (strcmp(op, "mod") == 0) {
    if (op2 < 1e-7) {
      ans = DIV_BY_ZERO;
    } else {
      res = fmod(op1, op2);
    }
  } else if (strcmp(op, "^") == 0) {
    res = pow(op1, op2);
  }
  if (ans == OK) {
    ans = s21_double_push(result, res);
  }
  return ans;
}

int eval_function(char *op, double_stack *result) {
  int ans = OK;
  int err = OK;
  double op1 = 0;
  double tmp = 0;
  err = s21_double_pop(result, &op1);
  if (err == OK) {
    if (strcmp(op, "sin") == 0) {
      tmp = sin(op1);
      err = s21_double_push(result, tmp);
    } else if (strcmp(op, "cos") == 0) {
      tmp = cos(op1);
      err = s21_double_push(result, tmp);
    } else if (strcmp(op, "tan") == 0) {
      tmp = tan(op1);
      err = s21_double_push(result, tmp);
    } else if (strcmp(op, "asin") == 0) {
      tmp = asin(op1);
      err = s21_double_push(result, tmp);
    } else if (strcmp(op, "acos") == 0) {
      tmp = acos(op1);
      err = s21_double_push(result, tmp);
    } else if (strcmp(op, "atan") == 0) {
      tmp = atan(op1);
      err = s21_double_push(result, tmp);
    } else if (strcmp(op, "log") == 0) {
      if (op1 <= 0) {
        ans = MATH_ERROR;
      } else {
        tmp = log10(op1);
        err = s21_double_push(result, tmp);
      }
    } else if (strcmp(op, "ln") == 0) {
      if (op1 <= 0) {
        ans = MATH_ERROR;
      } else {
        tmp = log(op1);
        err = s21_double_push(result, tmp);
      }
    } else if (strcmp(op, "sqrt") == 0) {
      if (op1 < 0) {
        ans = MATH_ERROR;
      } else {
        tmp = sqrt(op1);
        err = s21_double_push(result, tmp);
      }
    } else if (strcmp(op, "~") == 0) {
      tmp = op1 * -1;
      err = s21_double_push(result, tmp);
    }
  } else {
    ans = INVALID_EXPRESSION;
  }
  return ans;
}
