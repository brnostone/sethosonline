#include <math.h>

#include <GL/gl.h>
#include <SDL/SDL.h>

#include "Header/fonte.h"
#include "Header/opengl.h"
#include "Header/estruturas.h"
#include "Header/util.h"
#include "Header/global.h"
#include "Header/GUI.h"

struct componentes *guiElementoAtivo=NULL;

ListaDupla *prim_GUI=NULL;
struct componentes *componenteAtual=NULL;

ListaDupla *janelaAnt=NULL;
ListaDupla *paiAnt=NULL;

PILHA_S *pilha_GUI;

int idJanelaAtual=0;
int guiIdGeral=500;
int numComponentes;

int Componente_Acao(int id,char acao) {
  static int opcao=NAO_MUDAR_ID|ADD_CERTO;

  if (acao=='n') {
    componenteAtual=(struct componentes *) listaDupla_acao('n',&prim_GUI,id,opcao,sizeof(struct componentes));
    numComponentes++;
  }
  else if (acao=='d') {
    componenteAtual=(struct componentes *) listaDupla_acao('d',&prim_GUI,id,opcao,0);
    if (componenteAtual) numComponentes--;
  }
  else if (acao=='s') {
    componenteAtual=(struct componentes *) listaDupla_acao('s',&prim_GUI,id,opcao,numComponentes);
    return (!componenteAtual)?0:1;
  }
  else if (acao=='u') {
    componenteAtual=(struct componentes *) listaDupla_acao('u',&prim_GUI,id,opcao,numComponentes);
    return (!componenteAtual)?0:1;
  }
  else if (acao=='z') {
    while (prim_GUI!=NULL)
      Componente_Acao(prim_GUI->id,'d');

    numComponentes=0;
  }
  return 0;
}

void GUI_pilha(char oq) {
  if (oq == 'a') {
    struct pilhaElement *pilhaElm=(struct pilhaElement *)calloc(1,sizeof(struct pilhaElement));

    pilhaElm->atualComp=componenteAtual;
    pilhaElm->primComp=prim_GUI;

    empilha(pilha_GUI,pilhaElm);

    prim_GUI=NULL;
    componenteAtual=NULL;
  }
  else if (oq == 'r') {
    struct pilhaElement *pilhaElm=desempilha(pilha_GUI);

    componenteAtual=pilhaElm->atualComp;
    prim_GUI=pilhaElm->primComp;

    free(pilhaElm);
  }
}

static void GUI_setView(GLint *viewport, int x, int y, int w, int h) {
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glViewport(x+viewport[0], viewport[3]-h-y+viewport[1], w, h);
  glOrtho(0, w, h,0, -1, 500);

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
}

static void GUI_recuperarView(GLint *viewport) {
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();

  glViewport(viewport[0], viewport[1], viewport[2], viewport[3]);
  glOrtho(0, viewport[2], viewport[3],0, -1, 500);

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
}

void drawRepetir(Textura *img, int x, int y, int w, int h,int x2, int y2, int w2, int h2) {
  int largura,altura;
  int absLarg,absAlt;

  for (altura=0; altura<=h ;altura+=h2) {
    for (largura=0; largura<=w ;largura+=w2) {
      absLarg=abs(largura-w);
      absAlt=abs(altura-h);

      DrawIMG(img,x+largura,y+altura,(absLarg<w2)?absLarg:w2,(absAlt<h2)?absAlt:h2,x2,y2);
    }
  }
}

int GUI_BuscaElem(int id, int tipo) {
  if ((!componenteAtual) || (componenteAtual->id != id))
    Componente_Acao(id,'s');

  if ((!componenteAtual) || ((tipo!=0) && (componenteAtual->tipo!=tipo))) return 0;
  return 1;
}

void GUI_libera(ListaDupla **lista) {
  void *aux;

  forListDupla (struct componentes *, componenteTmp, *lista) {
    componenteAtual=componenteTmp;
    aux=componenteAtual->aux;

    if ((componenteAtual->larguraLenMax != -1) && (componenteAtual->label != NULL)) {
      free(componenteAtual->label);
      componenteAtual->label=NULL;
    }

    if (aux!=NULL) {
      if (componenteAtual->tipo == EDITBOX) {
        int i;
        char **antTexto=(char **) aux;

        for(i=0;i<5;i++) {
          free(antTexto[i]);
          antTexto[i]=NULL;
        }
        free(antTexto);
        antTexto=NULL;

        aux=NULL;
      }
      else if ((componenteAtual->tipo == LISTBOX) || (componenteAtual->tipo == COMBOBOX)) {
        Lista *primItens=NULL;

        if (componenteAtual->tipo == LISTBOX) {
          primItens=((ListboxVarAux *) aux)->listElementos;
          free(aux);
        }
        else
          primItens=(Lista *) aux;

        forList (struct componenteItem *, textoAtual, primItens) {
          if (textoAtual->texto != NULL) {
            free(textoAtual->texto);
            textoAtual->texto=NULL;
          }
        }

        while (primItens != NULL)
          lista_acao('d',&primItens,primItens->id,MUDAR_ID,0);

        aux=NULL;
      }
      else if ((componenteAtual->tipo == JANELA) || (componenteAtual->tipo == GRUPO) || (componenteAtual->tipo == GROUPBOX)) {
        ListaDupla *primJanela=(ListaDupla *) aux;
        GUI_pilha('a');
          GUI_libera(&primJanela);
        GUI_pilha('r');

        aux=NULL;
      }
      else if (componenteAtual->tipo == ABA) {
        Lista *primAbas=(Lista *) aux;

        forList (struct listaAbas *, abaTmp, primAbas) {

          if (abaTmp->label != NULL) {
            free(abaTmp->label);
            abaTmp->label=NULL;
          }

          ListaDupla *abaFilhos=(ListaDupla *) abaTmp->filhos;
          GUI_pilha('a');
            GUI_libera(&abaFilhos);
          GUI_pilha('r');
        }

        while (primAbas != NULL)
          lista_acao('d',&primAbas,primAbas->id,NAO_MUDAR_ID | ADD_CERTO,0);

        aux=NULL;
      }
      else if (componenteAtual->tipo == FUNCAODESENHO)
        aux=NULL;
      else if (componenteAtual->tipo == IMAGEM) {
        if (componenteAtual->opt&IMAGEM_DELETAR)
          SDL_FreeSurface((SDL_Surface *) aux);
        aux=NULL;
      }

      if (aux)
        free(aux);
    }
  }

  while (*lista != NULL)
    listaDupla_acao('d',lista,(*lista)->id,NAO_MUDAR_ID | ADD_CERTO,0);
}

void GUI_setecionar(int id) {
  if (!GUI_BuscaElem(id,0)) return;

  guiElementoAtivo=componenteAtual;
}

void GUI_MudarCor(int id, unsigned char r, unsigned char g, unsigned char b) {
  if (!GUI_BuscaElem(id,0)) return;

  if (componenteAtual->tipo == LISTBOX) return;

  componenteAtual->r=r;
  componenteAtual->g=g;
  componenteAtual->b=b;
}

void GUI_MudarFonte(int id, Fonte *fonte) {
  if (!GUI_BuscaElem(id,0)) return;

  componenteAtual->fonte=fonte;

  if (componenteAtual->tipo == TEXTO) {
    componenteAtual->w=larguraTexto(fonte,"%s",componenteAtual->label);
    componenteAtual->h=alturaTexto(fonte);
  }
}

ListaDupla **GUI_AbrirFilho(int id) {
  if (!GUI_BuscaElem(id,0)) return NULL;
  if ((componenteAtual->tipo != JANELA) && (componenteAtual->tipo != ABA) && (componenteAtual->tipo != GRUPO) && (componenteAtual->tipo != GROUPBOX))
    return NULL;

  ListaDupla **primComp;

  if (componenteAtual->tipo == ABA) {
    Lista *listElementos=(Lista *) componenteAtual->aux;
    struct listaAbas *abaAtual=(struct listaAbas *) lista_acao('s',&listElementos,componenteAtual->cursor,NAO_MUDAR_ID | ADD_CERTO,sizeof(struct componenteItem));
    if (abaAtual == NULL) return 0;

    primComp=&abaAtual->filhos;
  }
  else
    primComp=(ListaDupla **) &componenteAtual->aux;

  GUI_pilha('a');
    prim_GUI=*primComp;

  return primComp;
}

void GUI_FecharFilho(ListaDupla **primComp) {
    *primComp=prim_GUI;
  GUI_pilha('r');
}

void GUI_AbrirPai() {
  if (paiAnt == NULL) return;

  GUI_pilha('a');
    prim_GUI=paiAnt;
}

void GUI_FecharPai() {
    paiAnt=prim_GUI;
  GUI_pilha('r');
}

void EditBox(char oq, char *label,int id, int x, int y, unsigned int w, int ativo, int opt, void *funcao) {
  if (oq=='n') {
    int largura=larguraTexto(fontGUI,"A");

    largura=floor((w-6)/largura);

    Componente_Acao(id,'n');
    componenteAtual->id=id;
    componenteAtual->tipo=EDITBOX;

    componenteAtual->r=0;
    componenteAtual->g=0;
    componenteAtual->b=0;

    componenteAtual->opt=opt;
    componenteAtual->cursor=(label == NULL)? 0:strlen(label);
    componenteAtual->larguraLenMax=largura;
    componenteAtual->opt3=0;

    componenteAtual->ativo=ativo;
    componenteAtual->label=(char *) calloc(largura+1,sizeof(char));
    if (label) strncpy(componenteAtual->label,label,largura);

    componenteAtual->x=x;
    componenteAtual->y=y;
    componenteAtual->w=w;
    componenteAtual->h=19;

    componenteAtual->funcao=funcao;

    char **antTexto=NULL;

    if (opt & EDITBOX_HISTORICO) {
      int i;

      antTexto=(char **) calloc(5,sizeof(char *));
      for(i=0;i<5;i++)
        antTexto[i]=(char *) calloc(largura+1,sizeof(char));
    }
    componenteAtual->aux=(void *) antTexto;
  }
  else if (oq=='d') {
    unsigned char r=componenteAtual->r;
    unsigned char g=componenteAtual->g;
    unsigned char b=componenteAtual->b;

    int selec=(guiElementoAtivo == componenteAtual)*19;
    DrawIMG(gui_i,x,y,6,19,0,selec);
    drawRepetir(gui_i,x+6,y,w-12,19,6,selec,6,19);
    DrawIMG(gui_i,x+w-6,y,6,19,12,selec);

    if (label[0]!='\0') {
      if (opt&EDITBOX_PASSWORD) {
        int largura=larguraTexto(fontGUI,"*");
        int percorre;

        for (percorre=0; percorre<strlen(label) ;percorre++)
          DrawText(fontGUI,r,g,b,255,1,x+3+percorre*largura,y+3,"*");
      }
      else {
        if (opt&TEXTO_EMOTICO)
          Draw_TextEmo(fontGUI,r,g,b,255,1,x+3,y+3,"%s",label);
        else
          DrawText(fontGUI,r,g,b,255,1,x+3,y+3,"%s",label);
      }
    }

    if (guiElementoAtivo == componenteAtual) {
      int w,h;
      char chartemp;
      chartemp=label[componenteAtual->cursor];
      label[componenteAtual->cursor]='\0';

      w=larguraTexto(fontGUI,"%s",label);
      h=alturaTexto(fontGUI);

      if ((w == -1) || (h == -1))
        printf("ERRO gui\n");
      else
        fillRectangle(x+w+3,y+4,1,h-2,0,0,0,255);

      label[componenteAtual->cursor]=chartemp;
    }
  }
}

