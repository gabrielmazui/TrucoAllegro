#include <stdio.h>
#include <allegro5/allegro5.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include "..\..\..\config\config.h"

void drawn1(ALLEGRO_FONT *font1 , ALLEGRO_FONT *font2, int op1, int op2){
    al_clear_to_color(al_map_rgb(0, 0, 0));
    al_draw_text(font1, al_map_rgba(255, 255, 255, op1), (larguraEscolhida)/2, (alturaEscolhida/4) + (50*scale) , ALLEGRO_ALIGN_CENTRE,"Gabriel e Matheus");
    al_draw_text(font2, al_map_rgba(255, 255, 255, op2), (larguraEscolhida/2), (alturaEscolhida/4) + (150*scale), ALLEGRO_ALIGN_CENTRE,"Apresentam");
    al_flip_display();
}
