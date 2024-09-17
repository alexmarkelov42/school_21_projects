CC = gcc
CFLAGS = -Wall -Werror -Wextra -std=c11
TEST_LIBS = -lcheck -lm -lpthread
OBJECTS = s21_sprintf.o s21_string.o
SOURSES = s21_sprintf.c s21_string.c
GCOVFLAGS = -fprofile-arcs -ftest-coverage



all: clean s21_string.a test

s21_string.a: s21_string.o
	$(CC) $(CFLAGS) -g -c  $(SOURSES)
	ar rcs s21_string.a $(OBJECTS)

clean:
	rm -rf ./*.o ./*.a ./a.out gcov_test *.html *.css ./GcovReport ./*.gcno ./*.gcda ./report ./*.info ./sprintf_o ./string_o ./*.dSYM ./s21_string_test ./CPPLINT* test

test: test.c s21_string.a
	$(CC) $(CFLAGS) -c test.c -o test.o
	$(CC) $(CFLAGS) -g test.o s21_string.a $(TEST_LIBS) -o test

gcov_report: s21_string.a
	$(CC) $(CFLAGS) --coverage test.c s21_string.c s21_sprintf.c s21_string.a $(TEST_LIBS) -o gcov_test
	chmod +x *
	./gcov_test
	lcov -t "gcov_test" -o gcov_test.info --no-external -c -d .
	genhtml -o report/ gcov_test.info
	open ./report/index.html

check: s21_string.a
	cppcheck *.h *.c
	cp ../materials/linters/CPPLINT.cfg CPPLINT.cfg
	python3 ../materials/linters/cpplint.py --extension=c *.c *.h
	$(CC) test.c s21_string.a -lcheck
	$(CC) $(CFLAGS) -c test.c -o test.o
	$(CC) test.o s21_string.a $(TEST_LIBS) -o test
	CK_FORK=no leaks --atExit -- ./test

rebuild: clean all

prosto:
	gcc -g s21_sprintf.c s21_string.c prosto.c -o valg.out

mini_grind:test
	valgrind -q --leak-check=full --track-origins=yes ./test