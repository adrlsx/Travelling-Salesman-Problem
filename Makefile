#
# In order to execute this "Makefile" just type "make"
#	File generated thanks to https://www.nicomedes.assistedcoding.eu/#/app/makefilegen
#

OBJS	= main.o Constructive/Source/ConstructiveHeuristic.o Exact/Source/ExactAlgorithm.o UndirectedCompleteGraph.o Local_Search/Source/LocalSearchHeuristic.o ArgumentParser.o OptionProcess.o Grasp/Source/Grasp.o
SOURCE	= main.cpp Constructive/Source/ConstructiveHeuristic.cpp Exact/Source/ExactAlgorithm.cpp UndirectedCompleteGraph.cpp Local_Search/Source/LocalSearchHeuristic.cpp ArgumentParser.cpp OptionProcess.cpp Grasp/Source/Grasp.cpp
HEADER	= Constructive/Source/ConstructiveHeuristic.h Exact/Source/ExactAlgorithm.h UndirectedCompleteGraph.h Local_Search/Source/LocalSearchHeuristic.h ArgumentParser.h OptionProcess.h Grasp/Source/Grasp.h
OUT	= Travelling_Salesman_Problem
CC	 = g++
FLAGS	 = -O3 -c
LFLAGS	 = -std=c++17
# -g option enables debugging mode
# -c flag generates object code for separate files
# -O3 turns on all optimizations


all: $(OBJS)
	$(CC) -O3 $(OBJS) -o $(OUT) $(LFLAGS)


# create/compile the individual files >>separately<<
main.o: main.cpp
	$(CC) $(FLAGS) main.cpp $(LFLAGS)

ConstructiveHeuristic.o: Constructive/Source/ConstructiveHeuristic.cpp
	$(CC) $(FLAGS) Constructive/Source/ConstructiveHeuristic.cpp $(LFLAGS)

ExactAlgorithm.o: Exact/Source/ExactAlgorithm.cpp
	$(CC) $(FLAGS) Exact/Source/ExactAlgorithm.cpp $(LFLAGS)

UndirectedCompleteGraph.o: UndirectedCompleteGraph.cpp
	$(CC) $(FLAGS) UndirectedCompleteGraph.cpp $(LFLAGS)

LocalSearchHeuristic.o: Local_Search/Source/LocalSearchHeuristic.cpp
	$(CC) $(FLAGS) Local_Search/Source/LocalSearchHeuristic.cpp $(LFLAGS)

ArgumentParser.o: ArgumentParser.cpp
	$(CC) $(FLAGS) ArgumentParser.cpp $(LFLAGS)

OptionProcess.o: OptionProcess.cpp
	$(CC) $(FLAGS) OptionProcess.cpp $(LFLAGS)

Grasp.o: Grasp/Source/Grasp.cpp
	$(CC) $(FLAGS) Grasp/Source/Grasp.cpp $(LFLAGS)


# clean house
clean:
	rm -f $(OBJS) $(OUT)

# rebuild the project
rebuild: clean all

# compile program with debugging information
debug: $(OUT)
	valgrind $(OUT)

# run program with valgrind for errors
valgrind: $(OUT)
	valgrind $(OUT)

# run program with valgrind for leak checks
valgrind_leakcheck: $(OUT)
	valgrind --leak-check=full $(OUT)

# run program with valgrind for leak checks (extreme)
valgrind_extreme: $(OUT)
	valgrind --leak-check=full --show-leak-kinds=all --leak-resolution=high --track-origins=yes --vgdb=yes $(OUT)