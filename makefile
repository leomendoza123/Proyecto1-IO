NAME=main
CFLAGS=-g -Wall -o $(NAME)
GTKFLAGS=-export-dynamic `pkg-config --cflags --libs gtk+-3.0`
SRCS=main.c
Elemento1= RutaOptima.c
Elemento2= Mochila.c
CC=gcc
 
all: main Ruta Mochila
 
# compiling the source file.
main: $(SRCS)
	$(CC) $(CFLAGS) $(SRCS) $(GTKFLAGS)

Ruta:
	  gcc -o Ruta RutaOptima.c

Mochila: 	  
	  gcc -o Mochila Mochila.c
 
# cleaning everything that can be automatically recreated with "make".
clean:
	/bin/rm -f $(NAME)
	/bin/rm -f Mochila
	/bin/rm -f Ruta
