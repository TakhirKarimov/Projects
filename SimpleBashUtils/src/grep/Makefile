CC=gcc
WFLAGS=-Wall -Werror -Wextra
DFLAGS=
STD=-std=c11
EXE=s21_grep

all: s21_grep clean_o

s21_cat: s21_grep.o
	$(CC) s21_grep.o -o $(EXE)

s21_cat.o: s21_grep.c 
	$(CC) $(WFLAGS) $(STD) -c s21_grep.c
clean_o:
	rm -rf s21_grep.o

clean:
	rm -rf *.o *.a $(EXE)

rebuild: clean all