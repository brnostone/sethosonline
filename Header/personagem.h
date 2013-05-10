/*
 * personagem.h
 *
 *  Created on: 02/10/2009
 *      Author: bruno
 */

#ifndef PERSONAGEM_H_
#define PERSONAGEM_H_

  #include "balao.h"
  #include "pathfinding.h"

  #define MAX_FORCA 100
  #define MAX_AGILIDADE 100
  #define MAX_VITALIDADE 100
  #define MAX_INTELIGENCIA 100

  struct boneco {
    char *nome;
    char *guild;
    char type;
    char qual;
    char imagem;
    char lado;
    char acao;
    char aura;
    char auramom;
    char SegueOq;
    char levelup;
    int x;
    int y;
    int id;
    int vida;
    int auraimagem;
    int SegueID;
    pathfinder pathFind;

    struct baloes balao;
  } personagem;

  struct {
    unsigned int forca;
    unsigned int agilidade;
    unsigned int vitalidade;
    unsigned int inteligencia;
    unsigned int dinheiro;
    unsigned int level;
    unsigned int experiencia;
    unsigned int nextlevelexp;
    unsigned int pontos;
    unsigned int mana;
    unsigned int estamina;
  } meusstatsua;

  char tempoparado;

  void drawpersonagem();
  void Personagem_Imagens();

#endif /* PERSONAGEM_H_ */
