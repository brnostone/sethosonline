/*
 * flechas.h
 *
 *  Created on: 03/10/2009
 *      Author: bruno
 */

#ifndef FLECHAS_H_
#define FLECHAS_H_
  #include "estruturas.h"

  struct {
    char lado;
    double posx;
    double posy;
    double mposx;
    double mposy;
  } arrowtemp;


  struct arrow {
    char ativa;
    char lado;
    char excluir;

    double posx;
    double posy;

    double mposx;
    double mposy;
  };

  struct arrow *arrowatual;

  Lista *primarrow;

  int numarrow;

  int arrowacao(int id,char acao);

  void draw_arrow(int id);
  void criar_arrow(double posxx,double posyy,double mposxx,double mposyy,char lado2);

  void ativar_arrow();
  void deletar_arrow();

#endif /* FLECHAS_H_ */
