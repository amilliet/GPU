
#ifndef propagation_h
#define propagation_h

#include <stdio.h>
#include "utile.h"

#define DEPTH 16

int test_tas(int y, int x, int position, unsigned ocean[DIM][DIM], c couleurs[DIM][DIM]);
void propager(int y, int x, int position, unsigned ocean[DIM][DIM], c couleurs[DIM][DIM]);
int traiterProp(int y_d, int x_d, int y_f, int x_f, unsigned ocean[DIM][DIM], c couleurs[DIM][DIM]);

#endif /* propagation_h */
