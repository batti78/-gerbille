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
          if (visage) // test (i == 50 && j == 50 && i1 == 50 && j1 == 50)
          {
            if (i != 0 && j != 0 && i != w - 1 && j != h - 1)
              array[i-1][j-1] = array[i-1][j+j1] = array[i+i1][j-1] = array[i+i1][j+j1] = 0;
            for (unsigned i2 = i; i2 < i + i1; i2++)
              for (unsigned j2 = j; j2 < j + j1; j2++)
              {
                if (i2 == i && i != 0)
                  array[i2 - 1][j2] = 0;
                if (i2 == i + i1 - 1 && i != w - 1)
                  array[i2 + 1][j2] = 0;
                if (j2 == j && j != 0)
                  array[i2][j2 - 1] = 0;
                if (j2 == j + j1 - 1 && j != h - 1)
                  array[i2][j2 + 1] = 0;
              }
          }
        }
}
