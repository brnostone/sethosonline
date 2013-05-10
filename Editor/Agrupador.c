#include <stdio.h>
#include <GL/gl.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>

#include "Header/fonte.h"
#include "Header/opengl.h"
#include "Header/estruturas.h"
#include "Header/GUI.h"
#include "Header/util.h"
#include "Header/global.h"
#include "Header/sdl_png.h"
#include "Header/Agrupador.h"

struct AgrupAnim {
  int offsetX;
  int offsetY;

  int width;
  int height;

  int numImg;
  int anim;

  int numLado;
  int lado;

  char mostrarLinha;

  SDL_Surface *img;

} agrupAnim;


char nomeAgrupOpen[250]="agrupador/";
Textura *agrupada=NULL;
int posAgrupX=0,posAgrupY=0;
int velocMoveX=0,velocMoveY=0;

int AgripAnimLadoReplace(int lado) {
  int novo=lado;

  if (lado == 2) novo=7;
  else if (lado == 4) novo=8;
  else if (lado == 5) novo=4;
  else if (lado == 6) novo=5;
  else if (lado == 7) novo=2;
  else if (lado == 8) novo=6;

  return novo;
}

void drawAgrupImg() {
  posAgrupX+=velocMoveX;
  posAgrupY+=velocMoveY;

  if (posAgrupX < 0) posAgrupX=0;
  if (posAgrupY < 0) posAgrupY=0;

  if (CheckBox_isSelect(27))
    drawRepetir(fundoAlpha,0,0,600,400,0,0,fundoAlpha->w,fundoAlpha->h);

  if (agrupada != NULL)
    DrawIMG(agrupada,-posAgrupX,1-posAgrupY,agrupada->w,agrupada->h,0,0);
}

void drawAgrupAnim() {
  static int frames=0;

  if (CheckBox_isSelect(27))
    drawRepetir(fundoAlpha,0,0,200,150,0,0,fundoAlpha->w,fundoAlpha->h);

  if (agrupada != NULL) {
    int lado=AgripAnimLadoReplace(agrupAnim.lado);

    int posXanim=agrupAnim.anim*agrupAnim.width + agrupAnim.mostrarLinha + agrupAnim.mostrarLinha*agrupAnim.anim;
    int posYanim=(lado-1)*agrupAnim.height + agrupAnim.mostrarLinha + agrupAnim.mostrarLinha*(lado-1);

    DrawIMG(agrupada,0,0,agrupAnim.width,agrupAnim.height,posXanim,posYanim);

    if ( SDL_GetTicks()-frames >= 50 ) {
      //deixa a animação na velocidade do jogo
      agrupAnim.anim++;

      if (agrupAnim.anim>=agrupAnim.numImg) {
        agrupAnim.anim=0;

        agrupAnim.lado++;

        if (agrupAnim.lado > agrupAnim.numLado)
          agrupAnim.lado=1;
      }

      frames=SDL_GetTicks();
    }
  }
}

Uint32 AgrupRetornaColor(int x, int y) {
  SDL_Surface *surface=agrupAnim.img;

  if ((x >= surface->w) || (y >= surface->h))
    return 0;

  return *((Uint32 *)surface->pixels + y * surface->pitch/4 + x);
}

void AgrupSelectColor(int x, int y) {
  ListaDupla *raiz=prim_GUI;
  ListaDupla *tmp;
  Uint8 r,g,b;

  if (agrupAnim.img == NULL) return;

  SDL_GetRGB(AgrupRetornaColor(x-posAgrupX,1+y-posAgrupY),agrupAnim.img->format,&r,&g,&b);

  GUI_pilha('a');
    forListDupla (struct componentes *, componenteTmp, raiz) {
      componenteAtual=componenteTmp;

      if (componenteAtual->tipo == JANELA) {
        tmp=(ListaDupla *) componenteAtual->aux;

        GUI_pilha('a');
          prim_GUI=tmp;
          if (GUI_BuscaElem(8,OCULTO)) {
            if ((componenteAtual->opt == 1) || (componenteAtual->opt == 2)) {
              GUI_setLabel(2,"%d",r);
              GUI_setLabel(4,"%d",g);
              GUI_setLabel(6,"%d",b);

              GUI_MudarCor(9,r,g,b);
            }
          }
        GUI_pilha('r');
      }
    }
  GUI_pilha('r');
}

