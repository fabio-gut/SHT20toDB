.SUFFIXES:
.PHONY: compile test checkstyle clean valgrind
.PRECIOUS: *.o

CXX = g++ -g -Wall -pedantic -std=c++11 -I/usr/include/mariadb -I./src
ADDITIONAL_LIBS = -lmariadb -lmariadbclient
TEST_LIBS = -lgtest -lgtest_main -lpthread
SRCDIR = src
HEADERS = $(wildcard $(SRCDIR)/*.h)
OBJECTS = $(addsuffix .o, $(basename $(filter-out %Main.cpp %Test.cpp, $(wildcard $(SRCDIR)/*.cpp))))
MAINS = $(basename $(wildcard $(SRCDIR)/*Main.cpp))
TESTS = $(basename $(wildcard $(SRCDIR)/*Test.cpp))

all: compile copy checkstyle test

compile: $(MAINS) $(TESTS)

copy: $(MAINS)
	cp $^ $(subst Main,,$(notdir $^))

checkstyle:
	./cpplint.py --root=$(SRCDIR) *.cpp *.h

clean:
	rm -f $(SRCDIR)/*.o
	rm -f $(SRCDIR)/*Main
	rm -f *Main
	rm -f *Test
	rm -f $(subst Main,,$(notdir $(MAINS)))

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
	$(CXX) -c $< -o $@
