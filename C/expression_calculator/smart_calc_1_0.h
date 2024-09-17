#ifndef SMART_CALC_1_0_H
#define SMART_CALC_1_0_H

#define MAX_SIZE 256
#define OK 0
#define STRING_TOO_BIG 1
#define STACK_EMPTY 2
#define STACK_FULL 3
#define PARSE_ERROR 4
#define NUMBER_OVERFLOW 5
#define BRACKET_MISSMATCH 6
#define INVALID_EXPRESSION 7
#define DIV_BY_ZERO 8
#define MATH_ERROR 9
/* numbers from -1000000 to 1000000 */

#define IS_DIGIT 42
#define IS_OPERATOR 43
#define IS_FUNCTION 44
#define IS_OPEN_BRACKET 45
#define IS_CLOSE_BRACKET 46
#define IS_SPACE 47
#define IS_X 48
#define TOKEN_EMPTY 420

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct stack {
  int size;
  char *data[MAX_SIZE];
} s21_stack;

typedef struct double_stack {
  int size;
  double data[MAX_SIZE];
} double_stack;

void initialize_stack(s21_stack *stack);
int convert_to_rpn(char *input, s21_stack *rpn_stack);
int eval_expr(s21_stack rpn, double x, double *res);
int s21_pop(s21_stack *stack, char *res);
int s21_push(s21_stack *stack, char *val);
void s21_clear_stack(s21_stack *stack);
int parse_token(char *input, size_t *i, char *token);
int is_digit(char ch);
int is_function(char *input, int i);
int get_priority(char *token);
void s21_peek(s21_stack *stack, char *res);
void push_operator(s21_stack *op_stack, s21_stack *rpn_stack, char *token);
int s21_discard(s21_stack *stack);
int is_char(char ch);
int parse_number(char *input, size_t *i);
int s21_double_push(double_stack *stack, double val);
int s21_double_pop(double_stack *stack, double *res);
int s21_is_number(char *str);
int is_2_operand(char *str);
int eval_operator(char *op, double_stack *result);
int eval_function(char *op, double_stack *result);

#endif
