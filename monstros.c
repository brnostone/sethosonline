#include <stdio.h>
#include <math.h>

#include "Header/global.h"
#include "Header/fonte.h"
#include "Header/estruturas.h"
#include "Header/load.h"
#include "Header/lightmap.h"
#include "Header/caracteristicas.h"
#include "Header/personagem.h"
#include "Header/mapas.h"
#include "Header/ataca.h"
#include "Header/pathfinding.h"
#include "Header/colisao.h"
#include "Header/monstros.h"

struct monstro *monstroatual=NULL;
Lista *primmonstro=NULL;
int nummonstro=0;

int monsterlacao(int id,char acao) {
  static int opcao=MUDAR_ID;

  if (acao=='n') {
    monstroatual=(struct monstro *) lista_acao('n',&primmonstro,id,opcao,sizeof(struct monstro));
    nummonstro++;
  }
  else if (acao=='d') {
    monstroatual=(struct monstro *) lista_acao('d',&primmonstro,id,opcao,0);
    if (monstroatual) nummonstro--;
  }
  else if (acao=='s') {
    monstroatual=(struct monstro *) lista_acao('s',&primmonstro,id,opcao,nummonstro);
    return (!monstroatual)?0:1;
  }
  else if (acao=='z') {
    while (primmonstro!=NULL)
      monsterlacao(primmonstro->id,'d');

    nummonstro=0;
  }
  return 0;
}

void nomesmontros(char qual) {
  switch(qual) {
    case 1: { monstroatual->nome="Orc\0"; break; }
    case 2: { monstroatual->nome="Esqueleto\0"; break; }
    case 3: { monstroatual->nome="Lobo Marrom\0"; break; }
    case 4: { monstroatual->nome="Morcego\0"; break; }
  }
}

void criar_monstros(int posx,int posy,char qual,char lado,char acao) {
  monsterlacao(nummonstro+1,'n');
  nomesmontros(qual);
  monstroatual->x=posx;
  monstroatual->y=posy;
  monstroatual->pathFind.atualX=(posx+40)/16;
  monstroatual->pathFind.atualY=(posy+64)/16;
//  monstroatual->futurox=fposx;
//  monstroatual->futuroy=fposy;
  monstroatual->vida=100;
  monstroatual->qual=qual;
  monstroatual->imagem=0;
  monstroatual->lado=lado;
  monstroatual->acao=acao;
  monstroatual->timetempo=0; //temporario quantiver server nao vai ter mais
  monstroatual->pathFind.dest=NULL;
  monstroatual->pathFind.tipo=PATH_TIPO_MONSTRO;
}