void eventAgrupImg(GUIParms *parm) {
  if (parm->acao == TECLA_DOWN) {
    if (parm->sym == SDLK_UP) { velocMoveY=-2; }
    if (parm->sym == SDLK_DOWN) { velocMoveY=2; }
    if (parm->sym == SDLK_RIGHT) { velocMoveX=2; }
    if (parm->sym == SDLK_LEFT) { velocMoveX=-2; }
  }
  if (parm->acao == TECLA_UP) {
    if ((parm->sym == SDLK_UP) || (parm->sym == SDLK_DOWN)) { velocMoveY=0; }
    if ((parm->sym == SDLK_RIGHT) || (parm->sym == SDLK_LEFT)) { velocMoveX=0; }
  }

  else if (parm->acao == MOUSE_DOWN_LEFT) {
    AgrupSelectColor(parm->x, parm->y);
    GUI_setecionar(1);
  }
}

void AgrupNomeLado(int lado, char *nLado) {
  if (lado == 1) strcpy(nLado,"e");
  else if (lado == 2) strcpy(nLado,"n");
  else if (lado == 3) strcpy(nLado,"s");
  else if (lado == 4) strcpy(nLado,"w");
  else if (lado == 5) strcpy(nLado,"nw");
  else if (lado == 6) strcpy(nLado,"ne");
  else if (lado == 7) strcpy(nLado,"se");
  else if (lado == 8) strcpy(nLado,"sw");
}

static void AgrupCaminhoImg(char *arquivo, char *nome, char tipo, int masc, int lado, int quant) {
  char nLado[3];
  nLado[0]='\0';

  if (tipo == 'p')
    AgrupNomeLado(lado,nLado);

  if (masc)
    sprintf(arquivo,"%s%s%s%04d.bmp",nomeAgrupOpen,nome,nLado,quant);
  else
    sprintf(arquivo,"%s%s%s%d.bmp",nomeAgrupOpen,nome,nLado,quant);
}

static int AgrupNumImg(char *nome, char tipo, int masc) {
  int quant=0;
  char arquivo[256];
  FILE *fp;

  while (1) {
    AgrupCaminhoImg(arquivo,nome,tipo,masc,1,quant);

    fp=fopen(arquivo,"r");

    if (!fp) break;

    fclose(fp);
    quant++;
  }

  return quant;
}

void AgrupAnalizar(GUIParms *parm) {
  if (parm->acao == MOUSE_UP_LEFT) {
    char arquivo[256];
    char *nome=GUI_getLabel(5);
    char mascara=CheckBox_isSelect(6);
    char tipo=(RadioButton_getSelect(1)==7)?'o':'p';
    int numImg;

    if (nome[0] == '\0') return;

    numImg=AgrupNumImg(nome,tipo,mascara);

    if (!numImg) return;

    AgrupCaminhoImg(arquivo,nome,tipo,mascara,1,0);

    SDL_Surface *surface = IMG_Load(arquivo);
    if (!surface) return;

//Offset
    GUI_setLabel(11,"0");
    GUI_setLabel(13,"0");

//Tamanho
    GUI_setLabel(15,"%d",surface->w);
    GUI_setLabel(17,"%d",surface->h);

//Numero de imagens
    GUI_setLabel(19,"%d",numImg);

    SDL_FreeSurface(surface);
  }
}

void AgrupReplaceColor(SDL_Surface *surface, Uint32 ante, Uint32 nova) {
  int percorreX,percorreY;
  Uint32 *bufp;

  for (percorreY=0; percorreY < surface->h ; percorreY++) {
    for (percorreX = 0; percorreX < surface->w; percorreX++) {
      bufp = (Uint32 *)surface->pixels + percorreY*surface->pitch/4 + percorreX;
      if (*bufp == ante)
        *bufp = nova;
		}
  }
}

void AgrupMudarCorJn(Uint32 cor) {
    if (agrupada == NULL) return;

    char *ver=GUI_getLabel(2);
    if (ver[0] == '\0') return;

    ver=GUI_getLabel(4);
    if (ver[0] == '\0') return;

    ver=GUI_getLabel(6);
    if (ver[0] == '\0') return;

    unsigned char r=atoi(GUI_getLabel(2));
    unsigned char g=atoi(GUI_getLabel(4));
    unsigned char b=atoi(GUI_getLabel(6));

    SDL_Surface *surface=agrupAnim.img;

		AgrupReplaceColor(surface,SDL_MapRGB(surface->format,r,g,b), cor);

    deleteTextura(&agrupada);
    agrupada=carregar_memoria(surface->pixels,surface->w,surface->h,1);

    cursorT=1;
    Janela_fechar();
}

void buttonAgrupRemover(GUIParms *parm) {
  if (parm->acao == MOUSE_UP_LEFT) {
    AgrupMudarCorJn(0x00000000);
  }
}

void buttonAgrupCorSombra(GUIParms *parm) {
  if (parm->acao == MOUSE_UP_LEFT) {
    AgrupMudarCorJn(SDL_MapRGBA(agrupAnim.img->format,0,0,0,128));
  }
}

