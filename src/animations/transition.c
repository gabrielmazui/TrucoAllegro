#include <stdio.h>
#include <allegro5/allegro5.h>

#include "..\..\config\config.h"
#include "transition.h"


void loadRects(int* grupoAy1, int* grupoAy2){
    int i;
    for(i = 0; i < total_rects; i++){
        grupoAy1[i] = alturaEscolhida + (50*i*scale);
        grupoAy2[i] = (alturaEscolhida * 2) + (50*i*scale);
    }
}

void refreshRect1(int* grupoAy1, int* grupoAy2){
    for(int i=1; i <= total_rects; i++){
        al_draw_filled_rectangle((i-1)*rect_largura, grupoAy1[i-1], i*rect_largura, grupoAy2[i-1], al_map_rgba(0, 0, 0, 255));
    }
    al_flip_display();
}

void refreshRect2(int* grupoAy1, int* grupoAy2, ALLEGRO_BITMAP* menu_snapshot){
    al_draw_bitmap(menu_snapshot, 0, 0, 0);
    for(int i=1; i <= total_rects; i++){
        al_draw_filled_rectangle((i-1)*rect_largura, grupoAy1[i-1], i*rect_largura, grupoAy2[i-1], al_map_rgba(0, 0, 0, 255));
    }
    al_flip_display();
}

void animationTransition(int* animReady, ALLEGRO_BITMAP* menu_snapshot, int* firstExec, int* animationP1, int* animationPaused, double* timePaused, int* auxEnd, int* auxEnd2, int* grupoAy1, int* grupoAy2){
    if(*firstExec){
        loadRects(grupoAy1, grupoAy2);
    }
    if(!*animationP1){
        if(grupoAy1[total_rects-1] == 0){
            *animationP1 = 1;
            *animationPaused = 1;
            *timePaused = al_get_time();
            refreshRect2(grupoAy1, grupoAy2, menu_snapshot);
        }else{
            for(int i = 0; i < total_rects; i++){
                int m = ((grupoAy1[i] - speed) >= 0) ? speed : grupoAy1[i];
                grupoAy1[i] -= m;
                grupoAy2[i] -= m;
            }
            refreshRect1(grupoAy1, grupoAy2);
        }
    }
    if(*animationPaused && (al_get_time() - *timePaused) >= 2.0){
        *animationPaused = 0;
    }
    if(*animationP1 && !*animReady && !*animationPaused){
        if(grupoAy1[total_rects-1] == alturaEscolhida){
            *animReady = 1;
        }else{
            for(int i = 0; i < total_rects; i++){
                if(i <= *auxEnd){
                    int m = ((grupoAy1[i] + speed) <= alturaEscolhida) ? speed : alturaEscolhida - grupoAy1[i];
                    grupoAy1[i] += m;
                    grupoAy2[i] += m;
                    *auxEnd2 = (*auxEnd2 == 0) ? 1 : 0;
                }
            }
            if(*auxEnd < total_rects -1 && *auxEnd2 == 0){
                *auxEnd += 1;
            }
            refreshRect2(grupoAy1, grupoAy2, menu_snapshot);
        }
    }
}
