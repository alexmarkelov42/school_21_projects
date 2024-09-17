FLAGS = -Wall -Wextra -Werror -Wpedantic -pedantic-errors -std=c11 -D_GNU_SOURCE
all: clean build
clean:
	-rm s21_grep
	-rm test*.txt
build: s21_grep

s21_grep: s21_grep.c
	gcc $(FLAGS) s21_grep.c -o s21_grep
