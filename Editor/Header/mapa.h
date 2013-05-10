/*
 * mapa.h
 *
 *  Created on: 02/10/2009
 *      Author: bruno
 */

#ifndef MAPA_H_
#define MAPA_H_

  #define MAPA_PATHFIND_VEZES_X 4
  #define MAPA_PATHFIND_VEZES_Y 3

  #define TAM_MAPA_INICIAL_X 40
  #define TAM_MAPA_INICIAL_Y 40

  int map_sizex;
  int map_sizey;
  int qualmapa[5][3];

  unsigned char **mapcaminhar;
  unsigned char **map;
  unsigned char **map2;
  unsigned char **tipochao;
  unsigned char **tipochao2;
  unsigned char **mapobjetos;
  unsigned char **mapobjetostipo;

  void alocarMemMap(int rex,int rey);
  void salvarmap(char *arquivo);
  void lermapafile(char *arquivo);

#endif /* MAPA_H_ */
