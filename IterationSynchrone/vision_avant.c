
#include "vision_avant.h"


int traiter_vision_avant_parallele (int y_d, int x_d, int y_f, int x_f, unsigned ocean[DIM][DIM],c couleurs[DIM][DIM], int nb_threads){
    int div4 = 0;
    int oc1 = 0;
    int move = 0;
    int changement = 0;
    /*
     First line
     
     See only if ocean[DEBUT][x] (the case y+1) have something to give
     */
//#pragma omp parallel for  num_threads(nb_threads) private(oc1,div4,move)
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
    
    
    // Copy the second line of ocean
    int tmp_col[x_f - x_d + 1];
  
//#pragma omp parallel for num_threads(nb_threads) private(oc1,div4,move)
    for (int x = x_d; x < x_f; x++){
        tmp_col[x] = ocean[y_d][x];
    }
    
    for (int y = y_d; y < y_f; y++)
    {
        move = 0;
        
        // First column
        oc1 = tmp_col[x_d] / 4;
        
        if ( oc1 > 0 ){
            ocean[y][x_d-1] += oc1;
            move = 1;
            changement = 1;
        }
#ifdef DISPLAY
        coloring(y,DEBUT-1,move,ocean, couleurs);
        move = 0;
#endif
        
        // Center
        
#pragma omp parallel for  num_threads(nb_threads) private(oc1,div4,move)
        for (int x = x_d; x < x_f; x++){
            
            div4 = tmp_col[x] / 4;
            
            // Don't take the last column
            if (x+1 < x_f){
                oc1 = tmp_col[x+1] / 4;
                
            }else{
                oc1 = 0;
            }
            
            // Don't take the last line
            if (y+1 < y_f){
                oc1 += ocean[y+1][x] / 4;
            }
            
            if ( oc1 > 0 || div4 > 0){
                int mod = tmp_col[x] % 4;
#pragma omp critical
                {
                if (ocean[y][x] == tmp_col[x]){
                    ocean[y][x] = mod + oc1;
                }else{
                    ocean[y][x] = mod + oc1 + ocean[y][x] - tmp_col[x];
                }
                }
                changement = 1;
                move = 1;
            }
#ifdef DISPLAY
            coloring(y,x,move,ocean,couleurs);
            move = 0;
#endif
            
            tmp_col[x] = ocean[y+1][x];
            
            
            if ( div4 > 0 ){
#pragma omp critical
                {
                ocean[y][x+1] += div4;
                ocean[y+1][x] += div4;
                }
                changement = 1;
                move = 1;
            }

#ifdef DISPLAY
            coloring(y,x+1,move,ocean,couleurs);
            coloring(y+1,x,move,ocean,couleurs);
#endif
        }
        
    }
    return changement;
}





int traiter_vision_avant_sequentielle (int y_d, int x_d, int y_f, int x_f, unsigned ocean[DIM][DIM],c couleurs[DIM][DIM]){
    int div4 = 0;
    int oc1 = 0;
    int move = 0;
    int changement = 0;
    /*
     First line
     
     See only if ocean[DEBUT][x] (the case y+1) have something to give
     */
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
    
    
    // Copy the second line of ocean
    int tmp_col[x_f - x_d + 1];
    //printf("\n ligne 0 : ");
    for (int x = x_d; x < x_f; x++){
        tmp_col[x] = ocean[y_d][x];
    }
    
    
    for (int y = y_d; y < y_f; y++)
    {
        move = 0;
        
        // First column
        oc1 = tmp_col[x_d] / 4;
        
        if ( oc1 > 0 ){
            ocean[y][x_d-1] += oc1;
            move = 1;
            changement = 1;
        }
#ifdef DISPLAY
        coloring(y,DEBUT-1,move,ocean, couleurs);
        move = 0;
#endif
        
        // Center
        
        
        for (int x = x_d; x < x_f; x++){
            
            div4 = tmp_col[x] / 4;
            
            // Don't take the last column
            if (x+1 < x_f){
                oc1 = tmp_col[x+1] / 4;
            }else{
                oc1 = 0;
            }
            
            // Don't take the last line
            if (y+1 < y_f){
                oc1 += ocean[y+1][x] / 4;
            }
            
            if ( oc1 > 0 || div4 > 0){
                int mod = tmp_col[x] % 4;
                if (ocean[y][x] == tmp_col[x]){
                    ocean[y][x] = mod + oc1;
                }else{
                    ocean[y][x] = mod + oc1 + ocean[y][x] - tmp_col[x];
                }
                changement = 1;
                move = 1;
            }
#ifdef DISPLAY
            coloring(y,x,move,ocean,couleurs);
            move = 0;
#endif
            
            if (tmp_col[x] != ocean[y+1][x] && y < y_f - 1){
                tmp_col[x] = ocean[y+1][x];
            }
            
            if ( div4 > 0 ){
                ocean[y][x+1] += div4;
                ocean[y+1][x] += div4;
                changement = 1;
                move = 1;
            }
#ifdef DISPLAY
             coloring(y,x+1,move,ocean,couleurs);
             coloring(y+1,x,move,ocean,couleurs);
#endif
        }
        
    }
    return changement;
}