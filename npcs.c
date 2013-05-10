#include "Header/lightmap.h"
#include "Header/pesca.h"
#include "Header/mapas.h"
#include "Header/util.h"
#include "Header/npcs.h"

void Nome_Npcs(char tipo, char *nomeNPC) {
  switch(tipo) {
    case 1: { strcpy(nomeNPC,"Ferreiro"); break; }
    case 2: { strcpy(nomeNPC,"Pescador"); break; }
    case 3: { strcpy(nomeNPC,"Mago"); break; }
    case 4: { strcpy(nomeNPC,"Bau"); break; }
  }
}

int info_npcs(int qual,int oq) {
  int retorno=0;
  if (qual==0) {
    if (oq=='w') retorno=96;
    else if (oq=='h') retorno=96;
    //selecao
    else if (oq=='x') retorno=36;
    else if (oq=='y') retorno=17;
    else if (oq=='l') retorno=65;
    else if (oq=='a') retorno=80;
  }
  else if (qual==1) {
    if (oq=='w') retorno=96;
    else if (oq=='h') retorno=96;
    //selecao
    else if (oq=='x') retorno=36;
    else if (oq=='y') retorno=36;
    else if (oq=='l') retorno=65;
    else if (oq=='a') retorno=80;
  }
  else if (qual==2) {
    if (oq=='w') retorno=96;
    else if (oq=='h') retorno=96;
    //selecao
    else if (oq=='x') retorno=36;
    else if (oq=='y') retorno=36;
    else if (oq=='l') retorno=65;
    else if (oq=='a') retorno=80;
  }
  else if (qual==3) {
    if (oq=='w') retorno=64;
    else if (oq=='h') retorno=64;
    //selecao
    else if (oq=='x') retorno=10;
    else if (oq=='y') retorno=15;
    else if (oq=='l') retorno=52;
    else if (oq=='a') retorno=60;
  }
  return retorno;
}

void draw_npcs(int qual) {
  char nomeNpc[256];

  Nome_Npcs(npcs[qual].tipo,nomeNpc);

  int w=larguraTexto(font,"%s",nomeNpc);
  int h=alturaTexto(font);

  if ((w == -1) || (h == -1)) { printf("ERRO\n"); }
  else {
    int tempxboteox=(w-info_npcs(qual,'w'))/2;
    DrawText(font,78,238,172,255,4,npcs[qual].posx -tempxboteox -xpos,npcs[qual].posy-5-ypos,"%s",nomeNpc);
  }

  if (npcs[qual].tipo==4) {
    if (npcs[qual].acao==1) {
      npcs[qual].imagem++;
      if (npcs[qual].imagem>8) npcs[qual].imagem=8;
    }
    else if (npcs[qual].acao==2) {
      npcs[qual].imagem--;
      if (npcs[qual].imagem<0) npcs[qual].imagem=0;
    }
    DrawImg_LightMap(npcs_imag[qual],npcs[qual].posx-xpos,npcs[qual].posy-ypos,info_npcs(qual,'w'),info_npcs(qual,'h'),info_npcs(qual,'w')*npcs[qual].imagem,0);
  }
  else if ((npcs[qual].tipo==1) || (npcs[qual].tipo==3)) {
    DrawImg_LightMap(npcs_imag[qual],npcs[qual].posx-xpos,npcs[qual].posy-ypos,info_npcs(qual,'w'),info_npcs(qual,'h'),info_npcs(qual,'w')*npcs[qual].imagem,info_npcs(qual,'h')*npcs[qual].acao);
    npcs[qual].imagem++;
    if (npcs[qual].imagem>=9) { npcs[qual].imagem=0; npcs[qual].acao=0; }
  }
  else {
    DrawImg_LightMap(npcs_imag[qual],npcs[qual].posx-xpos,npcs[qual].posy-ypos,96,96,1+97*npcs[qual].imagem,97*npcs[qual].lado+1);
    if (npcs[qual].imagem<11) npcs[qual].imagem++;
    if ((npcs[qual].imagem>=11) && (npcs[qual].timetempo<=SDL_GetTicks()/1000)) {
      npcs[qual].imagem=0;
      npcs[qual].timetempo=SDL_GetTicks()/1000+10;
      boias[0].ativa=0;
    }
    else if (npcs[qual].imagem==11) boias[0].ativa=1;
  }

  //DrawIMG(npcs_imag[qual],npcs[qual].posx-xpos,npcs[qual].posy-ypos,info_npcs(qual,'w'),info_npcs(qual,'h'),info_npcs(qual,'w')*npcs[qual].imagem,info_npcs(qual,'h')*npcs[qual].acao);

  if (mouseverondeclia(npcs[qual].posx-xpos+info_npcs(qual,'x'),npcs[qual].posx-xpos+info_npcs(qual,'l'),npcs[qual].posy-ypos+info_npcs(qual,'y'),npcs[qual].posy-ypos+info_npcs(qual,'a'))) {
    CursorUsando[0]=2;
    CursorUsando[1]=qual+1;
  }
}
