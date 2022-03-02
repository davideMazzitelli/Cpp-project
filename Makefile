 

main.exe : main.o my_exceptions.o
	g++ main.o my_exceptions.o -o main.exe -std=c++0x


main.o : main.cpp progetto.h 
	g++ -c main.cpp -o main.o -std=c++0x


my_exceptions.o : my_exceptions.cpp
	g++ -c my_exceptions.cpp -o my_exceptions.o -std=c++0x


.PHONY: clean
clean:
	rm -rf *.o *.exe

