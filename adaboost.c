#include <stdio.h>
#include <stdlib.h>
#include "haar.c"
#include "haar.h"
#include "adaboost.h"
#include "math.h" 

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
struct stump *decision_stump(struct list_haar *larray, float  *w, unsigned long n, unsigned nbex)
{
  //_______________________________________________________//
  //                     INITIALISATION                    //
  //_______________________________________________________//
  //
  long t1 = larray->array[0]; //Threshold
  int i;
  struct list_haar *tmp = larray; 
  for (i = 0; i < 162336; i++)
  {
    if (tmp->array[i] < t)
      t1 = tmp->array[i];
    tmp = tmp->next; 
  }
  t1--;
  tmp = larray; 
  
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
  unsigned long j = 0;
  s->t = t;
  float e1 = 2;
  s->E = e1;
  long m1 = 0; 
  s->M = m1;
  int T1 = 0;
  s->T = T1; 

  
   //---------------------------------------------------//
  /* traitement */

  while (1)
  {
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

    j++;
    tmp = tmp->next;
  
    while (1)
    {
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

      if (j == nbex || larray->array != larray->next->array)
        break;
      else
      {
        j++;
        tmp = tmp->next;
      }
    }

    if (j == nbex)
    {
      struct list_haar *TMP = larray; 
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


struct stump *best_stump(struct list_haar *larray, float *w, int d) // d nombre de features initialisés à 5 dans la fonction adaboost
{
  //int n = larray->nb_haar; //numero du tableau d'image  
  struct stump *best = malloc(sizeof(struct stump));
  best->E = 2;
  int i = 1; 
  while (i <= d) 
  {
    struct stump *s = decision_stump(larray, w, i, nbex);

    if (s->E < best->E)
    {
      best = s; 
    }
    if(s->E == best->E)
      if(s->M > best->M)
        best = s; 
    i++;
  }

  return best;
}


struct stump *AdaBoost(struct list_haar *larray, int T)
{
  float alpha;
  long Et = 0;
  float *w; 
  w->poids = 1 / larray->nb_haar;

  struct stump *h;

  for (int t = 1; t <= T; t++) 
  {
    struct list_haar *haar_tmp = larray;
    while (haar_tmp)
    {
      struct weight *tmp = w;
      h = best_stump(larray, w, 5);
      while (tmp != NULL)
      {
        Et += tmp->poids;
        tmp = tmp->next;
      }

      if (Et == 0 && t == 1)
        return h;
      else
      {
        alpha = 0.5 * log ((1 - Et) / Et);
        w->next->poids = (w->poids / 2) * ((1 / Et) + (1 / (1 - Et))); 
        w = w->next;
      }
      haar_tmp = haar_tmp->next;
    }

  }

  h->M = alpha * h->M;
  return h ;
}
