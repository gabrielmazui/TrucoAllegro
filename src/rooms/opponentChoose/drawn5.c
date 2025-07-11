#include <stdio.h>
#include <allegro5/allegro5.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include "..\..\..\config\config.h"

#define CARD_W (380 * scale)
#define CARD_H (150 * scale)
#define RADIUS (20 * scale)
#define GAP_Y (20 * scale)

void desenhar_card(ALLEGRO_FONT* font, ALLEGRO_FONT* font2, ALLEGRO_BITMAP* img, float x, float y, const char* nome, float agressividade, float mentira, float desconfianca) {
    float w = CARD_W;
    float h = CARD_H;
    float radius = RADIUS;
    al_draw_filled_rounded_rectangle(x, y, x + w, y + h, radius, radius, al_map_rgba(0, 0, 0, 150));
    float img_size = 100 * scale;
    float img_x = x + 20 * scale;
    float img_y = y + (h - img_size) / 2;
    if (img) {
        al_draw_scaled_bitmap(img, 0, 0, al_get_bitmap_width(img), al_get_bitmap_height(img), img_x, img_y, img_size, img_size, 0);
    }

    float content_x = img_x + img_size + 25 * scale;
    float content_y = y + 25 * scale;  

    
    al_draw_text(font, al_map_rgb(255, 255, 255), content_x, content_y - (10*scale), 0, nome);

    content_y += 28 * scale;

    float bar_w = x + w - 20 * scale - content_x;
    float bar_h = 3 * scale;

    al_draw_text(font2, al_map_rgb(255, 0, 0), content_x, content_y, 0, "Agressividade");
    content_y += 20 * scale;  
    al_draw_filled_rectangle(content_x, content_y, content_x + bar_w * agressividade, content_y + bar_h, al_map_rgb(255, 0, 0));
    content_y += bar_h + 10 * scale;  

    // Mentira
    al_draw_text(font2, al_map_rgb(0, 255, 0), content_x, content_y, 0, "Mentira");
    content_y += 20 * scale;
    al_draw_filled_rectangle(content_x, content_y, content_x + bar_w * mentira, content_y + bar_h, al_map_rgb(0, 255, 0));
    content_y += bar_h + 10 * scale;

    // Desconfiança
    al_draw_text(font2, al_map_rgb(0, 0, 255), content_x, content_y, 0, "Desconfiança");
    content_y += 20 * scale;
    al_draw_filled_rectangle(content_x, content_y, content_x + bar_w * desconfianca, content_y + bar_h, al_map_rgb(0, 0, 255));

}



void drawn5(ALLEGRO_FONT* font, ALLEGRO_FONT* font2, character vetorPers[]){
    al_draw_tinted_scaled_bitmap(background, al_map_rgb(255, 255, 255), 0, 0, larguraB, alturaB, 0, 0, larguraEscolhida, alturaEscolhida, 0);

    float margin_x = 50 * scale;
    float spacing_y = CARD_H + GAP_Y;

    for (int i = 0; i < 4; i++) {
        float x = margin_x;
        float y = margin_x + i * spacing_y;
        desenhar_card(font, font2, vetorPers[i].pfp, x, y, vetorPers[i].name, vetorPers[i].agressividade, vetorPers[i].mentira, vetorPers[i].desconfianca);
    }

    for (int i = 0; i < 4; i++) {
        float x = larguraEscolhida - CARD_W - margin_x;
        float y = margin_x + i * spacing_y;
        desenhar_card(font, font2, vetorPers[i+5].pfp, x, y, vetorPers[i+5].name, vetorPers[i+5].agressividade, vetorPers[i+5].mentira, vetorPers[i+5].desconfianca);
    }

    float x_central = (larguraEscolhida - CARD_W) / 2.0f;
    float y_central = alturaEscolhida - CARD_H - 20 * scale;
    desenhar_card(font, font2, vetorPers[10].pfp, x_central, y_central, vetorPers[10].name, vetorPers[10].agressividade, vetorPers[10].mentira, vetorPers[10].desconfianca);
    desenhar_card(font, font2, vetorPers[9].pfp, x_central, y_central - CARD_H - 20 * scale, vetorPers[9].name, vetorPers[9].agressividade, vetorPers[9].mentira, vetorPers[9].desconfianca);
    desenhar_card(font, font2, vetorPers[4].pfp, x_central, y_central - CARD_H - 20 * scale - CARD_H - 20 * scale, vetorPers[4].name, vetorPers[4].agressividade, vetorPers[4].mentira, vetorPers[4].desconfianca);

    al_flip_display();
}