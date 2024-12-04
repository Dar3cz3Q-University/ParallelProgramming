CC = gcc

LD = gcc

OPT = -O3

INC = -fopenmp

LIB = -fopenmp

openmp_petle_simple: openmp_petle_simple.o
	$(LD) $(OPT) -o openmp_petle_simple openmp_petle_simple.o $(LIB)

openmp_petle_simple.o: openmp_petle_simple.c
	$(CC) -c $(OPT) openmp_petle_simple.c $(INC)

clean:
	rm -f *.o openmp_petle_simple
