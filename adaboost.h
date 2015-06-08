#ifndef"ADABOOST_H"
#define"ADABOOST_H"

struct stump *decision_stump(struct list_haar *larray, float w*, unsigned long n, unsigned nbex);

struct stump *best_stump(struct list_haar *larray, float *w , int nbex, int d);

void adaboost(struct list_haar *larray, int nbex, int T);


#endif
