#include <stdio.h>
#include <allegro5/allegro5.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#include "..\..\..\config\config.h"
#include "..\..\..\config\config.h"
#include "..\..\animations\transition.h"
#include "drawn6.h"
#include "..\opponentChoose\opponentchoose.h"
#include "..\..\paused\paused.h"
#include "..\menu1\menu1.h"
#include "..\..\extras\newres.h"

#define x3 larguraEscolhida/2 + (50*scale)
#define x2 x3 - (143*scale)
#define x1 x3 - (286*scale)
#define yUsr alturaEscolhida - (220*scale)
#define yOpp (20*scale)
#define yUsrTable yUsr - (210*scale)
#define yOppTable yOpp + (210*scale)

Game game;
Carta baralho[40];
int cartasUsadas[40] = {0};
void carregar_baralho(Carta baralho[40]) {
    char nome[64];
    for (int n = 0; n < 4; n++) {
        for (int v = 1; v <= 10; v++) {
            int idx = n * 10 + (v - 1);
            int aux = v;
            aux = (aux>=8)? aux+2 : aux;
            sprintf(nome, "images/cards/%d%s.jpg", aux, nomesNaipes[n]);
            baralho[idx].img = al_load_bitmap(nome);
            baralho[idx].naipe = (Naipe)n;
            baralho[idx].valor = (Valor)v;
            baralho[idx].envido = (baralho[idx].valor >= 7) ?  baralho[idx].valor : 0;
            baralho[idx].out = 0;
            if(baralho[idx].naipe == ESPADAS && baralho[idx].valor == AS){
                 baralho[idx].power = 14;
            }else if(baralho[idx].naipe == BASTOS && baralho[idx].valor == AS){
                baralho[idx].power = 13;
            }else if(baralho[idx].naipe == ESPADAS && baralho[idx].valor == SETE){
                baralho[idx].power = 12;
            }else if(baralho[idx].naipe == OUROS && baralho[idx].valor == SETE){
                baralho[idx].power = 11;
            }else{
                switch(baralho[idx].valor){
                    case TRES:
                        baralho[idx].power = 10;
                        break;
                    case DOIS:
                        baralho[idx].power = 9;
                        break;
                    case AS:
                        baralho[idx].power = 8;
                        break;
                    case DOZE:
                        baralho[idx].power = 7;
                        break;
                    case ONZE:
                        baralho[idx].power = 6;
                        break;
                    case DEZ:
                        baralho[idx].power = 5;
                        break;
                    case SETE:
                        baralho[idx].power = 4;
                        break;
                    case SEIS:
                        baralho[idx].power = 3;
                        break;
                    case CINCO:
                        baralho[idx].power = 2;
                        break;
                    case QUATRO:
                        baralho[idx].power = 1;
                        break;
                }
            }
        }
    }
}

void sorteio_cartas(int indexAux, int usrIndex, int oppIndex){
    int indice;
    do {
        indice = rand() % 40;
    } while (cartasUsadas[indice]);

    cartasUsadas[indice] = 1;
    if(indexAux%2 == 0){
       game.cartas->arrCartasUsr[usrIndex] = baralho[indice];
    }else{
        game.cartas->arrCartasOpp[oppIndex] = baralho[indice];
    }
}

void chooseCards(int starter){
    // starter = 0 -> user else opponent
    int max = 7;
    int oppIndex = 0;
    int UserIndex = 0;
    if(!starter){
        max = 6;
    }
    for(int i = (!starter) ? 0 : 1; i < max; i++){
       if(i%2 == 0){
            sorteio_cartas(i, UserIndex, oppIndex);
            UserIndex++;
            continue;
        }
        sorteio_cartas(i, UserIndex, oppIndex);
        oppIndex++;
    }
    memset(cartasUsadas, 0, sizeof(cartasUsadas));
    memset((game.cartas->cartasJogadasOrdem), 0, sizeof(game.cartas->cartasJogadasOrdem));
}


