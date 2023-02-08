CC=gcc
CFLAGS= -Wall -Werror -Wextra -c -g -std=c11
GCOVFLAGS := --coverage
LDFLAGS := -lcheck -fprofile-arcs
ifeq ($(shell uname), Linux)
LDFLAGS +=-pthread -lcheck_pic -lrt -lm -lsubunit
endif
Functions_matrix =\
	s21_calc_complements\
	s21_create_matrix\
	s21_determinant\
	s21_eq_matrix\
	s21_sub_matrix\
	s21_inverse_matrix\
	s21_mult_matrix\
	s21_mult_number\
	s21_remove_matrix\
	s21_sum_matrix\
	s21_transpose\

all: clean s21_matrix.a

s21_matrix.a:
	@for function in $(Functions_matrix);do $(CC) $(CFLAGS) -c $$function.c -o $$function.o; done;
	@-ar rc s21_matrix.a *.o
	@-rm -rf *.o

test: s21_matrix.a
	$(CC) test.c s21_matrix.a $(LDFLAGS) -o test.out
	./test.out

gcov_report: test
	for function in $(Functions_matrix); do $(CC) -c $$function.c $(GCOVFLAGS) $(LDFLAGS) -o $$function.o; done;
	$(CC) *.o test.c $(LDFLAGS) -o test.out
	-./test.out
	gcovr --html-details report.html

clean:
	@-rm -rf *.o
	@-rm -rf *.a
	@-rm -rf *.gcno
	@-rm -rf *.gcda
	@-rm -rf *.css
	@-rm -rf *.html
	@-rm -rf *.out


