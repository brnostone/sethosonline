/*
 * colisao.h
 *
 *  Created on: 02/10/2009
 *      Author: bruno
 */

#ifndef COLISAO_H_
#define COLISAO_H_

  struct {
    char ativado;
    char tipo;
    int valor;
    int posx;
    int posy;
    int alfa;
  } DanoTirado[31];

  void danonosmostr();

  int checararrowcolide(int x, int y,int lado);
  void colide_magic();

  int Verif_Colisao(int x, int y, int w, int h, int maisx, int maisy, int tamx, int tamy,char lado);

#endif /* COLISAO_H_ */
