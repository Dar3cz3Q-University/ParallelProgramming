# kompilator c
CCOMP = gcc

# konsolidator
LOADER = gcc

# opcje optymalizacji:
# wersja do debugowania
#OPT = -g -DDEBUG
# wersja zoptymalizowana do mierzenia czasu
OPT = -O3 -fopenmp

# pliki naglowkowe
INC = 

# biblioteki
LIB = 

# zaleznosci i komendy

calka_omp: calka_omp.o
	$(LOADER) $(OPT) calka_omp.o -o calka_omp $(LIB)

calka_omp.o: calka_omp.c 
	$(CCOMP) -c $(OPT) calka_omp.c $(INC) 

clean:
	rm -f *.o calka_omp
