/*
 * animais.h
 *
 *  Created on: 02/10/2009
 *      Author: bruno
 */

#ifndef ANIMAIS_H_
#define ANIMAIS_H_

  #include "estruturas.h"

  struct animal {
    int x;
    int y;
    unsigned char tipo;
    unsigned char imagem;
    unsigned char lado;
    unsigned char acao;
    char ativo;
  };

  struct animal *animalatual;
  Lista *primanimais;

  int animalacao(int id, char acao);

  void Criar_Animal(int posx, int posy, unsigned char tipo, unsigned char lado, unsigned char acao);
  void Draw_Animal(int id);
  void IA_Animal();

  int Info_Animal(int tipo, char oq);

#endif /* ANIMAIS_H_ */
