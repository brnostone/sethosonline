#include <math.h>

#include "Header/telas.h"
#include "Header/lightmap.h"
#include "Header/global.h"
#include "Header/mapas.h"
#include "Header/caracteristicas.h"
#include "Header/online.h"
#include "Header/modoconstrucao.h"

void ModoConstrucao_Start() {
  Tela_Selecionar(3);
  lightmap.ativo=0;

  xpos=0;
  ypos=0;
  Alorcar_Mapa(40, 40);

  objets_mapas(-1);

  int i,j;
  for (i=0;i<map_sizey;i++) {
    for (j=0;j<map_sizex;j++) {
      map[i][j]=1;
      tipochao[i][j]=8;
    }
  }

  modoContrucao.lado=0;
}

void ModoConstrucao_getMouseParede(int *pX, int *pY) {
  int selX, selY;
  selX=(mousemovidox+xpos+32)/64;
  selY=(mousemovidoy+ypos+24)/48;

  if ((selX+selY)&1) {
    *pX=selX;
    *pY=selY;
  }
  else {
    *pX=-1;
    *pY=-1;
  }
}

int ModoConstrucao_VerifObjetos(char qual, int x, int y) {
  if ((x<0) || (y<0) || (x>=map_sizex) || (y>=map_sizey)) return -1;
  if (qual=='o') return mapobjetos[y][x];
  else return mapobjetostipo[y][x];
}

void ModoConstrucao_SetMapa(int x,int y,int tipo,int qual) {
  if (ModoConstrucao_VerifObjetos('o', x, y) >= 0) {
    mapobjetos[y][x]=qual;
    mapobjetostipo[y][x]=tipo;
  }
}

void ModoConstrucao_SelectDraw(char tipo, int x, int y, int titleTipo, int paredeSel) {
  int cor=255;

  if (modoContrucao.tipo == 'r')
    cor=0;

  if (tipo == 'i')
    ModoConstrucao_SetMapa(x, y, titleTipo, paredeSel);
  else if (tipo == 'r')
      ModoConstrucao_SetMapa(x, y, 0, 0);
  else if ((tipo == 'd') && (titleTipo > 0))
    DrawIMG_RGBA(parede[titleTipo-1],x*64-tamanhoParedes(titleTipo,'x')-xpos,y*48-tamanhoParedes(titleTipo,'y')-ypos,tamanhoParedes(titleTipo,'w'),tamanhoParedes(titleTipo,'h'),((paredeSel-1)%8)*tamanhoParedes(titleTipo,'w'),((paredeSel-1)/8)*tamanhoParedes(titleTipo,'h'), 255,cor,cor,150);
}

