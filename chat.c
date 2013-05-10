#include "Header/balao.h"
#include "Header/util.h"
#include "Header/fonte.h"
#include "Header/global.h"
#include "Header/menusjogo.h"
#include "Header/comandos.h"
#include "Header/tela_jogo.h"
#include "Header/chat.h"

void Draw_MsgChat() {
  if (!janechaton) {
    if (!GUI_BuscaElem(4,LISTBOX)) return;
    int contar=0;
    int totalCabe=componenteAtual->quantidade;

    ListboxVarAux *variaveisAux=(ListboxVarAux *) componenteAtual->aux;

    forList (struct componenteItem *, textoAtual, variaveisAux->listElementos) {
      if (-contar >= totalCabe) break;
      int posY=(totalCabe+(--contar))*16;

      int mais=0;
      if (textoAtual->g==0) mais=220;
      if (textoAtual->g==84) mais=120;
      Draw_TextEmo(fontGUI,textoAtual->r+mais,textoAtual->g+mais,textoAtual->b+mais,255,9,((charmenuon)?229:5),5+posY,"%s",textoAtual->texto);
    }
  }
}

void EnviarChat() {
  char *label=GUI_getLabel(1);
  if (!label) return;

  if (label[0]=='/')
    comandos(label);
  else if (label[0]!='\0') {
    ListBox_Adicionar(4,0,0,0,7,"<%s> %s","tronix",label);

    Baloes_SetTexto(label);

    EditBox_SalvaHistorico(1);
  }

  GUI_setLabel(1,"\0");
}

//clica no botao de enviar
int ClickChat(GUIParms *parm) {
  int retorno=0;

  if (parm->acao==4) {
    EnviarChat();
    retorno=1;
  }
  return retorno;
}

int EditChat(GUIParms *parm) {
  int retorno=0;

  if (parm->acao==1) {
    if ((parm->sym == SDLK_RETURN) || (parm->sym == SDLK_KP_ENTER)) {
      EnviarChat();

      Tela_jogo_ChatAtivar();

      retorno=1;
    }
  }

  return retorno;
}
