CC=gcc
CFLAGS=-Wall -Werror -Wextra -std=c11 -pedantic
GCOV_FLAGS=-fprofile-arcs -ftest-coverage -lgcov
CHECK_FLAGS=-lcheck -lm -lpthread
ALL_FLAGS=$(CFLAGS) $(GCOV_FLAGS) $(CHECK_FLAGS)
SRCS =  s21_add.c \
		s21_sub.c \
		s21_mul.c \
		s21_mod.c \
		s21_cmp.c \
		s21_from_int_to_decimal.c \
		s21_from_float_to_decimal.c \
		s21_from_decimal_to_int.c \
		s21_from_decimal_to_float.c \
		s21_floor.c \
		s21_round.c \
		s21_truncate.c \
		s21_negate.c \
		s21_dbinary.c \
		s21_div.c
OBJS = $(SRCS:.c=.o) s21_decimal_tests.c
OBJST = $(SRCS:.c=.o)
NAME = test
REPORT_NAME = report

all: objs s21_decimal.a
# %.o: %.c
# $(CC) $(CFLAGS) $(CHECK_FLAGS) -c $< -o $@
test: $(OBJS)
	$(CC) $(CHECK_FLAGS) $(OBJS) -o $(NAME)
	make clean
clean_all:
	rm -rf $(OBJST)
	rm -rf *.o
	rm -rf *.gcno
	rm -rf *.gcda
	rm -rf *.info
	rm -rf *.a
	rm -rf $(REPORT_NAME)
	rm $(NAME)
clean:
	rm -rf $(OBJST)
	rm -rf *.o
	rm -rf *.gcno
	rm -rf *.gcda
	rm -rf *.info
objs: $(SRCS)
	$(CC) $(CFLAGS) -c $(SRCS) s21_div.c
s21_decimal.a: objs
	ar rc s21_decimal.a $(OBJST)
	ranlib s21_decimal.a
gcov_report:
	$(CC) -o $(NAME) $(SRCS) s21_decimal_tests.c $(GCOV_FLAGS) $(CHECK_FLAGS)
	./$(NAME)
	lcov -t "gcov_report" -o s21_decimal_tests.info -c -d .
	genhtml -o $(REPORT_NAME) s21_decimal_tests.info
	rm $(NAME)
	make clean
