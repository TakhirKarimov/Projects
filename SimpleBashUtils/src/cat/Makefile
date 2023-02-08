CC=gcc
WFLAGS=-Wall -Werror -Wextra
DFLAGS=
STD=-std=c11
EXE=s21_cat

all: s21_cat rm_ofile

s21_cat: s21_cat.o
	$(CC) s21_cat.o -o $(EXE)

s21_cat.o: s21_cat.c 
	$(CC) $(WFLAGS) $(STD) -c s21_cat.c

rm_ofile:
	rm -rf *.o

clean:
	rm -rf *.o *.a $(EXE)

rebuild: clean all