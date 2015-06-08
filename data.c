#include<stdlib.h>
#include<stdio.h>
#include"rect.h"
#include"data.h"

int write_data(struct stump *h, float alpha)
{
  FILE *file = fopen("./strong_classifier","a");
  if(file)
  {
    fprintf("%d %d %d %f %f\n",h->t, h->T, h->M, h->E, alpha); 
    fclose(file); 
  }
  else
    fprint("File doesn't exist");
}
