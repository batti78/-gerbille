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
    int h = 0;
    int w = 0;

    init_sdl();
    while ((name = get_nth_file_name(path, i)) && strcmp(name, "break"))
    {
      printf("%s\n",name);
      i++;

      // operation sur l image
      img = load_image(name);
      w = img->w;
      h = img->h;

      //display_image(img);

      gris_normalise(img);
      printf("normalized\n");
      tab = img_to_tab(img);
      printf("img to tab\n");
      integrale(tab, w, h);
      printf("integralized\n");   
      ada = e_to_24(tab, w, h);
      printf("e to 24\n");
      // appeler adaboost
      
      haar = malloc(162336 * sizeof(struct haar));
      fun_haar(ada, haar);
    
      // free
      for (unsigned i1 = 0; i1 < 24; i1++)
      {
        free(ada[i]);
        ada[i] = NULL;
      }

      free(ada);
      ada = NULL;

      free(haar);
      haar = NULL;

      name = NULL;
      printf("done\n");
    }

    return 0; 
  }
}
