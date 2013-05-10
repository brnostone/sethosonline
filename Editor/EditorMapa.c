#include <stdio.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_gfxPrimitives.h>

#include "Header/fonte.h"
#include "Header/opengl.h"
#include "Header/LightMap.h"
#include "Header/global.h"
#include "Header/estruturas.h"
#include "Header/GUI.h"
#include "Header/mapa.h"
#include "Header/util.h"
#include "Header/EditorMapa.h"

#define TAMANHO_INICIALX 40
#define TAMANHO_INICIALY 40

char objetoSelec=1;
char nomeMapaOpen[250]="../Data/Mapas/";
int editMapMouseX=-1, editMapMouseY=-1;

static int lightFerramSelect=-1;

void EditLighModif(int x, int y);

int tamanhoObjetos(char tipo,char oq) {
  int retorno=0;

  if (tipo==1) {
    if (oq=='x') retorno=64;
    else if (oq=='y') retorno=71;
    else if ((oq=='w') || (oq=='h')) retorno=128;
  }
  else if (tipo==2) {
    if (oq=='x') retorno=30;
    else if (oq=='y') retorno=78;
    else if ((oq=='w') || (oq=='h')) retorno=128;
  }
  else if (tipo==3) {
    if (oq=='x') retorno=0;
    else if (oq=='y') retorno=70;
    else if (oq=='w') retorno=64;
    else if (oq=='h') retorno=96;
  }
  else if (tipo==4) {
    if (oq=='x') retorno=0;
    else if (oq=='y') retorno=75;
    else if (oq=='w') retorno=96;
    else if (oq=='h') retorno=128;
  }
  else if (tipo==5) {
    if (oq=='x') retorno=0;
    else if (oq=='y') retorno=48;
    else if (oq=='w') retorno=96;
    else if (oq=='h') retorno=96;
  }
  else if (tipo==6) {
    if (oq=='x') retorno=0;
    else if (oq=='y') retorno=24;
    else if (oq=='w') retorno=64;
    else if (oq=='h') retorno=64;
  }
  else if (tipo==7) {
    if (oq=='x') retorno=64;
    else if (oq=='y') retorno=70;
    else if (oq=='w') retorno=128;
    else if (oq=='h') retorno=96;
  }
  return retorno;
}

int tamanhoParedes(int tipo,char oq) {
  int retorno=0;
  if (tipo==1) {
    if (oq=='x') retorno=0;
    else if (oq=='y') retorno=105;
    else if (oq=='w') retorno=64;
    else if (oq=='h') retorno=160;
  }
  if (tipo==2) {
    if (oq=='x') retorno=0;
    else if (oq=='y') retorno=141;
    else if (oq=='w') retorno=64;
    else if (oq=='h') retorno=196;
  }
  if (tipo==3) {
    if (oq=='x') retorno=0;
    else if (oq=='y') retorno=115;
    else if (oq=='w') retorno=64;
    else if (oq=='h') retorno=170;
  }
  return retorno;
}

int tamanhoCasa(char tipo,char oq) {
  int retorno=0;
  if (tipo==1) {
    if (oq=='x') retorno=114;
    else if (oq=='y') retorno=135;
    else if (oq=='w') retorno=178;
    else if (oq=='h') retorno=183;
  }
  else if (tipo==2) {
    if (oq=='x') retorno=184;
    else if (oq=='y') retorno=140;
    else if (oq=='w') retorno=248;
    else if (oq=='h') retorno=236;
  }
  return retorno;
}

int tamanhoInteracao(char tipo,char oq) {
  int retorno=0;
  if (tipo==1) {
    if (oq=='x') retorno=0;
    else if (oq=='y') retorno=20;
    else if (oq=='w') retorno=64;
    else if (oq=='h') retorno=64;

//referente a area de atuacao da Interacao
    else if (oq=='a') retorno=0; //mais x
    else if (oq=='b') retorno=0; //mais y
    else if (oq=='q') retorno=4; //quadrados
  }
  else if (tipo==2) {
    if (oq=='x') retorno=16;
    else if (oq=='y') retorno=36;
    else if (oq=='w') retorno=96;
    else if (oq=='h') retorno=96;

    else if (oq=='a') retorno=-1; //mais x
    else if (oq=='b') retorno=-1; //mais y
    else if (oq=='q') retorno=8; //quadrados
  }
  return retorno;
}

void criarmap() {
  int cirarmpx;
  int cirarmpy;

  for (cirarmpy=0; cirarmpy<=12 ;cirarmpy++) {
    for(cirarmpx=0; cirarmpx<=9 ;cirarmpx++) {
      if ((cirarmpx+xpos<map_sizex) && (cirarmpy+ypos<map_sizey)) {
        if (map[cirarmpy+ypos][cirarmpx+xpos])
          DrawImg_LightMap(title[tipochao[cirarmpy+ypos][cirarmpx+xpos]-1],cirarmpx*64,cirarmpy*48,64,48,((map[cirarmpy+ypos][cirarmpx+xpos]-1)%8)*64,((map[cirarmpy+ypos][cirarmpx+xpos]-1)/8)*48);
        if (map2[cirarmpy+ypos][cirarmpx+xpos])
          DrawImg_LightMap(title[tipochao2[cirarmpy+ypos][cirarmpx+xpos]-1],cirarmpx*64,cirarmpy*48,64,48,((map2[cirarmpy+ypos][cirarmpx+xpos]-1)%8)*64,((map2[cirarmpy+ypos][cirarmpx+xpos]-1)/8)*48);
      }
    }
  }
}

