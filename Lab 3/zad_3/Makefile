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

all: program

program: program.o
	$(LOADER) $(OPT) program.o -o program

program.o: program.c
	$(CCOMP) -c $(OPT) program.c

clean:
	rm -f *.o program
