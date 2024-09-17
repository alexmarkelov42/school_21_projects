FLAGS = -Wall -Wextra -Werror -Wpedantic -pedantic-errors -std=c11
all: clean build
clean:
	-rm s21_cat
	-rm *.txt
build: s21_cat

s21_cat: s21_cat.c
	gcc $(FLAGS) s21_cat.c -o s21_cat
