CC = gcc
OPTIONS  = -Wall -lm
FLAGSGTK = `pkg-config --cflags --libs gtk+-3.0`
GTKFOLDER = interfaceGraphique/


### EXECUTABLE
exe: interfacegtk.o main.o sudokugtk.o generation.o bitBoard.o grille.o liste.o resolution.o
	$(CC) -o $@ $^ $(OPTIONS) $(FLAGSGTK)
	rm -f *.o
	@echo "Excécutable prêt !"


### INTERFACE GRAPHIQUE
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


### CLEAN
clean:
	rm -f exe
	@echo "Executable effacé !"
