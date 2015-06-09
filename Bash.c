#include <stdio.h>
#include <stdlib.h>
#include "dir_functions.c" //get_nth_file_name(name_fichier, i)

int write (void)
{
  FILE* fichier = NULL;
  fichier = fopen ("dl_pic.cvs", "w+");

  if (fichier != NULL)
  {
    for (int i = 1, i <= 151, i++)
    {
        char* name-fichier = get_nth_name(database, i);
        char* token;
        char* tmp = strtok (name-fichier, "/");
        tmp = strtok (NULL, " ");
        
        fputs(name-fichier, fichier);
        fputs(";" + tmp + "\n", fichier);
    }
    fclose(fichier);
  }
  else
  {
    printf ("Impossible d'ouvrir le fichier");
  }

  return 0;
}
