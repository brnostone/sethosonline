#include "Header/util.h"
#include "Header/GUI.h"
#include "Header/menus.h"
#include "Header/personagem.h"
#include "Header/guiitens.h"
#include "Header/menusjogo.h"
#include "Header/util.h"
#include "Header/fonte.h"
#include "Header/global.h"
#include "Header/pesca.h"
#include "Header/msgs.h"

static void Msgs_interAdicionar(int tipo) {
  GUI_AbrirPai();
    Msgs_adicionar(tipo,NULL);
  GUI_FecharPai();
}

static void Msgs_clickButton(GUIParms *parm) {
  if (parm->acao == MOUSE_UP_LEFT) {
    if (!GUI_BuscaElem(1,OCULTO)) return;

    int tipo=componenteAtual->opt;
    int botao=parm->id-1;
    int fechar=1;

    switch (tipo) {
      case 1: {
        if (botao == 1)
          Msgs_interAdicionar(2);
        else {
          menus.ativo=1;
          menus.qual=2;
        }

        break;
      }
      case 2: {
        if (botao == 1) {
          if (meusstatsua.dinheiro < 100)
            Msgs_interAdicionar(3);
          else {
            if (1==1) {
              meusstatsua.dinheiro-=100;
              Msgs_interAdicionar(10);
            }
            else {
              /*nao possue os itens*/
              Msgs_interAdicionar(5);
            }
          }
        }
        else if (botao == 2) {
          memset(vendetrocatemp, 0, sizeof(vendetrocatemp));
          memset(itemvende_temp, 0, sizeof(itemvende_temp));
          numeroitem[1]=0;

          colocaritem(0,0,16,1,1,2);
          menus.ativo=0; mostrarmenu=1; inventarioon=1; charmenuon=0;
        }

        break;
      }
      case 5: {
        if (botao == 1) {
          memset(vendetrocatemp, 0, sizeof(vendetrocatemp));
          memset(itemvende_temp, 0, sizeof(itemvende_temp));
          numeroitem[1]=0;

          colocaritem(0,0,16,1,1,2);
          menus.ativo=0; mostrarmenu=1; inventarioon=1; charmenuon=0;
        }

        break;
      }
      case 10: {
        if (botao == 1)
          Msgs_interAdicionar(11);

        break;
      }
      case 11: {
        if (botao == 1)
          Msgs_interAdicionar(10);
        else if (botao == 2)
          Msgs_interAdicionar(12);

        break;
      }
      case 12: {
        if (botao == 1)
          Msgs_interAdicionar(11);
        else if (botao == 2)
          Msgs_interAdicionar(13);

        break;
      }
      case 13: {
        if (botao == 1)
          Msgs_interAdicionar(12);
        else if (botao == 2)
          Msgs_interAdicionar(14);

        break;
      }
      case 14: {
        if (botao == 1)
          Msgs_interAdicionar(13);
        else if (botao == 2)
          Msgs_interAdicionar(15);

        break;
      }
      case 15: {
        if (botao == 1)
          Msgs_interAdicionar(14);
        else if (botao == 3)
          tutorialpesca=1;

        break;
      }
    }

    if (fechar)
      Janela_fechar();
  }
}

