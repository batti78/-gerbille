#include <stdio.h>
#include <stdlib.h>
#include <SDL.h>
#include <SDL_image.h>
#include <err.h>
#include "image.h" 
#include "rect.h"

static inline
Uint8* pixelref(SDL_Surface *surf, unsigned x, unsigned y) {
      int bpp = surf->format->BytesPerPixel;
            return (Uint8*)surf->pixels + y * surf->pitch + x * bpp;
}

void wait_for_keypressed(void) {
    SDL_Event             event;
      for (;;) {
        SDL_PollEvent( &event );
        switch (event.type) {
          case SDL_KEYDOWN: return; 
          default: break;
        }
      }
}

void init_sdl(void) {
  if( SDL_Init(SDL_INIT_VIDEO)==-1 ) {
    errx(1,"Could not initialize SDL: %s.\n", SDL_GetError());
  }
}

SDL_Surface* load_image(char *path) {
  SDL_Surface          *img;
  img = IMG_Load(path);
  if (!img)
    errx(3, "can't load %s: %s", path, IMG_GetError());
  return img;
}

SDL_Surface* display_image(SDL_Surface *img) {
  SDL_Surface          *screen;
  screen = SDL_SetVideoMode(img->w, img->h, 0, SDL_SWSURFACE|SDL_ANYFORMAT);
  if ( screen == NULL ) {
    errx(1, "Couldn't set %dx%d video mode: %s\n",
        img->w, img->h, SDL_GetError());
      }
  if(SDL_BlitSurface(img, NULL, screen, NULL) < 0)
    warnx("BlitSurface error: %s\n", SDL_GetError());
  SDL_UpdateRect(screen, 0, 0, img->w, img->h);
  wait_for_keypressed();
  return screen;
}

Uint32 getpixel(SDL_Surface *surface, unsigned x, unsigned y) 
{
  Uint8 *p = pixelref(surface, x, y);
  switch(surface->format->BytesPerPixel) {
    case 1:
      return *p;
    case 2:
      return *(Uint16 *)p;
    case 3:
      if(SDL_BYTEORDER == SDL_BIG_ENDIAN)
        return p[0] << 16 | p[1] << 8 | p[2];
      else
        return p[0] | p[1] << 8 | p[2] << 16;
    case 4:
      return *(Uint32 *)p;
  }
  return 0;
}

void putpixel(SDL_Surface *surface, unsigned x, unsigned y, Uint32 pixel) {
  Uint8 *p = pixelref(surface, x, y);
  switch(surface->format->BytesPerPixel) {
    case 1:
      *p = pixel;
      break;
    case 2:
      *(Uint16 *)p = pixel;
      break;
    case 3:
      if(SDL_BYTEORDER == SDL_BIG_ENDIAN) {
        p[0] = (pixel >> 16) & 0xff;
        p[1] = (pixel >> 8) & 0xff;
        p[2] = pixel & 0xff;
      } 
      else {
        p[0] = pixel & 0xff;
        p[1] = (pixel >> 8) & 0xff;
        p[2] = (pixel >> 16) & 0xff;
      }
      break;
      case 4:
      *(Uint32 *)p = pixel;
      break;
  }
}

// grise puis normalise une image

void gris_normalise(SDL_Surface *img)
{
  Uint8 r, g, b, med, max = 0;
  Uint8 min = 255;
  unsigned x,y;
  // grise l'image et récupère les valeurs min et max pour la normalisation
  for (x = 0; x < (unsigned) img->h; x++)
  {
    for (y = 0; y < (unsigned) img->w; y++)
    {
      SDL_GetRGB(getpixel(img, y, x), img->format, &r, &g, &b);
      med = 0.3 * r + 0.59 * g + 0.11 * b;
      r = g = b = med;
      max = (max < med ? med : max);
      min = (min > med ? med : min);
      putpixel(img, y, x, SDL_MapRGB(img->format, r, g, b));
    }
  }
  // normalise l'image en fonction de min et max
  for (x = 0; x < (unsigned) img->h; x++)
  {
    for (y = 0; y < (unsigned) img->w; y++)
    {
      SDL_GetRGB(getpixel(img, y, x), img->format, &r, &g, &b);
      med = (b - min) * 255 / (max - min);
      putpixel(img, y, x, SDL_MapRGB(img->format, med, med ,med));
    }
  }
  printf("%s", "gris\n");
}

