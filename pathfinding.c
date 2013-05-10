#include <stdlib.h>
#include <math.h>
#include <SDL/SDL.h>

#include "Header/mapas.h"
#include "Header/interacao.h"
#include "Header/pathfinding.h"

unsigned char tiposParede[]={2,8,255};

struct pathUtil {
  int x;
  int y;

  int FCust;
  int GCust;
  struct pathUtil *pai;
};

int pathTamMapW=0;
int pathTamMapH=0;
int numListaFechada=2;
int numListaAberta=1;
int numOpenList;

struct pathUtil *path_elemtUsado=NULL;
int *path_listaAberta=NULL;
int **path_listas=NULL;

unsigned char pathVerifAndar(pathfinder *path, unsigned char **mapa, int x, int y) {
  if ((x>=pathTamMapW) || (x<0) || (y>=pathTamMapH) || (y<0))
    return PATH_PAREDE;

  unsigned char conteudo=mapa[y][x];

  if (conteudo != 0) {
    if (conteudo == 1) return PATH_PAREDE;

    //Verifica se o caminho for do tipo interacao
    if (conteudo == PATH_CAMINHO_INTERACAO) {
      if (path->tipo == PATH_TIPO_PERSONAGEM) {
        //se interacao_id == -1 ele ja retorna como PAREDE
        return (interacao_verifRaio(path->interacao_id,x,y))? PATH_CAMINHO:PATH_PAREDE;
      }
      else
        return PATH_PAREDE;
    }

    int percorre;
    for (percorre=0; tiposParede[percorre] != 255 ;percorre++) {
      if (tiposParede[percorre] == conteudo)
        return PATH_PAREDE;
    }
  }

  return PATH_CAMINHO;
}

void path_AddOpenList(int valor) {
  int m,temp;

  path_listaAberta[++numOpenList]=valor;

  for (m = numOpenList; m != 1 ;m=m/2) {
     if (path_elemtUsado[path_listaAberta[m]].FCust <= path_elemtUsado[path_listaAberta[m/2]].FCust) {
        temp = path_listaAberta[m/2];
        path_listaAberta[m/2] = path_listaAberta[m];
        path_listaAberta[m] = temp;
     }
     else
       break;
  }
}

void path_DelOpenList() {
  int u=0,v=1,temp;
  path_listaAberta[1] = path_listaAberta[numOpenList--];

  do {
    u=v;
    if (2*u+1 <= numOpenList) {
      if (path_elemtUsado[path_listaAberta[u]].FCust >= path_elemtUsado[path_listaAberta[2*u]].FCust) v=2*u;
      if (path_elemtUsado[path_listaAberta[v]].FCust >= path_elemtUsado[path_listaAberta[2*u+1]].FCust) v=2*u+1;
    }
    else if (2*u <= numOpenList) {
      if (path_elemtUsado[path_listaAberta[u]].FCust >= path_elemtUsado[path_listaAberta[2*u]].FCust)
        v=2*u;
    }

    if (u != v) {
      temp = path_listaAberta[u];
      path_listaAberta[u] = path_listaAberta[v];
      path_listaAberta[v] = temp;
    }
  } while (u != v);
}

void pathAlocaListas(int mapaW, int mapaH) {
  int i,tamanhoTotalMap=mapaW*mapaH;
  static int oldMapaW=0,oldMapaH=0;

  if ((oldMapaW == mapaW) && (oldMapaH == mapaH)) return;

  if (path_elemtUsado != NULL) free(path_elemtUsado);
  if (path_listaAberta != NULL) free(path_listaAberta);

  if (path_listas != NULL) {
    for(i=0;i<oldMapaH;i++)
      free(path_listas[i]);
    free(path_listas);
  }

  oldMapaW=mapaW;
  oldMapaH=mapaH;

  path_elemtUsado=(struct pathUtil *) calloc(tamanhoTotalMap,sizeof(struct pathUtil));
  path_listaAberta=(int *) calloc(tamanhoTotalMap+1,sizeof(int));

  path_listas=(int **) calloc(mapaH,sizeof(int *));
  for(i=0;i<mapaH;i++)
    path_listas[i]=(int *) calloc(mapaW,sizeof(int));
}

