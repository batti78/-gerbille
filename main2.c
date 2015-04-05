#include<stdlib.h>
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
    gris_normalise(img);
    unsigned long **tab = img_to_tab(img);
    printf("%s\n", "bien joué");
    integrale(tab, img->w, img->h);
    unsigned long **test = e_to_24(tab, img->w, img->h);
    printf("%d\n", test == tab);
    return 0; 
   }
}
