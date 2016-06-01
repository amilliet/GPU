
#ifndef basic_h
#define basic_h

#include <stdio.h>

#include "parameter.h"
#include "utile.h"

int traiter_basic_sequentielle(int y_d, int x_d, int y_f, int x_f, unsigned ocean[DIM][DIM], c couleurs[DIM][DIM]);
int traiter_basic_parallele(int y_d, int x_d, int y_f, int x_f, unsigned ocean[DIM][DIM], c couleurs[DIM][DIM]);

#endif /* basic_h */
