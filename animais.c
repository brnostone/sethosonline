#include <stdio.h>

#include "Header/estruturas.h"
#include "Header/util.h"
#include "Header/global.h"
#include "Header/lightmap.h"
#include "Header/mapas.h"
#include "Header/animais.h"

struct animal *animalatual=NULL;
Lista *primanimais=NULL;
int numanimais=0;

int animalacao(int id,char acao) {
  static int opcao=MUDAR_ID;

  if (acao=='n') {
    animalatual=(struct animal *) lista_acao('n',&primanimais,id,opcao,sizeof(struct animal));
    numanimais++;
  }
  else if (acao=='d') {
    animalatual=(struct animal *) lista_acao('d',&primanimais,id,opcao,0);
    if (animalatual) numanimais--;
  }
  else if (acao=='s') {
    animalatual=(struct animal *) lista_acao('s',&primanimais,id,opcao,numanimais);
    return (!animalatual)?0:1;
  }
  return 0;
}

void Criar_Animal(int posx, int posy, unsigned char tipo, unsigned char lado, unsigned char acao) {
  animalacao(numanimais+1,'n');

  animalatual->x=posx;
  animalatual->y=posy;
  animalatual->tipo=tipo;
  animalatual->imagem=0;
  animalatual->lado=lado;
  animalatual->acao=acao;
  animalatual->ativo=1;
}

int Info_Animal(int tipo,char oq) {
  int retorno=0;
  if (tipo == 1) {
    if (oq == 'w') retorno=64;
    else if (oq == 'h') retorno=64;
    else if (oq == 'x') retorno=0;
    else if (oq == 'y') retorno=64;
    else if (oq == 'i') retorno=9;
    else if (oq == 'v') retorno=2;
  }
  else if (tipo >= 2) {
    if (oq == 'w') retorno=32;
    else if (oq == 'h') retorno=32;
    else if (oq == 'x') retorno=0;
    else if (oq == 'y') retorno=200;
    else if (oq == 'i') retorno=7;
    else if (oq == 'v') retorno=3;
  }
  return retorno;
}

void Draw_Animal(int id) {
  if (animalacao(id,'s')) {
    int tipo=animalatual->tipo;
    int w=Info_Animal(tipo,'w');
    int h=Info_Animal(tipo,'h');

    animalatual->ativo=1;

    DrawImg_LightMap(animais[tipo-1], animalatual->x-xpos, animalatual->y-ypos,w,h,(w+1)*animalatual->imagem+1,(h+1)*animalatual->lado+1);
  }
}

void IA_Animal() {
  forList (struct animal *, animalTmp, primanimais) {
    animalatual=animalTmp;

    animalatual->x+=Info_Animal(animalatual->tipo,'v');

    animalatual->imagem++;
    if (animalatual->imagem>=Info_Animal(animalatual->tipo,'i')) animalatual->imagem=0;
  }
}
