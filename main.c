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
    unsigned long nb = 0; 
    struct haar *haartab = malloc(163000*sizeof(struct haar)); 
    printf("%lu \n", sizeof(*haartab)/sizeof(struct haar)); 
    // = fun_haar(tab, haartab);
    //nb = fun_haar(tab, haar);
    //printf("%lu \n", nb);
    //int i; 
    //for (i = 0; i < 20; i++)
    //  printf("%lu \n", haar[i].result);
    struct rect r;
    r.x = 0;
    r.y = 0;
    r.size_h = 3;
    r.size_w = 1;
    r.integ = tab;
    int haari = 3;
    printf("before case_h"); 
    case_h(&haartab[1000], &r, haari);
    printf("%lu \n", haartab[1000].result); 
    nb = fun_haar(tab, haartab); 
    //for(i = 100000; i < 101000; i++) 
    //  printf("%ld \n", haartab[i].result); 
    //printf("%lu \n", nb); 
    return 0; 
   }
}
