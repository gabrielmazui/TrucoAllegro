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
extern int toMenu1;
extern int exitGame;
extern int restartGame;



typedef struct character{
    char name[USER_MAX+1];
    ALLEGRO_BITMAP* pfp;
}character; 

extern character opponent;
extern character user;

// main game
typedef enum {
    ESPADAS, BASTOS, OUROS, COPAS
} Naipe;

typedef enum {
    AS = 1, DOIS, TRES, QUATRO, CINCO, SEIS, SETE, DEZ, ONZE, DOZE
} Valor;

typedef struct carta{
    ALLEGRO_BITMAP* img;
    Naipe naipe;
    Valor valor;
    int envido;
    int power;
    int out;
}Carta;

typedef struct Cards{
    Carta arrCartasUsr[3];
    Carta arrCartasOpp[3];
    int cartasJogadasOrdem[6][2];
    int cartasJogadas[6][2]; // [[quem jogou(1 ou 2), carta jogada]] 1 -> user 2 -> bot
}Cards;

typedef struct images{
    ALLEGRO_BITMAP* fosforo;
    ALLEGRO_BITMAP* reverso;
    ALLEGRO_BITMAP* mesa;
}images;

typedef struct Animations{
    int animationHappening;
    int baralhoAnimation;
    int cordsAux[7];
    int cords[12];
}Animations;

typedef struct Round{
    int mao;
    int usrTurn;
    int cardsPlayed;
    int pointsRound;
    int firstRoundEndVerify;
    double timeRoundEndVerify;
    int firstBotJogadaVerify;
    double timeBotJogadaVerify;
    int roundsWon[3];
    void (*jogarCarta)(int, int); // quem vai jogar, index da carta
}Round;

typedef struct game{
    int maxPoints;
    int opponentPoints;
    int userPoints;
    images imagens;
    Cards* cartas; 
    Animations* animations;
    int gameRounds;
    Round* round;
}Game;

const char* nomesNaipes[4];

#endif
