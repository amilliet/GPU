
#ifndef propagation_h
#define propagation_h

#include <stdio.h>
#include "utile.h"

#define DEPTH 3

int test_tas(int y, int x, int deep, unsigned ocean[DIM][DIM], int num_thread, int nb_lines, int tmp[2*DEPTH][DIM]);
void propager(int y, int x, int deep, unsigned ocean[DIM][DIM],int num_thread, int nb_lines,int tmp[2*DEPTH][DIM]);
int traiterProp(int y_d, int x_d, int y_f, int x_f, unsigned ocean[DIM][DIM], c couleurs[DIM][DIM]);


int in_my_domain(int num_thread, int nb_lines, int y);
int in_my_depth_domain(int num_thread, int nb_lines, int y);

#endif /* propagation_h */
