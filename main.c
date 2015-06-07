#include<stdlib.h>
#include<SDL.h>
#include<SDL_image.h>
#include<SDL/SDL.h>
#include"haar.c"
#include"image.c"
#include"adaboost.c"

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
    unsigned long *array = malloc(162336 * sizeof(unsigned long));
    unsigned long *array2 = malloc(162336 * sizeof(unsigned long));
    unsigned long *array3 = malloc(162336 * sizeof(unsigned long)); 
    nb = fun_haar(tab, array);
    nb = fun_haar(tab, array2); 
    nb = fun_haar(tab, array3);
    struct list_haar *larray = malloc(3 * sizeof(struct list_haar));

    int i; 
    for(i = 100000; i < 101000; i++) 
      printf("%ld \n", array[i]); 
    printf("%lu \n", nb); 
     
    printf("size of struct array : %lu \n", sizeof(array)); 
    return 0; 
   }
}
