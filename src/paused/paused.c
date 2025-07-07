#include <stdio.h>
#include <allegro5/allegro5.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_font.h>

#include "..\..\config\config.h"
#include "drawnpaused.h"
#include "paused.h"
#include "options.h"

void paused(ALLEGRO_BITMAP* menu_snapshot, int restart, double* lastEsc, int* newRes){
    int distance = scale*10;
    int aux1 = 50*scale;
    int quant = 10*scale;
    ALLEGRO_FONT *fonts[quant];
    for (int i = 0; i < quant; i++) {
        int size = aux1 + i;
        fonts[i] = al_load_font("fonts/retro.ttf", size, 0);
    }
    int f1 = 0;
    int f2 = 0;
    int f3 = 0;
    int f4 = 0;
    int f5 = 0;
    ALLEGRO_FONT *font1 = al_load_ttf_font("fonts/retro.ttf", aux1,0);
    ALLEGRO_FONT *font2 = al_load_ttf_font("fonts/retro.ttf", aux1,0);
    ALLEGRO_FONT *font3 = al_load_ttf_font("fonts/retro.ttf", aux1,0);
    ALLEGRO_FONT *font4 = al_load_ttf_font("fonts/retro.ttf", aux1,0);
    ALLEGRO_FONT *font5 = al_load_ttf_font("fonts/retro.ttf", aux1,0);
    int txtHeight = al_get_font_line_height(fonts[0]);
    int f1L = al_get_text_width(fonts[0], "Resume");
    int f2L = al_get_text_width(fonts[0], "Options");
    int f3L = al_get_text_width(fonts[0], "Back to main menu");
    int f4L = al_get_text_width(fonts[0], "Exit");
    int f5L = al_get_text_width(fonts[0], "Restart");
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
    int clicked = 0;
    void verifyButtons(void){
        if(button1Ac && f1 < quant-1){
            f1++;
            font1 = fonts[f1];
        }else if(f1 > 0 && !button1Ac){
            f1--;
            font1 = fonts[f1];
        }

        if(button2Ac && f2 < quant-1){
            f2++;
            font2 = fonts[f2];
        }else if(f2 > 0 && !button2Ac){
            f2--;
            font2 = fonts[f2];
        }

        if(button3Ac && f3 < quant-1){
            f3++;
            font3 = fonts[f3];
        }else if(f3 > 0 && !button3Ac){
            f3--;
            font3 = fonts[f3];
        }

        if(button4Ac && f4 < quant-1){
            f4++;
            font4 = fonts[f4];
        }else if(f4 > 0 && !button4Ac){
            f4--;
            font4 = fonts[f4];
        }

        if(button5Ac && f5 < quant-1){
            f5++;
            font5 = fonts[f5];
        }else if(f5 > 0 && !button5Ac){
            f5--;
            font5 = fonts[f5];
        }
    }
    int optionsMenu = 0;
    int usingKey = 0;
    int keyAux = 0;
    int closeEsc = 0;
    while(1)
    {
        if(al_event_queue_is_empty(event_queue)){
            if(*newRes == 1 || closeEsc){
                break;
            }
            if(keyAux){
                verifyButtons();
                drawnpaused(menu_snapshot, restart, font1, font2, font3, font4, font5, txtHeight);
                continue;
            }
            if(clicked || optionsMenu){
                continue;
            }
            if(restart){
                if(mouse_x >= x1){
                    if(mouse_x <= x1 + f1L && (mouse_y >= alturaEscolhida/2 - ((float)(5.0/2.0)*txtHeight)- distance*2) && mouse_y<= alturaEscolhida/2 - ((float)(5.0/2.0)*txtHeight)- distance*2 + txtHeight){
                        button1Ac = 1;
                        usingKey = 1;

                    }else if(mouse_x <= x1 + f5L && (mouse_y >= alturaEscolhida/2 - ((float)(3.0/2.0)*txtHeight)- distance && mouse_y<= alturaEscolhida/2 - ((float)(3.0/2.0)*txtHeight)- distance + txtHeight)){
                        button5Ac = 1;
                        usingKey = 5;

                    }else if(mouse_x <= x1 + f2L && (mouse_y >= alturaEscolhida/2 - ((float)(1.0/2.0)*txtHeight) && mouse_y<= alturaEscolhida/2 - ((float)(1.0/2.0)*txtHeight) + txtHeight)){
                        button2Ac = 1;
                        usingKey = 2;

                    }else if(mouse_x <= x1 + f3L && (mouse_y >= alturaEscolhida/2 + ((float)(1.0/2.0)*txtHeight)+ distance && mouse_y<= alturaEscolhida/2 + ((float)(1.0/2.0)*txtHeight)+ distance + txtHeight)){
                        button3Ac = 1;
                        usingKey = 3;

                    }else if(mouse_x <= x1 + f4L && (mouse_y >= alturaEscolhida/2 + ((float)(3.0/2.0)*txtHeight)+ distance*2 && mouse_y<= alturaEscolhida/2 + ((float)(3.0/2.0)*txtHeight)+ distance*2 + txtHeight)){
                        button4Ac = 1;
                        usingKey = 4;

                    }else{
                        usingKey = 0;
                        button1Ac = 0;
                        button2Ac = 0;
                        button3Ac = 0;
                        button4Ac = 0;
                        button5Ac = 0;
                    }
                }else{
                    usingKey = 0;
                    button1Ac = 0;
                    button2Ac = 0;
                    button3Ac = 0;
                    button4Ac = 0;
                    button5Ac = 0;
                }
            }else{
                if(mouse_x >= x1){
                    if(mouse_x <= x1 + f1L && (mouse_y >= alturaEscolhida/2 - ((float)(2.0)*txtHeight) - distance*2 && mouse_y <= alturaEscolhida/2 - ((float)(2.0)*txtHeight) - distance*2 + txtHeight)){
                        button1Ac = 1;
                        usingKey = 1;

                    }else if(mouse_x <= x1 + f2L && (mouse_y >= alturaEscolhida/2 - ((float)(1.0)*txtHeight) - distance/2 && mouse_y <= alturaEscolhida/2 - ((float)(1.0)*txtHeight) - distance/2 + txtHeight)){
                        button2Ac = 1;
                        usingKey = 2;

                    }else if(mouse_x <= x1 + f3L && (mouse_y >= alturaEscolhida/2 + distance/2 && mouse_y <= alturaEscolhida/2 + distance/2 + txtHeight)){
                        button3Ac = 1;
                        usingKey = 3;

                    }else if(mouse_x <= x1 + f4L && (mouse_y >= alturaEscolhida/2 + ((float)(1.0)*txtHeight) + distance * 2 && mouse_y <= alturaEscolhida/2 + ((float)(1.0)*txtHeight) + distance * 2 + txtHeight)){
                        button4Ac = 1;
                        usingKey = 4;

                    }else{
                        button1Ac = 0;
                        button2Ac = 0;
                        button3Ac = 0;
                        button4Ac = 0;
                        button5Ac = 0;
                        usingKey = 0;
                    }
                }else{
                    usingKey = 0;
                    button1Ac = 0;
                    button2Ac = 0;
                    button3Ac = 0;
                    button4Ac = 0;
                    button5Ac = 0;
                }
            }
            verifyButtons();
            drawnpaused(menu_snapshot, restart, font1, font2, font3, font4, font5, txtHeight);
        }
        al_wait_for_event(event_queue, &event);
        if(event.type==ALLEGRO_EVENT_DISPLAY_CLOSE){
            al_destroy_display(display);
            al_destroy_timer(timer);
            al_destroy_audio_stream(menuTheme);
            return;
        }else if(event.type == ALLEGRO_EVENT_KEY_DOWN){
            if(event.keyboard.keycode == ALLEGRO_KEY_ESCAPE && ((al_get_time() - *lastEsc) >= 0.3) && !clicked)
            {
                al_flush_event_queue(event_queue);
                clicked = 1;
                break;
            }else if(event.keyboard.keycode == ALLEGRO_KEY_UP || event.keyboard.keycode == ALLEGRO_KEY_DOWN){
                button1Ac = 0;
                button2Ac = 0;
                button3Ac = 0;
                button4Ac = 0;
                button5Ac = 0;
                keyAux = 1;
                if(!usingKey){
                    usingKey = 1;
                    button1Ac = 1;
                    continue;
                }if(event.keyboard.keycode == ALLEGRO_KEY_UP && !restart){
                    switch(usingKey){
                        case 1:
                            usingKey = 1;
                            button1Ac = 1;
                            break;
                        case 2:
                            usingKey = 1;
                            button1Ac = 1;
                            button2Ac = 0;
                            break;
                        case 3:
                            usingKey = 2;
                            button2Ac = 1;
                            button3Ac = 0;
                            break;
                        case 4:
                            usingKey = 3;
                            button3Ac = 1;
                            button4Ac = 0;
                            break;
                    }
                    continue;
                }else if(event.keyboard.keycode == ALLEGRO_KEY_DOWN && !restart){
                    switch(usingKey){
                        case 2:
                            usingKey = 3;
                            button3Ac = 1;
                            button2Ac = 0;
                            break;
                        case 3:
                            usingKey = 4;
                            button4Ac = 1;
                            button3Ac = 0;
                            break;
                        case 4:
                            usingKey = 4;
                            button4Ac = 1;
                            break;
                        case 1:
                            usingKey = 2;
                            button2Ac = 1;
                            button1Ac = 0;
                            break;
                    }
                    continue;
                }else if(event.keyboard.keycode == ALLEGRO_KEY_UP && restart){
                    switch(usingKey){
                        case 1:
                            usingKey = 1;
                            button1Ac = 1;
                            break;
                        case 5:
                            usingKey = 1;
                            button1Ac = 1;
                            button5Ac = 0;
                            break;
                        case 2:
                            usingKey = 5;
                            button5Ac = 1;
                            button2Ac = 0;
                            break;
                        case 3:
                            usingKey = 2;
                            button2Ac = 1;
                            button3Ac = 0;
                            break;
                        case 4:
                            usingKey = 3;
                            button3Ac = 1;
                            button4Ac = 0;
                            break;
                    }
                }else if(event.keyboard.keycode == ALLEGRO_KEY_DOWN && restart){
                    switch(usingKey){
                        case 1:
                            usingKey = 5;
                            button5Ac = 1;
                            button1Ac = 0;
                            break;
                        case 5:
                            usingKey = 2;
                            button2Ac = 1;
                            button5Ac = 0;
                            break;
                        case 2:
                            usingKey = 3;
                            button3Ac = 1;
                            button2Ac = 0;
                            break;
                        case 3:
                            usingKey = 4;
                            button4Ac = 1;
                            button3Ac = 0;
                            break;
                        case 4:
                            usingKey = 4;
                            button4Ac = 1;
                            break;
                    }
                }
            }else if(event.keyboard.keycode == ALLEGRO_KEY_ENTER){
                if(keyAux){                        
                    if(usingKey == 1){
                        if(al_get_time() - *lastEsc >= 0.3){
                            al_flush_event_queue(event_queue);
                            clicked = 1;
                            break;
                        }
                    }else if(usingKey == 2){
                        clicked = 1;
                        optionsMenu = 1;
                        options(menu_snapshot, &clicked, &optionsMenu, newRes, &closeEsc, lastEsc);
                    }else if(usingKey == 3){
                        clicked = 1;
                        toMenu1 = 1;
                        break;
                    }else if(usingKey == 4){
                        clicked = 1;
                        exitGame = 1;
                        break;
                    }else if(usingKey == 5){
                        printf("restart");
                    }
                }
            }
        }else if(event.type == ALLEGRO_EVENT_MOUSE_AXES) {
            keyAux = 0;
            mouse_x = event.mouse.x;
            mouse_y = event.mouse.y;
        }else if (event.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN){
            if (event.mouse.button == 1 && !keyAux) {
                mouse_x = event.mouse.x;
                mouse_y = event.mouse.y;
                if(restart){
                    if(mouse_x >= x1 && !clicked){
                        if(mouse_x <= x1 + f1L && (mouse_y >= alturaEscolhida/2 - ((float)(5.0/2.0)*txtHeight)- distance*2) && mouse_y<= alturaEscolhida/2 - ((float)(5.0/2.0)*txtHeight)- distance*2 + txtHeight){
                            if(al_get_time() - *lastEsc >= 0.3){
                                al_flush_event_queue(event_queue);
                                clicked = 1;
                                break;
                            }

                        }else if(mouse_x <= x1 + f5L && (mouse_y >= alturaEscolhida/2 - ((float)(3.0/2.0)*txtHeight)- distance && mouse_y<= alturaEscolhida/2 - ((float)(3.0/2.0)*txtHeight)- distance + txtHeight)){
                            if(al_get_time() - *lastEsc >= 0.3){
                                al_flush_event_queue(event_queue);
                                clicked = 1;
                                restartGame = 1;
                                break;
                            }

                        }else if(mouse_x <= x1 + f2L && (mouse_y >= alturaEscolhida/2 - ((float)(1.0/2.0)*txtHeight) && mouse_y<= alturaEscolhida/2 - ((float)(1.0/2.0)*txtHeight) + txtHeight)){
                            clicked = 1;
                            optionsMenu = 1;
                            options(menu_snapshot, &clicked, &optionsMenu, newRes, &closeEsc, lastEsc);

                        }else if(mouse_x <= x1 + f3L && (mouse_y >= alturaEscolhida/2 + ((float)(1.0/2.0)*txtHeight)+ distance && mouse_y<= alturaEscolhida/2 + ((float)(1.0/2.0)*txtHeight)+ distance + txtHeight)){
                            clicked = 1;
                            toMenu1 = 1;
                            break;

                        }else if(mouse_x <= x1 + f4L && (mouse_y >= alturaEscolhida/2 + ((float)(3.0/2.0)*txtHeight)+ distance*2 && mouse_y<= alturaEscolhida/2 + ((float)(3.0/2.0)*txtHeight)+ distance*2 + txtHeight)){
                            clicked = 1;
                            exitGame = 1;
                            break;
                        }
                    }
                }else{
                    if(mouse_x >= x1 && !clicked){
                        if(mouse_x <= x1 + f1L && (mouse_y >= alturaEscolhida/2 - ((float)(2.0)*txtHeight) - distance*2 && mouse_y <= alturaEscolhida/2 - ((float)(2.0)*txtHeight) - distance*2 + txtHeight)){
                            if(al_get_time() - *lastEsc >= 0.3){
                                al_flush_event_queue(event_queue);
                                clicked = 1;
                                break;
                            }
                        }else if(mouse_x <= x1 + f2L && (mouse_y >= alturaEscolhida/2 - ((float)(1.0)*txtHeight) - distance/2 && mouse_y <= alturaEscolhida/2 - ((float)(1.0)*txtHeight) - distance/2 + txtHeight)){
                            clicked = 1;
                            optionsMenu = 1;
                            options(menu_snapshot, &clicked, &optionsMenu, newRes, &closeEsc, lastEsc);

                        }else if(mouse_x <= x1 + f3L && (mouse_y >= alturaEscolhida/2 + distance/2 && mouse_y <= alturaEscolhida/2 + distance/2 + txtHeight)){
                            clicked = 1;
                            toMenu1 = 1;
                            break;

                        }else if(mouse_x <= x1 + f4L && (mouse_y >= alturaEscolhida/2 + ((float)(1.0)*txtHeight) + distance * 2 && mouse_y <= alturaEscolhida/2 + ((float)(1.0)*txtHeight) + distance * 2 + txtHeight)){
                            clicked = 1;
                            exitGame = 1;
                            break;
                        }
                    }
                }
            }
        }
    }
    for (int i = 0; i < quant; i++) {
        if(fonts[i]){ 
            al_destroy_font(fonts[i]);
        }
    }
    *lastEsc = al_get_time();
    al_flush_event_queue(event_queue);
    return;
}