void restartGameFunc(void){
    restartGame = 0;
    chooseCards(0);
    game.opponentPoints = 0;
    game.userPoints = 0;
    memset((game.cartas->cartasJogadas), 0, sizeof(game.cartas->cartasJogadas));
    memset((game.cartas->cartasJogadasOrdem), 0, sizeof(game.cartas->cartasJogadasOrdem));
    int coordAux[12] = {x1, yUsr, x2, yUsr, x3, yUsr, x1, yOpp, x2, yOpp, x3, yOpp};
    memcpy(game.animations->cords, coordAux, sizeof(coordAux));
    game.gameRounds = 0;
    game.round->usrTurn = 1;
    game.round->cardsPlayed = 0;
    game.round->firstBotJogadaVerify = 1;
    game.round->firstRoundEndVerify = 1;
    game.round->timeBotJogadaVerify = 0.0;
    game.round->timeRoundEndVerify = 0.0;
    memset(game.round->roundsWon, 0, sizeof(game.round->roundsWon));
}

void endRound(int user){
    if(game.round->firstRoundEndVerify){
        game.round->firstRoundEndVerify = 0;
        game.round->timeRoundEndVerify = al_get_time();
        return;
    }
    if(al_get_time() - game.round->timeRoundEndVerify >= 2.0){
        if(user == 1){
            game.userPoints += game.round->pointsRound;
            if(game.userPoints >= game.maxPoints){
                //end game
            }
        }else{
            game.opponentPoints += game.round->pointsRound;
            if(game.opponentPoints >= game.maxPoints){
                //end game
            }
        }
        game.gameRounds += 1;
        game.round->mao = (game.round->mao == 1) ? 2 : 1;
        game.round->usrTurn = game.round->mao;
        game.round->cardsPlayed = 0;
        chooseCards(0);
        memset((game.cartas->cartasJogadas), 0, sizeof(game.cartas->cartasJogadas));
        memset((game.cartas->cartasJogadasOrdem), 0, sizeof(game.cartas->cartasJogadasOrdem));
        int coordAux[12] = {x1, yUsr, x2, yUsr, x3, yUsr, x1, yOpp, x2, yOpp, x3, yOpp};
        memcpy(game.animations->cords, coordAux, sizeof(coordAux));
        game.round->firstRoundEndVerify = 1;
        game.round->timeRoundEndVerify = 0.0;
        memset(game.round->roundsWon, 0, sizeof(game.round->roundsWon));
    }
}

