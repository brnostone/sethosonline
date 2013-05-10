#include "Header/estruturas.h"
#include "Header/util.h"
#include "Header/opengl.h"
#include "Header/global.h"
#include "Header/personagem.h"
#include "Header/mapas.h"
#include "Header/balao.h"

void Draw_Balao(Fonte *fonte, int x, int y,int largura,int alpha, char *msg) {
  ListString listaTextos = String_quebraTexto(fonte, largura, "%s", msg);

  int linhas=ListString_tamanho(listaTextos);
  int w,h;
  int cont=0;

  if (linhas == 1)
    w=larguraTexto(fonte,"%s",ListString_get(&listaTextos,1));
  else
    w=largura;

  h=linhas*alturaTexto(fonte);

  fillRectangle(x,y-h,w+12,h+12,108,126,48,alpha);
  fillRectangle(x+1,y+1-h,w+10,h+10,255,253,213,alpha);

  forList (char *, texto, listaTextos) {
    Draw_TextEmo(fonte,50,50,50,alpha,(alpha>180)?1:0,x+5,y+5+cont*14-h,"%s",texto);

    cont++;
  }

  DrawIMG_RGBA(balao,x,y+11,11,9,0,0,255,255,255,alpha);

  ListString_limpa(&listaTextos);
}

void Draw_Baloes() {
  if (personagem.balao.ativo) {
    if (personagem.balao.timeout<SDL_GetTicks()/100) {
      personagem.balao.alpha-=10;

      if (personagem.balao.alpha<=10) {
        personagem.balao.ativo=0;
        personagem.balao.alpha=0;
      }
    }
    Draw_Balao(fontGUI,personagem.x-xpos+55,personagem.y-ypos,150,personagem.balao.alpha,personagem.balao.msg);
  }
}

void Baloes_SetTexto(char *texto) {
  strncpy(personagem.balao.msg,texto,254);
  strcat(personagem.balao.msg," ");

  personagem.balao.alpha=255;
  personagem.balao.ativo=1;
  personagem.balao.timeout=SDL_GetTicks()/100+50;
}
