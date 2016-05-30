
#include "other_sequentielle.h"

#define NB 10

int traiter_sequentielle (int y_d, int x_d, int y_f, int x_f, unsigned ocean[DIM][DIM],c couleurs[DIM][DIM]){
    int div4 = 0;
    int oc1 = 0;
    int move = 0;
    int changement = 0;
    
    // Copy the second line of ocean
    int tmp[x_f - x_d + 1][x_f - x_d + 1];
    /*
     First line
     
     See only if ocean[DEBUT][x] (the case y+1) have something to give
     */
    
#pragma omp parallel for collapse(2) num_threads(NB)
    for (int y = y_d; y < y_f; y++)
    {
        for (int x = x_d; x < x_f; x++){
            tmp[y][x] = ocean[y][x];
        }
        
    }
    
#pragma omp parallel num_threads(NB) firstprivate(oc1,move,div4)
    {
#pragma omp for nowait
        for (int x = x_d; x < x_f ; x++){
            oc1 = ocean[y_d][x] / 4;
            
            if ( oc1 > 0 ){
                ocean[y_d-1][x] += oc1;
                changement = 1;
                move = 1;
            }
#ifdef DISPLAY
            coloring(DEBUT-1,x,move, ocean, couleurs);
#endif
        }
        
        
        
        
#pragma omp for collapse(2)
        for (int y = y_d; y < y_f; y++)
        {
            for (int x = 0; x < x_f; x++){
                
                if(x == 0){
                    move = 0;
                    
                    // First column
                    oc1 = tmp[y][x_d] / 4;
                    
                    if ( oc1 > 0 ){
                        ocean[y][x_d-1] += oc1;
                        move = 1;
                        changement = 1;
                    }
#ifdef DISPLAY
                    coloring(y,DEBUT-1,move,ocean, couleurs);
                    move = 0;
#endif
                }else{
                    div4 = tmp[y][x] / 4;
                    // Don't take the last column
                    if (x+1 < x_f){
                        oc1 = tmp[y][x+1] / 4;
                    }else{
                        oc1 = 0;
                    }
                    
                    if(x>x_d){
                        oc1 += tmp[y][x-1] / 4;
                    }
                    // Don't take the last line
                    if (y+1 < y_f){
                        oc1 += tmp[y+1][x] / 4;
                    }
                    
                    if(y>y_d){
                        oc1 += tmp[y-1][x] / 4;
                    }
                    
                    if ( oc1 > 0 || div4 > 0){
                        int mod = tmp[y][x] % 4;
                        ocean[y][x] = mod + oc1;
                        changement = 1;
                        move = 1;
                    }
#ifdef DISPLAY
                    coloring(y,x,move,ocean,couleurs);
                    move = 0;
#endif
                    
                    
                }
                oc1 = tmp[y][x_f-1] / 4;
                if ( oc1 > 0 ){
                    ocean[y][x_f] += oc1;
                    move = 1;
                    changement = 1;
                }
#ifdef DISPLAY
                coloring(y,x_f,move,ocean, couleurs);
                move = 0;
#endif
                
                
            }
        }
#pragma omp for nowait
        for (int x = x_d; x < x_f; x++){
            oc1 = tmp[y_f-1][x] / 4;
            
            if ( oc1 > 0 ){
                ocean[y_f][x] += oc1;
                move = 1;
                changement = 1;
            }
#ifdef DISPLAY
            coloring(y_f,x,move,ocean, couleurs);
            move = 0;
#endif
        }
        
    }
    
    return changement;
}