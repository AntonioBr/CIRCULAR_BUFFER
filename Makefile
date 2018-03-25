CXXFLAGS = -DNDEBUG

main.exe: main.o 
	g++ main.o -o main.exe

main.o: main.cpp
	g++ $(CXXFLAGS) -c main.cpp -o main.o

.PHONY: clean, ndexec, valgrindexec, doxyhtml

clean:
	rm *.exe *.o

exec:
	./main.exe

valgrindexec:
	valgrind ./main.exe

doxyhtml:
	doxygen Doxyfile

