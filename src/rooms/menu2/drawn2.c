#include <stdio.h>
#include <allegro5/allegro5.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include "..\..\..\config\config.h"

void drawn2(int alturaBackground, int alturaTitulo, int alturaPress, int opPlay, ALLEGRO_FONT *font1 , ALLEGRO_FONT *font2){
    al_draw_tinted_scaled_bitmap(background, al_map_rgba(255, 255, 255, 255), 0, 0, larguraB, alturaB, 0, alturaBackground, larguraEscolhida, alturaEscolhida, 0); // posicao da original, tamanho dela, novo tamanho, e posicao do display
    al_draw_text(font1, al_map_rgb(255,229,32), larguraEscolhida/2, alturaTitulo, ALLEGRO_ALIGN_CENTRE,"Truco");
    al_draw_text(font2, al_map_rgba(255,255,255, opPlay), larguraEscolhida/2, alturaPress, ALLEGRO_ALIGN_CENTER, "Press to play");

    al_flip_display();

}
