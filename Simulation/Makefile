CC=gcc
CFLAGS=-W -Wall -ansi -pedantic
LDFLAGS=
EXEC=main

allMacOs: $(EXEC)
	./main Lambda.txt
	Rscript Graphe.R
	Rscript Graphe2.R

main : LireFichier.o File.o MM10.o MM1.o MM10min.o main.o 
	$(CC) -o $@ $^ $(LDFLAGS)
	
File.o: File.c
	$(CC) -o $@ -c $< $(CFLAGS)

LireFichier.o: LireFichier.c
	$(CC) -o $@ -c $< $(CFLAGS)

MM10.o : MM10.c MM10.h
	$(CC) -o $@ -c $< $(CFLAGS)

MM1.o : MM1.c MM1.h
	$(CC) -o $@ -c $< $(CFLAGS)

MM10min.o : MM10min.c MM10min.h
	$(CC) -o $@ -c $< $(CFLAGS)

main.o : main.c LireFichier.h
	$(CC) -o $@ -c $< $(CFLAGS)

Graphe: 
	Rscript Graphe.R 
	Rscript Graphe2.R
clean :
	rm -f *.o
	rm -f *.exe
	rm -f *.h.gch
	rm main
