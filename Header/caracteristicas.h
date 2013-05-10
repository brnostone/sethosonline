/*
 * caracteristicas.h
 *
 *  Created on: 02/10/2009
 *      Author: bruno
 */

#ifndef CARACTERISTICAS_H_
#define CARACTERISTICAS_H_

  int tamanhoObjetos(char tipo,char oq);
  int tamanhoParedes(int tipo,char oq);
  int tamanhoCasa(char tipo,char oq);
  int tamanhoInteracao(char tipo,char oq);

  void nomedasmagicas(char opcao, char qual, char *nomeMagic);

  int imagemdereset(char qual,char acao);
  int monstroimreset(char qual,char acao);

  int imagemtamanho(char qual,char acao);
  int imagtamonstro(char qual,char acao);

  int Info_Magic(int tipo,char oq);
  int Info_Colid_Magic(int tipo,char cat,char oq);

#endif /* CARACTERISTICAS_H_ */
