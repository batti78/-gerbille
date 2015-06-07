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
    //unsigned long *haar = NULL;
    //struct list_haar *list = malloc(sizeof(struct list_haar*));
    //struct list_haar *tmp = NULL;
    //list->next = NULL;
    //list->face = 1;
    //list->ieme = 0;

    init_sdl();
    while ((name = get_nth_file_name(path, i)) && strcmp(name, "break"))
    {
      printf("%s\n",name);

      // operation sur l image
      img = load_image(name);
      printf("loaded\n");

      //display_image(img);

      gris_normalise(img);
      printf("normalized\n");
      tab = img_to_tab(img);
      printf("img to tab\n");
      integrale(tab, 24, 24);
      printf("integralized\n");   
      //printf("e to 24\n");
      // appeler adaboost
      /*
      haar = malloc(162336 * sizeof(unsigned long));
      fun_haar(ada, haar);

      tmp = malloc(sizeof(struct list_haar*));
      tmp->next = list->next;
      list->next = tmp;
      tmp->face = 1;
      tmp->ieme = i;
      tmp->array = haar;
      free(tmp);
      tmp = NULL;
      printf("");

      */
      // free
      for (unsigned i1 = 0; i1 < 24; i1++)
      {
        free(tab[i]);
        tab[i] = NULL;
      }
      printf("free\n");
      free(tab);
      tab = NULL;
      
      //free(haar);
      //haar = NULL;
      
      name = NULL;
      printf("%d\n",i);
      i++;
    }

    return 0; 
  }
}
