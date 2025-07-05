#include <stdio.h>
#include <allegro5/allegro5.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <string.h>

#include "..\..\..\config\config.h"
#include "..\..\..\config\config.h"
#include "..\..\animations\transition.h"
#include "drawn6.h"
#include "..\opponentChoose\opponentchoose.h"
#include "..\..\paused\paused.h"
#include "..\menu1\menu1.h"
#include "..\..\extras\newres.h"

void mainGameLoop(){
    ALLEGRO_FONT *font = al_load_ttf_font("fonts/retro.ttf",30*scale,0);
    ALLEGRO_BITMAP* card1 = NULL;
    ALLEGRO_BITMAP* card2 = NULL;
    ALLEGRO_BITMAP* card3 = NULL;
    ALLEGRO_BITMAP* OPcard1 = NULL;
    ALLEGRO_BITMAP* OPcard2 = NULL;
    ALLEGRO_BITMAP* OPcard3 = NULL;
    ALLEGRO_BITMAP* reverso = al_load_bitmap("images/cards/reverso.png");
    ALLEGRO_BITMAP* mesa = al_load_bitmap("images/mesa.jpg");

    void chooseCards(void){
        card1 = al_load_bitmap("images/cards/1Espadas.jpg");
        card2 = al_load_bitmap("images/cards/1Bastos.jpg");
        card3 = al_load_bitmap("images/cards/7Ouro.jpg");

        OPcard1 = al_load_bitmap("images/cards/7Espadas.jpg");
        OPcard2 = al_load_bitmap("images/cards/3Copas.jpg");
        OPcard3 = al_load_bitmap("images/cards/4Ouro.jpg");
    }
    
    chooseCards();
    
    ALLEGRO_BITMAP* menu_snapshot = NULL;

    menu_snapshot = al_create_bitmap(larguraEscolhida, alturaEscolhida); // tirar print da tela (para a transicao)
    al_set_target_bitmap(menu_snapshot);
    drawn6(card1, card2, card3, OPcard1, OPcard2, OPcard3, reverso, font, mesa);
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
                drawn6(card1, card2, card3, OPcard1, OPcard2, OPcard3, reverso, font, mesa);
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
                drawn6(card1, card2, card3, OPcard1, OPcard2, OPcard3, reverso, font, mesa);
                al_set_target_backbuffer(display);
                paused(menu_snapshot, 1, &lastEsc, &newRes);
                al_flush_event_queue(event_queue);
                continue;
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
        opponentChooseLoop();
    }
}
