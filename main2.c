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
    while ((name = get_nth_file_name(path, i)))
    {
      printf("%s\n",name);
      i++;
      init_sdl();
      SDL_Surface *img = load_image(name);
      gris_normalise(img);
      unsigned long **tab = img_to_tab(img);

      //integrale(tab, img->w, img->h);

      struct rect *rec = malloc(sizeof(struct rect));
      rec->x = 200;
      rec->y = 200;
      rec->size_w = 200;
      rec->size_h = 200;
      rec->integ = tab; 
      unsigned long** ada = adaboost_rect(rec);

      unsigned long **test = e_to_24(tab, img->w, img->h);
      display_image(img);
      display_image(tab_to_img(test, 24, 24));
      display_image(tab_to_img(ada, 24, 24));
      for (unsigned i = 0; i < 24; i++)
        free(test[i]);
      for (unsigned j = 0; j < 24; j++)
        free(ada[j]);
      free(rec);
    }

    return 0; 
  }
}