void verificarTurno(void){
    if(game.round->cardsPlayed % 2 == 0){
        int firstCardPlayer = game.cartas->cartasJogadas[(game.round->cardsPlayed) - 2][0];
        int firstCardIndex = game.cartas->cartasJogadas[(game.round->cardsPlayed) - 2][1];
        int firstCardPower = (firstCardPlayer == 1) ? game.cartas->arrCartasUsr[firstCardIndex].power : game.cartas->arrCartasOpp[firstCardIndex].power; 
        int secondCardPlayer = (firstCardPlayer == 1) ? 2 : 1;
        int secondCardIndex = game.cartas->cartasJogadas[(game.round->cardsPlayed) - 1][1];
        int secondCardPower = (secondCardPlayer == 1) ? game.cartas->arrCartasUsr[secondCardIndex].power : game.cartas->arrCartasOpp[secondCardIndex].power; 
        if(firstCardPower > secondCardPower){
            game.round->roundsWon[(game.round->cardsPlayed/2) - 1] = firstCardPlayer;
            game.round->usrTurn = firstCardPlayer;
            if(game.round->firstRoundEndVerify == 1){
                int matrizAux1[2];
                int matrizAux2[2];
                memcpy(matrizAux1, game.cartas->cartasJogadasOrdem[(game.round->cardsPlayed) - 1], sizeof(matrizAux1));
                memcpy(matrizAux2, game.cartas->cartasJogadasOrdem[(game.round->cardsPlayed) - 2], sizeof(matrizAux2));
                memcpy(game.cartas->cartasJogadasOrdem[(game.round->cardsPlayed) - 1], matrizAux2, sizeof(matrizAux2));
                memcpy(game.cartas->cartasJogadasOrdem[(game.round->cardsPlayed) - 2], matrizAux1, sizeof(matrizAux1));
            }
        }else if(firstCardPower < secondCardPower){
            game.round->roundsWon[(game.round->cardsPlayed/2) - 1] = secondCardPlayer;
            game.round->usrTurn = secondCardPlayer;
        }else{
            game.round->roundsWon[(game.round->cardsPlayed/2) - 1] = 3;
            game.round->usrTurn = game.round->mao;
        }
        if(game.round->cardsPlayed >= 4){
            if(game.round->roundsWon[0] == 3){
                if(game.round->roundsWon[1] == 1 || game.round->roundsWon[1] == 2){
                    endRound(game.round->roundsWon[1]);
                }else if(game.round->roundsWon[1] == 3){
                    if(game.round->roundsWon[2] == 1 || game.round->roundsWon[2] == 2){
                        endRound(game.round->roundsWon[2]);
                    }else if(game.round->roundsWon[2] == 3){
                        endRound(game.round->mao);
                    }
                }
            }else if(game.round->roundsWon[0] == 1 || game.round->roundsWon[0] == 2){
                if(game.round->roundsWon[1] == 3){
                    endRound(game.round->roundsWon[0]);
                }else if(game.round->roundsWon[0] == game.round->roundsWon[1]){
                    endRound(game.round->roundsWon[0]);
                }else{
                    if(game.round->roundsWon[2] == 3){
                        endRound(game.round->roundsWon[0]);
                    }else if(game.round->roundsWon[2] == 1 || game.round->roundsWon[2] == 2){
                        endRound(game.round->roundsWon[2]);
                    }
                }
            }
        }
    }else{
        game.round->usrTurn = (game.round->usrTurn == 1) ? 2 : 1;
    }
}
void jogarCarta(int user, int cardIndex){
    int cartasJogadasAux = game.round->cardsPlayed;
    game.round->cardsPlayed += 1;
    if(user == 1){
        game.cartas->arrCartasUsr[cardIndex].out = 1;
        game.cartas->cartasJogadas[cartasJogadasAux][0] = user;
        game.cartas->cartasJogadas[cartasJogadasAux][1] = cardIndex;
        game.cartas->cartasJogadasOrdem[cartasJogadasAux][0] = user;
        game.cartas->cartasJogadasOrdem[cartasJogadasAux][1] = cardIndex;

    }else{
        game.cartas->arrCartasOpp[cardIndex].out = 1;
        game.cartas->cartasJogadas[cartasJogadasAux][0] = user;
        game.cartas->cartasJogadas[cartasJogadasAux][1] = cardIndex;
        game.cartas->cartasJogadasOrdem[cartasJogadasAux][0] = user;
        game.cartas->cartasJogadasOrdem[cartasJogadasAux][1] = cardIndex;
    }
    verificarTurno();
}

int botJogada(void){
    if(game.round->firstBotJogadaVerify == 1){
        game.round->firstBotJogadaVerify = 0;
        game.round->timeBotJogadaVerify = al_get_time();
        return 0;
    }
    if(al_get_time() - game.round->timeBotJogadaVerify >= 1.5){
        int aux = game.round->cardsPlayed/2;
        jogarCarta(2, aux);
        game.round->firstBotJogadaVerify = 1;
        game.round->timeBotJogadaVerify = 0.0;
        return 1;
    }
    return 0;
}

