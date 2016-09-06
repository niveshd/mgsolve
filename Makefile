
all:mgsolve.o grid.o gauss_seidel.o vsolve.o
	g++ -O3 -Wall -Winline -Wshadow -std=c++11 grid.o mgsolve.o gauss_seidel.o vsolve.o -o mgsolve

mgsolve.o:mgsolve.cpp include/grid.h include/gauss_seidel.h include/vsolve.h
	g++ -O3 -Wall -Winline -Wshadow -std=c++11 -c mgsolve.cpp

grid.o:src/grid.cpp include/grid.h
	g++ -O3 -Wall -Winline -Wshadow -std=c++11 -c ./src/grid.cpp

gauss_seidel.o:src/gauss_seidel.cpp include/gauss_seidel.h include/grid.h
	g++ -O3 -Wall -Winline -Wshadow -std=c++11 -c ./src/gauss_seidel.cpp

vsolve.o:src/vsolve.cpp include/vsolve.h include/gauss_seidel.h include/grid.h
	g++ -O3 -Wall -Winline -Wshadow -std=c++11 -c ./src/vsolve.cpp

.PHONY:test clean all

test:
	g++ -O3 -Wall -Winline -Wshadow -std=c++11 -c mgsolve.cpp
	g++ -O3 -Wall -Winline -Wshadow -std=c++11 -c ./src/grid.cpp
	g++ -O3 -Wall -Winline -Wshadow -std=c++11 -c ./src/gauss_seidel.cpp
	g++ -O3 -Wall -Winline -Wshadow -std=c++11 -c ./src/vsolve.cpp
	g++ -O3 -Wall -Winline -Wshadow -std=c++11 grid.o mgsolve.o gauss_seidel.o vsolve.o -o mgsolve
	./mgsolve 6 10
	
gprof:
	g++ -O3 -pg -Wall -Winline -Wshadow -std=c++11 -c mgsolve.cpp
	g++ -O3 -pg -Wall -Winline -Wshadow -std=c++11 -c ./src/grid.cpp
	g++ -O3 -pg -Wall -Winline -Wshadow -std=c++11 -c ./src/gauss_seidel.cpp
	g++ -O3 -pg -Wall -Winline -Wshadow -std=c++11 -c ./src/vsolve.cpp
	g++ -O3 -pg -Wall -Winline -Wshadow -std=c++11 grid.o mgsolve.o gauss_seidel.o vsolve.o -o mgsolve_gprof

clean:
	rm -f *.o
	rm -f *.txt
