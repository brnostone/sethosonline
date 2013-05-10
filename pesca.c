#include <math.h>
#include <SDL/SDL.h>

#include "Header/personagem.h"
#include "Header/log.h"
#include "Header/equipamentos.h"
#include "Header/global.h"
#include "Header/mapas.h"
#include "Header/msgs.h"
#include "Header/guiitens.h"
#include "Header/lightmap.h"
#include "Header/pesca.h"

char flagpuchou=0;
char tutorialpesca=0;
int pescapucha=50;

void IA_Pesca() {
  if ((boias[1].acao==1) && (boias[1].ativa==1)) {
    if (peixe.timedurac<=SDL_GetTicks()/100) {
      peixe.timeanda=SDL_GetTicks()/100+5+rand()%5;
      peixe.timedurac=peixe.timeanda+rand()%5;
      peixe.velocidade=rand()%3;
      peixe.angulo=rand()%360;
    }
    if (peixe.timeanda<=SDL_GetTicks()/100) {
      boias[1].x+=peixe.forca*cos(peixe.angulo*M_PI/180);
      boias[1].y+=(-peixe.forca)*sin(peixe.angulo*M_PI/180);
//      char temppux=(3-(peixe.peso*5)/150);
      pescapucha-=(3-(peixe.peso*3)/150)+1;
      peixe.timeanda=SDL_GetTicks()/100+peixe.velocidade;

      if (tutorialpesca>0) { if (pescapucha<=70) { tutorialpesca=4; } }
      if (pescapucha<=0) {
        if (tutorialpesca>0) { tutorialpesca=6; }
        pescapucha=0;
        Error("O peixe escapou, tente novamente",ERRO_AVISO);
        boias[1].ativa=0;
      }

      float angoloux2=(personagem.x+50)-boias[1].x;
      float angolouy2=boias[1].y-(personagem.y+70);
      float tempfasda2=atan(angolouy2/angoloux2)/M_PI*180;
      int anguloasda2=tempfasda2+((angoloux2<0)?180:((angolouy2<0)?360:0));
      boias[1].fx=cos(anguloasda2*M_PI/180)*5.0f;
      boias[1].fy=sin(anguloasda2*M_PI/180)*-5.0f;
    }
    if (flagpuchou==1) {
      flagpuchou=0;
      pescapucha+=10;
      if (tutorialpesca>0) { if (pescapucha>=80) { tutorialpesca=5; } }
      if (pescapucha>=100) {
        if (tutorialpesca>0) { tutorialpesca=6; }
        pescapucha=100;
        Error("A linha arrebentou.",ERRO_AVISO);
        boias[1].ativa=0;
      }
    }
  }
}

void Draw_TutoPesca() {
  if (tutorialpesca>0) {
    Criar_Janela(300,85,200,30,0);
    if (tutorialpesca==1) { if (personagem.qual!=7) { DrawText(font,230,230,230,250,3,305,92,"Equipe a vara de pesca..."); } else { tutorialpesca=2; } }
    else if (tutorialpesca==2) { DrawText(font,230,230,230,250,3,305,92,"Clique na áqua."); }
    else if (tutorialpesca==3) { if (boias[1].ativa==1) { DrawText(font,230,230,230,250,3,305,92,"Espere o peixe fisgar a isca."); } else { tutorialpesca=2; } }
    else if (tutorialpesca==4) { DrawText(font,230,230,230,250,3,305,92,"Aperte \"p\"..."); }
    else if (tutorialpesca==5) { DrawText(font,230,230,230,250,3,305,92,"Espere o peixe se acalmar."); }
    else if (tutorialpesca==6) { DrawText(font,230,230,230,250,3,305,92,"Tente denovo e fique atento as dicas."); }
  }
}

void Draw_Boias() {
  int tempasda;
  for (tempasda=0;tempasda<10;tempasda++) {
    if (boias[tempasda].ativa==1) {
      if (tempasda!=0) {
        if ((personagem.qual!=7) || (personagem.acao!=9)) {
          boias[tempasda].ativa=0;
          personagem.acao=0;
          tempoparado=(SDL_GetTicks()/1000)+5;
        }
        if (boias[tempasda].acao==0) {
          boias[tempasda].imagem=0;
          if (boias[tempasda].timecheck<=SDL_GetTicks()/100) {
            if (rand()%4==0) {
              boias[tempasda].acao=1;
              if (boias[tempasda].idquem==personagem.id) {
                if (tutorialpesca>0)
                  tutorialpesca=4;
              }
              if (tempasda==1) {
                peixe.forca=2+rand()%4;
                peixe.timeanda=SDL_GetTicks()/100+5+rand()%5;
                peixe.timedurac=peixe.timeanda+rand()%5;
                peixe.velocidade=rand()%3;
                peixe.peso=rand()%145+5;
                peixe.angulo=rand()%360;
                pescapucha=50;
              }
            }
            else {
              boias[tempasda].acao=0;
              boias[tempasda].timecheck=(SDL_GetTicks()/100)+rand()%40;
            }
          }
        }
        if ((mapcaminhar[(int)((int)(boias[1].y)/16)][(int)((int)(boias[1].x)/16)]==1) || (mapcaminhar[(int)((int)(boias[1].y)/16)][(int)((int)(boias[1].x)/16)]==8)) {
          boias[1].ativa=0;
          personagem.acao=0;
          personagem.imagem=0;
          if (boias[1].acao==1) {
            Msgs_adicionar(9,NULL);

            if (!colocaritem_procurar(17,1,1))
              Error("Inventario cheio!",ERRO_AVISO);

            if (tutorialpesca>0)
              tutorialpesca=-1;
          }
        }
      }

      DrawImg_LightMap(boia,(int)(boias[tempasda].x-15)-xpos,(int)(boias[tempasda].y-11)-ypos,32,15,boias[tempasda].imagem*32,0);
      boias[tempasda].imagem++;
      if (boias[tempasda].imagem>=15) { boias[tempasda].imagem=0; }
    }
  }
}
