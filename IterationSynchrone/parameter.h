

#ifndef parameter_h
#define parameter_h

/*
    CHANGER LES TESTS
*/
//#define DISPLAY // Commenter pour faire les tests de performance
#define CENTRALE // Initialisation Configuration ou une case centrale comporte 10^5 éléments -- Commenter pour avoir la configuration homogène

#define DIM 128 //5
#define MAX_HEIGHT 100000
#define DEBUT 1
#define FIN  DIM - 1

#include <sys/time.h>


// vecteur de pixel renvoyé par compute
typedef struct {
    float R, G, B;
} c;


#endif /* parameter_h */
