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
#include "..\opponentChoose\opponentchoose.h"
void venceuMenu(int vencedor){
    al_install_audio();
    al_init_acodec_addon();
    al_reserve_samples(16);
    ALLEGRO_SAMPLE* somVitoria = al_load_sample("sounds/venceu.ogg");
    ALLEGRO_SAMPLE* somDerrota = al_load_sample("sounds/perdeu.ogg");
    ALLEGRO_FONT *font1 = al_load_ttf_font("fonts/cartoon.ttf",90*scale,0);
    ALLEGRO_FONT *font2 = al_load_ttf_font("fonts/retro.ttf",30*scale,0);
    
    if(vencedor == 1){
        al_play_sample(somVitoria, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
    }else{
        al_play_sample(somDerrota, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
    }

    double startTime = al_get_time();
    while(1){
        if(transitionMusic == 1){
            continue;
        }
        if(al_event_queue_is_empty(event_queue)){
            drawnVenceu(font1, font2, vencedor, startTime); 
        }
        al_wait_for_event(event_queue, &event);
        if(event.type == ALLEGRO_EVENT_DISPLAY_CLOSE){
            al_destroy_display(display);
            al_destroy_timer(timer);
            al_destroy_audio_stream(menuTheme);
            return;
        }else if(event.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN && al_get_time() - startTime >= 4.0) {
            if (event.mouse.button == 1){
                int mouse_x = event.mouse.x;
                int mouse_y = event.mouse.y;

                float centerX = larguraEscolhida / 2.0f;
                float textoBotao_y = alturaEscolhida - (80 * scale);
                float larguraTexto = al_get_text_width(font2, "Voltar");
                float alturaTexto = al_get_font_line_height(font2);

                float x1 = centerX - (larguraTexto/2);
                float y1 = textoBotao_y - (alturaTexto/2);
                float x2 = centerX + (larguraTexto/2);
                float y2 = textoBotao_y + (alturaTexto/2);
                if(mouse_x >= x1 && mouse_x <= x2 && mouse_y >= y1 && mouse_y <= y2){
                    break;
                }

            }
        }
    }
    float volumeInicial = menuSound/10.0; 
    float volumeFinal = menuSound/10.0;   
        
    double start = al_get_time();
    float volume = volumeInicial;
    transitionMusic = 1;
    while (volume > 0.0f) {
        double elapsed = al_get_time() - start;
        float t = (float)(elapsed / 1.5); 
        if (t > 1.0f) t = 1.0f;

        volume = volumeInicial * (1.0f - t); 
        al_set_audio_stream_gain(menuTheme, volume);
        al_rest(0.01);
    }

    al_set_audio_stream_gain(menuTheme, 0.0f);
    al_set_audio_stream_playing(menuTheme, false);
    al_destroy_audio_stream(menuTheme);
    menuTheme = NULL;
        

    menuTheme = al_load_audio_stream("sounds/menuTheme.ogg", 4, 2048);
    
    al_attach_audio_stream_to_mixer(menuTheme, al_get_default_mixer());
    al_set_audio_stream_playmode(menuTheme, ALLEGRO_PLAYMODE_LOOP);
    al_set_audio_stream_playing(menuTheme, true);
    
    double start2 = al_get_time();
    float volume2 = 0.0f;

        while (volume2 < volumeFinal) {
            double elapsed = al_get_time() - start2;
            float t = (float)(elapsed / 1.5); 
            if (t > 1.0f) t = 1.0f;

            volume2 = volumeFinal * t; 
            al_set_audio_stream_gain(menuTheme, volume2);
            al_rest(0.01);
        }
        transitionMusic = 0;

    al_set_audio_stream_gain(menuTheme, volumeFinal); 
    opponentChooseLoop();
}
