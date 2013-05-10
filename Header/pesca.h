/*
 * pesca.h
 *
 *  Created on: 04/10/2009
 *      Author: bruno
 */

#ifndef PESCA_H_
#define PESCA_H_

  struct {
    float forca;
    unsigned int peso;
    char velocidade;
    int timeanda;
    int timedurac;
    int angulo;
  } peixe;

  struct {
    char ativa;
    char imagem;
    char acao;
    float x;
    float y;
    float fx;
    float fy;
    int idquem;
    int timecheck;
  } boias[10];

  char tutorialpesca;
  int boiastemp[2];
  float boiastemp2[2];
  int pescapucha;
  char flagpuchou;

  void IA_Pesca();
  void Draw_TutoPesca();
  void Draw_Boias();

#endif /* PESCA_H_ */