void draw_monstros(int id) {
  if (monsterlacao(id,'s')) {
    int cor;
    int acaoTemp;

    if (monstroatual->acao!=4) {
      int w=larguraTexto(font,"%s",monstroatual->nome);
      int h=alturaTexto(font);

      if ((w == -1) || (h == -1)) { printf("ERRO monstro\n"); }
      else {
        int tempxboteox=(w-97)/2;

        DrawText(font,250,109,73,255,4,monstroatual->x -tempxboteox -xpos,monstroatual->y-19-ypos,"%s",monstroatual->nome);
      }

      cor=(100-monstroatual->vida)*2;

      drawRectangle(monstroatual->x+17-xpos,monstroatual->y-3-ypos,62,4,90,90,90,255);
      fillRectangle(monstroatual->x+18-xpos,monstroatual->y-2-ypos,(60*monstroatual->vida)/100,2,cor,200-cor,0,255);

      fillRectangle(monstroatual->x+18-xpos+(60*monstroatual->vida)/100,monstroatual->y-2-ypos,1,2,90,90,90,255);
    }

    acaoTemp=((monstroatual->seguindo==1)&&(monstroatual->acao==1))?5:monstroatual->acao;

    if (loadint.loadmonstro[monstroatual->qual-1][acaoTemp]==0) {
      LoadInteligent('m',monstroatual->qual,acaoTemp);
    }

    int r=LightMap_getColor(monstroatual->pathFind.atualX,monstroatual->pathFind.atualY,0);
    int g=LightMap_getColor(monstroatual->pathFind.atualX,monstroatual->pathFind.atualY,1);
    int b=LightMap_getColor(monstroatual->pathFind.atualX,monstroatual->pathFind.atualY,2);

    if (imagtamonstro(monstroatual->qual,acaoTemp)==1)
      DrawIMG_RGBA(monstros[monstroatual->qual-1][acaoTemp],monstroatual->x-xpos,monstroatual->y-ypos,96,96,1+monstroatual->imagem*97,1+monstroatual->lado*97,r,g,b,255);
    else
      DrawIMG_RGBA(monstros[monstroatual->qual-1][acaoTemp],monstroatual->x-xpos-16,monstroatual->y-ypos-16,128,128,1+monstroatual->imagem*129,1+monstroatual->lado*129,r,g,b,255);

    loadint.loadmonstro[monstroatual->qual-1][acaoTemp]=(SDL_GetTicks()/1000)+60;

    if (monstroatual->acao!=4) {
      if (mouseverondeclia(monstroatual->x-xpos+36,monstroatual->x-xpos+70,monstroatual->y-ypos+36,monstroatual->y-ypos+80)) {
        CursorUsando[0]=1;
        CursorUsando[1]=id;
      }
    }
  }
  //draw_quadrado(250,0,250,monstroatual->pathFind.atualX*16-xpos,monstroatual->pathFind.atualY*16-ypos,16,16);
}

void visao_mostro(int id) {
  if (((monstroatual->acao==0) || (monstroatual->acao==1)) && (personagem.acao!=7) && (monstroatual->acao!=2)) {
    int raiomonstro=sqrt(pow(monstroatual->x-personagem.x,2)+pow(monstroatual->y-personagem.y,2));
    if (raiomonstro<=150) {
      monstroatual->seguindo=1;
      if (raiomonstro<=40) { monstroatual->acao=2; }
      else {
        //Segue personagem
        pathFindPadrao(personagem.pathFind.atualX,personagem.pathFind.atualY,&monstroatual->pathFind);
        monstroatual->acao=1;
        monstroatual->timetempo=SDL_GetTicks()/100;
      }
    }
    else { monstroatual->seguindo=0; }
    if (raiomonstro<=600) {
      if (loadint.loadmonstro[(int)monstroatual->qual-1][(int)monstroatual->acao]==0) { LoadInteligent(2,monstroatual->qual-1,monstroatual->acao); }
    }
  }
  else { monstroatual->seguindo=0; }
}

int additemchao(int x,int y,int tipo,int qual,int add) {
  if ((y<0) || (x<0) || (y>=map_sizey) || (x>=map_sizex)) return 0;

  if (!itenschao[0][y][x]) {
    if (!mapobjetos[y][x]) {
      itenschao[0][y][x]=tipo;
      itenschao[1][y][x]=qual;
      itenschao[2][y][x]=add;
      return 1;
    }
  }
  return 0;
}

//TODO: verificar se isto tem que ficar aqui
void colocaritemchao(int posatx,int posaty) {
  int sortpositionx,sortpositiony,posatx2,posaty2;
  char largoitem=0,contaras=0;
  posatx2=posatx/64;
  posaty2=posaty/48;
  do {
    sortpositionx=rand()%3;
    sortpositiony=rand()%3;

    if (additemchao(sortpositionx+posatx2-1,sortpositiony+posaty2-1,53,1,rand()%100+30)) { largoitem=1; }

    contaras++;
  } while ((!largoitem) && (contaras<=10));

  if (!largoitem) {
    contaras=1;
    do {
      sortpositionx=posatx2-contaras;
      sortpositiony=posaty2-contaras;
      char teampsx, teampsy;
      for (teampsy=contaras*-1;teampsy<=contaras;teampsy++) {
        for (teampsx=contaras*-1;teampsx<=contaras;teampsx++) {
          if (additemchao(sortpositionx+teampsx,sortpositiony+teampsy,53,1,rand()%100+30)) {
            largoitem=1; teampsy=5; teampsx=5;
            break;
          }
        }
      }
      contaras++;
    } while ((!largoitem) && (contaras<=2));
  }
  if (!largoitem) {
    itenschao[0][posaty2][posatx2]=53;
    itenschao[1][posaty2][posatx2]=1;
    itenschao[2][posaty2][posatx2]=rand()%100+30;
  }
}

