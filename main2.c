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

int main(int argc, char *argv[])
{
  if(argc == 2)
  {
    char *path = argv[1];
    unsigned i = 1;
    char *name = NULL;
    unsigned long **tab = NULL;
    SDL_Surface *img = NULL;
    struct rect *rec = malloc(sizeof(struct rect));
    unsigned long **ada = NULL;

    init_sdl();
    while ((name = get_nth_file_name(path, i)) && strcmp(name, "break"))
    {
      printf("%s\n",name);
      i++;

      img = load_image(name);
      gris_normalise(img);
      tab = img_to_tab(img);

      //integrale(tab, img->w, img->h);

      rec->x = 200;
      rec->y = 200;
      rec->size_w = 200;
      rec->size_h = 200;
      rec->integ = tab; 
      ada = adaboost_rect(rec);

      for (unsigned i = 0; i < 24; i++)
      {
        free(ada[i]);
      }
      free(rec);
    }

    return 0; 
  }
}
