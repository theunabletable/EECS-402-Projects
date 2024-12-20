proj3.exe: project3.o ColorClass.o ImageColorClass.o PatternClass.o RectangleClass.o getValidInput.o
	g++ project3.o ColorClass.o ImageColorClass.o PatternClass.o RectangleClass.o getValidInput.o -o proj3.exe

project3.o: project3.cpp ColorClass.h ImageColorClass.h PatternClass.h RectangleClass.h getValidInput.h constants.h
	g++ -std=c++98 -Wall -c project3.cpp -o project3.o

ColorClass.o: ColorClass.cpp ColorClass.h constants.h getValidInput.h
	g++ -std=c++98 -Wall -c ColorClass.cpp -o ColorClass.o

ImageColorClass.o: ImageColorClass.cpp ImageColorClass.h ColorClass.h PatternClass.h RectangleClass.h constants.h
	g++ -std=c++98 -Wall -c ImageColorClass.cpp -o ImageColorClass.o

PatternClass.o: PatternClass.cpp PatternClass.h constants.h
	g++ -std=c++98 -Wall -c PatternClass.cpp -o PatternClass.o

RectangleClass.o: RectangleClass.cpp RectangleClass.h ColorClass.h constants.h
	g++ -std=c++98 -Wall -c RectangleClass.cpp -o RectangleClass.o

getValidInput.o: getValidInput.cpp getValidInput.h
	g++ -std=c++98 -Wall -c getValidInput.cpp -o getValidInput.o

clean:
	rm -f *.o proj3.exe
