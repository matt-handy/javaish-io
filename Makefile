CC=g++
MAKE=make
INCLUDE=./include
GTEST_LOC=../Common/gtest-1.7.0

default:
	-rm libjavaish-io.a
	$(CC) -I$(INCLUDE) -Wall -c src/*.cpp
	ar -cvq libjavaish-io.a *.o
	$(CC) -I$(GTEST_LOC)/include -I$(INCLUDE) -Wall -c test/*.cpp
	$(CC) -pthread -o all_tests ConfigurationTest.o $(GTEST_LOC)/make/gtest_main.a libjavaish-io.a
	rm *.o
