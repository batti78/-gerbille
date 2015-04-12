#include <haar.h>

struct weight{             //structure pour les poids
  float poids;             //sous forme de list chainée
  struct weight *next;
  int face;                //Si visage = 1 sinon -1 
};

struct list_haar{   //structure liste de haar
  struct haar *array;
  struct list_haar *next;
  int nb_haar;
};


struct stump{
  long t;    //Treshold
  int T;     //Toggle
  long M;    //Margin
  float E;   //Error
};