void ModoConstrucao_AdicionarParede(char tipo) {
  int initX=modoContrucao.x_click, initY=modoContrucao.y_click;
  int endX=0, endY=0;
  int oldX=initX, oldY=initY;
  int menosUp=0;
  int sinal=1;

  int posAddTmpX_Ini, posAddTmpX_Meio, posAddTmpX_Fim;
  int objTmp;

  char lado;

  ModoConstrucao_getMouseParede(&endX, &endY);

  if (((initX == -1) && (initY == -1)) || ((endX == -1) && (endY == -1))) return;

  lado=(((initX <= endX) && (initY <= endY)) || ((initX >= endX) && (initY >= endY)))?2:1;

  menosUp=(initY > endY);
  sinal=((initX > endX)?1:-1);

  //Inicio
  posAddTmpX_Ini=oldX+(lado-2)-(menosUp-1)*sinal;
  if ((ModoConstrucao_VerifObjetos('o',posAddTmpX_Ini, oldY) == 0) || (modoContrucao.tipo == 'r'))
    ModoConstrucao_SelectDraw(tipo, posAddTmpX_Ini, oldY, 3, ((menosUp)?lado:((lado==1)?2:1))+2);

  //Inicio remover errados
  if (tipo == 'i') {
    if (ModoConstrucao_VerifObjetos('o', posAddTmpX_Ini-1, oldY) == 3)
      ModoConstrucao_SelectDraw(tipo, posAddTmpX_Ini - 1, oldY, 0, 0);

    if (ModoConstrucao_VerifObjetos('o', posAddTmpX_Ini+1, oldY) == 4)
      ModoConstrucao_SelectDraw(tipo, posAddTmpX_Ini + 1, oldY, 0, 0);


    objTmp=ModoConstrucao_VerifObjetos('o', posAddTmpX_Ini, oldY-1);
    if ((objTmp <= 2) && (objTmp) && (ModoConstrucao_VerifObjetos('o', posAddTmpX_Ini, oldY) >= 3))
      ModoConstrucao_SelectDraw(tipo, posAddTmpX_Ini, oldY, 0, 0);
  }

  //Meio
  while (1) {

    if ((initX < endX) && (initY < endY))
      initX++, initY++;
    else if ((initX < endX) && (initY > endY))
      initX++, initY--;
    else if ((initX > endX) && (initY < endY))
          initX--, initY++;
    else if ((initX > endX) && (initY > endY))
          initX--, initY--;
    else
      break;

    posAddTmpX_Meio=oldX+(lado-2)-menosUp * sinal;

    //Meio remover errados
    if (tipo == 'i') {
      if ((posAddTmpX_Meio+1 != posAddTmpX_Ini) && (ModoConstrucao_VerifObjetos('o', posAddTmpX_Meio+1, oldY-menosUp) == 4))
        ModoConstrucao_SelectDraw(tipo, posAddTmpX_Meio + 1, oldY-menosUp, 0, 0);

      if ((posAddTmpX_Meio-1 != posAddTmpX_Ini) && (ModoConstrucao_VerifObjetos('o', posAddTmpX_Meio-1, oldY-menosUp) == 3))
        ModoConstrucao_SelectDraw(tipo, posAddTmpX_Meio - 1, oldY-menosUp, 0, 0);
    }

    //adicionar no meio
    ModoConstrucao_SelectDraw(tipo, posAddTmpX_Meio, oldY-menosUp, 3, lado);

    oldX=initX;
    oldY=initY;
  }

  //Final
  posAddTmpX_Fim=oldX+(lado-2)-menosUp * sinal;

  if ((ModoConstrucao_VerifObjetos('o', posAddTmpX_Fim, oldY) == 0) || (modoContrucao.tipo == 'r'))
    ModoConstrucao_SelectDraw(tipo, posAddTmpX_Fim, oldY, 3, ((menosUp)?((lado==1)?2:1):lado)+2);

  //Final remover errados
  if (tipo == 'i') {
    if (ModoConstrucao_VerifObjetos('o', posAddTmpX_Fim+1, oldY) == 4)
      ModoConstrucao_SelectDraw(tipo, posAddTmpX_Fim + 1, oldY, 0, 0);

    objTmp=ModoConstrucao_VerifObjetos('o', posAddTmpX_Fim, oldY-1);
    if ((objTmp <= 2) && (objTmp) && (ModoConstrucao_VerifObjetos('o', posAddTmpX_Fim, oldY) >= 3))
      ModoConstrucao_SelectDraw(tipo, posAddTmpX_Fim, oldY, 0, 0);
  }
}

