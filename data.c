#include<stdlib.h>
#include<stdio.h>
#include"rect.h"
#include"data.h"

void write_data(struct stump *h, float alpha)
{
  FILE *file = fopen("./strong_classifier","a");
  if(file)
  {
    fprintf(file,"%ld %d %ld %f %ld %f\n",h->t, h->T, h->M, h->E, h->coord, alpha); 
    fclose(file); 
  }
  else
    printf("File doesn't exist");
}
