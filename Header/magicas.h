/*
 * magicas.h
 *
 *  Created on: 02/10/2009
 *      Author: bruno
 */

#ifndef MAGICAS_H_
#define MAGICAS_H_

  #include "estruturas.h"
  #include "global.h"

  struct magic {
    char lado;
    char mposx;
    char mposy;
    char qual;
    char imagem;
    char ativa;
    char deletar;

    int posx;
    int posy;
    int time;
  };

  struct {
    char lado;
    char mposx;
    char mposy;
    char qual;

    int posx;
    int posy;
  } magictemp;

  struct {
    char nummagic;
    char level;
    int experiencia;
  } minhasmagicas[NUM_MAGICS];

  int MagicNumAtual;
  int nummagic;
  int magicasel;

  struct magic *magicatual;
  Lista *primmagic;

  int magicacao(int id,char acao);

  void draw_magic(int id);
  void criar_magic(int posxx,int posyy,char mposxx,char mposyy,char lado2,char qual);

  void ativar_magic();
  void deletar_magic();

#endif /* MAGICAS_H_ */
