#include<stdlib.h>
#include<stdio.h>
#include<SDL.h>
#include<SDL_image.h>
#include<SDL/SDL.h>
#include"image.c"
#include<dirent.h>
#include<sys/types.h>
#include<string.h>
#include"dir_functions.c"
#include"haar.c"

int main(int argc, char *argv[])
{
  if(argc == 2)
  {
    char *path = argv[1];
    unsigned i = 1;
    char *name = NULL;
    unsigned long **tab = NULL;
    SDL_Surface *img = NULL;
    unsigned long **ada = NULL;
    struct haar *haar = NULL;

    init_sdl();
    while ((name = get_nth_file_name(path, i)) && strcmp(name, "break"))
    {
      printf("%s\n",name);
      i++;


      // operation sur l image
      img = load_image(name);

      display_image(img);

      gris_normalise(img);

      display_image(img);

      tab = img_to_tab(img);
      integrale(tab, img->w, img->h);

      display_image(tab_to_img(tab, img->w, img->h));
      
      ada = e_to_24(tab, img->w, img->h);

      display_image(tab_to_img(ada, 24, 24));

      // appeler adaboost
      
      haar = malloc(162336 * sizeof(struct haar));
      fun_haar(ada, haar);
    
      // free
      for (unsigned i = 0; i < 24; i++)
      {
        free(ada[i]);
        ada[i] = NULL;
      }
      free(ada);
      ada = NULL;

      free(haar);
      haar = NULL;
    }

    return 0; 
  }
}
