#include <stdio.h>
#include <allegro5/allegro5.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <string.h>

#include "..\MainGame\maingame.h"
#include "..\..\..\config\config.h"
#include "..\..\animations\transition.h"
#include "drawn5.h"
#include "..\..\paused\paused.h"
#include "..\menu1\menu1.h"
#include "..\..\extras\newres.h"
#define CARD_W (380 * scale)
#define CARD_H (150 * scale)
#define GAP_Y (20 * scale)
void opponentChooseLoop()
{
    // tirar print
    ALLEGRO_BITMAP* menu_snapshot = NULL;

    ALLEGRO_FONT* font = al_load_ttf_font("fonts/cartoon.ttf", 28 * scale, 0);
    ALLEGRO_FONT* font2 = al_load_ttf_font("fonts/retro.ttf", 20 * scale, 0);

    character vetorPers[11] = {
        {"Mazui", al_load_bitmap("images/chars/mazui.jpg"), 0.5, 0.5, 0.8},
        {"Artur", al_load_bitmap("images/chars/segat.jpg"), 1.0, 0.3, 1.0},
        {"Zart", al_load_bitmap("images/chars/zart.jpg"), 1.0, 1.0, 0.5},
        {"Pivetta", al_load_bitmap("images/chars/pivetta.jpg"), 0.7, 0.3, 0.2},
        {"Lucas", al_load_bitmap("images/chars/maranhao.jpg"), 0.1, 0.8, 0.3},
        {"Matheus", al_load_bitmap("images/chars/math.jpg"), 0.3, 0.8, 0.2},
        {"Izabely", al_load_bitmap("images/chars/iza.jpg"), 0.4, 0.9, 1.0},
        {"Jacques", al_load_bitmap("images/chars/jacques.jpg"), 0.3, 0.5, 0.6},
        {"Potter", al_load_bitmap("images/chars/arthur.jpg"), 0.6, 0.5, 0.4},
        {"Enzo", al_load_bitmap("images/chars/enzo.jpg"), 0.5, 0.5, 0.5},
        {"Zanetti", al_load_bitmap("images/chars/zanetti.jpg"), 1.0, 1.0, 1.0}
    };
    //opponent = op1;
    menu_snapshot = al_create_bitmap(larguraEscolhida, alturaEscolhida); // tirar print da tela (para a transicao)
    al_set_target_bitmap(menu_snapshot);
    drawn5(font, font2 ,vetorPers);
    al_set_target_backbuffer(display);

    int animationP1 = 0;
    int animationPaused = 0;
    double timePaused;
    int auxEnd = 0;
    int auxEnd2= 0;
    int grupoAy1[total_rects];
    int grupoAy2[total_rects];
    int firstExec = 1;
    int animReady = 0;

    double lastEsc = 0.0;
    int newRes = 0;

    while(1)
    {
        if(al_event_queue_is_empty(event_queue)){
            if(toMenu1 || exitGame || newRes) break;
            if(animReady){
                drawn5(font, font2 ,vetorPers);
            }else{
                animationTransition(&animReady, menu_snapshot, &firstExec, &animationP1, &animationPaused, &timePaused, &auxEnd, &auxEnd2, grupoAy1, grupoAy2);
                if(firstExec){
                    firstExec = 0;
                }
            }
        }
        al_wait_for_event(event_queue, &event);
        if(event.type == ALLEGRO_EVENT_TIMER){
        }else if(event.type == ALLEGRO_EVENT_DISPLAY_CLOSE){
            al_destroy_display(display);
            al_destroy_timer(timer);
            al_destroy_audio_stream(menuTheme);
            return;
        }else if(event.type == ALLEGRO_EVENT_KEY_CHAR && animReady){
            if(event.keyboard.keycode == ALLEGRO_KEY_ESCAPE &&((al_get_time() - lastEsc) >= 0.3)){
                lastEsc = al_get_time();
                menu_snapshot = al_create_bitmap(larguraEscolhida, alturaEscolhida); // tirar print da tela (para a transicao)
                al_set_target_bitmap(menu_snapshot);
                drawn5(font, font2 ,vetorPers);
                al_set_target_backbuffer(display);
                paused(menu_snapshot, 0, &lastEsc, &newRes);
                al_flush_event_queue(event_queue);
                continue;
            }
        }else if (event.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN && event.mouse.button == 1) {
            float margin_x = 50 * scale;
            float spacing_y = CARD_H + GAP_Y;

            // Personagem 0 (esquerda cima)
            float x0 = margin_x;
            float y0 = margin_x;
            if (event.mouse.x >= x0 && event.mouse.x <= x0 + CARD_W &&
                event.mouse.y >= y0 && event.mouse.y <= y0 + CARD_H) {
                opponent = vetorPers[0];
                break;
            }

            // Personagem 1 (esquerda)
            float x1 = margin_x;
            float y1 = margin_x + spacing_y;
            if (event.mouse.x >= x1 && event.mouse.x <= x1 + CARD_W &&
                event.mouse.y >= y1 && event.mouse.y <= y1 + CARD_H) {
                opponent = vetorPers[1];
                break;
            }

            // Personagem 2 (esquerda)
            float x2 = margin_x;
            float y2 = margin_x + spacing_y * 2;
            if (event.mouse.x >= x2 && event.mouse.x <= x2 + CARD_W &&
                event.mouse.y >= y2 && event.mouse.y <= y2 + CARD_H) {
                opponent = vetorPers[2];
                break;
            }

            // Personagem 3 (esquerda)
            float x3 = margin_x;
            float y3 = margin_x + spacing_y * 3;
            if (event.mouse.x >= x3 && event.mouse.x <= x3 + CARD_W &&
                event.mouse.y >= y3 && event.mouse.y <= y3 + CARD_H) {
                opponent = vetorPers[3];
                break;
            }

            // Personagem 5 (direita)
            float x5 = larguraEscolhida - CARD_W - margin_x;
            float y5 = margin_x;
            if (event.mouse.x >= x5 && event.mouse.x <= x5 + CARD_W &&
                event.mouse.y >= y5 && event.mouse.y <= y5 + CARD_H) {
                opponent = vetorPers[5];
                break;
            }

            // Personagem 6 (direita)
            float x6 = x5;
            float y6 = margin_x + spacing_y;
            if (event.mouse.x >= x6 && event.mouse.x <= x6 + CARD_W &&
                event.mouse.y >= y6 && event.mouse.y <= y6 + CARD_H) {
                opponent = vetorPers[6];
                break;
            }

            // Personagem 7 (direita)
            float x7 = x5;
            float y7 = margin_x + spacing_y * 2;
            if (event.mouse.x >= x7 && event.mouse.x <= x7 + CARD_W &&
                event.mouse.y >= y7 && event.mouse.y <= y7 + CARD_H) {
                opponent = vetorPers[7];
                break;
            }

            // Personagem 8 (direita)
            float x8 = x5;
            float y8 = margin_x + spacing_y * 3;
            if (event.mouse.x >= x8 && event.mouse.x <= x8 + CARD_W &&
                event.mouse.y >= y8 && event.mouse.y <= y8 + CARD_H) {
                opponent = vetorPers[8];
                break;
            }

            // Personagem 4 (centro topo)
            float x4 = (larguraEscolhida - CARD_W) / 2.0f;
            float y4 = alturaEscolhida - CARD_H - 20 * scale - CARD_H - 20 * scale - CARD_H - 20 * scale;
            if (event.mouse.x >= x4 && event.mouse.x <= x4 + CARD_W &&
                event.mouse.y >= y4 && event.mouse.y <= y4 + CARD_H) {
                opponent = vetorPers[4];
                break;
            }

            // Personagem 9 (centro meio)
            float y9 = alturaEscolhida - CARD_H - 20 * scale - CARD_H - 20 * scale;
            if (event.mouse.x >= x4 && event.mouse.x <= x4 + CARD_W &&
                event.mouse.y >= y9 && event.mouse.y <= y9 + CARD_H) {
                opponent = vetorPers[9];
                break;
            }

            // Personagem 10 (centro baixo)
            float y10 = alturaEscolhida - CARD_H - 20 * scale;
            if (event.mouse.x >= x4 && event.mouse.x <= x4 + CARD_W &&
                event.mouse.y >= y10 && event.mouse.y <= y10 + CARD_H) {
                opponent = vetorPers[10];
                break;
            }

        }
    }
    if(toMenu1){
        al_destroy_audio_stream(menuTheme);
        toMenu1 = 0;
        al_flush_event_queue(event_queue);
        menuLoop1();
    }else if(exitGame){
        return;
    }else if(newRes){
        al_destroy_display(display);
        al_destroy_audio_stream(menuTheme);
        al_flush_event_queue(event_queue);
        newres();
    }else{
        mainGameLoop();
    }
}
