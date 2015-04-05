#include<stdlib.h>
#include<SDL.h>
#include<SDL_image.h>
#include<SDL/SDL.h>
#include"image.c"
#include"haar.c"

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
    unsigned long nb = 0; 
    struct haar *haar = NULL;
    nb = fun_haar(tab, haar);
    printf("%lu \n", nb);
    int i; 
    for (i = 0; i < 20; i++)
      printf("%lu \n", haar[i].result);
    return 0; 
   }
}