/*
1 - Parede
2 - Agua
3 - Portal
4 - Portal
5 - Portal
6 - Portal
7 - Portal
8 - Parede baixa (personagem nao passa mas magica e flecha passam)
9 - Interação
*/

void criarmap3() {
  int cirarmpx=0, cirarmpy=0;
  for (cirarmpy=0; cirarmpy <= 37; cirarmpy++) {
    for (cirarmpx=0; cirarmpx <= 40; cirarmpx++) {
      if ((cirarmpx + xpos * 4 < map_sizex * 4) && (cirarmpy + ypos * 3 < map_sizey * 3)) {
        if (mapcaminhar[cirarmpy + ypos * 3][cirarmpx + xpos * 4] == 1)
          fillRectangle(cirarmpx * 16, cirarmpy * 16, 16, 16, 100, 100, 100, 255);
        else if (mapcaminhar[cirarmpy + ypos * 3][cirarmpx + xpos * 4] == 2)
          fillRectangle(cirarmpx * 16, cirarmpy * 16, 16, 16, 10, 110, 250, 255);
        else if (mapcaminhar[cirarmpy + ypos * 3][cirarmpx + xpos * 4] == 8)
          fillRectangle(cirarmpx * 16, cirarmpy * 16, 16, 16, 133, 77, 9, 255);
        else if (mapcaminhar[cirarmpy + ypos * 3][cirarmpx + xpos * 4] == 9)
          fillRectangle(cirarmpx * 16, cirarmpy * 16, 16, 16, 50, 250, 50, 255);
        else if (mapcaminhar[cirarmpy + ypos * 3][cirarmpx + xpos * 4] > 2)
          fillRectangle(cirarmpx * 16, cirarmpy * 16, 16, 16, 250, 250, 50, 255);
      }
    }
  }
}

void criarmap2() {
  int cirarmpx;
  int cirarmpy;
  int tempoas;

  for (cirarmpy=0; cirarmpy<=14 ;cirarmpy++) {
    for (cirarmpx=0; cirarmpx<=11 ;cirarmpx++) {
      if ((cirarmpx+xpos<map_sizex) && (cirarmpy+ypos<map_sizey)) {
        tempoas=mapobjetostipo[cirarmpy+ypos][cirarmpx+xpos];
        if (tempoas == 0) continue;

        if (tempoas/NUM_TITLE<1) {
          tempoas=tempoas-((tempoas/NUM_TITLE)*NUM_TITLE);
          DrawImg_LightMap(parede[tempoas-1],cirarmpx*64-tamanhoParedes(tempoas,'x'),cirarmpy*48-tamanhoParedes(tempoas,'y'),tamanhoParedes(tempoas,'w'),tamanhoParedes(tempoas,'h'),((mapobjetos[cirarmpy+ypos][cirarmpx+xpos]-1)%8)*tamanhoParedes(tempoas,'w'),((mapobjetos[cirarmpy+ypos][cirarmpx+xpos]-1)/8)*tamanhoParedes(tempoas,'h'));
        }
        else if (tempoas/NUM_TITLE<3) {
          tempoas=tempoas-((tempoas/NUM_TITLE)*NUM_TITLE);
          DrawImg_LightMap(objetos[tempoas-1],cirarmpx*64-tamanhoObjetos(tempoas,'x'),cirarmpy*48-tamanhoObjetos(tempoas,'y'),tamanhoObjetos(tempoas,'w'),tamanhoObjetos(tempoas,'h'),((mapobjetos[cirarmpy+ypos][cirarmpx+xpos]-1)%8)*tamanhoObjetos(tempoas,'w'),((mapobjetos[cirarmpy+ypos][cirarmpx+xpos]-1)/8)*tamanhoObjetos(tempoas,'h'));
        }
        else if (tempoas/NUM_TITLE==3) {
          tempoas=tempoas-((tempoas/NUM_TITLE)*NUM_TITLE);
          DrawImg_LightMap(casa[tempoas-1], cirarmpx*64-tamanhoCasa(tempoas,'x'), cirarmpy*48-tamanhoCasa(tempoas,'y'),tamanhoCasa(tempoas,'w'),tamanhoCasa(tempoas,'h'),((mapobjetos[cirarmpy+ypos][cirarmpx+xpos]-1)%8)*tamanhoCasa(tempoas,'w'),((mapobjetos[cirarmpy+ypos][cirarmpx+xpos]-1)/8)*tamanhoCasa(tempoas,'h'));
        }
        else {
          tempoas=tempoas-((tempoas/NUM_TITLE)*NUM_TITLE);
          DrawImg_LightMap(interacao[tempoas-1], cirarmpx*64-tamanhoInteracao(tempoas,'x'), cirarmpy*48-tamanhoInteracao(tempoas,'y'),tamanhoInteracao(tempoas,'w'),tamanhoInteracao(tempoas,'h'),((mapobjetos[cirarmpy+ypos][cirarmpx+xpos]-1)%8)*tamanhoInteracao(tempoas,'w'),((mapobjetos[cirarmpy+ypos][cirarmpx+xpos]-1)/8)*tamanhoInteracao(tempoas,'h'));
        }
      }
    }
  }
}

