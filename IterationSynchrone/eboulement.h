
#ifndef basic_h
#define basic_h

#include <stdio.h>

#include "parameter.h"
#include "utile.h"

int traiter_eboulement_sequentielle(int y_d, int x_d, int y_f, int x_f, unsigned ocean[DIM][DIM], c couleurs[DIM][DIM]);
int traiter_eboulement_parallele(int y_d, int x_d, int y_f, int x_f, unsigned ocean[DIM][DIM], c couleurs[DIM][DIM], int nb_threads);

#endif /* basic_h */
