CC = gcc
OPTIONS  = -Wall
FLAGSGTK = `pkg-config --cflags --libs gtk+-3.0`
GTKFOLDER = interfaceGraphique/


exe: interfacegtk.o main.o sudokugtk.o generation.o
	$(CC) $(OPTIONS) *.o $(FLAGSGTK) -o $@ -lm
	rm -f *.o
	@echo "Excécutable prêt !"

interfacegtk.o: $(GTKFOLDER)interfacegtk.c
	$(CC) $(OPTIONS) -c $^ $(FLAGSGTK)

sudokugtk.o: $(GTKFOLDER)sudokugtk.c
	$(CC) $(OPTIONS) -c $^ $(FLAGSGTK)

main.o: $(GTKFOLDER)main.c
	$(CC) $(OPTIONS) -c $^ $(FLAGSGTK)

generation.o: generation.c
	$(CC) $(OPTIONS) -c $^

clean:
	rm -f exe
