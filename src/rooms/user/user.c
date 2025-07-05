#include <stdio.h>
#include <allegro5/allegro5.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <string.h>

#include "..\..\animations\transition.h"
#include "..\charChoose\charchoose.h"
#include "..\..\..\config\config.h"
#include "..\..\extras\userverify.h"
#include "..\..\animations\colorerror.h"
#include "..\..\animations\interrogacao.h"
#include "..\..\animations\errorposition.h"
#include "drawn3.h"
#include "..\..\paused\paused.h"
#include "..\menu1\menu1.h"
#include "..\..\extras\newres.h"

void UserLoop()
{
    ALLEGRO_SAMPLE *error = al_load_sample("sounds/error.wav");
    double lastTimeError = 0.0;
    int PlayedError = 0;

    ALLEGRO_FONT *font1 = al_load_ttf_font("fonts/cartoon.ttf",70*scale,0), *font2 = al_load_ttf_font("fonts/retro.ttf",45*scale,0);

    int txtTypeOp = 100;
    int txtX1 = larguraEscolhida/2 - (250*scale);
    int txtX2 = larguraEscolhida/2 + (250*scale);
    int txtY1 = alturaEscolhida/2 - (30*scale);
    int txtY2 = alturaEscolhida/2 + (30*scale);

    float centroY = (txtY1 + txtY2) / 2;
    float centroX = (txtX1 + txtX2) / 2;
    float altura_texto = al_get_font_line_height(font2);
    float y_ajustado = centroY - (altura_texto / 2);

    int alturaPergunta = alturaEscolhida/2 - (200*scale);
    int interrogacao = alturaEscolhida/2 - (200*scale);

    int whiteToRed = 255;
    int blackToRed = 0;

    int animationP1 = 0;
    int animationPaused = 0;
    double timePaused;
    int auxEnd = 0;
    int auxEnd2= 0;
    int grupoAy1[total_rects];
    int grupoAy2[total_rects];
    int firstExec = 1;
    int animReady = 0;

    // tirar print
    ALLEGRO_BITMAP* menu_snapshot = NULL;

    menu_snapshot = al_create_bitmap(larguraEscolhida, alturaEscolhida); // tirar print da tela (para a transicao)
    al_set_target_bitmap(menu_snapshot);
    drawn3(255, txtTypeOp, txtX1, txtX2, txtY1, txtY2, centroY, centroX, y_ajustado, alturaPergunta, interrogacao, whiteToRed, blackToRed, font1, font2);
    al_set_target_backbuffer(display);

    // variaveis para realizar animacao
    int up = 1;
    int timesDone = 0;
    double lastTimeDone;
    int animPiscaStart = 0;

    double cooldownAux;
    int cooldownAuxInitiated = 0;
    int direitaErr = 1;
    int quantErr = 0;
    int errorAnimationHappening = 0;

    int upRed = 1;
    int ColorAnimInitiated = 0;
    int colorAnimHappening = 0;

    int lenUser = 0;
    int verDone = 1;
    double lastEsc = 0.0;
    int newRes = 0;
    while(1)
    {
        if(al_event_queue_is_empty(event_queue)){
            if(animReady){
                if(toMenu1 || exitGame || newRes) break;
                drawn3(255, txtTypeOp, txtX1, txtX2, txtY1, txtY2, centroY, centroX, y_ajustado, alturaPergunta, interrogacao, whiteToRed, blackToRed, font1, font2);
            }
        }
        al_wait_for_event(event_queue, &event);
        if(event.type == ALLEGRO_EVENT_TIMER){
            if(errorAnimationHappening && animReady){
                errorAnimation(&cooldownAux, &cooldownAuxInitiated, &direitaErr, &quantErr, &errorAnimationHappening, &txtX1, &txtX2, &centroX);
            }
            if(colorAnimHappening && animReady){
                colorErrAnimation(&upRed, &ColorAnimInitiated, &colorAnimHappening, &whiteToRed, &blackToRed);
            }
            if(!animReady){
                animationTransition(&animReady, menu_snapshot, &firstExec, &animationP1, &animationPaused, &timePaused, &auxEnd, &auxEnd2, grupoAy1, grupoAy2);
                if(firstExec){
                    firstExec = 0;
                }
            }else{
                interrogacaoAnim(&up, &timesDone, &lastTimeDone, &animPiscaStart, &interrogacao);
            }
        }
        else if(event.type == ALLEGRO_EVENT_DISPLAY_CLOSE){
            al_destroy_display(display);
            al_destroy_timer(timer);
            al_destroy_audio_stream(menuTheme);
            return;

        }else if(event.type == ALLEGRO_EVENT_KEY_CHAR && animReady){
            int unichar = event.keyboard.unichar; // tabela ascii

            if(event.keyboard.keycode == ALLEGRO_KEY_BACKSPACE) {
                if (lenUser > 0) {
                    lenUser--;
                    user.name[lenUser] = '\0';
                }
            }else if(event.keyboard.keycode == ALLEGRO_KEY_ENTER) {
                if(animReady && verDone){
                    if(userVerify(&lenUser, &verDone)){
                        break;
                    }else{
                        if(!PlayedError){
                            al_play_sample(error, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
                            errorAnimationHappening = 1;
                            colorAnimHappening = 1;
                            lastTimeError = al_get_time();
                            PlayedError = 1;
                            continue;
                        }else if(al_get_time() - lastTimeError >= 0.15){
                            al_play_sample(error, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
                            errorAnimationHappening = 1;
                            colorAnimHappening = 1;
                            lastTimeError = al_get_time();
                        }
                        continue;
                    }
                }
            }else if(lenUser < USER_MAX && ((unichar >= 65 && unichar <= 90) ||(unichar >= 97 && unichar <= 122) || unichar == 32)){
                if(unichar == 32 && lenUser == 0){
                        continue;
                     }else{
                        user.name[lenUser] = (char)unichar;
                        lenUser++;
                        user.name[lenUser] = '\0';
                    }
            }else if(event.keyboard.keycode == ALLEGRO_KEY_ESCAPE &&((al_get_time() - lastEsc) >= 0.3)){
                lastEsc = al_get_time();
                menu_snapshot = al_create_bitmap(larguraEscolhida, alturaEscolhida); // tirar print da tela (para a transicao)
                al_set_target_bitmap(menu_snapshot);
                drawn3(255, txtTypeOp, txtX1, txtX2, txtY1, txtY2, centroY, centroX, y_ajustado, alturaPergunta, interrogacao, whiteToRed, blackToRed, font1, font2);
                al_set_target_backbuffer(display);
                paused(menu_snapshot, 0, &lastEsc, &newRes);
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
    }
    else{
        charChooseLoop();
    } 
}
