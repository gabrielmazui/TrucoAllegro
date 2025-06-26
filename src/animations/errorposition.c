#include <stdio.h>
#include <allegro5/allegro5.h>
#include "..\..\config\config.h"


void errorAnimation(double* cooldownAux, int* cooldownAuxInitiated, int* direitaErr, int* quantErr, int* errorAnimationHappening, int* txtX1, int* txtX2, float* centroX){
    int mv = 4*scale;
    if(*quantErr == 6){
        *quantErr = 0;
        *errorAnimationHappening = 0;
        *cooldownAuxInitiated = 0;
    }
    if(!*cooldownAuxInitiated){
        *txtX1 +=mv;
        *txtX2 +=mv;
        *centroX +=mv;
        *direitaErr = 0;
        *cooldownAuxInitiated = 1;
        *cooldownAux = al_get_time();
        (*quantErr)++;
    }else if(al_get_time() - *cooldownAux >=0.05){
        if(*direitaErr==1){
            *direitaErr = 0;
            *txtX1 +=mv;
            *txtX2 +=mv;
            *centroX +=mv;
            *cooldownAux = al_get_time();
            (*quantErr)++;
        }else{
            *direitaErr = 1;
            *txtX1 -=mv;
            *txtX2 -=mv;
            *centroX -=mv;
            *cooldownAux = al_get_time();
            (*quantErr)++;
        }
    }
}
