#include <stdio.h>
#include <string.h>

#include <SDL/SDL.h>

#include "Header/estruturas.h"
#include "Header/fonte.h"
#include "Header/GUI.h"
#include "Header/util.h"
#include "Header/log.h"

char loginfo[20][256];

int ticjsja;

void logging(int estado, char *gravar, ...) {
  char text2[256];
  va_list ap;

  if (gravar==NULL) return;

  va_start( ap, gravar );
  vsprintf( text2, gravar, ap );
  va_end( ap );

  int tamanho=strlen(text2),percorre;
  if (estado==1) {
    logtemp=0;
    ticjsja=SDL_GetTicks();
    printf("%s",text2);
    for (percorre=tamanho;percorre<50;percorre++)
      putchar(32);
  }
  else if (estado==2) {
    printf("[%s]\n",text2);
    for (percorre=0;percorre<20;percorre++) {
      if (strlen(loginfo[percorre]))
        printf("  * %s\n",loginfo[percorre]);
    }
    memset(loginfo,'\0',sizeof(loginfo));
    printf("  ** Tempo: %.3fseg\n\n",(double)(SDL_GetTicks()-ticjsja)/1000);
  }
  else {
    for (percorre=0;percorre<20;percorre++) {
      if (!strlen(loginfo[percorre])) {
        strcpy(loginfo[percorre],text2);
        percorre=0;
        break;
      }
    }
    if (percorre) strcpy(loginfo[19],"...");
  }
}

void Error(char *msg, enum ErroLevel erLv) {
  if (erLv == ERRO_AVISO) {
    int cont=1;
    int h=alturaTexto(fontGUI)+1;

    ListaDupla *tmp_GUI;
    GUI_filhos('i',&tmp_GUI);
      Lista *textoLista=String_quebraTexto(fontGUI,250,msg);

      forList (char *, msgTexto, textoLista) {
        Texto('n', msgTexto, cont, 15, h*(cont-1),3, GUI_ATIVO, 0, NULL);
        GUI_MudarCor(cont,255,255,255);
        GUI_MudarFonte(cont,fontGUI);

        cont++;
      }

      Botao('n',"OK",cont,110,cont*h,60,GUI_ATIVO,NULL);

      ListString_limpa(&textoLista);
     GUI_filhos('f',&tmp_GUI);

     Janela('n', " ",tmp_GUI, guiIdGeral++, 0, 0, 280, cont*h+40, GUI_ATIVO, JANELA_CENTRALIZADA, NULL);
  }
  else if (erLv == ERRO_FATAL) {
    printf("Erro fatal: %s\n",msg);
    exit(1);
  }
}
