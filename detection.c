#include<stdlib.h>
#include<stdio.h>

void parcours(unsigned long **array, unsigned w, unsigned h)
{
  int visage = 0;
  float coef_w = w / 24;
  float coef_h = h / 24;
  for (unsigned i = 0; i < w; i++)
    for (unsigned j = 0; j < h; j++)
      for (unsigned i1 = 24; i1 < w - i - 24; i1 = i1 + coef_w)
        for (unsigned j1 = 24; j1 < h - j - 24; j1 = j1 + coef_h)
        {
          // mise à jour de visage
          // si visage dessine un carré noir sinon rien
          if (visage)// (i == 50 && j == 50 && i1 == 24 && j1 == 24)
          {
            if (i != 0 && j != 0 && i != w - 1 && j != h - 1)
              array[i - 1][j - 1] = array[i - 1][j + j1] = array[i + i1][j - 1] = array[i + i1][j + j1] = 256;
            for (unsigned i2 = i; i2 < i + i1; i2++)
              for (unsigned j2 = j; j2 < j + j1; j2++)
              {
                if (i2 == i && i != 0)
                  array[i2 - 1][j2] = 256;
                if (i2 == i + i1 - 1 && i != w - 1)
                  array[i2 + 1][j2] = 256;
                if (j2 == j && j != 0)
                  array[i2][j2 - 1] = 256;
                if (j2 == j + j1 - 1 && j != h - 1)
                  array[i2][j2 + 1] = 256;
              }
          }
        }
}
