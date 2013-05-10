/*
 * global.h
 *
 *  Created on: 02/10/2009
 *      Author: bruno
 */

#ifndef GLOBAL_H_
#define GLOBAL_H_

#include <SDL/SDL.h>
#include "opengl.h"
#include "fonte.h"

#define NUMERODEPERSONAGENS 7
#define NUM_TITLE 9
#define NUM_TITLEOU 9
#define NUM_TIPOS 4
#define NUM_CASAS 2
#define NUM_PAREDES 3
#define NUM_TIPOSOBJ 7
#define NUM_ANIMAIS 4
#define NUM_MAGICS 5
#define NUM_LOAD 23
#define NUM_INTERAC 2
#define QUANT_MONSTROS 3
#define NUM_NPCS 4

SDL_Surface *screen;
Textura *personagens[NUMERODEPERSONAGENS][8];
Textura *monstros[QUANT_MONSTROS][6];
Textura *personagemmagica;
Textura *barra;
Textura *emoticon;
Textura *barraquantid;
Textura *botaopress;
Textura *inventario;
Textura *charmenu;
Textura *magicmenu;
Textura *baumenu;
Textura *mouse;
Textura *parede[NUM_PAREDES];
Textura *objetos[NUM_TIPOSOBJ];
Textura *casa[NUM_CASAS];
Textura *title[NUM_TITLEOU];
Textura *flechas[32];
Textura *animais[NUM_ANIMAIS];
Textura *magicas[NUM_MAGICS];
Textura *interacao[NUM_INTERAC];
Textura *helms;
Textura *blackaura[7];
Textura *aurazul[16];
Textura *aurawhite[7];
Textura *auraverde[5];
Textura *auraba[5];
Textura *auragirado[6];
Textura *magicasbotao;
Textura *efeitos;
Textura *armor;
Textura *escudos;
Textura *clavas;
Textura *machados;
Textura *espadas;
Textura *staffs;
Textura *arcos;
Textura *amuletos;
Textura *aneis;
Textura *braco;
Textura *luvas;
Textura *botas;
Textura *capas;
Textura *item;
Textura *item2;
Textura *armasnochao;
Textura *amuletosanelchao;
Textura *barclubochao;
Textura *capaschao;
Textura *itenschaoi;
Textura *itens2chaoi;
Textura *armesccaho;
Textura *helmschao;
Textura *dinheirochao;
Textura *varapesca;
Textura *barrapesca;
Textura *cursorpesca;
Textura *BotaoEstilo;
Textura *boia;
Textura *balao;
Textura *gui_i;
Textura *particulas[3];
Textura *logo[2];
Textura *npcs_imag[NUM_NPCS];
Textura *vendeitem;

Fonte *font;
Fonte *font2;
Fonte *fontGUI;

Uint8 *keystate;

char done;
char lctrlpress;
char estaaandar;
char antesaltpress;

int mousemovidox;
int mousemovidoy;
int contapress;

int addbotaoclick;

//TODO: remover SegueIDAux
int SegueIDAux;

int logtemp;

int quantidade;

int proximolevelexp;

int mouseencima;
int CursorUsando[2];

#endif /* GLOBAL_H_ */
