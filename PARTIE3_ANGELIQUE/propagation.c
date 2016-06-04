
#include "propagation.h"
#define NB_THREADS 4




void propager(int y, int x, int deep, unsigned ocean[DIM][DIM],int num_thread, int nb_lines,int **tmp){
    if(deep < DEPTH){
        if (y > num_thread*nb_lines-DEPTH && y>=DEBUT && x > DEBUT && y+1 < FIN &&  y+1 < (num_thread+1)*nb_lines+DEPTH && x+1 < FIN){
            test_tas(y, x-1, deep, ocean,num_thread,nb_lines,tmp);
            //test_tas(y, x+1, deep, ocean);
            test_tas(y-1, x, deep, ocean,num_thread,nb_lines,tmp);
            //test_tas(y+1, x, deep, ocean);
        }
    }
}

int test_tas(int y, int x, int deep, unsigned ocean[DIM][DIM], int num_thread, int nb_lines, int **tmp){
    int changement = 0;
    int position = in_my_depth_domain(num_thread, nb_lines, y);
    if ((position != 0)){
        int tmp_line = y-num_thread*nb_lines-DEPTH;
        if(position > 0){
            tmp_line = y-num_thread*nb_lines;
        }
        if(tmp[y-num_thread*nb_lines-DEPTH][x] >= 4){
            int div4 = tmp[tmp_line][x] / 4;
            tmp[tmp_line][x] = tmp[tmp_line][x]  % 4;
            tmp[tmp_line][x] += div4;
            tmp[tmp_line][x] += div4;
            
            if(position <= -1){ //&& position + DEPTH + 1 >= 0){
                tmp[tmp_line-1][x] += div4;
                if(position == -1){
                    ocean[y+1][x] += div4;
                }else{
                    tmp[tmp_line+1][x] += div4;
                }
            }else if(position >= nb_lines){
                tmp[tmp_line+1][x] += div4;
                if(position == nb_lines){
                    ocean[y-1][x] += div4;
                }else{
                    tmp[tmp_line-1][x] += div4;
                }
                ocean[y+1][x] += div4;
            }
        }
        
        propager(y,x, deep+1, ocean, num_thread,nb_lines,tmp);
        changement = 1;
    }else{
        position = in_my_domain(num_thread,nb_lines,y);
        if (position !=-1) {
        if (ocean[y][x] >= 4){
            int div4 = ocean[y][x] / 4;
            ocean[y][x] = ocean[y][x]  % 4;
            ocean[y][x-1] += div4;
            ocean[y][x+1] += div4;
            
            if(position >= 0){
                ocean[y-1][x] += div4;
            }
            if(position == 0){
                tmp[y-num_thread*nb_lines-DEPTH-1][x] += div4;
                 ocean[y+1][x] += div4;
            }
            if(position < (num_thread+1)*nb_lines && position > 0){
                ocean[y-1][x] += div4;
                
                if(position == (num_thread+1)*nb_lines -1){
                    tmp[y-num_thread*nb_lines+1][x] += div4;
                }else{
                    ocean[y+1][x] += div4;
                }
            }

            
            propager(y,x, deep+1, ocean, num_thread,nb_lines,tmp);
            changement = 1;
            
        }
        }
    }
    
    return changement;
}

int in_my_domain(int num_thread, int nb_lines, int y){
    if(y >= num_thread*nb_lines && y < (num_thread+1)*nb_lines){
        return y-num_thread*nb_lines;
    }
    return -1;
}

int in_my_depth_domain(int num_thread, int nb_lines, int y){
    if((y < num_thread*nb_lines && y >= num_thread*nb_lines-DEPTH) || (y >= (num_thread+1)*nb_lines && y < num_thread*nb_lines+DEPTH)){
        return y - num_thread*nb_lines;
    }
    return 0;
}

int traiterProp(int y_d, int x_d, int y_f, int x_f, unsigned ocean[DIM][DIM], c couleurs[DIM][DIM]){
    int changement = 0;
    
    // Nombre de lignes par thread
    int nb_lines = ceil(1.0*DIM/NB_THREADS);
    int num_thread = 0;
#pragma omp parallel num_threads(NB_THREADS) shared(num_thread)
    {
        int my_num = num_thread;
        num_thread++;
        int tmp_lines;
        if(my_num > 0 && (my_num+1)*nb_lines< DIM ){
            tmp_lines = 2*DEPTH;
            
        }else if(my_num == 0 || (my_num+1)*nb_lines >= DIM ){
            tmp_lines = DEPTH;
        }else{
            tmp_lines = 0;
        }
        
        printf("my_num : %d | tmp_line: %d \n",my_num,tmp_lines);
        int tmp[tmp_lines][DIM];
        int cursor = 0;
        
        // Les parties centrales
        if(tmp_lines == 2*DEPTH){
            printf("my num : %d",my_num);
            for(int y = my_num*nb_lines-DEPTH; y < my_num*nb_lines; y++){
                for (int x = DEBUT; x < FIN; x++){
                    tmp[cursor][x] = ocean[y][x];
                    tmp[cursor+DEPTH][x] = ocean[y+nb_lines][x];
                    
                    printf("%d %d\n",tmp[cursor][x], tmp[cursor+DEPTH][x]);
                }
                cursor++;
            }
        }else if (my_num == 0){
            printf("my num : %d",my_num);
            for(int y = (my_num+1)*nb_lines; y < (my_num+1)*nb_lines+DEPTH; y++){
                for (int x = DEBUT; x < FIN; x++){
                    tmp[cursor][x] = ocean[y][x];
                    printf("%d ", tmp[cursor][x]);
                }
                printf("\n");
                cursor++;
            }
        }else if ((my_num+1)*nb_lines >= DIM ) {
            printf("my num : %d",my_num);
            for(int y = my_num*nb_lines-DEPTH; y < FIN; y++){
                for (int x = DEBUT; x < FIN; x++){
                    tmp[cursor][x] = ocean[y][x];
                    printf("%d ", tmp[cursor][x]);
                }
                printf("\n");
                cursor++;
            }
        }
        
//#pragma omp for schedule(static)
        for (int y = my_num*nb_lines; y < ((my_num+1)*nb_lines) ; y++){
            if (y < DIM){
                
                printf(" t: %d y: %d ",my_num, y);
                for (int x = 0; x < DIM; x++) {
                    int move = test_tas(y,x, 0, ocean,  my_num,nb_lines,tmp);
                    
                    if (move == 1){
                        changement = 1;
                    }
                }
            }
        }
        
    }
    return changement;
}