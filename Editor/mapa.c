/*
 * mapa.c
 *
 *  Created on: 02/10/2009
 *      Author: bruno
 */
#include <stdio.h>
#include <time.h>

#include "Header/fonte.h"
#include "Header/opengl.h"
#include "Header/global.h"
#include "Header/LightMap.h"
#include "Header/crypto.h"
#include "Header/EditorMapa.h"
#include "Header/mapa.h"

int map_sizex=0, map_sizey=0;

void alocMatriz(unsigned char ***parmAloc, int quantX, int quantY, int oldX, int oldY) {
  int percorreX, percorreY;
  unsigned char **tmpAloc;
  unsigned char **oldAloc=*parmAloc;

  tmpAloc=(unsigned char **) calloc(quantY, sizeof(unsigned char *));
  for (percorreY=0; percorreY < quantY; percorreY++)
    tmpAloc[percorreY]=(unsigned char *) calloc(quantX, sizeof(unsigned char));

  for (percorreY=0; percorreY < quantY; percorreY++) {
    for (percorreX=0; percorreX < quantX; percorreX++) {
      if ((percorreX < oldX) && (percorreY < oldY))
        tmpAloc[percorreY][percorreX]=oldAloc[percorreY][percorreX];
      else
        tmpAloc[percorreY][percorreX]=0;
    }
  }

  if ((percorreY != 0) && (oldAloc != NULL)) {
    for (percorreY=0; percorreY < oldY; percorreY++)
      free(oldAloc[percorreY]);

    free(oldAloc);
  }

  *parmAloc=tmpAloc;
}

void alocarMemMap(int rex,int rey) {
  alocMatriz(&map, rex, rey, map_sizex, map_sizey);
  alocMatriz(&map2, rex, rey, map_sizex, map_sizey);
  alocMatriz(&tipochao, rex, rey, map_sizex, map_sizey);
  alocMatriz(&tipochao2, rex, rey, map_sizex, map_sizey);
  alocMatriz(&mapobjetostipo, rex, rey, map_sizex, map_sizey);
  alocMatriz(&mapobjetos, rex, rey, map_sizex, map_sizey);
  alocMatriz(&mapcaminhar, rex * 4, rey * 3, map_sizex * 4, map_sizey * 3);

  //LightMap_aloca(rex * 4, rey * 3);

  map_sizex=rex;
  map_sizey=rey;

  mapWidth=map_sizex*MAPA_PATHFIND_VEZES_X;
  mapHeight=map_sizey*MAPA_PATHFIND_VEZES_Y;
}

int chave[13]={0x57,0x54,0xA46,0xA8,0x9B4,0xFA4,0x98,0XAF0,0x51,0x54,0x167,0x46,0x12};

void mapcripto(FILE *fl,unsigned char **mapponteiro,int vezx,int vezy) {
  int chave2[13];
  int tempsx,tempsy,incre=0,randnume=0;
  int mapcripto[map_sizey*vezy][map_sizex*vezx];

  memset(mapcripto,'\0',sizeof(mapcripto));

  srand(time(NULL));
  randnume=rand()%50;
  Crypto_geradorkey(randnume,chave2);

  for (tempsy=0;tempsy<(map_sizey*vezy);tempsy++) {
    for (tempsx=0;tempsx<(map_sizex*vezx);tempsx++,incre++)
      mapcripto[tempsy][tempsx]=Crypto_uchar(mapponteiro[tempsy][tempsx], chave, chave2, incre);
  }
  randnume+=268;
  fwrite(&randnume,sizeof(randnume),1,fl);
  fwrite(mapcripto,sizeof(mapcripto),1,fl);
}

void mapLightMapSave(FILE *fl) {
  int chave2[13];
  int mapcripto[mapWidth*mapHeight*3];
  int percorreX,percorreY,cor,incre=0,randnume=0;

  memset(mapcripto,'\0',sizeof(mapcripto));

  srand(time(NULL));
  randnume=rand()%50;
  Crypto_geradorkey(randnume,chave2);

  fwrite(&lightmap.ativo, sizeof(lightmap.ativo), 1, fl);

  if (lightmap.ativo) {
    for (percorreY=0; percorreY<mapHeight ;percorreY++) {
      for (percorreX=0; percorreX<mapWidth ;percorreX++) {
        for (cor=0; cor<3 ;cor++,incre++)
          mapcripto[incre]=Crypto_uchar(LightMap_getColor(percorreX,percorreY,cor), chave, chave2, incre);
      }
    }

    randnume+=34050;

    fwrite(&randnume, sizeof(randnume), 1, fl);
    fwrite(mapcripto, sizeof(mapcripto), 1, fl);
  }
}

