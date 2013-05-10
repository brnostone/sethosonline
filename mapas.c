#include <stdio.h>

#include "Header/lightmap.h"
#include "Header/global.h"
#include "Header/mapas.h"
#include "Header/personagem.h"
#include "Header/animais.h"
#include "Header/monstros.h"
#include "Header/flechas.h"
#include "Header/magicas.h"
#include "Header/interacao.h"
#include "Header/npcs.h"
#include "Header/log.h"
#include "Header/caracteristicas.h"
#include "Header/crypto.h"
#include "Header/mapas.h"

int map_sizex=0;
int map_sizey=0;

struct oredCriarMapa {
  int id;
  char tipo;
  int y;
};

void criarmap() {
  int xpos2=(xpos/64),ypos2=(ypos/48);
  int tempx2,tempy2;
  int cirarmpx,cirarmpy;
  char mouseencima2=0,tipotemp;

  mouseencima&=2;
  for (cirarmpy=0; cirarmpy<=13 ;cirarmpy++) {
    for (cirarmpx=0; cirarmpx<=13 ;cirarmpx++) {
      if ((cirarmpx+xpos2<map_sizex) && (cirarmpy+ypos2<map_sizey)) {
        tempx2=(cirarmpx*64)-xpos%64;
        tempy2=(cirarmpy*48)-ypos%48;

        if (map[cirarmpy+ypos2][cirarmpx+xpos2])
          DrawImg_LightMap(title[tipochao[cirarmpy+ypos2][cirarmpx+xpos2]-1],tempx2,tempy2,64,48,((map[cirarmpy+ypos2][cirarmpx+xpos2]-1)%8)*64,((map[cirarmpy+ypos2][cirarmpx+xpos2]-1)/8)*48);
        if (map2[cirarmpy+ypos2][cirarmpx+xpos2])
          DrawImg_LightMap(title[tipochao2[cirarmpy+ypos2][cirarmpx+xpos2]-1],tempx2,tempy2,64,48,((map2[cirarmpy+ypos2][cirarmpx+xpos2]-1)%8)*64,((map2[cirarmpy+ypos2][cirarmpx+xpos2]-1)/8)*48);

        tipotemp=itenschao[0][cirarmpy+ypos2][cirarmpx+xpos2];
        if (tipotemp) {
          if (mouseverondeclia(tempx2,tempx2+63,tempy2,tempy2+47)) { mouseencima|=1; mouseencima2=1; }
          if (tipotemp==1)
            DrawImg_LightMap(helmschao,tempx2,tempy2,64,48,(itenschao[1][cirarmpy+ypos2][cirarmpx+xpos2]-1)*64,mouseencima2*48);
          else if ((tipotemp>=2) && (tipotemp<=3))
            DrawImg_LightMap(armesccaho,tempx2,tempy2,64,48,(itenschao[1][cirarmpy+ypos2][cirarmpx+xpos2]-1)*64,(tipotemp-2)*96+mouseencima2*48);
          else if ((tipotemp>=4) && (tipotemp<=8))
            DrawImg_LightMap(armasnochao,tempx2,tempy2,64,48,(itenschao[1][cirarmpy+ypos2][cirarmpx+xpos2]-1)*64,(tipotemp-4)*96+mouseencima2*48);
          else if ((tipotemp>=9) && (tipotemp<=10))
            DrawImg_LightMap(amuletosanelchao,tempx2+16,tempy2+9,32,30,(itenschao[1][cirarmpy+ypos2][cirarmpx+xpos2]-1)*32,(tipotemp-9)*60+mouseencima2*30);
          else if ((tipotemp>=11) && (tipotemp<=13))
            DrawImg_LightMap(barclubochao,tempx2+16,tempy2+9,32,30,(itenschao[1][cirarmpy+ypos2][cirarmpx+xpos2]-1)*32,(tipotemp-11)*60+mouseencima2*30);
          else if (tipotemp==14)
            DrawImg_LightMap(capaschao,tempx2,tempy2-3,64,51,(itenschao[1][cirarmpy+ypos2][cirarmpx+xpos2]-1)*64,mouseencima2*51);
          else if (tipotemp==15)
            DrawImg_LightMap(itenschaoi,tempx2+9,tempy2+9,30,30,(itenschao[1][cirarmpy+ypos2][cirarmpx+xpos2]-1)*30,mouseencima2*30);
          else if (tipotemp==17)
            DrawImg_LightMap(itens2chaoi,tempx2+8,tempy2,48,48,(itenschao[1][cirarmpy+ypos2][cirarmpx+xpos2]-1)*48,mouseencima2*48);
          else if (tipotemp==53)
            DrawImg_LightMap(dinheirochao,tempx2+9,tempy2+9,30,30,(itenschao[1][cirarmpy+ypos2][cirarmpx+xpos2]-1)*30,mouseencima2*30);
          mouseencima2=0;
        }
      }
    }
  }
}

