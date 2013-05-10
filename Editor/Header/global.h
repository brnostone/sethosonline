#ifndef GLOBAL_H_
#define GLOBAL_H_

#define NUM_TITLE 9
#define NUM_TIPOS 6
#define NUM_TIPOSOBJ 7
#define NUM_CASAS 2
#define NUM_INTERAC 2

Textura *title[NUM_TITLE];
Textura *parede[2];
Textura *objetos[NUM_TIPOSOBJ];
Textura *interacao[NUM_INTERAC];
Textura *casa[NUM_CASAS];

SDL_Surface *screen;

Textura *mouse;
Textura *cursorCor;

Textura *cores;
Textura *ferramentas;

Uint8 *keystate;

int mousemovidox;
int mousemovidoy;
int contapress;

int xpos;
int ypos;

int cursorT;
int numJanela;

int mapWidth;
int mapHeight;

#endif /* GLOBAL_H_ */

