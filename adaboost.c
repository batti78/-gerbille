#include <stdio.h>
#include <stdlib.h>
#include "haar.c"
#include "haar.h"


struct weight{            // Structure pour les poids :
  float poids;            // Sous forme de liste chainée
  struct weight *next;
  int face;               //Si visage = 1 sinon = -1
};

struct list_haar{  // structure liste de haar
  struct haar *array;
  struct list_haar *next;
  int nb_haar;
};

struct stump{
  long t; // Threshold
  int T; //Toggle
  long M; //Margin
  float E; //Error
};



//n le nombre d'exemple, une liste de features et une liste de poids associés
//t un threshold, T un toggle, m la marge, E l'erreur
void decision_stump( struct list_haar *larray, struct weight *w,struct stump s)
{
  //_______________________________________________________//
  //                     INITIALISATION                    //
  //_______________________________________________________//
  
  int n = larray->nb_haar;
  t = larray->array->result - 1; //Threshold
  long t' = t;
  s->T = 0;                   //Toggle
  int T' = s->T;
  s->M = 0;                   //Margin
  long m' = s->M;
  s->E = 2;                   //Error
  float e';
  int j = 0;
  float Wp_1 = 0;    //Sommes des poids sur photos avec visage
  float Wp_m1 = 0;   //Sommes des poids sur photos sans visage
  struct weight *tmp = w;

  while (w != NULL)
  {
    if (w->face == 1)
      Wp_1 += w->poids;
    else
      Wp_m1 += w->poids;

    w = w->next;
  }

  float Wm_1 = 0;
  float Wm_m1 = 0;

  

  /* traitement */

  while (true)
  {
    float erreur_p = Wm_1 + Wp_m1;
    float erreur_m = Wm_m1 + Wp_1;

    if (erreur_p < erreur_m)
    {
      e' = erreur_p;
      T' = 1;
    }
    else
    {
      e' = erreur_m;
      T' = -1;
    }

    if ((e' < E) || ( e' == E && M = m'))
    {
      s->E = e';
      s->t = t';
      s->M = m';
      s->T = T';
    }

    if (j == n)
      break;

    j++;
    tmp = tmp->next;
    larray = larray->next;
  }
  while (true)
  {
    if (w->face == -1)
    {
      Wm_m1 += tmp->poids;
      Wp_m1 += tmp->poids;
    } 
    else
    {
      Wm_1 += tmp->poids;
      Wp_1 += tmp->poids;
    }

    if (j == n || larray->array != larray->next->array)
      break;
    else
    {
      j++;
      tmp = tmp->next;
      larray = larray->next;
    }
  }

  if (j == n)
  {
    struct list_haar TMP = larray;
    while (TMP->next != NULL)
      TMP = TMP->next;

    t' = TMP->array->result + 1;
    m' = 0;
  }
  else 
  {
    t' = (larray->array->result + larray->next->array->result) / 2 ;
    m' = larray->next->result - larray->result;
  }

}


void best-stump(struct list_haar *larray, struct weight *w, int d) // d nombre de features
{
  int n = larray->nb_haar;
  struct stump s;
  s->E = 2;

  for (f = 1; f <= d; f++) //pour chaques features
  {
    decision_stump(larray, w, s);

    if ()
    {
      //--?--//
    }
  }
}


long AdaBoost(struct list_haar *larray, int T)
{
  float alpha;
  long Et = 0;
  struct weight *w;
  weight->poids = 1 / larray->nb_haar;

  for (int t = 1; t <= T; t++) 
  {
    best-stump(larray, w, 5);
    while (w != NULL)
    {
      Et += w->poids;
      w = w->next;
    }

    if (Et == 0 && t == 1)
      return h1;
    else
    {
      alpha = 0.5 * ln ((1 - Et) / Et);
      w->next->poids = (w->poids / 2) * ((1 / Et) + (1 / (1 - Et))); 
    }
  }

  return /*?*/ ;
}
