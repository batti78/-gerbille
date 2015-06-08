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
#include"detection.c"

int main(int argc, char *argv[])
{
  if(argc == 2)
  {
    char *path = argv[1];
    unsigned i = 1;
    unsigned count = 1;
    char *name = NULL;
    unsigned long **tab = NULL;
    SDL_Surface *img = NULL;
    long *haar = NULL;
    struct list_haar *list = malloc(sizeof(struct list_haar*));
    struct list_haar *tmp = NULL;
    list->next = NULL;
    list->face = 1;
    list->ieme = 0;

    init_sdl();
    while ((name = get_nth_file_name(path, i)) && strcmp(name, "break"))
    {
      if (strcmp(name, "database/.") && strcmp(name, "database/.."))
      {
        printf("%s\n",name);

        // operation sur l image
        img = load_image(name);
        //printf("loaded\n");

        //display_image(img);

        gris_normalise(img);
        //printf("normalized\n");
        tab = img_to_tab(img);
        //printf("img to tab\n");
        integrale(tab, 24, 24);
        //printf("integralized\n");   

        // appeler adaboost

        haar = malloc(162336 * sizeof(long));
        fun_haar(tab, haar);

        tmp = malloc(sizeof(struct list_haar*));
        tmp->next = list->next;
        list->next = tmp;
        tmp->face = 1;
        tmp->ieme = count;
        tmp->array = haar;
        //free(tmp);
        //tmp = NULL;


        // free
        for (unsigned i1 = 0; i1 < 24; i1++)
        {
          free(tab[i1]);
          tab[i1] = NULL;
        }
        //printf("free\n");
        //free(tab);
        tab = NULL;

        //free(haar);
        //haar = NULL;

        //name = NULL;
        printf("%d\n",count);
        count++;

      }

      i++;
    }
    /*
       tmp = list;
       while (tmp->next)
       {
       printf("%d\n", tmp->next->ieme);
       tmp = tmp->next;
       }
       tmp = NULL;
       */    
    return 0; 
  }
}
