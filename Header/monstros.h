/*
 * monstro.h
 *
 *  Created on: 02/10/2009
 *      Author: bruno
 */

#ifndef MONSTROS_H_
#define MONSTROS_H_

  #include "pathfinding.h"
  #include "estruturas.h"

  struct monstro {
    const char *nome;
    char qual;
    char imagem;
    char lado;
    char acao;
    char seguindo;

    int x;
    int y;

    int vida;
    int timetempo;
    pathfinder pathFind;
  };

  struct monstro *monstroatual;

  Lista *primmonstro;

  int nummonstro;

  int monsterlacao(int id,char acao);

  void criar_monstros(int posx,int posy,char qual,char lado,char acao);
  void draw_monstros(int id);

  void IA_Monstro();

  void colocaritemchao(int posatx,int posaty);

#endif /* MONSTROS_H_ */
