#include <stdio.h>
#include <allegro5/allegro5.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include "..\..\..\config\config.h"

void drawn4(int x, ALLEGRO_FONT *font, ALLEGRO_BITMAP* img1, ALLEGRO_BITMAP* img2, int pfpChoosed){
    al_draw_tinted_scaled_bitmap(background, al_map_rgba(255, 255, 255, x), 0, 0, larguraB, alturaB, 0, 0, larguraEscolhida, alturaEscolhida, 0);
    al_draw_text(font, al_map_rgb(255,229,32), larguraEscolhida/2, alturaEscolhida/2 - (300*scale), ALLEGRO_ALIGN_CENTRE, "Escolha o seu personagem");
    al_draw_scaled_bitmap(img1,0, 0, al_get_bitmap_width(img1), al_get_bitmap_height(img1),larguraEscolhida/2 - (100*scale) - (200*scale), alturaEscolhida/2 +(50*scale) - (200*scale), 200*scale, 200*scale, 0);
    al_draw_scaled_bitmap(img2,0, 0, al_get_bitmap_width(img2), al_get_bitmap_height(img2), larguraEscolhida/2 + (100*scale), alturaEscolhida/2 + (50*scale) - (200*scale), 200*scale, 200*scale, 0);
    al_draw_scaled_bitmap(img1,0, 0, al_get_bitmap_width(img1), al_get_bitmap_height(img1), larguraEscolhida/2 - (100*scale) - (200*scale), alturaEscolhida/2 + (100*scale), 200*scale, 200*scale, 0);
    al_draw_scaled_bitmap(img1,0, 0, al_get_bitmap_width(img1), al_get_bitmap_height(img1), larguraEscolhida/2 + (100*scale), alturaEscolhida/2 + (100*scale), 200*scale, 200*scale, 0);
    
    int compX1 = larguraEscolhida/2 - (100*scale) - (200*scale);
    int compX2 = compX1 + 200*scale;
    int compX3 = larguraEscolhida/2 + (100*scale);
    int compX4 = compX3 + 200*scale;

    int compY1 = alturaEscolhida/2 +(50*scale) - (200*scale);
    int compY2 = compY1 + (200*scale);
    int compY3 = alturaEscolhida/2 + (100*scale);
    int compY4 = compY3 + (200*scale);
    switch (pfpChoosed)
    {
    case 1:
        al_draw_rectangle(compX1, compY1, compX2, compY2, al_map_rgb(255, 255, 255), (float)3*scale);
        break;
    case 2:
        al_draw_rectangle(compX3, compY1, compX4, compY2, al_map_rgb(255, 255, 255), 3*scale);
        break;
    case 3:
        al_draw_rectangle(compX1, compY3, compX2, compY4, al_map_rgb(255, 255, 255), 3*scale);
        break;
    case 4:
        al_draw_rectangle(compX3, compY3, compX4, compY4, al_map_rgb(255, 255, 255), 3*scale);
        break;
    }
    al_flip_display();
}