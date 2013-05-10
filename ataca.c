#include <math.h>

#include "Header/flechas.h"
#include "Header/magicas.h"
#include "Header/caracteristicas.h"
#include "Header/global.h"
#include "Header/personagem.h"
#include "Header/mapas.h"
#include "Header/ataca.h"

int verquanto(char xory,char lado,char botao,char qual) {
  if ((botao==1) && (qual==3)) {
    if (lado == 0) { return ((xory=='x')?79:18); }
    if (lado == 1) { return ((xory=='x')?27:-15); }
    if (lado == 2) { return ((xory=='x')?41:62); }
    if (lado == 3) { return ((xory=='x')?-16:28); }
    if (lado == 4) { return ((xory=='x')?-13:5); }
    if (lado == 5) { return ((xory=='x')?57:-7); }
    if (lado == 6) { return ((xory=='x')?72:42); }
    if (lado == 7) { return ((xory=='x')?5:51); }
  }
  else if ((botao==3) && (qual==4)) {
    if (lado == 0) { return ((xory=='x')?89:41); }
    if (lado == 1) { return ((xory=='x')?53:3); }
    if (lado == 2) { return ((xory=='x')?35:73); }
    if (lado == 3) { return ((xory=='x')?2:29); }
    if (lado == 4) { return ((xory=='x')?18:8); }
    if (lado == 5) { return ((xory=='x')?83:16); }
    if (lado == 6) { return ((xory=='x')?76:64); }
    if (lado == 7) { return ((xory=='x')?5:53); }
  }
  return 0;
}

double arrumadorangulo(double angulo) {
  if (angulo<0) angulo+=360;
  else if (angulo>360) angulo-=360;
  return angulo;
}

int arrumadordelado(int lado) {
  int retorno=0;
  if (lado==7) { retorno=0; }
  else if (lado==0) { retorno=5; }
  else if (lado==1) { retorno=1; }
  else if (lado==2) { retorno=4; }
  else if (lado==3) { retorno=3; }
  else if (lado==4) { retorno=7; }
  else if (lado==5) { retorno=2; }
  else if (lado==6) { retorno=6; }
  return retorno;
}

int arrumaragoliuasd(int personx,int persony, int mosntoasx,int mosntoasy) {
  double angoloux=mosntoasx-personx;
  double angolouy=persony-mosntoasy;
  double tempfasda=atan(angolouy/angoloux)/M_PI*180;
  tempfasda+=((angoloux<0)?180:((angolouy<0)?360:0));
  return arrumadordelado(arrumadorangulo(tempfasda-22.5)/45);
}

void atacar(char botao,int posicaox,int posicaoy) {
  if (botao==1) {
    if (personagem.qual==3) {
      /*
      arrowtemp.posx=(double)personagem.x+verquanto('x',personagem.lado,1,3);
      arrowtemp.posy=(double)personagem.y+verquanto('y',personagem.lado,1,3);

      double angoloux2=posicaox-(arrowtemp.posx-xpos);
      double angolouy2=(arrowtemp.posy-ypos)-posicaoy;
      double tempfasda2=atan(angolouy2/angoloux2)/M_PI*180;
      double anguloasda2=tempfasda2+((angoloux2<0)?180:((angolouy2<0)?360:0));

      arrowtemp.mposx=(double)cos(anguloasda2*M_PI/180)*16;
      arrowtemp.mposy=(double)sin(anguloasda2*M_PI/180)*-16;
      //printf("%f %f %f\n",arrowtemp.mposx,arrowtemp.mposy,anguloasda2);
      arrowtemp.lado=(int)(arrumadorangulo((int)(anguloasda2+5.625))/11.25);
      */

      double angoloux2=posicaox-(personagem.x-xpos+verquanto('x',personagem.lado,1,3));
      double angolouy2=(personagem.y-ypos+verquanto('y',personagem.lado,1,3)+46)-posicaoy;
      double tempfasda2=(double)atan(angolouy2/angoloux2)/M_PI*180;
      double anguloasda2=(double)tempfasda2+((angoloux2<0)?180:((angolouy2<0)?360:0));
      arrowtemp.posx=personagem.x+verquanto('x',personagem.lado,1,3);
      arrowtemp.posy=personagem.y+verquanto('y',personagem.lado,1,3);
      arrowtemp.mposx=(double)cos(anguloasda2*M_PI/180)*15;
      arrowtemp.mposy=(double)sin(anguloasda2*M_PI/180)*-15;
      arrowtemp.lado=(int)(arrumadorangulo((anguloasda2+5.625))/11.25);
      if ((arrowtemp.lado>=32) || (arrowtemp.lado<0)) arrowtemp.lado=0;
      personagem.lado=arrumaragoliuasd(personagem.x+48,personagem.y+68,posicaox+xpos,posicaoy+ypos);
    }
  }
  else if (botao==3) {
    if (personagem.qual==4) {
      double angoloux2=mousemovidox-(personagem.x-xpos+48);
      double angolouy2=(personagem.y-ypos+68)-mousemovidoy;
      double tempfasda2=atan(angolouy2/angoloux2)/M_PI*180;
      int anguloasda2=tempfasda2+((angoloux2<0)?180:((angolouy2<0)?360:0));
      if (Info_Magic(magicasel,'v')!=0) {
        magictemp.posx=personagem.x+verquanto('x',personagem.lado,3,4)-Info_Magic(magicasel,1);
        magictemp.posy=personagem.y+verquanto('y',personagem.lado,3,4)-Info_Magic(magicasel,2);
      }
      else {
        magictemp.posx=mousemovidox+xpos-(Info_Magic(magicasel,'w')/2);
        magictemp.posy=mousemovidoy+ypos-Info_Magic(magicasel,'h');
      }
      magictemp.mposx=cos(anguloasda2*M_PI/180)*(Info_Magic(magicasel,'v'));
      magictemp.mposy=sin(anguloasda2*M_PI/180)*-(Info_Magic(magicasel,'v'));
      magictemp.lado=(int)(arrumadorangulo((int)(anguloasda2+5.625))/11.25);
      magictemp.qual=magicasel;
    }
  }
}
