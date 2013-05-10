#include <math.h>

#include "Header/opengl.h"
#include "Header/fonte.h"
#include "Header/global.h"
#include "Header/load.h"
#include "Header/lightmap.h"
#include "Header/caracteristicas.h"
#include "Header/flechas.h"
#include "Header/magicas.h"
#include "Header/monstros.h"
#include "Header/pathfinding.h"
#include "Header/ataca.h"
#include "Header/colisao.h"
#include "Header/pesca.h"
#include "Header/mapas.h"
#include "Header/online.h"
#include "Header/menus.h"
#include "Header/equipamentos.h"
#include "Header/npcs.h"
#include "Header/guiitens.h"
#include "Header/menusjogo.h"
#include "Header/interacao.h"
#include "Header/log.h"
#include "Header/personagem.h"

char estaaandar=0;
char antesaltpress=-1;
int proximolevelexp=600;

void PersonAndar();

//TODO: remover SegueIDAux
int SegueIDAux=0;

void drawpersonagem() {
  int w2=0,tempxboteox2=0,tempxboteox=0;
  int contefeitotemp;
  int cor;

  if (personagem.levelup<6) {
    for (contefeitotemp=0;contefeitotemp<personagem.levelup;contefeitotemp++)
      DrawIMG(efeitos,personagem.x-xpos+25,personagem.y-ypos+45-(contefeitotemp-1)*10,44,22,0,0);
  }
  else {
    for (contefeitotemp=0;contefeitotemp<(5-(personagem.levelup-5));contefeitotemp++)
      DrawIMG(efeitos,personagem.x-xpos+25,personagem.y-ypos+15+(contefeitotemp)*10,44,22,0,0);
  }

  int w=larguraTexto(font,"%s",personagem.nome);
  int h=alturaTexto(font);

  if ((w == -1) || (h == -1))
    printf("ERRO fonte Personagem\n");
  else {
    if (personagem.guild) {
      w2=larguraTexto(font,"%s",personagem.guild);

      tempxboteox2=(w+w2-97)/2;

      DrawText(font,198,202,34,255,4,personagem.x -tempxboteox2 -xpos,personagem.y-19-ypos,"%s",personagem.guild);
    }
    tempxboteox=(w-w2-97)/2;

    if (personagem.type == 0)
      DrawText(font,190,190,190,255,4,personagem.x -tempxboteox -xpos,personagem.y-19-ypos,"%s",personagem.nome);
    else if (personagem.type == 1)
      DrawText(font,250,0,0,255,4,personagem.x -tempxboteox -xpos,personagem.y-19-ypos,"%s",personagem.nome);
    else if (personagem.type == 2)
      DrawText(font,0,90,230,255,4,personagem.x -tempxboteox -xpos,personagem.y-19-ypos,"%s",personagem.nome);
  }

  cor=(100-personagem.vida)*2;

  drawRectangle(personagem.x+17-xpos,personagem.y-3-ypos,62,4,90,90,90,255);
  fillRectangle(personagem.x+18-xpos,personagem.y-2-ypos,(60*personagem.vida)/100,2,cor,200-cor,0,255);

  fillRectangle(personagem.x+18-xpos+(60*personagem.vida)/100,personagem.y-2-ypos,1,2,90,90,90,255);

  int acaotemp=(personagem.acao==9)?4:personagem.acao;

  if (loadint.loadperson[personagem.qual-1][acaotemp]==0)
    LoadInteligent('p',personagem.qual,acaotemp);

  int r=LightMap_getColor(personagem.pathFind.atualX,personagem.pathFind.atualY,0);
  int g=LightMap_getColor(personagem.pathFind.atualX,personagem.pathFind.atualY,1);
  int b=LightMap_getColor(personagem.pathFind.atualX,personagem.pathFind.atualY,2);

  if (personagem.acao!=8) {
    if (imagemtamanho(personagem.qual,acaotemp)==1)
      DrawIMG_RGBA(personagens[personagem.qual-1][acaotemp],personagem.x-xpos,personagem.y-ypos,96,96,1+personagem.imagem*97,1+personagem.lado*97,r,g,b,255);
    else
      DrawIMG_RGBA(personagens[personagem.qual-1][acaotemp],personagem.x-xpos-16,personagem.y-16-ypos,128,128,1+personagem.imagem*129,1+personagem.lado*129,r,g,b,255);
  }
  else
    DrawIMG_RGBA(personagemmagica,personagem.x-xpos,personagem.y-ypos,96,96,1+personagem.imagem*97,1+personagem.lado*97,r,g,b,255);

  loadint.loadperson[personagem.qual-1][acaotemp]=(SDL_GetTicks()/1000)+30;

  if (personagem.levelup<6) {
    for (contefeitotemp=0;contefeitotemp<personagem.levelup;contefeitotemp++)
      DrawIMG(efeitos,personagem.x-xpos+25,personagem.y-ypos+53-(contefeitotemp-1)*10,48,25,0,22);
  }
  else {
    for (contefeitotemp=0;contefeitotemp<(5-(personagem.levelup-5));contefeitotemp++)
      DrawIMG(efeitos,personagem.x-xpos+25,personagem.y-ypos+23+(contefeitotemp)*10,48,25,0,22);
  }

  if (personagem.levelup>=5) DrawIMG(efeitos,personagem.x-xpos+22,personagem.y-ypos,55,25,0,48);
}
//  *Fim: Desenha os personagens.

