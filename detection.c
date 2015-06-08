#include<stdlib.h>
#include<stdio.h>

void parcours(unsigned long **array, unsigned w, unsigned h)
{
  int visage = 0;
  for (unsigned i = 0; i < w; i++)
    for (unsigned j = 0; j < h; j++)
      for (unsigned i1 = 24; i1 < w - i; i1++)
        for (unsigned j1 = 24; j1 < h - j; j1++)
        {
          // si oui dessine un carré noir sinon rien
          if (visage)
          {
            array[i-1][j-1] = array[i-1][j1] = array[i1][j-1] = array[i1][j1] = 255;
            for (unsigned i2 = i; i2 < i1; i2++)
              for (unsigned j2 = j; j2 < j1; j2++)
              {
                if (i2 == i)
                  array[i2 - 1][j2] = 255;
                if (i2 == i1 - 1)
                  array[i2 + 1][j2] = 255;
                if (j2 == j)
                  array[i2][j2 - 1] = 255;
                if (j2 == j1 - 1)
                  array[i2][j2 + 1] = 255;
              }
          }
        }
}
