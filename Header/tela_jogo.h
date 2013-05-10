/*
 * tela_jogo.h
 *
 *  Created on: 02/10/2009
 *      Author: bruno
 */

#ifndef TELA_JOGO_H_
#define TELA_JOGO_H_

  #include <SDL/SDL.h>

  void Tela_Jogo_DrawScene();
  void Tela_Jogo_Eventos(SDL_Event *event);
  void Tela_Jogo_Depois_Eventos();
  void Tela_Jogo_Iniciar();

  void Tela_jogo_ChatAtivar();

#endif /* TELA_JOGO_H_ */
