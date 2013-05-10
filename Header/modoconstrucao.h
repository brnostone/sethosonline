/*
 * modoconstrucao.h
 *
 *  Created on: 04/10/2009
 *      Author: bruno
 */

#ifndef MODOCONSTRUCAO_H_
#define MODOCONSTRUCAO_H_

  struct {
    char ativo;
    char tipo;

    int x_click;
    int y_click;
    int qual;
    int lado;
  } modoContrucao;

  void ModoConstrucao_Start();

  void ModoConstrucao_draw();
  void ModoConstrucao_getMouseParede(int *pX, int *pY);

  void ModoConstrucao_AdicionarParede(char tipo);
  void ModoConstrucao_RemoveParede();

#endif /* MODOCONSTRUCAO_H_ */