void criarmap3() {
  int xpos2=(xpos/64),ypos2=(ypos/48);
  int posX,posY;
  int cirarmpx,cirarmpy;

  cirarmpx=0,cirarmpy=0;
  while(cirarmpy<=39) {
    while(cirarmpx<=52) {
      if ((cirarmpx+xpos2*4<map_sizex*4) && (cirarmpy+ypos2*3<map_sizey*3)) {
        if (mapcaminhar[cirarmpy+ypos2*3][cirarmpx+xpos2*4]) {
          posX=(cirarmpx*16)-xpos%64;
          posY=(cirarmpy*16)-ypos%48;

          if (mapcaminhar[cirarmpy+ypos2*3][cirarmpx+xpos2*4]==1)
            fillRectangle(posX,posY,16,16,100,100,100,255);
          else if (mapcaminhar[cirarmpy+ypos2*3][cirarmpx+xpos2*4]==2)
            fillRectangle(posX,posY,16,16,10,110,250,255);
          else if (mapcaminhar[cirarmpy+ypos2*3][cirarmpx+xpos2*4]==8)
            fillRectangle(posX,posY,16,16,133,77,9,255);
          else if (mapcaminhar[cirarmpy+ypos2*3][cirarmpx+xpos2*4]==9)
            fillRectangle(posX,posY,16,16,50,250,50,255);
          else if (mapcaminhar[cirarmpy+ypos2*3][cirarmpx+xpos2*4]>2)
            fillRectangle(posX,posY,16,16,250,250,50,255);
        }
      }
      cirarmpx++;
    }
    cirarmpx=0;
    cirarmpy++;
  }
}

void Draw_Algo(char tipo,int id) {
  switch(tipo) {
    case 'm': draw_monstros(id); break;
    case 'n': draw_npcs(id); break;
    case 'f': draw_arrow(id); break;
    case 'g': draw_magic(id); break;
    case 'a': Draw_Animal(id); break;
    case 'p': {
      if (personagem.aura!=0) {
        if (personagem.aura==1) { DrawIMG(blackaura[personagem.auraimagem],personagem.x-xpos-6,personagem.y-ypos+28,108,86,0,0); }
        else if (personagem.aura==2) { DrawIMG(aurazul[personagem.auraimagem],personagem.x-xpos,personagem.y-ypos+38,96,72,0,0); }
        else if (personagem.aura==3) { DrawIMG(aurawhite[personagem.auraimagem],personagem.x-xpos-8,personagem.y-ypos+30,104,77,0,0); }
        else if (personagem.aura==4) { if (personagem.auraimagem<5) { DrawIMG(auraverde[personagem.auraimagem],personagem.x-xpos+3,personagem.y-ypos+38,87,71,0,0); } }
        else if (personagem.aura==5) { DrawIMG(auraba[personagem.auraimagem],personagem.x-xpos+5,personagem.y-ypos+36,85,68,0,0); }
        else if (personagem.aura==6) { DrawIMG(auragirado[personagem.auraimagem],personagem.x-xpos+9,personagem.y-ypos+37,76,65,0,0); }
      }
      drawpersonagem();
      break;
    }
  }
}

