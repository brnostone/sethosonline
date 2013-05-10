/*
 * npcs.h
 *
 *  Created on: 04/10/2009
 *      Author: bruno
 */

#ifndef NPCS_H_
#define NPCS_H_

  #include "global.h"

  struct {
    char tipo;
    char ativo;
    char imagem;
    char acao;
    char lado;

    int posx;
    int posy;
    int timetempo;
  } npcs[NUM_NPCS];

  void Nome_Npcs(char tipo, char *nomeNPC);
  int info_npcs(int qual,int oq);
  void draw_npcs(int qual);

#endif /* NPCS_H_ */
