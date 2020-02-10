CXX = g++
FLAGS = -gstabs+

all: proj4.out test1.out test2.out test3.out test4.out test5.out test6.out

test1.out: MinMaxHeap.o test1.cpp
	$(CXX) $(FLAGS)  MinMaxHeap.o test1.cpp -o test1.out
test2.out: MinMaxHeap.o test2.cpp
	$(CXX) $(FLAGS)  MinMaxHeap.o test2.cpp -o test2.out
test3.out: MinMaxHeap.o test3.cpp NoCopyString.cpp
	$(CXX) $(FLAGS)  MinMaxHeap.o test3.cpp NoCopyString.cpp -o test3.out
test4.out: MinMaxHeap.o test4.cpp
	$(CXX) $(FLAGS)  MinMaxHeap.o test4.cpp -o test4.out
test5.out: MinMaxHeap.o test5.cpp
	$(CXX) $(FLAGS)  MinMaxHeap.o test5.cpp -o test5.out
test6.out: MinMaxHeap.o test6.cpp
	$(CXX) $(FLAGS)  MinMaxHeap.o test6.cpp -o test6.out

proj4.out: MinMaxHeap.o Driver.cpp
	$(CXX) $(FLAGS) MinMaxHeap.o Driver.cpp -o proj4.out

MinMaxHeap.o: MinMaxHeap.cpp MinMaxHeap.h
	$(CXX) $(FLAGS) -c MinMaxHeap.cpp

NoCopyString.o: NoCopyString.cpp NoCopyString.h
	$(CXX) $(FLAGS) -c NoCopyString.cpp

run:
	./proj4.out

t1:
	./test1.out
t2:
	./test2.out
t3:
	./test3.out
t4:
	./test4.out
t5:
	./test5.out
t6:
	./test6.out

val:
	valgrind ./proj4.out

val1:
	valgrind ./test1.out
val2:
	valgrind ./test2.out
val3:
	valgrind ./test3.out
val4:
	valgrind ./test4.out
val5:
	valgrind ./test5.out
val6:
	valgrind ./test6.out

clean:
	$(RM) *~
	$(RM) *.o