void drawEditMapa() {
  int opcaoSelec=ComboBox_getValor(3);
  int tipoSelec=ComboBox_getValor(5);

  fillRectangle(0,0,640,576,0,0,0,255);
  criarmap();
  criarmap2();

  if (tipoSelec==2)
    DrawImg_LightMap(parede[opcaoSelec-1], editMapMouseX*64-tamanhoParedes(opcaoSelec,'x'), editMapMouseY*48-tamanhoParedes(opcaoSelec,'y'),tamanhoParedes(opcaoSelec,'w'),tamanhoParedes(opcaoSelec,'h'),((objetoSelec-1)%8)*tamanhoParedes(opcaoSelec,'w'),((objetoSelec-1)/8)*tamanhoParedes(opcaoSelec,'h'));
  else if (tipoSelec==3){
    criarmap3();
    int temp=0;
    for (temp=0;temp*16<600;temp++) { fillRectangle(0,temp*16,800,1,0,0,0,255); }
    for (temp=0;temp*16<800;temp++) { fillRectangle(temp*16,0,1,600,0,0,0,255); }
  }
  else if (tipoSelec==4)
    DrawImg_LightMap(objetos[opcaoSelec-1], editMapMouseX*64-tamanhoObjetos(opcaoSelec,'x'), editMapMouseY*48-tamanhoObjetos(opcaoSelec,'y'),tamanhoObjetos(opcaoSelec,'w'),tamanhoObjetos(opcaoSelec,'h'),((objetoSelec-1)%8)*tamanhoObjetos(opcaoSelec,'w'),((objetoSelec-1)/8)*tamanhoObjetos(opcaoSelec,'h'));
  else if (tipoSelec==5)
    DrawImg_LightMap(casa[opcaoSelec-1], editMapMouseX*64-tamanhoCasa(opcaoSelec,'x'), editMapMouseY*48-tamanhoCasa(opcaoSelec,'y'),tamanhoCasa(opcaoSelec,'w'),tamanhoCasa(opcaoSelec,'h'),((objetoSelec-1)%8)*tamanhoCasa(opcaoSelec,'w'),((objetoSelec-1)/8)*tamanhoCasa(opcaoSelec,'h'));
  else if (tipoSelec==6)
    DrawImg_LightMap(interacao[opcaoSelec-1], editMapMouseX*64-tamanhoInteracao(opcaoSelec,'x'), editMapMouseY*48-tamanhoInteracao(opcaoSelec,'y'),tamanhoInteracao(opcaoSelec,'w'),tamanhoInteracao(opcaoSelec,'h'),((objetoSelec-1)%8)*tamanhoInteracao(opcaoSelec,'w'),((objetoSelec-1)/8)*tamanhoInteracao(opcaoSelec,'h'));
}

void drawSelectObj() {
 // fillRectangle(0,0,131,434,216,220,200,255);

  Textura **img=NULL;

  int opcaoSelec=ComboBox_getValor(3);
  int tipoSelec=ComboBox_getValor(5);

  int scrollX=Scroll_getPosicao(13);
  int scrollY=Scroll_getPosicao(6);

  int percorrer;
  int repeticoes;

  int tamW=0;
  int tamH=0;

  if (tipoSelec==1) {
    img=title;
    tamW=64;
    tamH=48;
  }
  else if (tipoSelec==2) {
    img=parede;
    tamW=tamanhoParedes(opcaoSelec,'w');
    tamH=tamanhoParedes(opcaoSelec,'h');
  }
  else if (tipoSelec==4) {
    img=objetos;
    tamW=tamanhoObjetos(opcaoSelec,'w');
    tamH=tamanhoObjetos(opcaoSelec,'h');
  }
  else if (tipoSelec==5) {
    img=casa;
    tamW=tamanhoCasa(opcaoSelec,'w');
    tamH=tamanhoCasa(opcaoSelec,'h');
  }
  else if (tipoSelec==6) {
    img=interacao;
    tamW=tamanhoInteracao(opcaoSelec,'w');
    tamH=tamanhoInteracao(opcaoSelec,'h');
  }
  else return;

  repeticoes=GUI_getTamanho(12,'h')/tamH+1;

  for (percorrer=0; percorrer<repeticoes ;percorrer++) {
    DrawIMG(img[opcaoSelec-1], 0, (tamH+1)*percorrer, tamW, tamH,tamW*scrollX,tamH*(percorrer+scrollY));
    DrawIMG(img[opcaoSelec-1], tamW+2, (tamH+1)*percorrer, tamW, tamH,tamW*(scrollX+1),tamH*(percorrer+scrollY));

    if (objetoSelec == scrollX+8*(percorrer+scrollY)+1)
      drawRectangle(0,(tamH+1)*percorrer,tamW,tamH,250,0,0,180);
    else if (objetoSelec == (scrollX+1)+8*(percorrer+scrollY)+1)
      drawRectangle(66,(tamH+1)*percorrer,tamW,tamH,250,0,0,180);
  }
}

