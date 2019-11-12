.SUFFIXES:
.PHONY: compile test checkstyle clean valgrind
.PRECIOUS: *.o

CXX = g++ -g -Wall -pedantic -std=c++11
ADDITIONAL_LIBS =
TEST_LIBS = -lgtest -lgtest_main -lpthread
HEADERS = $(wildcard *.h)
OBJECTS = $(addsuffix .o, $(basename $(filter-out %Main.cpp %Test.cpp, $(wildcard *.cpp))))
MAINS = $(basename $(wildcard *Main.cpp))
TESTS = $(basename $(wildcard *Test.cpp))

all: compile checkstyle test

compile: $(MAINS) $(TESTS)

checkstyle:
	./cpplint.py --repository=. *.cpp *.h

clean:
	rm -f *.o
	rm -f *Main
	rm -f *Test

valgrind: $(TESTS) $(MAINS)
	for T in $(TESTS); do valgrind --leak-check=full --track-origins=yes --show-leak-kinds=all ./$$T; done
	for M in $(MAINS); do valgrind --leak-check=full --track-origins=yes --show-leak-kinds=all ./$$M; done

test: $(TESTS)
	for T in $(TESTS); do ./$$T; done

%Main: %Main.o $(OBJECTS)
	$(CXX) -o $@ $^ $(ADDITIONAL_LIBS)

%Test: %Test.o $(OBJECTS)
	$(CXX) -o $@ $^ $(TEST_LIBS) $(ADDITIONAL_LIBS)

%.o: %.cpp $(HEADERS)
	$(CXX) -c $<
