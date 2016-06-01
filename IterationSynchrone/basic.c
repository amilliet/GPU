#include "basic.h"



int traiter_basic_parallele(int y_d, int x_d, int y_f, int x_f, unsigned ocean[DIM][DIM], c couleurs[DIM][DIM]){
    int changement = 0;
    static int a = 1;
#pragma omp parallel for num_threads(NB_THREAD) collapse(2) shared(ocean) schedule(static)
    for (int y = y_d; y < y_f; y++)
    {
        for (int x = x_d; x < x_f ; x++){
            int move = 0;
            if (ocean[y][x] >= 4){
                int div4 = ocean[y][x] / 4;
#pragma critical
                {
                ocean[y][x] = ocean[y][x]  % 4;
                ocean[y][x-1] = ocean[y][x-1] + div4;
                ocean[y][x+1] = ocean[y][x+1] + div4;
                ocean[y-1][x] = ocean[y-1][x] + div4;
                ocean[y + 1][x] = ocean[y + 1][x] + div4;
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
	    if(a == 1){
	      //	      int tid = omp_get_thread_num();
	      //printf("the thread = %d change (%d,%d)\n", tid,y,x);
	    }
	} 
        
    }
    a = 0;
    return changement;
}


int traiter_basic_sequentielle(int y_d, int x_d, int y_f, int x_f, unsigned ocean[DIM][DIM], c couleurs[DIM][DIM]){
    int changement = 0;
    for (int y = y_d; y < y_f; y++)
    {
        for (int x = x_d; x < x_f ; x++){
            int move = 0;
            if (ocean[y][x] >= 4){
                int div4 = ocean[y][x] / 4;
                ocean[y][x] = ocean[y][x]  % 4;
                ocean[y][x-1] += div4;
                ocean[y][x+1] += div4;
                ocean[y-1][x] += div4;
                ocean[y + 1][x] += div4;
                
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
        }
        
    }
    return changement;
}