void EditBox_SalvaHistorico(int id) {

  if ((!GUI_BuscaElem(id,EDITBOX)) || (!(componenteAtual->opt & EDITBOX_HISTORICO))) return;

  char **antTexto=(char **) componenteAtual->aux;

  int tempconver;
  for (tempconver=3;tempconver>=0;tempconver--)
    strcpy(antTexto[tempconver+1],antTexto[tempconver]);
  strcpy(antTexto[0],componenteAtual->label);

  componenteAtual->opt3=0;
  componenteAtual->aux=(void *) antTexto;
}

void Botao(char oq, char *label, int id, int x, int y, unsigned int w, int ativo, void *funcao) {
  if (oq=='n') {
    int tamanho=strlen(label);

    Componente_Acao(id,'n');
    componenteAtual->id=id;
    componenteAtual->tipo=BOTAO;
    componenteAtual->label=(char *) calloc(tamanho+1,sizeof(char));
    strncpy(componenteAtual->label,label,tamanho);

    componenteAtual->x=x;
    componenteAtual->y=y;
    componenteAtual->w=w;
    componenteAtual->h=19;

    componenteAtual->r=0;
    componenteAtual->g=0;
    componenteAtual->b=0;

    componenteAtual->funcao=funcao;
    componenteAtual->opt=0;
    componenteAtual->larguraLenMax=tamanho;
    componenteAtual->ativo=ativo;

    componenteAtual->fonte=fontGUI;
    componenteAtual->aux=NULL;
  }
  else if (oq=='d') {
    unsigned char r=componenteAtual->r;
    unsigned char g=componenteAtual->g;
    unsigned char b=componenteAtual->b;
    Fonte *fonte=componenteAtual->fonte;

    int press=(componenteAtual->opt!=0)*19;
    int tamanho=larguraTexto(fonte,"%s",label);

    DrawIMG(gui_i,x,y,6,19,18,press);
    drawRepetir(gui_i,x+6,y,w-12,19,24,press,6,19);
    DrawIMG(gui_i,x+w-6,y,6,19,30,press);

    DrawText(fonte,r,g,b,255,1,x+w/2-tamanho/2,y+3,"%s",label);
  }
}

void Scroll_Draw(int x, int y, int tamanho, int lado,ScrollElmt *scroll) {
  int elemtClick=scroll->elemtClick;
  int scrollPosicao=scroll->barraPosicaoVer*(tamanho-SCROLL_LISTBOX*2-10)/100+SCROLL_LISTBOX;

  if (lado&SCROLLBAR_VERTICAL) {
    DrawIMG(gui_i,x,y,SCROLL_LISTBOX,SCROLL_LISTBOX,51 + ((elemtClick == 1)? SCROLL_LISTBOX:0),0);
    DrawIMG(gui_i,x,y+tamanho-SCROLL_LISTBOX,SCROLL_LISTBOX,SCROLL_LISTBOX,36 + ((elemtClick == 2)? SCROLL_LISTBOX:0),20);
    drawRepetir(gui_i,x,y+SCROLL_LISTBOX,SCROLL_LISTBOX,tamanho-SCROLL_LISTBOX*2,51,15,15,5);

    DrawIMG(gui_i, x, y+scrollPosicao,SCROLL_LISTBOX,10,36,(elemtClick == 3)? 10:0);
  }
  else {
    DrawIMG(gui_i,x,y,SCROLL_LISTBOX,SCROLL_LISTBOX,128,((elemtClick == 1)? SCROLL_LISTBOX:0));
    DrawIMG(gui_i,x+tamanho-SCROLL_LISTBOX,y,SCROLL_LISTBOX,SCROLL_LISTBOX,113,15 + ((elemtClick == 2)? SCROLL_LISTBOX:0));
    drawRepetir(gui_i,x+SCROLL_LISTBOX,y,tamanho-SCROLL_LISTBOX*2,SCROLL_LISTBOX,143,15,5,SCROLL_LISTBOX);

    DrawIMG(gui_i, x+scrollPosicao, y,10,SCROLL_LISTBOX,(elemtClick == 3)? 128:138,30);
  }
}

void ScrollBar(char oq, int id, int x, int y, unsigned int tamanho, int quantidade, int ativo, int opt, void *funcao) {
  if (oq=='n') {
    int lado=(opt&SCROLLBAR_HORIZONTAL) | (opt&SCROLLBAR_VERTICAL);

    if (!lado) opt|=SCROLLBAR_VERTICAL;

    Componente_Acao(id,'n');
    componenteAtual->id=id;
    componenteAtual->tipo=SCROLLBAR;
    componenteAtual->label=NULL;

    componenteAtual->x=x;
    componenteAtual->y=y;
    componenteAtual->w=(lado == SCROLLBAR_HORIZONTAL)?tamanho:SCROLL_LISTBOX;
    componenteAtual->h=(lado == SCROLLBAR_VERTICAL)?tamanho:SCROLL_LISTBOX;

    componenteAtual->opt2=tamanho;
    componenteAtual->opt3=lado;
    componenteAtual->quantidade=0;

    componenteAtual->funcao=funcao;
    componenteAtual->opt=opt;
    componenteAtual->ativo=ativo;

    componenteAtual->larguraLenMax=-1;

    ScrollElmt *scroll=(ScrollElmt *) calloc(1,sizeof(ScrollElmt));

    scroll->elemtClick=0;
    scroll->quantElementos=quantidade-1;
    scroll->barraPosicaoRol=0;
    scroll->barraPosicaoVer=(opt & SCROLL_INVERSO)?100:0;
    scroll->inverso=opt & SCROLL_INVERSO;

    componenteAtual->aux=(void *) scroll;
  }
  else if (oq=='d') {
    Scroll_Draw(x,y,tamanho,opt,(ScrollElmt *) componenteAtual->aux);
  }
}

static void Scroll_BarraRolar(int id, int x, int y, int tamanho, int lado,ScrollElmt *scroll) {
  if (!GUI_BuscaElem(id,0)) return;
  if ((componenteAtual->tipo != LISTBOX) && (componenteAtual->tipo != SCROLLBAR)) return;

  int baseComp;
  int baseEntrada;
  int totalCabe=componenteAtual->quantidade;

  if (lado&SCROLLBAR_VERTICAL) {
    baseComp=componenteAtual->y;
    baseEntrada=y;
  }
  else {
    baseComp=componenteAtual->x;
    baseEntrada=x;
  }

  if (x<0) x=0;
  if (y<0) y=0;

  scroll->barraPosicaoVer=(((baseEntrada-(baseComp+SCROLL_LISTBOX))*100)/(tamanho-SCROLL_LISTBOX*2));

  if (baseEntrada>=baseComp+tamanho-SCROLL_LISTBOX) { scroll->barraPosicaoVer=100; }
  else if (baseEntrada<=baseComp+SCROLL_LISTBOX) { scroll->barraPosicaoVer=0; }

  scroll->barraPosicaoRol=((scroll->barraPosicaoVer*(scroll->quantElementos-totalCabe))/100);

  if (scroll->barraPosicaoRol<0)
    scroll->barraPosicaoRol=0;
  if (totalCabe+scroll->barraPosicaoRol>scroll->quantElementos)
    scroll->barraPosicaoRol=scroll->quantElementos-totalCabe;

  if (scroll->inverso)
    scroll->barraPosicaoRol=(scroll->quantElementos-scroll->barraPosicaoRol)-totalCabe;

  if (scroll->barraPosicaoRol<0) { scroll->barraPosicaoRol=0; }

}

static void Scroll_arrumar(ScrollElmt *scroll) {
  int totalCabe=componenteAtual->quantidade;

  if (totalCabe+scroll->barraPosicaoRol > scroll->quantElementos)
    scroll->barraPosicaoRol=scroll->quantElementos-totalCabe;

  if (scroll->barraPosicaoRol<0)
    scroll->barraPosicaoRol=0;

  if (scroll->quantElementos > totalCabe) {
    int scrollPos=scroll->barraPosicaoRol;
    if (scroll->inverso)
      scrollPos=(scroll->quantElementos-scroll->barraPosicaoRol)-totalCabe;

    scroll->barraPosicaoVer=(scrollPos*100)/(scroll->quantElementos-totalCabe);
  }
}

static void Scroll_evento(int x, int y, int guiX, int guiY, int tamanho, int lado, int tipo, ScrollElmt *scroll) {
  int tamanhoX=0;
  int tamanhoY=0;
  int clicou=-1;

  if (lado&SCROLLBAR_HORIZONTAL)
    tamanhoX=tamanho-SCROLL_LISTBOX;
  else
    tamanhoY=tamanho-SCROLL_LISTBOX;

  x+=guiX;
  y+=guiY;

  if (mouseverondeclia(x,x+SCROLL_LISTBOX,y,y+SCROLL_LISTBOX)) {
    scroll->elemtClick=1;
    clicou=1;
  }
  else if (mouseverondeclia(x+tamanhoX,x+tamanhoX+SCROLL_LISTBOX,y+tamanhoY,y+tamanhoY+SCROLL_LISTBOX)) {
    scroll->elemtClick=2;
    clicou=0;
  }
  else {
    scroll->elemtClick=3;
    Scroll_BarraRolar(componenteAtual->id,mousemovidox-guiX,mousemovidoy-guiY,tamanho,lado,scroll);
  }
  if (tipo == 2) {
    scroll->elemtClick=0;

    if (clicou != -1) {
      clicou=abs(!(scroll->inverso) - clicou);

      if (clicou) scroll->barraPosicaoRol++;
      else scroll->barraPosicaoRol--;

      Scroll_arrumar(scroll);
    }
  }
}

