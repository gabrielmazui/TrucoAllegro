#include <stdio.h>
#include <allegro5/allegro5.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
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

    al_draw_tinted_scaled_bitmap(background, al_map_rgb(255, 255, 255), 0, 0, larguraB, alturaB, 0, 0, larguraEscolhida, alturaEscolhida, 0);
    al_draw_scaled_bitmap(opponent.pfp, 0, 0, al_get_bitmap_width(opponent.pfp), al_get_bitmap_height(opponent.pfp), larguraEscolhida - (150*scale) - (100*scale), (50*scale), 150*scale, 150*scale, 0);
    al_draw_scaled_bitmap(user.pfp, 0, 0, al_get_bitmap_width(user.pfp), al_get_bitmap_height(user.pfp), larguraEscolhida - (150*scale) - (100*scale), alturaEscolhida - (150*scale) - (50*scale), 150*scale, 150*scale, 0);
    al_draw_scaled_bitmap(user.pfp, 0, 0, al_get_bitmap_width(user.pfp), al_get_bitmap_height(user.pfp), larguraEscolhida - (150*scale) - (100*scale), alturaEscolhida - (150*scale) - (50*scale), 150*scale, 150*scale, 0);
    al_draw_scaled_bitmap(mesa, 0, 0, al_get_bitmap_width(mesa), al_get_bitmap_height(mesa), larguraEscolhida/2 - (118*scale)*2 - (30*scale), alturaEscolhida/2 - (306*scale)/2, 470*scale, 285*scale, 0);
    al_draw_rectangle(larguraEscolhida/2 - (118*scale)*2 - (30*scale), alturaEscolhida/2 - (306*scale)/2, larguraEscolhida/2 - (118*scale)*2 - (30*scale) + (470*scale), alturaEscolhida/2 - (306*scale)/2 + (285*scale), al_map_rgb(0, 0, 0), (float)2*scale);
    
    int fontHeight = al_get_font_line_height(font);
    al_draw_text(font, al_map_rgb(255, 255, 255),larguraEscolhida - (150*scale) - (100*scale) + (150*scale)/2, alturaEscolhida - (150*scale) - (50*scale) - (10*scale) - fontHeight, ALLEGRO_ALIGN_CENTRE, user.name);
    al_draw_text(font, al_map_rgb(255, 255, 255),larguraEscolhida - (150*scale) - (100*scale)+ (150*scale)/2, (50*scale) + (150*scale) + (10*scale), ALLEGRO_ALIGN_CENTRE, opponent.name);
    
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
    al_draw_scaled_bitmap(mesa, 0, 0, al_get_bitmap_width(mesa), al_get_bitmap_height(mesa), (20*scale), (alturaEscolhida) - (130*scale), ((xRect-(20*scale))/2) - (10*scale) , 50*scale, 0);
    al_draw_rectangle((20*scale), (alturaEscolhida) - (130*scale), ((xRect + (20*scale))/2) - (10*scale), alturaEscolhida - (80*scale), al_map_rgb(255, 255, 255), (float)2*scale);

    al_draw_scaled_bitmap(mesa, 0, 0, al_get_bitmap_width(mesa), al_get_bitmap_height(mesa), ((xRect + (20*scale))/2) + (10*scale), (alturaEscolhida) - (130*scale), ((xRect-(20*scale))/2) - (10*scale) , 50*scale, 0);
    al_draw_rectangle(((xRect + (20*scale))/2) + (10*scale), (alturaEscolhida) - (130*scale), xRect, alturaEscolhida - (80*scale), al_map_rgb(255, 255, 255), (float)2*scale);

    al_draw_scaled_bitmap(mesa, 0, 0, al_get_bitmap_width(mesa), al_get_bitmap_height(mesa), (20*scale), (alturaEscolhida) - (70*scale), ((xRect-(20*scale))/2) - (10*scale) , 50*scale, 0);
    al_draw_rectangle((20*scale), alturaEscolhida - (70*scale), ((xRect + (20*scale))/2) - (10*scale), alturaEscolhida - (20*scale), al_map_rgb(255, 255, 255), (float)2*scale);

    al_draw_scaled_bitmap(mesa, 0, 0, al_get_bitmap_width(mesa), al_get_bitmap_height(mesa), ((xRect + (20*scale))/2) +(10*scale), (alturaEscolhida) - (70*scale), ((xRect-(20*scale))/2) - (10*scale) , 50*scale, 0);
    al_draw_rectangle(((xRect + (20*scale))/2) + (10*scale), alturaEscolhida - (70*scale), xRect, alturaEscolhida - (20*scale), al_map_rgb(255, 255, 255), (float)2*scale);
    
    void mainButtons(void){
        al_draw_text(font3, al_map_rgb(255, 255, 255),
        ((20*scale) + (((xRect + (20*scale))/2) - (10*scale))) / 2,
        (((alturaEscolhida - (130*scale)) + (alturaEscolhida - (80*scale))) / 2) - al_get_font_line_height(font3)/2,
        ALLEGRO_ALIGN_CENTRE, "TRUCO");

        al_draw_text(font3, al_map_rgb(255, 255, 255),
        ((((xRect + (20*scale))/2) + (10*scale)) + xRect) / 2,
        (((alturaEscolhida - (130*scale)) + (alturaEscolhida - (80*scale))) / 2) - al_get_font_line_height(font3)/2,
        ALLEGRO_ALIGN_CENTRE, "ENVIDO");

        al_draw_text(font3, al_map_rgb(255, 255, 255),
        ((20*scale) + (((xRect + (20*scale))/2) - (10*scale))) / 2,
        (((alturaEscolhida - (70*scale)) + (alturaEscolhida - (20*scale))) / 2) - al_get_font_line_height(font3)/2,
        ALLEGRO_ALIGN_CENTRE, "FLOR");

        al_draw_text(font3, al_map_rgb(255, 255, 255),
        ((((xRect + (20*scale))/2) + (10*scale)) + xRect) / 2,
        (((alturaEscolhida - (70*scale)) + (alturaEscolhida - (20*scale))) / 2) - al_get_font_line_height(font3)/2,
        ALLEGRO_ALIGN_CENTRE, "MAZO");
    }
    
    void envidoButtons(void){
        al_draw_text(font3, al_map_rgb(255, 255, 255),
        ((20*scale) + (((xRect + (20*scale))/2) - (10*scale))) / 2,
        (((alturaEscolhida - (130*scale)) + (alturaEscolhida - (80*scale))) / 2) - al_get_font_line_height(font3)/2,
        ALLEGRO_ALIGN_CENTRE, "ENVIDO");

        al_draw_text(font3, al_map_rgb(255, 255, 255),
        ((((xRect + (20*scale))/2) + (10*scale)) + xRect) / 2,
        (((alturaEscolhida - (130*scale)) + (alturaEscolhida - (80*scale))) / 2) - al_get_font_line_height(font3)/2,
        ALLEGRO_ALIGN_CENTRE, "REAL ENVIDO");

        al_draw_text(font3, al_map_rgb(255, 255, 255),
        ((20*scale) + (((xRect + (20*scale))/2) - (10*scale))) / 2,
        (((alturaEscolhida - (70*scale)) + (alturaEscolhida - (20*scale))) / 2) - al_get_font_line_height(font3)/2,
        ALLEGRO_ALIGN_CENTRE, "FALTA ENVIDO");

        al_draw_text(font3, al_map_rgb(255, 255, 255),
        ((((xRect + (20*scale))/2) + (10*scale)) + xRect) / 2,
        (((alturaEscolhida - (70*scale)) + (alturaEscolhida - (20*scale))) / 2) - al_get_font_line_height(font3)/2,
        ALLEGRO_ALIGN_CENTRE, "VOLTAR");
    }

    void accOrDeny(void){
        int botao_largura = 150 * scale;
        int botao_altura = 50 * scale;
        int y_botao = alturaEscolhida - botao_altura;
        int x_centro_tela = larguraEscolhida/2;
        int x1_quero = x_centro_tela - botao_largura;
        int x2_quero = x_centro_tela;
    
        al_draw_filled_rectangle(x1_quero, y_botao, x2_quero, alturaEscolhida, al_map_rgba(150, 40, 0, 200));
        al_draw_rectangle(x1_quero, y_botao, x2_quero, alturaEscolhida, al_map_rgb(255, 255, 255), 2 * scale);
        al_draw_text(font3, al_map_rgb(255, 255, 255), (x1_quero + x2_quero) / 2, y_botao + botao_altura / 2 - al_get_font_line_height(font3) / 2, ALLEGRO_ALIGN_CENTRE, "QUERO");
    
        float x1_naoquero = x_centro_tela;
        float x2_naoquero = x_centro_tela + botao_largura;
    
        al_draw_filled_rectangle(x1_naoquero, y_botao, x2_naoquero, alturaEscolhida, al_map_rgba(0, 100, 0, 200));
        al_draw_rectangle(x1_naoquero, y_botao, x2_naoquero, alturaEscolhida, al_map_rgb(255, 255, 255), 2 * scale);
        al_draw_text(font3, al_map_rgb(255, 255, 255),(x1_naoquero + x2_naoquero) / 2, y_botao + botao_altura / 2 - al_get_font_line_height(font3) / 2,ALLEGRO_ALIGN_CENTRE, "NÃO QUERO");
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

    al_flip_display();
}