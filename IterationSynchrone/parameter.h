

#ifndef parameter_h
#define parameter_h

/*
    CHANGER LES TESTS
*/
//#define DISPLAY // Commenter pour faire les tests de performance
#define CENTRALE // Initialisation Configuration ou une case centrale comporte 10^5 éléments -- Commenter pour avoir la configuration homogène
#define OTHER

#define DIM 128
#define MAX_HEIGHT 100000
#define DEBUT 1
#define FIN  DIM - 1

#include <sys/time.h>
#include <omp.h>


// vecteur de pixel renvoyé par compute
typedef struct {
    float R, G, B;
} c;

typedef float * (*traiter_func_t) (int y_d, int x_d, int y_f, int x_f, unsigned ocean[DIM][DIM], c couleurs[DIM][DIM]);


#endif /* parameter_h */