void eventSelectObj(GUIParms *parm) {
  if (parm->acao == MOUSE_DOWN_LEFT) {
    int opcaoSelec=ComboBox_getValor(3);
    int tipoSelec=ComboBox_getValor(5);

    int scrollX=Scroll_getPosicao(13);
    int scrollY=Scroll_getPosicao(6);

    int tamW;
    int tamH;

    if (tipoSelec==1) {
      tamW=64;
      tamH=48;
    }
    else if (tipoSelec==2) {
      tamW=tamanhoParedes(opcaoSelec,'w');
      tamH=tamanhoParedes(opcaoSelec,'h');
    }
    else if (tipoSelec==4) {
      tamW=tamanhoObjetos(opcaoSelec,'w');
      tamH=tamanhoObjetos(opcaoSelec,'h');
    }
    else if (tipoSelec==5) {
      tamW=tamanhoCasa(opcaoSelec,'w');
      tamH=tamanhoCasa(opcaoSelec,'h');
    }
    else if (tipoSelec==6) {
      tamW=tamanhoInteracao(opcaoSelec,'w');
      tamH=tamanhoInteracao(opcaoSelec,'h');
    }
    else return;

    objetoSelec=(parm->x/(tamW+2)+scrollX)+8*(parm->y/(tamH-1)+scrollY)+1;
  }
}

void eventEditMapa(GUIParms *parm) {
  static char clickou=0;

  if (parm->acao == TECLA_DOWN) {
    if (parm->sym == SDLK_UP) { if (ypos>0) { ypos--; } }
    if (parm->sym == SDLK_DOWN) { if (ypos+14<=map_sizey) { ypos++; } }
    if (parm->sym == SDLK_RIGHT) { if (xpos+11<=map_sizex) { xpos++; } }
    if (parm->sym == SDLK_LEFT) { if (xpos>0) { xpos--; } }
  }
  else if (parm->acao == MOUSE_MOVE) {
    editMapMouseX=parm->x/64;
    editMapMouseY=parm->y/48;
  }

  if ((parm->acao == MOUSE_DOWN_LEFT) || ((clickou) && (parm->acao == MOUSE_MOVE) && (SDL_GetMouseState(NULL, NULL)&SDL_BUTTON(1)))){
    if (parm->acao == MOUSE_DOWN_LEFT)
      clickou=1;

    int opcaoSelec=ComboBox_getValor(3);
    int tipoSelec=ComboBox_getValor(5);
    int camandaSelec=RadioButton_getSelect(1);

    int posAddX=editMapMouseX+xpos;
    int posAddY=editMapMouseY+ypos;

    if ((posAddX < 0) || (posAddY < 0) || (posAddX >= map_sizex) || (posAddY >= map_sizey)) return;

    if (tipoSelec==1) {
      if (camandaSelec==7) {
        map[posAddY][posAddX]=objetoSelec;
        tipochao[posAddY][posAddX]=opcaoSelec;
      }
      else {
        map2[posAddY][posAddX]=objetoSelec;
        tipochao2[posAddY][posAddX]=opcaoSelec;
      }
    }
    else if (tipoSelec==3)
      mapcaminhar[parm->y/16 + ypos*3][parm->x/16 + xpos*4]=opcaoSelec;
    else if ((tipoSelec >= 2) && (tipoSelec < 7)) {
      if (tipoSelec == 2)
        mapobjetos[posAddY][posAddX]=objetoSelec;
      else if (tipoSelec >= 4)
        mapobjetos[posAddY][posAddX]=objetoSelec;

      mapobjetostipo[posAddY][posAddX]=opcaoSelec + ((tipoSelec - 2)*NUM_TITLE);
    }
    else if (tipoSelec == 7) {
      if (lightmap.ativo)
        EditLighModif(parm->x/16+xpos*4, parm->y/16+ypos*3);
    }

  }
  else if (parm->acao == MOUSE_UP_LEFT)
    clickou=0;
  else if ((parm->acao == MOUSE_DOWN_RIGHT) || ((clickou) && (parm->acao == MOUSE_MOVE) && (SDL_GetMouseState(NULL, NULL)&SDL_BUTTON(3)))){
    if (parm->acao == MOUSE_DOWN_RIGHT)
      clickou=1;

    int tipoSelec=ComboBox_getValor(5);
    int camandaSelec=RadioButton_getSelect(1);

    int posAddX=editMapMouseX+xpos;
    int posAddY=editMapMouseY+ypos;

    if ((posAddX < 0) || (posAddY < 0) || (posAddX >= map_sizex) || (posAddY >= map_sizey)) return;

    if (tipoSelec==1) {
      if (camandaSelec==7) {
        map[posAddY][posAddX]=0;
        tipochao[posAddY][posAddX]=0;
      }
      else {
        map2[posAddY][posAddX]=0;
        tipochao2[posAddY][posAddX]=0;
      }
    }
    else if (tipoSelec==3)
      mapcaminhar[parm->y/16+ypos*3][parm->x/16+xpos*4]=0;
    else if (tipoSelec>=2) {
      if (tipoSelec==2) mapobjetos[posAddY][posAddX]=0;
      else if (tipoSelec>=4) mapobjetos[posAddY][posAddX]=0;

      mapobjetostipo[posAddY][posAddX]=0;
    }
  }
  else if (parm->acao == MOUSE_UP_RIGHT)
    clickou=0;
}