int pathFind(int destinoX, int destinoY, pathfinder *path, unsigned char **mapa, int mapaW, int mapaH) {
  int percX,percY;
  int paiXval=0,paiYval=0;
  int GDirecao,conteudo,percorre,totalLista=0,valor;
  unsigned char caminho;
  struct pathUtil *posAtual,*ptmp=NULL;

  pathTamMapW=mapaW;
  pathTamMapH=mapaH;

  caminho=pathVerifAndar(path,mapa,destinoX,destinoY);

  if ((caminho==PATH_PAREDE) || ((path->atualX==destinoX) && (path->atualY==destinoY)) || ((path->destinoX==destinoX) && (path->destinoY==destinoY))) {
    path->achou=(caminho==PATH_CAMINHO)?PATH_ACHOU:PATH_NAO_ACHOU;
    return path->achou;
  }

  pathAlocaListas(mapaW,mapaH);

  if (numListaFechada > 1000000) {
    for (percY = 0; percY < pathTamMapH ;percY++) {
      for (percX = 0; percX < pathTamMapW ;percX++) {
        path_listas[percY][percX] = 0;
      }
    }
    numListaFechada = 1;
  }

  numListaAberta=numListaFechada+1;
  numListaFechada+=2;
  numOpenList=0;

  path->destinoX=destinoX;
  path->destinoY=destinoY;

  path_elemtUsado[totalLista].x=path->atualX;
  path_elemtUsado[totalLista].y=path->atualY;
  path_elemtUsado[totalLista].pai=NULL;
  path_elemtUsado[totalLista].FCust=0;
  path_elemtUsado[totalLista].GCust=0;

  path_AddOpenList(totalLista);
  posAtual=&path_elemtUsado[totalLista];

  totalLista++;

  while (numOpenList!=0) {
    paiXval=posAtual->x;
    paiYval=posAtual->y;

    if ((paiXval == destinoX) && (paiYval == destinoY)) break;

    //adiciona lista fechada
    path_listas[paiYval][paiXval]=numListaFechada;

    //remove lista aberta
    path_DelOpenList();

    //Percorre os nos irmaos
    for (percY=-1; percY <= 1 ;percY++) {
      for (percX=-1; percX <= 1 ;percX++) {
        if ((percX==0) && (percY==0))
          continue;

        int posNovaX=paiXval+percX;
        int posNovaY=paiYval+percY;

        if (pathVerifAndar(path,mapa,posNovaX,posNovaY) == PATH_PAREDE)
          continue;

        if ((percX==0) || (percY==0)) GDirecao=10;
        else {
          //verifica se tem parede entre a diagonal
          if (pathVerifAndar(path,mapa,paiXval+percX,paiYval) == PATH_PAREDE)
            continue;
          if (pathVerifAndar(path,mapa,paiXval,paiYval+percY) == PATH_PAREDE)
            continue;

          GDirecao=14;
        }

        conteudo=path_listas[posNovaY][posNovaX];

        if (conteudo==numListaFechada)
          continue;
        else if (conteudo==numListaAberta) {
          //procura elemento na lista aberta
          for (percorre=1; percorre <= numOpenList ;percorre++) {
            valor=path_listaAberta[percorre];
            if ((path_elemtUsado[valor].x == posNovaX) && (path_elemtUsado[valor].y == posNovaY)) {
              //verifica se trocando de pai o GCust fica menor
              if (path_elemtUsado[valor].GCust > posAtual->GCust+GDirecao) {
                ptmp=&path_elemtUsado[valor];
                conteudo=(percorre*-1)-2;
              }
              else
                ptmp=NULL;

              break;
            }
          }
        }
        else {
          conteudo=-1;
          ptmp=&path_elemtUsado[totalLista];
        }

        if (ptmp==NULL) continue;

        ptmp->x=posNovaX;
        ptmp->y=posNovaY;
        ptmp->pai=posAtual;
        ptmp->GCust=posAtual->GCust+GDirecao;
        ptmp->FCust=ptmp->GCust + 10*(abs(ptmp->x - destinoX) + abs(ptmp->y - destinoY));

        path_listas[ptmp->y][ptmp->x]=numListaAberta;

        if (conteudo == -1) {
          //Adiciona item na lista Aberta
          path_AddOpenList(totalLista);
          totalLista++;
        }
        else if (conteudo < -1) {
          //Troca posicao depois de ter atualizado o ZCust
          for (percorre=(conteudo+2)*-1; percorre != 1 ;percorre = percorre/2) {
            if (path_elemtUsado[path_listaAberta[percorre]].FCust <= path_elemtUsado[path_listaAberta[percorre/2]].FCust) {
               conteudo = path_listaAberta[percorre/2];
               path_listaAberta[percorre/2] = path_listaAberta[percorre];
               path_listaAberta[percorre] = conteudo;
            }
            else
              break;
          }
        }
      }
    }

    //Seta o elemento que possui o menor FCust como o atual
    posAtual=&path_elemtUsado[path_listaAberta[1]];
  }

  if ((paiXval != destinoX) && (paiYval != destinoY)) {
    path->achou=PATH_NAO_ACHOU;
    return PATH_NAO_ACHOU;
  }

  for (ptmp=posAtual, percorre=0; ptmp!=NULL ;ptmp=ptmp->pai,percorre++);

  path->tamanho=percorre-1;
  path->posicao=0;
  path->chegou=0;

  if (path->dest) free(path->dest);

  if (percorre > 0) {
    path->dest=(posXY_int *) calloc(percorre-1,sizeof(posXY_int));

    int destinoX2=-50;
    int destinoY2=-50;

    for (percorre-=2; posAtual!=NULL && posAtual->pai != NULL; posAtual=posAtual->pai, percorre--) {
      if (path->interacao_id != -1) {
        if (mapa[posAtual->y][posAtual->x] == PATH_CAMINHO_INTERACAO) {
          path->tamanho--;
          continue;
        }
      }
      if ((destinoX2==-50) && (destinoY2==-50)) {
          destinoX2=posAtual->x;
          destinoY2=posAtual->y;
      }

      path->dest[percorre].x=posAtual->x;
      path->dest[percorre].y=posAtual->y;
    }

    //Caso o caminho for do tipo interacao ele chegou ao destino
    if ((destinoX2==-50) && (destinoY2==-50)) {
      destinoX2=path->atualX;
      destinoY2=path->atualY;

      path->chegou=1;
    }

    path->destinoX=destinoX2;
    path->destinoY=destinoY2;
  }

  path->achou=PATH_ACHOU;
  return PATH_ACHOU;
}

