#include <stdio.h>
#include <allegro5/allegro5.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>
#include "../../config/config.h"

void drawnpaused(ALLEGRO_BITMAP* menu_snapshot, int restart, ALLEGRO_FONT *font1, ALLEGRO_FONT *font2, ALLEGRO_FONT *font3, ALLEGRO_FONT *font4, ALLEGRO_FONT *font5, int txtHeight){
    // resume
    // restart (depois que o jogo estiver encaminhado)
    // options
    // Back to the main menu
    // Exit
    int distance = scale*10;
    al_draw_bitmap(menu_snapshot, 0, 0, 0);
    al_draw_filled_rectangle(0, 0, larguraEscolhida, alturaEscolhida, al_map_rgba(0, 0, 0, 180));
    if(!restart){
        al_draw_text(font1, al_map_rgba(255, 255, 255, 255), larguraEscolhida/2 - (400*scale), alturaEscolhida/2 - ((float)(2.0)*txtHeight) - distance*2, 0,"Resume");
        al_draw_text(font2, al_map_rgba(255, 255, 255, 255), larguraEscolhida/2 - (400*scale), alturaEscolhida/2 - ((float)(1.0)*txtHeight) - distance/2, 0,"Options");
        al_draw_text(font3, al_map_rgba(255, 255, 255, 255), larguraEscolhida/2 - (400*scale), alturaEscolhida/2 + distance/2, 0,"Back to main menu");
        al_draw_text(font4, al_map_rgba(255, 255, 255, 255), larguraEscolhida/2 - (400*scale), alturaEscolhida/2 + ((float)(1.0)*txtHeight) + distance * 2, 0,"Exit");
    }else{
        al_draw_text(font1, al_map_rgba(255, 255, 255, 255), larguraEscolhida/2 - (400*scale), alturaEscolhida/2 - ((float)(5.0/2.0)*txtHeight)- distance*2, 0,"Resume");
        al_draw_text(font5, al_map_rgba(255, 255, 255, 255), larguraEscolhida/2 - (400*scale), alturaEscolhida/2 - ((float)(3.0/2.0)*txtHeight) - distance, 0,"Restart");
        al_draw_text(font2, al_map_rgba(255, 255, 255, 255), larguraEscolhida/2 - (400*scale), alturaEscolhida/2 - ((float)(1.0/2.0)*txtHeight), 0,"Options");
        al_draw_text(font3, al_map_rgba(255, 255, 255, 255), larguraEscolhida/2 - (400*scale), alturaEscolhida/2 + ((float)(1.0/2.0)*txtHeight)+ distance, 0,"Back to main menu");
        al_draw_text(font4, al_map_rgba(255, 255, 255, 255), larguraEscolhida/2 - (400*scale), alturaEscolhida/2 + ((float)(3.0/2.0)*txtHeight) + distance*2, 0,"Exit");
    }
    al_flip_display();
}
