

#ifndef other_sequentielle_h
#define other_sequentielle_h

#include <stdio.h>

#include "parameter.h"
#include "utile.h"


int traiter_vision_voisin_avant_sequentielle (int y_d, int x_d, int y_f, int x_f, unsigned ocean[DIM][DIM], c couleurs[DIM][DIM]);
int traiter_vision_voisin_avant_parallele (int y_d, int x_d, int y_f, int x_f, unsigned ocean[DIM][DIM],c couleurs[DIM][DIM], int nb_threads)

#endif /* other_sequentielle_h */
