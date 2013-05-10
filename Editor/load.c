#include <GL/gl.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>

#include "Header/fonte.h"
#include "Header/opengl.h"
#include "Header/global.h"
#include "Header/estruturas.h"
#include "Header/GUI.h"
#include "Header/Agrupador.h"
#include "Header/log.h"
#include "Header/load.h"

void InitImages() {
  int percorre;
  gui_i=carregar_img(IMG_FUNDOROSA,"../Data/Imagens/Outros/gui.png");
  mouse=carregar_img(IMG_ALPHA,"../Data/Imagens/Outros/mouse.png");
  cursorCor=carregar_img(IMG_ALPHA,"Data/verCor.png");
  fundoAlpha=carregar_img(IMG_ALPHA,"Data/fundoAlpha.png");
  cores=carregar_img(IMG_ALPHA,"Data/cores.png");
  ferramentas=carregar_img(IMG_ALPHA,"Data/ferramentas.png");

  for (percorre=1; percorre<=NUM_TITLE ;percorre++)
    title[percorre-1]=carregar_img(IMG_FUNDOROSA,"../Data/Imagens/Mapa/Tiles/%d.png",percorre);

  for (percorre=1; percorre<=3 ;percorre++)
    parede[percorre-1]=carregar_img(IMG_ALPHA,"../Data/Imagens/Mapa/Paredes/parede%02d.png", percorre);

  objetos[0]=carregar_img(IMG_ALPHA,"../Data/Imagens/Mapa/Objetos/objetos.png");
  objetos[1]=carregar_img(IMG_ALPHA,"../Data/Imagens/Mapa/Objetos/arvores.png");
  objetos[2]=carregar_img(IMG_ALPHA,"../Data/Imagens/Mapa/Objetos/objetos2.png");
  objetos[3]=carregar_img(IMG_ALPHA,"../Data/Imagens/Mapa/Objetos/objetos3.png");
  objetos[4]=carregar_img(IMG_ALPHA,"../Data/Imagens/Mapa/Objetos/objetos4.png");
  objetos[5]=carregar_img(IMG_ALPHA,"../Data/Imagens/Mapa/Objetos/objetos5.png");
  objetos[6]=carregar_img(IMG_ALPHA,"../Data/Imagens/Mapa/Objetos/objetos6.png");

  casa[0]=carregar_img(IMG_ALPHA,"../Data/Imagens/Mapa/Casas/mina1.png");
  casa[1]=carregar_img(IMG_ALPHA,"../Data/Imagens/Mapa/Casas/casa1.png");

  interacao[0]=carregar_img(IMG_ALPHA,"../Data/Imagens/Mapa/Objetos/berrybush.png");
  interacao[1]=carregar_img(IMG_ALPHA,"../Data/Imagens/Mapa/Objetos/uva.png");

  fontGUI=carregar_fonte("../Data/Fontes/DejaVuSansMono.ttf",12);
}

void Slock(SDL_Surface *screen) { if ( SDL_MUSTLOCK(screen) ) { if ( SDL_LockSurface(screen) < 0 ) { return; } } }
/* destrava a "tela" */
void Sulock(SDL_Surface *screen) { if ( SDL_MUSTLOCK(screen) ) { SDL_UnlockSurface(screen); } }

int mouseverondeclia (int tx,int tx2,int ty,int ty2) { if ((mousemovidox >= tx && mousemovidox <= tx2) && (mousemovidoy >= ty && mousemovidoy <= ty2)) { return 1; } else { return 0; } }

void InitGl() {
	glShadeModel( GL_SMOOTH );
	glClearColor( 1.0f, 1.0f, 1.0f, 0.0f );
	glClearDepth( 0.0f );
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable( GL_DEPTH_TEST );
	glDepthFunc( GL_ALWAYS );
	glHint( GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST );

	glDisable(GL_LIGHTING);

  glEnable(GL_BLEND);

	glEnable(GL_TEXTURE_2D);
}

char Initialize(int Width, int Height) {
    //setup ortho mode
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();

	glOrtho(0, (GLfloat)Width, (GLfloat)Height, 0, -10, 10);
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();

	return 1;
}

void GraphicsInit(const char *caption, int width, int height, int bpp, char fullscreen) {
  logging(1,"Iniciando video:");

  int m_Flags = SDL_OPENGL | SDL_GL_DOUBLEBUFFER | SDL_HWPALETTE;
  const SDL_VideoInfo* videoInfo = SDL_GetVideoInfo();

  SDL_WM_SetCaption(caption, NULL);
  SDL_WM_SetIcon(IMG_Load("../Data/Imagens/Outros/icon.bmp"), NULL);

	if (videoInfo->hw_available)
		m_Flags |= SDL_HWSURFACE;
	else
		m_Flags |= SDL_SWSURFACE;

  if ( videoInfo->blit_hw )
    m_Flags |= SDL_HWACCEL;

  SDL_GL_SetAttribute( SDL_GL_DOUBLEBUFFER, 1 );

  if (fullscreen) {
    m_Flags |= SDL_FULLSCREEN;
    logging(3,"Modo fullscreen setado");
  }
  else
    logging(3,"Modo janela setado");

  if ((m_Flags & SDL_FULLSCREEN) != SDL_FULLSCREEN)
    putenv("SDL_VIDEO_CENTERED=1");

  screen = SDL_SetVideoMode(width, height, bpp, m_Flags);

  if ( screen == NULL ) {
    logging(3, "Erro ao setar modo de video: %s", SDL_GetError());
    logging(2,"ERRO");
    exit(1);
  }
  else
    logging(3,"Modo de video setado");

	glViewport(0, 0, (GLsizei)width, (GLsizei) height);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

  InitGl();

  SDL_ShowCursor(SDL_DISABLE);
  logging(2,"OK");

  Initialize(width,height);
}
