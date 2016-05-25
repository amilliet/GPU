
#define _XOPEN_SOURCE 600

#include "display.h"

#include <stdio.h>
#include <stdlib.h>

#define DIM 128 //5
#define MAX_HEIGHT 100000
#define DEBUT 1
#define FIN  DIM - 1


#define TIME_DIFF(t1, t2) \
((t2.tv_sec - t1.tv_sec) * 1000000 + (t2.tv_usec - t1.tv_usec))
#include <math.h>

unsigned ocean[DIM][DIM];

// vecteur de pixel renvoyé par compute
struct {
    float R, G, B;
} couleurs[DIM][DIM];

// callback
unsigned get (unsigned x, unsigned y)
{
    return ocean[y][x];
}

// Tas de sable initial
static void sable_init ()
{
    unsigned dmax2 = MAX_HEIGHT;
    ocean[DIM/2][DIM/2] = dmax2;
    /*
     for (int y = 0; y < DIM; y++)
     for (int x = 0; x < DIM; x++) {
     ocean[y][x] = MAX_HEIGHT ;
     }
    */
    
}

void print_ocean(){
    printf("\n");
    for (int i = 0; i < DIM; i++){
        for (int j = 0; j < DIM; j++){
            printf("%d ", ocean[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

/* move :
    - 0 : no mouvement
    - 1 else
 */
void coloring(int y, int x, int move){
    switch (move) {
        case 0:
            couleurs[y][x].B = 1;
            couleurs[y][x].G = 0;
            break;
        case 1:
            couleurs[y][x].B = 0;
            couleurs[y][x].G = 1;
            break;
            
        default:
            break;
    }
    
    if (ocean[y][x] >= 4){
        couleurs[y][x].R = 1.0;
        couleurs[y][x].B = 0;
    }else{
        couleurs[y][x].R = 1.0*(MAX_HEIGHT - ocean[y][x])*ocean[y][x]/ (2*MAX_HEIGHT);
    }
}

// Version basique
float *compute (unsigned iterations)
{
    static int step = 0;
    for (unsigned i = 0; i < iterations; i++)
    {
        step++;
        for (int y = DEBUT; y < FIN; y++)
        {
            for (int x = DEBUT; x < FIN ; x++){
                
                int div4 = ocean[y][x] / 4;
                ocean[y][x] = ocean[y][x]  % 4;
                ocean[y][x-1] += div4;
                ocean[y][x+1] += div4;
                ocean[y-1][x] += div4;
                ocean[y + 1][x] += div4;
                
                // VIEW
                int move;
                if (div4 >= 4){
                    move = 1;
                }else{
                    move = 0;
                }
                
                coloring(y,x-1,move);
                coloring(y,x+1,move);
                coloring(y-1,x,move);
                coloring(y+1,x,move);
                
                coloring(y,x,move);
            }
            
        }
    }
    print_ocean();
    //return DYNAMIC_COLORING; // altitude-based coloring
    return couleurs;
}


// Optimisation sequentielle
float *compute_sequetielle (unsigned iterations)
{
    static int step = 0;
    for (unsigned i = 0; i < iterations; i++)
    {
        step++;
        
        int div4 = 0;
        int oc1 = 0;
        int move = 0;
        
        /* 
            First line
            
            See only if ocean[DEBUT][x] (the case y+1) have something to give
         */
        for (int x = DEBUT; x < FIN ; x++){
            oc1 = ocean[DEBUT][x] / 4;
            
            if ( oc1 > 0 ){
                ocean[DEBUT-1][x] += oc1;
                move = 1;
            }
            
            coloring(DEBUT-1,x,move);
        }
        
        
        // Copy the second line of ocean
        int tmp_col[FIN - DEBUT + 1];
        printf("\n ligne 0 : ");
        for (int x = DEBUT; x < FIN; x++){
            tmp_col[x] = ocean[DEBUT][x];
            printf("%d ", tmp_col[x]);
        }
        
        
        for (int y = DEBUT; y < FIN; y++)
        {
            printf("\n");
            printf("ligne %d :", y+1);
            move = 0;
            
            // First column
            oc1 = tmp_col[DEBUT] / 4;
            
            if ( oc1 > 0 ){
                ocean[y][DEBUT-1] += oc1;
                move = 1;
            }
            
            coloring(y,DEBUT-1,move);
            
            // Center
            
            move = 0;
            
            for (int x = DEBUT; x < FIN; x++){
                
                div4 = tmp_col[x] / 4;
                
                // Don't take the last column
                if (x+1 < FIN){
                    oc1 = tmp_col[x+1] / 4;
                }else{
                    oc1 = 0;
                }
                
                // Don't take the last line
                if (y+1 < FIN){
                    oc1 += ocean[y+1][x] / 4;
                }
                
                if ( oc1 > 0 || div4 > 0){
                    int mod = tmp_col[x] % 4;
                    if (ocean[y][x] == tmp_col[x]){
                        ocean[y][x] = mod + oc1;
                    }else{
                        ocean[y][x] = mod + oc1 + ocean[y][x] - tmp_col[x];
                    }
                    
                    move = 1;
                }
                
                coloring(y,x,move);
                
                if (tmp_col[x] != ocean[y+1][x] && y < FIN - 1){
                    tmp_col[x] = ocean[y+1][x];
                }
                
                if (y < FIN - 1)
                    printf(" %d ", tmp_col[x]);
               
                move = 0;
                if ( div4 > 0 ){
                    ocean[y][x+1] += div4;
                    ocean[y+1][x] += div4;
                    
                    move = 1;
                }
                
                coloring(y,x+1,move);
                coloring(y+1,x,move);
            }
            
        }
    }
    print_ocean();
    return couleurs;
}





int main (int argc, char **argv)
{
    sable_init ();
    
    display_init (argc, argv,
                  DIM,              // dimension ( = x = y) du tas
                  MAX_HEIGHT,       // hauteur maximale du tas
                  get,              // callback func
                  compute_sequetielle);         // callback func
    
    return 0;
}
