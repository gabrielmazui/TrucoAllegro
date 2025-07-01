#include <stdio.h>
#include <allegro5/allegro5.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <string.h>
#include <math.h>

#include "src\rooms\menu1\menu1.h"
#include "config\config.h"
#include "resolution\resolution.h"

int main(int argc, char **argv)
{
    if(!al_init()){
        fprintf(stderr, "failed to initialize allegro!\n");
        return -1;
    }

    al_set_blender(ALLEGRO_ADD, ALLEGRO_ALPHA, ALLEGRO_INVERSE_ALPHA);

    if(!resolution()){
        return 0;
    }

    timer = al_create_timer(1.0 / FPS);

    if(!timer){
        fprintf(stderr, "failed to create timer!\n");
        return -1;
    }

    scale = fmin(((float)larguraEscolhida / LARGURA_TELA), ((float)alturaEscolhida /ALTURA_TELA));
    if(fullscreen){
        al_set_new_display_flags(ALLEGRO_OPENGL | ALLEGRO_FULLSCREEN_WINDOW);
    }else{
        al_set_new_display_flags(ALLEGRO_OPENGL | ALLEGRO_WINDOWED);
    }
    // ALLEGRO_WINDOWED   / ALLEGRO_FULLSCREEN_WINDOW

    display = al_create_display(larguraEscolhida, alturaEscolhida);
    al_set_window_position(display, 0, 0);
    al_set_window_title(display, "Truco");
    //al_set_display_flag(display, ALLEGRO_FULLSCREEN_WINDOW, fullScreen);

    if(!display){
        fprintf(stderr, "failed to create display!\n");
        al_destroy_timer(timer);
        return -1;
    }

    if(!al_init_image_addon()){
        fprintf(stderr, "failed to initialize the image addon!\n");
        return -1;
    }

    if(!al_install_audio()){
        fprintf(stderr, "failed to initialize the audio");
    }
    if(!al_init_acodec_addon()){
        fprintf(stderr, "failed to initialize the codec addon");
    }
    al_reserve_samples(15);

    event_queue = al_create_event_queue();
    if (event_queue==NULL) {
		fprintf(stderr, "failed to create event_queue!\n");
		al_destroy_display(display);
        al_destroy_timer(timer);
        return -1;
	}

	al_register_event_source(event_queue, al_get_keyboard_event_source());
	al_register_event_source(event_queue, al_get_display_event_source(display));
	al_register_event_source(event_queue, al_get_mouse_event_source());
	al_register_event_source(event_queue, al_get_timer_event_source(timer));
    menuSound = 5;
    menuLoop1();
	return 0;
}
