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
#include "drawnvenceu.h"

void venceuMenu(int vencedor){
    ALLEGRO_FONT *font1 = al_load_ttf_font("fonts/cartoon.ttf",90*scale,0);
    ALLEGRO_FONT *font2 = al_load_ttf_font("fonts/retro.ttf",30*scale,0);
    double startTime = al_get_time();
    while(1){
        if(al_event_queue_is_empty(event_queue)){
            drawnVenceu(font1, font2, vencedor, startTime); 
        }
        al_wait_for_event(event_queue, &event);
        if(event.type == ALLEGRO_EVENT_DISPLAY_CLOSE){
            al_destroy_display(display);
            al_destroy_timer(timer);
            al_destroy_audio_stream(menuTheme);
            return;
        }
    }
}
