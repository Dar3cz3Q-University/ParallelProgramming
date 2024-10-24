# kompilator c
CCOMP = gcc

# konsolidator
LOADER = gcc

# opcje optymalizacji:
# wersja do debugowania
OPT = -g -DDEBUG
# wersja zoptymalizowana do mierzenia czasu
# OPT = -O3

# pliki naglowkowe
INC = -I../pomiar_czasu

# biblioteki
LIB = -L../pomiar_czasu -lpomiar_czasu -lm

all: fork clone two_threads program

# zaleznosci i komendy
fork: fork.o 
	$(LOADER) $(OPT) fork.o -o fork $(LIB)

# jak uzyskac plik fork.o ?
fork.o: fork.c ../pomiar_czasu/pomiar_czasu.h
	$(CCOMP) -c $(OPT) fork.c $(INC) 

# zaleznosci i komendy
clone: clone.o 
	$(LOADER) $(OPT) clone.o -o clone $(LIB)

# jak uzyskac plik clone.o ?
clone.o: clone.c ../pomiar_czasu/pomiar_czasu.h
	$(CCOMP) -c $(OPT) clone.c $(INC) 

# zaleznosci i komendy
two_threads: two_threads.o 
	$(LOADER) $(OPT) two_threads.o -o two_threads $(LIB)

# jak uzyskac plik two_threads.o ?
two_threads.o: two_threads.c ../pomiar_czasu/pomiar_czasu.h
	$(CCOMP) -c $(OPT) two_threads.c $(INC) 

# zaleznosci i komendy
program: program.o 
	$(LOADER) $(OPT) program.o -o program

# jak uzyskac plik two_threads.o ?
program.o: program.c
	$(CCOMP) -c $(OPT) program.c

clean:
	rm -f *.o fork clone two_threads program