// convertit un tableau en image

SDL_Surface* tab_to_img(unsigned long **tab, unsigned w, unsigned h)
{
  SDL_Surface *img = SDL_CreateRGBSurface(0, w, h, 32, 0, 0, 0, 0);
  Uint8 r = 0;
  for (unsigned i = 0; i < h; i++)
  {
    for (unsigned j = 0; j < w; j++)
    {
      r = tab[i][j];
      putpixel(img, j, i, SDL_MapRGB(img->format, r, r, r));
    }
  }
  return img;
}

// convertit un rect en tableau

unsigned long** rect_to_tab(struct rect *rec)
{
  unsigned long **array = malloc(sizeof(unsigned long) * rec->size_h);
  for (unsigned i = 0; (int) i < rec->size_h; i++)
  {
    array[i] = malloc(sizeof(unsigned long) * rec->size_w);
    for (unsigned j = 0; (int) j < rec->size_w; j++)
      array[i][j] = rec->integ[rec->y + i][rec->x + j];
  }
  return array;
}

// integralise un tableau correspondant à une image

void integrale(unsigned long **integ, unsigned w, unsigned h)
{
  unsigned i = 0;
  unsigned j;
  while (i < h)
  {
    j = 0;
    while (j < w)
    {
      if (i)
        integ[i][j] += integ[i - 1][j];
      if (j)
        integ[i][j] += integ[i][j - 1];
      if (i && j)
        integ[i][j] -= integ[i - 1][j - 1];
      j ++;
    }
    i++;
  }
}

// convertit une image en tableau

unsigned long** img_to_tab(SDL_Surface *img)
{
  Uint8 r = 0;
  unsigned i,j;
  unsigned long **array = malloc(sizeof(unsigned long*) * img->h);
  for (i = 0; i < (unsigned) img->h; i++)
  {
    array[i] = malloc(sizeof(unsigned long) * img->w);
    for (j = 0; j < (unsigned) img->w; j++)
    {
      SDL_GetRGB(getpixel(img, j, i), img->format, &r, &r, &r);
      array[i][j] = (unsigned long) r;
    }
  }
  return array;
}

// reduit une image w*h en 24*24
// libère array

unsigned long** e_to_24(unsigned long **array, unsigned w, unsigned h)
{
  unsigned long med;
  unsigned long **big = malloc(sizeof(unsigned long) * 24 * h);
  unsigned long **ret = malloc(sizeof(unsigned long) * 24);
  
  // remplissage de la matrice big qui contient 24 pixel pour chaque pixel de array
  // libère array

  for (unsigned i = 0; i < h; i++)
  {
    for (unsigned x = 0; x < 24; x++)
      big[i * 24 + x] = malloc(sizeof(unsigned long) * w * 24);
    for (unsigned j = 0; j < w; j++)
      for (unsigned k = 0; k < 24; k++)
        for (unsigned l = 0; l < 24; l++)
          big[i * 24 + k][j * 24 + l] = array[i][j];
    free(array[i]);
  }
  free(array);
  // remplissage de la matrice 24*24 par moyennage des valeurs de big
  // libère big

  for (unsigned i = 0; i < 24; i++)
  {
    ret[i] = malloc(sizeof(unsigned long) * 24);
    for (unsigned j = 0; j < 24; j++)
    {
      med = 0;
      for (unsigned k = 0; k < h; k++)
        for (unsigned l = 0; l < w; l++)
          med += big[i * h + k][j * w + l];
      med = med / (h * w);
      ret[i][j] = med;
    }
    free(big[i]);
  }
  free(big);
  return ret;
}

// applique adaboost à un rect dont le morceau correspondant est réduit en 24*24

unsigned long** adaboost_rect(struct rect *rec)
{
  unsigned long **array = e_to_24(rect_to_tab(rec), rec->size_w, rec->size_h);
  // array correspond au morceau delimite par le rect, ramene en 24*24
  // adaboost (array);
  return array;
}
