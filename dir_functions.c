#include<dirent.h>
#include<sys/types.h>
#include<stdio.h>
#include<stdlib.h>
#include"dir_functions.h"
#include<string.h>

char* get_nth_file_name(char* dir_name, unsigned n)
{
  char *name = malloc(sizeof(char*));
  char *patherase = malloc(sizeof(char*));
  DIR *rep = NULL;
  struct dirent *fichier = NULL;
  rep = opendir(dir_name);

  if (rep == NULL)
    printf("Dossier inexistant\n");

  for (unsigned i = 0; i < n + 2; i++)
    fichier = readdir(rep);

  if(fichier)
  {
    //printf("used %d time\n", n);
    strcpy(patherase, dir_name);
    name = fichier->d_name;
    if (closedir(rep) == -1)
      printf("Erreur fermeture\n");
    return strcat(patherase, name);
  }
  else
  {
    if (closedir(rep) == -1)
      printf("Erreur fermeture\n");
    return "break";
  }
}

