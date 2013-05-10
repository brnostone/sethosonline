/*
 * magicas.c
 *
 *  Created on: 02/10/2009
 *      Author: bruno
 */

#include <stdio.h>

#include "Header/colisao.h"
#include "Header/caracteristicas.h"
#include "Header/util.h"
#include "Header/mapas.h"
#include "Header/magicas.h"

struct magic *magicatual=NULL;

int MagicNumAtual=0;
int nummagic=0;
int magicasel=0;

int magicacao(int id,char acao) {
  static int opcao=MUDAR_ID;

  if (acao=='n') {
    magicatual=(struct magic *) lista_acao('n',&primmagic,id,opcao,sizeof(struct magic));
    nummagic++;
  }
  else if (acao=='d') {
    magicatual=(struct magic *) lista_acao('d',&primmagic,id,opcao,0);
    if (magicatual) nummagic--;
  }
  else if (acao=='s') {
    magicatual=(struct magic *) lista_acao('s',&primmagic,id,opcao,nummagic);
    return (!magicatual)?0:1;
  }
  return 0;
}

void ativar_magic() {
  forList (struct magic *, magicTmp, primmagic) {
    magicatual= magicTmp;

    magicatual->ativa=1;

    if (!magicatual->deletar) {
      if (Info_Magic(magicatual->qual,'v') > 0) {
        magicatual->posx+=magicatual->mposx;
        magicatual->posy+=magicatual->mposy;
      }
    }
  }
}

void deletar_magic() {
  Lista *percorreLista=primmagic;

  while (percorreLista!=NULL) {
    magicatual=(struct magic *) percorreLista->d;

    colide_magic();

    if (!magicatual->deletar) {
      magicatual->imagem++;
      if (magicatual->imagem>Info_Magic(magicatual->qual,'i'))
        magicatual->imagem=0;
    }
    else {
      //isto é feito para não incrementar a imagem varias vezes.
      if (magicatual->ativa!=6) {
        magicatual->imagem++;
        magicatual->ativa=6;
      /*  if (Info_Magic(magicatual->qual,'m')) {
          magicacao(magicatual->id,'d');
          magicatual=primmagic;
          continue;
        }*/
      }
      if (magicatual->imagem>Info_Magic(magicatual->qual,'n')) {
        magicacao(percorreLista->id,'d');
        percorreLista=primmagic;
        continue;
      }
    }
    percorreLista=percorreLista->prox;
  }
}

void draw_magic(int id) {
  if (magicacao(id,'s')) {
    if (magicatual->imagem>=0)
      DrawIMG(magicas[magicatual->qual-1], magicatual->posx-xpos, magicatual->posy-ypos,Info_Magic(magicatual->qual,'w'),Info_Magic(magicatual->qual,'h'),Info_Magic(magicatual->qual,'w')*magicatual->imagem,Info_Magic(magicatual->qual,'h')*magicatual->lado);
  }
}

void criar_magic(int posxx,int posyy,char mposxx,char mposyy,char lado2,char qual) {
  magicacao(nummagic+1,'n');
  magicatual->posx=posxx;
  magicatual->posy=posyy;
  magicatual->mposx=mposxx;
  magicatual->mposy=mposyy;
  magicatual->lado=0;
  magicatual->time=0;
  magicatual->qual=qual;
  magicatual->imagem=0;
  magicatual->deletar=Info_Magic(qual,'s');
  magicatual->ativa=1;
  if (qual==3) {
    int temp;
    for (temp=1;temp<=5;temp++) {
      magicacao(nummagic+1,'n');
      magicatual->posx=posxx+mposxx*(temp*2);
      magicatual->posy=posyy+mposyy*(temp*2);
      magicatual->mposx=mposxx;
      magicatual->mposy=mposyy;
      magicatual->lado=0;
      magicatual->time=0;
      magicatual->qual=qual;
      magicatual->imagem=-(temp*2);
      magicatual->deletar=Info_Magic(qual,'s');
      magicatual->ativa=1;
    }
  }
}
