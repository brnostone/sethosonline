/*
 * load.h
 *
 *  Created on: 02/10/2009
 *      Author: bruno
 */

#ifndef LOAD_H_
#define LOAD_H_

  #include "global.h"

  struct {
    int loadperson[NUMERODEPERSONAGENS][8];
    int loadmonstro[QUANT_MONSTROS][6];
    int loadaura[6];
    int temp;
  } loadint;

  void LoadInteligent(char oq,int tipo,int acao);
  void CheckInteligent();

  void InitImages();
  void GraphicsInit(const char *caption, int width, int height, int bpp, char fullscreen);

  void limpaMemoria();

#endif /* LOAD_H_ */