void salvarmap(char *arquivo) {
  FILE *fl;
  fl=fopen(arquivo, "wb");
  if (!fl)
    return;

  fwrite(&map_sizex, sizeof(int), 1, fl);
  fwrite(&map_sizey, sizeof(int), 1, fl);
  mapcripto(fl, map, 1, 1);
  mapcripto(fl, map2, 1, 1);
  mapcripto(fl, tipochao, 1, 1);
  mapcripto(fl, tipochao2, 1, 1);
  mapcripto(fl, mapobjetos, 1, 1);
  mapcripto(fl, mapobjetostipo, 1, 1);
  mapcripto(fl, mapcaminhar, 4, 3);
  fwrite(qualmapa, sizeof(qualmapa), 1, fl);

  mapLightMapSave(fl);

  fclose(fl);
}

void mapdescripto(FILE *fl,unsigned char **mapponteiro,int vezx,int vezy) {
  int chave2[13];
  int tempsx,tempsy,incre=0,randnume=0;
  int mapcripto[map_sizey*vezy][map_sizex*vezx];

  memset(mapcripto,'\0',sizeof(mapcripto));

  fread(&randnume,sizeof(randnume),1,fl);
  fread(mapcripto,sizeof(mapcripto),1,fl);

  Crypto_geradorkey(randnume-268,chave2);

  for (tempsy=0; tempsy<(map_sizey*vezy) ;tempsy++) {
    for (tempsx=0; tempsx<(map_sizex*vezx) ;tempsx++,incre++)
      mapponteiro[tempsy][tempsx]=Decrypto_uchar(mapcripto[tempsy][tempsx], chave, chave2, incre);
  }
}

void mapLightMapLoad(FILE *fl) {
  int chave2[13];
  int mapcripto[mapWidth*mapHeight*3];
  unsigned char mapTemp[mapWidth*mapHeight*3];
  int percorre,randnume=0;
  unsigned char cor[3]= { 255, 255, 255 };

  memset(mapcripto,'\0',sizeof(mapcripto));
  memset(mapTemp,'\0',sizeof(mapTemp));

  fread(&lightmap.ativo, sizeof(lightmap.ativo), 1, fl);

  if (lightmap.ativo) {
    fread(&randnume, sizeof(randnume), 1, fl);
    fread(mapcripto, sizeof(mapcripto), 1, fl);

    Crypto_geradorkey(randnume-34050,chave2);

    for (percorre=0; percorre<mapWidth*mapHeight*3 ;percorre++)
      mapTemp[percorre]=Decrypto_uchar(mapcripto[percorre], chave, chave2, percorre);

    LightMap_carregar(mapWidth, mapHeight, cor, mapTemp);
  }

  GUI_AbrirPai();
    CheckBox_setSelect(15,lightmap.ativo);

    if (ComboBox_getValor(5) == 7)
      EditLighAtualizaLight();
  GUI_FecharPai();

  LightMap_atualizar();
}

void lermapafile(char *arquivo) {
  FILE *fl;
  fl=fopen(arquivo, "rb");
  if (!fl)
    return;

  int tempmap_sizex=0;
  int tempmap_sizey=0;

  fread(&tempmap_sizex, sizeof(int), 1, fl);
  fread(&tempmap_sizey, sizeof(int), 1, fl);

  if ((tempmap_sizex != map_sizex) || (tempmap_sizey != map_sizey))
    alocarMemMap(tempmap_sizex,tempmap_sizey);

  mapdescripto(fl, map, 1, 1);
  mapdescripto(fl, map2, 1, 1);
  mapdescripto(fl, tipochao, 1, 1);
  mapdescripto(fl, tipochao2, 1, 1);
  mapdescripto(fl, mapobjetos, 1, 1);
  mapdescripto(fl, mapobjetostipo, 1, 1);
  mapdescripto(fl, mapcaminhar, 4, 3);

  fread(qualmapa, sizeof(qualmapa), 1, fl);

  mapLightMapLoad(fl);

  fclose(fl);
}