void Personagem_Imagens() {
      if (personagem.acao==0) {
        personagem.imagem=0;
        if ((tempoparado==0) || (tempoparado*1000<=SDL_GetTicks())) {
          personagem.acao=5;
          tempoparado=(SDL_GetTicks()/1000)+5;
        }
      }
      else if ((personagem.acao==1) || (personagem.acao==2)) {
        PersonAndar();
      }
      else if (personagem.acao == 3) {
        personagem.imagem++;
        if (personagem.imagem >= imagemdereset(personagem.qual, personagem.acao)) {
          if ((antesaltpress == 1) || (antesaltpress == 2)) {
            personagem.acao=1 + lctrlpress;
          }
          else {
            personagem.acao=0;
          }
          personagem.imagem=0;
          antesaltpress=-1;
          if (personagem.acao == 0) {
            tempoparado=(SDL_GetTicks() / 1000) + 10;
          }
        }
      }
      else if (personagem.acao==4) {
        personagem.imagem++;
        if (personagem.qual!=7) {
          if ((personagem.qual == 3) && (personagem.imagem == 5))
            criar_arrow(arrowtemp.posx, arrowtemp.posy, arrowtemp.mposx, arrowtemp.mposy, arrowtemp.lado);

          if ((personagem.qual!=3) && (personagem.imagem==imagemdereset(personagem.qual,4)-1)) {
            int temp=1;
            while (monsterlacao(temp,'s')==1) {
              if (sqrt(pow(personagem.x-monstroatual->x,2)+pow(personagem.y-monstroatual->y,2))<=40) {
                if ((monstroatual->acao!=4) && (arrumaragoliuasd(personagem.x+48,personagem.y+68,monstroatual->x+((imagtamonstro(monstroatual->qual,monstroatual->acao)==1)?45:29),monstroatual->y+((imagtamonstro(monstroatual->qual,monstroatual->acao)==1)?79:63))==personagem.lado)) {
                  danonosmostr();
                }
              }
             temp++;
            }
          }
          if (personagem.imagem>=imagemdereset(personagem.qual,personagem.acao)) {
            personagem.imagem=0;
            if ((antesaltpress==1) || (antesaltpress==2))
              personagem.acao=1+lctrlpress;
            else
              personagem.acao=0;
            antesaltpress=-1;

            if (personagem.acao==0)
              tempoparado=(SDL_GetTicks()/1000)+10;
          }
        }
        else if (personagem.imagem>=imagemdereset(personagem.qual,personagem.acao)) {
          personagem.imagem=imagemdereset(personagem.qual,personagem.acao)-1;
          personagem.acao=9;
          boias[1].ativa=1;
          boias[1].x=boiastemp[0];
          boias[1].y=boiastemp[1];
          boias[1].imagem=0;
          boias[1].idquem=personagem.id;
          boias[1].acao=0;
          boias[1].timecheck=(SDL_GetTicks()/100)+rand()%40+20;
          boias[1].fx=boiastemp2[0];
          boias[1].fy=boiastemp2[1];
          if (tutorialpesca>0) { tutorialpesca=3; }
        }
      }
      else if (personagem.acao==5) { personagem.imagem++; if (personagem.imagem>=imagemdereset(personagem.qual,5)) { if (tempoparado*1000<=SDL_GetTicks()) { tempoparado=(SDL_GetTicks()/1000)+10; personagem.imagem=0; personagem.acao=0; } else { personagem.imagem=0; personagem.acao=5; } } }
      else if (personagem.acao==6) { personagem.imagem++; if (personagem.imagem>=imagemdereset(personagem.qual,6)) { if ((antesaltpress==1) || (antesaltpress==2)) { personagem.acao=1+lctrlpress; } else { personagem.acao=0; } antesaltpress=-1; personagem.imagem=0; if (personagem.acao==0) { tempoparado=(SDL_GetTicks()/1000)+10; } } }
      else if (personagem.acao==7) { personagem.imagem++; if (personagem.imagem>=imagemdereset(personagem.qual,7)) { personagem.imagem=imagemdereset(personagem.qual,personagem.acao)-1; personagem.acao=7; } }
      else if (personagem.acao==8) {
        if (personagem.qual!=4) {
          personagem.acao=0;
          personagem.imagem=0;
        }

        personagem.imagem++;

        if ((personagem.imagem==5) && (personagem.qual==4))
          criar_magic(magictemp.posx,magictemp.posy,magictemp.mposx,magictemp.mposy,magictemp.lado,magictemp.qual);

        if (personagem.imagem>=imagemdereset(personagem.qual,8)) {
           personagem.imagem=0;

            if (!(SDL_GetMouseState(NULL, NULL)&SDL_BUTTON(3))) {
              if ((antesaltpress==1) || (antesaltpress==2))
                personagem.acao=1+lctrlpress;
              else
                personagem.acao=0;
              antesaltpress=-1;
            }
            else {
              personagem.lado=arrumaragoliuasd(personagem.x+48,personagem.y+68,mousemovidox+xpos,mousemovidoy+ypos);
              atacar(3,0,0);
            }

           if (personagem.acao==0)
             tempoparado=(SDL_GetTicks()/1000)+10;
        }
      }
      else if (personagem.acao==9) { tempoparado=(SDL_GetTicks()/1000)+10; }
}

