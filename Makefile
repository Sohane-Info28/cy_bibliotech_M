CC=gcc
CFLAGS=-Wall -Wextra

all: cybibliotech

cybibliotech: main.o outils.o recherches.o affichage.o fichiers.o utilisateurs.o emprunts.o recherche_tri.o bibliothecaire.o menus.o
	$(CC) main.o outils.o recherches.o affichage.o fichiers.o utilisateurs.o emprunts.o recherche_tri.o bibliothecaire.o menus.o -o cybibliotech

%.o: %.c bibliotheque.h
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f *.o cybibliotech