void IA_Monstro() {
  int tempx,tempy,tempadd;

  forList (struct monstro *, monstroTmp, primmonstro) {
    monstroatual=monstroTmp;

    visao_mostro(monstroTmp_Id);
    if ((personagem.SegueOq==1) && (personagem.SegueID==monstroTmp_Id)) {
      if (monstroatual->acao!=4) {
        int raiomonstro=sqrt(pow(monstroatual->x-personagem.x,2)+pow(monstroatual->y-personagem.y,2));
        if ((raiomonstro<=40) && (personagem.qual!=3)) {
          personagem.acao=4;
          personagem.lado=arrumaragoliuasd(personagem.x+48,personagem.y+68,monstroatual->x+((imagtamonstro(monstroatual->qual,monstroatual->acao)==1)?48:29),monstroatual->y+((imagtamonstro(monstroatual->qual,monstroatual->acao)==1)?73:63));
        }
        else if ((raiomonstro<=300) && (personagem.qual==3)) {
          personagem.acao=4;
          atacar(1,monstroatual->x+((imagtamonstro(monstroatual->qual,monstroatual->acao)==1)?48:29)-xpos,monstroatual->y+((imagtamonstro(monstroatual->qual,monstroatual->acao)==1)?73:63)-ypos);
        }
        else if (pathFindPadrao(monstroatual->pathFind.atualX,monstroatual->pathFind.atualY,&personagem.pathFind) == PATH_ACHOU)
          personagem.acao=(lctrlpress==1)?2:1;

      }
      else { personagem.SegueOq=0; personagem.SegueID=0; }
    }
    if (((monstroatual->acao==0) || (monstroatual->acao==1)) && (monstroatual->acao!=2)) {
      if (monstroatual->timetempo==0) {
        monstroatual->acao=0;
        int novoDestinoX,novoDestinoY;

        novoDestinoX=monstroatual->pathFind.atualX+(rand()%7-3);
        novoDestinoY=monstroatual->pathFind.atualY+(rand()%7-3);
        monstroatual->timetempo=(SDL_GetTicks()/100)+(rand()%100);
        if (novoDestinoX<0) { novoDestinoX=0; }
        if (novoDestinoY<0) { novoDestinoY=0; }
        if (novoDestinoX>=map_sizex*4-1) { novoDestinoX=map_sizex*4-1; }
        if (novoDestinoY>=map_sizey*3-1) { novoDestinoY=map_sizey*3-1; }

        pathFindPadrao(novoDestinoX,novoDestinoY,&monstroatual->pathFind);
      }
      else if (monstroatual->timetempo<=SDL_GetTicks()/100) {
        if (monstroatual->acao==0) { monstroatual->acao=1; }
        tempy=monstroatual->pathFind.atualY*16-64;
        tempx=monstroatual->pathFind.atualX*16-40;
        if (tempy>monstroatual->y) {
          if (monstroatual->lado>=4) { tempadd=(monstroatual->seguindo==1)?5:3; } else { tempadd=(monstroatual->seguindo==1)?7:4; }
          if (monstroatual->y+tempadd>tempy) { tempadd=tempy-monstroatual->y; monstroatual->y+=tempadd; }
          else { monstroatual->y+=tempadd; }
        }
        else if (tempy<monstroatual->y) {
          if (monstroatual->lado>=4) { tempadd=(monstroatual->seguindo==1)?5:3; } else { tempadd=(monstroatual->seguindo==1)?7:4; }
          if (monstroatual->y-tempadd<tempy) { tempadd=tempy-monstroatual->y; monstroatual->y+=tempadd; }
          else { monstroatual->y-=tempadd; }
        }
        if (tempx>monstroatual->x) {
          if (monstroatual->lado>=4) { tempadd=(monstroatual->seguindo==1)?5:3; } else { tempadd=(monstroatual->seguindo==1)?7:4; }
          if (monstroatual->x+tempadd>tempx) { tempadd=tempx-monstroatual->x; monstroatual->x+=tempadd; }
          else { monstroatual->x+=tempadd; }
        }
        else if (tempx<monstroatual->x) {
          if (monstroatual->lado>=4) { tempadd=(monstroatual->seguindo==1)?5:3; } else { tempadd=(monstroatual->seguindo==1)?7:4; }
          if (monstroatual->x-tempadd<tempx) { tempadd=tempx-monstroatual->x; monstroatual->x+=tempadd; }
          else { monstroatual->x-=tempadd; }
        }

        if ((tempy==monstroatual->y) && (tempx==monstroatual->x)) {
          if ((monstroatual->pathFind.achou == PATH_ACHOU) && (!monstroatual->pathFind.chegou))
            pathMove(&monstroatual->pathFind,&monstroatual->lado);
          else {
            monstroatual->acao=0;
            int novoDestinoX,novoDestinoY;

            novoDestinoX=monstroatual->pathFind.atualX+(rand()%21-10);
            novoDestinoY=monstroatual->pathFind.atualY+(rand()%21-10);
            monstroatual->timetempo=(SDL_GetTicks()/100)+(rand()%100);
            if (novoDestinoX<0) { novoDestinoX=0; }
            if (novoDestinoY<0) { novoDestinoY=0; }
            if (novoDestinoX>=map_sizex*4-1) { novoDestinoX=map_sizex*4-1; }
            if (novoDestinoY>=map_sizey*3-1) { novoDestinoY=map_sizey*3-1; }

            pathFindPadrao(novoDestinoX,novoDestinoY,&monstroatual->pathFind);
          }
        }
        monstroatual->imagem++;
        if (monstroatual->imagem>=monstroimreset(monstroatual->qual,monstroatual->acao)) { monstroatual->imagem=0; }
      }
    }
    else {
      if (monstroatual->acao==2) {
        monstroatual->imagem++;
        if (monstroatual->imagem>=monstroimreset(monstroatual->qual,2)) {
          monstroatual->imagem=0; monstroatual->acao=0;
          monstroatual->lado=arrumaragoliuasd(monstroatual->x+((imagtamonstro(monstroatual->qual,monstroatual->acao)==1)?45:29),monstroatual->y+((imagtamonstro(monstroatual->qual,monstroatual->acao)==1)?79:63),personagem.x+48,personagem.y+68);

          int tempasda;
          for (tempasda=0;tempasda<30;tempasda++) {
            if (DanoTirado[tempasda].ativado==0) { break; }
          }

          DanoTirado[tempasda].valor=0;

          if (rand()%4==2) { DanoTirado[tempasda].valor=-1; }
          else { DanoTirado[tempasda].valor=rand()%3+2; personagem.vida-=DanoTirado[tempasda].valor; }

          DanoTirado[tempasda].ativado=1;
          DanoTirado[tempasda].tipo=2;
          DanoTirado[tempasda].posx=personagem.x+40;
          DanoTirado[tempasda].posy=personagem.y+30;
          DanoTirado[tempasda].alfa=500;

          if (personagem.vida<=0) {
            personagem.vida=0; if (personagem.acao!=7) { personagem.imagem=0; } personagem.acao=7;
            monstroatual->seguindo=0;
            monstroatual->acao=1;
          }
        }
      }
      else if (monstroatual->acao==3) { monstroatual->imagem++; if (monstroatual->imagem>=monstroimreset(monstroatual->qual,3)) { monstroatual->imagem=0; monstroatual->acao=0; } }
      else if (monstroatual->acao==4) {
        monstroatual->imagem++;
        if (monstroatual->imagem>=monstroimreset(monstroatual->qual,4)) {
          monstroatual->imagem=monstroimreset(monstroatual->qual,4)-1;
          monstroatual->acao=4;

        }
      }
    }
  }
}
