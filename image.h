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

void waitforkeypressed(void);

Uint32 getpixel(SDL_Surface *surface, unsigned x, unsigned y);

void putpixel(SDL_Surface *surface, unsigned x, unsigned y, Uint32 pixel);

SDL_Surface* load_image(char *path); 

void init_sdl(void);

void gris_normalise(SDL_Surface *img);

SDL_Surface* tab_to_img(unsigned long **tab, unsigned w, unsigned h);

unsigned long** rect_to_tab(struct rect *rec);

void integrale(unsigned long **integ, unsigned w, unsigned h);

unsigned long** img_to_tab(SDL_Surface *img);

unsigned long** e_to_24(unsigned long **array, unsigned w, unsigned h);

unsigned long** adaboost_rec(struct rect *rec);

#endif


