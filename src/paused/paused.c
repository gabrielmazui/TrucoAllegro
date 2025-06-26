#include <stdio.h>
#include <allegro5/allegro5.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_font.h>

#include "..\..\config\config.h"
#include "drawnpaused.h"

void paused(void){
    //al_set_audio_stream_playing(audio_stream, false);
    // pausar a musica
    while(1)
    {
        if(al_event_queue_is_empty(event_queue)){
            drawnpaused();
        }
        al_wait_for_event(event_queue, &event);
        if(event.type==ALLEGRO_EVENT_DISPLAY_CLOSE){
            al_destroy_display(display);
            al_destroy_timer(timer);
            al_destroy_sample(menuTheme);
            return;
        }else if(event.type == ALLEGRO_EVENT_KEY_DOWN){
            if(event.keyboard.keycode == ALLEGRO_KEY_ESCAPE)
            {
                break;
            }
        }
    }
    al_flush_event_queue(event_queue);
    return;
}