int oredCriarMapa_cmp(const void *c1, const void *c2){
  int temp=((struct oredCriarMapa *)c1)->y-((struct oredCriarMapa *)c2)->y;
  if (temp > 0)
    return 1;
  else if (temp < 0)
    return -1;
  else
    return 0;
}

void criarmap2() {
  char tempoas=0,botouimagem=0,botouimagem2[nummonstro],botouimagem3[NUM_NPCS];
  int xpos2=(xpos/64),ypos2=(ypos/48);
  int cirarmpx, cirarmpy;
  int qual,cursorant[2],numitemsqtr;
  int cont1;
  Lista *percorreLista;
  struct oredCriarMapa oredem[50];

  cursorant[0]=CursorUsando[0];
  cursorant[1]=CursorUsando[1];

  CursorUsando[0]=0;
  CursorUsando[1]=0;

  if (numarrow) ativar_arrow();
  if (nummagic) ativar_magic();

  memset(botouimagem2, 0, sizeof(botouimagem2));
  memset(botouimagem3, 0, sizeof(botouimagem3));

  for (cirarmpy=-1; cirarmpy<=14 ;cirarmpy++) {
    for (cirarmpx=-1; cirarmpx<=15 ;cirarmpx++) {
      if (cirarmpy+ypos2<0) cirarmpy=0;
      if (cirarmpx+xpos2<0) cirarmpx=0;
      numitemsqtr=0;

      forList (struct arrow *, fechaTmp, primarrow) {
        if ((fechaTmp->ativa==1) && (cirarmpx==((int)fechaTmp->posx)/64-xpos2) && (cirarmpy==((int)fechaTmp->posy+40)/48-ypos2))  {
          if (numitemsqtr<50) {
            oredem[numitemsqtr].id=fechaTmp_Id;
            oredem[numitemsqtr].tipo='f';
            oredem[numitemsqtr++].y=fechaTmp->posy+40;
          }
          else Draw_Algo('f',fechaTmp_Id);
          fechaTmp->ativa=0;
        }
      }
      forList (struct magic *, magicaTmp, primmagic) {
        if ((magicaTmp->ativa==1) && (cirarmpx==(magicaTmp->posx+Info_Magic(magicaTmp->qual,'x'))/64-xpos2) && (cirarmpy==(magicaTmp->posy+Info_Magic(magicaTmp->qual,'y'))/48-ypos2)) {
          if (numitemsqtr<50) {
            oredem[numitemsqtr].id=magicaTmp_Id;
            oredem[numitemsqtr].tipo='g';
            oredem[numitemsqtr++].y=magicaTmp->posy+Info_Magic(magicaTmp->qual,'y');
          }
          else Draw_Algo('g',magicaTmp_Id);
          magicaTmp->ativa=0;
        }
      }
//FIXME: modificar para forList
      for (qual=0,percorreLista=primmonstro; percorreLista!=NULL; percorreLista=percorreLista->prox,qual++) {
        monstroatual=(struct monstro *) percorreLista->d;

        if ((!botouimagem2[qual]) && (cirarmpx==(monstroatual->x)/64-xpos2) && (cirarmpy==(monstroatual->y+110)/48-ypos2)) {
          if (numitemsqtr<50) {
            oredem[numitemsqtr].id=percorreLista->id;
            oredem[numitemsqtr].tipo='m';
            oredem[numitemsqtr++].y=((monstroatual->acao!=4)?monstroatual->y+110:0);
          }
          else Draw_Algo('m',percorreLista->id);
          botouimagem2[qual]=1;
        }
      }

      forList (struct animal *, animalTmp, primanimais) {
        if ((animalTmp->ativo) && (cirarmpx==(animalTmp->x+Info_Animal(animalTmp->tipo,'x'))/64-xpos2) && (cirarmpy==(animalTmp->y+Info_Animal(animalTmp->tipo,'y'))/48-ypos2)) {
          if (numitemsqtr<50) {
            oredem[numitemsqtr].id=animalTmp_Id;
            oredem[numitemsqtr].tipo='a';
            oredem[numitemsqtr++].y=animalTmp->y+Info_Animal(animalTmp->tipo,'y');
          }
          else Draw_Algo('a',animalTmp_Id);
          animalTmp->ativo=0;
        }
      }

      for (qual=0;qual<NUM_NPCS;qual++) {
        if ((npcs[qual].ativo==1) && (!botouimagem3[qual]) && (cirarmpx==(npcs[qual].posx)/64-xpos2) && (cirarmpy==(npcs[qual].posy+100)/48-ypos2)) {
          if (numitemsqtr<50) {
            oredem[numitemsqtr].id=qual;
            oredem[numitemsqtr].tipo='n';
            oredem[numitemsqtr++].y=npcs[qual].posy+100;
          }
          else Draw_Algo('n',qual);
          botouimagem3[qual]=1;
        }
      }

      if ((!botouimagem) && (cirarmpx==(personagem.x)/64-xpos2) && (cirarmpy==(personagem.y+100)/48-ypos2)) {
        if (numitemsqtr<50) {
          oredem[numitemsqtr].id=1;
          oredem[numitemsqtr].tipo='p';
          oredem[numitemsqtr++].y=personagem.y+100;
        }
        else Draw_Algo('p',1);
        botouimagem=1;
      }

      //Ordenar imagens

      qsort(oredem, numitemsqtr, sizeof(struct oredCriarMapa), oredCriarMapa_cmp);

      //Desenha imagens
      int anterio=0;
      for (cont1=0;cont1<numitemsqtr;cont1++) {
        if (anterio>oredem[cont1].y) printf("erro ordenacao %d %d\n",anterio,oredem[cont1].y);
        Draw_Algo(oredem[cont1].tipo,oredem[cont1].id);
      }

      if ((cirarmpx+xpos2<map_sizex) && (cirarmpy+ypos2<map_sizey)) {
        tempoas=mapobjetostipo[cirarmpy+ypos2][cirarmpx+xpos2];

        if (tempoas!=0){
          if (tempoas/NUM_TITLE<1) {
            tempoas=tempoas-((tempoas/NUM_TITLE)*NUM_TITLE);
            DrawImg_LightMap(parede[tempoas-1],(cirarmpx*64-tamanhoParedes(tempoas,'x'))-xpos%64,(cirarmpy*48-tamanhoParedes(tempoas,'y'))-ypos%48,tamanhoParedes(tempoas,'w'),tamanhoParedes(tempoas,'h'),((mapobjetos[cirarmpy+ypos2][cirarmpx+xpos2]-1)%8)*tamanhoParedes(tempoas,'w'),((mapobjetos[cirarmpy+ypos2][cirarmpx+xpos2]-1)/8)*tamanhoParedes(tempoas,'h'));
          }
          else if (tempoas/NUM_TITLE<3) {
            tempoas=tempoas-((tempoas/NUM_TITLE)*NUM_TITLE);
            DrawImg_LightMap(objetos[tempoas-1],(cirarmpx*64-tamanhoObjetos(tempoas,'x'))-xpos%64,(cirarmpy*48-tamanhoObjetos(tempoas,'y'))-ypos%48,tamanhoObjetos(tempoas,'w'),tamanhoObjetos(tempoas,'h'),((mapobjetos[cirarmpy+ypos2][cirarmpx+xpos2]-1)%8)*tamanhoObjetos(tempoas,'w'),((mapobjetos[cirarmpy+ypos2][cirarmpx+xpos2]-1)/8)*tamanhoObjetos(tempoas,'h'));
          }
          else if (tempoas/NUM_TITLE==3) {
            tempoas=tempoas-((tempoas/NUM_TITLE)*NUM_TITLE);
            DrawImg_LightMap(casa[tempoas-1], (cirarmpx*64-tamanhoCasa(tempoas,'x'))-xpos%64, (cirarmpy*48-tamanhoCasa(tempoas,'y'))-ypos%48,tamanhoCasa(tempoas,'w'),tamanhoCasa(tempoas,'h'),((mapobjetos[cirarmpy+ypos2][cirarmpx+xpos2]-1)%8)*tamanhoCasa(tempoas,'w'),((mapobjetos[cirarmpy+ypos2][cirarmpx+xpos2]-1)/8)*tamanhoCasa(tempoas,'h'));
          }
          else {
            tempoas=tempoas-((tempoas/NUM_TITLE)*NUM_TITLE);
            int posicao_x=(cirarmpx*64-tamanhoInteracao(tempoas,'x'))-xpos%64;
            int posicao_y=(cirarmpy*48-tamanhoInteracao(tempoas,'y'))-ypos%48;
            int tipo=(mapobjetos[cirarmpy+ypos2][cirarmpx+xpos2]-1);

            if (mouseverondeclia(posicao_x,posicao_x+tamanhoInteracao(tempoas,'w'),posicao_y,posicao_y+tamanhoInteracao(tempoas,'h'))) {
              if (tipo>=interacao_caract(tempoas,'a')) {
                int percorre;

                tipo+=interacao_caract(tempoas,'m');

                CursorUsando[0]=-1;
                CursorUsando[1]=cursorant[1];

                //procura pela interacao na lista
                for (percorre=0;percorre<inter_position.quantidade;percorre++) {
                  if (inter_position.qual[percorre]==&mapobjetos[cirarmpy+ypos2][cirarmpx+xpos2]) {
                    CursorUsando[1]=percorre;
                    break;
                  }
                }

                if (percorre>=inter_position.quantidade) CursorUsando[0]=0;
              }
            }

            DrawImg_LightMap(interacao[tempoas-1], posicao_x, posicao_y,tamanhoInteracao(tempoas,'w'),tamanhoInteracao(tempoas,'h'),tipo*tamanhoInteracao(tempoas,'w'),0);
          }
        }
      }
    }
  }
  if (CursorUsando[0]==0) {
    int mousePosY=(mousemovidoy+ypos)/16;
    int mousePosX=(mousemovidox+xpos)/16;

    if ((mousePosX<map_sizex*MAPA_PATHFIND_VEZES_X) && (mousePosY<map_sizey*MAPA_PATHFIND_VEZES_Y)) {
      if ((mapcaminhar[mousePosY][mousePosX]>2) && (mapcaminhar[mousePosY][mousePosX]<8))
        CursorUsando[0]=2;
    }
  }
  if (mousemovidoy>=534) { CursorUsando[0]=0; CursorUsando[1]=0; }
}

