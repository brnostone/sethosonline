#include <SDL/SDL.h>
#include <SDL/SDL_image.h>

#include "Header/mapas.h"
#include "Header/pathfinding.h"
#include "Header/lightmap.h"
#include "Header/flechas.h"
#include "Header/magicas.h"
#include "Header/monstros.h"
#include "Header/animais.h"
#include "Header/GUI.h"
#include "Header/telas.h"
#include "Header/log.h"
#include "Header/modoconstrucao.h"
#include "Header/load.h"

int quantidade=0;

void carregar() {
  quantidade++;
  DrawScene();
}

void LoadInteligent(char oq,int tipo,int acao) {
  if (oq == 'p') {
    personagens[tipo-1][acao]=carregar_img(IMG_ALPHA,"Data/Imagens/Personagens/%02d%d.png",tipo,acao);
    loadint.loadperson[tipo-1][acao]=(SDL_GetTicks()/1000)+30;
  }
  else if (oq == 'm') {
    monstros[tipo-1][acao]=carregar_img(IMG_ALPHA,"Data/Imagens/Monstros/%02d%d.png",tipo,acao);
    loadint.loadmonstro[tipo-1][acao]=(SDL_GetTicks()/1000)+60;
  }
}

void CheckInteligent() {
  if (loadint.temp<=SDL_GetTicks()/1000) {
    int tipo,acao;

    for (tipo=0; tipo<NUMERODEPERSONAGENS ;tipo++) {
      for (acao=0; acao<8 ;acao++) {
        if ((loadint.loadperson[tipo][acao] != 0) && (loadint.loadperson[tipo][acao]<=SDL_GetTicks()/1000)) {
          deleteTextura(&personagens[tipo][acao]);

          loadint.loadperson[tipo][acao]=0;
        }
      }
    }

    for (tipo=0;tipo<QUANT_MONSTROS;tipo++) {
      for (acao=0; acao<6 ;acao++) {
        if ((loadint.loadmonstro[tipo][acao]!=0) && (loadint.loadmonstro[tipo][acao]<=SDL_GetTicks()/1000)) {
          deleteTextura(&monstros[tipo][acao]);

          loadint.loadmonstro[tipo][acao]=0;
        }
      }
    }

    loadint.temp=(SDL_GetTicks()/1000)+5;
  }
}