void Scroll_setTamanho(int id, int tamanho) {
  if (!GUI_BuscaElem(id,SCROLLBAR)) return;

  int lado=(componenteAtual->opt&SCROLLBAR_HORIZONTAL) | (componenteAtual->opt&SCROLLBAR_VERTICAL);

  if (!lado) componenteAtual->opt|=SCROLLBAR_VERTICAL;

  componenteAtual->w=(lado == SCROLLBAR_HORIZONTAL)?tamanho:SCROLL_LISTBOX;
  componenteAtual->h=(lado == SCROLLBAR_VERTICAL)?tamanho:SCROLL_LISTBOX;

  componenteAtual->opt2=tamanho;
}

int Scroll_getPosicao(int id) {
  if (!GUI_BuscaElem(id,SCROLLBAR)) return -1;

  ScrollElmt *scroll=(ScrollElmt *) componenteAtual->aux;

  return scroll->barraPosicaoRol;
}

//TODO: Implementar funcao
void Scroll_setPosicao(int id, int posicao) {
  if (!GUI_BuscaElem(id,SCROLLBAR)) return;

  ScrollElmt *scroll=(ScrollElmt *) componenteAtual->aux;
  scroll->barraPosicaoRol=posicao;

  Scroll_arrumar(scroll);
}

void ListBox(char oq, int id, int x, int y, unsigned int w, unsigned int h, int ativo, int opt, void *funcao) {
  if (oq=='n') {
    int altura;
    int largura=larguraTexto(fontGUI,"A");

    largura=floor((w-6-SCROLL_LISTBOX)/largura);
    altura=floor((h-6)/14);

    Componente_Acao(id,'n');
    componenteAtual->id=id;
    componenteAtual->label=NULL;
    componenteAtual->tipo=LISTBOX;
    componenteAtual->opt=opt;

    componenteAtual->quantidade=altura;

    componenteAtual->cursor=0;
    componenteAtual->ativo=ativo;

    componenteAtual->x=x;
    componenteAtual->y=y;
    componenteAtual->w=w;
    componenteAtual->h=h;

    ListboxVarAux *variaveisAux=(ListboxVarAux *) calloc(1,sizeof(ListboxVarAux));
    variaveisAux->larguraLen=largura;

    variaveisAux->scroll.barraPosicaoVer=(opt & SCROLL_INVERSO)?100:0;
    variaveisAux->scroll.barraPosicaoRol=0;
    variaveisAux->scroll.quantElementos=0;
    variaveisAux->scroll.elemtClick=0;
    variaveisAux->scroll.inverso=opt & SCROLL_INVERSO;

    componenteAtual->aux=(void *) variaveisAux;

    componenteAtual->funcao=funcao;
    componenteAtual->larguraLenMax=-1;
  }
  else if (oq=='d') {
    ListboxVarAux *variaveisAux=(ListboxVarAux *) componenteAtual->aux;
    ScrollElmt *scroll=&variaveisAux->scroll;

    Scroll_Draw(x+w-SCROLL_LISTBOX,y,h,SCROLLBAR_VERTICAL,scroll);

    fillRectangle(x,y,w-SCROLL_LISTBOX,h,255,255,255,(opt&LISTBOX_FUNDOTRANS)?150:255);

    if (!(opt&LISTBOX_SEMBORDA))
      drawRectangle(x,y,w-SCROLL_LISTBOX,h,138,138,128,255);

    int totalCabe=componenteAtual->quantidade;
    int quant=0,contar=0,posY=0,chegou=0;

    int chegada=scroll->barraPosicaoRol;

    forList (struct componenteItem *, textoAtual, variaveisAux->listElementos) {
      if (chegou!=-1) {
        if (chegada==chegou)
          chegou=-1;
        else {
          chegou++;
          continue;
        }
      }

      if (contar >= totalCabe) break;

      if (scroll->inverso)
        posY=(totalCabe+(--quant))*16;
      else
        posY=(quant++)*16;

      if (opt&TEXTO_EMOTICO)
        Draw_TextEmo(fontGUI,textoAtual->r,textoAtual->g,textoAtual->b,255,textoAtual->qualidade,x+3,y+3+posY,"%s",textoAtual->texto);
      else
        DrawText(fontGUI,textoAtual->r,textoAtual->g,textoAtual->b,255,textoAtual->qualidade,x+3,y+3+posY,"%s",textoAtual->texto);

      contar++;
    }
  }
}

void ListBox_Adicionar(int id, unsigned char r,unsigned char g,unsigned char b, char qualid, char *texto, ...) {
  char mesg[256];
  va_list ap;

  if (texto==NULL) return;

  va_start( ap, texto );
  vsprintf( mesg, texto, ap );
  va_end( ap );

  if (!GUI_BuscaElem(id,LISTBOX)) return;

  ListboxVarAux *variaveisAux=(ListboxVarAux *) componenteAtual->aux;
  ScrollElmt *scroll=&variaveisAux->scroll;

  struct componenteItem *lItem=(struct componenteItem *) lista_acao('n',&variaveisAux->listElementos,1,MUDAR_ID,sizeof(struct componenteItem));
  (scroll->quantElementos)++;

  scroll->barraPosicaoVer=(scroll->inverso)?100:0;
  scroll->barraPosicaoRol=0;

  lItem->r=r;
  lItem->g=g;
  lItem->b=b;
  lItem->qualidade=qualid;
  lItem->texto=(char *) calloc(variaveisAux->larguraLen+1,sizeof(char));

  if (mesg[0] != '\0') strncpy(lItem->texto,mesg,variaveisAux->larguraLen);
}

void CheckBox(char oq, char *label, int id, int x, int y, int sel, int ativo, void *funcao) {
  if (oq=='n') {
    int tamanho=strlen(label);

    Componente_Acao(id,'n');
    componenteAtual->id=id;
    componenteAtual->tipo=CHECKBOX;
    componenteAtual->label=(char *) calloc(tamanho+1,sizeof(char));
    strncpy(componenteAtual->label,label,tamanho);

    componenteAtual->x=x;
    componenteAtual->y=y;
    componenteAtual->w=13;
    componenteAtual->h=13;

    componenteAtual->r=0;
    componenteAtual->g=0;
    componenteAtual->b=0;

    componenteAtual->funcao=funcao;
    componenteAtual->opt=sel;
    componenteAtual->ativo=ativo;

    componenteAtual->larguraLenMax=tamanho;

    componenteAtual->fonte=fontGUI;
    componenteAtual->aux=NULL;
  }
  else if (oq=='d') {
    unsigned char r=componenteAtual->r;
    unsigned char g=componenteAtual->g;
    unsigned char b=componenteAtual->b;
    Fonte *fonte=componenteAtual->fonte;

    DrawIMG(gui_i,x,y,13,13,85,componenteAtual->opt*13);

    DrawText(fonte,r,g,b,255,1,x+15,y-1,"%s",label);
  }
}

void CheckBox_setSelect(int id, int sel) {
  if (!GUI_BuscaElem(id,CHECKBOX)) return;

  componenteAtual->opt=(sel)?1:0;
}

int CheckBox_isSelect(int id) {
  if (!GUI_BuscaElem(id,CHECKBOX)) return -1;

  return componenteAtual->opt;
}

void RadioButton(char oq, char *label, int id, int grupo, int x, int y, int ativo,void *funcao) {
  if (oq=='n') {
    int tamanho=strlen(label);

    Componente_Acao(id,'n');
    componenteAtual->id=id;
    componenteAtual->tipo=RADIOBUTTON;
    componenteAtual->label=(char *) calloc(tamanho+1,sizeof(char));
    strncpy(componenteAtual->label,label,tamanho);

    componenteAtual->x=x;
    componenteAtual->y=y;
    componenteAtual->w=13;
    componenteAtual->h=13;

    componenteAtual->r=0;
    componenteAtual->g=0;
    componenteAtual->b=0;

    componenteAtual->funcao=funcao;
    componenteAtual->opt=0;
    componenteAtual->opt2=grupo;
    componenteAtual->ativo=ativo;

    componenteAtual->larguraLenMax=tamanho;

    componenteAtual->fonte=fontGUI;
    componenteAtual->aux=NULL;
  }
  else if (oq=='d') {
    unsigned char r=componenteAtual->r;
    unsigned char g=componenteAtual->g;
    unsigned char b=componenteAtual->b;
    Fonte *fonte=componenteAtual->fonte;

    DrawIMG(gui_i,x,y,13,13,70+componenteAtual->opt*13,26);

    DrawText(fonte,r,g,b,255,1,x+15,y-1,"%s",label);
  }
}

int RadioButton_Select(int id) {
  int grupo;

  if (GUI_BuscaElem(id,RADIOBUTTON)) {
    componenteAtual->opt=1;
    grupo=componenteAtual->opt2;

    forListDupla (struct componentes *, componenteTmp, prim_GUI) {
      componenteAtual=componenteTmp;

      if ((componenteAtual->tipo==RADIOBUTTON) && (componenteAtual->opt2==grupo) && (componenteAtual->id!=id))
        componenteAtual->opt=0;
    }
    return 1;
  }

  return 0;
}

int RadioButton_getSelect(int grupo) {
  forListDupla (struct componentes *, componenteTmp, prim_GUI) {
    componenteAtual=componenteTmp;

    if ((componenteAtual->tipo==RADIOBUTTON) && (componenteAtual->opt2==grupo) && (componenteAtual->opt))
      return componenteAtual->id;
  }

  return -1;
}

