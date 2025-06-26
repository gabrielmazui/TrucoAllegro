#include <stdio.h>
#include <allegro5/allegro5.h>

void interrogacaoAnim(int * up, int * timesDone, double* lastTimeDone, int* animPiscaStart, int *interrogacao){
    if(!*animPiscaStart){
        *animPiscaStart = 1;
        *lastTimeDone = al_get_time();
        (*timesDone)++;
        *interrogacao += 4;
        return;
    }
    if((al_get_time() - *lastTimeDone) >= 0.85){
        if(up){
            if(*timesDone<3){
                (*timesDone)++;
                *interrogacao += 5;
                *lastTimeDone = al_get_time();
            }else{
                *up = 0;
                (*timesDone)--;
                *interrogacao -=5;
                *lastTimeDone = al_get_time();
            }
        }else{
            if(*timesDone>-1){
                (*timesDone)--;
                *interrogacao -=5;
                *lastTimeDone = al_get_time();
            }else{
                *up = 1;
                (*timesDone)++;
                *interrogacao += 5;
                *lastTimeDone = al_get_time();
            }
        }
    }
}
