/*
 * tela.h
 *
 *  Created on: 03/10/2009
 *      Author: bruno
 */

#ifndef TELAS_H_
#define TELAS_H_

  #include <SDL/SDL.h>

  #include "estruturas.h"

  struct tela{
    void (*draw)();
    void (*evento)(SDL_Event *);
    void (*depois)();
    void (*inicio)();
  };

  struct tela *telaAtual;
  Lista *prim_Tela;

  void Tela_adicionar(int id, void *func_draw, void *func_eventos, void *func_depois, void *func_iniciar);

  void Tela_Iniciar();
  void Tela_Fim();

  void Tela_Evento(SDL_Event *evnt);
  void Tela_Draw();
  void Tela_Depois();
  void Tela_Selecionar(int id);

  int tela_Atual;

#endif /* TELAS_H_ */
