#ifndef TRANSITION_H
#define TRANSITION_H

#include "../../config/config.h"
#include <allegro5/allegro5.h>

#define speed 25*scale
#define rect_largura (larguraEscolhida / total_rects)

void animationTransition(int* animReady, ALLEGRO_BITMAP* menu_snapshot, int* firstExec, int* animationP1, int* animationPaused, double* timePaused, int* auxEnd, int* auxEnd2, int* grupoAy1, int* grupoAy2);

#endif