void cancelPortal(GUIParms *parm) {
  if (parm->acao == MOUSE_UP_LEFT) {
    GUI_AbrirPai();
      int opcao=ComboBox_getValor(3);
    GUI_FecharPai();

    GUI_setLabel(5,"%d",qualmapa[opcao-3][0]);
    GUI_setLabel(6,"%d",qualmapa[opcao-3][1]);
    GUI_setLabel(7,"%d",qualmapa[opcao-3][2]);
  }
}

void salvarPortal(GUIParms *parm) {
  if (parm->acao == MOUSE_UP_LEFT) {
    GUI_AbrirPai();
      int opcao=ComboBox_getValor(3);
    GUI_FecharPai();

    qualmapa[opcao-3][0]=atoi(GUI_getLabel(5));
    qualmapa[opcao-3][1]=atoi(GUI_getLabel(6));
    qualmapa[opcao-3][2]=atoi(GUI_getLabel(7));
  }
}

void buttonSalvarMapa(GUIParms *parm) {
  if (parm->acao == MOUSE_UP_LEFT) {
    salvarmap(GUI_getLabel(2));

    Janela_fechar();
  }
}

void salvarMapa(GUIParms *parm) {
  if (parm->acao == MOUSE_UP_LEFT) {
    ListaDupla *tmp_GUI;
    GUI_filhos('i',&tmp_GUI);
      Texto('n', "Arquivo:", 1, 15, 23,1, GUI_ATIVO, 0, NULL);
      EditBox('n', nomeMapaOpen, 2, 80, 20, 200,GUI_ATIVO, 0, NULL);

      Botao('n',"Salvar",3,100,60,100,GUI_ATIVO,buttonSalvarMapa);

      GUI_setecionar(2);
    GUI_filhos('f',&tmp_GUI);

    Janela('n', "Salvar mapa",tmp_GUI, numJanela++, 0, 0, 300, 110, GUI_ATIVO, JANELA_CENTRALIZADA ,NULL);
  }
}

void buttonCarregarMapa(GUIParms *parm) {
  if (parm->acao == MOUSE_UP_LEFT) {
    strncpy(nomeMapaOpen, GUI_getLabel(2), 250);
    lermapafile(nomeMapaOpen);

    Janela_fechar();
  }
}

void carregarMapa(GUIParms *parm) {
  if (parm->acao == MOUSE_UP_LEFT) {
    ListaDupla *tmp_GUI;
    GUI_filhos('i',&tmp_GUI);
      Texto('n', "Arquivo:", 1, 15, 23, 1, GUI_ATIVO, 0, NULL);
      EditBox('n', nomeMapaOpen, 2, 80, 20, 200,GUI_ATIVO, 0, NULL);

      Botao('n',"Carregar",3,100,60,100,GUI_ATIVO,buttonCarregarMapa);

      GUI_setecionar(2);
    GUI_filhos('f',&tmp_GUI);

    Janela('n', "Carregar mapa",tmp_GUI, numJanela++, 0, 0, 300, 110, GUI_ATIVO, JANELA_CENTRALIZADA ,NULL);
  }
}

void buttonRedimencionarMapa(GUIParms *parm) {
  if (parm->acao == MOUSE_UP_LEFT) {
    char *charAltura=GUI_getLabel(2);
    char *charLargura=GUI_getLabel(4);

    if ((charAltura[0] == '\0') || (charLargura[0] == '\0')) return;

    int altura=atoi(charAltura);
    int largura=atoi(charLargura);

    alocarMemMap(largura,altura);

    Janela_fechar();
  }
}


void redimencionarMapa(GUIParms *parm) {
  if (parm->acao == MOUSE_UP_LEFT) {
    ListaDupla *tmp_GUI;
    GUI_filhos('i',&tmp_GUI);
      Texto('n', "Altura:", 1, 15, 23, 1, GUI_ATIVO, 0, NULL);
      EditBox('n', "", 2, 80, 20, 50,GUI_ATIVO, EDITBOX_NUMERICO, NULL);

      Texto('n', "Largura:", 3, 15, 48, 1, GUI_ATIVO, 0, NULL);
      EditBox('n', "", 4, 80, 45, 50,GUI_ATIVO, EDITBOX_NUMERICO, NULL);

      Botao('n',"Redimensionar",5,25,80,100,GUI_ATIVO,buttonRedimencionarMapa);

      GUI_setLabel(2,"%d",map_sizey);
      GUI_setLabel(4,"%d",map_sizex);

      GUI_setecionar(2);
    GUI_filhos('f',&tmp_GUI);

    Janela('n', "Redimensionar mapa",tmp_GUI, numJanela++, 0, 0, 150, 120, GUI_ATIVO, JANELA_CENTRALIZADA, NULL);
  }
}

void selectOpcao(GUIParms *parm) {
  if (parm->acao == MOUSE_DOWN_LEFT) {
    int tipo=ComboBox_getValor(5);
    int opcao=ComboBox_getValor(3);

    int estadoCam=GUI_INATIVO;

    if ((tipo == 3) && (opcao>=3) && (opcao<=7)) {
      estadoCam=GUI_ATIVO;
      ListaDupla **ListaTmp=GUI_AbrirFilho(14);

      GUI_setLabel(5,"%d",qualmapa[opcao-3][0]);
      GUI_setLabel(6,"%d",qualmapa[opcao-3][1]);
      GUI_setLabel(7,"%d",qualmapa[opcao-3][2]);

      GUI_FecharFilho(ListaTmp);
    }

    GUI_setAtivo(14,estadoCam);
  }
}

