CXXFLAGS=-Wall -Wextra -Werror -Wpedantic -std=c++17 -fprofile-arcs -ftest-coverage -fstack-protector-all -g
SOURCES=s21_matrix_oop.cc
HEADERS=s21_matrix_oop.h

all: clean s21_matrix_oop.a

s21_matrix_oop.a:
	g++ $(CXXFLAGS) -c $(SOURCES) -o s21_matrix_oop.o
	ar rcs s21_matrix_oop.a s21_matrix_oop.o

test: clean test.cc s21_matrix_oop.a
	g++ $(CXXFLAGS) test.cc s21_matrix_oop.a s21_matrix_oop.h -o test.out -lgtest
	./test.out
gcov_report: clean s21_matrix_oop.a
	g++ $(CXXFLAGS) test.cc s21_matrix_oop.h s21_matrix_oop.cc -o gcov_test.out -lgtest
	./gcov_test.out
	gcov $(SOURCES)
	lcov --capture --directory . --output-file gcov_test.info --ignore-errors mismatch
	genhtml -o report/ gcov_test.info

clean:
	-rm -r *.o *.out s21_matrix_oop.a ./report *.gcda *.gcno *.info *.gcov
valgrind:
	valgrind --leak-check=full --track-origins=yes --show-leak-kinds=all ./test.out
