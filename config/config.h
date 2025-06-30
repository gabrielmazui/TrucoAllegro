#ifndef CONFIG_H
#define CONFIG_H

#include <stdio.h>
#include <allegro5/allegro5.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <string.h>

#define USER_MAX 18
#define FPS 90
#define LARGURA_TELA 1280
#define ALTURA_TELA 720
#define total_rects 16

extern ALLEGRO_DISPLAY *display;
extern ALLEGRO_EVENT_QUEUE *event_queue;
extern ALLEGRO_TIMER *timer;
extern ALLEGRO_AUDIO_STREAM *menuTheme;
extern ALLEGRO_BITMAP* menu_snapshot;
ALLEGRO_BITMAP *background;
int larguraB;
int alturaB;
extern int menuSound;
extern int resInd;
extern float scale;
extern int larguraEscolhida;
extern int alturaEscolhida;
extern int fullscreen;
extern int gamePaused;
extern ALLEGRO_EVENT event;
extern char username[USER_MAX];
extern int toMenu1;
extern int exitGame;

#endif
