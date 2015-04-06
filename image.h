#ifndef IMAGE_H
#define IMAGE_H

#include <stdio.h>
#include <stdlib.h>
#include <SDL.h>
#include <SDL_image.h>
#include <err.h>
#include "rect.h" 


/*struct rect{
  int x; 
  int y;
  int size_w;
  int size_h;
  unsigned long **integ;
};*/



Uint32 getpixel(SDL_Surface *surface, unsigned x, unsigned y);

void putpixel(SDL_Surface *surface, unsigned x, unsigned y, Uint32 pixel);

SDL_Surface* load_image(char *path); 

void init_sdl(void);

#endif


