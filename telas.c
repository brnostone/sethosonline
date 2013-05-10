#include <stdio.h>

#include "Header/GUI.h"
#include "Header/tela_carregar.h"
#include "Header/tela_jogo.h"
#include "Header/tela_modoConstrucao.h"
#include "Header/telas.h"

struct tela *telaAtual=NULL;
Lista *prim_Tela=NULL;

int numTelas=0;
int tela_Atual=0;

int Tela_Acao(int id,char acao) {
  static int opcao=NAO_MUDAR_ID;

  if (acao=='n') {
    telaAtual=(struct tela *) lista_acao('n',&prim_Tela,id,opcao,sizeof(struct tela));
    numTelas++;
  }
  else if (acao=='d') {
    telaAtual=(struct tela *) lista_acao('d',&prim_Tela,id,opcao,0);
    if (telaAtual) numTelas--;
  }
  else if (acao=='s') {
    telaAtual=(struct tela *) lista_acao('s',&prim_Tela,id,opcao,numTelas);
    return (!telaAtual)?0:1;
  }
  else if (acao=='z') {
    while (prim_Tela!=NULL)
      Tela_Acao(prim_Tela->id,'d');

    numTelas=0;
  }
  return 0;
}

void Tela_adicionar(int id, void *func_draw, void *func_eventos, void *func_depois, void *func_iniciar) {
  Tela_Acao(id,'n');
  telaAtual->draw=func_draw;
  telaAtual->evento=func_eventos;
  telaAtual->depois=func_depois;
  telaAtual->inicio=func_iniciar;

  if (tela_Atual)
    Tela_Acao(tela_Atual,'s');
}

void Tela_Iniciar() {
  GUI_Iniciar();

  Tela_adicionar(1,Tela_Carr_DrawScene,Tela_Carr_Eventos,NULL,NULL);
  Tela_adicionar(2,Tela_Jogo_DrawScene,Tela_Jogo_Eventos,Tela_Jogo_Depois_Eventos,Tela_Jogo_Iniciar);
  Tela_adicionar(3,Tela_ModContr_DrawScene,Tela_ModContr_Eventos,Tela_ModContr_Depois_Eventos,Tela_ModContr_Iniciar);
}

void Tela_Fim() {
  Tela_Acao(0,'z');
  tela_Atual=0;

  GUI_libera(&prim_GUI);
}

void Tela_Evento(SDL_Event *evnt) {
  if ((!GUI_Evento(evnt,0,0,'p')) && (telaAtual->evento))
    (*telaAtual->evento)(evnt);
}

void Tela_Draw() {
  if (telaAtual->draw)
    (*telaAtual->draw)();
  GUI_Draw(0,0,prim_GUI);
}

void Tela_Depois() {
  if (telaAtual->depois)
    (*telaAtual->depois)();
  GUI_Depois();
}

void Tela_Selecionar(int id) {
  tela_Atual=id;
  Tela_Acao(tela_Atual,'s');
  if (telaAtual->inicio)
    (*telaAtual->inicio)();
}
