#include<stdlib.h>
#include<stdio.h>
#include<SDL.h>
#include<SDL_image.h>
#include<SDL/SDL.h>
#include"rect.h" 
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
    long *array = malloc(162336 * sizeof(unsigned long));
    long *array2 = malloc(162336 * sizeof(unsigned long));
    long *array3 = malloc(162336 * sizeof(unsigned long)); 
    nb = fun_haar(tab, array);
    nb = fun_haar(tab, array2); 
    nb = fun_haar(tab, array3);
    printf("apres fun haar\n"); 
    struct list_haar *larray;
    struct list_haar tmp1, tmp2, tmp3;
    tmp1.array = array;
    tmp1.ieme = 1; 
    tmp1.next = &tmp2;
    printf("apres avoir geré tmp1\n");
    tmp2.array = array2; 
    tmp2.ieme = 2; 
    tmp2.next = &tmp3;
    tmp3.array = array3;
    tmp3.ieme = 3;
    tmp3.next = NULL;
    tmp1.face = -1; 
    tmp1.face = -1;
    tmp1.face = -1; 
    larray = &tmp1;
    printf("slt, je lance adaboost"); 
    adaboost(larray, 3, 2); 
    int i; 
    for(i = 100000; i < 101000; i++) 
      printf("%ld \n", array[i]); 
    printf("%lu \n", nb); 
     
    printf("size of struct array : %lu \n", sizeof(array)); 
    return 0; 
   }
}