void mainGameLoop(){
    srand(time(NULL));

    ALLEGRO_FONT *font = al_load_ttf_font("fonts/retro.ttf",30*scale,0);
    ALLEGRO_FONT *font2 = al_load_ttf_font("fonts/retro.ttf",25*scale,0);

    Animations animations = {0, 0, {x1, x2, x3, yUsr, yOpp, yUsrTable, yOppTable}, {x1, yUsr, x2, yUsr, x3, yUsr, x1, yOpp, x2, yOpp, x3, yOpp}};
    Round round = {1, 1, 0, 1, 1, 0, 1, 0,{0}, jogarCarta};
    carregar_baralho(baralho);

    images imagens = {al_load_bitmap("images/fosforo.png"), al_load_bitmap("images/cards/reverso.png"), al_load_bitmap("images/mesa.jpg")};
    
    Cards cartas;
    memset(&cartas, 0, sizeof(Cards));

    game.maxPoints = 15;
    game.opponentPoints = 0;
    game.userPoints = 0;
    game.imagens = imagens;
    game.cartas = &cartas;
    game.animations = &animations;
    game.gameRounds = 0;
    game.round = &round;

    chooseCards(0);

    ALLEGRO_BITMAP* menu_snapshot = NULL;

    menu_snapshot = al_create_bitmap(larguraEscolhida, alturaEscolhida); // tirar print da tela (para a transicao)
    al_set_target_bitmap(menu_snapshot);
    drawn6(game, font, font2);
    al_set_target_backbuffer(display);

    int animationP1 = 0;
    int animationPaused = 0;
    double timePaused;
    int auxEnd = 0;
    int auxEnd2= 0;
    int grupoAy1[total_rects];
    int grupoAy2[total_rects];
    int firstExec = 1;
    int animReady = 0;

    double lastEsc = 0.0;
    int newRes = 0;

    int mouse_x = 0;
    int mouse_y = 0;
    
    while(1)
    {
        if(al_event_queue_is_empty(event_queue)){
            if(toMenu1 || exitGame || newRes) break;
            if(restartGame && animReady){
                restartGameFunc();
                drawn6(game,font, font2);
            }
            if(animReady){
                drawn6(game, font, font2);
            }else{
                animationTransition(&animReady, menu_snapshot, &firstExec, &animationP1, &animationPaused, &timePaused, &auxEnd, &auxEnd2, grupoAy1, grupoAy2);
                if(firstExec){
                    firstExec = 0;
                }
            }
        }
        al_wait_for_event(event_queue, &event);
        if(event.type == ALLEGRO_EVENT_TIMER){
            if(game.round->usrTurn == 2 && game.round->firstRoundEndVerify == 1){
                botJogada();
            }if(game.round->firstRoundEndVerify == 0){
                verificarTurno();
            }
        }else if(event.type == ALLEGRO_EVENT_DISPLAY_CLOSE){
            al_destroy_display(display);
            al_destroy_timer(timer);
            al_destroy_audio_stream(menuTheme);
            return;
        }else if(event.type == ALLEGRO_EVENT_KEY_CHAR && animReady){
            if(event.keyboard.keycode == ALLEGRO_KEY_ESCAPE &&((al_get_time() - lastEsc) >= 0.3)){
                lastEsc = al_get_time();
                menu_snapshot = al_create_bitmap(larguraEscolhida, alturaEscolhida); // tirar print da tela (para a transicao)
                al_set_target_bitmap(menu_snapshot);
                drawn6(game, font, font2);
                al_set_target_backbuffer(display);
                paused(menu_snapshot, 1, &lastEsc, &newRes);
                al_flush_event_queue(event_queue);
                continue;
            }
        }else if(event.type == ALLEGRO_EVENT_MOUSE_AXES && animReady) {
            mouse_x = event.mouse.x;
            mouse_y = event.mouse.y;
        }else if (event.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN && animReady){
            if (event.mouse.button == 1){
                mouse_x = event.mouse.x;
                mouse_y = event.mouse.y;
                if(game.round->usrTurn == 1 && game.round->firstRoundEndVerify == 1){
                    if(mouse_y >= yUsr && mouse_y <= yUsr + (180*scale)){
                        if(mouse_x >= x1 && mouse_x <= x1 + (118*scale) && game.cartas->arrCartasUsr[0].out == 0){
                            jogarCarta(1, 0);
                        }
                        else if(mouse_x >= x2 && mouse_x <= x2 + (118*scale) && game.cartas->arrCartasUsr[1].out == 0){
                            jogarCarta(1, 1);
                        }
                        else if(mouse_x >= x3 && mouse_x <= x3 + (118*scale) && game.cartas->arrCartasUsr[2].out == 0){
                            jogarCarta(1, 2);
                        }
                    }
                }
            }
        }
    }
    if(toMenu1){
        al_destroy_audio_stream(menuTheme);
        toMenu1 = 0;
        al_flush_event_queue(event_queue);
        menuLoop1();
    }else if(exitGame){
        return;
    }else if(newRes){
        al_destroy_display(display);
        al_destroy_audio_stream(menuTheme);
        al_flush_event_queue(event_queue);
        newres();
    }else{
        opponentChooseLoop();
    }
}
