#simple SDL mini code
 
CC=clang  
CPPFLAGS= `pkg-config --cflags sdl`
CFLAGS= -Wall -Wextra -Werror -std=c99 -O3
LDFLAGS=
LDLIBS= `pkg-config --libs sdl` -lSDL_image
SRC= main.c
SRC2= main2.c
SRC3= main3.c
OBJ= ${SRC:.c=.o}
OBJ2= ${SRC2:.c=.o}
OBJ3= ${SRC3:.c=.o}
all: main3
main: ${OBJ}
main2: ${OBJ2}
main3: ${OBJ3}
clean:
	rm -f *~ *.o
	rm -f main main2 main3
		       
			     # END
