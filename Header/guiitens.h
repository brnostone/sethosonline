/*
 * guiitens.h
 *
 *  Created on: 03/10/2009
 *      Author: bruno
 */

#ifndef GUIITENS_H_
#define GUIITENS_H_

  void colocaritem(char x,char y,int type,int qual,int add,char opcao);
  int checarsecabe(char x,char y,char w,char h,char qual);
  void retiraritem(int numero,int opcao);

  int colocaritem_procurar(int tipo, int qual, int add);

//TODO: verificar se não pode remover numeroitennm2
  int numeroitennm2;

  int numeroitem[3];

  int itemnumeroeh[49][3];
  int itemvende_temp[49][3];
  int itembau_numero[98][3];

  int itens[7][7];

  int vendetrocatemp[7][7];

  int itensbau[14][7];

#endif /* GUIITENS_H_ */
