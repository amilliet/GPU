#include "basic.h"


int traiter(int y_d, int x_d, int y_f, int x_f, unsigned ocean[DIM][DIM], c couleurs[DIM][DIM]){
    int changement = 0;

#pragma omp parallel for collapse(2) //reduction(+:ocean[y][x],ocean[y][x-1],ocean[y][x+1],ocean[y-1][x],ocean[y + 1][x])
    for (int y = y_d; y < y_f; y++)
    {
        for (int x = x_d; x < x_f ; x++){
            int move = 0;
            if (ocean[y][x] >= 4){
                int div4 = ocean[y][x] / 4;
#pragma critical
            {
                ocean[y][x] = ocean[y][x]  % 4;
                ocean[y][x-1] += div4;
                ocean[y][x+1] += div4;
                ocean[y-1][x] += div4;
                ocean[y + 1][x] += div4;
            }
                changement = 1;
                move = 1;
            }
#ifdef DISPLAY
            coloring(y,x-1,move, ocean, couleurs);
            coloring(y,x+1,move, ocean, couleurs);
            coloring(y-1,x,move, ocean, couleurs);
            coloring(y+1,x,move, ocean, couleurs);
            coloring(y,x,move,ocean, couleurs);
#endif
            //int tid = omp_get_thread_num();
            //printf("Hello World from thread = %d\n", tid);
        }
        
    }
    return changement;
}
