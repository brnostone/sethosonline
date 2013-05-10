/*
 * balao.h
 *
 *  Created on: 02/10/2009
 *      Author: bruno
 */

#ifndef BALAO_H_
#define BALAO_H_

  #include "fonte.h"

  struct baloes {
    char ativo;
    unsigned char alpha;
    char msg[256];
    int timeout;
  };

  void Draw_Balao(Fonte *fonte, int x, int y,int largura,int alpha, char *msg);
  void Draw_Baloes();
  void Baloes_SetTexto(char *texto);

#endif /* BALAO_H_ */
