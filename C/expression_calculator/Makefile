CC=gcc
CFLAGS = -Wall -Wextra -Werror -Wpedantic -pedantic-errors -std=c11 -lm -g
TEST_LIBS = -lcheck
GUI_FLAGS=`pkg-config --libs --cflags gtk+-3` -export-dynamic
TEXI2DVI=texi2dvi
OS=$(shell uname)


ifeq ($(OS), Darwin)
	open_command=open help.txt
else
	open_command=xdg-open help.txt
endif

all: test smart_calc_1_0.a

smart_calc_1_0.a: smart_calc_1_0.c
	$(CC) $(CFLAGS) -c smart_calc_1_0.c
	ar rcs smart_calc_1_0.a smart_calc_1_0.o

clean:
	-rm -r ./*.o ./*.a gcov_test ./*.gcno ./*.gcda ./report ./*.info ./*.dSYM ./build/ *.tar.gz ./smartcalc-1.0 test

install: gui
	-mkdir build
	mv SmartCalc_1_0.out ./build
	cp smartcalc.glade ./build

uninstall:
	rm -r ./build


test: test.c smart_calc_1_0.a
	$(CC) $(CFLAGS) -c test.c -o test.o $(TEST_LIBS)
	$(CC) $(CFLAGS) test.o smart_calc_1_0.a $(TEST_LIBS) -o test
	./test

localtest: localtest.c smart_calc_1_0.a
	$(CC) $(CFLAGS) localtest.c smart_calc_1_0.a -o localtest.out
	./localtest.out

gcov_report: smart_calc_1_0.a
	$(CC) $(CFLAGS) --coverage test.c smart_calc_1_0.c smart_calc_1_0.a $(TEST_LIBS) -o gcov_test
	./gcov_test
	lcov -t "gcov_test" -o gcov_test.info --no-external -c -d .
	genhtml -o report/ gcov_test.info

rebuild: clean all

gui: smart_calc_1_0.a
	gcc $(CFLAGS) smart_calc_gui.c smart_calc_1_0.c smart_calc_1_0.a  -o SmartCalc_1_0.out -export-dynamic -lm `pkg-config --libs --cflags gtk+-3.0`

dist:
	-mkdir smartcalc-1.0
	cp smartcalc.glade test.c smart_calc_1_0.c smart_calc_1_0.h smart_calc_gui.c Makefile smartcalc-1.0/
	gzip -r smartcalc-1.0/*
	tar -czvf smartcalc.tar.gz smartcalc-1.0/*
dvi:
	$(open_command)
