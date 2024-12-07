CC = gcc

LD = gcc

OPT = -O3

INC = -fopenmp

LIB = -fopenmp

all: openmp_petle openmp_petle_simple

openmp_petle_simple: openmp_petle_simple.o
	$(LD) $(OPT) -o openmp_petle_simple openmp_petle_simple.o $(LIB)

openmp_petle_simple.o: openmp_petle_simple.c
	$(CC) -c $(OPT) openmp_petle_simple.c $(INC)

openmp_petle: openmp_petle.o
	$(LD) $(OPT) -o openmp_petle openmp_petle.o $(LIB)

openmp_petle.o: openmp_petle.c
	$(CC) -c $(OPT) openmp_petle.c $(INC)

clean:
	rm -f *.o openmp_petle_simple openmp_petle
