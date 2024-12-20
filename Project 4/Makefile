project4.exe: project4.o FIFOQueueClass.o LIFOStackClass.o SortedListClass.o LinkedNodeClass.o
	g++ project4.o FIFOQueueClass.o LIFOStackClass.o SortedListClass.o LinkedNodeClass.o -o project4.exe

project4.0: project4.cpp FIFOQueueClass.h LIFOStackClass.h SortedListClass.h LinkedNodeClass.h
	g++ -std=c++98 -Wall -c project4.cpp -o project4.o

FIFOQueueClass.o: FIFOQueueClass.cpp FIFOQueueClass.h LinkedNodeClass.h
	g++ -std=c++98 -Wall -c FIFOQueueClass.cpp -o FIFOQueueClass.o

LIFOStackClass.o: LIFOStackClass.cpp LIFOStackClass.h LinkedNodeClass.h
	g++ -std=c++98 -Wall -c LIFOStackClass.cpp -o LIFOStackClass.o

SortedListClass.o: SortedListClass.cpp SortedListClass.h LinkedNodeClass.h
	g++ -std=c++98 -Wall -c SortedListClass.cpp -o SortedListClass.o

LinkedNodeClass.o: LinkedNodeClass.cpp LinkedNodeClass.h
	g++ -std=c++98 -Wall -c LinkedNodeClass.cpp -o LinkedNodeClass.o

clean:
	rm -f *.o project4.exe
