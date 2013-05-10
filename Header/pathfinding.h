/*
 * pathfinding.h
 *
 *  Created on: 02/10/2009
 *      Author: bruno
 */

#ifndef PATHFINDING_H_
#define PATHFINDING_H_

  #include "util.h"

  #define PATH_ACHOU 1
  #define PATH_NAO_ACHOU 0

  #define PATH_CAMINHO 1
  #define PATH_PAREDE 0

  #define PATH_TIPO_PERSONAGEM 1
  #define PATH_TIPO_MONSTRO 2

  #define PATH_CAMINHO_INTERACAO 9

  #define MAPA_PATHFIND_VEZES_X 4
  #define MAPA_PATHFIND_VEZES_Y 3

  #define MAPA_PATHFIND mapcaminhar

  typedef struct {
    int atualX;
    int atualY;

    int destinoX;
    int destinoY;

    int tamanho;
    int posicao;

    int tipo;

    int interacao_id;

    char achou;
    char chegou;

    posXY_int *dest;
  } pathfinder;

  int pathFind(int destinoX, int destinoY, pathfinder *path, unsigned char **mapa, int mapaW, int mapaH);
  int pathFindPadrao(int destinoX, int destinoY, pathfinder *path);
  void pathMove(pathfinder *path,char *lado);

  void fimPathfind();

#endif /* PATHFINDING_H_ */