void GroupBox(char oq, char *label, ListaDupla *filhos, int id, int x, int y, int w, int h, int ativo, void *funcao) {
  if (oq=='n') {
    int tamanho=strlen(label);
    int largura=larguraTexto(fontGUI,"%s",label);

    Componente_Acao(id,'n');
    componenteAtual->id=id;
    componenteAtual->tipo=GROUPBOX;
    componenteAtual->label=(char *) calloc(tamanho+1,sizeof(char));
    strncpy(componenteAtual->label,label,tamanho);

    componenteAtual->x=x;
    componenteAtual->y=y;
    componenteAtual->w=w;
    componenteAtual->h=h;

    componenteAtual->r=0;
    componenteAtual->g=0;
    componenteAtual->b=0;

    componenteAtual->funcao=funcao;
    componenteAtual->opt=largura;
    componenteAtual->ativo=ativo;

    componenteAtual->larguraLenMax=tamanho;

    componenteAtual->aux=filhos;
  }
  else if (oq=='d') {
    struct componentes *tempComponet=componenteAtual;

    unsigned char r=componenteAtual->r;
    unsigned char g=componenteAtual->g;
    unsigned char b=componenteAtual->b;

    drawLine(x,y,x+5,y,0,0,0,255);

    drawLine(x+componenteAtual->opt+5,y,x+w,y,0,0,0,255);

    drawLine(x,y,x,y+h,0,0,0,255);
    drawLine(x+w,y,x+w,y+h,0,0,0,255);
    drawLine(x,y+h,x+w,y+h,0,0,0,255);

    DrawText(fontGUI,r,g,b,255,1,x+5,y-8,"%s",label);

   	GLint	viewport[4];
    glGetIntegerv(GL_VIEWPORT, viewport);

    GUI_setView(viewport,x,y,w,h);

      GUI_Draw(5,5,filhos);

    GUI_recuperarView(viewport);

    componenteAtual=tempComponet;
  }
}

void ProgressBar(char oq, int id, int x, int y, int w, int percentatual, int percentmax, int ativo, void *funcao) {
  if (oq=='n') {
    Componente_Acao(id,'n');
    componenteAtual->id=id;
    componenteAtual->tipo=PROGRESSBAR;

    componenteAtual->x=x;
    componenteAtual->y=y;
    componenteAtual->w=w;
    componenteAtual->h=14;

    componenteAtual->funcao=funcao;
    componenteAtual->opt=percentatual;
    componenteAtual->opt2=percentmax;
    componenteAtual->ativo=ativo;

    componenteAtual->larguraLenMax=-1;

    componenteAtual->aux=NULL;
  }
  else if (oq=='d') {
    int barra=(w-2)*percentatual/percentmax;
    if (barra<0) barra=0;
    else if (barra>w-2) barra=w-2;

    drawRepetir(gui_i,x+1,y,barra,14,0,38,31,14);
    drawRepetir(gui_i,x+barra+1,y,w-2-barra,14,31,38,5,14);

    DrawIMG(gui_i,x,y,4,15,36,38);
    DrawIMG(gui_i,x+w-4,y,4,15,40,38);
  }
}

void ProgressBar_setValor(int id, int valor) {
  if (!GUI_BuscaElem(id,PROGRESSBAR)) return;

  if (valor <= componenteAtual->opt2)
    componenteAtual->opt=valor;
}

int ProgressBar_getValor(int id) {
  if (!GUI_BuscaElem(id,PROGRESSBAR)) return -1;

  return componenteAtual->opt;
}

void ComboBox(char oq, int id, int x, int y, unsigned int w, int ativo,int opt, void *funcao) {
  if (oq=='n') {
    int largura=larguraTexto(fontGUI,"A");

    largura=floor((w-6-19)/largura);

    Componente_Acao(id,'n');
    componenteAtual->id=id;
    componenteAtual->label=(char *) calloc(largura+1,sizeof(char));

    componenteAtual->tipo=COMBOBOX;
    componenteAtual->larguraLenMax=largura;

    componenteAtual->opt=opt;
    componenteAtual->opt2=0;
    componenteAtual->opt3=0;

    componenteAtual->quantidade=0;
    componenteAtual->cursor=0;

    componenteAtual->x=x;
    componenteAtual->y=y;
    componenteAtual->w=w;
    componenteAtual->h=19;

    componenteAtual->r=0;
    componenteAtual->g=0;
    componenteAtual->b=0;

    componenteAtual->aux=NULL;
    componenteAtual->ativo=ativo;
    componenteAtual->funcao=funcao;
  }
  else if (oq=='d') {
    unsigned char r=componenteAtual->r;
    unsigned char g=componenteAtual->g;
    unsigned char b=componenteAtual->b;

    DrawIMG(gui_i,x,y,6,19,44,38);
    drawRepetir(gui_i,x+6,y,w-12,19,50,38,6,19);
    DrawIMG(gui_i,x+w-6,y,6,19,56,38);

    DrawIMG(gui_i,x+w-19,y+2,17,15,62,39);

    if (opt&TEXTO_EMOTICO)
      Draw_TextEmo(fontGUI,r,g,b,255,1,x+3,y+3,"%s",componenteAtual->label);
    else
      DrawText(fontGUI,r,g,b,255,1,x+3,y+3,"%s",componenteAtual->label);

    if (componenteAtual->opt3) {
      int altura=componenteAtual->quantidade*16;
      int cont=0;
      int posY=y+19;

      w-=19;

      //esquerda
      drawRepetir(gui_i,x,posY,6,altura,79,39,6,5);
      DrawIMG(gui_i,x,posY+altura,6,5,79,44);

      //meio
      drawRepetir(gui_i,x+6,posY,w-12,altura,85,39,6,5);
      drawRepetir(gui_i,x+6,posY+altura,w-12,5,85,44,6,5);

      //direita
      drawRepetir(gui_i,x+w-6,posY,6,altura,91,39,6,5);
      DrawIMG(gui_i,x+w-6,posY+altura,6,5,91,44);

      forList (struct componenteItem *, textoAtual, (Lista *) componenteAtual->aux) {

        if (++cont == componenteAtual->cursor) {
          drawRepetir(gui_i,x,posY+2,6,16,79,49,6,5);
          drawRepetir(gui_i,x+6,posY+2,w-12,16,85,49,6,5);
          drawRepetir(gui_i,x+w-6,posY+2,6,16,91,49,6,5);
        }

        if (opt&TEXTO_EMOTICO)
          Draw_TextEmo(fontGUI,textoAtual->r,textoAtual->g,textoAtual->b,255,textoAtual->qualidade,x+3,posY+3,"%s",textoAtual->texto);
        else
          DrawText(fontGUI,textoAtual->r,textoAtual->g,textoAtual->b,255,textoAtual->qualidade,x+3,posY+3,"%s",textoAtual->texto);

        posY+=16;
      }
    }
  }
}

void ComboBox_Adicionar(int id, unsigned char r,unsigned char g,unsigned char b, char qualid, char *texto, ...) {
  char mesg[256];
  va_list ap;

  if (texto==NULL) return;

  va_start( ap, texto );
  vsprintf( mesg, texto, ap );
  va_end( ap );

  if (!GUI_BuscaElem(id,COMBOBOX)) return;

  Lista *listElementos=(Lista *) componenteAtual->aux;

  struct componenteItem *lItem=(struct componenteItem *) lista_acao('n',&listElementos,++componenteAtual->quantidade,NAO_MUDAR_ID | ADD_CERTO,sizeof(struct componenteItem));

  lItem->r=r;
  lItem->g=g;
  lItem->b=b;
  lItem->qualidade=qualid;
  lItem->texto=(char *) calloc(componenteAtual->larguraLenMax+1,sizeof(char));

  if (mesg[0] != '\0') strncpy(lItem->texto,mesg,componenteAtual->larguraLenMax);

  componenteAtual->aux=(void *) listElementos;
}

void ComboBox_Limpar(int id) {
  if (!GUI_BuscaElem(id,COMBOBOX)) return;

  Lista *primItens=(Lista *) componenteAtual->aux;

  forList (struct componenteItem *, textoAtual, primItens) {
    if (textoAtual->texto != NULL) {
      free(textoAtual->texto);
      textoAtual->texto=NULL;
    }
  }

  while (primItens != NULL)
    lista_acao('d',&primItens,primItens->id,MUDAR_ID,0);

  componenteAtual->aux=NULL;
  componenteAtual->opt2=0;
  componenteAtual->label[0]='\0';
  componenteAtual->quantidade=0;
}

void ComboBox_Seleciona(int id, int elemento) {
  if (!GUI_BuscaElem(id,COMBOBOX)) return;

  Lista *listElementos=(Lista *) componenteAtual->aux;

  componenteAtual->opt3=0;
  componenteAtual->opt2=elemento;

  if (elemento<=0) return;

  struct componenteItem *lItem=(struct componenteItem *) lista_acao('s',&listElementos,elemento,0,componenteAtual->quantidade);

  if (lItem == NULL) return;

  GUI_MudarCor(id,lItem->r,lItem->g,lItem->b);
  strncpy(componenteAtual->label,lItem->texto,componenteAtual->larguraLenMax);
}

int ComboBox_getValor(int id) {
  if (!GUI_BuscaElem(id,COMBOBOX)) return -1;

  return componenteAtual->opt2;
}

void Texto(char oq, char *label, int id, int x, int y, int qualidade, int ativo, int opt, void *funcao) {
  if (oq=='n') {
    int altura=alturaTexto(fontGUI);
    int largura=larguraTexto(fontGUI,"%s",label);
    int tamanho=strlen(label);

    Componente_Acao(id,'n');
    componenteAtual->id=id;
    componenteAtual->tipo=TEXTO;
    componenteAtual->label=(char *) calloc(tamanho+1,sizeof(char));
    strncpy(componenteAtual->label,label,tamanho);

    componenteAtual->x=x;
    componenteAtual->y=y;
    componenteAtual->w=largura;
    componenteAtual->h=altura;

    componenteAtual->r=0;
    componenteAtual->g=0;
    componenteAtual->b=0;
    componenteAtual->opt2=qualidade;

    componenteAtual->funcao=funcao;
    componenteAtual->opt=opt;
    componenteAtual->ativo=ativo;

    componenteAtual->aux=NULL;

    componenteAtual->fonte=fontGUI;
    componenteAtual->larguraLenMax=tamanho;
  }
  else if (oq=='d') {
    unsigned char r=componenteAtual->r;
    unsigned char g=componenteAtual->g;
    unsigned char b=componenteAtual->b;
    Fonte *fonte=componenteAtual->fonte;

    if (opt&TEXTO_EMOTICO)
      Draw_TextEmo(fonte,r,g,b,255,qualidade,x,y,"%s",label);
    else
      DrawText(fonte,r,g,b,255,qualidade,x,y,"%s",label);
  }
}

