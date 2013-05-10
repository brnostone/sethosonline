#include "Header/global.h"
#include "Header/tela_carregar.h"

void Tela_Carr_DrawScene() {
  int posicao=(260*((quantidade*100)/NUM_LOAD))/100;

  DrawIMG(logo[1],253,437,posicao,14,260-posicao,0);
  DrawIMG(logo[0],0,0,800,600,0,0);
//    DrawText2(250,250,250,0,0,0,"Carregando: %d",quantidade);
}

void Tela_Carr_Eventos(SDL_Event *event) {
  return;
}
