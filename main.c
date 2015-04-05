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
    //unsigned long nb = 0; 
    struct haar haartab[163000];
    printf("%lu \n", sizeof(haartab)/sizeof(struct haar)); 
    // = fun_haar(tab, haartab);
    //nb = fun_haar(tab, haar);
    //printf("%lu \n", nb);
    //int i; 
    //for (i = 0; i < 20; i++)
    //  printf("%lu \n", haar[i].result);
    struct rect r;
    r.x = 12;
    r.y = 12;
    r.size_h = 6;
    r.size_w = 6;
    r.integ = tab;
    int haari = 1;
    printf("before case_h"); 
    case_h(&haartab[1000], &r, haari);
    printf("%lu \n", haartab[1000].result); 
    //for(i = 100000; i < 101000; i++) 
    //  printf("%ld \n", haartab[i].result); 
    //printf("%lu \n", nb); 
    return 0; 
   }
}
