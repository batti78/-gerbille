#include<stdlib.h>
#include<stdio.h>

void parcours(unsigned long **array, unsigned w, unsigned h)
{
  for (unsigned i = 0; i < w; i++)
  {
    for (unsigned j = 0; j < h; j++)
    {
      for (unsigned i1 = 24; i1 < w - i; i1++)
      {
        for (unsigned j1 = 24; j1 < h - j; j1++)
        {
          // est-ce que le carré de dim i1xj1 est un visage ?
          // si oui dessine un carré rouge sinon rien
        }
      }
    }
  }
}