void ModoConstrucao_RemoveParede2() {
	  int initX=modoContrucao.x_click, initY=modoContrucao.y_click;
	  int endX=0, endY=0;
	  int oldX=initX, oldY=initY;
	  int menosUp=0;
	  int sinal=1;

	  int posAddTmpX_Ini, posAddTmpX_Ini2, posAddTmpX_Ini3;
	  int posAddTmpX_Meio;
	  int posAddTmpX_Fim, posAddTmpX_Fim2;
	  int objTmp, objTmp2, objTmp3;
	  int ladoTmp;

	  char ultiDel=0;
	  char podeAdd;
	  char lado;

	  ModoConstrucao_getMouseParede(&endX, &endY);

	  if (((initX == -1) && (initY == -1)) || ((endX == -1) && (endY == -1))) return;

	  podeAdd=((initX != endX) || (initY != endY));

	  lado=(((initX <= endX) && (initY <= endY)) || ((initX >= endX) && (initY >= endY))) ? 2 : 1;

	  menosUp=(initY > endY);
	  sinal=((initX > endX)?1:-1);

	  //Inicio
	  posAddTmpX_Ini=oldX+(lado-2)-menosUp*sinal;
	  posAddTmpX_Ini2=oldX+(lado-2);
	  posAddTmpX_Ini3=oldX+(lado-2)-(menosUp-1)*sinal;

	  objTmp = ModoConstrucao_VerifObjetos('o', posAddTmpX_Ini, oldY);
	  objTmp2 = ModoConstrucao_VerifObjetos('o', posAddTmpX_Ini2, oldY);
	  objTmp3 = ModoConstrucao_VerifObjetos('o', posAddTmpX_Ini3, oldY);
	  int objTmp4 = ModoConstrucao_VerifObjetos('o', posAddTmpX_Ini2-1, oldY);
	  int objTmp5=ModoConstrucao_VerifObjetos('o', posAddTmpX_Ini2, oldY-1);

	  ladoTmp=((menosUp)?((lado==1)?2:1):lado)+2;


	  if ((objTmp3 >=3) && (objTmp3 != ladoTmp)) {
	    printf("entro\n");
	    if (((objTmp5 != 1) && (objTmp4 != 1)) || (lado == 1)) {
	      printf("remove ini\n");
	  	  ModoConstrucao_SelectDraw('r', posAddTmpX_Ini3, oldY, 0, 0);
	    }
	  }
	  else if ((objTmp2 <= 2) && (objTmp2) && (!objTmp3) && (podeAdd)) {
		  printf("add ini\n");
		  ModoConstrucao_SelectDraw('i', posAddTmpX_Ini, oldY, 3, ladoTmp);
	  }

	  //Meio
	  while (1) {
	    if ((initX < endX) && (initY < endY))
	      initX++, initY++;
	    else if ((initX < endX) && (initY > endY))
	      initX++, initY--;
	    else if ((initX > endX) && (initY < endY))
	          initX--, initY++;
	    else if ((initX > endX) && (initY > endY))
	          initX--, initY--;
	    else
	      break;

	    ultiDel++;
	    posAddTmpX_Meio=oldX+(lado-2)-menosUp * sinal;
	    objTmp=ModoConstrucao_VerifObjetos('o',posAddTmpX_Meio, oldY-menosUp);

	    //remover do meio
	    if ((objTmp <= 2) && (objTmp)) {
	      ultiDel=1;
	    	ModoConstrucao_SelectDraw('r', posAddTmpX_Meio, oldY-menosUp, 0, 0);

	    	objTmp2=ModoConstrucao_VerifObjetos('o', posAddTmpX_Meio, oldY-menosUp+((objTmp == 2)?-1:1));
	    	if (!objTmp2) {
	    	  objTmp=ModoConstrucao_VerifObjetos('o', posAddTmpX_Meio+1, oldY-menosUp);
          if ((objTmp <= 2) && (objTmp)) {
            printf("prim %d %d\n",objTmp,objTmp2);
            ModoConstrucao_SelectDraw('i',  posAddTmpX_Meio, oldY-(menosUp-1)-(objTmp-1), 3, 3);
          }
          objTmp=ModoConstrucao_VerifObjetos('o', posAddTmpX_Meio-1, oldY-menosUp);
          if ((objTmp <= 2) && (objTmp)) {
            printf("seg %d %d\n",objTmp,objTmp2);
            ModoConstrucao_SelectDraw('i',  posAddTmpX_Meio, oldY-(menosUp-1)+(objTmp-2), 3, 4);
          }
	    	}
/*	    	objTmp=ModoConstrucao_VerifObjetos('o', posAddTmpX_Meio-1, oldY-menosUp);
	    	if ((objTmp <= 2) && (objTmp))*/
	    }

	    oldX=initX;
	    oldY=initY;
	  }

	  //Final
	  posAddTmpX_Fim=oldX+(lado-2)-(menosUp-1)*sinal;
	  posAddTmpX_Fim2=oldX+(lado-2)- menosUp*sinal;

	  objTmp=ModoConstrucao_VerifObjetos('o',posAddTmpX_Fim, oldY);
	  objTmp2=ModoConstrucao_VerifObjetos('o',posAddTmpX_Fim2, oldY);
	  ladoTmp=((menosUp)?lado:((lado==1)?2:1))+2;

	  if ((objTmp2 >=3) && (objTmp2 != ladoTmp)) {
	    printf("remove Final\n");
	  	ModoConstrucao_SelectDraw('r', posAddTmpX_Fim2, oldY, 0, 0);
	  }
	  else if ((ultiDel) && (podeAdd)) {
		  printf("add Final\n");
		  ModoConstrucao_SelectDraw('i', posAddTmpX_Fim, oldY, 3, ladoTmp);
	  }

}

