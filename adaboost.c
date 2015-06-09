#include <stdio.h>
#include <stdlib.h>
#include <math.h> 
#include "rect.h" 
#include "data.c" 
#include "adaboost.h"


/*
struct list_haar{ 
  struct haar *array;
  int face; 
  struct list_haar *next;
  int nb_haar;
};

struct stump{
  long t;   // Threshold
  int T;    //Toggle
  long M;   //Margin
  float E;  //Error
};

*/

//n le nombre d'exemple, une liste de features et une liste de poids associés
//t un threshold, T un toggle, m la marge, E l'erreur
struct stump *decision_stump(struct list_haar *larray, float *w, unsigned long n, unsigned nbex)//n, le feature sur lequel on bosse, nb ex le nb d'exemple 
{
  //_______________________________________________________//
  //                     INITIALISATION                    //
  //_______________________________________________________//
  //
  printf("lancement de decision stump");
  long t1 = larray->array[0]; //Threshold
  struct list_haar *tmp = larray; 
  while(tmp) 
  {
    if (tmp->array[n] < t1)
      t1 = tmp->array[n];
    tmp = tmp->next; 
  }
  t1--;
  tmp = larray; 
  printf("apres le while \n");  
  float Wp_1 = 1, Wp_m1 = -1, Wm_1 = 0, Wm_m1 = 0; 
  /*for(i = 0; i < 162366; i++)
  {
    if(larray->array[i] >= t)
      W_plus = W_plus + w;
  }*/
  /*unsigned float W_less = 0;
  for(i = 0; i < 162366; i++)
  {
    if(larray->array[i] < t)
      W_less = W_less + w; 
  }*/
  //unsigned float W_less = 0; 

  struct stump *s = malloc(sizeof(struct stump)); 
  unsigned long j = 1;
  s->t = t1;
  float e1 = 2;
  s->E = e1;
  long m1 = 0; 
  s->M = m1;
  int T1 = 0;
  s->T = T1; 

  printf("end of init\n");  
   //---------------------------------------------------//
  /* traitement */

  while (1)
  {
    printf("dans le while 1 %lu\n", j); 
    float erreur_p = Wm_1 + Wp_m1;
    float erreur_m = Wm_m1 + Wp_1;

    if (erreur_p < erreur_m)
    {
      e1 = erreur_p;
      T1 = 1;
    }
    else
    {
      e1 = erreur_m;
      T1 = -1;
    }

    if ((e1 < s->E) || ( e1 == s->E && s->M == m1))
    {
      s->E = e1;
      s->t = t1;
      s->M = m1;
      s->T = T1;
    }

    if (j == nbex)
      break;

    while (1)
    {
      printf("dans le deuxieme while %lu\n", j); 
      if (tmp->face == -1)
      {
        Wm_m1 += w[n];
        Wp_m1 += w[n];
      } 
      else
      {
        Wm_1 += w[n];
        Wp_1 += w[n];
      }
      printf("juste avant le break\n"); 
      if (j == nbex || larray->array[j] != larray->next->array[j])
        break;
      else
      {
        j++;
        printf("%lu\n", j); 
        tmp = tmp->next;
        printf("%d\n", tmp->ieme); 
      }
    }

    if (j == nbex)
    {
      struct list_haar *TMP = larray; 
      //fflush(stdout); 
      printf("juste avant le trosieme while  \n"); 
      while (TMP != NULL)
      {
        if (t1 < TMP->array[n])
          t1 = TMP->array[n];
        TMP = TMP->next;
      }
      t1++;
      m1 = 0;
    }
    else 
    {
      t1 = (tmp->array[n] + tmp->next->array[n]) / 2 ;
      m1 = tmp->next->array[n] - larray->array[n];
    }
  }
  return s; 
}


struct stump *best_stump(struct list_haar  *larray, float *w, int nbex, int d) // d nombre de features initialisés à 5 dans la fonction adaboost
{
 //printf(" **** lancement de best stump **** \n\n"); 
  //int n = larray->nb_haar; //numero du tableau d'image  
  struct stump *best = malloc(sizeof(struct stump));
  best->E = 2;
  int i = 0; 
  while (i < d) 
  {
   // printf("dans le while de best stump\n");
    struct stump *s = decision_stump(larray, w, i, nbex);

    if (s->E < best->E)
    {
      best = s; 
    }
    if(s->E == best->E)
      if(s->M > best->M)
      {
        best = s; 
        best->coord = i; 
      }
    i++;
  }

  return best;
}


void adaboost(struct list_haar *larray, int nbex, int T)
{
  //printf("******lancement d'adaboost****\n\n");  
  float alpha = 1;    
  long Et = 0;
  float *w = malloc(nbex * sizeof(float)); 
  *w = (1/(float)nbex); 
  int i, j; 

  struct stump *h; 

  for (int t = 1; t <= T; t++) 
  {
    //struct list_haar *haar_tmp = larray;
      //float *tmp = w;
      h = best_stump(larray, w, nbex, 162336);
      for (i = 0; i < nbex; i++)
      {
        Et += w[i];
      }

      if (Et == 0 && t == 1)
        write_data(h, 1); 
      else
      { 
        alpha = 0.5 * log ((1 - Et) / Et);
        for(j = 0; j < nbex; j++ )
          w[j] = (w[j] / 2) * ((1 / Et) + (1 / (1 - Et)));
      }
  }
  write_data(h, alpha); 
}