void Imagem(char oq, int id, Textura *img, int x, int y, int w, int h, int x2, int y2, int ativo, int opt, void *funcao) {
  if (oq=='n') {
    Componente_Acao(id,'n');
    componenteAtual->id=id;
    componenteAtual->tipo=IMAGEM;

    componenteAtual->x=x;
    componenteAtual->y=y;
    componenteAtual->w=w;
    componenteAtual->h=h;
    componenteAtual->opt2=x2;
    componenteAtual->opt3=y2;

    componenteAtual->funcao=funcao;
    componenteAtual->opt=opt;
    componenteAtual->ativo=ativo;

    componenteAtual->larguraLenMax=-1;

    componenteAtual->aux=img;
  }
  else if (oq=='d') {
    if (img == NULL) return;

    DrawIMG(img,x,y,w,h,x2,y2);
  }
}

void Quadrado(char oq, int id, int x, int y, int w, int h, int ativo, int opt, void *funcao) {
  if (oq=='n') {
    Componente_Acao(id,'n');
    componenteAtual->id=id;
    componenteAtual->tipo=QUADRADO;
    componenteAtual->label=NULL;

    componenteAtual->x=x;
    componenteAtual->y=y;
    componenteAtual->w=w;
    componenteAtual->h=h;

    componenteAtual->r=0;
    componenteAtual->g=0;
    componenteAtual->b=0;

    componenteAtual->funcao=funcao;
    componenteAtual->opt=opt;
    componenteAtual->ativo=ativo;

    componenteAtual->aux=NULL;

    componenteAtual->larguraLenMax=-1;
  }
  else if (oq=='d') {
    unsigned char r=componenteAtual->r;
    unsigned char g=componenteAtual->g;
    unsigned char b=componenteAtual->b;

    if (opt&QUADRADO_PREENCHIDO)
      fillRectangle(x,y,w,h,r,g,b,255);
    else
      drawRectangle(x,y,w,h,r,g,b,255);
  }
}

void FuncaoDesenho(char oq, int id, void (*funcDes)(), int x, int y, int w, int h, int ativo, int opt, void *funcao) {
  if (oq=='n') {
    Componente_Acao(id,'n');
    componenteAtual->id=id;
    componenteAtual->tipo=FUNCAODESENHO;

    componenteAtual->x=x;
    componenteAtual->y=y;
    componenteAtual->w=w;
    componenteAtual->h=h;

    componenteAtual->funcao=funcao;
    componenteAtual->opt=opt;
    componenteAtual->ativo=ativo;

    componenteAtual->larguraLenMax=-1;

    componenteAtual->aux=funcDes;
  }
  else if (oq=='d') {
    if (funcDes == NULL) return;

   	GLint	viewport[4];
    glGetIntegerv(GL_VIEWPORT, viewport);

    GUI_setView(viewport,x,y,w,h);

      (*funcDes)();

      if (opt&FUNCAODESENHO_BORDA)
        drawRectangle(0,0,w,h,0,0,0,255);

    GUI_recuperarView(viewport);
  }
}

void Janela(char oq, char *label, ListaDupla *filhos, int id, int x, int y, int w, int h, int ativo, int opt, void *funcao) {
  if (oq=='n') {
    int tamanho=strlen(label);

    Componente_Acao(id,'n');
    componenteAtual->id=id;
    componenteAtual->tipo=JANELA;
    componenteAtual->label=(char *) calloc(tamanho+1,sizeof(char));
    strncpy(componenteAtual->label,label,tamanho);

    if (opt & JANELA_CENTRALIZADA) {
      componenteAtual->x=screen->w/2-w/2;
      componenteAtual->y=screen->h/2-h/2;
    }
    else {
      componenteAtual->x=x;
      componenteAtual->y=y;
    }
    componenteAtual->w=w;
    componenteAtual->h=h;

    componenteAtual->r=0;
    componenteAtual->g=0;
    componenteAtual->b=0;

    componenteAtual->funcao=funcao;
    componenteAtual->opt=opt;
    componenteAtual->ativo=ativo;
    componenteAtual->cursor=0;

    componenteAtual->larguraLenMax=tamanho;

    componenteAtual->fonte=fontGUI;
    componenteAtual->aux=filhos;
  }
  else if (oq=='d') {
    struct componentes *tempComponet=componenteAtual;
    unsigned char r=componenteAtual->r;
    unsigned char g=componenteAtual->g;
    unsigned char b=componenteAtual->b;
    Fonte *fonte=componenteAtual->fonte;

    fillRectangle(x,y,w,h,128,128,128,255);
    drawRectangle(x,y,w,h,0,0,0,255);

    if (opt&TEXTO_EMOTICO)
      Draw_TextEmo(fonte,r,g,b,255,1,x+5,y,"%s",label);
    else
      DrawText(fonte,r,g,b,255,1,x+5,y,"%s",label);

    if (!(opt&JANELA_NAOFECHAR))
      DrawIMG(gui_i,x+w-16,y,15,10,70,16);

   	GLint	viewport[4];
    glGetIntegerv(GL_VIEWPORT, viewport);

    GUI_setView(viewport,x,y,w,h);

      GUI_Draw(0,15,filhos);

    GUI_recuperarView(viewport);

    componenteAtual=tempComponet;
  }
}

int Janela_getPai() {
  return idJanelaAtual;
}

void Janela_botaoFechar(GUIParms *parm) {
  if (parm->acao == MOUSE_UP_LEFT)
    Janela_fechar();
}

void Janela_fechar() {
  int id=Janela_getPai();

  if (id == -1) return;

  GUI_pilha('a');
    prim_GUI=janelaAnt;

    if (!GUI_BuscaElem(id,JANELA)) return;
    if (componenteAtual->aux == NULL) return;

    struct componentes *atual=componenteAtual;

    ListaDupla *lista=(ListaDupla *) atual->aux;
    GUI_libera(&lista);

    atual->aux=NULL;
    componenteAtual=NULL;

    prim_GUI=janelaAnt;

    Componente_Acao(id,'d');
  GUI_pilha('r');

  prim_GUI=NULL;
}

void Grupo(char oq, ListaDupla *filhos, int id, int x, int y, int w, int h, int ativo, int opt, void *funcao) {
  if (oq=='n') {
    Componente_Acao(id,'n');
    componenteAtual->id=id;
    componenteAtual->tipo=GRUPO;
    componenteAtual->label=NULL;

    componenteAtual->x=x;
    componenteAtual->y=y;
    componenteAtual->w=w;
    componenteAtual->h=h;

    componenteAtual->funcao=funcao;
    componenteAtual->opt=opt;
    componenteAtual->ativo=ativo;

    componenteAtual->larguraLenMax=-1;

    componenteAtual->aux=filhos;
  }
  else if (oq=='d') {
    struct componentes *tempComponet=componenteAtual;

   	GLint	viewport[4];
    glGetIntegerv(GL_VIEWPORT, viewport);

    GUI_setView(viewport,x,y,w,h);

      GUI_Draw(0,0,filhos);

    GUI_recuperarView(viewport);

    componenteAtual=tempComponet;
  }
}

void Aba(char oq, int id, int x, int y, int w, int h, int ativo, int opt, void *funcao) {
  if (oq=='n') {
    Componente_Acao(id,'n');
    componenteAtual->id=id;
    componenteAtual->tipo=ABA;

    componenteAtual->x=x;
    componenteAtual->y=y;
    componenteAtual->w=w;
    componenteAtual->h=h;

    componenteAtual->r=0;
    componenteAtual->g=0;
    componenteAtual->b=0;

    componenteAtual->funcao=funcao;
    componenteAtual->opt=opt;
    componenteAtual->ativo=ativo;
    componenteAtual->cursor=1;

    componenteAtual->quantidade=0;

    componenteAtual->larguraLenMax=-1;

    componenteAtual->aux=NULL;
  }
  else if (oq=='d') {
    struct componentes *tempComponet=componenteAtual;
    unsigned char r=componenteAtual->r;
    unsigned char g=componenteAtual->g;
    unsigned char b=componenteAtual->b;

    int largura;
    int posSel;
    const int altAba=27;
    int maisX=0;
    ListaDupla *filhosDraw=NULL;

    DrawIMG(gui_i,x,y+altAba,5,5,113,0);
    drawRepetir(gui_i,x,y+altAba+5,5,h-altAba-10,113,5,5,5);
    DrawIMG(gui_i,x,y+h-5,5,5,113,10);

    drawRepetir(gui_i,x+5,y+altAba,w-10,5,118,0,5,5);
    drawRepetir(gui_i,x+5,y+altAba+5,w-10,h-altAba-10,118,5,5,5);
    drawRepetir(gui_i,x+5,y+h-5,w-10,5,118,10,5,5);

    DrawIMG(gui_i,x+w-5,y+altAba,5,5,123,0);
    drawRepetir(gui_i,x+w-5,y+altAba+5,5,h-altAba-10,123,5,5,5);
    DrawIMG(gui_i,x+w-5,y+h-5,5,5,123,10);

    forList (struct listaAbas *, abaAtual, (Lista *) componenteAtual->aux) {
      largura=abaAtual->largura;

      if (tempComponet->cursor == abaAtual_Id) {
        filhosDraw=abaAtual->filhos;
        posSel=0;
      }
      else
        posSel=29;

      DrawIMG(gui_i,x+maisX,y,5,28,98,posSel);
      drawRepetir(gui_i,x+maisX+5,y,largura,28,103,posSel,5,28);
      DrawIMG(gui_i,x+largura+maisX+5,y,5,28,108,posSel);

      if (opt&TEXTO_EMOTICO)
        Draw_TextEmo(fontGUI,r,g,b,255,1,x+maisX+5,y+8,"%s",abaAtual->label);
      else
        DrawText(fontGUI,r,g,b,255,1,x+maisX+5,y+8,"%s",abaAtual->label);

      maisX+=largura+10;
    }

    if (filhosDraw != NULL) {
     	GLint	viewport[4];
      glGetIntegerv(GL_VIEWPORT, viewport);

      GUI_setView(viewport,x,y,w,h);

        GUI_Draw(5,altAba,filhosDraw);

      GUI_recuperarView(viewport);
    }

    componenteAtual=tempComponet;
  }
}

