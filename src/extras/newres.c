#include <stdio.h>
#include <allegro5/allegro5.h>
#include "..\..\config\config.h"
#include "..\rooms\menu1\menu1.h"
void newres(void){
    scale = fmin(((float)larguraEscolhida / LARGURA_TELA), ((float)alturaEscolhida /ALTURA_TELA));
    if(fullscreen){
        al_set_new_display_flags(ALLEGRO_OPENGL | ALLEGRO_FULLSCREEN_WINDOW);
    }else{
        al_set_new_display_flags(ALLEGRO_OPENGL | ALLEGRO_WINDOWED);
    }
    display = al_create_display(larguraEscolhida, alturaEscolhida);
    al_set_window_position(display, 0, 0);
    al_set_window_title(display, "Truco");
    al_register_event_source(event_queue, al_get_display_event_source(display));
    al_set_target_backbuffer(display);
    menuLoop1();
}