void selectTipo(GUIParms *parm) {
  static int oldTipo=-1;

  if (parm->acao == MOUSE_DOWN_LEFT) {
    int tipo=ComboBox_getValor(5);

    if ((tipo == oldTipo) || (tipo == 0)) return;

    ComboBox_Limpar(3);
    objetoSelec=1;

    GUI_setAtivo(6,GUI_ATIVO);
    GUI_setAtivo(13,GUI_ATIVO);

    GUI_setAtivo(14,GUI_INATIVO);
    GUI_setAtivo(15,GUI_INATIVO);

    if (oldTipo == 1) {
      GUI_setAtivo(7,GUI_INATIVO);
      GUI_setAtivo(8,GUI_INATIVO);

      GUI_setPosicao(13,661,492);
      GUI_setTamanho(12,131,434);
      Scroll_setTamanho(6,452);
    }

    if (oldTipo == 7) {
      GUI_setAtivo(2,GUI_ATIVO);
      GUI_setAtivo(3,GUI_ATIVO);

      GUI_setAtivo(16,GUI_INATIVO);
    }

    switch (tipo) {
      case 1:
        ComboBox_Adicionar(3,0,0,0,1,"Grama 1");
        ComboBox_Adicionar(3,0,0,0,1,"Grama 2");
        ComboBox_Adicionar(3,0,0,0,1,"Lava seca");
        ComboBox_Adicionar(3,0,0,0,1,"Água");
        ComboBox_Adicionar(3,0,0,0,1,"Lava");
        ComboBox_Adicionar(3,0,0,0,1,"Neve");
        ComboBox_Adicionar(3,0,0,0,1,"Aleatórios");
        ComboBox_Adicionar(3,0,0,0,1,"Normais");
        ComboBox_Adicionar(3,0,0,0,1,"Grama 3");

        GUI_setAtivo(7,GUI_ATIVO);
        GUI_setAtivo(8,GUI_ATIVO);

        GUI_setPosicao(13,661,462);
        GUI_setTamanho(12,131,405);
        Scroll_setTamanho(6,420);

        break;
      case 2:
        ComboBox_Adicionar(3,0,0,0,1,"Medieval");
        ComboBox_Adicionar(3,0,0,0,1,"Lava");

        break;
      case 3:
        ComboBox_Adicionar(3,100,100,100,1,"Parede");
        ComboBox_Adicionar(3,10,110,250,1,"Água");
        ComboBox_Adicionar(3,250,250,50,1,"Portal 1");
        ComboBox_Adicionar(3,250,250,50,1,"Portal 2");
        ComboBox_Adicionar(3,250,250,50,1,"Portal 3");
        ComboBox_Adicionar(3,250,250,50,1,"Portal 4");
        ComboBox_Adicionar(3,250,250,50,1,"Portal 5");
        ComboBox_Adicionar(3,133,77,9,1,"Parede baixa");
        ComboBox_Adicionar(3,50,250,50,1,"Interação");

        GUI_setAtivo(6,GUI_INATIVO);
        GUI_setAtivo(13,GUI_INATIVO);

        break;
      case 4:
        ComboBox_Adicionar(3,0,0,0,1,"128x128");
        ComboBox_Adicionar(3,0,0,0,1,"128x128 2");
        ComboBox_Adicionar(3,0,0,0,1,"64x96");
        ComboBox_Adicionar(3,0,0,0,1,"96x128");
        ComboBox_Adicionar(3,0,0,0,1,"96x96");
        ComboBox_Adicionar(3,0,0,0,1,"64x64");
        ComboBox_Adicionar(3,0,0,0,1,"128x96");

        break;

      case 5:
        ComboBox_Adicionar(3,0,0,0,1,"Mina");
        ComboBox_Adicionar(3,0,0,0,1,"Ferreiro");

        break;

      case 6:
        ComboBox_Adicionar(3,0,0,0,1,"Pêssego");
        ComboBox_Adicionar(3,0,0,0,1,"Uva");

        break;

      case 7:
        GUI_setAtivo(2,GUI_INATIVO);
        GUI_setAtivo(3,GUI_INATIVO);
        GUI_setAtivo(6,GUI_INATIVO);
        GUI_setAtivo(13,GUI_INATIVO);

        GUI_setAtivo(15,GUI_ATIVO);

        if (CheckBox_isSelect(15))
          GUI_setAtivo(16,GUI_ATIVO);

        break;
    }

    ComboBox_Seleciona(3,1);
    oldTipo=tipo;
  }
}

void InitEditMap() {
  unsigned char cor[3]={255,255,255};

  alocarMemMap(TAMANHO_INICIALX, TAMANHO_INICIALY);
  LightMap_carregar(mapWidth,mapHeight,cor,NULL);

  lightmap.ativo=0;
}