void ModoConstrucao_RemoveParede() {
    int initX=modoContrucao.x_click, initY=modoContrucao.y_click;
    int endX=0, endY=0;
    int oldX=initX, oldY=initY;
    int menosUp=0;
    int sinal=1;

    int posAddTmpX_Ini, posAddTmpX_Ini2, posAddTmpX_Ini3;
    int posAddTmpX_Meio;
    int posAddTmpX_Fim, posAddTmpX_Fim2;
    int objTmp, objTmp2, objTmp3;
    int ladoTmp;

    char ultiDel=0;
    char podeAdd;
    char lado;

    ModoConstrucao_getMouseParede(&endX, &endY);

    if (((initX == -1) && (initY == -1)) || ((endX == -1) && (endY == -1))) return;

    podeAdd=((initX != endX) || (initY != endY));

    lado=(((initX <= endX) && (initY <= endY)) || ((initX >= endX) && (initY >= endY))) ? 2 : 1;

    menosUp=(initY > endY);
    sinal=((initX > endX)?1:-1);

    //Inicio
    posAddTmpX_Ini=oldX+(lado-2)-menosUp*sinal;
    posAddTmpX_Ini2=oldX+(lado-2);
    posAddTmpX_Ini3=oldX+(lado-2)-(menosUp-1)*sinal;

    objTmp = ModoConstrucao_VerifObjetos('o', posAddTmpX_Ini, oldY);
    objTmp2 = ModoConstrucao_VerifObjetos('o', posAddTmpX_Ini2, oldY);
    objTmp3 = ModoConstrucao_VerifObjetos('o', posAddTmpX_Ini3, oldY);
    int objTmp4 = ModoConstrucao_VerifObjetos('o', posAddTmpX_Ini2-1, oldY);
    int objTmp5=ModoConstrucao_VerifObjetos('o', posAddTmpX_Ini2, oldY-1);

    ladoTmp=((menosUp)?((lado==1)?2:1):lado)+2;


    if ((objTmp3 >=3) && (objTmp3 != ladoTmp)) {
      printf("entro\n");
      if (((objTmp5 != 1) && (objTmp4 != 1)) || (lado == 1)) {
        printf("remove ini\n");
        ModoConstrucao_SelectDraw('r', posAddTmpX_Ini3, oldY, 0, 0);
      }
    }
    else if ((objTmp2 <= 2) && (objTmp2) && (!objTmp3) && (podeAdd)) {
      printf("add ini\n");
      ModoConstrucao_SelectDraw('i', posAddTmpX_Ini, oldY, 3, ladoTmp);
    }

    //Meio
    while (1) {
      if ((initX < endX) && (initY < endY))
        initX++, initY++;
      else if ((initX < endX) && (initY > endY))
        initX++, initY--;
      else if ((initX > endX) && (initY < endY))
            initX--, initY++;
      else if ((initX > endX) && (initY > endY))
            initX--, initY--;
      else
        break;

      ultiDel++;
      posAddTmpX_Meio=oldX+(lado-2)-menosUp * sinal;
      objTmp=ModoConstrucao_VerifObjetos('o',posAddTmpX_Meio, oldY-menosUp);

      //remover do meio
      if ((objTmp <= 2) && (objTmp)) {
        ultiDel=1;
        ModoConstrucao_SelectDraw('r', posAddTmpX_Meio, oldY-menosUp, 0, 0);

        objTmp2=ModoConstrucao_VerifObjetos('o', posAddTmpX_Meio, oldY-menosUp+((objTmp == 2)?-1:1));
        if (!objTmp2) {
          objTmp=ModoConstrucao_VerifObjetos('o', posAddTmpX_Meio+1, oldY-menosUp);
          if ((objTmp <= 2) && (objTmp)) {
            printf("prim %d %d\n",objTmp,objTmp2);
            ModoConstrucao_SelectDraw('i',  posAddTmpX_Meio, oldY-(menosUp-1)-(objTmp-1), 3, 3);
          }
          objTmp=ModoConstrucao_VerifObjetos('o', posAddTmpX_Meio-1, oldY-menosUp);
          if ((objTmp <= 2) && (objTmp)) {
            printf("seg %d %d\n",objTmp,objTmp2);
            ModoConstrucao_SelectDraw('i',  posAddTmpX_Meio, oldY-(menosUp-1)+(objTmp-2), 3, 4);
          }
        }
/*        objTmp=ModoConstrucao_VerifObjetos('o', posAddTmpX_Meio-1, oldY-menosUp);
        if ((objTmp <= 2) && (objTmp))*/
      }

      oldX=initX;
      oldY=initY;
    }

    //Final
    posAddTmpX_Fim=oldX+(lado-2)-(menosUp-1)*sinal;
    posAddTmpX_Fim2=oldX+(lado-2)- menosUp*sinal;

    objTmp=ModoConstrucao_VerifObjetos('o',posAddTmpX_Fim, oldY);
    objTmp2=ModoConstrucao_VerifObjetos('o',posAddTmpX_Fim2, oldY);
    ladoTmp=((menosUp)?lado:((lado==1)?2:1))+2;

    if ((objTmp2 >=3) && (objTmp2 != ladoTmp)) {
      printf("remove Final\n");
      ModoConstrucao_SelectDraw('r', posAddTmpX_Fim2, oldY, 0, 0);
    }
    else if ((ultiDel) && (podeAdd)) {
      printf("add Final\n");
      ModoConstrucao_SelectDraw('i', posAddTmpX_Fim, oldY, 3, ladoTmp);
    }

}

