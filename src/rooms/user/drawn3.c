#include <stdio.h>
#include <allegro5/allegro5.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include "..\..\..\config\config.h"

void drawn3(int x, int x2, int txtX1, int txtX2, int txtY1, int txtY2, int centroY, int centroX, int y_ajustado, int alturaPergunta, int interrogacao, int whiteToRed, int blackToRed, ALLEGRO_FONT *font1 , ALLEGRO_FONT *font2){
    al_draw_tinted_scaled_bitmap(background, al_map_rgba(255, 255, 255, x), 0, 0, larguraB, alturaB, 0, 0, larguraEscolhida, alturaEscolhida, 0);
    al_draw_text(font1, al_map_rgba(255,229,32, x), larguraEscolhida/2, alturaPergunta, ALLEGRO_ALIGN_CENTRE,"Qual o seu Nome");
    al_draw_text(font1, al_map_rgba(255,229,32, x), larguraEscolhida/2 + (325*scale), interrogacao, ALLEGRO_ALIGN_CENTRE,"?");
    al_draw_filled_rectangle(txtX1, txtY1, txtX2, txtY2, al_map_rgba(blackToRed, 0, 0, x2));
    al_draw_rectangle(txtX1, txtY1, txtX2, txtY2, al_map_rgb(255, whiteToRed, whiteToRed), 2);
    al_draw_text(font2, al_map_rgba(255, whiteToRed, whiteToRed, x), centroX, y_ajustado, ALLEGRO_ALIGN_CENTRE,user.name);
    al_flip_display();
}