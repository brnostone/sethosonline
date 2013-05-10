#include "Header/mapas.h"
#include "Header/caracteristicas.h"
#include "Header/guiitens.h"
#include "Header/global.h"
#include "Header/log.h"
#include "Header/interacao.h"

#define TEMPO_INTERACAO_SEG 2

int interacao_caract(int qual,char oq) {
  int returno=0;
  //apartir desta imagem vai mudar de cor
  if (oq=='a') {
    if (qual==1) returno=6;
    else if (qual==2) returno=12;
  }
  //mais quanto para mudar de cor
  if (oq=='m') {
    if (qual==1) returno=5;
    else if (qual==2) returno=1;
  }
  return returno;
}

void interacao_int() {
  int tempx,tempy,cont=0;
  for (tempy=0;tempy<map_sizey;tempy++) {
    for (tempx=0;tempx<map_sizex;tempx++) {
      if (mapobjetostipo[tempy][tempx]/NUM_TITLE==4) {
        cont++;
      }
    }
  }
  inter_position.quantidade=cont;
  inter_position.tipo=(unsigned char **) calloc(cont,sizeof(unsigned char *));
  inter_position.qual=(unsigned char **) calloc(cont,sizeof(unsigned char *));

  inter_position.posicao=(posXY_int *) calloc(cont,sizeof(posXY_int));

  cont=0;
  for (tempy=0;tempy<map_sizey;tempy++) {
    for (tempx=0;tempx<map_sizex;tempx++) {
      if (mapobjetostipo[tempy][tempx]/NUM_TITLE==4) {
        inter_position.tipo[cont]=&mapobjetostipo[tempy][tempx];
        inter_position.qual[cont]=&mapobjetos[tempy][tempx];

        inter_position.posicao[cont].x=tempx;
        inter_position.posicao[cont].y=tempy;

        cont++;
      }
    }
  }
}

void interacao_crescer() {
  if (inter_position.tempo<SDL_GetTicks()/1000) {
    int cont,tempoas;
    for (cont=0;cont<inter_position.quantidade;cont++) {
      tempoas=*inter_position.tipo[cont]-((*inter_position.tipo[cont]/NUM_TITLE)*NUM_TITLE);
      if (*inter_position.qual[cont]-1<interacao_caract(tempoas,'a'))
        (*inter_position.qual[cont])++;
    }
    inter_position.tempo=SDL_GetTicks()/1000+TEMPO_INTERACAO_SEG;
  }
}

int interacao_acao(int tipo,char qual) {
  int returno=0;
  if (tipo==1) {
    if (qual=='t') returno=15;
    else if (qual=='q') returno=20;
    else if (qual=='a') returno=1;
    else if (qual=='o') returno=1;
  }
  else if (tipo==2) {
    if (qual=='t') returno=15;
    else if (qual=='q') returno=21;
    else if (qual=='a') returno=1;
    else if (qual=='o') returno=1;
  }
  return returno;
}

void interacao_pegar(int inter) {
  int cont=*inter_position.tipo[inter];
  cont=cont-((cont/NUM_TITLE)*NUM_TITLE);

  if (*inter_position.qual[inter]>interacao_caract(cont,'a')) {
    int tipo,qual,add;
    tipo=interacao_acao(cont,'t');
    qual=interacao_acao(cont,'q');
    add=interacao_acao(cont,'a');
    switch (interacao_acao(cont,'o')) {
      case 1: {
        if (colocaritem_procurar(tipo,qual,add))
          (*inter_position.qual[inter])++;
        else
          Error("Inventário cheio.",ERRO_AVISO);
        break;
      }
    }
    if (*inter_position.qual[inter]>interacao_caract(cont,'a')+interacao_caract(cont,'m'))
      *inter_position.qual[inter]=1;
  }
}

int interacao_verifRaio(int id, int x, int y) {
  if ((id >= inter_position.quantidade) || (id < 0)) return 0;

  int tipo = *inter_position.tipo[id];
  tipo=tipo-((tipo/NUM_TITLE)*NUM_TITLE);

  int quadrados=tamanhoInteracao(tipo,'q');
  int posX=(inter_position.posicao[id].x*64)/16+tamanhoInteracao(tipo,'a');
  int posY=(inter_position.posicao[id].y*48)/16+tamanhoInteracao(tipo,'b');

  //Verfica se esta dentro do raio do objeto de interacao
  return ((x >= posX) && (x <= posX+quadrados) && (y >= posY) && (y <= posY+quadrados));
}
