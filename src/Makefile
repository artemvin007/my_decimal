CC=gcc 
CFLAGS=-Wall -Werror -Wextra -g -std=c11 
LFLAGS=-lcheck -lpthread -pthread -lm 
SRC=$(wildcard *.c) 
OBJ=$(patsubst %.c, %.o, $(SRC)) 
LIBNAME=s21_decimal.a
TEST=tests/*test.c


ifeq ($(shell uname -s),Linux)
	LFLAGS += -lsubunit -lgcov
endif

all: gcov_report

$(LIBNAME): $(OBJ) 
	ar rcs $@ $^

test: $(LIBNAME)
	$(CC) $(CFLAGS) $(TEST) $^ $(LFLAGS) -o $@ 
	./$@

%.o: %.c 
	$(CC) $(CFLAGS) -c $< -o $@

gcov_report: $(LIBNAME)
	$(CC) $(CFLAGS) --coverage *.c $(TEST) $^ $(LFLAGS) -o $@ 
	./$@
	lcov -t "test" -o test_report.info -c -d .
	genhtml -o report test_report.info
	open report/index.html

format:
	cp ../materials/linters/.clang-format .
	clang-format -i *.c *.h tests/*.c tests/*.h
	rm .clang-format

clean: 
	rm -rf *.o $(LIBNAME) test *.info gcov* ./*.gcda ./*.gcno report

leaks: clean test
	clear
ifeq ($(shell uname -s), Linux)
	valgrind --tool=memcheck --leak-check=yes ./test
else
	leaks -atExit -- ./test 
endif