void Aba_adicionar(int id, ListaDupla *elementos, char *texto, ...) {
  char mesg[256];
  int tamanho;
  int largura;
  va_list ap;

  if (texto==NULL) return;

  va_start( ap, texto );
  vsprintf( mesg, texto, ap );
  va_end( ap );

  if (!GUI_BuscaElem(id,ABA)) return;

  largura=larguraTexto(fontGUI,"%s",mesg);
  tamanho=strlen(mesg);

  Lista *listElementos=(Lista *) componenteAtual->aux;

  struct listaAbas *abaAtual=(struct listaAbas *) lista_acao('n',&listElementos,++componenteAtual->quantidade,NAO_MUDAR_ID | ADD_CERTO,sizeof(struct componenteItem));

  abaAtual->largura=largura;
  abaAtual->label=(char *) calloc(tamanho+1,sizeof(char));
  abaAtual->filhos=elementos;
  if (mesg[0] != '\0') strncpy(abaAtual->label,mesg,tamanho);

  componenteAtual->aux=(void *) listElementos;
}

void Oculto(char oq, int id, int opt, int opt2, int opt3, void *aux) {
  if (oq=='n') {
    Componente_Acao(id,'n');
    componenteAtual->id=id;
    componenteAtual->tipo=OCULTO;
    componenteAtual->label=NULL;

    componenteAtual->funcao=NULL;
    componenteAtual->opt=opt;
    componenteAtual->opt2=opt3;
    componenteAtual->opt3=opt2;

    componenteAtual->ativo=GUI_INATIVO;

    componenteAtual->aux=aux;

    componenteAtual->larguraLenMax=-1;
  }
}

void GUI_filhos(char oq, ListaDupla **elementos) {
  if (oq == 'i') {
    *elementos=NULL;
    GUI_pilha('a');
  }
  else if (oq == 'f') {
    *elementos=prim_GUI;
    GUI_pilha('r');
  }
}

static int GUI_eventoFilhos(int id, SDL_Event *event, int guiX, int guiY) {
  if (!GUI_BuscaElem(id,0)) return 0;
  if ((componenteAtual->tipo != JANELA) && (componenteAtual->tipo != ABA) && (componenteAtual->tipo != GRUPO) && (componenteAtual->tipo != GROUPBOX))
    return 0;

  int ocorreu=0;
  int posX=componenteAtual->x;
  int posY=componenteAtual->y;
  ListaDupla **primComp=NULL;
  paiAnt=prim_GUI;

  if (componenteAtual->tipo == ABA) {
    Lista *listElementos=(Lista *) componenteAtual->aux;
    struct listaAbas *abaAtual=(struct listaAbas *) lista_acao('s',&listElementos,componenteAtual->cursor,NAO_MUDAR_ID | ADD_CERTO,sizeof(struct componenteItem));
    if (abaAtual == NULL) return 0;

    primComp=&abaAtual->filhos;
    posX+=5;
    posY+=27;
  }
  else if (componenteAtual->tipo == JANELA) {
    janelaAnt=prim_GUI;
    idJanelaAtual=id;
    primComp=(ListaDupla **) &componenteAtual->aux;
    posY+=15;
  }
  else if (componenteAtual->tipo == GRUPO)
    primComp=(ListaDupla **) &componenteAtual->aux;
  else if (componenteAtual->tipo == GROUPBOX) {
    primComp=(ListaDupla **) &componenteAtual->aux;
    posX+=5;
    posY+=5;
  }

  GUI_pilha('a');
    prim_GUI=*primComp;
    ocorreu=GUI_Evento(event, posX+guiX, posY+guiY,'f');
    *primComp=prim_GUI;
  GUI_pilha('r');

  return ocorreu;
}

void GUI_Iniciar() {
  pilha_GUI=cria_pilha(30);
}

void GUI_Depois() {
  if ((contapress<=SDL_GetTicks()/100) && (contapress!=0)) {
    if (guiElementoAtivo != NULL) {
      componenteAtual=guiElementoAtivo;

      if (componenteAtual->tipo == EDITBOX) {
        char *label=componenteAtual->label;
        int *cursorPosicao=&componenteAtual->cursor;

        if (keystate[SDLK_LEFT]) {
          if (*cursorPosicao>0)
           (*cursorPosicao)--;
        }
        else if (keystate[SDLK_RIGHT]) {
          if (*cursorPosicao<strlen(label))
            (*cursorPosicao)++;
        }
        else if (keystate[SDLK_BACKSPACE]) {
          if ((strlen(label)) && (*cursorPosicao>0)) {
            if (*cursorPosicao==strlen(label)) {
              label[strlen(label)-1]='\0';
              (*cursorPosicao)--;
            }
            else {
              int temeamoa;
              for (temeamoa=*cursorPosicao; label[temeamoa]!='\0' ;temeamoa++)
                label[temeamoa-1]=label[temeamoa];

              label[temeamoa-1]='\0';
              (*cursorPosicao)--;
            }
          }
        }
        else if (keystate[SDLK_DELETE]) {
          if (*cursorPosicao<strlen(label)) {
            int temeamoa;
            for (temeamoa=*cursorPosicao+1; label[temeamoa]!='\0' ;temeamoa++)
              label[temeamoa-1]=label[temeamoa];
            label[temeamoa-1]='\0';
          }
        }
      }
    }
  }
}

static void Draw_Componente(int x,int y) {
  if (componenteAtual->tipo == EDITBOX)
    EditBox('d',componenteAtual->label, componenteAtual->id, componenteAtual->x+x, componenteAtual->y+y, componenteAtual->w, componenteAtual->ativo, componenteAtual->opt, componenteAtual->funcao);
  else if (componenteAtual->tipo == BOTAO)
    Botao('d', componenteAtual->label, componenteAtual->id, componenteAtual->x+x, componenteAtual->y+y, componenteAtual->w, componenteAtual->ativo, componenteAtual->funcao);
  else if (componenteAtual->tipo == LISTBOX)
    ListBox('d', componenteAtual->id, componenteAtual->x+x, componenteAtual->y+y, componenteAtual->w, componenteAtual->h, componenteAtual->ativo, componenteAtual->opt, componenteAtual->funcao);
  else if (componenteAtual->tipo == SCROLLBAR)
    ScrollBar('d', componenteAtual->id, componenteAtual->x+x, componenteAtual->y+y, componenteAtual->opt2, componenteAtual->quantidade, componenteAtual->ativo, componenteAtual->opt, componenteAtual->funcao);
  else if (componenteAtual->tipo == CHECKBOX)
    CheckBox('d', componenteAtual->label, componenteAtual->id, componenteAtual->x+x, componenteAtual->y+y, componenteAtual->opt, componenteAtual->ativo, componenteAtual->funcao);
  else if (componenteAtual->tipo == RADIOBUTTON)
    RadioButton('d', componenteAtual->label, componenteAtual->id, componenteAtual->opt2 , componenteAtual->x+x, componenteAtual->y+y, componenteAtual->ativo, componenteAtual->funcao);
  else if (componenteAtual->tipo == GROUPBOX)
    GroupBox('d', componenteAtual->label, (ListaDupla *) componenteAtual->aux, componenteAtual->id, componenteAtual->x+x, componenteAtual->y+y, componenteAtual->w, componenteAtual->h, componenteAtual->ativo, componenteAtual->funcao);
  else if (componenteAtual->tipo == PROGRESSBAR)
    ProgressBar('d', componenteAtual->id, componenteAtual->x+x, componenteAtual->y+y, componenteAtual->w, componenteAtual->opt, componenteAtual->opt2, componenteAtual->ativo, componenteAtual->funcao);
  else if (componenteAtual->tipo == COMBOBOX)
    ComboBox('d', componenteAtual->id, componenteAtual->x+x, componenteAtual->y+y, componenteAtual->w, componenteAtual->ativo, componenteAtual->opt, componenteAtual->funcao);
  else if (componenteAtual->tipo == TEXTO)
    Texto('d', componenteAtual->label, componenteAtual->id, componenteAtual->x+x, componenteAtual->y+y, componenteAtual->opt2, componenteAtual->ativo, componenteAtual->opt, componenteAtual->funcao);
  else if (componenteAtual->tipo == IMAGEM)
    Imagem('d', componenteAtual->id, (Textura *) componenteAtual->aux, componenteAtual->x+x, componenteAtual->y+y, componenteAtual->w, componenteAtual->h, componenteAtual->opt2, componenteAtual->opt3, componenteAtual->ativo, componenteAtual->opt, componenteAtual->funcao);
  else if (componenteAtual->tipo == QUADRADO)
    Quadrado('d', componenteAtual->id, componenteAtual->x+x, componenteAtual->y+y, componenteAtual->w, componenteAtual->h, componenteAtual->ativo, componenteAtual->opt, componenteAtual->funcao);
  else if (componenteAtual->tipo == FUNCAODESENHO)
    FuncaoDesenho('d', componenteAtual->id, componenteAtual->aux, componenteAtual->x+x, componenteAtual->y+y, componenteAtual->w, componenteAtual->h, componenteAtual->ativo, componenteAtual->opt, componenteAtual->funcao);
  else if (componenteAtual->tipo == JANELA)
    Janela('d', componenteAtual->label, (ListaDupla *) componenteAtual->aux,componenteAtual->id, componenteAtual->x+x, componenteAtual->y+y, componenteAtual->w, componenteAtual->h, componenteAtual->ativo, componenteAtual->opt, componenteAtual->funcao);
  else if (componenteAtual->tipo == GRUPO)
    Grupo('d', (ListaDupla *) componenteAtual->aux,componenteAtual->id, componenteAtual->x+x, componenteAtual->y+y, componenteAtual->w, componenteAtual->h, componenteAtual->ativo, componenteAtual->opt, componenteAtual->funcao);
  else if (componenteAtual->tipo == ABA)
    Aba('d', componenteAtual->id, componenteAtual->x+x, componenteAtual->y+y, componenteAtual->w, componenteAtual->h, componenteAtual->ativo, componenteAtual->opt, componenteAtual->funcao);
}

void GUI_Draw(int x, int y, ListaDupla *primElemento) {
  GUI_pilha('a');

  prim_GUI=primElemento;

  forListDupla (struct componentes *, componenteTmp, primElemento) {
    componenteAtual=componenteTmp;

    if (componenteAtual->ativo==GUI_ATIVO)
      Draw_Componente(x,y);
  }

  GUI_pilha('r');
}