void ModoConstrucao_drawGrid() {
  int percorreX, percorreY;
  int gridX, gridY;
  int selectX, selectY;

  ModoConstrucao_getMouseParede(&selectX, &selectY);

  for (percorreY=0; percorreY < 13; percorreY++)
    for (percorreX=0; percorreX < 14; percorreX++) {
      if ((percorreX + percorreY + xpos/64 + ypos/48) & 1) {
        gridX=64 * percorreX-xpos%64;
        gridY=48 * percorreY-ypos%48;

        fillRectangle(gridX - 1, gridY - 1, 3, 3, ((percorreX+xpos/64 == selectX) && (percorreY+ypos/48 == selectY)) ? 255 : 0, 0, 0, 255);

        drawLine(gridX, gridY, gridX + 64, gridY + 48, 0, 0, 0, 150);
        drawLine(gridX, gridY, gridX - 64, gridY + 48, 0, 0, 0, 150);
      }
    }
}

char ModoConstrucao_verifMap() {
  return 1;
}

void ModoConstrucao_CriarMapa() {
  int xpos2=(xpos / 64), ypos2=(ypos / 48), tempoas=0;
  int cirarmpx, cirarmpy;

  for (cirarmpy=-1; cirarmpy<=14 ;cirarmpy++) {
    for (cirarmpx=-1; cirarmpx<=15 ;cirarmpx++) {
      if (cirarmpy+ypos2<0) cirarmpy=0;
      if (cirarmpx+xpos2<0) cirarmpx=0;

      if ((cirarmpx+xpos2<map_sizex) && (cirarmpy+ypos2<map_sizey)) {
        tempoas=mapobjetostipo[cirarmpy+ypos2][cirarmpx+xpos2];
        if (tempoas!=0){
          if (tempoas/NUM_TITLE<1) {
            tempoas=tempoas-((tempoas/NUM_TITLE)*NUM_TITLE);
            DrawIMG(parede[tempoas-1],(cirarmpx*64-tamanhoParedes(tempoas,'x'))-xpos%64,(cirarmpy*48-tamanhoParedes(tempoas,'y'))-ypos%48,tamanhoParedes(tempoas,'w'),tamanhoParedes(tempoas,'h'),((mapobjetos[cirarmpy+ypos2][cirarmpx+xpos2]-1)%8)*tamanhoParedes(tempoas,'w'),((mapobjetos[cirarmpy+ypos2][cirarmpx+xpos2]-1)/8)*tamanhoParedes(tempoas,'h'));
          }
          else if (tempoas/NUM_TITLE<3) {
            tempoas=tempoas-((tempoas/NUM_TITLE)*NUM_TITLE);
            DrawIMG(objetos[tempoas-1],(cirarmpx*64-tamanhoObjetos(tempoas,'x'))-xpos%64,(cirarmpy*48-tamanhoObjetos(tempoas,'y'))-ypos%48,tamanhoObjetos(tempoas,'w'),tamanhoObjetos(tempoas,'h'),((mapobjetos[cirarmpy+ypos2][cirarmpx+xpos2]-1)%8)*tamanhoObjetos(tempoas,'w'),((mapobjetos[cirarmpy+ypos2][cirarmpx+xpos2]-1)/8)*tamanhoObjetos(tempoas,'h'));
          }
        }
      }
    }
  }
}

void ModoConstrucao_CriarMapaTMP() {
  int xpos2=(xpos/64),ypos2=(ypos/48),tempoas=0;
  int cirarmpx, cirarmpy;

  for (cirarmpy=-1; cirarmpy<=14 ;cirarmpy++) {
    for (cirarmpx=-1; cirarmpx<=15 ;cirarmpx++) {
      if (cirarmpy+ypos2<0) cirarmpy=0;
      if (cirarmpx+xpos2<0) cirarmpx=0;

      if ((cirarmpx+xpos2<map_sizex) && (cirarmpy+ypos2<map_sizey)) {
        tempoas=mapobjetostipo[cirarmpy+ypos2][cirarmpx+xpos2];

        if (tempoas)
          fillRectangle((cirarmpx*64)-xpos%64,(cirarmpy*48)-ypos%48,64,48,250,250,50,255);
      }
    }
  }
}

void ModoConstrucao_draw() {
  criarmap();
  ModoConstrucao_drawGrid();

  ModoConstrucao_CriarMapaTMP();
  ModoConstrucao_CriarMapa();

  if (modoContrucao.ativo)
    ModoConstrucao_AdicionarParede('d');
}
