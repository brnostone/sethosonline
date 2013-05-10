/*
 * mapas.h
 *
 *  Created on: 02/10/2009
 *      Author: bruno
 */

#ifndef MAPAS_H_
#define MAPAS_H_

  unsigned char **mapcaminhar;
  unsigned char **map;
  unsigned char **map2;
  unsigned char **tipochao;
  unsigned char **tipochao2;
  unsigned char **mapobjetos;
  unsigned char **mapobjetostipo;

  unsigned int itenschao[3][40][40];
  int qualmapa[5][3];

  int xpos;
  int ypos;

  int map_sizex;
  int map_sizey;

  int mapHeight;
  int mapWidth;

  void criarmap();
  void criarmap2();
  void criarmap3();

  void Alorcar_Mapa();
  void Liberar_Mapa();

  void lermapafile(char *text,int x, int y);
  void chamarPathFind(char evento);

#endif /* MAPAS_H_ */
