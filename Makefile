#simple SDL mini code
 
CC=clang  
CPPFLAGS= `pkg-config --cflags sdl`
CFLAGS= -Wall -Wextra -Werror -std=c99 -O3
LDFLAGS=
LDLIBS= `pkg-config --libs sdl` -lSDL_image
SRC= main.c
SRC2= main2.c
OBJ= ${SRC:.c=.o}
OBJ2= ${SRC2:.c=.o}
all: main	 
main: ${OBJ}
main2: ${OBJ2}
clean:
	rm -f *~ *.o
	rm -f main main2
		       
			     # END
