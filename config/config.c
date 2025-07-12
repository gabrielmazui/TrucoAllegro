#include <allegro5/allegro5.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <string.h>
#include "config.h"

ALLEGRO_DISPLAY *display = NULL;
ALLEGRO_EVENT_QUEUE *event_queue = NULL;
ALLEGRO_TIMER *timer = NULL;
ALLEGRO_AUDIO_STREAM *menuTheme = NULL;
ALLEGRO_BITMAP* menu_snapshot = NULL;
ALLEGRO_BITMAP *background = NULL;
character opponent = { "", NULL };
character user = { "", NULL };
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
int restartGame = 0;
int transitionMusic = 0;
const char* nomesNaipes[4] = {"Espadas", "Bastos", "Ouro",  "Copas"};