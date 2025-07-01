#include <stdio.h>
#include <allegro5/allegro5.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>

#include "..\..\config\config.h"

void update_display(int largura, int altura, int full) {
    al_destroy_display(display);
    larguraEscolhida = largura;
    alturaEscolhida = alturaEscolhida;
    scale = alturaEscolhida/ALTURA_TELA;
    fullscreen = full;
    if (fullscreen)
        al_set_new_display_flags(ALLEGRO_FULLSCREEN_WINDOW);
    else
        al_set_new_display_flags(ALLEGRO_WINDOWED);

    display = al_create_display(larguraEscolhida, alturaEscolhida);

    al_set_target_bitmap(al_get_backbuffer(display));
    al_register_event_source(event_queue, al_get_display_event_source(display));
}


void drawnOptions(ALLEGRO_BITMAP* menu_snapshot, ALLEGRO_FONT *font, ALLEGRO_FONT *font1, ALLEGRO_FONT *font2, ALLEGRO_FONT *font3, ALLEGRO_FONT *font4, ALLEGRO_FONT *font5, ALLEGRO_FONT *font6, ALLEGRO_FONT *font7, ALLEGRO_FONT *font8, ALLEGRO_FONT *font9, ALLEGRO_FONT *font10, ALLEGRO_FONT *font11, ALLEGRO_FONT *fontA, ALLEGRO_FONT *fontB, ALLEGRO_FONT *fontC, int txtHeight, char* strVal1, char* strVal2, char* strVal3, int op, int op2)
{
    int distance = scale*10;
    al_draw_bitmap(menu_snapshot, 0, 0, 0);

    int p1 = al_get_text_width(font, "FullScreen:") + 30;
    
    int seta = al_get_text_width(font, "<") + (al_get_text_width(font, "OFF") / 2) + 10;
    int seta2 = (al_get_text_width(font, "OFF") / 2) + 10;

    al_draw_filled_rectangle(0, 0, larguraEscolhida, alturaEscolhida, al_map_rgba(0, 0, 0, 180));
    al_draw_text(font9, al_map_rgba(255, 255, 255, 255), larguraEscolhida/2 - (400*scale), alturaEscolhida/2 - ((float)(2.0)*txtHeight) - distance*2, 0,"FullScreen:");
    al_draw_text(font1, al_map_rgba(255, 255, 255, 255), larguraEscolhida/2 - (400*scale) + p1, alturaEscolhida/2 - ((float)(2.0)*txtHeight) - distance*2, 0,"<");
    al_draw_text(fontA, al_map_rgba(255, 255, 255, 255), larguraEscolhida/2 - (400*scale) + p1 + seta, alturaEscolhida/2 - ((float)(2.0)*txtHeight) - distance*2,ALLEGRO_ALIGN_CENTRE, strVal1);
    al_draw_text(font2, al_map_rgba(255, 255, 255, 255), larguraEscolhida/2 - (400*scale) + p1 + seta + seta2, alturaEscolhida/2 - ((float)(2.0)*txtHeight) - distance*2, 0,">");

    int p2 = al_get_text_width(font, "Resolution:") + 30;
    int seta3 = al_get_text_width(font, "<") + (al_get_text_width(font, "1920 X 1080") / 2) + 10;
    int seta4 = (al_get_text_width(font, "1920 X 1080") / 2) + 10;
    al_draw_text(font10, al_map_rgba(op, op, op, 255), larguraEscolhida/2 - (400*scale), alturaEscolhida/2 - ((float)(1.0)*txtHeight) - distance/2, 0,"Resolution:");
    al_draw_text(font3, al_map_rgba(op, op, op, 255), larguraEscolhida/2 - (400*scale) + p2, alturaEscolhida/2 - ((float)(1.0)*txtHeight) - distance/2, 0,"<");
    al_draw_text(fontB, al_map_rgba(op, op, op, 255), larguraEscolhida/2 - (400*scale) + p2 + seta3, alturaEscolhida/2 - ((float)(1.0)*txtHeight) - distance/2,ALLEGRO_ALIGN_CENTRE, strVal2);
    al_draw_text(font4, al_map_rgba(op, op, op, 255), larguraEscolhida/2 - (400*scale) + p2 + seta3 + seta4, alturaEscolhida/2 - ((float)(1.0)*txtHeight) - distance/2, 0,">");

    int p3 = al_get_text_width(font, "Volume:") + 30;
    int seta5 = al_get_text_width(font, "<") + (al_get_text_width(font, "1.0") / 2) + 10;
    int seta6 = (al_get_text_width(font, "1.0") / 2) + 10;

    al_draw_text(font11, al_map_rgba(255, 255, 255, 255), larguraEscolhida/2 - (400*scale), alturaEscolhida/2 + distance/2, 0,"Volume:");
    al_draw_text(font5, al_map_rgba(255, 255, 255, 255), larguraEscolhida/2 - (400*scale) + p3, alturaEscolhida/2 + distance/2, 0,"<");
    al_draw_text(fontC, al_map_rgba(255, 255, 255, 255), larguraEscolhida/2 - (400*scale) + p3 + seta5, alturaEscolhida/2 + distance/2,ALLEGRO_ALIGN_CENTRE, strVal3);
    al_draw_text(font6, al_map_rgba(255, 255, 255, 255), larguraEscolhida/2 - (400*scale) + p3 + seta5 + seta6, alturaEscolhida/2 + distance/2, 0,">");

    al_draw_text(font7, al_map_rgba(255, 255, 255, 255), larguraEscolhida/2 - (400*scale), alturaEscolhida/2 + ((float)(1.0)*txtHeight) + distance * 2, 0,"Return");
     
    al_draw_text(font8, al_map_rgba(op2, op2, op2, 255), larguraEscolhida/2 , alturaEscolhida/2 + (200*scale), ALLEGRO_ALIGN_CENTRE,"Apply Resolution");
    al_flip_display();  
}

