#include <stdlib.h>

#include "Header/magicas.h"
#include "Header/particulas.h"
#include "Header/personagem.h"
#include "Header/monstros.h"
#include "Header/magicas.h"
#include "Header/mapas.h"
#include "Header/caracteristicas.h"
#include "Header/util.h"
#include "Header/global.h"
#include "Header/colisao.h"

//TODO: Adicionar arquivo para adiciar dano com lista encadeada

void danonosmostr() {
  int tempasda;
  for (tempasda=0; tempasda < 5; tempasda++) {
    if (DanoTirado[tempasda].ativado == 0) {
      break;
    }
  }
  DanoTirado[tempasda].valor=0;
  if (rand() % 3 == 0) {
    Add_Particulas(1, 1, monstroatual->x + 50, monstroatual->y + 50);
  }
  else if (rand() % 4 == 2) {
    DanoTirado[tempasda].valor=-1;
  }
  if (DanoTirado[tempasda].valor != -1) {
    DanoTirado[tempasda].valor=rand() % 5 + 6;
    monstroatual->vida-=DanoTirado[tempasda].valor;
  }
  DanoTirado[tempasda].ativado=1;
  DanoTirado[tempasda].tipo=1;
  DanoTirado[tempasda].posx=monstroatual->x + 40;
  DanoTirado[tempasda].posy=monstroatual->y + 30;
  DanoTirado[tempasda].alfa=500;

  if (monstroatual->vida <= 0) {
    monstroatual->vida=0;
    monstroatual->acao=4;
    monstroatual->imagem=0;
    meusstatsua.experiencia+=200;
    meusstatsua.nextlevelexp+=200;

    colocaritemchao(monstroatual->x + 48, monstroatual->y + 75);
  }
  else if ((rand() % 4 == 0) && (DanoTirado[tempasda].valor != -1)) {
    monstroatual->acao=3;
    monstroatual->imagem=0;
  }
  if (meusstatsua.experiencia >= proximolevelexp) {
    personagem.levelup=0;
    meusstatsua.level++;
    meusstatsua.pontos+=5;
    meusstatsua.nextlevelexp=meusstatsua.experiencia - proximolevelexp;
    proximolevelexp+=500;
  }
}

int checararrowcolide(int x, int y,int lado) {
  /*x+=16;
  y+=32;*/
  int maisy,maisx,posxarrow,posyarrow;
  if ((x<-27) || (y<-50) || (x+27>=(map_sizex-1)*64) || (y+50>=(map_sizey-1)*48)) { return 0; }

  maisy=2+lado/16;
  maisx=(((lado/8)==3) || ((lado/8)==0))?1:0;
  posyarrow=(int)(y/16)+maisy;
  posxarrow=(int)(x/16)+maisx;

  if ((posyarrow<0) || (posxarrow<0) || (posxarrow>=map_sizex*4) || (posyarrow>=map_sizey*3)) return 0;
  if (mapcaminhar[posyarrow][posxarrow]==1) return 0;
  if (mapcaminhar[posyarrow][posxarrow]==PATH_CAMINHO_INTERACAO) return 0;

//draw_quadrado(250,0,250,posxarrow*16-xpos,posyarrow*16-ypos,16,16);

  int colide=0,forxtemp,forytemp;

  forList (struct monstro *, monstroTmp, primmonstro) {
    if (monstroTmp->acao!=4) {
      colide=0;

      for (forytemp=-1;forytemp<=1;forytemp++) {
        for (forxtemp=-1;forxtemp<=1;forxtemp++) {
          //draw_quadrado(250,0,250,(monstroatual->pathFind.atualX+forxtemp)*16-xpos,(monstroatual->pathFind.atualY+forytemp)*16-ypos,16,16);
          if ((monstroTmp->pathFind.atualX+forxtemp==posxarrow) && (monstroTmp->pathFind.atualY+forytemp==posyarrow)) {
            colide=1; forxtemp=2; forytemp=2;
          }
        }
      }

      //Acertou o monstro e monstro segue personagem
      if (colide) {
        if (monstroTmp->acao!=2) {
          monstroTmp->timetempo=SDL_GetTicks()/100;
          pathFindPadrao(personagem.pathFind.atualX,personagem.pathFind.atualY,&monstroTmp->pathFind);
        }
        danonosmostr();
        return 0;
      }
    }
  }

  return 1;
}

