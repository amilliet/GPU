#include "propagation.h"

void propager(int y, int x, int position, unsigned ocean[DIM][DIM], c couleurs[DIM][DIM]){
    if(position < DEPTH){
        if (y > DEBUT && x > DEBUT && y+1 < FIN && x+1 < FIN){
            test_tas(y, x-1, position, ocean, couleurs);
            //test_tas(y, x+1, position, ocean);
            test_tas(y-1, x, position, ocean, couleurs);
            //test_tas(y+1, x, position, ocean);
        }
    }
}

int test_tas(int y, int x, int position, unsigned ocean[DIM][DIM], c couleurs[DIM][DIM]){
    int changement = 0;
    if (ocean[y][x] >= 4){
        
       
#pragma omp critical
        {
        int div4 = ocean[y][x] / 4;
        ocean[y][x] = ocean[y][x]  % 4;
        ocean[y][x-1] += div4;
        ocean[y][x+1] += div4;
        ocean[y-1][x] += div4;
        ocean[y+1][x] += div4;
        }
#ifdef DISPLAY
        coloring(y,x-1,1, ocean, couleurs);
        coloring(y,x+1,1, ocean, couleurs);
        coloring(y-1,x,1, ocean, couleurs);
        coloring(y+1,x,1, ocean, couleurs);
        
        coloring(y,x,1, ocean, couleurs);
#endif
        
        propager(y,x, position+1, ocean, couleurs);
        changement = 1;
        
        
    }
    
    return changement;
}

int traiterProp(int y_d, int x_d, int y_f, int x_f, unsigned ocean[DIM][DIM], c couleurs[DIM][DIM]){
    int changement = 0;
#pragma omp parallel for collapse(2)
    for (int y = y_d; y < y_f; y++)
    {
        for (int x = x_d; x < x_f ; x++){
            int move = test_tas(y,x, 0, ocean, couleurs);
#ifdef DISPLAY
            coloring(y,x-1,move, ocean, couleurs);
            coloring(y,x+1,move, ocean, couleurs);
            coloring(y-1,x,move, ocean, couleurs);
            coloring(y+1,x,move, ocean, couleurs);
            
            coloring(y,x,move, ocean, couleurs);
#endif
            
            if (move == 1){
                changement = 1;
            }
        }
        
    }
    return changement;
}