void EditLight_setColor(GUIParms *parm) {
  static char clickou=0;

  if ((parm->acao == MOUSE_DOWN_LEFT) || ((clickou) && (parm->acao == MOUSE_MOVE) && (SDL_GetMouseState(NULL, NULL)&SDL_BUTTON(1)))) {
    if (parm->acao == MOUSE_DOWN_LEFT)
      clickou=1;

    cursorT=2;

    unsigned char r,g,b;
    int posLerX=mousemovidox-parm->x;
    int posLerY=mousemovidoy-parm->y;

    glPixelStorei(GL_PACK_ALIGNMENT, 1);

    unsigned char *pixels = malloc(3 * parm->dados->w * parm->dados->h);
    glReadPixels(posLerX, screen->h-parm->dados->h-posLerY, parm->dados->w, parm->dados->h, GL_RGB, GL_UNSIGNED_BYTE, pixels);

    r=pixels[(parm->dados->h-parm->y) * parm->dados->w * 3 + parm->x * 3 + 0];
    g=pixels[(parm->dados->h-parm->y) * parm->dados->w * 3 + parm->x * 3 + 1];
    b=pixels[(parm->dados->h-parm->y) * parm->dados->w * 3 + parm->x * 3 + 2];

    GUI_setLabel(5,"%d",r);
    GUI_setLabel(7,"%d",g);
    GUI_setLabel(9,"%d",b);

    GUI_MudarCor(10,r,g,b);

    free(pixels);
  }
  else if (parm->acao == MOUSE_UP_LEFT) {
    clickou=0;
    cursorT=1;
  }
}

void EditLighAtualizaCor(GUIParms *parm) {
  if (parm->acao == TECLA_UP) {
    char *ver=GUI_getLabel(5);
    if (ver[0] == '\0') return;

    ver=GUI_getLabel(7);
    if (ver[0] == '\0') return;

    ver=GUI_getLabel(9);
    if (ver[0] == '\0') return;

    unsigned char r=atoi(GUI_getLabel(5));
    unsigned char g=atoi(GUI_getLabel(7));
    unsigned char b=atoi(GUI_getLabel(9));

    GUI_MudarCor(10,r,g,b);
  }
}

void EditLighAtualizaAmbCor(GUIParms *parm) {
  int r=Scroll_getPosicao(2);
  int g=Scroll_getPosicao(4);
  int b=Scroll_getPosicao(6);

  GUI_MudarCor(7,r,g,b);

  GUI_setLabel(1,"R (%d)",r);
  GUI_setLabel(3,"G (%d)",g);
  GUI_setLabel(5,"B (%d)",b);
}

void buttonEditLighNovaLight(GUIParms *parm) {
  if (parm->acao == MOUSE_UP_LEFT) {
    unsigned char cor[3];

    ListaDupla **listTmp=GUI_AbrirFilho(1);
      cor[0]=Scroll_getPosicao(2);
      cor[1]=Scroll_getPosicao(4);
      cor[2]=Scroll_getPosicao(6);
    GUI_FecharFilho(listTmp);

    LightMap_carregar(lightmap.width, lightmap.height, cor, NULL);

    Janela_fechar();
  }
}

void EditLighNovaLight(GUIParms *parm) {
  if (parm->acao == MOUSE_UP_LEFT) {
    GUI_AbrirPai();
    ListaDupla *tmp_GUI;
    GUI_filhos('i',&tmp_GUI);
      GUI_filhos('i',&tmp_GUI);
        Texto('n', "R (255):", 1, 5, 10, 1, GUI_ATIVO, 0, NULL);
        ScrollBar('n', 2, 65, 10, 150, 256, GUI_ATIVO, SCROLLBAR_HORIZONTAL, EditLighAtualizaAmbCor);

        Texto('n', "G (255):", 3, 5, 30, 1, GUI_ATIVO, 0, NULL);
        ScrollBar('n', 4, 65, 30, 150, 256, GUI_ATIVO, SCROLLBAR_HORIZONTAL, EditLighAtualizaAmbCor);

        Texto('n', "B (255):", 5, 5, 50, 1, GUI_ATIVO, 0, NULL);
        ScrollBar('n', 6, 65, 50, 150, 256, GUI_ATIVO, SCROLLBAR_HORIZONTAL, EditLighAtualizaAmbCor);

        Quadrado('n', 7, 220, 10, 25, 55, GUI_ATIVO, QUADRADO_PREENCHIDO, NULL);

        Scroll_setPosicao(2,255);
        Scroll_setPosicao(4,255);
        Scroll_setPosicao(6,255);

        GUI_MudarCor(7,255,255,255);
      GUI_filhos('f',&tmp_GUI);

      GroupBox('n',"Cor ambiente:", tmp_GUI, 1, 5, 10,255,80, GUI_ATIVO, NULL);

      Botao('n',"Criar",2,82,100,100,GUI_ATIVO,buttonEditLighNovaLight);

      GUI_MudarCor(1,193,232,0);
    GUI_filhos('f',&tmp_GUI);

    Janela('n', "Novo LightMap",tmp_GUI, numJanela++, 0, 0, 265, 150, GUI_ATIVO, JANELA_CENTRALIZADA, NULL);

    GUI_FecharPai();
  }
}

void EditLighAtualizaLight() {
  int ativo=(CheckBox_isSelect(15))?GUI_ATIVO:GUI_INATIVO;

  GUI_setAtivo(16,ativo);
  lightmap.ativo=ativo;
}

void EditLighAtivo(GUIParms *parm) {
  if (parm->acao == MOUSE_UP_LEFT) {
    EditLighAtualizaLight();
  }
}

void EditLighFerramentas(GUIParms *parm) {
  if (parm->acao == MOUSE_DOWN_LEFT)
    lightFerramSelect=parm->x/25+(parm->y/25)*4;
}

