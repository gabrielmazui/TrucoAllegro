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
#include "maingame.h"
#include "..\..\extras\newres.h"
#include "venceu.h"

#define x3 larguraEscolhida/2 + (50*scale)
#define x2 x3 - (143*scale)
#define x1 x3 - (286*scale)
#define yUsr alturaEscolhida - (220*scale)
#define yOpp (20*scale)
#define yUsrTable yUsr - (210*scale)
#define yOppTable yOpp + (210*scale)

int venceu = 0;
int perdeu = 0;
Game game;
Carta baralho[40];
int cartasUsadas[40] = {0};
void verificarFlor(void);
void verificarEnvidoPontos(void);
void definirCalculoPontos(void);
void verificarTurno(void);

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
            baralho[idx].envido = (baralho[idx].valor <= 7) ? baralho[idx].valor : 0;
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

void endRound(int user){
    printf("ednRound");
    
    if(game.round->firstRoundEndVerify){
        game.round->firstRoundEndVerify = 0;
        game.round->timeRoundEndVerify = al_get_time();
        return;
    }
    if(al_get_time() - game.round->timeRoundEndVerify >= 2.0){
        if(game.chamadas->cartasNaMesaVerify == 0){
            game.chamadas->cartasNaMesaVerify = 1;
            game.chamadas->cartasNaMesaVerifyTimer = al_get_time();
            return;
        }
        if(al_get_time() - game.chamadas->cartasNaMesaVerifyTimer < 4.0){
            return;
        }
        for (int i = 0; i < 3; i++) {
            game.cartas->arrCartasUsr[i].mostrarExtra = 0;
            game.cartas->arrCartasOpp[i].mostrarExtra = 0;
        }
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
       

        game.chamadas->msgPopUpOnUsr = 0;
        game.chamadas->msgPopUpTimerUsr = 0.0;
        game.chamadas->cartasNaMesaVerify = 0;
        game.chamadas->cartasNaMesaVerifyTimer = 0.0;
        game.chamadas->audiofirstTime = 0;
        game.chamadas->msgPopUpOn = 0;
        game.chamadas->msgPopUpTimer = 0.0;
        game.round->alMazo2 = 0;
        game.round->alMazo = 0;
        game.round->trucoNegado = 0;
        game.chamadas->cantado = 0;
        game.chamadas->envido = 0;
        game.chamadas->envido2 = 0;
        game.chamadas->realEnvido = 0;
        game.chamadas->faltaEnvido = 0;
        game.chamadas->respostaBot = 0;
        game.chamadas->firstChamada = 1;
        game.chamadas->mainButtons = 1;
        game.chamadas->envidoFeito = 0;
        game.chamadas->aceitarPopUp = 0;
        game.chamadas->envidoButtons = 0;
        game.chamadas->resultadoPopUp = 0;
        game.chamadas->resultadoPopUpAux = 0;
        game.chamadas->truco = 0;
        game.chamadas->retruco = 0;
        game.chamadas->valeQuatro = 0;
        game.chamadas->trucoButtons = 0;
        game.chamadas->trucoAux = 0;
        game.round->firstBotJogadaVerify = 1;
        game.chamadas->envidoAceito = 0;
        game.chamadas->envidoAux = 0;
        game.chamadas->flor = 0;
        game.chamadas->contraFlor = 0;
        game.chamadas->contraFlorResto = 0;
        game.chamadas->florFeita = 0;
        game.chamadas->florButtons = 0;
        game.round->timeBotJogadaVerify = 0.0;

        game.gameRounds += 1;
        game.round->mao = (game.round->mao == 1) ? 2 : 1;
        game.round->usrTurn = game.round->mao;
        game.round->cardsPlayed = 0;
        game.round->pointsRound = 1;
        chooseCards(0);
        memset((game.cartas->cartasJogadas), 0, sizeof(game.cartas->cartasJogadas));
        memset((game.cartas->cartasJogadasOrdem), 0, sizeof(game.cartas->cartasJogadasOrdem));
        int coordAux[12] = {x1, yUsr, x2, yUsr, x3, yUsr, x1, yOpp, x2, yOpp, x3, yOpp};
        memcpy(game.animations->cords, coordAux, sizeof(coordAux));
        game.round->firstRoundEndVerify = 1;
        game.round->timeRoundEndVerify = 0.0;
        memset(game.round->roundsWon, 0, sizeof(game.round->roundsWon));
        game.round->alMazo = 0;
        verificarEnvidoPontos();
        verificarFlor();
    }
}

