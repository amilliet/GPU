
#define _XOPEN_SOURCE 600

#include "display.h"

#include <stdio.h>
#include <stdlib.h>

//////////////////////////////////////////////////////////////////////////
// Tas de sable "fake" (juste pour tester)

#define DIM 5
#define MAX_HEIGHT 16
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
    ocean[2][2] = dmax2;
    /*
     for (int y = 0; y < DIM; y++)
     for (int x = 0; x < DIM; x++) {
     ocean[y][x] = MAX_HEIGHT ;
     }
     */
    
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
            }
            
        }
    }
    return DYNAMIC_COLORING; // altitude-based coloring
    // return couleurs;
}

// Optimisation sequentielle
float *compute_sequetielle (unsigned iterations)
{
    static int step = 0;
    for (unsigned i = 0; i < iterations; i++)
    {
        step++;
        
        int div4 = 0;
        int tmp1 = ocean[0][0];
        
        for (int y = DEBUT; y < FIN; y++)
        {
            for (int x = DEBUT; x < FIN ; x++){
                int tmp = ocean[y][x];
                
                div4 = tmp1 / 4;
                int oc1 = ocean[y][x+1] / 4 + ocean[y+1][x] / 4;
                
                if ( oc1 > 0 || div4 > 0){
                    ocean[y][x] = tmp % 4 + oc1;
                }
                
                if ( div4 > 0 ){
                    ocean[y][x+1] += div4;
                    ocean[y+1][x] += div4;
                }
                
                tmp1 = ocean[y][x+1];
                
            }
            
        }
    }
    return DYNAMIC_COLORING; // altitude-based coloring
    // return couleurs;
}



int main (int argc, char **argv)
{
    sable_init ();
    
    display_init (argc, argv,
                  DIM,              // dimension ( = x = y) du tas
                  MAX_HEIGHT,       // hauteur maximale du tas
                  get,              // callback func
                  compute);         // callback func
    
    return 0;
}