void pathMove(pathfinder *path,char *lado) {
  char ladoUsar=-1;
  int xPath=0,yPath=0;

  if (path->posicao < path->tamanho) {
    xPath=path->dest[path->posicao].x;
    yPath=path->dest[path->posicao].y;

    path->posicao++;
  }
  else {
    path->chegou=1;
    return;
  }

  if (path->atualY > yPath) { path->atualY-=1; ladoUsar=1; }
  if (path->atualY < yPath) { path->atualY+=1; ladoUsar=2; }
  if (path->atualX > xPath) {
    path->atualX-=1;
    if (ladoUsar==-1) ladoUsar=3;
    else {
      if (ladoUsar==2) ladoUsar=7;
      else ladoUsar=4;
    }
  }
  if (path->atualX < xPath) {
    path->atualX+=1;
    if (ladoUsar==-1) ladoUsar=0;
    else {
      if (ladoUsar==2) ladoUsar=6;
      else ladoUsar=5;
    }
  }
  if (path->posicao == path->tamanho) {
    if (abs(path->atualX - xPath) == 0) path->atualX=xPath;
    if (abs(path->atualY - yPath) == 0) path->atualY=yPath;
    path->chegou=1;
  }

  if ((ladoUsar!=-1) && (lado != NULL))
    *lado=ladoUsar;
}

void fimPathfind() {
  if (path_elemtUsado != NULL) free(path_elemtUsado);
  if (path_listaAberta != NULL) free(path_listaAberta);

  if (path_listas != NULL) {
    /*for(i=0;i<oldMapaH;i++)
      free(path_listas[i]);*/
    free(path_listas);
  }
}

int pathFindPadrao(int destinoX, int destinoY, pathfinder *path) {
  return pathFind(destinoX,destinoY,path,MAPA_PATHFIND,map_sizex*MAPA_PATHFIND_VEZES_X,map_sizey*MAPA_PATHFIND_VEZES_Y);
}