void InitImages() {
  logging(1,"Carregando imagens:");

  int percorre=0,percorre2=1;

  for (percorre2=0; percorre2<NUMERODEPERSONAGENS ;percorre2++) {
    for (percorre=0; percorre<8 ;percorre++) {
      personagens[percorre2][percorre]=NULL;
      loadint.loadperson[percorre2][percorre]=0;
    }
    carregar();
  }

  personagemmagica=carregar_img(IMG_ALPHA,"Data/Imagens/Personagens/048.png");
  npcs_imag[0]=carregar_img(IMG_ALPHA,"Data/Imagens/NPCs/ferreiro.png");
  npcs_imag[1]=carregar_img(IMG_ALPHA,"Data/Imagens/NPCs/pescador.png");
  npcs_imag[2]=carregar_img(IMG_ALPHA,"Data/Imagens/NPCs/mago.png");
  npcs_imag[3]=carregar_img(IMG_ALPHA,"Data/Imagens/NPCs/bau.png");

  if (!logtemp) logging(3,"Personagens carregados");
  else { logging(3,"Erro ao carregar personagens"); goto fim; }

  for (percorre2=0; percorre2<QUANT_MONSTROS ;percorre2++) {
    for (percorre=0; percorre<6 ;percorre++) {
      monstros[percorre2][percorre]=NULL;
      loadint.loadmonstro[percorre2][percorre]=0;
    }
  }

  carregar();

  if (!logtemp) logging(3,"Monstros carregados");
  else { logging(3,"Erro ao carregar monstros"); goto fim; }

  for (percorre=0; percorre<32 ;percorre++) {
    flechas[percorre]=carregar_img(IMG_ALPHA,"Data/Imagens/Ataques/Flechas/arrow%d.png",percorre);
  }

  carregar();

  for (percorre=0; percorre<NUM_MAGICS ;percorre++)
    magicas[percorre]=carregar_img(IMG_ALPHA,"Data/Imagens/Ataques/magicas/%d.png",percorre);

  for (percorre=0; percorre<7 ;percorre++)
    blackaura[percorre]=carregar_img(IMG_ALPHA,"Data/Imagens/Ataques/Auras/aurablack%d.png",percorre);

  carregar();

  for (percorre=0; percorre<16 ;percorre++)
    aurazul[percorre]=carregar_img(IMG_ALPHA,"Data/Imagens/Ataques/Auras/aurazul%d.png",percorre);

  carregar();

  for (percorre=0; percorre<7 ;percorre++)
    aurawhite[percorre]=carregar_img(IMG_ALPHA,"Data/Imagens/Ataques/Auras/aurazul%d.png",percorre);

  for (percorre=0; percorre<5 ;percorre++)
    auraverde[percorre]=carregar_img(IMG_ALPHA,"Data/Imagens/Ataques/Auras/auraverde%d.png",percorre);

  carregar();

  for (percorre=0; percorre<5 ;percorre++)
    auraba[percorre]=carregar_img(IMG_ALPHA,"Data/Imagens/Ataques/Auras/auraba%d.png",percorre);

  for (percorre=0; percorre<6 ;percorre++)
    auragirado[percorre]=carregar_img(IMG_ALPHA,"Data/Imagens/Ataques/Auras/auragirado%d.png",percorre);

  if (!logtemp) logging(3,"Magicas carregadas");
  else { logging(3,"Erro ao carregar magicas"); goto fim; }

  carregar();

  for (percorre=1; percorre<=NUM_TITLEOU ;percorre++)
    title[percorre-1]=carregar_img(IMG_FUNDOROSA,"Data/Imagens/Mapa/Tiles/%d.png",percorre);

  carregar();

  if (!logtemp) logging(3,"Tiles carregados");
  else { logging(3,"Erro ao carregar tiles"); goto fim; }

  barra=carregar_img(IMG_FUNDOROSA,"Data/Imagens/Outros/barra.png");
  barraquantid=carregar_img(IMG_FUNDOROSA,"Data/Imagens/Outros/quantidade.png");
  botaopress=carregar_img(IMG_NORMAL,"Data/Imagens/Outros/botaopresionado.png");
  inventario=carregar_img(IMG_NORMAL,"Data/Imagens/Outros/inventario.png");
  charmenu=carregar_img(IMG_FUNDOROSA,"Data/Imagens/Outros/char.png");
  magicmenu=carregar_img(IMG_NORMAL,"Data/Imagens/Outros/magicas.png");
  baumenu=carregar_img(IMG_NORMAL,"Data/Imagens/Outros/bau.png");
  balao=carregar_img(IMG_FUNDOROSA,"Data/Imagens/Outros/balao.png");

  carregar();
  gui_i=carregar_img(IMG_FUNDOROSA,"Data/Imagens/Outros/gui.png");
  boia=carregar_img(IMG_FUNDOROSA,"Data/Imagens/Outros/boia.png");
  BotaoEstilo=carregar_img(IMG_FUNDOROSA,"Data/Imagens/Outros/Botao_Estilo.png");
  cursorpesca=carregar_img(IMG_FUNDOROSA,"Data/Imagens/Outros/pescacursor.png");
  barrapesca=carregar_img(IMG_ALPHA,"Data/Imagens/Outros/barrapesca.png");

  carregar();
  efeitos=carregar_img(IMG_ALPHA,"Data/Imagens/Outros/efeitos.png");

  for (percorre=1; percorre<=NUM_PAREDES ;percorre++)
    parede[percorre-1]=carregar_img(IMG_ALPHA,"Data/Imagens/Mapa/Paredes/parede%02d.png", percorre);

  objetos[0]=carregar_img(IMG_ALPHA,"Data/Imagens/Mapa/Objetos/objetos.png");
  objetos[1]=carregar_img(IMG_ALPHA,"Data/Imagens/Mapa/Objetos/arvores.png");
  objetos[2]=carregar_img(IMG_ALPHA,"Data/Imagens/Mapa/Objetos/objetos2.png");

  carregar();
  objetos[3]=carregar_img(IMG_ALPHA,"Data/Imagens/Mapa/Objetos/objetos3.png");
  objetos[4]=carregar_img(IMG_ALPHA,"Data/Imagens/Mapa/Objetos/objetos4.png");
  objetos[5]=carregar_img(IMG_ALPHA,"Data/Imagens/Mapa/Objetos/objetos5.png");
  objetos[6]=carregar_img(IMG_ALPHA,"Data/Imagens/Mapa/Objetos/objetos6.png");

  casa[0]=carregar_img(IMG_ALPHA,"Data/Imagens/Mapa/Casas/mina1.png");
  casa[1]=carregar_img(IMG_ALPHA,"Data/Imagens/Mapa/Casas/casa1.png");

  interacao[0]=carregar_img(IMG_ALPHA,"Data/Imagens/Mapa/Objetos/berrybush.png");
  interacao[1]=carregar_img(IMG_ALPHA,"Data/Imagens/Mapa/Objetos/uva.png");

  if (!logtemp) logging(3,"Objetos do mapa carregados");
  else { logging(3,"Erro ao carregar objetos do mapa"); goto fim; }

  carregar();

  for (percorre=1; percorre<=NUM_ANIMAIS ;percorre++)
    animais[percorre-1]=helms=carregar_img(IMG_ALPHA,"Data/Imagens/Animais/animal%02d_1.png", percorre);

  if (!logtemp) logging(3,"Animais carregados");
  else { logging(3,"Erro ao carregar animais"); goto fim; }

  carregar();

  helms=carregar_img(IMG_FUNDOROSA,"Data/Imagens/Objetos/helms.png");
  armor=carregar_img(IMG_FUNDOROSA,"Data/Imagens/Objetos/armor.png");
  escudos=carregar_img(IMG_FUNDOROSA,"Data/Imagens/Objetos/escudos.png");
  clavas=carregar_img(IMG_FUNDOROSA,"Data/Imagens/Objetos/clavas.png");
  machados=carregar_img(IMG_FUNDOROSA,"Data/Imagens/Objetos/machados.png");
  espadas=carregar_img(IMG_FUNDOROSA,"Data/Imagens/Objetos/espadas.png");
  staffs=carregar_img(IMG_FUNDOROSA,"Data/Imagens/Objetos/staffs.png");
  arcos=carregar_img(IMG_FUNDOROSA,"Data/Imagens/Objetos/arcos.png");
  amuletos=carregar_img(IMG_FUNDOROSA,"Data/Imagens/Objetos/amuletos.png");
  aneis=carregar_img(IMG_FUNDOROSA,"Data/Imagens/Objetos/aneis.png");
  varapesca=carregar_img(IMG_FUNDOROSA,"Data/Imagens/Objetos/varapesca.png");

  if (!logtemp) logging(3,"Armas e armaduras carregadas");
  else { logging(3,"Erro ao carregar armas e armaduras"); goto fim; }

  carregar();

  braco=carregar_img(IMG_FUNDOROSA,"Data/Imagens/Objetos/braco.png");
  luvas=carregar_img(IMG_FUNDOROSA,"Data/Imagens/Objetos/luvas.png");
  botas=carregar_img(IMG_FUNDOROSA,"Data/Imagens/Objetos/botas.png");
  capas=carregar_img(IMG_FUNDOROSA,"Data/Imagens/Objetos/capas.png");
  item=carregar_img(IMG_FUNDOROSA,"Data/Imagens/Objetos/itens.png");
  item2=carregar_img(IMG_FUNDOROSA,"Data/Imagens/Objetos/itens2.png");
  armasnochao=carregar_img(IMG_FUNDOROSA,"Data/Imagens/Objetos/armaschao.png");
  amuletosanelchao=carregar_img(IMG_FUNDOROSA,"Data/Imagens/Objetos/amuletosanelchao.png");
  barclubochao=carregar_img(IMG_FUNDOROSA,"Data/Imagens/Objetos/barclubochao.png");
  capaschao=carregar_img(IMG_FUNDOROSA,"Data/Imagens/Objetos/capaschao.png");

  carregar();

  itenschaoi=carregar_img(IMG_FUNDOROSA,"Data/Imagens/Objetos/itenschao.png");
  itens2chaoi=carregar_img(IMG_FUNDOROSA,"Data/Imagens/Objetos/itens2chao.png");
  armesccaho=carregar_img(IMG_FUNDOROSA,"Data/Imagens/Objetos/armesccaho.png");
  helmschao=carregar_img(IMG_FUNDOROSA,"Data/Imagens/Objetos/helmschao.png");
  dinheirochao=carregar_img(IMG_FUNDOROSA,"Data/Imagens/Objetos/dinheiro.png");

  if (!logtemp) logging(3,"Itens carregados");
  else { logging(3,"Erro ao carregar itens"); goto fim; }

  particulas[0]=carregar_img(IMG_ALPHA,"Data/Imagens/Ataques/particulas/particula1.png");
  particulas[1]=carregar_img(IMG_ALPHA,"Data/Imagens/Ataques/particulas/particula2.png");
  particulas[2]=carregar_img(IMG_ALPHA,"Data/Imagens/Ataques/particulas/particula3.png");
  magicasbotao=carregar_img(IMG_NORMAL,"Data/Imagens/Ataques/magicas/magicas.PNG");

  vendeitem=carregar_img(IMG_ALPHA,"Data/Imagens/Outros/vendeitem.png");
  carregar();

  mouse=carregar_img(IMG_ALPHA,"Data/Imagens/Outros/mouse.png");
  emoticon=carregar_img(IMG_FUNDOROSA,"Data/Imagens/Outros/emoticon.png");

  font2=carregar_fonte("Data/Fontes/DejaVuSans-Bold.ttf",12);
  fontGUI=carregar_fonte("Data/Fontes/DejaVuSansMono.ttf",10);

  if ((!font2) || (!fontGUI)) { logging(3,"Erro ao carregadar fontes"); logtemp=1; }
  else logging(3,"Fontes carregadas");

  carregar();
  Tela_Selecionar(2);
  ModoConstrucao_Start();

//  printf("%d\n",quantidade);

  fim:
  if (logtemp) { logging(2,"ERRO"); exit(1); }
  else logging(2,"OK");
}

void InitGl() {
	glShadeModel( GL_SMOOTH );
	glClearColor( 0.72f, 0.72f, 0.72f, 0.0f );
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
  SDL_WM_SetIcon(IMG_Load("Data/Imagens/Outros/icon.bmp"), NULL);

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

void limpaMemoria() {
  Liberar_Mapa();

  while (arrowacao(1,'s')) arrowacao(1,'d');
  while (magicacao(1,'s')) magicacao(1,'d');
  while (animalacao(1,'s')) animalacao(1,'d');
  monsterlacao(1,'z');

  fimPathfind();
  Tela_Fim();

  deleteFonte(&font);
  deleteFonte(&font2);
  deleteFonte(&fontGUI);
  LightMap_delete();

  GUI_libera(&prim_GUI);
}
