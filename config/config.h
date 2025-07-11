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
    double mentira;
    double desconfianca;
    double agressividade;
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
    int mostrarExtra;
}Carta;

typedef struct Cards{ 
    int cartasJogarAux[6][2];
    int cartasJogarAux2[6][2];
    int indexEnvidop1[2];
    int indexEnvidop2[2];
    Carta arrCartasUsr[3];
    Carta arrCartasOpp[3];
    int cantarFlor[2];
    int cartasJogadasOrdem[6][2];
    int cartasJogadas[6][2]; // [[quem jogou(1 ou 2), carta jogada]] 1 -> user 2 -> bot
    int pontosEnvido[2]; // pontos de cada jogador
}Cards;

typedef struct images{
    ALLEGRO_BITMAP* fosforo;
    ALLEGRO_BITMAP* reverso;
    ALLEGRO_BITMAP* mesa;
    ALLEGRO_BITMAP* nuvem;
}images;

typedef struct Animations{
    int animationHappening;
    int baralhoAnimation;
    int cordsAux[7];
    int cords[12];
}Animations;

typedef struct Round{
    int trucoNegado;
    int alMazo;
    int alMazo2;
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


typedef struct Chamadas{
    int audiofirstTime;
    int envidoAux;
    int envidoAceito;
    int cartasNaMesaVerify;
    double cartasNaMesaVerifyTimer;
    int cartasNaMesa;
    double msgPopUpTimerUsr;
    int msgPopUpOnUsr;
    int msgPopUpAuxUsr;
    char usrMsg[80];
    double msgPopUpTimer;
    int msgPopUpOn;
    int msgPopUpAux;
    char botMsg[80];
    int respostaBot;
    int pontosValendoCantada;
    int pontosNegarCantada;

    int firstChamada;
    double timeFirstChamada;
    int aceitarPopUp;
    int cantado;
    int resultadoPopUp;
    int resultadoPopUpAux;
    double resultadoPopUpTimer;

    int truco; //(usuario que cantou truco)
    int retruco;
    int valeQuatro;
    int trucoAux;

    int p1FalarPontos;
    int p2falarPontos;
    int primeiroEnvido;
    int envidoFeito;
    int envido; //(usuario que cantou envido)
    int envido2;
    int realEnvido;
    int faltaEnvido;

    int flor;
    int contraFlor;
    int contraFlorResto;
    int florFeita;
    
    int mainButtons;
    int envidoButtons;
    int trucoButtons;
    int florButtons;
}Chamadas;

typedef struct Calculo{
    double situacaoRound; // se = 0 , 0.5, se 1, 1.0, se -1, 0
    double responderTruco;
    double cantarTruco;
    double blefeTruco; // cantar com mao ruim
    double blefeInversoTruco; // nao cantar com mao boa
    double forcaMaoTruco;
    double cartasParaJogar[3];
    double fatorHistoricoPontos;
    double forcaMaoBotPontos;
    double forcaMaoUsrPontos;
    double valorChamadaPontos;
    double inversovalorChamadaPontos;
    double valorRespostaPontos;
    double inversovalorRespostaPontos;
    double responderFlor;
    double responderFlorBlefe;
    double forcaFlor;
}Calculo;

typedef struct game{
    int maxPoints;
    int opponentPoints;
    int userPoints;
    images imagens;
    Cards* cartas; 
    Animations* animations;
    int gameRounds;
    Round* round;
    Chamadas* chamadas;
    Calculo* calculo;
}Game;

const char* nomesNaipes[4];

#endif