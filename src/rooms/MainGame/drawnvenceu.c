#include <stdio.h>
#include <allegro5/allegro5.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <string.h>
#include <math.h>
#include "..\..\..\config\config.h"

void drawnVenceu(ALLEGRO_FONT *font1, ALLEGRO_FONT *font2, int user, double startTime){
    float imageW = 280 * scale;
    float imageH = 280 * scale;

    float centerX = larguraEscolhida / 2.0f;

    float texto1_y = 60 * scale;
    float imagem_y = texto1_y + (200 * scale);
    float texto2_y = imagem_y + imageH + 20 * scale;
    float textoBotao_y = alturaEscolhida - 80 * scale;


    double tempo = al_get_time() - startTime;

    float alpha1 = fmin(1.0, tempo / 1.0);
    float alpha2 = tempo >= 1.0 ? fmin(1.0, (tempo - 1.0) / 1.0) : 0;
    float alpha3 = tempo >= 2.0 ? fmin(1.0, (tempo - 2.0) / 1.0) : 0;
    float alpha4 = tempo >= 3.0 ? fmin(1.0, (tempo - 3.0) / 1.0) : 0;

    char texto1[80];
    if(user == 1){
        sprintf(texto1, "Voce venceu");
    }else{
        sprintf(texto1, "Voce perdeu");
    }

    al_clear_to_color(al_map_rgb(0, 0, 0));

    ALLEGRO_COLOR corTexto1 = al_map_rgba_f(1, 1, 1, alpha1);
    al_draw_text(font1, corTexto1, centerX, texto1_y, ALLEGRO_ALIGN_CENTER, texto1);

    // Imagem com opacidade
    if (opponent.pfp) {
        float imageX = centerX - imageW / 2.0f;
        ALLEGRO_COLOR tint = al_map_rgba_f(1, 1, 1, alpha2);
        al_draw_tinted_scaled_bitmap(opponent.pfp, tint,
                                     0, 0, al_get_bitmap_width(opponent.pfp), al_get_bitmap_height(opponent.pfp),
                                     imageX, imagem_y, imageW, imageH, 0);
    }
    char texto2[200];
    if(user == 2){
        sprintf(texto2, "%s", opponent.fraseVitoria);
    }else{
        sprintf(texto2, "%s", opponent.fraseVitoria);
    }

    ALLEGRO_COLOR corTexto2 = al_map_rgba(255, 255, 255, alpha3); 
    al_draw_text(font2, corTexto2, centerX, texto2_y, ALLEGRO_ALIGN_CENTER, texto2);

    al_draw_text(font2, al_map_rgba(255, 255, 255, alpha4), centerX, textoBotao_y, ALLEGRO_ALIGN_CENTER, "Voltar");

    al_flip_display();
}