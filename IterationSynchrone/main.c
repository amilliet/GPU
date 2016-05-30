
#define _XOPEN_SOURCE 600

#include "display.h"
#include "basic.h"
#include "other_sequentielle.h"
#include <stdio.h>
#include <stdlib.h>



#define TIME_DIFF(t1, t2) \
((t2.tv_sec - t1.tv_sec) * 1000000 + (t2.tv_usec - t1.tv_usec))
#include <math.h>

unsigned ocean[DIM][DIM];

c couleurs[DIM][DIM];

// callback
unsigned get (unsigned x, unsigned y)
{
    return ocean[y][x];
}

// Tas de sable initial

static void homogene__sable_init ()
{
    for (int y = 0; y < DIM; y++){
        for (int x = 0; x < DIM; x++) {
            ocean[y][x] = 5;
        }
    }
    
}

static void centrale_case__sable_init ()
{
    unsigned dmax2 = MAX_HEIGHT;
    ocean[DIM/2][DIM/2] = dmax2;
    
}



// Version basique

float *compute (unsigned iterations)
{
    static int step = 0;
    for (unsigned i = 0; i < iterations; i++)
    {
        step++;
        int changement = traiter(DEBUT, DEBUT, FIN, FIN, ocean, couleurs);
    }
    
    return couleurs;
}

// Optimisation sequentielle



float *compute_sequetielle (unsigned iterations)
{
    static int step = 0;
    for (unsigned i = 0; i < iterations; i++)
    {
        step++;
        
        int changement = traiter_sequentielle(DEBUT, DEBUT, FIN, FIN, ocean, couleurs);
    }
    //print_ocean();
    return couleurs;
}


int main (int argc, char **argv)
{
#ifdef CENTRALE
    centrale_case__sable_init();
#else
    homogene__sable_init ();
#endif
    
    
#ifdef OTHER
    compute_func_t c = compute_sequetielle;
    traiter_func_t t = traiter_sequentielle;
#else
    compute_func_t c = compute;
    traiter_func_t t = traiter;
#endif
    
    
#ifdef DISPLAY
    
    display_init (argc, argv,
                  DIM,              // dimension ( = x = y) du tas
                  MAX_HEIGHT,       // hauteur maximale du tas
                  get,              // callback func
                  c);               // callback func
    
#else
    
    struct timeval t1, t2;
    
    gettimeofday(&t1, NULL);
    int i = 0;
    
    
    while(t(DEBUT, DEBUT, FIN, FIN, ocean, couleurs))
    {
        i++;
    }
    gettimeofday(&t2, NULL);
    printf("Temps d'exécution basic: %f ms\n",((float)TIME_DIFF(t1,t2)) / 1000);
    printf("steep %d\n", i);
    
#endif
   
    return 0;
}
