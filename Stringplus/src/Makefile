CC=gcc
CFLAGS= -Wall -Werror -Wextra -c -g -std=c11
GCOVFLAGS := --coverage
LDFLAGS := -lcheck -fprofile-arcs
ifeq ($(shell uname), Linux)
LDFLAGS +=-pthread -lcheck_pic -lrt -lm -lsubunit
endif
#SOURCES := s21_memchr.c s21_memcmp.c s21_memcpy.c s21_memmove.c s21_memset.c s21_sprintf.c s21_strcat.c s21_strchr.c s21_strcmp.c s21_strcpy.c s21_strcspn.c s21_strerror.c s21_strlen.c s21_strncat.c s21_strncmp.c s21_strncpy.c s21_strpbrk.c s21_strrchr.c s21_strspn.c s21_strstr.c s21_strtok.c s21_void.c
#OBJECTS := $(SOURCES:.c=.o)
Functions_string =\
	s21_memchr\
	s21_memcmp\
	s21_memcpy\
	s21_memmove\
	s21_memset\
	s21_sprintf\
	s21_strcat\
	s21_strchr\
	s21_strcmp\
	s21_strcpy\
	s21_strcspn\
	s21_strerror\
	s21_strlen\
	s21_strncat\
	s21_strncmp\
	s21_strncpy\
	s21_strpbrk\
	s21_strrchr\
	s21_strspn\
	s21_strstr\
	s21_strtok\
	s21_void

all: clean s21_string.a

# .c.o:
# 	$(CC) $(CFLAGS) $< -o $@

s21_string.a:
#$(CC) $(CFLAGS) $(GCOVFLAGS) $(SOURCES) 
	@for function in $(Functions_string); do $(CC) $(CFLAGS) -c $$function.c -o $$function.o; done;
	@-ar rc s21_string.a *.o
	@-rm -rf *.o
#@-ranlib s21_string.a

test: s21_string.a
	$(CC) test.c s21_string.a $(LDFLAGS) -o test.out
	./test.out

gcov_report: test
#@gcovr --html-details report.html
#@open report.html
	for function in $(Functions_string); do $(CC) -c $$function.c $(GCOVFLAGS) $(LDFLAGS) -o $$function.o; done;
	$(CC) *.o test.c $(LDFLAGS) -o test.out
	-./test.out
	gcovr --html-details report.html
	open report.html
#rm -rf *.g* *.o test.c

style: 
	@cppcheck *.c 
	@clang-format -i *.c 

clean:
	@-rm -rf *.o
	@-rm -rf *.a
	@-rm -rf *.gcno
	@-rm -rf *.gcda
	@-rm -rf *.css
	@-rm -rf *.html
	@-rm -rf *.out

