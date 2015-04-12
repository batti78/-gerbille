#include<stdio.h>
#include<stdlib.h>
#include<dirent.h>
#include<sys/types.h>

int main(int argc, char *argv[])
{
  if (argc == 2)
  {
    DIR *rep = NULL;
    rep = opendir( argv[1]);
    printf("yolo\n");
    if (rep == NULL)
      printf("Dossier inexistant");
    if (closedir(rep) == -1)
      printf("Erreur fermeture");
  }
  printf("yeah\n");
  return 0;
}
