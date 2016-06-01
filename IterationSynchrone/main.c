
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
        int changement = traiter_basic_parallele(DEBUT, DEBUT, FIN, FIN, ocean, couleurs);
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
        
        int changement = traiter_vision_voisin_parallele(DEBUT, DEBUT, FIN, FIN, ocean, couleurs);
    }
    //print_ocean();
    return couleurs;
}


int main (int argc, char **argv)
{
#ifdef CENTRALE
    int i = 0;
    centrale_case__sable_init();
#else
    int i = 1;
    homogene__sable_init ();
#endif
    
    
#ifdef OTHER
    compute_func_t c = compute_sequetielle;
    traiter_func_t ts = traiter_vision_voisin_sequentielle;
    traiter_func_t tp = traiter_vision_voisin_parallele;
#else
    compute_func_t c = compute;
    traiter_func_t ts = traiter_basic_sequentielle;
    traiter_func_t tp = traiter_basic_parallele;

#endif
    
    
#ifdef DISPLAY
    
    display_init (argc, argv,
                  DIM,              // dimension ( = x = y) du tas
                  MAX_HEIGHT,       // hauteur maximale du tas
                  get,              // callback func
                  c);               // callback func
    
#elifdef ACC
    
    
    FILE *f = NULL;
    f = fopen("./../Courbe/test.data","a");
    
    
    for(int t=0; t<24; t++){
        //initilisation du tas de sable
        if (i == 0){
            centrale_case__sable_init();
        }else{
            homogene__sable_init();
        }
        
        struct timeval t1, t2, t3, t4;
        gettimeofday(&t1, NULL);
        while(tp(DEBUT, DEBUT, FIN, FIN, ocean, couleurs)){}
        gettimeofday(&t2, NULL);
        
        //initilisation du tas de sable
        if (i == 0){
            centrale_case__sable_init();
        }else{
            homogene__sable_init();
        }
        
        gettimeofday(&t3, NULL);
        while(ts(DEBUT, DEBUT, FIN, FIN, ocean, couleurs)){}
        gettimeofday(&t4, NULL);
        
        printf("%g / %g  = acceleration = %g\n", TIME_DIFF(t1,t2) / 1000,  TIME_DIFF(t3,t4) / 1000, TIME_DIFF(t3,t4)/TIME_DIFF(t1,t2));
        
        
        if (f != NULL)
        {
            fprintf(f,"%d  %f\n",NB_THREAD,1.0*TIME_DIFF(t3,t4)/TIME_DIFF(t1,t2));
        }
        else
        {
            printf("Impossible d'ouvrir le fichier");
        }
    }
    
    fclose(f);
    
#else
    struct timeval t1, t2;
    
    
    
    gettimeofday(&t1, NULL);
    int j = 0;
    
    while(tp(DEBUT, DEBUT, FIN, FIN, ocean, couleurs))
    {
        j++;
    }
    gettimeofday(&t2, NULL);
    print_ocean(ocean);
    printf("Temps d'exécution basic: %f ms\n",((float)TIME_DIFF(t1,t2)) / 1000);
    printf("steep %d\n", j);
#endif
   
    return 0;
}
