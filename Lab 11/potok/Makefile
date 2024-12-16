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

all: potok run 

run: potok
	$(MPI_run) -np 5 ./potok

# zaleznosci i komendy
potok : potok.o
	$(LOADER) $(OPT) potok.o -o potok $(LIB)

# jak uzyskac plik moj_program.o ?
potok.o: potok.c 
	$(CCOMP) -c $(OPT) potok.c

clean:
	rm -f *.o potok
