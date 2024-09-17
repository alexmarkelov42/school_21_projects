CC=gcc
CFLAGS = -Wall -Wextra -Werror -Wpedantic -pedantic-errors -std=c11 -lm -g
TEST_LIBS = -lcheck

all: test s21_matrix.a

s21_matrix.a: s21_matrix.c
	$(CC) $(CFLAGS) -c s21_matrix.c
	ar rcs s21_matrix.a s21_matrix.o

clean:
	rm -rf ./*.o ./*.a ./a.out gcov_test *.html *.css ./GcovReport ./*.gcno ./*.gcda ./report ./*.info ./sprintf_o ./matrix_o ./*.dSYM ./s21_matrix_test ./CPPLINT* test

test: test.c s21_matrix.a
	$(CC) $(CFLAGS) -c test.c -o test.o $(TEST_LIBS)
	$(CC) $(CFLAGS) test.o s21_matrix.a $(TEST_LIBS) -o test

localtest: localtest.c s21_matrix.a
	$(CC) $(CFLAGS) localtest.c s21_matrix.a -o localtest.out
	./localtest.out

gcov_report: s21_matrix.a
	$(CC) $(CFLAGS) --coverage test.c s21_matrix.c s21_matrix.a $(TEST_LIBS) -o gcov_test
	./gcov_test
	lcov -t "gcov_test" -o gcov_test.info --no-external -c -d .
	genhtml -o report/ gcov_test.info

rebuild: clean all
