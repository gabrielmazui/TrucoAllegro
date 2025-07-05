#include <stdio.h>
#include <allegro5/allegro5.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include "..\..\..\config\config.h"

void drawn6(ALLEGRO_BITMAP* card1, ALLEGRO_BITMAP* card2, ALLEGRO_BITMAP* card3, ALLEGRO_BITMAP* OPcard1, ALLEGRO_BITMAP* OPcard2, ALLEGRO_BITMAP* OPcard3,ALLEGRO_BITMAP* reverso, ALLEGRO_FONT *font, ALLEGRO_BITMAP* mesa){
    al_draw_tinted_scaled_bitmap(background, al_map_rgb(255, 255, 255), 0, 0, larguraB, alturaB, 0, 0, larguraEscolhida, alturaEscolhida, 0);
    al_draw_scaled_bitmap(opponent.pfp, 0, 0, al_get_bitmap_width(opponent.pfp), al_get_bitmap_height(opponent.pfp), larguraEscolhida - (150*scale) - (100*scale), (50*scale), 150*scale, 150*scale, 0);
    al_draw_scaled_bitmap(user.pfp, 0, 0, al_get_bitmap_width(user.pfp), al_get_bitmap_height(user.pfp), larguraEscolhida - (150*scale) - (100*scale), alturaEscolhida - (150*scale) - (50*scale), 150*scale, 150*scale, 0);
    al_draw_scaled_bitmap(user.pfp, 0, 0, al_get_bitmap_width(user.pfp), al_get_bitmap_height(user.pfp), larguraEscolhida - (150*scale) - (100*scale), alturaEscolhida - (150*scale) - (50*scale), 150*scale, 150*scale, 0);
    al_draw_scaled_bitmap(mesa, 0, 0, al_get_bitmap_width(mesa), al_get_bitmap_height(mesa), larguraEscolhida/2 - (118*scale)*2 - (30*scale), alturaEscolhida/2 - (306*scale)/2, 470*scale, 285*scale, 0);
    al_draw_rectangle(larguraEscolhida/2 - (118*scale)*2 - (30*scale), alturaEscolhida/2 - (306*scale)/2, larguraEscolhida/2 - (118*scale)*2 - (30*scale) + (470*scale), alturaEscolhida/2 - (306*scale)/2 + (285*scale), al_map_rgb(0, 0, 0), (float)2*scale);

    int fontHeight = al_get_font_line_height(font);
    al_draw_text(font, al_map_rgb(255, 255, 255),larguraEscolhida - (150*scale) - (100*scale) + (150*scale)/2, alturaEscolhida - (150*scale) - (50*scale) - (10*scale) - fontHeight, ALLEGRO_ALIGN_CENTRE, user.name);
    al_draw_text(font, al_map_rgb(255, 255, 255),larguraEscolhida - (150*scale) - (100*scale)+ (150*scale)/2, (50*scale) + (150*scale) + (10*scale), ALLEGRO_ALIGN_CENTRE, opponent.name);

    al_draw_scaled_bitmap(card1, 0, 0, al_get_bitmap_width(card1), al_get_bitmap_height(card1), larguraEscolhida/2 + (50*scale), alturaEscolhida - (200*scale) - (20*scale), 118*scale, 180*scale, 0);
    al_draw_scaled_bitmap(card2, 0, 0, al_get_bitmap_width(card2), al_get_bitmap_height(card2), larguraEscolhida/2 + (25*scale) - (118*scale), alturaEscolhida - (200*scale) - (20*scale), 118*scale, 180*scale, 0);
    al_draw_scaled_bitmap(card3, 0, 0, al_get_bitmap_width(card3), al_get_bitmap_height(card3), larguraEscolhida/2 - (118*scale)*2, alturaEscolhida - (200*scale) - (20*scale), 118*scale, 180*scale, 0);

    al_draw_scaled_bitmap(reverso, 0, 0, al_get_bitmap_width(reverso), al_get_bitmap_height(reverso), larguraEscolhida/2 + (50*scale), (20*scale), 118*scale, 180*scale, 0);
    al_draw_scaled_bitmap(reverso, 0, 0, al_get_bitmap_width(reverso), al_get_bitmap_height(reverso), larguraEscolhida/2 + (25*scale) - (118*scale), (20*scale), 118*scale, 180*scale, 0);
    al_draw_scaled_bitmap(reverso, 0, 0, al_get_bitmap_width(reverso), al_get_bitmap_height(reverso), larguraEscolhida/2 - (118*scale)*2, (20*scale), 118*scale, 180*scale, 0);

    al_draw_scaled_bitmap(card1, 0, 0, al_get_bitmap_width(card1), al_get_bitmap_height(card1), larguraEscolhida/2 + (50*scale), (20*scale) + (180*scale) + (30*scale), 118*scale, 180*scale, 0);
    al_draw_scaled_bitmap(OPcard1, 0, 0, al_get_bitmap_width(card1), al_get_bitmap_height(card1), larguraEscolhida/2 + (50*scale), alturaEscolhida - (200*scale) - (20*scale) - (180*scale) - (30*scale), 118*scale, 180*scale, 0);

    al_flip_display();
}