void AgrupAtualizaCor(GUIParms *parm) {
  if (parm->acao == TECLA_UP) {
    char *ver=GUI_getLabel(2);
    if (ver[0] == '\0') return;

    ver=GUI_getLabel(4);
    if (ver[0] == '\0') return;

    ver=GUI_getLabel(6);
    if (ver[0] == '\0') return;

    unsigned char r=atoi(GUI_getLabel(2));
    unsigned char g=atoi(GUI_getLabel(4));
    unsigned char b=atoi(GUI_getLabel(6));

    GUI_MudarCor(9,r,g,b);
  }
}

void AgrupRemoveFundo(GUIParms *parm) {
  if (parm->acao == MOUSE_UP_LEFT) {
    ListaDupla *tmp_GUI;
    GUI_filhos('i',&tmp_GUI);
      Oculto('n',8,1,0,0,NULL);

      Texto('n', "R:", 1, 15, 18, 1, GUI_ATIVO, 0, NULL);
      EditBox('n', "0", 2, 30, 15, 50,GUI_ATIVO, EDITBOX_NUMERICO, AgrupAtualizaCor);

      Texto('n', "G:", 3, 15, 43, 1, GUI_ATIVO, 0, NULL);
      EditBox('n', "0", 4, 30, 40, 50,GUI_ATIVO, EDITBOX_NUMERICO, AgrupAtualizaCor);

      Texto('n', "B:", 5, 15, 68, 1, GUI_ATIVO, 0, NULL);
      EditBox('n', "0", 6, 30, 65, 50,GUI_ATIVO, EDITBOX_NUMERICO, AgrupAtualizaCor);

      Botao('n',"Remover",7,25,90,80,GUI_ATIVO,buttonAgrupRemover);

      Quadrado('n', 9, 90, 15, 30, 68, GUI_ATIVO, QUADRADO_PREENCHIDO, NULL);

      GUI_setecionar(2);
    GUI_filhos('f',&tmp_GUI);

    cursorT=2;
    Janela('n', "Remover Fundo",tmp_GUI, numJanela++, 0, 0, 130, 130, GUI_ATIVO, JANELA_CENTRALIZADA, NULL);
  }
}

void AgrupCorSombra(GUIParms *parm) {
  if (parm->acao == MOUSE_UP_LEFT) {
    ListaDupla *tmp_GUI;
    GUI_filhos('i',&tmp_GUI);
      Oculto('n',8,2,0,0,NULL);

      Texto('n', "R:", 1, 15, 18, 1, GUI_ATIVO, 0, NULL);
      EditBox('n', "0", 2, 30, 15, 50,GUI_ATIVO, EDITBOX_NUMERICO, AgrupAtualizaCor);

      Texto('n', "G:", 3, 15, 43, 1, GUI_ATIVO, 0, NULL);
      EditBox('n', "0", 4, 30, 40, 50,GUI_ATIVO, EDITBOX_NUMERICO, AgrupAtualizaCor);

      Texto('n', "B:", 5, 15, 68, 1, GUI_ATIVO, 0, NULL);
      EditBox('n', "0", 6, 30, 65, 50,GUI_ATIVO, EDITBOX_NUMERICO, AgrupAtualizaCor);

      Botao('n',"Remover",7,25,90,80,GUI_ATIVO,buttonAgrupCorSombra);

      Quadrado('n', 9, 90, 15, 30, 68, GUI_ATIVO, QUADRADO_PREENCHIDO, NULL);

      GUI_setecionar(2);
    GUI_filhos('f',&tmp_GUI);

    cursorT=2;
    Janela('n', "Cor Sombra",tmp_GUI, numJanela++, 0, 0, 130, 130, GUI_ATIVO, JANELA_CENTRALIZADA, NULL);
  }
}

void buttonMudarPasta(GUIParms *parm) {
  if (parm->acao == MOUSE_UP_LEFT) {
    strncpy(nomeAgrupOpen,GUI_getLabel(2),250);

    Janela_fechar();
  }
}

void AgrupConfigPasta(GUIParms *parm) {
  if (parm->acao == MOUSE_UP_LEFT) {
    ListaDupla *tmp_GUI;
    GUI_filhos('i',&tmp_GUI);
      Texto('n', "Pasta:", 1, 15, 23, 1, GUI_ATIVO, 0, NULL);
      EditBox('n', nomeAgrupOpen, 2, 80, 20, 200,GUI_ATIVO, 0, NULL);

      Botao('n',"Mudar",3,100,60,100,GUI_ATIVO,buttonMudarPasta);

      GUI_setecionar(2);
    GUI_filhos('f',&tmp_GUI);

    Janela('n', "Configurar Pasta",tmp_GUI, numJanela++, 0, 0, 300, 110, GUI_ATIVO, JANELA_CENTRALIZADA ,NULL);
  }
}

