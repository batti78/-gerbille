#include"image.c"
#include"detection.c"

int main(void)
{
  SDL_Surface *img = load_image("visage");
  display_image(img);
  unsigned long **array = img_to_tab(img);
  parcours(array, img->w, img->h);
  img = tab_to_img(array, img->w, img->h);
  display_image(img);
  return 0;
}
