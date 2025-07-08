#include <stdio.h>
#include <allegro5/allegro5.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <string.h>

#include "..\opponentChoose\opponentchoose.h"
#include "..\..\..\config\config.h"
#include "..\..\animations\transition.h"
#include "drawn4.h"
#include "..\..\paused\paused.h"
#include "..\menu1\menu1.h"
#include "..\..\extras\newres.h"

void charChooseLoop(){
    int pfpChoosed = 0;
    ALLEGRO_BITMAP* img1 = al_load_bitmap("images/chars/1.jpeg");
    ALLEGRO_BITMAP* img2 = al_load_bitmap("images/chars/2.jpeg");
    ALLEGRO_BITMAP* img3 = al_load_bitmap("images/chars/3.jpeg");
    ALLEGRO_BITMAP* img4 = al_load_bitmap("images/chars/4.jpeg");
    ALLEGRO_FONT *font = al_load_ttf_font("fonts/cartoon.ttf",70*scale,0);

    ALLEGRO_BITMAP* menu_snapshot = NULL;
    menu_snapshot = al_create_bitmap(larguraEscolhida, alturaEscolhida); // tirar print da tela (para a transicao)
    al_set_target_bitmap(menu_snapshot);
    drawn4(255, font, img1, img2, img3, img4, pfpChoosed);
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

    int compX1 = larguraEscolhida/2 - (100*scale) - (200*scale);
    int compX2 = compX1 + 200*scale;
    int compX3 = larguraEscolhida/2 + (100*scale);
    int compX4 = compX3 + 200*scale;

    int compY1 = alturaEscolhida/2 +(50*scale) - (200*scale);
    int compY2 = compY1 + (200*scale);
    int compY3 = alturaEscolhida/2 + (100*scale);
    int compY4 = compY3 + (200*scale);

    double lastEsc = 0.0;
    int newRes = 0;

    while(1)
    {
        if(al_event_queue_is_empty(event_queue)){
            if(toMenu1 || exitGame || newRes) break;
            if(animReady){
                drawn4(255, font, img1, img2, img3, img4, pfpChoosed);
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
            if(event.keyboard.keycode == ALLEGRO_KEY_ENTER && pfpChoosed){
                switch(pfpChoosed){
                    case 1:
                        user.pfp = img1;
                        break;
                    case 2:
                        user.pfp = img2;
                        break;
                    case 3:
                        user.pfp = img3;
                        break;
                    case 4:
                        user.pfp = img4;
                        break;
                }
                break;
            }else if(event.keyboard.keycode == ALLEGRO_KEY_ESCAPE &&((al_get_time() - lastEsc) >= 0.3)){
                lastEsc = al_get_time();
                menu_snapshot = al_create_bitmap(larguraEscolhida, alturaEscolhida); // tirar print da tela (para a transicao)
                al_set_target_bitmap(menu_snapshot);
                drawn4(255, font, img1, img2, img3, img4, pfpChoosed);
                al_set_target_backbuffer(display);
                paused(menu_snapshot, 0, &lastEsc, &newRes);
                al_flush_event_queue(event_queue);
                continue;
            }
        }else if(event.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN && animReady) {
            if (event.mouse.button == 1){
                int mouse_x = event.mouse.x;
                int mouse_y = event.mouse.y;
                if(mouse_x >= compX1 && mouse_x <= compX2 && mouse_y >= compY1 && mouse_y <= compY2){
                    pfpChoosed = 1;
                }else if(mouse_x >= compX3 && mouse_x <= compX4 && mouse_y >= compY1 && mouse_y <= compY2){
                    pfpChoosed = 2;
                }else if(mouse_x >= compX1 && mouse_x <= compX2 && mouse_y >= compY3 && mouse_y <= compY4){
                    pfpChoosed = 3;
                }else if(mouse_x >= compX3 && mouse_x <= compX4 && mouse_y >= compY3 && mouse_y <= compY4){
                    pfpChoosed = 4;
                }
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
