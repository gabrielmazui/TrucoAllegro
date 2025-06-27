#include <stdio.h>
#include <allegro5/allegro5.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_font.h>

void drawnRes(ALLEGRO_FONT *font1, char* strVal1, char* strVal2, int op){
    int pMain = (1280)/2 - 400;
    int p1 = al_get_text_width(font1, "FullScreen:") + 30;
    int p2 = al_get_text_width(font1, "Resolution:") + 30;

    int seta = al_get_text_width(font1, "<") + (al_get_text_width(font1, "OFF") / 2) + 10;
    int seta2 = (al_get_text_width(font1, "OFF") / 2) + 10;

    al_clear_to_color(al_map_rgb(0, 0, 0));
    al_draw_text(font1, al_map_rgba(255, 255, 255, 255), pMain, (720/2) - 100 , 0,"FullScreen:");
    al_draw_text(font1, al_map_rgba(255, 255, 255, 255), pMain + p1, (720/2) - 100  , 0,"<");
    al_draw_text(font1, al_map_rgba(255, 255, 255, 255), pMain + p1 + seta, (720/2) - 100  ,ALLEGRO_ALIGN_CENTRE, strVal1);
    al_draw_text(font1, al_map_rgba(255, 255, 255, 255), pMain + p1 + seta + seta2, (720/2) - 100 , 0,">");

    int seta3 = al_get_text_width(font1, "<") + (al_get_text_width(font1, "1920 X 1080") / 2) + 10;
    int seta4 = (al_get_text_width(font1, "1920 X 1080") / 2) + 10;

    al_draw_text(font1, al_map_rgba(op, op, op, 255), pMain, (720/2) , 0,"Resolution:");
    al_draw_text(font1, al_map_rgba(op, op, op, 255), pMain + p2, (720/2) , 0,"<");
    al_draw_text(font1, al_map_rgba(op, op, op, 255), pMain + p2 + seta3, (720/2),ALLEGRO_ALIGN_CENTRE, strVal2);
    al_draw_text(font1, al_map_rgba(op, op, op, 255), pMain + p2 + seta3 + seta4, (720/2), 0,">");

    al_draw_text(font1, al_map_rgba(255, 255, 255, 255), 1280/2, 600 , ALLEGRO_ALIGN_CENTRE,"Done");

    al_flip_display();
}