void liberarMatriz(unsigned char ***matriz, int tamanhoY){
  int percorreY;
  unsigned char **oldAloc=*matriz;

  if ((tamanhoY != 0) && (matriz != NULL)) {
    for (percorreY=0; percorreY < tamanhoY; percorreY++)
      free(oldAloc[percorreY]);

    free(oldAloc);
  }

  *matriz=NULL;
}

void alocMatriz(unsigned char ***parmAloc, int quantX, int quantY, int oldX, int oldY) {
  int percorreY;
  unsigned char **tmpAloc;
  unsigned char **oldAloc=*parmAloc;

  tmpAloc=(unsigned char **) calloc(quantY, sizeof(unsigned char *));
  for (percorreY=0; percorreY < quantY; percorreY++)
    tmpAloc[percorreY]=(unsigned char *) calloc(quantX, sizeof(unsigned char));

  liberarMatriz(&oldAloc, oldY);

  *parmAloc=tmpAloc;
}

int chave[13]={0x57,0x54,0xA46,0xA8,0x9B4,0xFA4,0x98,0XAF0,0x51,0x54,0x167,0x46,0x12};

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

  LightMap_atualizar();
}

void Alorcar_Mapa(int rex,int rey) {
  int vezesWidth=MAPA_PATHFIND_VEZES_X;
  int vezesHeight=MAPA_PATHFIND_VEZES_Y;

  alocMatriz(&map, rex, rey, map_sizex, map_sizey);
  alocMatriz(&map2, rex, rey, map_sizex, map_sizey);
  alocMatriz(&tipochao, rex, rey, map_sizex, map_sizey);
  alocMatriz(&tipochao2, rex, rey, map_sizex, map_sizey);
  alocMatriz(&mapobjetostipo, rex, rey, map_sizex, map_sizey);
  alocMatriz(&mapobjetos, rex, rey, map_sizex, map_sizey);
  alocMatriz(&mapcaminhar, rex*vezesWidth, rey*vezesHeight, map_sizex*vezesWidth, map_sizey*vezesHeight);

  map_sizex=rex;
  map_sizey=rey;

  mapWidth=map_sizex*vezesWidth;
  mapHeight=map_sizey*vezesHeight;
}

