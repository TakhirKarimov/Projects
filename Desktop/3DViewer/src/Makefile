FLAGS=-Wall -Wextra -Werror -std=c11 #-fsanitize=address -pedantic
LIBS=-lcheck
OS:=$(shell uname -s)
ifeq ($(OS), Darwin)
	FLAGS += -D MACOS
	OPEN = open
	RUN = open ./build/3DViewer.app/
else
	LIBS += -lsubunit -lrt -lm -lpthread -fprofile-arcs
	OPEN = xdg-open
	RUN = ./build/3DViewer
endif

TEMP_DIR = temp
TEST_DIR = tests_src
REPORT_DIR = $(TEMP_DIR)/report
OBJ_DIR = $(TEMP_DIR)/obj

rebuild: clean all

all: install

install:
	mkdir -p build
	cd 3DViewer && cmake -S ./ -B ../build
	cd build && $(MAKE)

run: install
	$(RUN)

uninstall: clean
	rm -rf build/	

dvi:
	cd docs && latex dvi.tex

dist: install
	tar -cf 3DViewer-1.0.tar build/*

test: clean $(OBJ_DIR)
	gcc $(FLAGS) -c --coverage ./modules/s21_3dviewer.c -o $(OBJ_DIR)/s21_3dviewer.o
	gcc $(FLAGS) -c --coverage ./modules/s21_transformations.c -o $(OBJ_DIR)/s21_transformations.o
	gcc $(FLAGS) -c $(TEST_DIR)/test_s21_viewer_read.c -o $(OBJ_DIR)/test_s21_viewer_read.o
	gcc $(FLAGS) -c $(TEST_DIR)/test_s21_viewer_transformations.c -o $(OBJ_DIR)/test_s21_viewer_transformations.o
	gcc $(FLAGS) -c $(TEST_DIR)/test.c -o $(OBJ_DIR)/test.o
	gcc $(FLAGS) --coverage -o test $(OBJ_DIR)/s21_transformations.o $(OBJ_DIR)/test_s21_viewer_transformations.o $(OBJ_DIR)/test.o $(OBJ_DIR)/test_s21_viewer_read.o $(OBJ_DIR)/s21_3dviewer.o $(LIBS)
	./test
	
gcov_report: test $(REPORT_DIR)
	gcovr -r . --html --html-details -o $(REPORT_DIR)/report.html
	$(OPEN) $(REPORT_DIR)/report.html

clean:
	@rm -rf *.o *.a *.css *.html *.gcda *.gcno test
	@rm -rf tests tests_gcov build* ./3DViewer/*txt.user 3DViewer-1.0.tar
	@rm -rf docs/*.aux docs/*.dvi docs/*.pdf docs/*.log *.log
	@rm -rf $(TEMP_DIR)

$(REPORT_DIR):
	@mkdir -p $(REPORT_DIR)
	
$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)
	@mkdir -p $(OBJ_DIR)/test

clf:
	clang-format -n --style=Google modules/*.[ch]
	clang-format -n --style=Google 3DViewer/*.[cpp,h]
	clang-format -n --style=Google tests_src/*.[ch]

cpk:
	cppcheck modules/*.[ch]
	cppcheck tests_src/*.[ch]
	cppcheck --language=c++ 3DViewer/*.[cpp,h]

style: clf cpk