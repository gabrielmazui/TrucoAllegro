#include <allegro5/allegro5.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <string.h>
#include "config.h"

char username[USER_MAX] = "";
ALLEGRO_DISPLAY *display = NULL;
ALLEGRO_EVENT_QUEUE *event_queue = NULL;
ALLEGRO_TIMER *timer = NULL;
ALLEGRO_AUDIO_STREAM *menuTheme = NULL;
ALLEGRO_BITMAP* menu_snapshot = NULL;
ALLEGRO_BITMAP *background = NULL;
int larguraB;
int alturaB;
ALLEGRO_EVENT event;
int resInd;
int menuSound;
int larguraEscolhida;
int alturaEscolhida;
int fullscreen;
float scale;
int gamePaused = 0;
int toMenu1 = 0;
int exitGame = 0;