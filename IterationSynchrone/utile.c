
#include "utile.h"

/* move :
 - 0 : no mouvement
 - 1 else
 */
void coloring(int y, int x, int move, unsigned ocean[DIM][DIM], c couleurs[DIM][DIM]){
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

void print_ocean(unsigned ocean[DIM][DIM]){
    printf("\n");
    for (int i = 0; i < DIM; i++){
        for (int j = 0; j < DIM; j++){
            printf("%d ", ocean[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}