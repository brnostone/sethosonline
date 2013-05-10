/*
 * fechas.c
 *
 *  Created on: 02/10/2009
 *      Author: bruno
 */

#include <stdio.h>

#include "Header/util.h"
#include "Header/colisao.h"
#include "Header/monstros.h"
#include "Header/opengl.h"
#include "Header/global.h"
#include "Header/mapas.h"
#include "Header/flechas.h"

Lista *primarrow=NULL;
struct arrow *arrowatual=NULL;

int numarrow=0;

int arrowacao(int id,char acao) {
  static int opcao=MUDAR_ID;

  if (acao=='n') {
    arrowatual=(struct arrow *) lista_acao('n',&primarrow,id,opcao,sizeof(struct arrow));
    numarrow++;
  }
  else if (acao=='d') {
    arrowatual=(struct arrow *) lista_acao('d',&primarrow,id,opcao,0);
    if (arrowatual) numarrow--;
  }
  else if (acao=='s') {
    arrowatual=(struct arrow *) lista_acao('s',&primarrow,id,opcao,numarrow);
    return (!arrowatual)?0:1;
  }
  return 0;
}

void ativar_arrow() {
  int codcolide=0;

  forList (struct arrow *, arrowTmp, primarrow) {
    arrowatual=arrowTmp;

    arrowatual->ativa=1;
    if (!arrowatual->excluir) {
      codcolide=Verif_Colisao((int)arrowatual->posx+arrowatual->mposx,(int)arrowatual->posy+arrowatual->mposy,27,50,(((arrowatual->lado/8)==3) || ((arrowatual->lado/8)==0))?1:0,2+arrowatual->lado/16,1,1,arrowatual->lado);
      if (codcolide) {
        if (codcolide>1) {
           monsterlacao(codcolide-1,'s');
           danonosmostr();
        }
        arrowatual->excluir=1;
      }
      arrowatual->posx+=arrowatual->mposx; arrowatual->posy+=arrowatual->mposy;
    }
  }
}

void deletar_arrow() {
  Lista *percorreLista=primarrow;
  while (percorreLista!=NULL) {
    if (((struct arrow *) percorreLista->d)->excluir) {
      arrowacao(percorreLista->id,'d');
      percorreLista=primarrow;
      continue;
    }
    percorreLista=percorreLista->prox;
  }
}

void draw_arrow(int id) {
  if (arrowacao(id,'s'))
    DrawIMG(flechas[(int)arrowatual->lado], (int)arrowatual->posx-xpos, (int)arrowatual->posy-ypos,32,64,0,0);
}

void criar_arrow(double posxx,double posyy,double mposxx,double mposyy,char lado2) {
  arrowacao(numarrow+1,'n');

  arrowatual->posx=posxx;
  arrowatual->posy=posyy;
  arrowatual->mposx=mposxx;
  arrowatual->mposy=mposyy;
  arrowatual->lado=lado2;
  arrowatual->ativa=1;
  arrowatual->excluir=0;
}
