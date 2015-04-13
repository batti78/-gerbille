#include<stdlib.h>
#include<stdio.h>
#include<SDL.h>
#include<SDL_image.h>
#include<SDL/SDL.h>
#include"image.c"
#include<dirent.h>
#include<sys/types.h>

int main(int argc, char *argv[])
{
  if(argc == 2)
  {
    char *path = argv[1];

    DIR *rep = NULL;
    struct dirent *fichier = NULL;
    rep = opendir(path);
    printf("open\n");
    if (rep == NULL)
      printf("Dossier inexistant");
    fichier = readdir(rep);
    printf("read");
    path = "des.png";
    printf("given\n");
    
    init_sdl();
    SDL_Surface *img = load_image(path);
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
    printf("1\n");
    for (unsigned j = 0; j < 24; j++)
      free(ada[j]);
    printf("2\n");
    free(rec);

    if (closedir(rep) == -1)
      printf("Erreur fermeture");

    return 0; 
   }
}
