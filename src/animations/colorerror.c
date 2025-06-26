#include <stdio.h>
#include <allegro5/allegro5.h>

void colorErrAnimation(int* upRed, int* ColorAnimInitiated, int* colorAnimHappening, int* whiteToRed, int* blackToRed){
    if(!*ColorAnimInitiated){
        *whiteToRed -=15;
        *blackToRed +=15;
        *ColorAnimInitiated = 1;
    }else{
        if(*upRed){
            if(*whiteToRed == 0 && *blackToRed == 255){
                *upRed = 0;
                *whiteToRed +=15;
                *blackToRed -=15;
             }else{
                *whiteToRed -=15;
                *blackToRed +=15;
            }
        }else{
            if(*whiteToRed == 255 && *blackToRed == 0){
                *upRed = 1;
                *colorAnimHappening = 0;
                return;
            }else{
                *whiteToRed +=15;
                *blackToRed -=15;
            }
        }
    }
}