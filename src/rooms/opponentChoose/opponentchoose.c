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
    int selecionado = -1;
    // tirar print
    ALLEGRO_BITMAP* menu_snapshot = NULL;

    ALLEGRO_FONT* font = al_load_ttf_font("fonts/cartoon.ttf", 28 * scale, 0);
    ALLEGRO_FONT* font2 = al_load_ttf_font("fonts/retro.ttf", 20 * scale, 0);

    Cantadas lucas = {
        al_load_sample("sounds/lucas/quero.ogg"),
        al_load_sample("sounds/lucas/naoQuero.ogg"),
        al_load_sample("sounds/lucas/envido.ogg"),
        al_load_sample("sounds/lucas/realEnvido.ogg"),
        al_load_sample("sounds/lucas/faltaEnvido.ogg"),
        al_load_sample("sounds/lucas/truco.ogg"),
        al_load_sample("sounds/lucas/retruco.ogg"),
        al_load_sample("sounds/lucas/valeQuatro.ogg"),
        al_load_sample("sounds/lucas/flor.ogg"),
        al_load_sample("sounds/lucas/contraFlor.ogg"),
        al_load_sample("sounds/lucas/contraFlorResto.ogg"),
        al_load_sample("sounds/lucas/pontosNaMesa.ogg"),
        al_load_sample("sounds/lucas/florNaMesa.ogg"),
        al_load_sample("sounds/lucas/mazo.ogg")
    };
    Cantadas zart = {
        al_load_sample("sounds/zart/quero.ogg"),
        al_load_sample("sounds/zart/naoQuero.ogg"),
        al_load_sample("sounds/zart/envido.ogg"),
        al_load_sample("sounds/zart/realEnvido.ogg"),
        al_load_sample("sounds/zart/faltaEnvido.ogg"),
        al_load_sample("sounds/zart/truco.ogg"),
        al_load_sample("sounds/zart/retruco.ogg"),
        al_load_sample("sounds/zart/valeQuatro.ogg"),
        al_load_sample("sounds/zart/flor.ogg"),
        al_load_sample("sounds/zart/contraFlor.ogg"),
        al_load_sample("sounds/zart/contraFlorResto.ogg"),
        al_load_sample("sounds/zart/pontosNaMesa.ogg"),
        al_load_sample("sounds/zart/florNaMesa.ogg"),
        al_load_sample("sounds/zart/mazo.ogg")
    };

    Cantadas segat = {
        al_load_sample("sounds/segat/quero.ogg"),
        al_load_sample("sounds/segat/naoQuero.ogg"),
        al_load_sample("sounds/segat/envido.ogg"),
        al_load_sample("sounds/segat/realEnvido.ogg"),
        al_load_sample("sounds/segat/faltaEnvido.ogg"),
        al_load_sample("sounds/segat/truco.ogg"),
        al_load_sample("sounds/segat/retruco.ogg"),
        al_load_sample("sounds/segat/valeQuatro.ogg"),
        al_load_sample("sounds/segat/flor.ogg"),
        al_load_sample("sounds/segat/contraFlor.ogg"),
        al_load_sample("sounds/segat/contraFlorResto.ogg"),
        al_load_sample("sounds/segat/pontosNaMesa.ogg"),
        al_load_sample("sounds/segat/florNaMesa.ogg"),
        al_load_sample("sounds/segat/mazo.ogg")
    };
    Cantadas iza = {
        al_load_sample("sounds/iza/quero.ogg"),
        al_load_sample("sounds/iza/naoQuero.ogg"),
        al_load_sample("sounds/iza/envido.ogg"),
        al_load_sample("sounds/iza/realEnvido.ogg"),
        al_load_sample("sounds/iza/faltaEnvido.ogg"),
        al_load_sample("sounds/iza/truco.ogg"),
        al_load_sample("sounds/iza/retruco.ogg"),
        al_load_sample("sounds/iza/valeQuatro.ogg"),
        al_load_sample("sounds/iza/flor.ogg"),
        al_load_sample("sounds/iza/contraFlor.ogg"),
        al_load_sample("sounds/iza/contraFlorResto.ogg"),
        al_load_sample("sounds/iza/pontosNaMesa.ogg"),
        al_load_sample("sounds/iza/florNaMesa.ogg"),
        al_load_sample("sounds/iza/mazo.ogg")
    };
    Cantadas matheus = {
        al_load_sample("sounds/matheus/quero.ogg"),
        al_load_sample("sounds/matheus/naoQuero.ogg"),
        al_load_sample("sounds/matheus/envido.ogg"),
        al_load_sample("sounds/matheus/realEnvido.ogg"),
        al_load_sample("sounds/matheus/faltaEnvido.ogg"),
        al_load_sample("sounds/matheus/truco.ogg"),
        al_load_sample("sounds/matheus/retruco.ogg"),
        al_load_sample("sounds/matheus/valeQuatro.ogg"),
        al_load_sample("sounds/matheus/flor.ogg"),
        al_load_sample("sounds/matheus/contraFlor.ogg"),
        al_load_sample("sounds/matheus/contraFlorResto.ogg"),
        al_load_sample("sounds/matheus/pontosNaMesa.ogg"),
        al_load_sample("sounds/matheus/florNaMesa.ogg"),
        al_load_sample("sounds/matheus/mazo.ogg")
    };
    Cantadas jacques = {
        al_load_sample("sounds/jacques/quero.ogg"),
        al_load_sample("sounds/jacques/naoQuero.ogg"),
        al_load_sample("sounds/jacques/envido.ogg"),
        al_load_sample("sounds/jacques/realEnvido.ogg"),
        al_load_sample("sounds/jacques/faltaEnvido.ogg"),
        al_load_sample("sounds/jacques/truco.ogg"),
        al_load_sample("sounds/jacques/retruco.ogg"),
        al_load_sample("sounds/jacques/valeQuatro.ogg"),
        al_load_sample("sounds/jacques/flor.ogg"),
        al_load_sample("sounds/jacques/contraFlor.ogg"),
        al_load_sample("sounds/jacques/contraFlorResto.ogg"),
        al_load_sample("sounds/jacques/pontosNaMesa.ogg"),
        al_load_sample("sounds/jacques/florNaMesa.ogg"),
        al_load_sample("sounds/jacques/mazo.ogg")
    };
    Cantadas pivetta = {
        al_load_sample("sounds/pivetta/quero.ogg"),
        al_load_sample("sounds/pivetta/naoQuero.ogg"),
        al_load_sample("sounds/pivetta/envido.ogg"),
        al_load_sample("sounds/pivetta/realEnvido.ogg"),
        al_load_sample("sounds/pivetta/faltaEnvido.ogg"),
        al_load_sample("sounds/pivetta/truco.ogg"),
        al_load_sample("sounds/pivetta/retruco.ogg"),
        al_load_sample("sounds/pivetta/valeQuatro.ogg"),
        al_load_sample("sounds/pivetta/flor.ogg"),
        al_load_sample("sounds/pivetta/contraFlor.ogg"),
        al_load_sample("sounds/pivetta/contraFlorResto.ogg"),
        al_load_sample("sounds/pivetta/pontosNaMesa.ogg"),
        al_load_sample("sounds/pivetta/florNaMesa.ogg"),
        al_load_sample("sounds/pivetta/mazo.ogg")
    };
    Cantadas mazui = {
        al_load_sample("sounds/mazui/quero.ogg"),
        al_load_sample("sounds/mazui/naoQuero.ogg"),
        al_load_sample("sounds/mazui/envido.ogg"),
        al_load_sample("sounds/mazui/realEnvido.ogg"),
        al_load_sample("sounds/mazui/faltaEnvido.ogg"),
        al_load_sample("sounds/mazui/truco.ogg"),
        al_load_sample("sounds/mazui/retruco.ogg"),
        al_load_sample("sounds/mazui/valeQuatro.ogg"),
        al_load_sample("sounds/mazui/flor.ogg"),
        al_load_sample("sounds/mazui/contraFlor.ogg"),
        al_load_sample("sounds/mazui/contraFlorResto.ogg"),
        al_load_sample("sounds/mazui/pontosNaMesa.ogg"),
        al_load_sample("sounds/mazui/florNaMesa.ogg"),
        al_load_sample("sounds/mazui/mazo.ogg")
    };
    Cantadas enzo = {
        al_load_sample("sounds/enzo/quero.ogg"),
        al_load_sample("sounds/enzo/naoQuero.ogg"),
        al_load_sample("sounds/enzo/envido.ogg"),
        al_load_sample("sounds/enzo/realEnvido.ogg"),
        al_load_sample("sounds/enzo/faltaEnvido.ogg"),
        al_load_sample("sounds/enzo/truco.ogg"),
        al_load_sample("sounds/enzo/retruco.ogg"),
        al_load_sample("sounds/enzo/valeQuatro.ogg"),
        al_load_sample("sounds/enzo/flor.ogg"),
        al_load_sample("sounds/enzo/contraFlor.ogg"),
        al_load_sample("sounds/enzo/contraFlorResto.ogg"),
        al_load_sample("sounds/enzo/pontosNaMesa.ogg"),
        al_load_sample("sounds/enzo/florNaMesa.ogg"),
        al_load_sample("sounds/enzo/mazo.ogg")
    };
    Cantadas potter = {
        al_load_sample("sounds/potter/quero.ogg"),
        al_load_sample("sounds/potter/naoQuero.ogg"),
        al_load_sample("sounds/potter/envido.ogg"),
        al_load_sample("sounds/potter/realEnvido.ogg"),
        al_load_sample("sounds/potter/faltaEnvido.ogg"),
        al_load_sample("sounds/potter/truco.ogg"),
        al_load_sample("sounds/potter/retruco.ogg"),
        al_load_sample("sounds/potter/valeQuatro.ogg"),
        al_load_sample("sounds/potter/flor.ogg"),
        al_load_sample("sounds/potter/contraFlor.ogg"),
        al_load_sample("sounds/potter/contraFlorResto.ogg"),
        al_load_sample("sounds/potter/pontosNaMesa.ogg"),
        al_load_sample("sounds/potter/florNaMesa.ogg"),
        al_load_sample("sounds/potter/mazo.ogg")
    };

    character vetorPers[11] = {
        {"Mazui", al_load_bitmap("images/chars/mazui.jpg"), 0.5, 0.5, 0.8, "Nem tenta na próxima", "A gente não pode ser bom em tudo mas pode ser ruim em tudo", mazui},
        {"Artur", al_load_bitmap("images/chars/segat.jpg"), 1.0, 0.3, 1.0, "Tu é muito ruim pia", "Nem tentei ganhar mesmo", segat},
        {"Zart", al_load_bitmap("images/chars/zart.jpg"), 1.0, 1.0, 0.5, "Bota ruim tu viu", "Cade meu cigarro", zart},
        {"Pivetta", al_load_bitmap("images/chars/pivetta.jpg"), 0.7, 0.3, 0.4, "Truco y ceva", "Quando eu crescer eu tento", pivetta},
        {"Lucas", al_load_bitmap("images/chars/maranhao.jpg"), 0.4, 0.8, 0.3, "Bixo véi ruim", "Oloco mano", lucas},
        {"Matheus", al_load_bitmap("images/chars/math.jpg"), 0.3, 0.8, 0.3, "Filosoficamente falando...", "Affs", matheus},
        {"Izabely", al_load_bitmap("images/chars/iza.jpg"), 0.4, 0.9, 1.0, "Toma esse rock yo body", "Com essa sorte toda até eu", iza},
        {"Jacques", al_load_bitmap("images/chars/jacques.jpg"), 0.3, 0.5, 0.6, "Nem Conor Mcgregor apanhou tanto", "Ta dopado mane", jacques},
        {"Potter", al_load_bitmap("images/chars/arthur.jpg"), 0.6, 0.5, 0.4, "Não deu nem para aquecer", "Se jogar na loteria fica milionário", potter},
        {"Enzo", al_load_bitmap("images/chars/enzo.jpg"), 0.5, 0.5, 0.5, "It's over pros betinhas", "It's over pros betinhas", enzo},
        {"Zanetti", al_load_bitmap("images/chars/zanetti.jpg"), 1.0, 1.0, 1.0, "Sem sua IA não consegue né...", "Tu usou CHATGPT", lucas}
    };
    //opponent = op1;
    menu_snapshot = al_create_bitmap(larguraEscolhida, alturaEscolhida); // tirar print da tela (para a transicao)
    al_set_target_bitmap(menu_snapshot);
    drawn5(font, font2 ,vetorPers, selecionado);
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
        if(transitionMusic == 1){
            continue;
        }
        if(al_event_queue_is_empty(event_queue)){
            if(toMenu1 || exitGame || newRes) break;
            if(animReady){
                drawn5(font, font2 ,vetorPers, selecionado);
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
                drawn5(font, font2 ,vetorPers, selecionado);
                al_set_target_backbuffer(display);
                paused(menu_snapshot, 0, &lastEsc, &newRes);
                al_flush_event_queue(event_queue);
                continue;
            }
        }else if (event.type == ALLEGRO_EVENT_KEY_DOWN && event.keyboard.keycode == ALLEGRO_KEY_ENTER && selecionado != -1) {
            break;
        }else if (event.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN && event.mouse.button == 1) {
            float margin_x = 50 * scale;
            float spacing_y = CARD_H + GAP_Y;

            // Personagem 0 (esquerda cima)
            float x0 = margin_x;
            float y0 = margin_x;
            if (event.mouse.x >= x0 && event.mouse.x <= x0 + CARD_W &&
                event.mouse.y >= y0 && event.mouse.y <= y0 + CARD_H) {
                opponent = vetorPers[0];
                selecionado = 0;
            }

            // Personagem 1 (esquerda)
            float x1 = margin_x;
            float y1 = margin_x + spacing_y;
            if (event.mouse.x >= x1 && event.mouse.x <= x1 + CARD_W &&
                event.mouse.y >= y1 && event.mouse.y <= y1 + CARD_H) {
                opponent = vetorPers[1];
                selecionado = 1;
            }

            // Personagem 2 (esquerda)
            float x2 = margin_x;
            float y2 = margin_x + spacing_y * 2;
            if (event.mouse.x >= x2 && event.mouse.x <= x2 + CARD_W &&
                event.mouse.y >= y2 && event.mouse.y <= y2 + CARD_H) {
                opponent = vetorPers[2];
                selecionado = 2;
            }

            // Personagem 3 (esquerda)
            float x3 = margin_x;
            float y3 = margin_x + spacing_y * 3;
            if (event.mouse.x >= x3 && event.mouse.x <= x3 + CARD_W &&
                event.mouse.y >= y3 && event.mouse.y <= y3 + CARD_H) {
                opponent = vetorPers[3];
                selecionado = 3;
            }

            // Personagem 5 (direita)
            float x5 = larguraEscolhida - CARD_W - margin_x;
            float y5 = margin_x;
            if (event.mouse.x >= x5 && event.mouse.x <= x5 + CARD_W &&
                event.mouse.y >= y5 && event.mouse.y <= y5 + CARD_H) {
                opponent = vetorPers[5];
                selecionado = 5;
            }

            // Personagem 6 (direita)
            float x6 = x5;
            float y6 = margin_x + spacing_y;
            if (event.mouse.x >= x6 && event.mouse.x <= x6 + CARD_W &&
                event.mouse.y >= y6 && event.mouse.y <= y6 + CARD_H) {
                opponent = vetorPers[6];
                selecionado = 6;
            }

            // Personagem 7 (direita)
            float x7 = x5;
            float y7 = margin_x + spacing_y * 2;
            if (event.mouse.x >= x7 && event.mouse.x <= x7 + CARD_W &&
                event.mouse.y >= y7 && event.mouse.y <= y7 + CARD_H) {
                opponent = vetorPers[7];
                selecionado = 7;
            }

            // Personagem 8 (direita)
            float x8 = x5;
            float y8 = margin_x + spacing_y * 3;
            if (event.mouse.x >= x8 && event.mouse.x <= x8 + CARD_W &&
                event.mouse.y >= y8 && event.mouse.y <= y8 + CARD_H) {
                opponent = vetorPers[8];
                selecionado = 8;
            }

            // Personagem 4 (centro topo)
            float x4 = (larguraEscolhida - CARD_W) / 2.0f;
            float y4 = alturaEscolhida - CARD_H - 20 * scale - CARD_H - 20 * scale - CARD_H - 20 * scale;
            if (event.mouse.x >= x4 && event.mouse.x <= x4 + CARD_W &&
                event.mouse.y >= y4 && event.mouse.y <= y4 + CARD_H) {
                opponent = vetorPers[4];
                selecionado = 4;
            }

            // Personagem 9 (centro meio)
            float y9 = alturaEscolhida - CARD_H - 20 * scale - CARD_H - 20 * scale;
            if (event.mouse.x >= x4 && event.mouse.x <= x4 + CARD_W &&
                event.mouse.y >= y9 && event.mouse.y <= y9 + CARD_H) {
                opponent = vetorPers[9];
                selecionado = 9;
            }

            // Personagem 10 (centro baixo)
            float y10 = alturaEscolhida - CARD_H - 20 * scale;
            if (event.mouse.x >= x4 && event.mouse.x <= x4 + CARD_W &&
                event.mouse.y >= y10 && event.mouse.y <= y10 + CARD_H) {
                opponent = vetorPers[10];
                selecionado = 10;
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
