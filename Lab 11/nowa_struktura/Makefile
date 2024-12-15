# kompilator c
CCOMP = /usr/bin/mpicc

# konsolidator
LOADER = /usr/bin/mpicc

# program uruchomieniowy MPI
MPI_run = /usr/bin/mpiexec -oversubscribe

# opcje optymalizacji:
# wersja do debugowania
OPT = -g -DDEBUG
# wersja zoptymalizowana do mierzenia czasu
# OPT = -O3

# pliki naglowkowe
#INC = -I../pomiar_czasu

# biblioteki
#LIB = -L../pomiar_czasu -lm
LIB = -lm

all: nowa_struktura run 

run: nowa_struktura
	$(MPI_run) -np 5 ./nowa_struktura

# zaleznosci i komendy
nowa_struktura : nowa_struktura.o
	$(LOADER) $(OPT) nowa_struktura.o -o nowa_struktura $(LIB)

# jak uzyskac plik moj_program.o ?
nowa_struktura.o: nowa_struktura.c 
	$(CCOMP) -c $(OPT) nowa_struktura.c

clean:
	rm -f *.o nowa_struktura