void Liberar_Mapa() {
  liberarMatriz(&map, map_sizey);
  liberarMatriz(&map2, map_sizey);
  liberarMatriz(&tipochao, map_sizey);
  liberarMatriz(&tipochao2, map_sizey);
  liberarMatriz(&mapobjetostipo, map_sizey);
  liberarMatriz(&mapobjetos, map_sizey);
  liberarMatriz(&mapcaminhar, map_sizey*MAPA_PATHFIND_VEZES_Y);
}

void lermapafile(char *text,int x, int y) {
  logging(1,"Carregando Mapa:");

  int newWidth=0;
  int newHeight=0;

  personagem.x=x;
  personagem.y=y;
  personagem.pathFind.atualX=(x+40)/16;
  personagem.pathFind.atualY=(y+64)/16;

  ypos=y-200;
  xpos=x-300;
  if (ypos<0) ypos=0;
  if (xpos<0) xpos=0;

  FILE *fp;
  fp = fopen(text, "rb");
  if(fp == NULL) { logging(3,"Nao foi possivel abrir o mapa: %s",text); logging(2,"ERRO"); exit(1); }
  fread(&newWidth, sizeof(newWidth), 1, fp);
  fread(&newHeight, sizeof(newHeight), 1, fp);

  Alorcar_Mapa(newWidth, newHeight);

  mapdescripto(fp,map,1,1);
  mapdescripto(fp,map2,1,1);
  mapdescripto(fp,tipochao,1,1);
  mapdescripto(fp,tipochao2,1,1);
  mapdescripto(fp,mapobjetos,1,1);
  mapdescripto(fp,mapobjetostipo,1,1);
  mapdescripto(fp,mapcaminhar,4,3);

  fread(qualmapa, sizeof(qualmapa), 1, fp);

  mapLightMapLoad(fp);

  fclose(fp);

  interacao_int();

  logging(2,"OK");
}

/*
  evento:
    'c' = click do mouse
    'm' = mover mouse ou pathFind moveu tela
*/
void chamarPathFind(char evento) {
  int moverX=(mousemovidox+xpos)/16;
  int moverY=(mousemovidoy+ypos)/16;

  char executar=1;

  personagem.pathFind.interacao_id=-1;

  if ((CursorUsando[0] == -1) && (CursorUsando[1] >= 0)) {
    if (evento == 'c') {
      moverX=(inter_position.posicao[CursorUsando[1]].x*64)/16+2;
      moverY=(inter_position.posicao[CursorUsando[1]].y*48)/16+2;

      personagem.pathFind.interacao_id=CursorUsando[1];
    }
    else
      executar=0;
  }

  if (executar) {
    personagem.SegueOq=CursorUsando[0];
    personagem.SegueID=CursorUsando[1];
    personagem.acao=(lctrlpress==1)?2:1;

    pathFindPadrao(moverX,moverY,&personagem.pathFind);
  }

  personagem.pathFind.interacao_id=-1;
}
