#include <stdio.h>
#include <allegro5/allegro5.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>
#include <string.h>

#include "drawnres.h"
#include "..\config\config.h"

int resolution(void){

    al_init_primitives_addon();
    al_init_font_addon();
    al_init_ttf_addon();
    al_install_keyboard();
    al_install_mouse();

    ALLEGRO_DISPLAY *displayRes;
    ALLEGRO_EVENT_QUEUE *event_queueRes;
    ALLEGRO_TIMER *timerRes;
    ALLEGRO_FONT *font1 = al_load_ttf_font("fonts/retro.ttf",55,0);

    timerRes = al_create_timer(1.0 / 90);
    event_queueRes= al_create_event_queue();

    al_set_new_display_flags(ALLEGRO_OPENGL | ALLEGRO_WINDOWED);
    displayRes = al_create_display(1280, 720);
    al_set_window_position(displayRes, 0, 0);
    al_set_window_title(displayRes, "Truco");
    ALLEGRO_EVENT eventRes;
    al_register_event_source(event_queueRes, al_get_keyboard_event_source());
	al_register_event_source(event_queueRes, al_get_display_event_source(displayRes));
	al_register_event_source(event_queueRes, al_get_mouse_event_source());
	al_register_event_source(event_queueRes, al_get_timer_event_source(timerRes));

    ALLEGRO_MONITOR_INFO info;
    al_get_monitor_info(0, &info);
    int largura_monitor = info.x2 - info.x1;
    int altura_monitor = info.y2 - info.y1;

    int q = 1;
    int larguras[10] = {
        1280, 1280, 1360, 1366, 1440,
        1536, 1600, 1680, 1600, 1920
    };

    int alturas[10] = {
        720, 800, 768, 768, 900,
        864, 900, 1050, 1024, 1080
    };
    while(q<10){
        if(larguras[q] <= largura_monitor && alturas[q] <= altura_monitor){
            q++;
            continue;
        }
        break;
    }

    char resolutions[q+1][20];

    for(int i = 0; i<q ;i++){
        char str1[20];
        sprintf(str1, "%d", alturas[i]);
        char* str2 = " X ";
        sprintf(resolutions[i], "%d", larguras[i]);
        strcat(resolutions[i], str2);
        strcat(resolutions[i], str1);
    }
    char str2[20];
    char strDisp[20];
    char strDisp1[20];
    sprintf(strDisp1, "%d", altura_monitor);

    char* strDisp2 = " X ";
    char strDisp3[20];
    sprintf(strDisp3, "%d", largura_monitor);
    strcpy(strDisp, strDisp3);
    strcat(strDisp, strDisp2);
    strcat(strDisp, strDisp1);

    int index = q;
    fullscreen = 1;
    char str1[3] = "ON";
    strcpy(str2, strDisp);
    al_start_timer(timerRes);

    int op = 100;
    while(1)
    {
        al_wait_for_event(event_queueRes, &eventRes);
        if(eventRes.type == ALLEGRO_EVENT_DISPLAY_CLOSE){
            al_destroy_event_queue(event_queueRes);
            al_destroy_display(displayRes);
            al_destroy_timer(timerRes);
            return 0;
        }else if(eventRes.type == ALLEGRO_EVENT_KEY_DOWN){
            if(eventRes.keyboard.keycode == ALLEGRO_KEY_ENTER){
               break;
            }
        }else if(eventRes.type == ALLEGRO_EVENT_TIMER){
            drawnRes(font1, str1, str2, op);
        }else if (eventRes.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {
            if (eventRes.mouse.button == 1) { // Botão esquerdo
                int mouse_x = eventRes.mouse.x;
                int mouse_y = eventRes.mouse.y;
                int donex1 = 1280/2 - al_get_text_width(font1, "Done")/2;
                int donex2 = donex1 + al_get_text_width(font1, "Done");
                int doney1 = 600;
                int doney2 = doney1 + al_get_font_line_height(font1);

                if(mouse_x >= donex1 && mouse_x <= donex2 && mouse_y >= doney1 && mouse_y <= doney2){
                    break;
                }

                int seta1X1 = ((1280)/2 - 400) + al_get_text_width(font1, "FullScreen:") + 30;
                int seta1X2 = seta1X1 + al_get_text_width(font1, "<");
                int seta1Y1 = (720/2) - 100;
                int seta1Y2 = seta1Y1 +  al_get_font_line_height(font1);

                int seta2X1 = ((1280)/2 - 400) + al_get_text_width(font1, "FullScreen:") + 30 + al_get_text_width(font1, "<") + (al_get_text_width(font1, "OFF")) + 20;
                int seta2X2 = seta2X1 + al_get_text_width(font1, ">");

                int seta3X1 = ((1280)/2 - 400) + al_get_text_width(font1, "Resolution:") + 30;
                int seta3X2 = seta3X1 + al_get_text_width(font1, "<");
                int seta3Y1 = (720/2);
                int seta3Y2 = seta3Y1 +  al_get_font_line_height(font1);

                int seta4X1 = ((1280)/2 - 400) + al_get_text_width(font1, "Resolution:") + 30 + al_get_text_width(font1, "<") + (al_get_text_width(font1, "1920 X 1080")) + 20;
                int seta4X2 = seta4X1 + al_get_text_width(font1, "<");

                if(mouse_y >= seta1Y1 && mouse_y <= seta1Y2){
                    if((mouse_x >= seta1X1 && mouse_x <= seta1X2) || (mouse_x >= seta2X1 && mouse_x <= seta2X2)){
                        if(!fullscreen){
                            op = 100;
                            char* aux = "ON";
                            strcpy(str1, aux);
                            strcpy(str2, strDisp);
                            index = q;
                            fullscreen = 1;
                            continue;
                            // mudar a cor para cinza
                        }else{
                            op = 255;
                            char* aux = "OFF";
                            strcpy(str1, aux);
                            index = q-1;
                            strcpy(str2, resolutions[index]);
                            fullscreen = 0;
                            continue;
                        }
                    }
                }else if(mouse_y >= seta3Y1 && mouse_y <= seta3Y2 && !fullscreen){
                    if(mouse_x >= seta3X1 && mouse_x <= seta3X2){
                        if(index > 0){
                            index--;
                            strcpy(str2, resolutions[index]);
                            continue;
                        }else{
                            index = q-1;
                            strcpy(str2, resolutions[index]);
                            continue;
                        }

                    }else if(mouse_x >= seta4X1 && mouse_x <= seta4X2){
                        if(index < q-1){
                            index++;
                            strcpy(str2, resolutions[index]);
                            continue;
                        }else{
                            index = 0;
                            strcpy(str2, resolutions[index]);
                            continue;
                        }
                    }
                }
            }
        }
    }
    if(fullscreen){
        larguraEscolhida = largura_monitor;
        alturaEscolhida = altura_monitor;
    }else{
        larguraEscolhida = larguras[index];
        alturaEscolhida = alturas[index];
    }
    al_destroy_event_queue(event_queueRes);
    al_destroy_display(displayRes);
    al_destroy_timer(timerRes);
    return 1;
}
