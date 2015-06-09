#simple SDL mini code
 
CC=clang  
CPPFLAGS= `pkg-config --cflags sdl gtk+-3.0`
CFLAGS= -Wall -Wextra -Werror -std=c99 -O3
LDFLAGS=
LDLIBS= `pkg-config --libs sdl gtk+-3.0` -lSDL_image -lm
SRC= main.c
SRC2= main2.c
SRC3= main3.c
SRC4 = gtk.c
OBJ= ${SRC:.c=.o}
OBJ2= ${SRC2:.c=.o}
OBJ3= ${SRC3:.c=.o}
OBJ4= ${SRC4:.c=.o}
all: main
main: ${OBJ}
main2: ${OBJ2}
main3: ${OBJ3}
gtk: ${OBJ4}
clean:
	rm -f *~ *.o
	rm -f main main2 main3 gtk
		       
			     # END