void options(ALLEGRO_BITMAP* menu_snapshot, int* clicked, int* optionsMenu, int* newRes, int* closeEsc, double* lastEsc)
{
    int auxFullScreen = fullscreen;
    int auxInd = resInd;
    int op2 = 100;

    int distance = scale*10;
    int aux1 = 50*scale;
    int quant = 10*scale;
    ALLEGRO_FONT *fonts[quant];
    for (int i = 0; i < quant; i++) {
        int size = aux1 + i;
        fonts[i] = al_load_font("fonts/retro.ttf", size, 0);
    }
    int f = 0;
    int f2 = 0;
    int fb1 = 0;
    int fb2 = 0;
    int fb3 = 0;
    int fb4 = 0;
    int fb5 = 0;
    int fb6 = 0;
    int f9 = 0;
    int f10 = 0;
    int f11 = 0;

    int fA = 0;
    int fB = 0;
    int fC = 0;

    ALLEGRO_FONT *font = al_load_ttf_font("fonts/retro.ttf", aux1,0);
    ALLEGRO_FONT *font1 = al_load_ttf_font("fonts/retro.ttf", aux1,0);
    ALLEGRO_FONT *font2 = al_load_ttf_font("fonts/retro.ttf", aux1,0);
    ALLEGRO_FONT *font3 = al_load_ttf_font("fonts/retro.ttf", aux1,0);
    ALLEGRO_FONT *font4 = al_load_ttf_font("fonts/retro.ttf", aux1,0);
    ALLEGRO_FONT *font5 = al_load_ttf_font("fonts/retro.ttf", aux1,0);
    ALLEGRO_FONT *font6 = al_load_ttf_font("fonts/retro.ttf", aux1,0);
    ALLEGRO_FONT *font7 = al_load_ttf_font("fonts/retro.ttf", aux1,0);
    ALLEGRO_FONT *font8 = al_load_ttf_font("fonts/retro.ttf", aux1,0);
    ALLEGRO_FONT *font9 = al_load_ttf_font("fonts/retro.ttf", aux1,0);
    ALLEGRO_FONT *font10 = al_load_ttf_font("fonts/retro.ttf", aux1,0);
    ALLEGRO_FONT *font11 = al_load_ttf_font("fonts/retro.ttf", aux1,0);
    
    ALLEGRO_FONT *fontA = al_load_ttf_font("fonts/retro.ttf", aux1,0);
    ALLEGRO_FONT *fontB = al_load_ttf_font("fonts/retro.ttf", aux1,0);
    ALLEGRO_FONT *fontC = al_load_ttf_font("fonts/retro.ttf", aux1,0);

    int txtHeight = al_get_font_line_height(fonts[0]);
    int f4L = al_get_text_width(fonts[0], "Return");
    int f5L = al_get_text_width(fonts[0], "<");
    int f6L = al_get_text_width(fonts[0], ">");

    ALLEGRO_MOUSE_STATE mouse;
    al_get_mouse_state(&mouse);
    int x1 = larguraEscolhida/2 - (400*scale);

    int mouse_x = 0;
    int mouse_y = 0;

    int button1Ac = 0;
    int button2Ac = 0;
    int button3Ac = 0;
    int button4Ac = 0;
    int button5Ac = 0;
    int button6Ac = 0;

    int button9Ac = 0;
    int button10Ac = 0;
    int button11Ac = 0;
    int button7Ac = 0;
    int button8Ac = 0;

    int buttonA = 0;
    int buttonB = 0;
    int buttonC = 0;
    
    char* volumVals[11] = {"0.0", "0.1", "0.2", "0.3", "0.4", "0.5", "0.6", "0.7", "0.8", "0.9", "1.0"};
    
    void verifyButtons(void){
        if(button1Ac && f < quant-1){
            f++;
            font7 = fonts[f];
        }else if(f > 0 && !button1Ac){
            f--;
            font7 = fonts[f];
        }

        if(button2Ac && fb1 < quant-1){
            fb1++;
            font1 = fonts[fb1];
        }else if(fb1 > 0 && !button2Ac){
            fb1--;
            font1 = fonts[fb1];
        }

        if(button3Ac && fb2 < quant-1){
            fb2++;
            font2 = fonts[fb2];
        }else if(fb2 > 0 && !button3Ac){
            fb2--;
            font2 = fonts[fb2];
        }

        if(button4Ac && fb3 < quant-1){
            fb3++;
            font3 = fonts[fb3];
        }else if(fb3 > 0 && !button4Ac){
            fb3--;
            font3 = fonts[fb3];
        }

        if(button5Ac && fb4 < quant-1){
            fb4++;
            font4 = fonts[fb4];
        }else if(fb4 > 0 && !button5Ac){
            fb4--;
            font4 = fonts[fb4];
        }

        if(button6Ac && fb5 < quant-1){
            fb5++;
            font5 = fonts[fb5];
        }else if(fb5 > 0 && !button6Ac){
            fb5--;
            font5 = fonts[fb5];
        }

        if(button7Ac && fb6 < quant-1){
            fb6++;
            font6 = fonts[fb6];
        }else if(fb6 > 0 && !button7Ac){
            fb6--;
            font6 = fonts[fb6];
        }

        if(button8Ac && f2 < quant-1){
            f2++;
            font8 = fonts[f2];
        }else if(f2 > 0 && !button8Ac){
            f2--;
            font8 = fonts[f2];
        }

        if(button9Ac && f9 < quant-(4*scale)){
            f9++;
            font9 = fonts[f9];
        }else if(f9 > 0 && !button9Ac){
            f9--;
            font9 = fonts[f9];
        }

        if(button10Ac && f10 < quant-(4*scale)){
            f10++;
            font10 = fonts[f10];
        }else if(f10 > 0 && !button10Ac){
            f10--;
            font10 = fonts[f10];
        }

        if(button11Ac && f11 < quant-1){
            f11++;
            font11 = fonts[f11];
        }else if(f11 > 0 && !button11Ac){
            f11--;
            font11 = fonts[f11];
        }

        if(buttonA && fA < quant-1){
            fA++;
            fontA = fonts[fA];
        }else if(fA > 0 && !buttonA){
            fA--;
            fontA = fonts[fA];
        }

        if(buttonB && fB < quant-(6*scale)){
            fB++;
            fontB = fonts[fB];
        }else if(fB > 0 && !buttonB){
            fB--;
            fontB = fonts[fB];
        }

        if(buttonC && fC < quant-(2*scale)){
            fC++;
            fontC = fonts[fC];
        }else if(fC > 0 && !buttonC){
            fC--;
            fontC = fonts[fC];
        }
    }
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

    int index = resInd;
    if(fullscreen){
        strcpy(str2, strDisp);
    }else{
        strcpy(str2, resolutions[resInd]);
    }
    char str1[3];
    int fullscreenAux;
    if(fullscreen){
        strcpy(str1, "ON");
        fullscreenAux = 1;
    }else{
        strcpy(str1, "OFF");
        fullscreenAux = 0;
    }
    int op = (fullscreenAux) ? 100 : 255;

    int p1 = al_get_text_width(font, "FullScreen:") + 30;
    int seta = al_get_text_width(font, "<") + (al_get_text_width(font, "OFF") / 2) + 10;
    int seta2 = (al_get_text_width(font, "OFF") / 2) + 10;
    int p2 = al_get_text_width(font, "Resolution:") + 30;
    int seta3 = al_get_text_width(font, "<") + (al_get_text_width(font, "1920 X 1080") / 2) + 10;
    int seta4 = (al_get_text_width(font, "1920 X 1080") / 2) + 10;
    int p3 = al_get_text_width(font, "Volume:") + 30;
    int seta5 = al_get_text_width(font, "<") + (al_get_text_width(font, "1.0") / 2) + 10;
    int seta6 = (al_get_text_width(font, "1.0") / 2) + 10;
    int text_width = al_get_text_width(font8, "Apply Resolution");

    int different = 0;
    int keyAux = 0;
    int usingKey = 0;
    while(1)
    {
        if(al_event_queue_is_empty(event_queue)){

            different = (index == auxInd && fullscreenAux == auxFullScreen) ? 0 : 1;
            op2 = (different == 1) ? 255 : 100;
            if(keyAux){
                verifyButtons();
                drawnOptions(menu_snapshot, font, font1, font2, font3, font4, font5, font6, font7, font8, font9, font10, font11, fontA, fontB, fontC, txtHeight, str1, str2, volumVals[menuSound], op, op2);
                continue;
            }
            if(mouse_x >= x1){
                if(mouse_x <= x1 + f4L && (mouse_y >= alturaEscolhida/2 + ((float)(1.0)*txtHeight) + distance * 2 && mouse_y <= alturaEscolhida/2 + ((float)(1.0)*txtHeight) + distance * 2 + txtHeight)){
                    button1Ac = 1;
                }else if(mouse_x >= x1 + p1 && mouse_x <= x1+ p1 + f5L && mouse_y >= alturaEscolhida/2 - ((float)(2.0)*txtHeight) - distance*2 && mouse_y <= alturaEscolhida/2 - ((float)(2.0)*txtHeight) - distance*2 + txtHeight){
                    button2Ac = 1;
                }else if(mouse_x >= x1 + p1 + seta + seta2 && mouse_x <= x1 + p1 + seta + seta2 + f6L && mouse_y >= alturaEscolhida/2 - ((float)(2.0)*txtHeight) - distance*2 && mouse_y <= alturaEscolhida/2 - ((float)(2.0)*txtHeight) - distance*2 + txtHeight){
                    button3Ac = 1;
                }else if(!fullscreenAux && mouse_x >= x1 + p2 && mouse_x <= x1 + p2 + f5L && mouse_y >= alturaEscolhida/2 - ((float)(1.0)*txtHeight) - distance/2 && mouse_y <= alturaEscolhida/2 - ((float)(1.0)*txtHeight) - distance/2 + txtHeight){
                    button4Ac = 1;
                }else if(!fullscreenAux && mouse_x >= x1 + p2 + seta3 + seta4 && mouse_x <= x1 + p2 + seta3 + seta4 + f6L && mouse_y >= alturaEscolhida/2 - ((float)(1.0)*txtHeight) - distance/2 && mouse_y <= alturaEscolhida/2 - ((float)(1.0)*txtHeight) - distance/2 + txtHeight){
                    button5Ac = 1;
                }else if(mouse_x >= x1 + p3 && mouse_x <= x1 + p3 + f5L && mouse_y >= alturaEscolhida/2 + distance/2 && mouse_y <= alturaEscolhida/2 + distance/2 + txtHeight){
                    button6Ac = 1;
                }else if(mouse_x >= x1 + p3 + seta5 + seta6 && mouse_x <= x1 + p3 + seta5 + seta6 + f6L && mouse_y >= alturaEscolhida/2 + distance/2 && mouse_y <= alturaEscolhida/2 + distance/2 + txtHeight){
                    button7Ac = 1;
                }else if(different && mouse_x >= larguraEscolhida/2 - text_width / 2 && mouse_x <= larguraEscolhida/2 + text_width / 2 && mouse_y >= alturaEscolhida / 2 + (200 * scale) && mouse_y <= alturaEscolhida / 2 + (200 * scale) + txtHeight){
                    button8Ac = 1;
                }else{
                    button1Ac = 0;
                    button2Ac = 0;
                    button3Ac = 0;
                    button4Ac = 0;
                    button5Ac = 0;
                    button6Ac = 0;
                    button7Ac = 0;
                    button8Ac = 0;
                    button9Ac = 0;
                    button10Ac = 0;
                    button11Ac = 0;
                    buttonA = 0;
                    buttonB = 0;
                    buttonC = 0;
                }
            }else{
                button1Ac = 0;
                button2Ac = 0;
                button3Ac = 0;
                button4Ac = 0;
                button5Ac = 0;
                button6Ac = 0;
                button7Ac = 0;
                button8Ac = 0;
                button9Ac = 0;
                button10Ac = 0;
                button11Ac = 0;
                buttonA = 0;
                buttonB = 0;
                buttonC = 0;
            }
            verifyButtons();
            drawnOptions(menu_snapshot, font, font1, font2, font3, font4, font5, font6, font7, font8, font9, font10, font11, fontA, fontB, fontC, txtHeight, str1, str2, volumVals[menuSound], op, op2);
        }  
        al_wait_for_event(event_queue, &event); 
        if(event.type==ALLEGRO_EVENT_DISPLAY_CLOSE){
            al_destroy_display(display);
            al_destroy_timer(timer);
            al_destroy_audio_stream(menuTheme);
            return;
        }else if(event.type == ALLEGRO_EVENT_MOUSE_AXES) {
            keyAux = 0;
            mouse_x = event.mouse.x;
            mouse_y = event.mouse.y;
        }else if (event.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN){
            if (event.mouse.button == 1) {
                mouse_x = event.mouse.x;
                mouse_y = event.mouse.y;
                if(mouse_x >= x1 && mouse_x <= x1 + f4L && mouse_y >= alturaEscolhida/2 + ((float)(1.0)*txtHeight) + distance * 2 && mouse_y <= alturaEscolhida/2 + ((float)(1.0)*txtHeight) + distance * 2 + txtHeight){
                    *clicked = 0;
                    *optionsMenu = 0;
                    break;
                }else if(mouse_x >= x1 + p1 && mouse_x <= x1+ p1 + f5L && mouse_y >= alturaEscolhida/2 - ((float)(2.0)*txtHeight) - distance*2 && mouse_y <= alturaEscolhida/2 - ((float)(2.0)*txtHeight) - distance*2 + txtHeight){
                    fullscreenAux = !fullscreenAux;
                    if(fullscreenAux){
                        strcpy(str2, strDisp);
                        op = 100;
                        strcpy(str1, "ON");
                        index = q-1;
                    }else{
                        op = 255;
                        strcpy(str1, "OFF");
                        index = q-1;
                    }
                }else if(mouse_x >= x1 + p1 + seta + seta2 && mouse_x <= x1 + p1 + seta + seta2 + f6L && mouse_y >= alturaEscolhida/2 - ((float)(2.0)*txtHeight) - distance*2 && mouse_y <= alturaEscolhida/2 - ((float)(2.0)*txtHeight) - distance*2 + txtHeight){
                    fullscreenAux = !fullscreenAux;
                    if(fullscreenAux){
                        strcpy(str2, strDisp);
                        op = 100;
                        strcpy(str1, "ON");
                        index = q-1;
                    }else{
                        op = 255;
                        strcpy(str1, "OFF");
                        index = q-1;
                    }
                }else if(!fullscreenAux && mouse_x >= x1 + p2 && mouse_x <= x1 + p2 + f5L && mouse_y >= alturaEscolhida/2 - ((float)(1.0)*txtHeight) - distance/2 && mouse_y <= alturaEscolhida/2 - ((float)(1.0)*txtHeight) - distance/2 + txtHeight){
                    if(index > 0){
                        index--;
                        strcpy(str2, resolutions[index]);
                        resInd = index;
                    }else{
                        index = q-1;
                        strcpy(str2, resolutions[index]);
                        resInd = index;
                    }
                }else if(!fullscreenAux && mouse_x >= x1 + p2 + seta3 + seta4 && mouse_x <= x1 + p2 + seta3 + seta4 + f6L && mouse_y >= alturaEscolhida/2 - ((float)(1.0)*txtHeight) - distance/2 && mouse_y <= alturaEscolhida/2 - ((float)(1.0)*txtHeight) - distance/2 + txtHeight){
                    if(index < q-1){
                        index++;
                        strcpy(str2, resolutions[index]);
                        resInd = index;
                    }else{
                        index = 0;
                        strcpy(str2, resolutions[index]);
                        resInd = index;
                    }
                }else if(mouse_x >= x1 + p3 && mouse_x <= x1 + p3 + f5L && mouse_y >= alturaEscolhida/2 + distance/2 && mouse_y <= alturaEscolhida/2 + distance/2 + txtHeight){
                    if(menuSound > 0){
                        menuSound--;
                        al_set_audio_stream_gain(menuTheme, menuSound/10.0);
                    }
                }else if(mouse_x >= x1 + p3 + seta5 + seta6 && mouse_x <= x1 + p3 + seta5 + seta6 + f6L && mouse_y >= alturaEscolhida/2 + distance/2 && mouse_y <= alturaEscolhida/2 + distance/2 + txtHeight){
                    if(menuSound < 10){
                        menuSound++;
                        al_set_audio_stream_gain(menuTheme, menuSound/10.0);
                    }
                }else if(different && mouse_x >= larguraEscolhida/2 - text_width / 2 && mouse_x <= larguraEscolhida/2 + text_width / 2 && mouse_y >= alturaEscolhida / 2 + (200 * scale) && mouse_y <= alturaEscolhida / 2 + (200 * scale) + txtHeight){
                    *newRes = 1;
                    resInd = index;
                    alturaEscolhida = alturas[resInd];
                    larguraEscolhida = larguras[resInd];
                    fullscreen = fullscreenAux;
                    break;
                }   
            }
        }else if(event.type == ALLEGRO_EVENT_KEY_DOWN){
            if(event.keyboard.keycode == ALLEGRO_KEY_ESCAPE && ((al_get_time() - *lastEsc) >= 0.3))
            {
                al_flush_event_queue(event_queue);
                *closeEsc = 1;
                break;
            }else if(event.keyboard.keycode == ALLEGRO_KEY_UP || event.keyboard.keycode == ALLEGRO_KEY_DOWN){
                button1Ac = 0;
                button2Ac = 0;
                button3Ac = 0;
                button4Ac = 0;
                button5Ac = 0;
                button6Ac = 0;
                button7Ac = 0;
                button8Ac = 0;
                button9Ac = 0;
                button10Ac = 0;
                button11Ac = 0;
                buttonA = 0;
                buttonB = 0;
                buttonC = 0;
                keyAux = 1;
                if(!usingKey){
                    usingKey = 9;
                    button9Ac = 1;
                    button2Ac = 1;
                    button3Ac = 1;
                    buttonA = 1;
                    continue;
                }if(event.keyboard.keycode == ALLEGRO_KEY_UP){
                    switch(usingKey){
                        case 9:
                            usingKey = 9;
                            button9Ac = 1;
                            button2Ac = 1;
                            button3Ac = 1;
                            buttonA = 1;
                            break;
                        case 10:
                            usingKey = 9;
                            button9Ac = 1;
                            button2Ac = 1;
                            button3Ac = 1;
                            buttonA = 1;
                            button10Ac = 0;
                            button4Ac = 0;
                            button5Ac = 0;
                            buttonB = 0;
                            break;
                        case 11:
                            usingKey = 10;
                            button10Ac = 1;
                            button4Ac = 1;
                            button5Ac = 1;
                            buttonB = 1;
                            button11Ac = 0;
                            button6Ac = 0;
                            button7Ac = 0;
                            buttonC = 0;
                            break;
                        case 1:
                            usingKey = 11;
                            button11Ac = 1;
                            button6Ac = 1;
                            button7Ac = 1;
                            buttonC = 1;
                            button1Ac = 0;
                            break;
                        case 8:
                            usingKey = 1;
                            button1Ac = 1;
                            button8Ac = 0;
                            break;
                    }
                    continue;
                }else if(event.keyboard.keycode == ALLEGRO_KEY_DOWN){
                    switch(usingKey){
                        case 9:
                            usingKey = 10;
                            button10Ac = 1;
                            button4Ac = 1;
                            button5Ac = 1;
                            buttonB = 1;
                            button9Ac = 0;
                            button2Ac = 0;
                            button3Ac = 0;
                            buttonA = 0;
                            break;
                        case 10:
                            usingKey = 11;
                            button11Ac = 1;
                            button6Ac = 1;
                            button7Ac = 1;
                            buttonC = 1;
                            button10Ac = 0;
                            button4Ac = 0;
                            button5Ac = 0;
                            buttonB = 0;
                            break;
                        case 11:
                            usingKey = 1;
                            button1Ac = 1;
                            button11Ac = 0;
                            button6Ac = 0;
                            button7Ac = 0;
                            buttonC = 0;
                            break;
                        case 1:
                            usingKey = 8;
                            button8Ac = 1;
                            button1Ac = 0;
                            break;
                        case 8:
                            usingKey = 8;
                            button8Ac = 1;
                            break;
                    }
                    continue;
                }
            }else if((event.keyboard.keycode == ALLEGRO_KEY_LEFT || event.keyboard.keycode == ALLEGRO_KEY_RIGHT) && (usingKey == 9 || usingKey == 10 || usingKey == 11)){
                if(usingKey == 9){
                    if(event.keyboard.keycode == ALLEGRO_KEY_LEFT){
                        fullscreenAux = !fullscreenAux;
                        if(fullscreenAux){
                            strcpy(str2, strDisp);
                            op = 100;
                            strcpy(str1, "ON");
                            index = q-1;
                        }else{
                            op = 255;
                            strcpy(str1, "OFF");
                            index = q-1;
                        }
                        continue;
                    }
                    if(event.keyboard.keycode == ALLEGRO_KEY_RIGHT){
                        fullscreenAux = !fullscreenAux;
                        if(fullscreenAux){
                            strcpy(str2, strDisp);
                            op = 100;
                            strcpy(str1, "ON");
                            index = q-1;
                        }else{
                            op = 255;
                            strcpy(str1, "OFF");
                            index = q-1;
                        }
                        continue;
                    }
                }else if(usingKey == 10){
                    if(fullscreenAux){
                        continue;
                    }
                    if(event.keyboard.keycode == ALLEGRO_KEY_LEFT){
                        if(index > 0){
                            index--;
                            strcpy(str2, resolutions[index]);
                            resInd = index;
                        }else{
                            index = q-1;
                            strcpy(str2, resolutions[index]);
                            resInd = index;
                        }
                        continue;
                    }
                    if(event.keyboard.keycode == ALLEGRO_KEY_RIGHT){
                        if(index < q-1){
                            index++;
                            strcpy(str2, resolutions[index]);
                            resInd = index;
                        }else{
                            index = 0;
                            strcpy(str2, resolutions[index]);
                            resInd = index;
                        }
                        continue;
                    }
                }else if(usingKey == 11){
                    if(event.keyboard.keycode == ALLEGRO_KEY_LEFT){
                        if(menuSound > 0){
                            menuSound--;
                            al_set_audio_stream_gain(menuTheme, menuSound/10.0);
                        }
                        continue;
                    }
                    if(event.keyboard.keycode == ALLEGRO_KEY_RIGHT){
                        if(menuSound < 10){
                            menuSound++;
                            al_set_audio_stream_gain(menuTheme, menuSound/10.0);
                        }
                        continue;
                    }
                }
            }else if(event.keyboard.keycode == ALLEGRO_KEY_ENTER && (usingKey == 1 || usingKey == 8)){
                if(usingKey == 1){
                    *clicked = 0;
                    *optionsMenu = 0;
                    break; 
                }
                if(usingKey == 8 && different){
                    *newRes = 1;
                    resInd = index;
                    alturaEscolhida = alturas[resInd];
                    larguraEscolhida = larguras[resInd];
                    fullscreen = fullscreenAux;
                    break;
                }
            }
        }
    }
    for (int i = 0; i < quant; i++) {
        al_destroy_font(fonts[i]);
    }
}