#include <stdio.h>
#include <stdlib.h>
#include "dir_functions.c" //get_nth_file_name(name_fichier, i)

int main (int argc, char *argv[])
{
  FILE* fichier = NULL;
  fichier = fopen ("dl_pic.cvs", "w+");

  if (fichier != NULL)
  {
    for (int i = 1, i <= 151, i++)
    {
        char* name-fichier = get_nth_name(database, i);
        fputs(name_fichier, fichier);
    }
    fclose(fichier);
  }
  else
  {
    printf ("Impossible d'ouvrir le fichier");
  }

  return 0;
}
