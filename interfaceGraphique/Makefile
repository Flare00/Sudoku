CC = gcc
OPTIONS  = -Wall
FLAGSGTK = `pkg-config --cflags --libs gtk+-3.0`

exe: interfacegtk.o main.o
	$(CC) $(OPTIONS) *.o $(FLAGSGTK) -o exe
	rm -f *.o
	@echo "Excécutable prêt !"

interfacegtk.o: interfacegtk.c
	$(CC) $(OPTIONS) -c interfacegtk.c $(FLAGSGTK)

main.o: main.c
	$(CC) $(OPTIONS) -c main.c $(FLAGSGTK)

clean:
	rm -f exe