void buttonAgrupSalvar(GUIParms *parm) {
  if (parm->acao == MOUSE_UP_LEFT) {
    char arquivo[1024];
    char *nomeArquivo=GUI_getLabel(3);

    if ((nomeArquivo == NULL) || (nomeArquivo[0] == '\0')) return;

    sprintf(arquivo,"%s%s",nomeAgrupOpen,nomeArquivo);
    IMG_SavePNG(arquivo,agrupAnim.img,IMG_COMPRESS_MAX);

    Janela_fechar();
  }
}

void AgrupSalvar(GUIParms *parm) {
  if (parm->acao == MOUSE_UP_LEFT) {
    if (agrupada == NULL) return;

    ListaDupla *tmp_GUI;
    GUI_filhos('i',&tmp_GUI);
      Texto('n', "", 1, 15, 5, 1, GUI_ATIVO, 0, NULL);

      Texto('n', "Arquivo:", 2, 15, 33, 1, GUI_ATIVO, 0, NULL);
      EditBox('n', "", 3, 80, 30, 200,GUI_ATIVO, 0, NULL);

      Botao('n',"Salvar",4,100,60,100,GUI_ATIVO,buttonAgrupSalvar);

      GUI_setecionar(3);
      GUI_setLabel(1,"Pasta: %s",nomeAgrupOpen);

    GUI_filhos('f',&tmp_GUI);

    Janela('n', "Salvar",tmp_GUI, numJanela++, 0, 0, 300, 110, GUI_ATIVO, JANELA_CENTRALIZADA ,NULL);
  }
}

void AgrupCarregar(GUIParms *parm) {
  if (parm->acao == MOUSE_UP_LEFT) {
    char arquivo[256];
    char *nome=GUI_getLabel(5);
    char mascara=CheckBox_isSelect(6);
    char tipo=(RadioButton_getSelect(1)==7)?'o':'p';

    int numImg=atoi(GUI_getLabel(19));
    int numLado=(tipo == 'p')? 8:1;

    int lado;
    int percorre;

    int offsetX=atoi(GUI_getLabel(11));
    int offsetY=atoi(GUI_getLabel(13));

    int width=atoi(GUI_getLabel(15));
    int height=atoi(GUI_getLabel(17));

    char mostrarLinha=CheckBox_isSelect(20);

    if (!numImg) return;

  Uint32 rmask, gmask, bmask, amask;
#if SDL_BYTEORDER == SDL_BIG_ENDIAN
  rmask = 0xff000000;
  gmask = 0x00ff0000;
  bmask = 0x0000ff00;
  amask = 0x000000ff;
#else
  rmask = 0x000000ff;
  gmask = 0x0000ff00;
  bmask = 0x00ff0000;
  amask = 0xff000000;
#endif

    SDL_Surface *surface=SDL_CreateRGBSurface(SDL_SWSURFACE | SDL_ANYFORMAT, width*numImg + numImg*mostrarLinha +mostrarLinha, height*numLado + numLado*mostrarLinha + mostrarLinha, 32, rmask, gmask, bmask, amask);
    SDL_Surface *img=NULL;

    if (mostrarLinha) {
      SDL_Rect rect;

      rect.x = 0; rect.y = 0;
      rect.w = surface->w; rect.h = surface->h;

      SDL_FillRect (surface, &rect, SDL_MapRGBA(surface->format,0,0,0,255));
    }



    for (lado=1; lado<=numLado ;lado++) {
      for (percorre=0; percorre<=numImg ;percorre++) {
        AgrupCaminhoImg(arquivo,nome,tipo,mascara,lado,percorre);

        img=IMG_Load(arquivo);
        if (!img) break;

        SDL_Rect dest,dest2;

        dest.x = width*percorre + mostrarLinha + percorre*mostrarLinha;
        dest.y = height*(lado-1) + mostrarLinha + (lado-1)*mostrarLinha;

        dest2.x = offsetX; dest2.y = offsetY;
        dest2.w = width; dest2.h = height;

        SDL_BlitSurface(img, &dest2, surface, &dest);

        SDL_FreeSurface(img);
      }
    }

    if (agrupada != NULL) {
      SDL_FreeSurface(agrupAnim.img);
      deleteTextura(&agrupada);
    }

    agrupAnim.offsetX=offsetX;
    agrupAnim.offsetY=offsetY;

    agrupAnim.width=width;
    agrupAnim.height=height;

    agrupAnim.numImg=numImg;
    agrupAnim.anim=0;

    agrupAnim.numLado=numLado;
    agrupAnim.lado=1;

    agrupAnim.mostrarLinha=mostrarLinha;

    agrupAnim.img=surface;

    agrupada=carregar_memoria(surface->pixels,surface->w,surface->h,1);

    GUI_setLabel(26,"Tamanho: %d x %d pixels.",surface->w,surface->h);
  }
}
