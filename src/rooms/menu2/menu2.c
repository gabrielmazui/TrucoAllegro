#include <stdio.h>
#include <allegro5/allegro5.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <string.h>

#include "..\user\user.h"
#include "..\..\..\config\config.h"
#include "..\charChoose\charchoose.h"
#include "drawn2.h"

void menuLoop2()
{
    
    background = al_load_bitmap("images/background.png");
    larguraB = al_get_bitmap_width(background);
    alturaB = al_get_bitmap_height(background);

    menuTheme = al_load_audio_stream("sounds/menuTheme.wav", 4, 2048);
    ALLEGRO_SAMPLE *click = al_load_sample("sounds/gameStart.wav");

    ALLEGRO_FONT *font1 = al_load_ttf_font("fonts/cartoon.ttf",150*scale,0),*font2 = al_load_ttf_font("fonts/retro.ttf",40*scale,0);

    int alturaBackground = -alturaEscolhida*2;
    int alturaTitulo = (alturaEscolhida/4) - alturaEscolhida*2;
    int alturaPress = (alturaEscolhida/2 + (100*scale)) - alturaEscolhida*2;
    int aux = 0;
    int BackReady = 0;
    int clicked = 0;

    int opPlay = 255;
    int up = 0;

    void piscaAnimation(){
        if(up){
            opPlay+=3;
            if(opPlay==255){
                up = 0;
            }
            return;
        }
        opPlay-=3;
        if(opPlay == 0){
            up = 1;
        }
        return;
    }

    int q = 1;
    void DownAnimation(){
        if (aux + q > alturaEscolhida*2){
            q = (alturaEscolhida*2) - aux;
        }
        alturaBackground += q;
        alturaTitulo += q;
        alturaPress += q;
        aux+= q;
        q+= 1;
        if(aux == alturaEscolhida*2){
            BackReady = 1;
        }
    }

    double paused_time;
    int paused = 0;
    al_attach_audio_stream_to_mixer(menuTheme, al_get_default_mixer());
    al_set_audio_stream_gain(menuTheme, menuSound/10.0);
    al_set_audio_stream_playing(menuTheme, true);
    while(1)
    {
        if(al_event_queue_is_empty(event_queue)){
            drawn2(alturaBackground, alturaTitulo, alturaPress, opPlay, font1, font2);
        }
        al_wait_for_event(event_queue, &event);

        if(event.type==ALLEGRO_EVENT_DISPLAY_CLOSE){
            al_destroy_font(font1);
            al_destroy_font(font2);
            al_destroy_display(display);
            al_destroy_timer(timer);
            al_destroy_audio_stream(menuTheme);
            return;
        }else if((event.type==ALLEGRO_EVENT_KEY_DOWN || event.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) && !paused && BackReady){
            al_play_sample(click, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
            clicked = 1;
            opPlay = 255;
            al_flip_display();
            paused = 1;
            paused_time = al_get_time();
        }else if(event.type == ALLEGRO_EVENT_TIMER){
            if(!BackReady){
                DownAnimation();
            }
            if(BackReady && !clicked){
                piscaAnimation();
            }
            if(paused){
                if((al_get_time() - paused_time) >= 1.5){
                    break;
                }
            }
        }
    }
    UserLoop();
    return;
}
