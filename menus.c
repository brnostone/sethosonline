#include <stdio.h>
#include <string.h>

#include "Header/guiitens.h"
#include "Header/menusjogo.h"
#include "Header/log.h"
#include "Header/msgs.h"
#include "Header/equipamentos.h"
#include "Header/npcs.h"
#include "Header/menus.h"

char str_temp[256];

int Info_Menu(char oq,char acao) {
  int retorno=0;
  switch (menus.qual) {
    case 1:{
      if (acao==1) {
        if (oq=='n') { retorno=3; }
        else if (oq=='t') { retorno=127; }
        else if (oq==1) { strcpy(str_temp,"Comprar/Vender"); }
        else if (oq==2) { strcpy(str_temp,"Reparar itens"); }
        else if (oq==3) { strcpy(str_temp,"Nada..."); }
      }
      else {
        if (oq==1) {
          memset(vendetrocatemp, 0, sizeof(vendetrocatemp));
          memset(itemvende_temp, 0, sizeof(itemvende_temp));
          numeroitem[1]=0;

          colocaritem(0,0,4,1,1,2);
          colocaritem(1,0,4,2,1,2);
          colocaritem(2,0,4,3,1,2);
          colocaritem(3,0,4,4,1,2);
          colocaritem(4,0,4,5,1,2);
          colocaritem(5,0,5,1,1,2);
          colocaritem(6,0,5,2,1,2);
          colocaritem(0,2,5,3,1,2);
          colocaritem(1,2,5,4,1,2);
          colocaritem(2,2,5,5,1,2);
          colocaritem(3,2,6,1,1,2);
          colocaritem(4,2,6,2,1,2);
          colocaritem(5,2,6,3,1,2);
          colocaritem(6,2,6,4,1,2);
          colocaritem(0,4,6,5,1,2);
          colocaritem(1,4,8,1,1,2);
          colocaritem(2,4,8,2,1,2);
          colocaritem(3,4,8,3,1,2);
          colocaritem(4,4,8,4,1,2);
          colocaritem(5,4,8,5,1,2);

          menus.ativo=0;
          mostrarmenu=1;
          inventarioon=1;
          charmenuon=0;
        }
        else if (oq==2) { menus.ativo=0; Error("Opção ainda não implementada!",ERRO_AVISO); }
        else if (oq==3) { menus.ativo=0; }
      }
      break;
    }
    case 2:{
      if (acao==1) {
        if (oq=='n') { retorno=4; }
        else if (oq=='t') { retorno=157; } //127
        else if (oq==1) { strcpy(str_temp,"Aprender a pescar"); }
        else if (oq==2) { strcpy(str_temp,"Comprar/Vender"); }
        else if (oq==3) { strcpy(str_temp,"Reparar a vara de pesca"); }
        else if (oq==4) { strcpy(str_temp,"Nada..."); }
      }
      else {
        if (oq==1)
          Msgs_adicionar(1,NULL);
        else if (oq==2) {
          memset(vendetrocatemp, 0, sizeof(vendetrocatemp));
          memset(itemvende_temp, 0, sizeof(itemvende_temp));
          numeroitem[1]=0;

          colocaritem(0,0,16,1,1,2);
          menus.ativo=0; mostrarmenu=1; inventarioon=1; charmenuon=0;
        }
        else if (oq==3) { menus.ativo=0; Error("Opção ainda não implementada!",ERRO_AVISO); }
        else if (oq==4) { menus.ativo=0; }
      }
      break;
    }
    case 3:{
      if (acao==1) {
        if (oq=='n') { retorno=3; }
        else if (oq=='t') { retorno=127; }
        else if (oq==1) { strcpy(str_temp,"Comprar/Vender"); }
        else if (oq==2) { strcpy(str_temp,"Reparar itens"); }
        else if (oq==3) { strcpy(str_temp,"Nada..."); }
      }
      else {
        if (oq==1) {
          memset(vendetrocatemp, 0, sizeof(vendetrocatemp));
          memset(itemvende_temp, 0, sizeof(itemvende_temp));
          numeroitem[1]=0;

          colocaritem(0,0,7,1,1,2);
          colocaritem(1,0,7,2,1,2);
          colocaritem(2,0,7,3,1,2);
          colocaritem(3,0,7,4,1,2);
          colocaritem(4,0,7,5,1,2);
          colocaritem(0,2,15,1,5,2);
          colocaritem(1,2,15,2,5,2);
          colocaritem(2,2,15,3,5,2);
          colocaritem(3,2,15,4,5,2);
          colocaritem(4,2,15,5,5,2);
          colocaritem(5,2,15,6,5,2);
          colocaritem(6,2,15,7,1,2);
          colocaritem(0,3,15,8,1,2);
          colocaritem(1,3,15,9,1,2);
          colocaritem(2,3,15,10,1,2);
          colocaritem(3,3,15,11,1,2);
          colocaritem(4,3,15,12,1,2);
          colocaritem(5,3,15,13,1,2);
          colocaritem(6,3,15,14,1,2);
          colocaritem(0,4,15,15,1,2);
          colocaritem(1,4,15,16,1,2);
          colocaritem(2,4,15,17,1,2);
          colocaritem(3,4,15,18,1,2);


          menus.ativo=0; mostrarmenu=1; inventarioon=1; charmenuon=0;
        }
        else if (oq==2) { menus.ativo=0; Error("Opção ainda não implementada!",ERRO_AVISO); }
        else if (oq==3) { menus.ativo=0; }
      }
      break;
    }
    default: printf("Menu %d nao existe\n",menus.qual);
  }
  return retorno;
}

void Draw_Menu() {
  if (menus.ativo==1) {
    char nomeNpc[256];
    int Temp_Num=Info_Menu('n',1),Temp_Itens;
    int pox,poy;

    poy=300-(Temp_Num*15+54)/2;
    pox=400-Info_Menu('t',1)/2;
    Criar_Janela(pox,poy,Info_Menu('t',1),Temp_Num*15+54,1);
    Nome_Npcs(menus.nomequem+1,nomeNpc);
    DrawText(font,78,238,172,250,3,pox+8,poy+4,"%s",nomeNpc);
    DrawText(font,250,250,250,250,3,pox+5,poy+20,"O que você deseja?");
    for (Temp_Itens=0;Temp_Itens<Temp_Num;Temp_Itens++) {
      Info_Menu(Temp_Itens+1,1);
      if (menus.itemsel%(Temp_Num+1)==Temp_Itens+1) {
        if (menus.itemsel>Temp_Num) {
          fillRectangle(pox+10,poy+46+17*Temp_Itens,3,3,250,0,0,255);
          DrawText(font,250,0,0,250,3,pox+18,poy+40+17*Temp_Itens,"%s",str_temp);
        }
        else {
          fillRectangle(pox+10,poy+46+17*Temp_Itens,3,3,250,109,39,255);
          DrawText(font,250,170,39,250,3,pox+18,poy+40+17*Temp_Itens,"%s",str_temp);
        }
      }
      else {
        fillRectangle(pox+10,poy+46+17*Temp_Itens,3,3,250,250,250,255);
        DrawText(font,250,250,233,250,3,pox+18,poy+40+17*Temp_Itens,"%s",str_temp);
      }
    }
  }
}