void drawEditLighFerramentas() {
  DrawIMG(ferramentas,0,0,99,49,0,0);

  if (lightFerramSelect != -1)
    fillRectangle((lightFerramSelect%4)*25,(lightFerramSelect/4)*25,24,24,250,100,100,150);
}

SDL_Surface *lightMap_Surface() {
  int x, y;
  SDL_Surface *temp=NULL;
  Uint32 color;

  temp=SDL_CreateRGBSurface(SDL_SWSURFACE, mapWidth+2, mapHeight+2, 24, 0, 0, 0, 0);

  if (temp == NULL)
    return NULL;

  for (y=0; y<mapHeight+2 ;y++) {
    for (x=0; x<mapWidth+2 ;x++) {
      color=LightMap_getMapColor(temp->format, x, y);
      putpixel(temp, x, y, color);
    }
  }

  return temp;
}

void buttonImportarLightMap(GUIParms *parm) {
  if (parm->acao == MOUSE_UP_LEFT) {
    int x, y;
    Uint8 r,g,b;
    SDL_Surface *surface=NULL;
    unsigned char *correctPixels=NULL;
    unsigned char cor[3]= { 255, 255, 255 };
    char nome[256];

    strcpy(nome, GUI_getLabel(2));
    if (nome[0] == '\0') return;

    surface = IMG_Load(nome);
    if (surface == NULL) return;

    correctPixels=(unsigned char *) calloc(surface->w * surface->h * 3, sizeof(unsigned char));

    for (y=0; y<surface->h ;y++) {
      for (x=0; x<surface->w ;x++) {
        SDL_GetRGB(getpixel(surface, x, y), surface->format, &r, &g, &b);

        correctPixels[y * surface->w * 3 + x * 3 + 0]=r;
        correctPixels[y * surface->w * 3 + x * 3 + 1]=g;
        correctPixels[y * surface->w * 3 + x * 3 + 2]=b;
      }
    }

    LightMap_carregar(surface->w, surface->h, cor, correctPixels);

    SDL_FreeSurface(surface);
    free(correctPixels);

    Janela_fechar();
  }
}

void importarLightMap(GUIParms *parm) {
  if (parm->acao == MOUSE_UP_LEFT) {
    GUI_AbrirPai();

      ListaDupla *tmp_GUI;
      GUI_filhos('i',&tmp_GUI);
        Texto('n', "Arquivo:", 1, 15, 23, 1, GUI_ATIVO, 0, NULL);
        EditBox('n', "lightmap.bmp", 2, 80, 20, 200,GUI_ATIVO, 0, NULL);

        Botao('n',"Importar",3,100,60,100,GUI_ATIVO,buttonImportarLightMap);

        GUI_setecionar(2);
      GUI_filhos('f',&tmp_GUI);

      Janela('n', "Importar light",tmp_GUI, numJanela++, 0, 0, 300, 110, GUI_ATIVO, JANELA_CENTRALIZADA ,NULL);

    GUI_FecharPai();
  }
}

void buttonExportarLightMap(GUIParms *parm) {
  if (parm->acao == MOUSE_UP_LEFT) {
    char nome[256];
    SDL_Surface *temp=NULL;

    strcpy(nome, GUI_getLabel(2));
    if (nome[0] == '\0') return;

    temp=lightMap_Surface();

    SDL_SaveBMP(temp, nome);
    SDL_FreeSurface(temp);

    Janela_fechar();
  }
}

void exportarLightMap(GUIParms *parm) {
  if (parm->acao == MOUSE_UP_LEFT) {
    GUI_AbrirPai();

      ListaDupla *tmp_GUI;
      GUI_filhos('i',&tmp_GUI);
        Texto('n', "Arquivo:", 1, 15, 23, 1, GUI_ATIVO, 0, NULL);
        EditBox('n', "lightmap.bmp", 2, 80, 20, 200,GUI_ATIVO, 0, NULL);

        Botao('n',"Exportar",3,100,60,100,GUI_ATIVO,buttonExportarLightMap);

        GUI_setecionar(2);
      GUI_filhos('f',&tmp_GUI);

      Janela('n', "Exportar light",tmp_GUI, numJanela++, 0, 0, 300, 110, GUI_ATIVO, JANELA_CENTRALIZADA ,NULL);

    GUI_FecharPai();
  }
}

void EditLighModif(int x, int y) {
  x++;
  y++;

  if ((x >= lightmap.width) || (y >= lightmap.height))
    return;

  ListaDupla **tempList=GUI_AbrirFilho(16);
    char *ver=GUI_getLabel(5);
    if (ver[0] == '\0') goto finalizar;

    ver=GUI_getLabel(7);
    if (ver[0] == '\0') goto finalizar;

    ver=GUI_getLabel(9);
    if (ver[0] == '\0') goto finalizar;

    unsigned char r=atoi(GUI_getLabel(5));
    unsigned char g=atoi(GUI_getLabel(7));
    unsigned char b=atoi(GUI_getLabel(9));

    if (lightFerramSelect == 0) {
      mapLightMap[x*3 + y * lightmap.width*3 + 0]=r;
      mapLightMap[x*3 + y * lightmap.width*3 + 1]=g;
      mapLightMap[x*3 + y * lightmap.width*3 + 2]=b;
    }

    LightMap_atualizar();

finalizar:
  GUI_FecharFilho(tempList);
}