static void GUI_SelecionarProx() {
  struct componentes *novoSelect=NULL;
  struct componentes *primEdit=NULL;
  int achou=0;

  forListDupla (struct componentes *, componenteTmp, prim_GUI) {
    componenteAtual=componenteTmp;

    if (componenteAtual->tipo == EDITBOX) {
      if (!primEdit) primEdit=componenteAtual;
      if (guiElementoAtivo == componenteAtual) achou=1;
      else if (achou) {
        novoSelect=componenteAtual;
        break;
      }
    }
    /*else if (componenteAtual->tipo == JANELA) {
      ListaDupla *primComp=(ListaDupla *) componenteAtual->aux;

      GUI_pilha('a');
        prim_GUI=primComp;
        GUI_SelecionarProx();
      GUI_pilha('r');
    }*/
  }

  guiElementoAtivo=(novoSelect==NULL)?primEdit:novoSelect;
}

char *GUI_getLabel(int id) {
  if (!GUI_BuscaElem(id,0)) return NULL;
  return componenteAtual->label;
}

int GUI_getTamanho(int id, char qual) {
  if (GUI_BuscaElem(id,0)) {
    if (qual == 'w')
      return componenteAtual->w;

    if (qual == 'h')
      return componenteAtual->h;
  }

  return 0;
}

void GUI_setLabel(int id, char *msg, ...) {
  if (GUI_BuscaElem(id,0)) {
    if (componenteAtual->larguraLenMax == -1) return;
    char label[256];
    va_list ap;

    if (msg==NULL) return;

    va_start( ap, msg );
    vsprintf( label, msg, ap );
    va_end( ap );

    int tamanho=strlen(label);

    if (componenteAtual->tipo == EDITBOX)
      componenteAtual->cursor=(tamanho > componenteAtual->larguraLenMax)? componenteAtual->larguraLenMax:tamanho;
    else if (componenteAtual->tipo == COMBOBOX)
      componenteAtual->opt2=0;
    else if (tamanho > componenteAtual->larguraLenMax) {
      if (componenteAtual->label != NULL)
        free(componenteAtual->label);

      componenteAtual->label=(char *) calloc(tamanho+1,sizeof(char));
      strncpy(componenteAtual->label,label,tamanho);

      componenteAtual->larguraLenMax=tamanho;
    }

    strncpy(componenteAtual->label,label,componenteAtual->larguraLenMax);
  }
}

void GUI_setAtivo(int id, int ativo) {
  if (GUI_BuscaElem(id,0))
    componenteAtual->ativo=ativo;
}

int GUI_isAtivo(int id) {
  if (GUI_BuscaElem(id,0))
    return componenteAtual->ativo;

  return 0;
}

void GUI_setPosicao(int id, int x, int y) {
  if (GUI_BuscaElem(id,0)) {
    componenteAtual->x=x;
    componenteAtual->y=y;
  }
}

void GUI_setTamanho(int id, int w, int h) {
  if (!GUI_BuscaElem(id,0)) return;

  componenteAtual->w=w;
  componenteAtual->h=h;
}

static void GUI_ChamarFuncao(enum TipoEvento tipoEvento, SDL_Event *event,int guiX, int guiY) {
  if (!componenteAtual->funcao) return;
  GUIParms parm;

  parm.id=componenteAtual->id;
  parm.x=mousemovidox-(componenteAtual->x+guiX);
  parm.y=mousemovidoy-(componenteAtual->y+guiY);

  parm.acao=tipoEvento;
  parm.sym=event->key.keysym.sym;
  parm.dados=componenteAtual;

  int idAnt=componenteAtual->id;
  (*componenteAtual->funcao)(&parm);

  GUI_BuscaElem(idAnt,0);
}

