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
#include "..\menu2\menu2.h"
#include "menu1.h"
#include "drawn1.h"

void menuLoop1()
{
    ALLEGRO_FONT *font1 = al_load_ttf_font("fonts/cartoon.ttf",90*scale,0), *font2 = al_load_ttf_font("fonts/cartoon.ttf",70*scale,0);

    int op1 = 0; // 255
    int op2 = 0; // 255
    int t1 = 0;
    int t2 = 0;
    void upd1(){
        if(op1 == 255){
            t1 = 1;
        }else{
            op1++;
        }
        return;
    }

     void upd2(){
        if(op2 == 255){
            t2 = 1;
        }else{
            op2++;
        }
        return;
    }
    double lastTimePause;
    int paused = 0;
    al_start_timer(timer);
    while(1)
    {
       if(al_event_queue_is_empty(event_queue)){
            drawn1(font1, font2, op1, op2);
        }
        al_wait_for_event(event_queue, &event);
        if(event.type == ALLEGRO_EVENT_TIMER){
            if(!t1){
                upd1();
                continue;
            }else if(!t2){
                upd2();
            }
            if(t1 && t2){
                if(!paused){
                    lastTimePause = al_get_time();
                    paused = 1;
                }else if((al_get_time() - lastTimePause) >= 2.0 && paused){
                    break;
                }
            }

        }else if(event.type == ALLEGRO_EVENT_DISPLAY_CLOSE){
            al_destroy_font(font1);
            al_destroy_font(font2);
            al_destroy_display(display);
            al_destroy_timer(timer);
            return;
        }
        else if(event.type == ALLEGRO_EVENT_KEY_DOWN){
            if(event.keyboard.keycode == ALLEGRO_KEY_ESCAPE)
                {
                    break;
                }
        }
    }
    al_destroy_font(font1);
    al_destroy_font(font2);
    menuLoop2();
}
