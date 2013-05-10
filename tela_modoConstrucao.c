#include "Header/modoconstrucao.h"
#include "Header/mapas.h"
#include "Header/global.h"
#include "Header/tela_modoConstrucao.h"

void Tela_ModContr_DrawScene() {
  ModoConstrucao_draw();
}

void Tela_ModContr_Eventos(SDL_Event *event) {
  if (event->type == SDL_MOUSEMOTION) {
    CursorUsando[0]=0;
    if (mousemovidox>=screen->w-40) CursorUsando[0]=1;
    else if (mousemovidox<=40) CursorUsando[0]=2;
    if (mousemovidoy>=screen->h-40) CursorUsando[0]+=6;
    else if (mousemovidoy<=40) CursorUsando[0]+=3;
    if (CursorUsando[0]) CursorUsando[0]+=7;
  }
  else if ((event->type == SDL_MOUSEBUTTONDOWN) && (event->button.button == SDL_BUTTON_LEFT)) {
    modoContrucao.ativo=1;
    ModoConstrucao_getMouseParede(&modoContrucao.x_click, &modoContrucao.y_click);
  }
  else if ((event->type == SDL_MOUSEBUTTONUP) && (event->button.button == SDL_BUTTON_LEFT)) {
    if ((modoContrucao.ativo) && (CursorUsando[0]!=1)) {
      if (modoContrucao.tipo == 'i')
        ModoConstrucao_AdicionarParede(modoContrucao.tipo);
      else
        ModoConstrucao_RemoveParede();
    }

    modoContrucao.ativo=0;


    if (CursorUsando[0]==1) CursorUsando[0]=0;
  }
  else if ((event->type == SDL_MOUSEBUTTONDOWN) && (event->button.button == SDL_BUTTON_RIGHT)) {
    if (modoContrucao.ativo) modoContrucao.ativo=0;
  }
  else if (event->key.keysym.sym == SDLK_d) {
    modoContrucao.tipo='r';
  }
  else if (event->key.keysym.sym == SDLK_i) {
    modoContrucao.tipo='i';
  }
}
/*
5  3  4
2  0  1
8  6  7
*/
void Tela_ModContr_Depois_Eventos() {
  if (CursorUsando[0]>=8) {
    int cima=(CursorUsando[0]-7)/3;
    int lado=(CursorUsando[0]-7)%3;

    if (cima==1) { if (ypos>6) ypos-=6; }
    else if (cima==2) ypos+=6;
    if (lado==1) xpos+=6;
    else if (lado==2) { if (xpos>6) xpos-=6; }
  }
}

void Tela_ModContr_Iniciar() {
  modoContrucao.tipo='i';
}