int GUI_Evento(SDL_Event *event, int guiX, int guiY, char tipo) {
  if (tipo == 'p') {
    paiAnt=NULL;
    janelaAnt=NULL;
    idJanelaAtual=-1;
  }

  int ocorreu=0;
  ListaDupla *percorreLista;
  if (event->type == SDL_MOUSEMOTION) {
    percorreLista=prim_GUI;
    do {
      if (percorreLista == NULL) break;
      else percorreLista=percorreLista->ant;

      componenteAtual=(struct componentes *) percorreLista->d;

      if (componenteAtual->ativo == GUI_INATIVO) continue;

      if (componenteAtual->tipo == LISTBOX) {
        ListboxVarAux *variaveisAux=(ListboxVarAux *) componenteAtual->aux;
        ScrollElmt *scroll=&variaveisAux->scroll;

        if (scroll->elemtClick == 3)
          Scroll_BarraRolar(componenteAtual->id,mousemovidox-guiX,mousemovidoy-guiY,componenteAtual->h,SCROLLBAR_VERTICAL,scroll);
      }
      if (componenteAtual->tipo == SCROLLBAR) {
        ScrollElmt *scroll=(ScrollElmt *) componenteAtual->aux;

        if (scroll->elemtClick == 3)
          Scroll_BarraRolar(componenteAtual->id,mousemovidox-guiX,mousemovidoy-guiY,componenteAtual->opt2,componenteAtual->opt3,scroll);
      }
      else if (componenteAtual->tipo == JANELA) {
        if (componenteAtual->cursor) {
          componenteAtual->x+=event->motion.xrel;
          componenteAtual->y+=event->motion.yrel;
        }
      }

      ocorreu+=GUI_eventoFilhos(componenteAtual->id,event,guiX,guiY);

      if (mouseverondeclia(componenteAtual->x+guiX,componenteAtual->x+guiX+componenteAtual->w,componenteAtual->y+guiY,componenteAtual->y+guiY+componenteAtual->h)) {
        if (componenteAtual->tipo == COMBOBOX) {
          int posYMouseItem=mousemovidoy-guiY-(componenteAtual->y+19+2);

          if ((posYMouseItem>0) && (componenteAtual->opt3)) {
            componenteAtual->cursor=posYMouseItem/16+1;

            if (componenteAtual->cursor > componenteAtual->quantidade)
              componenteAtual->cursor=componenteAtual->quantidade;
          }
        }

        GUI_ChamarFuncao(MOUSE_MOVE,event,guiX,guiY);
      }
    } while (percorreLista!=prim_GUI && !ocorreu);
  }
  else if (event->type == SDL_KEYDOWN) {
    percorreLista=prim_GUI;
    do {
      if (percorreLista == NULL) break;
      else percorreLista=percorreLista->ant;

      componenteAtual=(struct componentes *) percorreLista->d;

      ocorreu+=GUI_eventoFilhos(componenteAtual->id,event,guiX,guiY);

      if (((guiElementoAtivo != componenteAtual) && (componenteAtual->tipo != FUNCAODESENHO)) || (componenteAtual->ativo == GUI_INATIVO)) continue;

      if (componenteAtual->tipo == EDITBOX) {
        ocorreu++;

        char *label=componenteAtual->label;
        int *cursorPosicao=&componenteAtual->cursor;
        int larguraLenMax=componenteAtual->larguraLenMax;

        if ((event->key.keysym.sym == SDLK_LCTRL) || (event->key.keysym.sym == SDLK_LALT))
          ocorreu--;
        else if (event->key.keysym.sym == SDLK_UP) {
          if (componenteAtual->opt & EDITBOX_HISTORICO) {
            char **antTexto=(char **) componenteAtual->aux;
            if ((componenteAtual->opt3<5) && (antTexto[componenteAtual->opt3][0]!='\0')) {
              GUI_setLabel(componenteAtual->id,antTexto[componenteAtual->opt3]);
              (componenteAtual->opt3)++;
            }
          }
        }
        else if (event->key.keysym.sym == SDLK_DOWN) {
          if (componenteAtual->opt & EDITBOX_HISTORICO) {
            (componenteAtual->opt3)--;
            if (componenteAtual->opt3<=0) {
              componenteAtual->opt3=0;
              GUI_setLabel(componenteAtual->id,"\0");
            }
            else {
              char **antTexto=(char **) componenteAtual->aux;
              GUI_setLabel(componenteAtual->id,antTexto[componenteAtual->opt3-1]);
            }
          }
        }
        else if (event->key.keysym.sym == SDLK_LEFT) {
          if (*cursorPosicao>0)
            (*cursorPosicao)--;
          contapress=SDL_GetTicks()/100+5;
        }
        else if (event->key.keysym.sym == SDLK_RIGHT) {
          if (*cursorPosicao<strlen(label))
            (*cursorPosicao)++;
          contapress=SDL_GetTicks()/100+5;
        }
        else if (event->key.keysym.sym == SDLK_HOME) { *cursorPosicao=0; }
        else if (event->key.keysym.sym == SDLK_END) { *cursorPosicao=strlen(label); }
        else if (event->key.keysym.sym == SDLK_TAB) { GUI_SelecionarProx();}
        else if (event->key.keysym.sym==SDLK_BACKSPACE) {
          if ((strlen(label)) && (*cursorPosicao>0)) {
            contapress=SDL_GetTicks()/100+5;
            if (*cursorPosicao==strlen(label)) {
              label[strlen(label)-1]='\0';
              (*cursorPosicao)--;
            }
            else {
              int temeamoa;
              for (temeamoa=*cursorPosicao; label[temeamoa]!='\0' ;temeamoa++)
                label[temeamoa-1]=label[temeamoa];

              label[temeamoa-1]='\0';
              (*cursorPosicao)--;
            }
          }
        }
        else if (event->key.keysym.sym==SDLK_DELETE) {
          if (*cursorPosicao<strlen(label)) {
            contapress=SDL_GetTicks()/100+5;

            int temeamoa;
            for (temeamoa=*cursorPosicao+1; label[temeamoa]!='\0' ;temeamoa++)
              label[temeamoa-1]=label[temeamoa];
            label[temeamoa-1]='\0';
          }
        }
        else if ((event->key.keysym.sym != SDLK_RETURN) && (event->key.keysym.sym != SDLK_KP_ENTER)) {
          char caracter=(char)event->key.keysym.unicode;
          if ((strlen(label) < larguraLenMax) && (caracter!=0) && (caracter!='\t') && (caracter!='\n')) {
            if ((componenteAtual->opt&EDITBOX_NUMERICO) && ((caracter > '9') || (caracter < '0')))
              continue;

            if (!((caracter==' ') && (((*cursorPosicao>0) && (label[*cursorPosicao-1]==' ')) || (label[*cursorPosicao]==' ')))) {
              if (*cursorPosicao==strlen(label)) {
                label[strlen(label)+1]='\0';
                label[strlen(label)]=caracter;
              }
              else {
                int temeamoa;
                for (temeamoa=strlen(label); temeamoa>=*cursorPosicao ;temeamoa--)
                  label[temeamoa+1]=label[temeamoa];
                label[*cursorPosicao]=caracter;
              }
              (*cursorPosicao)++;
            }
          }
        }
      }

      GUI_ChamarFuncao(TECLA_DOWN,event,guiX,guiY);

    } while (percorreLista!=prim_GUI && !ocorreu);
  }
  else if (event->type == SDL_KEYUP) {
    if ((event->key.keysym.sym==SDLK_BACKSPACE) || (event->key.keysym.sym==SDLK_DELETE) || (event->key.keysym.sym == SDLK_LEFT) || (event->key.keysym.sym == SDLK_RIGHT))
      contapress=0;

    percorreLista=prim_GUI;
    do {
      if (percorreLista == NULL) break;
      else percorreLista=percorreLista->ant;

      componenteAtual=(struct componentes *) percorreLista->d;

      ocorreu+=GUI_eventoFilhos(componenteAtual->id,event,guiX,guiY);

      if ((guiElementoAtivo != componenteAtual) || (componenteAtual->ativo == GUI_INATIVO)) continue;

      GUI_ChamarFuncao(TECLA_UP,event,guiX,guiY);

    } while (percorreLista!=prim_GUI && !ocorreu);
  }
  else if ((event->type == SDL_MOUSEBUTTONDOWN) && ( event->button.button == SDL_BUTTON_LEFT )) {
    percorreLista=prim_GUI;
    do {
      if (percorreLista == NULL) break;
      else percorreLista=percorreLista->ant;

      componenteAtual=(struct componentes *) percorreLista->d;

      if (componenteAtual->ativo == GUI_INATIVO) continue;

      if (mouseverondeclia(componenteAtual->x+guiX,componenteAtual->x+guiX+componenteAtual->w,componenteAtual->y+guiY,componenteAtual->y+guiY+componenteAtual->h)) {
        ocorreu++;

        if (componenteAtual->tipo == EDITBOX)
          guiElementoAtivo=componenteAtual;
        else if (componenteAtual->tipo == BOTAO)
          componenteAtual->opt=1;
        else if (componenteAtual->tipo == LISTBOX) {
          int posicaoBotaox=componenteAtual->x+componenteAtual->w-SCROLL_LISTBOX;
          ListboxVarAux *variaveisAux=(ListboxVarAux *) componenteAtual->aux;

          if (mousemovidox>=posicaoBotaox+guiX)
            Scroll_evento(posicaoBotaox, componenteAtual->y, guiX, guiY, componenteAtual->h, SCROLLBAR_VERTICAL, 1,&variaveisAux->scroll);
        }
        else if (componenteAtual->tipo == SCROLLBAR)
          Scroll_evento(componenteAtual->x, componenteAtual->y, guiX, guiY, componenteAtual->opt2, componenteAtual->opt3, 1,(ScrollElmt *) componenteAtual->aux);
        else if (componenteAtual->tipo == CHECKBOX)
          CheckBox_setSelect(componenteAtual->id,!CheckBox_isSelect(componenteAtual->id));
        else if (componenteAtual->tipo == RADIOBUTTON)
          RadioButton_Select(componenteAtual->id);
        else if (componenteAtual->tipo == COMBOBOX) {
          if (componenteAtual->opt3) {
            componenteAtual->h=19;
            ComboBox_Seleciona(componenteAtual->id,componenteAtual->cursor);
          }
          else {
            componenteAtual->cursor=componenteAtual->opt2;
            componenteAtual->opt3=1;
            componenteAtual->h=19+componenteAtual->quantidade*16;
          }
        }
        else if (componenteAtual->tipo == JANELA) {
          Componente_Acao(componenteAtual->id,'u');
          ocorreu=0;

          if (!GUI_eventoFilhos(componenteAtual->id,event,guiX,guiY)) {
            if ((componenteAtual->opt&JANELA_MOVEALL) || (mouseverondeclia(componenteAtual->x+guiX,componenteAtual->x+guiX+componenteAtual->w,componenteAtual->y+guiY,componenteAtual->y+guiY+13))) {
              ocorreu++;

              if ((!(componenteAtual->opt&JANELA_NAOFECHAR)) && (mouseverondeclia(componenteAtual->x+guiX+componenteAtual->w-16,componenteAtual->x+guiX+componenteAtual->w-1,componenteAtual->y+guiY,componenteAtual->y+guiY+10))) {
                ListaDupla *lista=(ListaDupla *) componenteAtual->aux;

                GUI_pilha('a');
                  GUI_libera(&lista);
                GUI_pilha('r');

                Componente_Acao(componenteAtual->id,'d');
                continue;
              }

              componenteAtual->cursor=1;
            }
          }

          if (!ocorreu) ocorreu=1;
        }
        else if ((componenteAtual->tipo == GRUPO) || (componenteAtual->tipo == GROUPBOX)) {
            ocorreu=0;

            ocorreu+=GUI_eventoFilhos(componenteAtual->id,event,guiX,guiY);
        }
        else if (componenteAtual->tipo == ABA) {
          if (mouseverondeclia(componenteAtual->x+guiX,componenteAtual->x+guiX+componenteAtual->w,componenteAtual->y+guiY,componenteAtual->y+guiY+27)) {
            int maisX=0;

            forList (struct listaAbas *, abaAtual, (Lista *) componenteAtual->aux) {
              if (mouseverondeclia(componenteAtual->x+guiX+maisX,componenteAtual->x+guiX+maisX+abaAtual->largura+10,componenteAtual->y+guiY,componenteAtual->y+guiY+27)) {
                componenteAtual->cursor=abaAtual_Id;
                break;
              }

              maisX+=abaAtual->largura+10;
            }
          }
          else {
            ocorreu--;

            ocorreu+=GUI_eventoFilhos(componenteAtual->id,event,guiX,guiY);

            if (!ocorreu) ocorreu=1;
          }
        }

        GUI_ChamarFuncao(MOUSE_DOWN_LEFT,event,guiX,guiY);

      }
    } while (percorreLista!=prim_GUI && !ocorreu);
  }
  else if ((event->type == SDL_MOUSEBUTTONUP) && ( event->button.button == SDL_BUTTON_LEFT )) {
    percorreLista=prim_GUI;
    do {
      if (percorreLista == NULL) break;
      else percorreLista=percorreLista->ant;

      componenteAtual=(struct componentes *) percorreLista->d;

      if (componenteAtual->ativo == GUI_INATIVO) continue;


      if (componenteAtual->tipo == BOTAO)
        componenteAtual->opt=0;
      else if (componenteAtual->tipo == LISTBOX) {
        ListboxVarAux *vA=(ListboxVarAux *) componenteAtual->aux;
        vA->scroll.elemtClick=0;
      }
      else if (componenteAtual->tipo == SCROLLBAR) {
        ScrollElmt *scroll=(ScrollElmt *) componenteAtual->aux;
        scroll->elemtClick=0;
      }
      else if (componenteAtual->tipo == JANELA)
        componenteAtual->cursor=0;

      ocorreu+=GUI_eventoFilhos(componenteAtual->id,event,guiX,guiY);

      if (!ocorreu && mouseverondeclia(componenteAtual->x+guiX,componenteAtual->x+guiX+componenteAtual->w,componenteAtual->y+guiY,componenteAtual->y+guiY+componenteAtual->h)) {
        ocorreu++;

        if (componenteAtual->tipo == LISTBOX) {
          int posicaoBotaox=componenteAtual->x+componenteAtual->w-SCROLL_LISTBOX;
          ListboxVarAux *vA=(ListboxVarAux *) componenteAtual->aux;

          if (mousemovidox>=posicaoBotaox+guiX)
            Scroll_evento(posicaoBotaox, componenteAtual->y, guiX, guiY, componenteAtual->h, SCROLLBAR_VERTICAL, 2,&vA->scroll);
        }
        else if (componenteAtual->tipo == SCROLLBAR)
          Scroll_evento(componenteAtual->x, componenteAtual->y, guiX, guiY, componenteAtual->opt2, componenteAtual->opt3, 2,(ScrollElmt *) componenteAtual->aux);

        GUI_ChamarFuncao(MOUSE_UP_LEFT,event,guiX,guiY);

      }
    } while (percorreLista!=prim_GUI && !ocorreu);
  }
  else if ((event->type == SDL_MOUSEBUTTONDOWN) && ( event->button.button == SDL_BUTTON_RIGHT )) {
    percorreLista=prim_GUI;
    do {
      if (percorreLista == NULL) break;
      else percorreLista=percorreLista->ant;

      componenteAtual=(struct componentes *) percorreLista->d;

      if (componenteAtual->ativo == GUI_INATIVO) continue;

      ocorreu+=GUI_eventoFilhos(componenteAtual->id,event,guiX,guiY);

      if (!ocorreu && mouseverondeclia(componenteAtual->x+guiX,componenteAtual->x+guiX+componenteAtual->w,componenteAtual->y+guiY,componenteAtual->y+guiY+componenteAtual->h)) {
        ocorreu++;

        GUI_ChamarFuncao(MOUSE_DOWN_RIGHT,event,guiX,guiY);

      }
    } while (percorreLista!=prim_GUI);
  }
  else if ((event->type == SDL_MOUSEBUTTONUP) && ( event->button.button == SDL_BUTTON_RIGHT )) {
    percorreLista=prim_GUI;
    do {
      if (percorreLista == NULL) break;
      else percorreLista=percorreLista->ant;

      componenteAtual=(struct componentes *) percorreLista->d;

      if (componenteAtual->ativo == GUI_INATIVO) continue;

      ocorreu+=GUI_eventoFilhos(componenteAtual->id,event,guiX,guiY);

      if (!ocorreu && mouseverondeclia(componenteAtual->x+guiX,componenteAtual->x+guiX+componenteAtual->w,componenteAtual->y+guiY,componenteAtual->y+guiY+componenteAtual->h)) {
        ocorreu++;

        GUI_ChamarFuncao(MOUSE_UP_RIGHT,event,guiX,guiY);

      }
    } while (percorreLista!=prim_GUI);
  }
  return ocorreu;
}