void verificarTurno(void){
    printf("verificarTurno");
    if(game.round->cardsPlayed % 2 == 0 && game.chamadas->envidoAux == 0){
        int firstCardPlayer = game.cartas->cartasJogadas[(game.round->cardsPlayed) - 2][0];
        int firstCardIndex = game.cartas->cartasJogadas[(game.round->cardsPlayed) - 2][1];
        int firstCardPower = (firstCardPlayer == 1) ? game.cartas->arrCartasUsr[firstCardIndex].power : game.cartas->arrCartasOpp[firstCardIndex].power; 
        int secondCardPlayer = (firstCardPlayer == 1) ? 2 : 1;
        int secondCardIndex = game.cartas->cartasJogadas[(game.round->cardsPlayed) - 1][1];
        int secondCardPower = (secondCardPlayer == 1) ? game.cartas->arrCartasUsr[secondCardIndex].power : game.cartas->arrCartasOpp[secondCardIndex].power; 
        if(firstCardPower > secondCardPower){
            game.calculo->situacaoRound -= 1;
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
            game.calculo->situacaoRound += 1;
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
    printf("jogarCarta");
    int cartasJogadasAux = game.round->cardsPlayed;
    game.round->cardsPlayed += 1;
    game.round->firstBotJogadaVerify = 1;
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

void verificarFlor(void){
    int verAux1 = 1;
    Naipe naipeCompAux = game.cartas->arrCartasUsr[0].naipe;  
    for(int i = 1; i < 3; i++){
        if(game.cartas->arrCartasUsr[i].naipe != naipeCompAux){
            verAux1 = 0;
            break;
        }
    }
    game.cartas->cantarFlor[0] = verAux1;
    
    int verAux2 = 1;
    Naipe naipeCompAux2 = game.cartas->arrCartasOpp[0].naipe;  
    for(int i = 1; i < 3; i++){
        if(game.cartas->arrCartasOpp[i].naipe != naipeCompAux2){
            verAux2 = 0;
            break;
        }
    }
    game.cartas->cantarFlor[1] = verAux2;
}
void calcularCarta(){
    int rodadaAtual = (game.round->cardsPlayed/2) + 1;
    int cartasNaMesaUsr = 0;
    double forcaMaoUsr = 0.0;
    double agressividade = (opponent.agressividade) + ((double)rand()/(double)RAND_MAX - 0.5)*0.6;
    double mentira = (opponent.mentira) + ((double)rand()/(double)RAND_MAX - 0.5)*0.6;
    double desconfianca = (opponent.desconfianca) + ((double)rand()/(double)RAND_MAX - 0.5)*0.6;
    int powerTotalBot = 0;

    double auxForcaMaoBot = 0.0;
    for(int j = 0; j < 3; j++){
        powerTotalBot += game.cartas->arrCartasOpp[j].power;
        auxForcaMaoBot += powerTotalBot/14.0;
        if(game.cartas->arrCartasUsr[j].out){
            cartasNaMesaUsr++;
            double auxF = (double)game.cartas->arrCartasUsr[j].power/14.0;
            forcaMaoUsr += auxF;
        }
    }
    if(cartasNaMesaUsr == 0){
        forcaMaoUsr = 0.5;
    }else{
       forcaMaoUsr = forcaMaoUsr/(double)cartasNaMesaUsr;
    }
    forcaMaoUsr = forcaMaoUsr/auxForcaMaoBot;
    
    for(int i = 0; i < 3; i++){
        Carta cartaAux = game.cartas->arrCartasOpp[i];
        double forcaReal = cartaAux.power;
        double riscoPerderCarta = (forcaReal*desconfianca)/rodadaAtual;
        double auxForcaIaCarta = (forcaReal*0.5) + (forcaMaoUsr*0.4) - (riscoPerderCarta*0.5);
        game.calculo->cartasParaJogar[i] = auxForcaIaCarta;
    }

    // truco
    double forcaMaoTruco = powerTotalBot/36.0;
    double situationAux = (game.calculo->situacaoRound == 1) ? 1.0 : ((game.calculo->situacaoRound == 0) ? 0.5 : 0);

    game.calculo->forcaMaoTruco = forcaMaoTruco;
    game.calculo->blefeTruco = (mentira*0.6) + ((1.0 - forcaMaoTruco)*0.4) - (forcaMaoUsr*0.3) + (((double)rand()/(double)RAND_MAX) - 0.5)*0.45;
    game.calculo->blefeInversoTruco = (mentira*0.6) + (forcaMaoTruco*0.4) + (((double)rand()/(double)RAND_MAX) - 0.5)*0.25;
    game.calculo->cantarTruco = (forcaMaoTruco*0.65) + (agressividade*0.45) - (desconfianca *0.5) - (forcaMaoUsr*0.35) + (situationAux)*0.3 + (((double)rand()/(double)RAND_MAX)-0.5)*0.4;
}
void definirCalculoPontos(void){
    // envido calculos
    int botPoints = game.cartas->pontosEnvido[1];
    double agressividade = (opponent.agressividade) + ((double)rand()/(double)RAND_MAX - 0.5)*0.6;
    double mentira = (opponent.mentira) + ((double)rand()/(double)RAND_MAX - 0.5)*0.6;
    double desconfianca = (opponent.desconfianca) + ((double)rand()/(double)RAND_MAX - 0.5)*0.6;
    double fatorHistorico = game.calculo->fatorHistoricoPontos;

    game.calculo->forcaMaoBotPontos = ((double)botPoints/33.0) + (((double)rand()/(double)RAND_MAX) - 0.5)*(0.2);

    double baseMedia = ((double)rand()/(double)RAND_MAX)*0.3;
    double AgressivMedia = agressividade/(5.0) + ((double)rand()/(double)RAND_MAX)*0.1;
    double DesconfMedia = ((double)rand()/(double)RAND_MAX)*0.3 - (desconfianca*0.2);
    
    game.calculo->forcaMaoUsrPontos = baseMedia + AgressivMedia + DesconfMedia + (fatorHistorico*0.1);

    double forcaMaoBot = game.calculo->forcaMaoBotPontos;
    double forcaMaoUsr = game.calculo->forcaMaoUsrPontos;
    double faltaEnvidoFator = ((double)(game.opponentPoints) / 30.0) - (double)(game.userPoints) / 30.0;

    game.calculo->valorChamadaPontos = (0.55*forcaMaoBot) + (agressividade*0.25) - (forcaMaoUsr * 0.2) + (faltaEnvidoFator*0.5) + (((double)rand()/(double)RAND_MAX) - 0.5)*0.15; 
    game.calculo->inversovalorChamadaPontos = (0.55*forcaMaoBot) - (agressividade*0.3) + (forcaMaoUsr * 0.2) + (mentira*0.6) - (faltaEnvidoFator*0.5) + (((double)rand()/(double)RAND_MAX) - 0.5)*0.15;
    
    game.calculo->valorRespostaPontos = (0.65*forcaMaoBot) + (agressividade*0.35) - (forcaMaoUsr * 0.2) + (faltaEnvidoFator*0.5) - (desconfianca*0.3) + (((double)rand()/(double)RAND_MAX) - 0.5)*0.15;
    game.calculo->inversovalorRespostaPontos = (agressividade*0.35) - (forcaMaoUsr * 0.3) - (faltaEnvidoFator*0.5) + (desconfianca*0.4) + (mentira*0.65) + (((double)rand()/(double)RAND_MAX) - 0.5)*0.35;
}

void calcularFlor(void){
    int botPoints = 20;
    for(int i = 0; i < 3; i ++){
        botPoints += game.cartas->arrCartasOpp[i].envido;
    }
    double agressividade = (opponent.agressividade) + ((double)rand()/(double)RAND_MAX - 0.5)*0.6;
    double mentira = (opponent.mentira) + ((double)rand()/(double)RAND_MAX - 0.5)*0.6;
    double desconfianca = (opponent.desconfianca) + ((double)rand()/(double)RAND_MAX - 0.5)*0.6;
    
    double forcaFlor = ((double)botPoints/38.0)+ (agressividade)*0.2;
    double responderFlor = (forcaFlor)*0.7 + (agressividade)*0.4 - (desconfianca)*0.3 + (((double)rand()/(double)RAND_MAX) - 0.5)*0.15;
    double responderFlorBlefe = -(forcaFlor - 1)*0.3 + (agressividade)*0.3 - (desconfianca)*0.5 + (mentira)*0.7 + (((double)rand()/(double)RAND_MAX) - 0.5)*0.35;
    game.calculo->forcaFlor = forcaFlor;
    game.calculo->responderFlor = responderFlor;
    game.calculo->responderFlorBlefe = responderFlorBlefe;
}
    
void verificarEnvidoPontos(void){
    
    int maxUsr = 0;
    for(int i = 0; i < 3; i++){
        if(game.cartas->arrCartasUsr[i].envido > maxUsr){
            maxUsr = game.cartas->arrCartasUsr[i].envido;
            game.cartas->indexEnvidop1[0] = i;
            game.cartas->indexEnvidop1[1] = -1;
        }
    }
    if(game.cartas->arrCartasUsr[0].naipe == game.cartas->arrCartasUsr[1].naipe){
        game.cartas->pontosEnvido[0] = game.cartas->arrCartasUsr[0].envido + game.cartas->arrCartasUsr[1].envido + 20;
        game.cartas->indexEnvidop1[0] = 0;
        game.cartas->indexEnvidop1[1] = 1;
    }else if(game.cartas->arrCartasUsr[0].naipe == game.cartas->arrCartasUsr[2].naipe){
        game.cartas->pontosEnvido[0] = game.cartas->arrCartasUsr[0].envido + game.cartas->arrCartasUsr[2].envido + 20;
        game.cartas->indexEnvidop1[0] = 0;
        game.cartas->indexEnvidop1[1] = 2;
    }else if(game.cartas->arrCartasUsr[1].naipe == game.cartas->arrCartasUsr[2].naipe){
        game.cartas->pontosEnvido[0] = game.cartas->arrCartasUsr[1].envido + game.cartas->arrCartasUsr[2].envido + 20;
        game.cartas->indexEnvidop1[0] = 1;
        game.cartas->indexEnvidop1[1] = 2;
    }else{
        game.cartas->pontosEnvido[0] = maxUsr;
    }
    
    int maxUsr2 = 0;
    for(int i = 0; i < 3; i++){
        if(game.cartas->arrCartasOpp[i].envido > maxUsr2){
            maxUsr2 = game.cartas->arrCartasOpp[i].envido;
            game.cartas->indexEnvidop2[0] = i;
            game.cartas->indexEnvidop2[1] = -1;
        }
    }
    if(game.cartas->arrCartasOpp[0].naipe == game.cartas->arrCartasOpp[1].naipe){
        game.cartas->pontosEnvido[1] = game.cartas->arrCartasOpp[0].envido + game.cartas->arrCartasOpp[1].envido + 20;
        game.cartas->indexEnvidop2[0] = 0;
        game.cartas->indexEnvidop2[1] = 1;
    }else if(game.cartas->arrCartasOpp[0].naipe == game.cartas->arrCartasOpp[2].naipe){
        game.cartas->pontosEnvido[1] = game.cartas->arrCartasOpp[0].envido + game.cartas->arrCartasOpp[2].envido + 20;
        game.cartas->indexEnvidop2[0] = 0;
        game.cartas->indexEnvidop2[1] = 2;
    }else if(game.cartas->arrCartasOpp[1].naipe == game.cartas->arrCartasOpp[2].naipe){
        game.cartas->pontosEnvido[1] = game.cartas->arrCartasOpp[1].envido + game.cartas->arrCartasOpp[2].envido + 20;
        game.cartas->indexEnvidop2[0] = 1;
        game.cartas->indexEnvidop2[1] = 2;
    }else{
        game.cartas->pontosEnvido[1] = maxUsr2;
    }
}

void msgBallonsUsr(int mode, int cantou, int type){
    game.chamadas->msgPopUpOnUsr = 1;
    game.chamadas->msgPopUpAuxUsr = 0;
    game.chamadas->msgPopUpTimerUsr = 0.0;
    // mode 1 -> envido
    // mode 2 -> truco
    // mode 3 -> flor
    // mode 4 -> mazo
    // cantou 0, -> type 1 aceita , 2 nao quero
    // (depende do mode)cantou 1, 1 envido, 2 envido denovo, 3 real, 4 falta
    char str[80];
    if(cantou == 0){
        if(type == 1){
            char Straux[80] = "Eu quero";
            memcpy(str, Straux, sizeof(str));
        }else {
            char Straux[80] = "Não quero";
            memcpy(str, Straux, sizeof(str));
            game.chamadas->msgPopUpAuxUsr = 1;
            game.chamadas->msgPopUpTimerUsr = al_get_time();
        }
    }else{
        if(mode == 1){
            if(type == 1){
                char Straux[80] = "Envido";
                memcpy(str, Straux, sizeof(str));
            }else if(type == 2){
                char Straux[80] = "Envido";
                memcpy(str, Straux, sizeof(str));
            }
            else if(type == 3){
                char Straux[80] = "Real envido";
                memcpy(str, Straux, sizeof(str));

            }else if(type == 4){
                char Straux[80] = "Falta envido";
                memcpy(str, Straux, sizeof(str));
            }
        }else if(mode == 2){
            if(type == 1){
                char Straux[80] = "Truco";
                memcpy(str, Straux, sizeof(str));
            }else if(type == 2){
                char Straux[80] = "Retruco";
                memcpy(str, Straux, sizeof(str));
            }else if(type == 3){
                char Straux[80] = "vale 4";
                memcpy(str, Straux, sizeof(str));
            }
        }else if(mode == 3){
            if(type == 1){
                char Straux[80] = "Flor";
                memcpy(str, Straux, sizeof(str));
            }else if(type == 2){
                char Straux[80] = "Contra Flor";
                memcpy(str, Straux, sizeof(str));
            }else if(type == 3){
                char Straux[80] = "Contra e o resto";
                memcpy(str, Straux, sizeof(str));
            }
        }else if(mode == 4){
            game.chamadas->msgPopUpAuxUsr = 1;
            game.chamadas->msgPopUpTimerUsr = al_get_time();
            char Straux[80] = "Vou ao baralho";
            memcpy(str, Straux, sizeof(str));
        }
    }  
    memcpy(game.chamadas->usrMsg, str, sizeof(str));    
}

void msgBallon(int mode, int cantou, int type){
    game.chamadas->msgPopUpOn = 1;
    game.chamadas->msgPopUpAux = 0;
    game.chamadas->msgPopUpTimer = 0.0;
    // mode 1 -> envido
    // mode 2 -> truco
    // mode 3 -> flor
    // mode 4 -> mazo
    // cantou 0, -> type 1 aceita , 2 nao quero
    // (depende do mode)cantou 1, 1 envido, 2 envido denovo, 3 real, 4 falta
    char str[80];
    if(cantou == 0){
        if(type == 1){
            char Straux[80] = "Eu quero";
            memcpy(str, Straux, sizeof(str));
        }else {
            char Straux[80] = "Não quero";
            memcpy(str, Straux, sizeof(str));
            game.chamadas->msgPopUpAux = 1;
            game.chamadas->msgPopUpTimer = al_get_time();
        }
    }else{
        if(mode == 1){
            if(type == 1){
                char Straux[80] = "Envido";
                memcpy(str, Straux, sizeof(str));
            }else if(type == 2){
                char Straux[80] = "Envido";
                memcpy(str, Straux, sizeof(str));
            }
            else if(type == 3){
                char Straux[80] = "Real envido";
                memcpy(str, Straux, sizeof(str));

            }else if(type == 4){
                char Straux[80] = "Falta envido";
                memcpy(str, Straux, sizeof(str));
            }
        }else if(mode == 2){
            if(type == 1){
                char Straux[80] = "Truco";
                memcpy(str, Straux, sizeof(str));
            }else if(type == 2){
                char Straux[80] = "Retruco";
                memcpy(str, Straux, sizeof(str));
            }else if(type == 3){
                char Straux[80] = "vale 4";
                memcpy(str, Straux, sizeof(str));
            }
        }else if(mode == 3){
            if(type == 1){
                char Straux[80] = "Flor";
                memcpy(str, Straux, sizeof(str));
            }else if(type == 2){
                char Straux[80] = "Contra Flor";
                memcpy(str, Straux, sizeof(str));
            }else if(type == 3){
                char Straux[80] = "Contra e o resto";
                memcpy(str, Straux, sizeof(str));
            }
        }else if(mode == 4){
            game.chamadas->msgPopUpAux = 1;
            game.chamadas->msgPopUpTimer = al_get_time();
            char Straux[80] = "Vou ao baralho";
            memcpy(str, Straux, sizeof(str));
        }
    }  
    memcpy(game.chamadas->botMsg, str, sizeof(str));
}

void cantarTruco(int user, int trucoType){
    printf("cantarTruco");
    // 1 truco
    // 2 retruco
    // 3 vale 4
    game.chamadas->cantado = 1;
    game.chamadas->mainButtons = 1;
    game.chamadas->trucoAux = user;
    int oppCardsPlayed = 0;
    if(user == 2){
        for(int i = 0; i<6; i++){
            if(game.cartas->cartasJogadas[i][0] == 1){
                oppCardsPlayed++;
            }
        }
        if(game.round->cardsPlayed < 2 && game.cartas->cantarFlor[0] == 1 && game.chamadas->florFeita == 0 && oppCardsPlayed == 0){
            game.chamadas->florButtons = 1;
        }else{
            game.chamadas->trucoButtons = 1;
            game.chamadas->aceitarPopUp = 1;
        }
        game.chamadas->respostaBot = 0;
        game.round->firstBotJogadaVerify = 1;
        game.round->timeBotJogadaVerify = 0.0;
    }else{
        game.chamadas->respostaBot = 1;
        game.chamadas->aceitarPopUp = 0;
        game.chamadas->trucoButtons = 0;
    }
    switch(trucoType){
        case 1:
            if(user == 2){
                msgBallon(2, 1, 1);
            }else{
                msgBallonsUsr(2, 1, 1);
            }
            game.chamadas->truco = user;
            game.chamadas->pontosNegarCantada = 1;
            game.chamadas->pontosValendoCantada = 2;
            break;
        case 2:
            if(user == 2){
                msgBallon(2, 1, 2);
            }else{
                msgBallonsUsr(2, 1, 2);
            }
            game.chamadas->truco = 0;
            game.chamadas->retruco = user;
            game.chamadas->pontosNegarCantada = 2;
            game.chamadas->pontosValendoCantada = 3;
            break;
        case 3:
            if(user == 2){
                msgBallon(2, 1, 3);
            }else{
                msgBallonsUsr(2, 1, 3);
            }
            game.chamadas->retruco = 0;
            game.chamadas->valeQuatro = user;
            game.chamadas->pontosNegarCantada = 3;
            game.chamadas->pontosValendoCantada = 4;
            game.chamadas->trucoButtons = 0;
            break;
    }
}

void aceitarTruco(int user){
    printf("aceitarTruco");
    game.chamadas->trucoAux = 0;
    if(user == 2){
        msgBallon(1, 0, 1);
    }else{
        msgBallonsUsr(1, 0, 1);
    }
    game.round->pointsRound = game.chamadas->pontosValendoCantada;
    game.chamadas->cantado = 1;
    game.chamadas->respostaBot = 0;
    game.chamadas->mainButtons = 1;
    game.chamadas->trucoButtons = 0;
    game.chamadas->aceitarPopUp = 0;
    game.chamadas->msgPopUpAux = 1;
    game.chamadas->msgPopUpTimer = al_get_time();
    game.chamadas->msgPopUpAuxUsr = 1;
    game.chamadas->msgPopUpTimerUsr = al_get_time();
    game.round->firstBotJogadaVerify = 1;
    game.round->timeBotJogadaVerify = 0.0;
    game.chamadas->envido = 0;
    game.chamadas->envido2 = 0;
    game.chamadas->realEnvido = 0;
    game.chamadas->faltaEnvido = 0;
    game.chamadas->envidoAux = 0;
    game.chamadas->florButtons = 0;
}

void negarTruco(int user){
    printf("negarTruco");
    if(user == 2){
        msgBallon(1, 0, 2);
    }else{
        msgBallonsUsr(1, 0, 2);
    }

    game.round->trucoNegado = user;
    game.round->pointsRound = game.chamadas->pontosNegarCantada;

    game.chamadas->cantado = 0;
    game.chamadas->truco = 0;
    game.chamadas->retruco = 0;
    game.chamadas->valeQuatro = 0;
    game.chamadas->trucoAux = 0;
    game.chamadas->respostaBot = 0;

    game.chamadas->mainButtons = 1;
    game.chamadas->trucoButtons = 0;
    game.chamadas->aceitarPopUp = 0;
    game.chamadas->msgPopUpAux = 1;
    game.chamadas->msgPopUpTimer = al_get_time();
    game.chamadas->msgPopUpAuxUsr = 1;
    game.chamadas->msgPopUpTimerUsr = al_get_time();

    game.round->firstBotJogadaVerify = 1;
    game.round->timeBotJogadaVerify = 0.0;
    game.chamadas->envidoAux = 0;

    game.chamadas->pontosNegarCantada = 0;
    game.chamadas->pontosValendoCantada = 0;
    endRound(user);
}

void cantarEnvido(int user, int envType){
    printf("cantarEnvido");
    game.chamadas->trucoButtons = 0;
    if(game.chamadas->flor || game.chamadas->contraFlor || game.chamadas->contraFlorResto || game.chamadas->florFeita) return;
    int opp = (user == 1) ? 2 : 1;
    int oppCardsPlayed = 0;
    for(int i = 0; i<6; i++){
        if(game.cartas->cartasJogadas[i][0] == 1){
            oppCardsPlayed++;
        }
    }
    if(user == 2){
        if(game.cartas->cantarFlor[0] == 1 && oppCardsPlayed == 0){
            game.chamadas->florButtons= 1;
            game.chamadas->mainButtons = 1;
        }else{
            game.chamadas->aceitarPopUp = 1;
            game.chamadas->envidoButtons = 1;
            game.chamadas->mainButtons = 0;
            game.chamadas->trucoButtons = 0;
            game.chamadas->florButtons= 0;

            
        }
        game.chamadas->respostaBot = 0;
        
        game.round->firstBotJogadaVerify = 1;
        game.round->timeBotJogadaVerify = al_get_time();
    }else{
        game.chamadas->respostaBot = 1;
        game.chamadas->aceitarPopUp = 0;
    }
    if(game.chamadas->cantado == 1 && game.chamadas->trucoAux == 2 && game.round->cardsPlayed == 0 && game.chamadas->envidoFeito == 0){
        if(user == 2){
            msgBallon(1, 1, 1);
        }else{
            msgBallonsUsr(1, 1, 1);
        }
        game.chamadas->trucoAux = 0;
        game.chamadas->truco = 0;
        game.chamadas->primeiroEnvido = user;
        game.chamadas->envido = user;
        game.chamadas->pontosNegarCantada = 1;
        game.chamadas->pontosValendoCantada = 2;
        return;
    }
    if(game.chamadas->cantado == 0){
        game.chamadas->cantado = 1;
        switch(envType){
            case 1:
                if(user == 2){
                    msgBallon(1, 1, 1);
                }else{
                    msgBallonsUsr(1, 1, 1);
                }
                game.chamadas->primeiroEnvido = user;
                game.chamadas->envido = user;
                game.chamadas->pontosNegarCantada = 1;
                game.chamadas->pontosValendoCantada = 2;
                return;
                break;
            case 2:
                if(user == 2){
                    msgBallon(1, 1, 3);
                }else{
                    msgBallonsUsr(1, 1, 3);
                }
                game.chamadas->primeiroEnvido = user;
                game.chamadas->realEnvido = user;
                game.chamadas->pontosNegarCantada = 1;
                game.chamadas->pontosValendoCantada = 3;
                return;
                break;
            case 3:
                if(user == 2){
                    msgBallon(1, 1, 4);
                }else{
                    msgBallonsUsr(1, 1, 4);
                }
                game.chamadas->primeiroEnvido = user;
                game.chamadas->faltaEnvido = user;
                game.chamadas->pontosNegarCantada = 1;
                game.chamadas->pontosValendoCantada = 0;
                return;
                break;
        } 
    }
    switch(envType){
        case 1:
            if(game.chamadas->envido == opp){
                if(user == 2){
                    msgBallon(1, 1, 2);
                }else{
                    msgBallonsUsr(1, 1, 2);
                }
                game.chamadas->envido = 0;
                game.chamadas->envido2 = user;
                game.chamadas->pontosNegarCantada = 2;
                game.chamadas->pontosValendoCantada = 4;
            }
            break;
        case 2:
            if(game.chamadas->envido == opp){
                if(user == 2){
                    msgBallon(1, 1, 3);
                }else{
                    msgBallonsUsr(1, 1, 3);
                }
                game.chamadas->envido = 0;
                game.chamadas->realEnvido = user;
            }else if(game.chamadas->envido2 == opp){
                if(user == 2){
                    msgBallon(1, 1, 3);
                }else{
                    msgBallonsUsr(1, 1, 3);
                }
                game.chamadas->envido2 = 0;
                game.chamadas->realEnvido = user;
            }
            game.chamadas->pontosNegarCantada = game.chamadas->pontosValendoCantada;
            game.chamadas->pontosValendoCantada += 3;
            break;
        case 3:
             if(game.chamadas->envido == opp){
                if(user == 2){
                    msgBallon(1, 1, 4);
                }else{
                    msgBallonsUsr(1, 1, 4);
                }
                game.chamadas->envido = 0;
                game.chamadas->faltaEnvido = user;
            }else if(game.chamadas->envido2 == opp){
                if(user == 2){
                    msgBallon(1, 1, 4);
                }else{
                    msgBallonsUsr(1, 1, 4);
                }
                game.chamadas->envido2 = 0;
                game.chamadas->faltaEnvido = user;
            }else if(game.chamadas->realEnvido == opp){
                if(user == 2){
                    msgBallon(1, 1, 4);
                }else{
                    msgBallonsUsr(1, 1, 4);
                }
                game.chamadas->realEnvido = 0;
                game.chamadas->faltaEnvido = user;
            }
            game.chamadas->pontosNegarCantada = game.chamadas->pontosValendoCantada;
            game.chamadas->pontosValendoCantada = 0;
            break;
    }
}

void AceitarEnvido(int user){
    printf("aceitarEnvido");
    if(user == 2){
        msgBallon(1, 0, 1);
    }else{
        msgBallonsUsr(1, 0, 1);
    }
    int p1 = game.cartas->pontosEnvido[0];
    int p2 = game.cartas->pontosEnvido[1];
    int winner = (p1 > p2) ? 1 : (p2 > p1) ? 2 : game.round->mao;
    if(winner == game.chamadas->primeiroEnvido){
        if(winner == 1){
            game.chamadas->p1FalarPontos = 1;
            game.chamadas->p2falarPontos = 0;
        }else {
            game.chamadas->p1FalarPontos = 0;
            game.chamadas->p2falarPontos = 1;
        }
    }else{
        game.chamadas->p1FalarPontos = 1;
        game.chamadas->p2falarPontos = 1;
    }
    if(game.chamadas->faltaEnvido){
        if(winner == 1){
            int points = 30 - game.opponentPoints;
            game.chamadas->pontosValendoCantada = points;
        }else{
            int points = 30 - game.userPoints;
            game.chamadas->pontosValendoCantada = points;
        }
    }
    if(game.chamadas->p1FalarPontos){
        double historic = (game.cartas->pontosEnvido[0])/33.0;
        game.calculo->fatorHistoricoPontos = (historic+game.calculo->fatorHistoricoPontos)/2.0;
    }
    game.chamadas->envidoAceito = 1;
    game.chamadas->cantado = 0;
    game.chamadas->envido = 0;
    game.chamadas->envido2 = 0;
    game.chamadas->realEnvido = 0;
    game.chamadas->faltaEnvido = 0;
    game.chamadas->envidoFeito = 1;
    game.chamadas->resultadoPopUpAux = 1;
    game.chamadas->mainButtons = 1;
    game.chamadas->envidoButtons = 0;
    game.chamadas->resultadoPopUpTimer = al_get_time();
    game.round->firstBotJogadaVerify = 1;
    game.round->timeBotJogadaVerify = 0.0;
    game.chamadas->respostaBot = 0;
}

void negarEnvido(int user){
    printf("negarEnvido");
    if(user == 1){
        game.opponentPoints += game.chamadas->pontosNegarCantada;
        msgBallonsUsr(1, 0, 2);
    }else{
        msgBallon(1, 0, 2);
        game.userPoints += game.chamadas->pontosNegarCantada;
    }
    game.chamadas->msgPopUpAuxUsr = 1;
    game.chamadas->msgPopUpAux = 1;
    game.chamadas->msgPopUpTimerUsr = al_get_time();
    game.chamadas->msgPopUpTimer = al_get_time();
    game.chamadas->cantado = 0;
    game.chamadas->envido = 0;
    game.chamadas->envido2 = 0;
    game.chamadas->realEnvido = 0;
    game.chamadas->faltaEnvido = 0;
    game.chamadas->envidoFeito = 1;
    game.chamadas->respostaBot = 0;
    game.chamadas->mainButtons = 1;
    game.chamadas->envidoButtons = 0;
    game.chamadas->pontosValendoCantada = 0;
    game.chamadas->pontosNegarCantada = 0;
    game.round->firstBotJogadaVerify = 1;
    game.round->timeBotJogadaVerify = 0.0;
    // end game verificar
}

void cantarFlor(int user, int tpye){
    printf("cantarFlor");
    if (game.chamadas->florFeita) return;
    if(user == 1){
        game.chamadas->florButtons = 0;
    }
    game.chamadas->envidoAceito = 0;
    int indxOpp = (user == 1) ? 1 : 0;

    if(game.chamadas->cantado == 0){
        if(game.cartas->cantarFlor[indxOpp] == 0){
            if(user == 1){
                msgBallonsUsr(3, 1, 1);
                game.chamadas->msgPopUpOnUsr  = 1;
                game.chamadas->msgPopUpAuxUsr = 1;
                game.chamadas->msgPopUpTimerUsr = al_get_time();
                game.userPoints += 3;
                game.chamadas->florFeita = 1;
            }else{
                msgBallon(3, 1, 1);
                game.chamadas->msgPopUpAux = 1;
                game.chamadas->msgPopUpTimer = al_get_time();
                game.chamadas->msgPopUpOn = 1;
                game.opponentPoints += 3;
                game.chamadas->florFeita = 1;
            }
        }else{
            game.chamadas->cantado = 1;
            if(user == 1){
                msgBallonsUsr(3, 1, 1);
                game.chamadas->flor = 1;
                game.chamadas->respostaBot = 1;
            }else{
                msgBallon(3, 1, 1);
                game.chamadas->flor = 2;
                game.chamadas->florButtons = 1;
                game.chamadas->aceitarPopUp = 1;
            }
        }
    }else if(game.chamadas->envido || game.chamadas->truco ){
        game.chamadas->envido = 0;
        game.chamadas->truco = 0;
        game.chamadas->trucoAux = 0;
        if(game.cartas->cantarFlor[indxOpp] == 0){
            if(user == 1){
                msgBallonsUsr(3, 1, 1);
                game.chamadas->msgPopUpOnUsr  = 1;
                game.chamadas->msgPopUpAuxUsr = 1;
                game.chamadas->msgPopUpTimerUsr = al_get_time();
                game.userPoints += 3;
                game.chamadas->florFeita = 1;
                game.chamadas->cantado = 0;
            }else{
                msgBallon(3, 1, 1);
                game.chamadas->msgPopUpAux = 1;
                game.chamadas->msgPopUpTimer = al_get_time();
                game.chamadas->msgPopUpOn = 1;
                game.opponentPoints += 3;
                game.chamadas->florFeita = 1;
                game.chamadas->cantado = 0;
            }
        }
    }else if(game.chamadas->flor){
        game.chamadas->cantado = 1;
        game.chamadas->flor = 0;
        if(user == 1){
            msgBallonsUsr(3, 1, 2);
            game.chamadas->contraFlor = 1;
            game.chamadas->respostaBot = 1;
        }else{
            msgBallon(3, 1, 2);
            game.chamadas->contraFlor = 2;
            game.chamadas->florButtons = 1;
            game.chamadas->aceitarPopUp = 1;
        }
    }else if(game.chamadas->contraFlor){
        game.chamadas->cantado = 1;
        game.chamadas->contraFlor = 0;
        if(user == 1){
            msgBallonsUsr(3, 1, 3);
            game.chamadas->contraFlorResto = 1;
            game.chamadas->respostaBot = 1;
        }else{
            msgBallon(3, 1, 3);
            game.chamadas->contraFlorResto = 2;
            game.chamadas->florButtons = 1;
            game.chamadas->aceitarPopUp = 1;
        }
    }
    game.chamadas->truco = 0;
    game.chamadas->envido = 0;
}

void negarFlor(int user){
    printf("negarFlor");
    if(game.chamadas->flor){
        if(user == 1){
            game.chamadas->msgPopUpOn = 0;
            msgBallonsUsr(1, 0, 2);
            game.opponentPoints += 3;
        }else{
            game.chamadas->msgPopUpOnUsr = 0;
            msgBallon(1, 0, 2);
            game.userPoints += 3;
        }
    }else if(game.chamadas->contraFlor){
        if(user == 1){
            game.chamadas->msgPopUpOn = 0;
            msgBallonsUsr(1, 0, 2);
            game.opponentPoints += 4;
        }else{
            game.chamadas->msgPopUpOnUsr = 0;
            msgBallon(1, 0, 2);
            game.userPoints += 4;
        }
    }else if(game.chamadas->contraFlorResto){
        if(user == 1){
            game.chamadas->msgPopUpOn = 0;
            msgBallonsUsr(1, 0, 2);
            game.opponentPoints += 6;
        }else{
            game.chamadas->msgPopUpOnUsr = 0;
            msgBallon(1, 0, 2);
            game.userPoints += 6;
        }
    }
    game.chamadas->flor = 0;
    game.chamadas->contraFlor = 0;
    game.chamadas->contraFlorResto = 0;
    game.chamadas->florButtons = 0;
    game.chamadas->florFeita = 1;
    game.chamadas->aceitarPopUp = 0;
    game.chamadas->trucoAux = 0;
}

void aceitarFlor(int user){
    printf("aaceitarFlor");
    // colocar os pontos no pontos envido mesmo
    int p1 = 20;
    int p2 = 20;
    for(int i = 0; i < 3; i ++){
        p1 += game.cartas->arrCartasUsr[i].envido;
    }
    for(int i = 0; i < 3; i ++){
        p2 += game.cartas->arrCartasOpp[i].envido;
    }
    game.cartas->pontosEnvido[0] = p1;
    game.cartas->pontosEnvido[1] = p2;
    if(user == 1){
        msgBallonsUsr(1, 0, 1);
    }else{
        msgBallon(1, 0, 1);
    }
    if(game.chamadas->flor){
        game.chamadas->pontosValendoCantada = 4;
    }else if(game.chamadas->contraFlor){
        game.chamadas->pontosValendoCantada = 6;
    }else if(game.chamadas->contraFlorResto){
        game.chamadas->pontosValendoCantada = 6;
    }
    game.chamadas->flor = 0;
    game.chamadas->contraFlor = 0;
    game.chamadas->contraFlorResto = 0;
    game.chamadas->florButtons = 0;
    game.chamadas->florFeita = 1;
    game.chamadas->aceitarPopUp = 0;
    game.chamadas->resultadoPopUpAux = 1;
    game.chamadas->resultadoPopUpTimer = al_get_time();
    game.chamadas->trucoAux = 0;
}

int botJogada(void){
    printf("botjogada");
    if(game.chamadas->respostaBot || game.chamadas->envido != 0 || game.chamadas->envido2 != 0 ||
    game.chamadas->realEnvido != 0 || game.chamadas->faltaEnvido != 0 || game.chamadas->trucoAux != 0) {
    return 0;
    }
    if(game.chamadas->resultadoPopUp == 1 || game.chamadas->resultadoPopUpAux == 1){
        game.round->firstBotJogadaVerify = 1;
        game.round->timeBotJogadaVerify = 0.0;
    }
    if(game.round->firstBotJogadaVerify == 1){
        game.round->firstBotJogadaVerify = 0;
        game.round->timeBotJogadaVerify = al_get_time();
        return 0;
    }
    if(al_get_time() - game.round->timeBotJogadaVerify >= 2.0 && game.chamadas->resultadoPopUp == 0 && game.chamadas->resultadoPopUpAux == 0){
        definirCalculoPontos();
        calcularCarta();
        calcularFlor();
        
        // envido
        if(game.round->cardsPlayed < 2 && game.chamadas->envidoFeito == 0 && game.chamadas->cantado == 0 && game.cartas->cantarFlor[1] == 0 && game.chamadas->florFeita == 0){
            if (game.calculo->forcaMaoBotPontos >= 0.8 && game.calculo->inversovalorChamadaPontos >= 0.85 && game.round->cardsPlayed == 0){
            }else{
                if(game.calculo->valorChamadaPontos >= 1.1){
                    game.round->firstBotJogadaVerify = 1;
                    game.round->timeBotJogadaVerify = 0.0;
                    cantarEnvido(2, 3);
                    return 1;

                }else if(game.calculo->valorChamadaPontos >= 0.8){
                    if(30 - game.opponentPoints <= 2){
                        cantarEnvido(2, 3);
                        return 1;
                    }
                    game.round->firstBotJogadaVerify = 1;
                    game.round->timeBotJogadaVerify = 0.0;
                    cantarEnvido(2, 2);
                    return 1;

                }else if(game.calculo->valorChamadaPontos >= 0.4){
                    if(30 - game.opponentPoints <= 2){
                        cantarEnvido(2, 3);
                        return 1;
                    }
                    game.round->firstBotJogadaVerify = 1;
                    game.round->timeBotJogadaVerify = 0.0;
                    cantarEnvido(2, 1);
                    return 1;
                }
            }
        }
        // flor
        int oppCardsPlayed = 0;
        for(int i = 0; i<6; i++){
            if(game.cartas->cartasJogadas[i][0] == 2){
                oppCardsPlayed++;
            }
        }
        if(oppCardsPlayed == 0 && game.cartas->cantarFlor[1] == 1 && game.round->cardsPlayed < 2 && game.chamadas->envidoFeito == 0 && game.chamadas->flor==0 && game.chamadas->florFeita==0 && (game.chamadas->cantado == 0 || game.chamadas->truco == 1 || game.chamadas->envido == 1)){
            game.round->firstBotJogadaVerify = 1;
            game.round->timeBotJogadaVerify = 0.0;
            cantarFlor(2, 1);
            return 1;
        }

        // decisao truco
        if(game.chamadas->valeQuatro == 0){
            if(game.chamadas->cantado == 0 || game.chamadas->trucoAux == 1){
                if(game.calculo->forcaMaoTruco <= 0.4 && game.calculo->blefeTruco >= 0.8){
                    if(game.chamadas->cantado == 0){
                        if(game.calculo->blefeTruco >= 0.7){
                            game.round->firstBotJogadaVerify = 1;
                            game.round->timeBotJogadaVerify = 0.0;
                            cantarTruco(2, 1);
                            return 1;
                        }
                    }else if(game.chamadas->truco == 1){
                        if(game.calculo->blefeTruco >= 0.88){
                            game.round->firstBotJogadaVerify = 1;
                            game.round->timeBotJogadaVerify = 0.0;
                            cantarTruco(2, 2);
                            return 1;
                        }
                    }else if(game.chamadas->retruco == 1){
                        if(game.calculo->blefeTruco >= 1.05){
                            game.round->firstBotJogadaVerify = 1;
                            game.round->timeBotJogadaVerify = 0.0;
                            cantarTruco(2, 3);
                            return 1;
                        }
                    }
                }else if(game.calculo->forcaMaoTruco >= 0.75 && game.calculo->blefeInversoTruco >= 0.85){
                }else{
                    if(game.chamadas->cantado == 0){
                        if(game.calculo->cantarTruco >= 0.65){
                            game.round->firstBotJogadaVerify = 1;
                            game.round->timeBotJogadaVerify = 0.0;
                            cantarTruco(2, 1);
                            return 1;
                        }
                    }else if(game.chamadas->truco == 1){
                        if(game.calculo->cantarTruco >= 0.8){
                            game.round->firstBotJogadaVerify = 1;
                            game.round->timeBotJogadaVerify = 0.0;
                            cantarTruco(2, 2);
                            return 1;
                        }
                    }else if(game.chamadas->retruco == 1){
                        if(game.calculo->cantarTruco >= 0.95){
                            game.round->firstBotJogadaVerify = 1;
                            game.round->timeBotJogadaVerify = 0.0;
                            cantarTruco(2, 3);
                            return 1;
                        }
                    }
                }
            }
        }
        if(game.round->cardsPlayed % 2 == 0){
            int matrizAux[1][2] = {{-10, -1}}; // valor, index
            for(int i = 0; i < 3; i++){
                if(game.cartas->arrCartasOpp[i].out == 0){
                    if(matrizAux[0][0] < game.calculo->cartasParaJogar[i]){
                        matrizAux[0][0] = game.calculo->cartasParaJogar[i];
                        matrizAux[0][1] = i;
                    }
                }
            }
            if(game.chamadas->cantado == 0 || (game.chamadas->cantado == 1 && game.chamadas->trucoAux == 0 && game.chamadas->envido == 0 && game.chamadas->envido2 == 0 && game.chamadas->realEnvido == 0 && game.chamadas->faltaEnvido == 0 && game.chamadas->flor == 0 && game.chamadas->contraFlor == 0 && game.chamadas->contraFlorResto == 0)){
                jogarCarta(2, matrizAux[0][1]);
                game.round->firstBotJogadaVerify = 1;
                game.round->timeBotJogadaVerify = 0.0;
                return 1;
            }
        }else{
            int cartaUsrIndex = game.cartas->cartasJogadas[game.round->cardsPlayed - 1][1];
            int cartaUsrPower = game.cartas->arrCartasUsr[cartaUsrIndex].power;
            
            int menorPower = 999;
            int indexMenor = -1;
            int menorMatadora = 999;
            int indexMatadora = -1;
            
            for(int i = 0; i < 3; i++){
                if(game.cartas->arrCartasOpp[i].out == 0){
                    int power = game.cartas->arrCartasOpp[i].power;
            
                    if(power < menorPower){
                        menorPower = power;
                        indexMenor = i;
                    }
                    if(power > cartaUsrPower && power < menorMatadora){
                        menorMatadora = power;
                        indexMatadora = i;
                    }
                }
            }

            int decisivo = 0;
            int r1 = game.round->roundsWon[0];
            int r2 = game.round->roundsWon[1];
            int rodadaAtual = game.round->cardsPlayed / 2;
            
            if(rodadaAtual == 2){
                if((r1 == 1 && r2 == 2) || (r1 == 2 && r2 == 1) || r1 == 3 || r2 == 3){
                    decisivo = 1;
                }
            }
            
            if(indexMatadora != -1){
                jogarCarta(2, indexMatadora);
            } else if(decisivo){
                game.round->alMazo2 = 1;
                msgBallon(4, 1, 1);
            } else {
                jogarCarta(2, indexMenor);
            }
        }
        
    }
    return 0;
}

void verificarCantadas(void){
    printf("verificarCantada");
    if(game.chamadas->resultadoPopUp == 1 || game.chamadas->resultadoPopUpAux == 1){
        game.round->firstBotJogadaVerify = 1;
    }
    if(game.chamadas->respostaBot){
        if(game.chamadas->firstChamada == 1){
            game.chamadas->firstChamada = 0;
            game.chamadas->timeFirstChamada = al_get_time();
            return;
        }else if(al_get_time() - game.chamadas->timeFirstChamada >= 2.5){
            definirCalculoPontos();
            calcularCarta();
            calcularFlor();
            // flor
            
            int oppCardsPlayed = 0;
            for(int i = 0; i<6; i++){
                if(game.cartas->cartasJogadas[i][0] == 2){
                    oppCardsPlayed++;
                }
            }   

            if(game.cartas->cantarFlor[1] == 1 && oppCardsPlayed == 0){
                if(game.chamadas->flor == 1){
                    if(game.userPoints + 3 >= 30){
                        cantarFlor(2, 2);
                    }else{
                        if(game.calculo->forcaFlor <= 0.4 && game.calculo->responderFlorBlefe >= 0.95){
                            cantarFlor(2, 2);
                        }else{
                            if(game.calculo->responderFlor >= 0.75){
                                cantarFlor(2, 2);
                            }else if(game.calculo->responderFlor >= 0.75){
                                aceitarFlor(2);
                            }else{
                                negarFlor(2);
                            }
                        }
                    }
                }else if(game.chamadas->contraFlor == 1){
                    if(game.userPoints + 4 >= 30){
                        cantarFlor(2, 2);
                    }else{
                        if(game.calculo->forcaFlor <= 0.4 && game.calculo->responderFlorBlefe >= 1.10){
                            cantarFlor(2, 3);
                        }else{
                            if(game.calculo->responderFlor >= 1.10){
                                cantarFlor(2, 3);
                            }else if(game.calculo->responderFlor >= 0.90){
                                aceitarFlor(2);
                            }else{
                                negarFlor(2);
                            }
                        }
                    }
                }else if(game.chamadas->contraFlorResto == 1){
                    if(game.calculo->responderFlor >= 1.10){
                        aceitarFlor(2);
                    }else{
                        negarFlor(2);
                    } 
                }
            }

            // envido
            if((game.chamadas->envido == 1 && game.cartas->cantarFlor[1] == 0)){
                game.chamadas->truco = 0;
                if(30 - game.userPoints <= game.chamadas->pontosNegarCantada){
                    if(30 - game.userPoints >= game.chamadas->pontosValendoCantada + 3){
                        cantarEnvido(2, 3);
                    }else{
                        cantarEnvido(2, 2); 
                    }
                }
                if (game.calculo->forcaMaoBotPontos <= 0.4 && game.calculo->inversovalorRespostaPontos >= 1.15){
                    cantarEnvido(2, 3);
                }else if(game.calculo->forcaMaoBotPontos <= 0.4 && game.calculo->inversovalorRespostaPontos >= 0.98){
                    cantarEnvido(2, 2);
                }else if(game.calculo->forcaMaoBotPontos <= 0.4 && game.calculo->inversovalorRespostaPontos >= 0.9){
                    cantarEnvido(2, 1);
                }
                else if (game.calculo->valorRespostaPontos >= 0.9) {
                    cantarEnvido(2, 3);
                } else if (game.calculo->valorRespostaPontos >= 0.85) {
                    cantarEnvido(2, 2);
                } else if (game.calculo->valorRespostaPontos >= 0.7) {
                    cantarEnvido(2, 1);
                } else if (game.calculo->valorRespostaPontos >= 0.5) {
                    AceitarEnvido(2);
                } else {
                    negarEnvido(2);
                }
            }else if(game.chamadas->envido2 == 1){
                if(30 - game.opponentPoints <= game.chamadas->pontosNegarCantada){
                    if(30 - game.userPoints >= game.chamadas->pontosValendoCantada + 3){
                        cantarEnvido(2, 3);
                    }else{
                         cantarEnvido(2, 2); 
                    }
                }
                if (game.calculo->forcaMaoBotPontos <= 0.4 && game.calculo->inversovalorRespostaPontos >= 0.9){
                    cantarEnvido(2, 3);
                }else if(game.calculo->forcaMaoBotPontos <= 0.4 && game.calculo->inversovalorRespostaPontos >= 0.75){
                    cantarEnvido(2, 2);
                }
                else if (game.calculo->valorRespostaPontos >= 0.9) {
                    cantarEnvido(2, 3);
                } else if (game.calculo->valorRespostaPontos >= 0.75) {
                    cantarEnvido(2, 2);
                }else if (game.calculo->valorRespostaPontos >= 0.6) {
                    AceitarEnvido(2);
                } else {
                    negarEnvido(2);
                }
            }else if(game.chamadas->realEnvido == 1){
                if(30 - game.opponentPoints <= game.chamadas->pontosNegarCantada){
                    if(30 - game.userPoints >= game.chamadas->pontosValendoCantada + 3){
                        cantarEnvido(2, 3);
                    }
                }
                else if (game.calculo->forcaMaoBotPontos <= 0.4 && game.calculo->inversovalorRespostaPontos >= 0.90){
                    cantarEnvido(2, 3);
                }
                else if (game.calculo->valorRespostaPontos >= 0.9) {
                    cantarEnvido(2, 3);
                } else if (game.calculo->valorRespostaPontos >= 0.83) {
                    AceitarEnvido(2);
                } else {
                    negarEnvido(2);
                }
            }else if(game.chamadas->faltaEnvido == 1){
                double lim = 0.9;
                if(30 - game.userPoints <= game.chamadas->pontosNegarCantada){
                    lim= 0.0;
                }else if(30 - game.userPoints - game.chamadas->pontosNegarCantada <= 3){
                    lim = 0.7;
                }
                else if (game.calculo->valorRespostaPontos >= lim) {
                    AceitarEnvido(2);
                }else {
                    negarEnvido(2);
                }
            }
            // truco
            if(game.chamadas->truco == 1){
                if(game.calculo->forcaMaoTruco <= 0.4 && game.calculo->blefeTruco >= 0.88) {
                    cantarTruco(2, 2);      
                }else{
                    if(game.calculo->cantarTruco >= 0.8){
                        cantarTruco(2, 2);
                    }else if(game.calculo->cantarTruco >= 0.65){
                        aceitarTruco(2);
                    }else{
                        negarTruco(2);
                    }
                }
            }else if(game.chamadas->retruco == 1){
                if(game.calculo->forcaMaoTruco <= 0.4 && game.calculo->blefeTruco >= 1.0){
                    cantarTruco(2, 3);
                }else{
                    if(game.calculo->cantarTruco >= 1.05){
                        cantarTruco(2, 3);
                    }else if(game.calculo->cantarTruco >= 0.95){
                        aceitarTruco(2);
                    }else{
                        negarTruco(2);
                    }
                }
            }else if(game.chamadas->valeQuatro == 1){ 
                if(game.calculo->cantarTruco >= 1.05){
                    aceitarTruco(2);  
                }else{
                    negarTruco(2);
                }
            }
                
            
            game.chamadas->firstChamada = 1;
            game.chamadas->timeFirstChamada = 0.0;
        }
    }
}

void mainGameLoop(){
    srand(time(NULL));

    ALLEGRO_FONT *font = al_load_ttf_font("fonts/retro.ttf",30*scale,0);
    ALLEGRO_FONT *font2 = al_load_ttf_font("fonts/retro.ttf",25*scale,0);
    ALLEGRO_FONT *font3 = al_load_ttf_font("fonts/retro.ttf",20*scale,0);

    Animations animations = {0, 0, {x1, x2, x3, yUsr, yOpp, yUsrTable, yOppTable}, {x1, yUsr, x2, yUsr, x3, yUsr, x1, yOpp, x2, yOpp, x3, yOpp}};
    Round round = {0, 0, 0, 1, 1, 0, 1, 1, 0, 1, 0,{0}, jogarCarta};
    carregar_baralho(baralho);

    images imagens = {al_load_bitmap("images/fosforo.png"), al_load_bitmap("images/cards/reverso.png"), al_load_bitmap("images/mesa.jpg"), al_load_bitmap("images/nuvem.png")};
    
    Calculo calculo = {0};
    Cards cartas;
    memset(&cartas, 0, sizeof(Cards));
    Chamadas chamadas = {0};
    chamadas.mainButtons = 1;
    chamadas.firstChamada = 1;
    

    game.maxPoints = 30;
    game.opponentPoints = 0;
    game.userPoints = 0;
    game.imagens = imagens;
    game.cartas = &cartas;
    game.animations = &animations;
    game.gameRounds = 0;
    game.round = &round;
    game.chamadas = &chamadas;
    game.calculo = &calculo;
    game.chamadas->cartasNaMesaVerify = 0;

    chooseCards(0);

    verificarFlor();
    verificarEnvidoPontos();

    ALLEGRO_BITMAP* menu_snapshot = NULL;

    menu_snapshot = al_create_bitmap(larguraEscolhida, alturaEscolhida); // tirar print da tela (para a transicao)
    al_set_target_bitmap(menu_snapshot);
    drawn6(game, font, font2, font3);
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
            if(game.opponentPoints >= 30 || game.userPoints >= 30){
                venceu = 1;
                break;
            }
            if(toMenu1 || exitGame || newRes) break;
            if(restartGame && animReady){
                restartGame = 0;
                mainGameLoop();
                break;
            }
            if(animReady){
                drawn6(game, font, font2, font3);
            }else{
                animationTransition(&animReady, menu_snapshot, &firstExec, &animationP1, &animationPaused, &timePaused, &auxEnd, &auxEnd2, grupoAy1, grupoAy2);
                if(firstExec){
                    firstExec = 0;
                }
            }
        }
        al_wait_for_event(event_queue, &event);
        if(event.type == ALLEGRO_EVENT_TIMER){
            if(game.chamadas->respostaBot) {
                verificarCantadas();
            }
        if(game.round->usrTurn == 2 && game.round->firstRoundEndVerify == 1) {
            botJogada();
        }if((game.chamadas->envidoAux == 0) && game.round->firstRoundEndVerify == 0){
                verificarTurno();
            }
            if(game.round->alMazo){
                endRound(2);
            }
            if(game.round->alMazo2){
                endRound(1);
            }
            if(game.round->trucoNegado){
                endRound((game.round->trucoNegado == 2) ? 1 : 2);
            }
            if(game.chamadas->msgPopUpAux == 1){
                if(al_get_time() - game.chamadas->msgPopUpTimer >= 3.5){
                    game.chamadas->msgPopUpAux = 0;
                    game.chamadas->msgPopUpTimer = 0.0;
                    game.chamadas->msgPopUpOn = 0;
                }
            }
            if(game.chamadas->msgPopUpAuxUsr == 1){
                if(al_get_time() - game.chamadas->msgPopUpTimerUsr >= 3.5){
                    game.chamadas->msgPopUpAuxUsr = 0;
                    game.chamadas->msgPopUpTimerUsr = 0.0;
                    game.chamadas->msgPopUpOnUsr = 0;
                }
            }
            if(game.chamadas->resultadoPopUpAux == 1){
                if(al_get_time() - game.chamadas->resultadoPopUpTimer >= 2.5){
                    game.chamadas->resultadoPopUpAux = 0;
                    game.chamadas->resultadoPopUp = 1;
                    game.chamadas->resultadoPopUpTimer = 0.0;
                }
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
                drawn6(game, font, font2, font3);
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
                if(game.round->firstRoundEndVerify == 1 && game.chamadas->resultadoPopUp == 0 && game.chamadas->resultadoPopUpAux == 0){  
                    if(mouse_y >= yUsr && mouse_y <= yUsr + (180*scale) && game.round->usrTurn == 1 &&
                    game.chamadas->resultadoPopUp == 0 && game.chamadas->resultadoPopUpAux == 0 &&
                    game.chamadas->respostaBot == 0 && ((game.chamadas->envido == 0 && game.chamadas->envido2 == 0 &&
                    game.chamadas->realEnvido == 0 && game.chamadas->faltaEnvido == 0 &&
                    game.chamadas->trucoAux == 0)))
                    {                        
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
                    
                    int xRect = (larguraEscolhida / 2 - (118 * scale) * 2 - (30 * scale) - (20 * scale));
                    int botao_largura = ((xRect - (20 * scale)) / 2) - (10 * scale);
                    int botao_altura = 50 * scale;
        
                    int bt1_x1 = (20 * scale);
                    int bt1_y1 = alturaEscolhida - (130 * scale);
                    int bt1_x2 = bt1_x1 + botao_largura;
                    int bt1_y2 = bt1_y1 + botao_altura;

                    int bt2_x1 = ((xRect + (20 * scale)) / 2) + (10 * scale);
                    int bt2_y1 = alturaEscolhida - (130 * scale);
                    int bt2_x2 = bt2_x1 + botao_largura;
                    int bt2_y2 = bt2_y1 + botao_altura;

                    int bt3_x1 = (20 * scale);
                    int bt3_y1 = alturaEscolhida - (70 * scale);
                    int bt3_x2 = bt3_x1 + botao_largura;
                    int bt3_y2 = bt3_y1 + botao_altura;

                    int bt4_x1 = ((xRect + (20 * scale)) / 2) + (10 * scale);
                    int bt4_y1 = alturaEscolhida - (70 * scale);
                    int bt4_x2 = bt4_x1 + botao_largura;
                    int bt4_y2 = bt4_y1 + botao_altura;

                    int botao_largura_q = 150 * scale;
                    int botao_altura_q = 50 * scale;
                    int y_botao_q = alturaEscolhida - botao_altura_q;
                    int x_centro_tela_q = larguraEscolhida / 2;

                    int x1_quero = x_centro_tela_q - botao_largura_q;
                    int x2_quero = x_centro_tela_q;

                    int x1_naoquero = x_centro_tela_q;
                    int x2_naoquero = x_centro_tela_q + botao_largura_q;

                    if(game.chamadas->aceitarPopUp && game.chamadas->cantado == 1 && (game.chamadas->envido == 2 || game.chamadas->envido2 == 2 || game.chamadas->realEnvido == 2 || game.chamadas->faltaEnvido == 2)){
                        if (mouse_x >= x1_quero && mouse_x <= x2_quero && mouse_y >= y_botao_q && mouse_y <= alturaEscolhida) {
                            AceitarEnvido(1);
                            game.chamadas->aceitarPopUp = 0;
                        }

                        if (mouse_x >= x1_naoquero && mouse_x <= x2_naoquero && mouse_y >= y_botao_q && mouse_y <= alturaEscolhida) {
                            negarEnvido(1);
                            game.chamadas->aceitarPopUp = 0;
                            
                        }
                    }

                    if(game.chamadas->aceitarPopUp && game.chamadas->cantado == 1 && game.chamadas->trucoAux == 2 && (game.chamadas->truco == 2 || game.chamadas->retruco == 2 || game.chamadas->valeQuatro == 2)){
                        if (mouse_x >= x1_quero && mouse_x <= x2_quero && mouse_y >= y_botao_q && mouse_y <= alturaEscolhida) {
                            aceitarTruco(1);
                            game.chamadas->aceitarPopUp = 0;
                            game.chamadas->trucoButtons = 0;
                        }

                        if (mouse_x >= x1_naoquero && mouse_x <= x2_naoquero && mouse_y >= y_botao_q && mouse_y <= alturaEscolhida) {
                            negarTruco(1);
                            game.chamadas->aceitarPopUp = 0;
                            game.chamadas->trucoButtons = 0;
                        }
                    }

                    if(game.chamadas->aceitarPopUp && game.chamadas->cantado == 1 && (game.chamadas->flor == 2 ||game.chamadas->contraFlor == 2 || game.chamadas->contraFlorResto == 2)){
                        if (mouse_x >= x1_quero && mouse_x <= x2_quero && mouse_y >= y_botao_q && mouse_y <= alturaEscolhida) {
                            aceitarFlor(1);
                            game.chamadas->aceitarPopUp = 0;
                            game.chamadas->florButtons = 0;
                        }

                        if (mouse_x >= x1_naoquero && mouse_x <= x2_naoquero && mouse_y >= y_botao_q && mouse_y <= alturaEscolhida) {
                            negarTruco(1);
                            game.chamadas->aceitarPopUp = 0;
                            game.chamadas->florButtons = 0;
                        }
                    }

                    int botao_largura2 = 150 * scale;
                    int botao_altura2 = 50 * scale;
                    int largura_total = botao_largura2 * 2;
                    int altura_botao = 45 * scale;
                    int xTruco = (larguraEscolhida - largura_total) / 2;
                    int yTruco = alturaEscolhida - botao_altura2 - altura_botao;

                    if(mouse_x >= xTruco && mouse_x <= xTruco + largura_total && mouse_y >= yTruco && mouse_y <= yTruco + altura_botao){
                        if(game.chamadas->trucoButtons){
                            if(game.chamadas->truco == 2){
                                cantarTruco(1, 2);
                            }else if(game.chamadas->retruco == 2){
                                cantarTruco(1, 3);
                            }
                        }else if(game.chamadas->florButtons){
                            if(game.chamadas->envido == 2 || game.chamadas->truco == 2){
                                cantarFlor(1, 1);
                            }else if(game.chamadas->flor == 2){
                                cantarFlor(1, 2);
                            }else if(game.chamadas->contraFlor){
                                cantarFlor(1, 3);
                            }
                        }
                    }

                    if(game.chamadas->mainButtons == 1){
                        if(mouse_x >= bt1_x1 && mouse_x <= bt1_x2 && mouse_y >= bt1_y1 && mouse_y <= bt1_y2 ) {
                            if(game.chamadas->valeQuatro == 0 && game.round->usrTurn == 1 && game.chamadas->flor == 0 && game.chamadas->contraFlor == 0 && game.chamadas->contraFlorResto == 0 && (game.chamadas->truco == 2 || game.chamadas->retruco == 2 || game.chamadas->cantado == 0)){
                                if(game.chamadas->cantado == 0){
                                    cantarTruco(1, 1);
                                }else if(game.chamadas->truco == 2){
                                    cantarTruco(1, 2);
                                }else if(game.chamadas->retruco == 2){
                                    cantarTruco(1, 3);
                                }
                            }
                            
                        }
                        
                        else if(mouse_x >= bt2_x1 && mouse_x <= bt2_x2 && mouse_y >= bt2_y1 && mouse_y <= bt2_y2 && game.chamadas->flor == 0 && game.chamadas->florFeita == 0 && game.chamadas->contraFlor == 0 && game.chamadas->contraFlorResto == 0 && ((game.chamadas->cantado == 0 && game.chamadas->envidoFeito == 0 && game.round->usrTurn == 1 && game.round->cardsPlayed< 2) || (game.chamadas->cantado == 1 && game.chamadas->trucoAux == 2 && game.round->cardsPlayed < 2 && game.chamadas->truco == 2 && game.chamadas->envidoFeito == 0))){
                            game.chamadas->envidoButtons = 1;
                            game.chamadas->mainButtons = 0;
                            continue;
                        }
            
                        else if(mouse_x >= bt3_x1 && mouse_x <= bt3_x2 && mouse_y >= bt3_y1 && mouse_y <= bt3_y2 && game.cartas->cantarFlor[0] == 1 && game.round->usrTurn == 1 && game.round->cardsPlayed < 2 && game.chamadas->florFeita == 0 && (game.chamadas->cantado == 0 || (game.chamadas->cantado == 1 && (game.chamadas->flor == 2 || game.chamadas->contraFlor == 2)))){
                            if(game.chamadas->cantado == 0){
                                cantarFlor(1, 1);
                            }else if(game.chamadas->flor == 2){
                                cantarFlor(1, 2);
                            }else if(game.chamadas->contraFlor == 2){
                                cantarFlor(1, 3);
                            }
                        }

                        else if(mouse_x >= bt4_x1 && mouse_x <= bt4_x2 && mouse_y >= bt4_y1 && mouse_y <= bt4_y2 && game.round->usrTurn == 1 && game.chamadas->trucoAux == 0 && game.chamadas->flor == 0 && game.chamadas->contraFlor == 0 && game.chamadas->contraFlorResto == 0){
                            if(game.round->cardsPlayed == 0 && (game.chamadas->truco == 0 && game.chamadas->retruco == 0 && game.chamadas->valeQuatro == 0)){
                                game.round->pointsRound = 2;
                                game.round->alMazo = 1;
                                msgBallonsUsr(4, 1, 1);
                                endRound(2);
                            }else{
                                game.round->alMazo = 1;
                                game.round->pointsRound = game.round->pointsRound;
                                msgBallonsUsr(4, 1, 1);
                                endRound(2);
                            }
                        }
                    }  
                    if(game.chamadas->envidoButtons == 1 && game.chamadas->flor == 0 && game.chamadas->florFeita == 0 && game.chamadas->contraFlor == 0 && game.chamadas->contraFlorResto == 0 && ((game.chamadas->cantado == 0 && game.chamadas->envidoFeito == 0 && game.round->usrTurn == 1  && game.round->cardsPlayed< 2) || (game.chamadas->cantado == 1 && game.chamadas->trucoAux == 2 && game.round->cardsPlayed < 2 && game.chamadas->truco == 2 && game.chamadas->envidoFeito == 0) || (game.chamadas->envido == 2 || game.chamadas->envido2 == 2 || game.chamadas->realEnvido == 2 || game.chamadas->faltaEnvido == 2))){
                        if(game.chamadas->cantado == 1 && game.chamadas->trucoAux == 1 && game.round->cardsPlayed == 0 && game.chamadas->truco == 2){
                            game.chamadas->trucoAux = 0;
                            game.chamadas->cantado = 0;
                            game.chamadas->truco = 0;
                        }
                        
                        if(mouse_x >= bt1_x1 && mouse_x <= bt1_x2 && mouse_y >= bt1_y1 && mouse_y <= bt1_y2 && (game.chamadas->envido == 2 || game.chamadas->cantado == 0 || game.chamadas->truco == 2)) {
                            cantarEnvido(1, 1);
                        }
                        
                        else if(mouse_x >= bt2_x1 && mouse_x <= bt2_x2 && mouse_y >= bt2_y1 && mouse_y <= bt2_y2 && (game.chamadas->envido == 2 || game.chamadas->envido2 == 2 || game.chamadas->cantado == 0 || game.chamadas->truco == 2)) {
                            cantarEnvido(1, 2);
                        }
            
                        else if(mouse_x >= bt3_x1 && mouse_x <= bt3_x2 && mouse_y >= bt3_y1 && mouse_y <= bt3_y2 && (game.chamadas->envido == 2 || game.chamadas->envido2 == 2 || game.chamadas->realEnvido == 2 || game.chamadas->cantado == 0 || game.chamadas->truco == 2)) {
                            cantarEnvido(1, 3);
                        }
                    
                        else if(mouse_x >= bt4_x1 && mouse_x <= bt4_x2 && mouse_y >= bt4_y1 && mouse_y <= bt4_y2) {
                            if(!game.chamadas->cantado){
                                game.chamadas->envidoButtons = 0;
                                game.chamadas->mainButtons = 1;
                            }
                        }
                    } 
                }if(game.round->firstRoundEndVerify == 1 && game.chamadas->resultadoPopUp == 1){
                    float larguraRet = 400 * scale;
                    float alturaRet = 200 * scale;
                    float xRet = (larguraEscolhida - larguraRet) / 2;
                    float yRet = (alturaEscolhida - alturaRet) / 2;
                    float larguraBotao = 80 * scale;
                    float alturaBotao = 40 * scale;
                    float xBotao = xRet + (larguraRet / 2) - (larguraBotao / 2);
                    float yBotao = yRet + alturaRet + (15 * scale);
                    if(mouse_x >= xBotao && mouse_x <= xBotao + larguraBotao && mouse_y >= yBotao && mouse_y <= yBotao + alturaBotao){
                        game.chamadas->resultadoPopUp = 0;
                        game.chamadas->msgPopUpOn = 0;
                        game.chamadas->msgPopUpOnUsr = 0;
                        game.chamadas->aceitarPopUp = 0;
                        game.chamadas->mainButtons = 1;
                        game.chamadas->envidoButtons = 0;
                        game.chamadas->florButtons = 0;
                        game.chamadas->flor = 0;
                        game.chamadas->contraFlor = 0;
                        game.chamadas->contraFlorResto = 0;
                        int p1 = game.cartas->pontosEnvido[0];
                        int p2 = game.cartas->pontosEnvido[1];
                        int winner = (p1 > p2) ? 1 : (p2 > p1) ? 2 : game.round->mao;
                        if(winner == 1){
                            game.userPoints += game.chamadas->pontosValendoCantada;
                        }else{ 
                            game.opponentPoints += game.chamadas->pontosValendoCantada;
                        }
                        game.chamadas->pontosValendoCantada = 0;
                        game.chamadas->pontosNegarCantada = 0;
                    // verify game (se passou de 30 end game)
                    }
                }
            }
        }
    }
    if(venceu == 1){
        venceuMenu(1);
    }else if(perdeu == 1){
        venceuMenu(2);
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