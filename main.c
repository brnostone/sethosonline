#include <time.h>
#include <GL/gl.h>
#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>

#include "Header/log.h"
#include "Header/global.h"
#include "Header/opengl.h"
#include "Header/load.h"
#include "Header/telas.h"
#include "Header/lightmap.h"
#include "Header/mapas.h"
#include "Header/online.h"
#include "Header/GUI.h"

#define WINDOW_W 800
#define WINDOW_H 600


#define TAMANHO_Y 120
#define TAMANHO_X 160

#define TITLE "Sethos Online versao de TESTE por Tronix"
#define FRAMES_PER_SECOND 50 //50==20 (1000/FRAMES_PER_SECOND)

//#define DEBUG

char lctrlpress=0;

int mapWidth = TAMANHO_X, mapHeight = TAMANHO_Y;

void DrawScene() {
  static int T0     = 0;
  static int Frames = 0;
  static float fps  = 0;

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  Tela_Draw();

  if (tela_Atual!=1) {
    DrawIMG(mouse, mousemovidox, mousemovidoy,28,28,(((CursorUsando[0]>0)?CursorUsando[0]:0)%8)*28,(((CursorUsando[0]>0)?CursorUsando[0]:0)/8)*28);

#ifdef DEBUG
    DrawText(font,200,200,200,255,0,0,30,"Flechas: %d",numarrow);
    DrawText(font,200,200,200,255,0,0,45,"Magicas: %d",nummagic);
    DrawText(font,200,200,200,255,0,0,60,"Xp: %d Yp: %d",personagem.x,personagem.y);
    DrawText(font,200,200,200,255,0,0,75,"atualX: %d atualY: %d",personagem.pathFind.atualX,personagem.pathFind.atualY);
    DrawText(font,200,200,200,255,0,0,90,"destinoX: %d destinoY: %d",personagem.pathFind.destinoX,personagem.pathFind.destinoY);
#endif

    DrawText(font,200,200,200,255,0,0,0,"FPS: %.2f",fps);
  }

  glFlush();
  SDL_GL_SwapBuffers();

  Frames++;
  int t = SDL_GetTicks();

  if (t - T0 >= 1000) {
    float seconds = (t - T0) / 1000.0;
    fps = Frames / seconds;
    T0 = t;
    Frames = 0;
  }
}

int main(int argc, char *argv[]) {
  Uint8 SDL_GetMouseState(int *x, int *y);
  keystate = SDL_GetKeyState(NULL);

  int ticks;

  logging(1,"Inicializando SDL:");
  if ( SDL_Init(SDL_INIT_AUDIO|SDL_INIT_VIDEO) < 0 ) {
    logging(3,"%s",SDL_GetError());
    ticjsja=SDL_GetTicks();
    logging(2,"ERRO");
    exit(1);
  }
  ticjsja=SDL_GetTicks();
  logging(2,"OK");
  atexit(SDL_Quit);

  GraphicsInit(TITLE, WINDOW_W,WINDOW_H,32,0);
  lightmap.textura=0;

  TTF_Init();
  atexit(TTF_Quit);
  SDL_EnableUNICODE( SDL_ENABLE );

  memset(itenschao,0,sizeof(itenschao));

  lermapafile("Data/Mapas/mapa1.set",296,384);
  objets_mapas(1);

  srand((unsigned) time(NULL));

  addtemporariamente();

  logging(1,"Carregando Menu:");

  logo[0]=carregar_img(IMG_FUNDOROSA,"Data/Imagens/Outros/sethos.png");
  logo[1]=carregar_img(IMG_NORMAL,"Data/Imagens/Outros/load.png");

  if (logtemp) logging(3,"Erro ao carregar imagens");
  else {
    logging(3,"Imagens carregadas");

    font=carregar_fonte("Data/Fontes/DejaVuSans.ttf",11);
    if (!font) { logging(3,"Erro ao carregar fonte"); logtemp=1; }
    else logging(3,"Fonte carregada");
  }
  if (logtemp) { logging(2,"ERRO"); exit(1); }
  else logging(2,"OK");


  Tela_Iniciar();
  Tela_Selecionar(1);

  DrawScene();

  InitImages();

  remove("Data/chat.log");

  while (done == 0) {
    SDL_Event event;
    ticks=SDL_GetTicks();
    while ( SDL_PollEvent(&event) ) {
      if (event.type == SDL_MOUSEMOTION) {
        mousemovidox=event.motion.x;
        mousemovidoy=event.motion.y;
      }
      else if (event.type == SDL_QUIT)  { done = 1; break; }
      else if (event.type == SDL_KEYDOWN) {
        if (event.key.keysym.sym == SDLK_F2)
          ListBox_Adicionar(4,9,84,130,7,"Foto salva [Fotos/foto%04d.bmp]",ScreenShot());
        else if (event.key.keysym.sym == SDLK_ESCAPE) { done=1; break; }
      }

      Tela_Evento(&event);
    }
/*
    if (keystate[SDLK_g]) {
      atacar(3,0,0);
      criar_magic(magictemp.posx,magictemp.posy,magictemp.mposx,magictemp.mposy,magictemp.lado,magictemp.qual);
    }
    if (keystate[SDLK_f]) {
      personagem.lado=arrumaragoliuasd(personagem.x+48,personagem.y+68,mousemovidox+xpos,mousemovidoy+ypos);
      atacar(1,mousemovidox,mousemovidoy);
      criar_arrow(arrowtemp.posx,arrowtemp.posy,arrowtemp.mposx,arrowtemp.mposy,arrowtemp.lado);
    }*/

    Tela_Depois();

    DrawScene();

    if ( SDL_GetTicks()-ticks < FRAMES_PER_SECOND ) { SDL_Delay(FRAMES_PER_SECOND - (SDL_GetTicks()-ticks)); }
  }

  limpaMemoria();

  remove("Data/chat.log");

  return 0;
}
