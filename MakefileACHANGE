CC = gcc

FLAGS = -Wall -O -lm

all : resolution

resolution : bitBoard.c grille.c liste.c resolution.c main.c
	@echo "Génération de l'excécutable ... "
	$(CC) -o $@ $^ $(FLAGS)
	@echo "Excécutable prêt !"

clean:
	rm -f resolution
	@echo "Fichier resolution effacé !"
