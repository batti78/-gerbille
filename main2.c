#include<stdlib.h>
#include<stdio.h>
#include<SDL.h>
#include<SDL_image.h>
#include<SDL/SDL.h>
#include"image.c"

int main(int argc, char *argv[])
{
  if(argc == 2)
  {
    char *path = argv[1]; 
    init_sdl();
    SDL_Surface *img = load_image(path);
    //gris_normalise(img);
    unsigned long **tab = img_to_tab(img);
    
    //integrale(tab, img->w, img->h);
    /*
    unsigned long **test = e_to_24(tab, img->w, img->h);
    display_image(img);
    display_image(tab_to_img(tab, img->w, img->h));
    display_image(tab_to_img(test, 24, 24));
    */
    struct rect *rec = malloc(sizeof(struct rect));
    rec->x = 200;
    rec->y = 200;
    rec->size_w = 200;
    rec->size_h = 200;
    rec->integ = tab;
    unsigned long** ada = adaboost_rect(rec);
    display_image(tab_to_img(ada, 24, 24));
    free(tab);
    free(rec);
    return 0; 
   }
}
