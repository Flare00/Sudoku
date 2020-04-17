CC = gcc
OPTIONS  = -Wall -lm
FLAGSGTK = `pkg-config --cflags --libs gtk+-3.0`
GTKFOLDER = interfaceGraphique/


### EXECUTABLE
exe: listeGtk.o interfacegtk.o sudokugtk.o generation.o bitBoard.o grille.o liste.o resolution.o main.o
	$(CC) -o $@ $^ $(OPTIONS) $(FLAGSGTK)
	rm -f *.o
	@echo "Excécutable prêt !"


### INTERFACE GRAPHIQUE
listeGtk.o: $(GTKFOLDER)listeGtk.c
	$(CC) $(OPTIONS) -c $^ $(FLAGSGTK)
interfacegtk.o: $(GTKFOLDER)interfacegtk.c
	$(CC) $(OPTIONS) -c $^ $(FLAGSGTK)
sudokugtk.o: $(GTKFOLDER)sudokugtk.c
	$(CC) $(OPTIONS) -c $^ $(FLAGSGTK)
main.o: $(GTKFOLDER)main.c
	$(CC) $(OPTIONS) -c $^ $(FLAGSGTK)


### GENERATION
generation.o: generation.c
	$(CC) $(OPTIONS) -c $^


### RESOLUTION
bitBoard.o: bitBoard.c
	$(CC) $(OPTIONS) -c $^
grille.o: grille.c
	$(CC) $(OPTIONS) -c $^
liste.o: liste.c
	$(CC) $(OPTIONS) -c $^
resolution.o: resolution.c
	$(CC) $(OPTIONS) -c $^

resolution : grille.c bitBoard.c liste.c resolution.c main.c
	$(CC) -o $@ $^


### CLEAN
clean:
	rm -f exe
	@echo "Executable effacé !"
