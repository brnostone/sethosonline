/*
 * equipamentos.h
 *
 *  Created on: 02/10/2009
 *      Author: bruno
 */

#ifndef EQUIPAMENTOS_H_
#define EQUIPAMENTOS_H_

  struct {
    unsigned char helm[2];
    unsigned char armor[2];
    unsigned char mao1[2];
    unsigned char mao2[2];
    unsigned char mao1tipo;
    unsigned char mao2tipo;
    unsigned char amuleto[2];
    unsigned char anel1[2];
    unsigned char anel2[2];
    unsigned char braco1[2];
    unsigned char braco2[2];
    unsigned char luvas[2];
    unsigned char capa[2];
    unsigned char botas[2];
  } equipamentos;

  int itemlocalrapido[2][8];
  int itemnamao[3];
  char carregarar;

  int sizearmos(char type,char posicao);
  void colocaritens();
  void Criar_Janela(int x, int y,int w,int h,char tipo);
  void itemjuntomouse(int xx,int yy,int tipou,int qual,int add);
  int equimaent(int type,int qual,int add,char bnoius,char oq);
  void nomesdositens(int tipo, int qual, int add, char *nomeItem);
  void janeladeinfo( int x, int y, int tipo, int qual, int add);
  int opcoesdeitens(int qual,char oq,int add);

  int UsarItem(int tipo,int qual,int add);
  void UsarItemLocalRap(int id);

#endif /* EQUIPAMENTOS_H_ */
