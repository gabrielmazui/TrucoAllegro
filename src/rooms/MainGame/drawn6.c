#include <stdio.h>
#include <allegro5/allegro5.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <string.h>
#include "..\..\..\config\config.h"

void drawn6(Game game, ALLEGRO_FONT *font, ALLEGRO_FONT *font2, ALLEGRO_FONT *font3){
    Carta card1 = game.cartas->arrCartasUsr[0];
    Carta card2 = game.cartas->arrCartasUsr[1];
    Carta card3 = game.cartas->arrCartasUsr[2];

    Carta OPcard1 = game.cartas->arrCartasOpp[0];
    Carta OPcard2 = game.cartas->arrCartasOpp[1];
    Carta OPcard3 = game.cartas->arrCartasOpp[2];

    ALLEGRO_BITMAP * fosforo = game.imagens.fosforo;
    ALLEGRO_BITMAP * mesa = game.imagens.mesa;
    ALLEGRO_BITMAP * reverso = game.imagens.reverso;

    ALLEGRO_COLOR branco = al_map_rgb(255, 255, 255);
    ALLEGRO_COLOR amarelo = al_map_rgb(255,229,32);
    ALLEGRO_COLOR cinza = al_map_rgb(180,180,180);

    ALLEGRO_COLOR usuarioBorda;
    ALLEGRO_COLOR oponenteBorda;

    if(game.round->firstRoundEndVerify == 1){
        if(game.chamadas->cantado == 0){
            if(game.round->usrTurn == 1){
                usuarioBorda = amarelo;
                oponenteBorda = branco;
            }else{
                usuarioBorda = branco;
                oponenteBorda = amarelo;
            }
        }else{
            if(game.chamadas->envido == 2 || game.chamadas->envido2 == 2 || game.chamadas->realEnvido == 2 || game.chamadas->faltaEnvido == 2 || game.chamadas->truco == 2 || game.chamadas->retruco == 2 || game.chamadas->valeQuatro == 2){
                usuarioBorda = amarelo;
                oponenteBorda = branco;
            }else{
                usuarioBorda = branco;
                oponenteBorda = amarelo;
            }
        }
    }else{
        usuarioBorda = branco;
        oponenteBorda = branco;
    }

    al_draw_tinted_scaled_bitmap(background, al_map_rgb(255, 255, 255), 0, 0, larguraB, alturaB, 0, 0, larguraEscolhida, alturaEscolhida, 0);
    al_draw_scaled_bitmap(opponent.pfp, 0, 0, al_get_bitmap_width(opponent.pfp), al_get_bitmap_height(opponent.pfp), larguraEscolhida - (150*scale) - (100*scale), (50*scale), 150*scale, 150*scale, 0);
    al_draw_rectangle(larguraEscolhida - (150*scale) - (100 * scale), (50*scale), larguraEscolhida - (100 * scale), (50*scale) + (150*scale) ,oponenteBorda, 3*scale);
    
    al_draw_scaled_bitmap(user.pfp, 0, 0, al_get_bitmap_width(user.pfp), al_get_bitmap_height(user.pfp), larguraEscolhida - (150*scale) - (100*scale), alturaEscolhida - (150*scale) - (50*scale), 150*scale, 150*scale, 0);
    al_draw_rectangle(larguraEscolhida - (150*scale) - (100 * scale), alturaEscolhida - (150*scale) - (50*scale), larguraEscolhida - (100 * scale), alturaEscolhida - (50*scale),usuarioBorda, 3*scale);

    al_draw_scaled_bitmap(mesa, 0, 0, al_get_bitmap_width(mesa), al_get_bitmap_height(mesa), larguraEscolhida/2 - (118*scale)*2 - (30*scale), alturaEscolhida/2 - (306*scale)/2, 470*scale, 285*scale, 0);
    al_draw_rectangle(larguraEscolhida/2 - (118*scale)*2 - (30*scale), alturaEscolhida/2 - (306*scale)/2, larguraEscolhida/2 - (118*scale)*2 - (30*scale) + (470*scale), alturaEscolhida/2 - (306*scale)/2 + (285*scale), al_map_rgb(0, 0, 0), (float)2*scale);
    
    int fontHeight = al_get_font_line_height(font);
    al_draw_text(font, usuarioBorda, larguraEscolhida - (150*scale) - (100*scale) + (150*scale)/2, alturaEscolhida - (150*scale) - (50*scale) - (10*scale) - fontHeight, ALLEGRO_ALIGN_CENTRE, user.name);
    al_draw_text(font, oponenteBorda, larguraEscolhida - (150*scale) - (100*scale)+ (150*scale)/2, (50*scale) + (150*scale) + (10*scale), ALLEGRO_ALIGN_CENTRE, opponent.name);
    
    int xCard1 = game.animations->cords[0];
    int yCard1 = game.animations->cords[1];

    int xCard2 = game.animations->cords[2];
    int yCard2 = game.animations->cords[3];

    int xCard3 = game.animations->cords[4];
    int yCard3 = game.animations->cords[5];

    int xOppCard1 = game.animations->cords[6];
    int yOppCard1 = game.animations->cords[7];

    int xOppCard2 = game.animations->cords[8];
    int yOppCard2 = game.animations->cords[9];

    int xOppCard3 = game.animations->cords[10];
    int yOppCard3 = game.animations->cords[11];

    if(!card1.out){
        al_draw_scaled_bitmap(card1.img, 0, 0, al_get_bitmap_width(card1.img), al_get_bitmap_height(card1.img), xCard1, yCard1, 118*scale, 180*scale, 0);
    }
    if(!card2.out){
        al_draw_scaled_bitmap(card2.img, 0, 0, al_get_bitmap_width(card2.img), al_get_bitmap_height(card2.img), xCard2, yCard2, 118*scale, 180*scale, 0);
    }
    if(!card3.out){
        al_draw_scaled_bitmap(card3.img, 0, 0, al_get_bitmap_width(card3.img), al_get_bitmap_height(card3.img), xCard3, yCard3, 118*scale, 180*scale, 0);
    }
    if(!OPcard1.out){
        al_draw_scaled_bitmap(reverso, 0, 0, al_get_bitmap_width(reverso), al_get_bitmap_height(reverso), xOppCard1, yOppCard1, 118*scale, 180*scale, 0);
    }
    if(!OPcard2.out){
        al_draw_scaled_bitmap(reverso, 0, 0, al_get_bitmap_width(reverso), al_get_bitmap_height(reverso), xOppCard2, yOppCard2, 118*scale, 180*scale, 0);
    }
    if(!OPcard3.out){
        al_draw_scaled_bitmap(reverso, 0, 0, al_get_bitmap_width(reverso), al_get_bitmap_height(reverso), xOppCard3, yOppCard3, 118*scale, 180*scale, 0);
    }

    int userPlayed = 0; 
    int oppPlayed = 0;
    void cartaNaMesa(int user, int cartaJogada){
        int x;
        ALLEGRO_BITMAP* cardToPlay;
        if(user == 1){
            userPlayed++;
            switch(userPlayed){
            case 1:
                x = game.animations->cordsAux[0];
                break;
            case 2:
                x = game.animations->cordsAux[1];
                break;
            case 3:
                x = game.animations->cordsAux[2];
                break;
            }
            int y = game.animations->cordsAux[5];

           switch(cartaJogada){
            case 0:
                cardToPlay = card1.img;
                break;
            case 1:
                cardToPlay = card2.img;
                break;
            case 2:
                cardToPlay = card3.img;
                break;
            }
            al_draw_scaled_bitmap(cardToPlay, 0, 0, al_get_bitmap_width(cardToPlay), al_get_bitmap_height(cardToPlay), x, y, 118*scale, 180*scale, 0);
        }else if(user == 2){
            int y = game.animations->cordsAux[6];
            oppPlayed++;
            switch(oppPlayed){
            case 1:
                x = game.animations->cordsAux[0];
                break;
            case 2:
                x = game.animations->cordsAux[1];
                break;
            case 3:
                x = game.animations->cordsAux[2];
                break;
            }
            switch(cartaJogada){
            case 0:
                cardToPlay = OPcard1.img;
                break;
            case 1:
                cardToPlay = OPcard2.img;
                break;
            case 2:
                cardToPlay = OPcard3.img;
                break;
            }
            al_draw_scaled_bitmap(cardToPlay, 0, 0, al_get_bitmap_width(cardToPlay), al_get_bitmap_height(cardToPlay), x, y, 118*scale, 180*scale, 0);
        }
    }
    for(int i = 0; i < 6; i++){
        if(game.cartas->cartasJogadas[i][0] == 0){
            break;
        }else{
            cartaNaMesa(game.cartas->cartasJogadasOrdem[i][0], game.cartas->cartasJogadasOrdem[i][1]);
        }
    }
    
    int xRect = (larguraEscolhida/2 - (118*scale)*2 - (30*scale) - (20*scale));
    al_draw_filled_rectangle((20*scale), (20*scale), xRect, (alturaEscolhida) - (150*scale), al_map_rgba(0, 0, 0, 125));
    al_draw_rectangle((20*scale), (20*scale), xRect, alturaEscolhida - (150*scale), al_map_rgb(255, 255, 255), (float)2*scale);
    al_draw_line((xRect + (20*scale))/2, (20*scale), (xRect + (20*scale))/2, (alturaEscolhida) - (150*scale), al_map_rgb(255, 255, 255), (1*scale));
    
    int fontHeight2 = al_get_font_line_height(font2);
    al_draw_text(font2, al_map_rgb(255,255,255), (20*scale)+ (xRect - (20*scale))/4.0, (20*scale) + (fontHeight2/2) + (10*scale), ALLEGRO_ALIGN_CENTRE, "Você");
    al_draw_text(font2, al_map_rgb(255,255,255), (20*scale)+ (xRect - (20*scale))*(3.0/4.0), (20*scale) + (fontHeight2/2) + (10*scale), ALLEGRO_ALIGN_CENTRE, opponent.name);
    
    int alturaFos = al_get_bitmap_height(fosforo);
    int larguraFos = al_get_bitmap_width(fosforo); 
    float fosEscala = (8 * scale) / alturaFos;

    float cx = larguraFos / 2.0;
    float cy = larguraFos / 2.0;

    float fosAlturaEsc = larguraFos * fosEscala;

    // centro
    float centroX = (20*scale)+ (xRect - (20*scale))/4.0;
    float centroY = (20 * scale) + fontHeight2 + (30 * scale) + fosAlturaEsc;

    for (int i = 0; i < game.userPoints; i++) {
        float angulo = (i % 5) * (ALLEGRO_PI / 2); // 0°, 90°, 180°, 270°
        float dx = centroX;
        float dy = centroY + (i/5)*(centroY/2);
        if(i % 5 == 4){
            angulo = ALLEGRO_PI / 4;
            dx -= fosAlturaEsc/4 + (2*scale);
            dy += fosAlturaEsc/4 + (2*scale);
        }
        al_draw_scaled_rotated_bitmap(fosforo, cx, cy, dx, dy, fosEscala, fosEscala, angulo, 0);
    }
    
    centroX = (20*scale)+ (xRect - (20*scale))*(3.0/4.0);
    for (int i = 0; i < game.opponentPoints; i++) {
        float angulo = (i % 5) * (ALLEGRO_PI / 2); // 0°, 90°, 180°, 270°
        float dx = centroX;
        float dy = centroY + (i/5)*(centroY/2);
        if(i % 5 == 4){
            angulo = ALLEGRO_PI / 4;
            dx -= fosAlturaEsc/4 + (2*scale);
            dy += fosAlturaEsc/4 + (2*scale);
        }   
        al_draw_scaled_rotated_bitmap(fosforo, cx, cy, dx, dy, fosEscala, fosEscala, angulo, 0);
    }
    
    
    void mainButtons(void){
        char trucoTxt[16] = "Truco"; 
        ALLEGRO_COLOR b1 = cinza, b2 = cinza, b3 = cinza, b4 = cinza;
        if(game.round->firstRoundEndVerify == 1 && game.chamadas->resultadoPopUp == 0 && game.chamadas->resultadoPopUpAux == 0){
            if(game.chamadas->valeQuatro == 0 && game.round->usrTurn == 1 && game.chamadas->flor == 0 && game.chamadas->contraFlor == 0 && game.chamadas->contraFlorResto == 0 && (game.chamadas->truco == 2 || game.chamadas->retruco == 2 || game.chamadas->cantado == 0)){
                b1 = branco;
                if(game.chamadas->cantado == 0){
                    strcpy(trucoTxt, "Truco");
                }else if(game.chamadas->truco == 2){
                    strcpy(trucoTxt, "Retruco");
                }else if(game.chamadas->retruco == 2){
                    strcpy(trucoTxt, "Vale 4");
                }else if(game.chamadas->valeQuatro){
                strcpy(trucoTxt, "Vale 4");
                b1 = cinza;
                }
            }else{
                if(game.chamadas->truco){
                    strcpy(trucoTxt, "Truco");
                    b1 = cinza;
                }else if(game.chamadas->retruco){
                    strcpy(trucoTxt, "Retruco");
                    b1 = cinza;
                }else if(game.chamadas->valeQuatro){
                    strcpy(trucoTxt, "Vale 4");
                    b1 = cinza;
                }
            }
            

            if(game.chamadas->flor == 0 && game.chamadas->florFeita == 0 && game.chamadas->contraFlor == 0 && game.chamadas->contraFlorResto == 0 && ((game.chamadas->cantado == 0 && game.chamadas->envidoFeito == 0 && game.round->usrTurn == 1 && game.round->cardsPlayed< 2) || (game.chamadas->cantado == 1 && game.chamadas->trucoAux == 2 && game.round->cardsPlayed < 2 && game.chamadas->truco == 2 && game.chamadas->envidoFeito == 0))){
                b2 = branco;  
            }
            if(game.cartas->cantarFlor[0] == 1 && game.round->usrTurn == 1 && game.round->cardsPlayed < 2 && game.chamadas->florFeita == 0 && (game.chamadas->cantado == 0 || (game.chamadas->cantado == 1 && (game.chamadas->flor == 2 || game.chamadas->contraFlor == 2)))){
                b3 = branco;
            }
            if(game.round->usrTurn == 1 && game.chamadas->trucoAux == 0 && game.chamadas->flor == 0 && game.chamadas->contraFlor == 0 && game.chamadas->contraFlorResto == 0){
                b4 = branco;
            }
        }

        al_draw_scaled_bitmap(mesa, 0, 0, al_get_bitmap_width(mesa), al_get_bitmap_height(mesa), (20*scale), (alturaEscolhida) - (130*scale), ((xRect-(20*scale))/2) - (10*scale) , 50*scale, 0);
        al_draw_rectangle((20*scale), (alturaEscolhida) - (130*scale), ((xRect + (20*scale))/2) - (10*scale), alturaEscolhida - (80*scale), b1, (float)2*scale);

        al_draw_scaled_bitmap(mesa, 0, 0, al_get_bitmap_width(mesa), al_get_bitmap_height(mesa), ((xRect + (20*scale))/2) + (10*scale), (alturaEscolhida) - (130*scale), ((xRect-(20*scale))/2) - (10*scale) , 50*scale, 0);
        al_draw_rectangle(((xRect + (20*scale))/2) + (10*scale), (alturaEscolhida) - (130*scale), xRect, alturaEscolhida - (80*scale), b2, (float)2*scale);

        al_draw_scaled_bitmap(mesa, 0, 0, al_get_bitmap_width(mesa), al_get_bitmap_height(mesa), (20*scale), (alturaEscolhida) - (70*scale), ((xRect-(20*scale))/2) - (10*scale) , 50*scale, 0);
        al_draw_rectangle((20*scale), alturaEscolhida - (70*scale), ((xRect + (20*scale))/2) - (10*scale), alturaEscolhida - (20*scale), b3, (float)2*scale);

        al_draw_scaled_bitmap(mesa, 0, 0, al_get_bitmap_width(mesa), al_get_bitmap_height(mesa), ((xRect + (20*scale))/2) +(10*scale), (alturaEscolhida) - (70*scale), ((xRect-(20*scale))/2) - (10*scale) , 50*scale, 0);
        al_draw_rectangle(((xRect + (20*scale))/2) + (10*scale), alturaEscolhida - (70*scale), xRect, alturaEscolhida - (20*scale), b4, (float)2*scale);

        al_draw_text(font3, b1,
        ((20*scale) + (((xRect + (20*scale))/2) - (10*scale))) / 2,
        (((alturaEscolhida - (130*scale)) + (alturaEscolhida - (80*scale))) / 2) - al_get_font_line_height(font3)/2,
        ALLEGRO_ALIGN_CENTRE, trucoTxt);

        al_draw_text(font3, b2,
        ((((xRect + (20*scale))/2) + (10*scale)) + xRect) / 2,
        (((alturaEscolhida - (130*scale)) + (alturaEscolhida - (80*scale))) / 2) - al_get_font_line_height(font3)/2,
        ALLEGRO_ALIGN_CENTRE, "ENVIDO");

        al_draw_text(font3, b3,
        ((20*scale) + (((xRect + (20*scale))/2) - (10*scale))) / 2,
        (((alturaEscolhida - (70*scale)) + (alturaEscolhida - (20*scale))) / 2) - al_get_font_line_height(font3)/2,
        ALLEGRO_ALIGN_CENTRE, "FLOR");


        al_draw_text(font3, b4,
        ((((xRect + (20*scale))/2) + (10*scale)) + xRect) / 2,
        (((alturaEscolhida - (70*scale)) + (alturaEscolhida - (20*scale))) / 2) - al_get_font_line_height(font3)/2,
        ALLEGRO_ALIGN_CENTRE, "MAZO");
    }
    
    void envidoButtons(void){
        ALLEGRO_COLOR b1 = cinza, b2 = cinza, b3 = cinza, b4 = cinza;
        if(game.round->firstRoundEndVerify == 1 && game.chamadas->resultadoPopUp == 0 && game.chamadas->resultadoPopUpAux == 0){
            if(game.chamadas->flor == 0 && game.chamadas->florFeita == 0 && game.chamadas->contraFlor == 0 && game.chamadas->contraFlorResto == 0 && ((game.chamadas->cantado == 0 && game.chamadas->envidoFeito == 0 && game.round->usrTurn == 1 && game.round->cardsPlayed< 2) || (game.chamadas->cantado == 1 && game.chamadas->trucoAux == 2 && game.round->cardsPlayed < 2 && game.chamadas->truco == 2 && game.chamadas->envidoFeito == 0) || (game.chamadas->envido == 2 || game.chamadas->envido2 == 2 || game.chamadas->realEnvido == 2 || game.chamadas->faltaEnvido == 2))){
                if((game.chamadas->envido == 2 || game.chamadas->cantado == 0 || game.chamadas->truco == 2 )){
                    b1 = branco;
                }if(game.chamadas->envido == 2 || game.chamadas->envido2 == 2 || game.chamadas->cantado == 0 || game.chamadas->truco == 2){
                    b2 = branco;
                }
                if(game.chamadas->envido == 2 || game.chamadas->envido2 == 2 || game.chamadas->realEnvido == 2 || game.chamadas->cantado == 0 || game.chamadas->truco == 2){
                    b3 = branco;
                }
                if(!game.chamadas->cantado){
                    b4 = branco;
                }
            }
        }

        al_draw_scaled_bitmap(mesa, 0, 0, al_get_bitmap_width(mesa), al_get_bitmap_height(mesa), (20*scale), (alturaEscolhida) - (130*scale), ((xRect-(20*scale))/2) - (10*scale) , 50*scale, 0);
        al_draw_rectangle((20*scale), (alturaEscolhida) - (130*scale), ((xRect + (20*scale))/2) - (10*scale), alturaEscolhida - (80*scale), b1, (float)2*scale);

        al_draw_scaled_bitmap(mesa, 0, 0, al_get_bitmap_width(mesa), al_get_bitmap_height(mesa), ((xRect + (20*scale))/2) + (10*scale), (alturaEscolhida) - (130*scale), ((xRect-(20*scale))/2) - (10*scale) , 50*scale, 0);
        al_draw_rectangle(((xRect + (20*scale))/2) + (10*scale), (alturaEscolhida) - (130*scale), xRect, alturaEscolhida - (80*scale), b2, (float)2*scale);

        al_draw_scaled_bitmap(mesa, 0, 0, al_get_bitmap_width(mesa), al_get_bitmap_height(mesa), (20*scale), (alturaEscolhida) - (70*scale), ((xRect-(20*scale))/2) - (10*scale) , 50*scale, 0);
        al_draw_rectangle((20*scale), alturaEscolhida - (70*scale), ((xRect + (20*scale))/2) - (10*scale), alturaEscolhida - (20*scale), b3, (float)2*scale);

        al_draw_scaled_bitmap(mesa, 0, 0, al_get_bitmap_width(mesa), al_get_bitmap_height(mesa), ((xRect + (20*scale))/2) +(10*scale), (alturaEscolhida) - (70*scale), ((xRect-(20*scale))/2) - (10*scale) , 50*scale, 0);
        al_draw_rectangle(((xRect + (20*scale))/2) + (10*scale), alturaEscolhida - (70*scale), xRect, alturaEscolhida - (20*scale), b4, (float)2*scale);


        al_draw_text(font3, b1,
        ((20*scale) + (((xRect + (20*scale))/2) - (10*scale))) / 2,
        (((alturaEscolhida - (130*scale)) + (alturaEscolhida - (80*scale))) / 2) - al_get_font_line_height(font3)/2,
        ALLEGRO_ALIGN_CENTRE, "ENVIDO");

        al_draw_text(font3, b2,
        ((((xRect + (20*scale))/2) + (10*scale)) + xRect) / 2,
        (((alturaEscolhida - (130*scale)) + (alturaEscolhida - (80*scale))) / 2) - al_get_font_line_height(font3)/2,
        ALLEGRO_ALIGN_CENTRE, "REAL ENVIDO");

        al_draw_text(font3, b3,
        ((20*scale) + (((xRect + (20*scale))/2) - (10*scale))) / 2,
        (((alturaEscolhida - (70*scale)) + (alturaEscolhida - (20*scale))) / 2) - al_get_font_line_height(font3)/2,
        ALLEGRO_ALIGN_CENTRE, "FALTA ENVIDO");
    
        al_draw_text(font3, b4,
        ((((xRect + (20*scale))/2) + (10*scale)) + xRect) / 2,
        (((alturaEscolhida - (70*scale)) + (alturaEscolhida - (20*scale))) / 2) - al_get_font_line_height(font3)/2,
        ALLEGRO_ALIGN_CENTRE, "VOLTAR");
    }

    void trucoButtons(void){
        int botao_largura = 150 * scale;
        int botao_altura = 50 * scale;
        int largura_total = botao_largura * 2;
        int altura_botao = 45 * scale;
        int x = (larguraEscolhida - largura_total) / 2;
        int y = alturaEscolhida - botao_altura - altura_botao;

        char trucoAccStr[25];
        if(game.chamadas->truco == 2){
            sprintf(trucoAccStr, "%s", "Retruco");
        }else if(game.chamadas->retruco == 2){
            sprintf(trucoAccStr, "%s", "Quero vale 4");
        }
        
        al_draw_filled_rectangle(x, y, x + largura_total, y + altura_botao, al_map_rgba(196, 143, 0, 200));
        al_draw_rectangle(x, y, x + largura_total, y + altura_botao, al_map_rgb(255, 255, 255), 2 * scale);
        al_draw_text(font3, al_map_rgb(255, 255, 255), x + largura_total / 2, y + altura_botao / 2 - al_get_font_line_height(font3) / 2, ALLEGRO_ALIGN_CENTRE, trucoAccStr);
    }

    void florButtons(void){
        int botao_largura = 150 * scale;
        int botao_altura = 50 * scale;
        int largura_total = botao_largura * 2;
        int altura_botao = 45 * scale;
        int x = (larguraEscolhida - largura_total) / 2;
        int y = alturaEscolhida - botao_altura - altura_botao;

        char FlorAccStr[25];
        if(game.chamadas->envido == 2 || game.chamadas->truco == 2 ){
            sprintf(FlorAccStr, "%s", "Flor");
        }
        if(game.chamadas->flor == 2){
            sprintf(FlorAccStr, "%s", "Contra flor");
        }else if(game.chamadas->contraFlor == 2){
            sprintf(FlorAccStr, "%s", "Contra flor e o resto");
        }
        
        al_draw_filled_rectangle(x, y, x + largura_total, y + altura_botao, al_map_rgba(196, 143, 0, 200));
        al_draw_rectangle(x, y, x + largura_total, y + altura_botao, al_map_rgb(255, 255, 255), 2 * scale);
        al_draw_text(font3, al_map_rgb(255, 255, 255), x + largura_total / 2, y + altura_botao / 2 - al_get_font_line_height(font3) / 2, ALLEGRO_ALIGN_CENTRE, FlorAccStr);
    }

    void accOrDeny(void){
        int botao_largura = 150 * scale;
        int botao_altura = 50 * scale;
        int y_botao = alturaEscolhida - botao_altura;
        int x_centro_tela = larguraEscolhida/2;
        int x1_quero = x_centro_tela - botao_largura;
        int x2_quero = x_centro_tela;
    
        al_draw_filled_rectangle(x1_quero, y_botao, x2_quero, alturaEscolhida, al_map_rgba(0, 100, 0, 200));
        al_draw_rectangle(x1_quero, y_botao, x2_quero, alturaEscolhida, al_map_rgb(255, 255, 255), 2 * scale);
        al_draw_text(font3, al_map_rgb(255, 255, 255), (x1_quero + x2_quero) / 2, y_botao + botao_altura / 2 - al_get_font_line_height(font3) / 2, ALLEGRO_ALIGN_CENTRE, "QUERO");
    
        float x1_naoquero = x_centro_tela;
        float x2_naoquero = x_centro_tela + botao_largura;
    
        al_draw_filled_rectangle(x1_naoquero, y_botao, x2_naoquero, alturaEscolhida, al_map_rgba(150, 40, 0, 200));
        al_draw_rectangle(x1_naoquero, y_botao, x2_naoquero, alturaEscolhida, al_map_rgb(255, 255, 255), 2 * scale);
        al_draw_text(font3, al_map_rgb(255, 255, 255),(x1_naoquero + x2_naoquero) / 2, y_botao + botao_altura / 2 - al_get_font_line_height(font3) / 2,ALLEGRO_ALIGN_CENTRE, "NÃO QUERO");
    } 

    
    void resultadosPopUp(void){
        float larguraRet = 400 * scale;
        float alturaRet = 200 * scale;
        
        float xRet = (larguraEscolhida - larguraRet) / 2;
        float yRet = (alturaEscolhida - alturaRet) / 2;
        
        
        al_draw_filled_rectangle(xRet, yRet, xRet + larguraRet, yRet + alturaRet, al_map_rgba(0, 0, 0, 200));
       
        al_draw_rectangle(xRet, yRet, xRet + larguraRet, yRet + alturaRet, al_map_rgb(255, 255, 255), 3 * scale);
        
        char Titleholder[40];
        char auxWinner[40];
        int p1 = game.cartas->pontosEnvido[0];
        int p2 = game.cartas->pontosEnvido[1];
        int winner = (p1 > p2) ? 1 : (p2 > p1) ? 2 : game.round->mao;
        if(winner == 1){
            char aux[40] = "Você";
            memcpy(auxWinner, aux, sizeof(auxWinner));
        }else{
            memcpy(auxWinner, opponent.name, sizeof(auxWinner));
        }

        sprintf(Titleholder, "%s %s", auxWinner, "venceu");
        float yTitulo = yRet + (15 * scale);
        al_draw_text(font, al_map_rgb(255, 255, 255), xRet + larguraRet / 2, yTitulo, ALLEGRO_ALIGN_CENTRE, Titleholder);
         
        float yCentro = yRet + alturaRet / 2 + al_get_font_line_height(font) / 2;
        
        float xEsquerda = xRet + (30 * scale); 
        
        char p2mao[10] = "";
        char p1mao[10] = "";
        if(p1 == p2){
            char* auxS = "(Mão)";
            if(game.round->mao == 1){
                memcpy(p1mao, auxS, sizeof(p1mao));
            }else{
                memcpy(p2mao, auxS, sizeof(p1mao));
            }
        }
        char p1Txt[40];
        char p2Txt[40];
        if(game.chamadas->p1FalarPontos){
            sprintf(p1Txt, "Você: %d pontos %s", p1, p1mao);
        }else{
            char auxFin[25] = "Você: É bom...";
            memcpy(p1Txt, auxFin, sizeof(auxFin));
        }

        if(game.chamadas->p2falarPontos){
            sprintf(p2Txt, "%s: %d pontos %s", opponent.name, p2, p2mao);
        }else{
            char auxFin[25];
            sprintf(auxFin, "%s: É bom...", opponent.name);
            memcpy(p2Txt, auxFin, sizeof(auxFin));
        }

        al_draw_text(font, al_map_rgb(255, 255, 255), xEsquerda, yCentro - al_get_font_line_height(font), 0, p1Txt);
        al_draw_text(font, al_map_rgb(255, 255, 255), xEsquerda, yCentro + (5 * scale), 0, p2Txt);
        
        
        const char* textoOk = "OK";
        float larguraBotao = 80 * scale;
        float alturaBotao = 40 * scale;
        float xBotao = xRet + (larguraRet / 2) - (larguraBotao / 2);
        float yBotao = yRet + alturaRet + (15 * scale);
        
       
        al_draw_filled_rectangle(xBotao, yBotao, xBotao + larguraBotao, yBotao + alturaBotao, al_map_rgba(0, 0, 0, 200));
        
        al_draw_rectangle(xBotao, yBotao, xBotao + larguraBotao, yBotao + alturaBotao, al_map_rgb(255, 255, 255), 2 * scale);
        
        al_draw_text(font2, al_map_rgb(255, 255, 255), xBotao + larguraBotao / 2, yBotao + alturaBotao / 2 - al_get_font_line_height(font2) / 2, ALLEGRO_ALIGN_CENTRE, textoOk);
    }
    
    int nuvemLarguraOriginal = 666;
    int nuvemAlturaOriginal = 375;
    float larguraNuvem = nuvemLarguraOriginal * scale * 0.5;
    float alturaNuvem = nuvemAlturaOriginal * scale * 0.5;

    void nuvemBot(void){
        float xNuvem = larguraEscolhida - (150 * scale) - (45 * scale) - larguraNuvem; 
        float yNuvem = (50 * scale) + (150 * scale / 2) - (alturaNuvem / 2); 
        float cx = xNuvem + larguraNuvem / 2;
        float cy = (yNuvem + alturaNuvem / 2 - al_get_font_line_height(font3) / 2) - (10*scale);
        al_draw_scaled_bitmap(game.imagens.nuvem, 0, 0, nuvemLarguraOriginal, nuvemAlturaOriginal, xNuvem, yNuvem, larguraNuvem, alturaNuvem, 0);
        al_draw_text(font3, al_map_rgb(0, 0, 0), cx, cy, ALLEGRO_ALIGN_CENTRE, game.chamadas->botMsg);
    }
    void nuvemUsr(void){
        float xNuvem = larguraEscolhida - (150 * scale) - (45 * scale) - larguraNuvem; 
        float yNuvem = alturaEscolhida - (150 * scale) - (50 * scale) + (150 * scale / 2) - (alturaNuvem / 2);
        float cx = xNuvem + larguraNuvem / 2;
        float cy = (yNuvem + alturaNuvem / 2 - al_get_font_line_height(font3) / 2) - (10*scale);
        al_draw_scaled_bitmap(game.imagens.nuvem, 0, 0, nuvemLarguraOriginal, nuvemAlturaOriginal, xNuvem, yNuvem, larguraNuvem, alturaNuvem, 0);
        al_draw_text(font3, al_map_rgb(0, 0, 0), cx, cy, ALLEGRO_ALIGN_CENTRE, game.chamadas->usrMsg);
    }
    
int userExtraCount = 0;
int oppExtraCount = 0;
for (int i = 0; i < 6; i++) {
    if (game.cartas->cartasJogadas[i][0] == 0) break;
    int quem = game.cartas->cartasJogadasOrdem[i][0];
    if (quem == 1) userExtraCount++;
    else if (quem == 2) oppExtraCount++;
}

for (int i = 0; i < 3; i++) {
    if (game.cartas->arrCartasUsr[i].mostrarExtra) {
        ALLEGRO_BITMAP *img = game.cartas->arrCartasUsr[i].img;
        int x = game.animations->cordsAux[userExtraCount];
        int y = game.animations->cordsAux[5];
        al_draw_scaled_bitmap(img, 0, 0,
            al_get_bitmap_width(img), al_get_bitmap_height(img),
            x, y, 118 * scale, 180 * scale, 0);
        userExtraCount++;
    }

    if (game.cartas->arrCartasOpp[i].mostrarExtra) {
        ALLEGRO_BITMAP *img = game.cartas->arrCartasOpp[i].img;
        int x = game.animations->cordsAux[oppExtraCount];
        int y = game.animations->cordsAux[6];
        al_draw_scaled_bitmap(img, 0, 0,
            al_get_bitmap_width(img), al_get_bitmap_height(img),
            x, y, 118 * scale, 180 * scale, 0);
        oppExtraCount++;
    }
}
void mostrarCartasEnvidoOuFlor(void) {
    int envidoUsr = game.cartas->pontosEnvido[0];
    int envidoBot = game.cartas->pontosEnvido[1];
    int winner = (envidoUsr > envidoBot) ? 1 : (envidoBot > envidoUsr) ? 2 : game.round->mao;

    int userPlayed = 0;
    int oppPlayed = 0;
    for (int i = 0; i < 6; i++) {
        if (game.cartas->cartasJogadas[i][0] == 0) break;
        int quem = game.cartas->cartasJogadasOrdem[i][0];
        if (quem == 1) userPlayed++;
        else if (quem == 2) oppPlayed++;
    }

    int cartasMostradasUsr = 0;
    int cartasMostradasBot = 0;

    if (game.chamadas->florFeita) {
        if (winner == 1) {
            for (int i = 0; i < 3; i++) {
                if (!game.cartas->arrCartasUsr[i].out) {
                    game.cartas->arrCartasUsr[i].mostrarExtra = 1;
                    game.cartas->arrCartasUsr[i].out = 1;
                    cartasMostradasUsr++;
                }
            }
            if (cartasMostradasUsr > 0) {
                sprintf(game.chamadas->usrMsg, "Flor na mesa");
                game.chamadas->msgPopUpOnUsr = 1;
                game.chamadas->msgPopUpTimerUsr = al_get_time();
            }
        } else {
            for (int i = 0; i < 3; i++) {
                if (!game.cartas->arrCartasOpp[i].out) {
                    game.cartas->arrCartasOpp[i].mostrarExtra = 1;
                    game.cartas->arrCartasOpp[i].out = 1;
                    cartasMostradasBot++;
                }
            }
            if (cartasMostradasBot > 0) {
                sprintf(game.chamadas->botMsg, "Flor na mesa");
                game.chamadas->msgPopUpOn = 1;
                game.chamadas->msgPopUpTimer = al_get_time();
            }
        }
    }
    else if (game.chamadas->envidoAceito) {
        if (winner == 1) {
            for (int i = 0; i < 2; i++) {
                int idx = game.cartas->indexEnvidop1[i];
                if (idx != -1 && !game.cartas->arrCartasUsr[idx].out) {
                    game.cartas->arrCartasUsr[idx].mostrarExtra = 1;
                    game.cartas->arrCartasUsr[idx].out = 1;
                    cartasMostradasUsr++;
                }
            }
            if (cartasMostradasUsr > 0) {
                sprintf(game.chamadas->usrMsg, "Meus pontos..");
                game.chamadas->msgPopUpOnUsr = 1;
                game.chamadas->msgPopUpTimerUsr = al_get_time();
            }
        } else {
            for (int i = 0; i < 2; i++) {
                int idx = game.cartas->indexEnvidop2[i];
                if (idx != -1 && !game.cartas->arrCartasOpp[idx].out) {
                    game.cartas->arrCartasOpp[idx].mostrarExtra = 1;
                    game.cartas->arrCartasOpp[idx].out = 1;
                    cartasMostradasBot++;
                }
            }
            if (cartasMostradasBot > 0) {
                sprintf(game.chamadas->botMsg, "Meus pontos..");
                game.chamadas->msgPopUpOn = 1;
                game.chamadas->msgPopUpTimer = al_get_time();
            }
        }
    }

    if ((cartasMostradasUsr > 0 || cartasMostradasBot > 0) && game.chamadas->audiofirstTime == 0) {
        game.chamadas->audiofirstTime = 1;
        // tocar áudio se necessário
    }
}



    if(game.chamadas->cartasNaMesaVerify == 1){
        mostrarCartasEnvidoOuFlor();
    }



    if(game.chamadas->mainButtons == 1){
        mainButtons();
    }
    if(game.chamadas->aceitarPopUp == 1){
        accOrDeny();
    }
    if(game.chamadas->envidoButtons == 1){
        envidoButtons();
    }
    if(game.chamadas->msgPopUpOn == 1){
        nuvemBot();
    }
    if(game.chamadas->msgPopUpOnUsr == 1){
        nuvemUsr();
    }
    if(game.chamadas->resultadoPopUp == 1){
        resultadosPopUp();
    }
    if(game.chamadas->trucoButtons == 1){
        trucoButtons();
    }
    if(game.chamadas->florButtons == 1){
        florButtons();
    }

    al_flip_display();
}