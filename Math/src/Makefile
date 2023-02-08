
CC = gcc
FLAGS = -Wall -Wextra -Werror -std=c11
TST_LIBS = -lcheck -lm

GCOVR_COVERAGE = --coverage
LCOV_COVERAGE = -fprofile-arcs -ftest-coverage -lgcov

SRCS= s21_math.c s21_trig.c s21_power.c s21_rounding.c

OBJS=$(SRCS:.c=.o)

LIB_NAME = s21_math

all: clean test

clean:
	rm -rf *.o test *.a *.gcno *.gcda *.gcov *.html *.css *.info report

%.o: %.c
	$(CC) $(FLAGS) -c -g $< -o $@

#создание статической библиотеки
$(LIB_NAME).a: $(OBJS)
#создание библиотеки из объектных файлов
	ar rc $(LIB_NAME).a $^
#чтобы сделать архив полноценной библиотекой объектных файлов, надо добавить к файлу индекс символов 
#т.е. список вложенных в библиотеку функций и переменных, чтобы линковка происходила быстрее
	ranlib $(LIB_NAME).a
	rm -rf *.o

#компиляция файла и тестирование
test: clean $(LIB_NAME).a
#для компиляции нужно сообщить компилятору, что надо использовать библиотеки
#каталог с библиотеками указывается ключом -L.
#компилируем вместе с тестом
	$(CC) $(FLAGS) -g s21_math_test_1.c $(LIB_NAME).a $(TST_LIBS) -o test

gcov_report: clean
	$(CC) $(FLAGS) $(GCOVR_COVERAGE) -g s21_math_test_1.c $(SRCS) $(TST_LIBS) -o test
	./test
	gcov -b -l -p -c *.gcno
	gcovr -o gcov_report.html --html --html-details

lcov_report: clean
	$(CC) $(FLAGS) $(LCOV_COVERAGE) -o test $(SRCS) s21_math_test_1.c $(TST_LIBS)
	./test
	lcov -t "gcov_report" -o s21_math_tests.info -c -d .
	genhtml -o report s21_math_tests.info
	rm report
	make clean


style: clean
	clang-format -i *.c *.h
	clang-format -n *.c *.h
