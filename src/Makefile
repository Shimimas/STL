CPP = g++ -std=c++17 -lstdc++
TESTTARGET = s21_test
CFLAGS = -Wall -Werror -Wextra
COV_FALGS= -fprofile-arcs -ftest-coverage
GTEST=`pkg-config --cflags --libs gtest`

OS=$(shell uname)

ifeq ($(OS), Linux)
	OPEN = xdg-open
	LIBS= -lgtest -lpthread -pthread -lrt -lm -lsubunit
	LEAKS= valgrind --track-origins=yes --leak-check=full  ./$(TESTTARGET)
else
	OPEN = open
	LIBS=-lcheck -lgtest -pthread
	LEAKS=leaks --atExit -- ./$(TESTTARGET)
endif

all: clean test

$(TESTTARGET):
	$(CPP) $(CFLAGS) $(LIBS) s21_test.cpp -lgtest -o $@

test: $(TESTTARGET)
	$(LEAKS)

gcov_report: clean
	-mkdir report
	$(CPP) $(COV_FALGS) s21_test.cpp $(GTEST) -o $(TESTTARGET)
	./$(TESTTARGET)
	gcov test_gcov
	lcov -t "s21_containers" -o s21_constainers.info -c -d .
	genhtml -o report s21_constainers.info
	$(OPEN) ./report/index.html

clean:	
	rm -rf s21_vector s21_vector s21_test
	rm -rf *.o *.so *.a fizz *.gc* *.info report *.out *.gcda *.so *.gcno *.info
	rm -rf test/*.o test/*.so test/*.a  test/*.gcda  test/*.so  test/*.gcno  test/*.info test/s21_vector

rebuild: clean all

cpplint:
	cp ../materials/linters/.clang-format . 
	clang-format -i  *.cpp *.h
	clang-format -n *.cpp *.h

checks:
	$(LEAKS)
	
.PHONY: all clean test s21_vector.a
