/*
 * interacao.h
 *
 *  Created on: 03/10/2009
 *      Author: bruno
 */

#ifndef INTERACAO_H_
#define INTERACAO_H_

  #include "util.h"

  struct {
    int quantidade;
    int tempo;

    unsigned char **tipo;
    unsigned char **qual;
    posXY_int *posicao;
  } inter_position;

  void interacao_int();

  int interacao_caract(int qual, char oq);
  int interacao_verifRaio(int id, int x, int y);
  void interacao_pegar(int inter);
  void interacao_crescer();

#endif /* INTERACAO_H_ */