static ListString Msgs_info(int tipo, char oq, char *args) {
  char *texto=NULL;
  ListString retono=NULL;

  switch (tipo) {
    case 1:
      if (oq == 't')
        texto=String_Param("Ol�, voc� quer aprender a pescar? ",args);
      else if (oq == 'b') {
        ListString_adiciona(&retono,"Sim");
        ListString_adiciona(&retono,"N�o");
      }

      break;
    case 2:
      if (oq == 't')
        texto=String_Param("   Hmm! A aula ir� custar 100 Golds, para realizar a aula voc� deve ter uma vara de pesca e iscas. \n \n\
Obs.: Caso voc� n�o tiver os itens pedidos clique em Comprar. ",args);
      else if (oq == 'b') {
        ListString_adiciona(&retono,"Come�ar");
        ListString_adiciona(&retono,"Comprar");
        ListString_adiciona(&retono,"Cancelar");
      }

      break;

    case 3:
      if (oq == 't')
        texto=String_Param("<1> ",args);
      else if (oq == 'b')
        ListString_adiciona(&retono,"OK");

      break;

    case 5:
      if (oq == 't')
        texto=String_Param("Voc� n�o possue os itens pedidos para pescar, deseja compra-los? ",args);
      else if (oq == 'b') {
        ListString_adiciona(&retono,"Sim");
        ListString_adiciona(&retono,"N�o");
      }

      break;

    case 9:
      if (oq == 't')
        texto=String_Param("Voc� pescou um peixe de <1> Kilos. ",args);
      else if (oq == 'b')
        ListString_adiciona(&retono,"OK");

      break;

    case 10:
      if (oq == 't')
        texto=String_Param("Para pescar voc� tem que seguir os passos: \n \n\
1� Equipar a vara de pesca. \n\
2� Estar na beirada do rio. \n\
3� Clicar na �gua. \n\
4� Esperar o peixe fisgar a isca. \n\
5� Puxar a linha, com cuidado para n�o arrebentar a linha e para n�o deixar o peixe escapar. \n \n\
Obs.: Para puxar � so apertar a tecla \'p\' ",args);
      else if (oq == 'b')
        ListString_adiciona(&retono,"Proximo");

      break;

    case 11:
      if (oq == 't')
        texto=String_Param("Quando o peixe fisgar a isca voc� notar� que a b�ia ir� se mexer e est� barra aparecera. \n \n \n \n\
O cursor indica a tens�o na linha. ",args);
      else if (oq == 'b') {
        ListString_adiciona(&retono,"Anterior");
        ListString_adiciona(&retono,"Proximo");
      }

      break;

    case 12:
      if (oq == 't')
        texto=String_Param("Se o cursor estiver no extremo da esquerda, significa que o peixe ir� escapar. \n \n \n \n\
Solu��o: puxar apertando \"p\". ",args);
      else if (oq == 'b') {
        ListString_adiciona(&retono,"Anterior");
        ListString_adiciona(&retono,"Proximo");
      }

      break;

    case 13:
      if (oq == 't')
        texto=String_Param("Se o cursor estiver no extremo da direita, significa que a linha est� com uma tens�o muito alta, e ela ira arrebentar. \n \n \n \n\
Solu��o: esperar o peixe se \"acalmar\". ",args);
      else if (oq == 'b') {
        ListString_adiciona(&retono,"Anterior");
        ListString_adiciona(&retono,"Proximo");
      }

      break;

    case 14:
      if (oq == 't')
        texto=String_Param("Dicas: \n\
1� Os peixes maiores est�o no fundo. \n\
2� O trapiche � um bom lugar para pescar pois � mais f�cil pegar peixes grandes. \n\
3� Voc� pode recuperar sua vida comendo peixes. \n\
4� Vender peixes � muito lucrativo. \n\
5� Para conseguir arremessar mais longe compre as varas melhores. ",args);
      else if (oq == 'b') {
        ListString_adiciona(&retono,"Anterior");
        ListString_adiciona(&retono,"Proximo");
      }

      break;

    case 15:
      if (oq == 't')
        texto=String_Param("Agora � hora da aula pratica! \n\
Utilize todo o seu conhecimento adquirido, mas n�o se preocupe que eu irei dar dicas para voc� em tempo real. ",args);
      else if (oq == 'b') {
        ListString_adiciona(&retono,"Anterior");
        ListString_adiciona(&retono,"Fechar");
        ListString_adiciona(&retono,"Iniciar");
      }

      break;

    case 16:
      if (oq == 't')
        texto=String_Param("Parab�ns!! \n\
Voc� conseguiu pegar um peixe, se voc� quiser pode me vender ele, ou com�-lo. ",args);
      else if (oq == 'b')
        ListString_adiciona(&retono,"Fechar");

      break;

    case 17:
      if (oq == 't')
        texto=String_Param("Resultado da opera��o �: \n<1> ",args);
      else if (oq == 'b')
        ListString_adiciona(&retono,"Fechar");

      break;
  }

  if ((oq == 't') && (texto != NULL)) {
    retono=String_quebraTexto(font,250,texto);
    free(texto);
  }

  return retono;
}

static void Msgs_outroAdd(int tipo, int *cont) {
  int h=alturaTexto(font);

  switch (tipo) {
    case 9:
      Imagem('n',100,item2,10,(*cont-10)*h,48,48,0,0,GUI_ATIVO,0,NULL);

      break;

    case 11:
      Imagem('n',100,barrapesca,17,(*cont-13)*h,245,26,0,0,GUI_ATIVO,0,NULL);
      Imagem('n',101,cursorpesca,17+114,(*cont-13)*h-7,16,17,0,0,GUI_ATIVO,0,NULL);

      break;

    case 12:
      Imagem('n',100,barrapesca,17,(*cont-13)*h,245,26,0,0,GUI_ATIVO,0,NULL);
      Imagem('n',101,cursorpesca,17+2,(*cont-13)*h-7,16,17,0,0,GUI_ATIVO,0,NULL);

      break;

    case 13:
      Imagem('n',100,barrapesca,17,(*cont-13)*h,245,26,0,0,GUI_ATIVO,0,NULL);
      Imagem('n',101,cursorpesca,17+227,(*cont-13)*h-7,16,17,0,0,GUI_ATIVO,0,NULL);

      break;
  }
}

void Msgs_adicionar(int tipo, char *parm, ...) {
  int cont=10,h,altura;
  int quantBotoes,pow;
  char texto[256];

  memset(texto,'\0',sizeof(texto));

  if (parm != NULL) {
    va_list ap;

    va_start(ap, parm);
      vsprintf(texto, parm, ap);
    va_end(ap);
  }

  ListaDupla *tmp_GUI;

  h=alturaTexto(font)+1;
  GUI_filhos('i',&tmp_GUI);
    Oculto('n',1,tipo,0,0,NULL);

    ListString textoLista=Msgs_info(tipo,'t',texto);

    forList (char *, msgTexto, textoLista) {
      Texto('n', msgTexto, cont, 15, h*(cont-10),3, GUI_ATIVO, 0, NULL);
      GUI_MudarCor(cont,255,255,255);
      GUI_MudarFonte(cont,font);

      cont++;
    }

    Msgs_outroAdd(tipo,&cont);

    altura=(cont-9)*h;

    cont=2;

    ListString botaoLista=Msgs_info(tipo,'b',NULL);
    quantBotoes=ListString_tamanho(botaoLista);

    pow=280/(quantBotoes+1);

    forList (char *, msgBotao, botaoLista) {
      Botao('n',msgBotao,cont,pow*(cont-1)-27,altura,57,GUI_ATIVO,Msgs_clickButton);
      cont++;
    }

   ListString_limpa(&textoLista);
   ListString_limpa(&botaoLista);
  GUI_filhos('f',&tmp_GUI);

  Janela('n', " ",tmp_GUI, guiIdGeral++, 0, 0, 280, altura+40, GUI_ATIVO, JANELA_CENTRALIZADA, NULL);
}
