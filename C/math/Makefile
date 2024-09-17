CC = gcc
CFLAGS = -Wall -Werror -Wextra -std=c11 -Wpedantic -pedantic-errors
TEST_LIBS = -lcheck -lm -lpthread
OBJECTS = s21_math.o
SOURSES = s21_math.c
GCOVFLAGS = -fprofile-arcs -ftest-coverage

all: clean s21_math.a test

s21_math.a: s21_math.o
	$(CC) $(CFLAGS) -g -c  $(SOURSES)
	ar rcs s21_math.a $(OBJECTS)
	ranlib s21_math.a

clean:
	rm -rf ./*.o ./*.a ./a.out gcov_test *.html *.css ./GcovReport ./*.gcno ./*.gcda ./report ./*.info ./sprintf_o ./string_o ./*.dSYM ./s21_math_test ./CPPLINT* test

test: test.c s21_math.a
	$(CC) $(CFLAGS) -c test.c $(TEST_LIBS) -o test.o
	$(CC) $(CFLAGS) -g test.o s21_math.a $(TEST_LIBS) -o test
	./test

gcov_report: s21_math.a
	$(CC) $(CFLAGS) --coverage test.c s21_math.c s21_math.a $(TEST_LIBS) -o gcov_test
	chmod +x *
	./gcov_test
	lcov -t "gcov_test" -o gcov_test.info --no-external -c -d .
	genhtml -o report/ gcov_test.info
	open ./report/index.html

check: s21_math.a
	cppcheck *.h *.c
	cp ../materials/linters/CPPLINT.cfg CPPLINT.cfg
	python3 ../materials/linters/cpplint.py --extension=c *.c *.h
	$(CC) test.c s21_math.a -lcheck
	$(CC) $(CFLAGS) -c test.c -o test.o
	$(CC) test.o s21_math.a $(TEST_LIBS) -o test
	CK_FORK=no leaks --atExit -- ./test

rebuild: clean all

localtest:
	gcc -g s21_math.c local_test.c -o local_test.out
	./local_test.out

mini_grind:test
	valgrind -q --leak-check=full --track-origins=yes ./test

graph:
	gcc -shared -o libafunc.so -fPIC afunc.c