int Verif_Colisao(int x, int y, int w, int h, int maisx, int maisy, int tamx, int tamy,char lado) {
  int colidposx,colidposy,colidposx2,colidposy2;
  if ((x<-w) || (y<-h) || (x+w>=(map_sizex-1)*64) || (y+h>=(map_sizey-1)*48)) return 1;

  colidposy=(int)(y/16)+maisy;
  colidposx=(int)(x/16)+maisx;

  if ((colidposy<0) || (colidposx<0) || (colidposx>=map_sizex*4) || (colidposy>=map_sizey*3)) return 1;

  char colide=0,forxtemp,forytemp;

  forList (struct monstro *, monstroTmp, primmonstro) {
    monstroatual=monstroTmp;

    if (monstroatual->acao!=4) {
      colide=0;

      for (colidposy2=-(tamy/2);colidposy2<tamy-(tamy/2);colidposy2++) {
        for (colidposx2=-(tamx/2);colidposx2<tamx-(tamx/2);colidposx2++) {
//draw_quadrado(250,0,250,(colidposx+colidposx2)*16-xpos,(colidposy+colidposy2)*16-ypos,16,16);
          if ((colidposx+colidposx2<map_sizex*4) && (colidposy+colidposy2<map_sizey*3) && (colidposx+colidposx2>=0) && (colidposy+colidposy2>=0)) {
            if (mapcaminhar[colidposy+colidposy2][colidposx+colidposx2]==1) return 1;
            if (mapcaminhar[colidposy+colidposy2][colidposx+colidposx2]==PATH_CAMINHO_INTERACAO) return 1;
          }
          for (forytemp=-1;forytemp<=1;forytemp++) {
            for (forxtemp=-1;forxtemp<=1;forxtemp++) {
              //draw_quadrado(0,0,250,(monstroatual->pathFind.atualX+forxtemp)*16-xpos,(monstroatual->pathFind.atualY+forytemp)*16-ypos,16,16);
              if ((monstroatual->pathFind.atualX+forxtemp==colidposx+colidposx2) && (monstroatual->pathFind.atualY+forytemp==colidposy+colidposy2)) {
                colide=1; forxtemp=2; forytemp=2;
              }
            }
          }
        }
      }

      //Acertou mostro e mostro segue personagem
      if (colide) {
        if (monstroatual->acao!=2) {
          monstroatual->timetempo=SDL_GetTicks()/100;
          pathFindPadrao(personagem.pathFind.atualX,personagem.pathFind.atualY,&monstroatual->pathFind);
        }
        //danonosmostr();
        return 1+monstroTmp_Id;
      }
    }
  }
//SDL_Flip(screen);
  return 0;
}

void colide_magic() {
  int codcolide=0;

  int qual=magicatual->qual;
  struct a { int x,y,w,h,maisx,maisy,tamx,tamy; };
  struct a magCol;

  magCol.x=magicatual->posx+magicatual->mposx+Info_Colid_Magic(qual,'a','x');
  magCol.y=magicatual->posy+magicatual->mposy+Info_Colid_Magic(qual,'a','y');

  magCol.w=Info_Magic(qual,'w');
  magCol.h=Info_Magic(qual,'h');

  magCol.maisx=Info_Colid_Magic(qual,'m','x');
  magCol.maisy=Info_Colid_Magic(qual,'m','y');
  magCol.tamx=Info_Colid_Magic(qual,'t','x');
  magCol.tamy=Info_Colid_Magic(qual,'t','y');

  codcolide=Verif_Colisao(magCol.x,magCol.y,magCol.w,magCol.h,magCol.maisx,magCol.maisy,magCol.tamx+1,magCol.tamy+1,magicatual->lado);

  if (codcolide) {
    if ((!magicatual->deletar) || (Info_Magic(qual,'d'))) {
      //magica colidiu com monstro
      if (codcolide>1) {
        if (monsterlacao(codcolide-1,'s')) {
          //Velocidade que vai tirar dano
          if ((magicatual->time==0) || (magicatual->time*100<SDL_GetTicks())) {
            danonosmostr();
            magicatual->time=SDL_GetTicks()/100+Info_Magic(qual,'k');
          }
        }
      }
    }
    if (!magicatual->deletar) {
      //Deleta se tire colidio com parede ou se a flag de deletar ao colidir com mostro for 1
      if ((Info_Magic(magicatual->qual,'m')) || (codcolide==1)) {
        magicatual->deletar=1;
        magicatual->imagem=Info_Magic(qual,'i')+1;
      }
    }
    else if ((codcolide==1) && (Info_Magic(magicatual->qual,'p')))
      magicatual->imagem=Info_Magic(magicatual->qual,'n');
  }
}