void PersonAndar() {
  int tempadd=0;
  int tempy=personagem.pathFind.atualY*16-64;
  int tempx=personagem.pathFind.atualX*16-40;

  if (tempy>personagem.y) {
    if (personagem.lado>=4) { tempadd=(lctrlpress==1)?6:3; } else { tempadd=(lctrlpress==1)?9:4; }
    if (personagem.y+tempadd>tempy) { tempadd=tempy-personagem.y; personagem.y+=tempadd; }
    else { personagem.y+=tempadd; }
    if (personagem.y-ypos>=200) { ypos+=abs(tempadd); }
    if (ypos >= (map_sizey-12)*48) { ypos=(map_sizey-12)*48; }
  }
  else if (tempy<personagem.y) {
    if (personagem.lado>=4) { tempadd=(lctrlpress==1)?6:3; } else { tempadd=(lctrlpress==1)?9:4; }
    if (personagem.y-tempadd<tempy) { tempadd=tempy-personagem.y; personagem.y+=tempadd; }
    else { personagem.y-=tempadd; }
    if (personagem.y-ypos<=200) { ypos-=abs(tempadd); }
    if (ypos <= 0) { ypos=0; }
  }
  if (tempx>personagem.x) {
    if (personagem.lado>=4) { tempadd=(lctrlpress==1)?6:3; } else { tempadd=(lctrlpress==1)?9:4; }
    if (personagem.x+tempadd>tempx) { tempadd=tempx-personagem.x; personagem.x+=tempadd; }
    else { personagem.x+=tempadd; }
    if (personagem.x-xpos>=300) { xpos+=abs(tempadd); }
    if (xpos >= (map_sizex-13)*64) { xpos=(map_sizex-13)*64; }
  }
  else if (tempx<personagem.x) {
    if (personagem.lado>=4) { tempadd=(lctrlpress==1)?6:3; } else { tempadd=(lctrlpress==1)?9:4; }
    if (personagem.x-tempadd<tempx) { tempadd=tempx-personagem.x; personagem.x+=tempadd; }
    else { personagem.x-=tempadd; }
    if (personagem.x-xpos<=300) { xpos-=abs(tempadd); }
    if (xpos <= 0) { xpos=0; }
  }

  if ((mapcaminhar[personagem.pathFind.atualY][personagem.pathFind.atualX]>2) && (mapcaminhar[personagem.pathFind.atualY][personagem.pathFind.atualX]<8)) {
    char mapatempos[30];

    while (arrowacao(1,'s')) { arrowacao(1,'d'); }
    while (magicacao(1,'s')) { magicacao(1,'d'); }
    monsterlacao(1,'z');

    sprintf(mapatempos,"Data/Mapas/mapa%d.set",qualmapa[mapcaminhar[personagem.pathFind.atualY][personagem.pathFind.atualX]-3][0]);
    lermapafile(mapatempos,qualmapa[mapcaminhar[personagem.pathFind.atualY][personagem.pathFind.atualX]-3][1],qualmapa[mapcaminhar[personagem.pathFind.atualY][personagem.pathFind.atualX]-3][2]);

    objets_mapas(qualmapa[mapcaminhar[personagem.pathFind.atualY][personagem.pathFind.atualX]-3][0]);

    personagem.pathFind.achou=PATH_NAO_ACHOU;
  }


  if ((SDL_GetMouseState(NULL, NULL)&SDL_BUTTON(1)) && (estaaandar==1)) {
    if ((personagem.pathFind.destinoX!=(int)((mousemovidox+xpos)/16)) || (personagem.pathFind.destinoY!=(int)((mousemovidoy+ypos)/16)))
      chamarPathFind('m');
  }

  if ((tempy==personagem.y) && (tempx==personagem.x)) {
    if ((personagem.pathFind.achou == PATH_ACHOU) && (!personagem.pathFind.chegou))
      pathMove(&personagem.pathFind,&personagem.lado);
    else {
      personagem.acao=0;
      tempoparado=(SDL_GetTicks()/1000)+5;
    }
  }

  personagem.imagem++;
  if (personagem.imagem>=imagemdereset(personagem.qual,personagem.acao)) { personagem.imagem=0; }
  if (personagem.SegueOq==2) {
    int raiomonstro=sqrt(pow(npcs[personagem.SegueID-1].posx-personagem.x,2)+pow(npcs[personagem.SegueID-1].posy-personagem.y,2));
    if (raiomonstro<=70) {
      personagem.lado=arrumaragoliuasd(personagem.x+48,personagem.y+68,npcs[personagem.SegueID-1].posx+50,npcs[personagem.SegueID-1].posy+68);
      if (personagem.SegueID==1) {
        npcs[personagem.SegueID-1].imagem=0; npcs[personagem.SegueID-1].acao=1; personagem.acao=6; personagem.imagem=0;
        menus.ativo=1; menus.nomequem=personagem.SegueID-1; menus.qual=1;
      }
      else if (personagem.SegueID==2) {
        menus.ativo=1; menus.nomequem=personagem.SegueID-1; menus.qual=2;
        personagem.acao=6; personagem.imagem=0;
      }
      else if (personagem.SegueID==3) {
        npcs[personagem.SegueID-1].imagem=0; npcs[personagem.SegueID-1].acao=1; personagem.acao=6; personagem.imagem=0;
        menus.ativo=1; menus.nomequem=personagem.SegueID-1; menus.qual=3;
      }
      else if (personagem.SegueID==4) {
        npcs[personagem.SegueID-1].imagem=0; npcs[personagem.SegueID-1].acao=1; personagem.acao=0; personagem.imagem=0;
        BauMenuOn=1; inventarioon=1;
      }
    }
  }
  else if ((personagem.SegueOq==3) && (personagem.acao==0)) {
    int quadradox=(int)((personagem.x+48)/64),quadradoy=(int)((personagem.y+68)/48);
    if ((personagem.SegueID==quadradox) && (SegueIDAux==quadradoy)) {
      if (itenschao[0][quadradoy][quadradox]) {
        if (itenschao[0][quadradoy][quadradox]==53) {
          meusstatsua.dinheiro+=itenschao[2][quadradoy][quadradox];
          itenschao[0][quadradoy][quadradox]=0;
          itenschao[1][quadradoy][quadradox]=0;
          itenschao[2][quadradoy][quadradox]=0;
        }
        else if ((!carregarar) && (inventarioon)) {
          itemnamao[0]=itenschao[0][quadradoy][quadradox];
          itemnamao[1]=itenschao[1][quadradoy][quadradox];
          itemnamao[2]=itenschao[2][quadradoy][quadradox];
          carregarar=1;
          itenschao[0][quadradoy][quadradox]=0;
          itenschao[1][quadradoy][quadradox]=0;
          itenschao[2][quadradoy][quadradox]=0;
        }
        else {
          if (colocaritem_procurar(itenschao[0][quadradoy][quadradox],itenschao[1][quadradoy][quadradox],itenschao[2][quadradoy][quadradox])) {
            itenschao[0][quadradoy][quadradox]=0;
            itenschao[1][quadradoy][quadradox]=0;
            itenschao[2][quadradoy][quadradox]=0;
          }
          else
            Error("Inventário cheio.",ERRO_AVISO);
        }
      }
    }
  }
  else if (personagem.SegueOq==-1) {
    if ((personagem.pathFind.chegou) && (personagem.acao == 0)) {
      tempx=personagem.pathFind.atualX;
      tempy=personagem.pathFind.atualY;

      if (interacao_verifRaio(personagem.SegueID,tempx,tempy)) {
        personagem.SegueOq=0;
        interacao_pegar(personagem.SegueID);
      }
    }
  }
}

