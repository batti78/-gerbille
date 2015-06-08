#ifndef RECT_H
#define RECT_H

#include<stdio.h>
#include<stdlib.h>

struct rect {
  int x;
  int y;
  int size_w;
  int size_h;
  unsigned long **integ;  
};

struct list_haar{
  long *array;
  int face;
  int ieme;
  struct list_haar *next;
};

struct stump{
  long t;
  int T;
  long M; 
  float E; 
};
#endif
