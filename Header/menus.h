/*
 * menus.h
 *
 *  Created on: 04/10/2009
 *      Author: bruno
 */

#ifndef MENUS_H_
#define MENUS_H_

  struct {
    char ativo;
    char qual;
    char itemsel;
    char nomequem;
  } menus;

  void Draw_Menu();
  int Info_Menu(char oq,char acao);

#endif /* MENUS_H_ */
