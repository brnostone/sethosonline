#include <stdio.h>
#include <GL/gl.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>

#include "Header/fonte.h"
#include "Header/opengl.h"
#include "Header/estruturas.h"
#include "Header/GUI.h"
#include "Header/global.h"
#include "Header/EditorMapa.h"
#include "Header/LightMap.h"
#include "Header/Agrupador.h"
#include "Header/load.h"

#define FRAMES_PER_SECOND 16
#define TITLE "Editor - Sethos Online v2.0 by Tronix"

int xpos=0,ypos=0;
int cursorT=1;
int numJanela=30;

void DrawScene() {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  GUI_Draw(0,0,prim_GUI);

  if (cursorT == 1)
    DrawIMG(mouse, mousemovidox, mousemovidoy,28,28,0,0);
  else
    DrawIMG(cursorCor, mousemovidox-1, mousemovidoy-15,16,16,0,0);

  glFlush();
  SDL_GL_SwapBuffers();
}

int main(int argc, char *argv[]) {
  int ticks;
  Uint8 SDL_GetMouseState(int *x, int *y);
  keystate = SDL_GetKeyState(NULL);

  if ( SDL_Init(SDL_INIT_AUDIO|SDL_INIT_VIDEO) < 0 ) {
     exit(1);
  }

  GraphicsInit(TITLE, 800,613,32,0);

  TTF_Init();
  atexit(TTF_Quit);
  SDL_EnableUNICODE( SDL_ENABLE );

  InitImages();
  InitEditMap();

  GUI_Iniciar();

  Aba('n', 1, 0, 0, 800, 613, GUI_ATIVO, 0 ,NULL);

  ListaDupla *tmp_GUI=NULL;

  GUI_filhos('i',&tmp_GUI);
    FuncaoDesenho('n', 1, drawEditMapa, 0, 5, 640, 576, GUI_ATIVO, 0, eventEditMapa);
    FuncaoDesenho('n', 12, drawSelectObj, 661, 55, 131, 434, GUI_ATIVO, 0, eventSelectObj);

    ScrollBar('n', 6, 643, 55, 452, 12, GUI_INATIVO, SCROLLBAR_VERTICAL, NULL);
    ScrollBar('n', 13, 661, 492, 130, 12, GUI_INATIVO, SCROLLBAR_HORIZONTAL, NULL);

    RadioButton('n', "Camada 1", 7, 1, 642, 485, GUI_INATIVO, NULL);
    RadioButton('n', "Camada 2", 8, 1, 720, 485, GUI_INATIVO, NULL);
    RadioButton_Select(7);

    Botao('n', "Redimensionar Mapa", 9, 645, 510, 145, GUI_ATIVO, redimencionarMapa);

    Botao('n', "Carregar Mapa", 10, 645, 540, 145, GUI_ATIVO, carregarMapa);
    Botao('n', "Salvar Mapa", 11, 645, 560, 145, GUI_ATIVO, salvarMapa);

    GUI_filhos('i',&tmp_GUI);
      Texto('n', "Portal para:", 1, 0, 0, 1, GUI_ATIVO, 0, NULL);
      Texto('n', "Mapa:", 2, 27, 20, 1, GUI_ATIVO, 0, NULL);
      Texto('n', "x:", 3, 27, 40, 1, GUI_ATIVO, 0, NULL);
      Texto('n', "y:", 4, 27, 60, 1, GUI_ATIVO, 0, NULL);

      EditBox('n', "", 5, 77, 20, 50, GUI_ATIVO, EDITBOX_NUMERICO, NULL);
      EditBox('n', "", 6, 77, 40, 50, GUI_ATIVO, EDITBOX_NUMERICO, NULL);
      EditBox('n', "", 7, 77, 60, 50, GUI_ATIVO, EDITBOX_NUMERICO, NULL);

      Botao('n',"Cancelar", 8, 2, 90, 70, GUI_ATIVO, cancelPortal);
      Botao('n',"Salvar", 9, 78, 90, 70, GUI_ATIVO, salvarPortal);
    GUI_filhos('f',&tmp_GUI);

    Grupo('n', tmp_GUI, 14, 643, 210, 150, 150, GUI_INATIVO, 0, NULL);

    CheckBox('n', "Ativo", 15, 643, 30, 0, GUI_INATIVO, EditLighAtivo);

    GUI_filhos('i', &tmp_GUI);

      Botao('n', "Nova lightmap", 2, 0, 5, 145, GUI_ATIVO, EditLighNovaLight);

      Imagem('n', 3, cores, 0, 32, 150, 190, 0, 0, GUI_ATIVO, 0, EditLight_setColor);

      Texto('n', "R:", 4, 15, 233, 1, GUI_ATIVO, 0, NULL);
      EditBox('n', "0", 5, 30, 230, 50, GUI_ATIVO, EDITBOX_NUMERICO, EditLighAtualizaCor);

      Texto('n', "G:", 6, 15, 255, 1, GUI_ATIVO, 0, NULL);
      EditBox('n', "0", 7, 30, 252, 50, GUI_ATIVO, EDITBOX_NUMERICO, EditLighAtualizaCor);

      Texto('n', "B:", 8, 15, 277, 1, GUI_ATIVO, 0, NULL);
      EditBox('n', "0", 9, 30, 274, 50, GUI_ATIVO, EDITBOX_NUMERICO, EditLighAtualizaCor);

      Quadrado('n', 10, 90, 230, 50, 63, GUI_ATIVO, QUADRADO_PREENCHIDO, NULL);

      FuncaoDesenho('n', 11, drawEditLighFerramentas, 30, 305, 99, 49, GUI_ATIVO, 0, EditLighFerramentas);

      Texto('n', "Tamanho:", 12, 15, 365, 1, GUI_ATIVO, 0, NULL);
      EditBox('n', "1", 13, 75, 363, 50, GUI_ATIVO, EDITBOX_NUMERICO, NULL);

      CheckBox('n', "Exibir imagem", 14, 0, 392, 0, GUI_ATIVO, NULL);

      Botao('n', "Importar lightmap", 15, 0, 415, 145, GUI_ATIVO, importarLightMap);
      Botao('n', "Exportar lightmap", 16, 0, 435, 145, GUI_ATIVO, exportarLightMap);

    GUI_filhos('f',&tmp_GUI);

    Grupo('n', tmp_GUI, 16, 643, 45, 150, 480, GUI_INATIVO, 0, NULL);

    Texto('n', "Opção:", 2, 643, 28, 1, GUI_ATIVO, 0, NULL);
    ComboBox('n', 3, 690, 25, 100, GUI_ATIVO, 0, selectOpcao);

    Texto('n', "Tipo:", 4, 650, 8, 1, GUI_ATIVO, 0, NULL);
    ComboBox('n', 5, 690, 5, 100, GUI_ATIVO, 0, selectTipo);
    ComboBox_Adicionar(5, 0, 0, 0, 1, "Tile");
    ComboBox_Adicionar(5, 0, 0, 0, 1, "Parede");
    ComboBox_Adicionar(5, 0, 0, 0, 1, "Caminho");
    ComboBox_Adicionar(5, 0, 0, 0, 1, "Objeto");
    ComboBox_Adicionar(5, 0, 0, 0, 1, "Casas");
    ComboBox_Adicionar(5, 0, 0, 0, 1, "Interação");
    ComboBox_Adicionar(5, 0, 0, 0, 1, "LightMap");

    GUI_setLabel(5,"...");

  GUI_filhos('f',&tmp_GUI);

  Aba_adicionar(1,tmp_GUI,"Editor de Mapa");

  GUI_filhos('i', &tmp_GUI);

    FuncaoDesenho('n', 1, drawAgrupImg, 0, 5, 600, 400, GUI_ATIVO, FUNCAODESENHO_BORDA, eventAgrupImg);

    Texto('n', "Animação:", 3, 10, 415, 1, GUI_ATIVO, 0, NULL);
    FuncaoDesenho('n', 2, drawAgrupAnim, 0, 432, 200, 150, GUI_ATIVO, FUNCAODESENHO_BORDA, NULL);

    Texto('n', "Nome:", 4, 610, 10, 1, GUI_ATIVO, 0, NULL);
    EditBox('n', "", 5, 650, 8, 140, GUI_ATIVO, 0, NULL);

    CheckBox('n', "Máscara numérica", 6, 640, 35, 0, GUI_ATIVO, NULL);

    RadioButton('n', "Objeto", 7, 1, 620, 60, GUI_ATIVO, NULL);
    RadioButton('n', "Personagem", 8, 1, 690, 60, GUI_ATIVO, NULL);
    RadioButton_Select(7);

    Botao('n', "Analisar", 9, 650, 100, 100, GUI_ATIVO, AgrupAnalizar);

    Texto('n', "Offset x:", 10, 603, 132, 1, GUI_ATIVO, 0, NULL);
    EditBox('n', "0", 11, 670, 130, 40, GUI_ATIVO, EDITBOX_NUMERICO, NULL);
    Texto('n', "y:", 12, 715, 132, 1, GUI_ATIVO, 0, NULL);
    EditBox('n', "0", 13, 730, 130, 40, GUI_ATIVO, EDITBOX_NUMERICO, NULL);

    Texto('n', "Tamanho:", 14, 610, 160, 1, GUI_ATIVO, 0, NULL);
    EditBox('n', "", 15, 670, 158, 40, GUI_ATIVO, EDITBOX_NUMERICO, NULL);
    Texto('n', "x", 16, 716, 160, 1, GUI_ATIVO, 0, NULL);
    EditBox('n', "", 17, 730, 158, 40, GUI_ATIVO, EDITBOX_NUMERICO, NULL);

    Texto('n', "Número de imagens:", 18, 603, 192, 1, GUI_ATIVO, 0, NULL);
    EditBox('n', "", 19, 730, 190, 40, GUI_ATIVO, EDITBOX_NUMERICO, NULL);

    CheckBox('n', "Mostrar linha", 20, 640, 220, 0, GUI_ATIVO, NULL);

    Botao('n', "Apagar fundo", 21, 650 - 3, 260, 100, GUI_ATIVO, AgrupRemoveFundo);
    Botao('n', "Cor sombra", 22, 650 - 3, 282, 100, GUI_ATIVO, AgrupCorSombra);
    Botao('n', "Configurar Pasta", 23, 622, 385, 150, GUI_ATIVO, AgrupConfigPasta);

    Botao('n', "Carregar", 24, 622, 540, 150, GUI_ATIVO, AgrupCarregar);
    Botao('n', "Salvar", 25, 622, 560, 150, GUI_ATIVO, AgrupSalvar);

    Texto('n', "Tamanho: 0 x 0 pixels.", 26, 400, 410, 1, GUI_ATIVO, 0, NULL);

    CheckBox('n', "Mostrar fundo Alpha", 27, 622, 350, 0, GUI_ATIVO, NULL);

  GUI_filhos('f',&tmp_GUI);

  Aba_adicionar(1,tmp_GUI,"Agrupador");

  GUI_filhos('i', &tmp_GUI);

    Texto('n', "Tipo:", 1, 0, 15, 1, GUI_ATIVO, 0, NULL);
    ComboBox('n', 2, 40, 13, 160, GUI_ATIVO, 0, NULL);
    ComboBox_Adicionar(2, 0, 0, 0, 1, "Capacete");
    ComboBox_Adicionar(2, 0, 0, 0, 1, "Armadura");
    ComboBox_Adicionar(2, 0, 0, 0, 1, "Escudo");
    ComboBox_Adicionar(2, 0, 0, 0, 1, "Clava");
    ComboBox_Adicionar(2, 0, 0, 0, 1, "Machado");
    ComboBox_Adicionar(2, 0, 0, 0, 1, "Espada");
    ComboBox_Adicionar(2, 0, 0, 0, 1, "Staff");
    ComboBox_Adicionar(2, 0, 0, 0, 1, "Arco");
    ComboBox_Adicionar(2, 0, 0, 0, 1, "Amuleto");
    ComboBox_Adicionar(2, 0, 0, 0, 1, "Anel");
    ComboBox_Adicionar(2, 0, 0, 0, 1, "Bracelete");
    ComboBox_Adicionar(2, 0, 0, 0, 1, "Luvas");
    ComboBox_Adicionar(2, 0, 0, 0, 1, "Botas");
    ComboBox_Adicionar(2, 0, 0, 0, 1, "Capa");
    ComboBox_Adicionar(2, 0, 0, 0, 1, "Itens");
    ComboBox_Adicionar(2, 0, 0, 0, 1, "Varas de pesca");
    ComboBox_Adicionar(2, 0, 0, 0, 1, "Peixe");
    ComboBox_Adicionar(2, 0, 0, 0, 1, "Dinheiro");

    ScrollBar('n',3,185,40,540,12,GUI_ATIVO,SCROLLBAR_VERTICAL,NULL);

    FuncaoDesenho('n',4,drawEditMapa,0,40,180,540, GUI_ATIVO, 0, eventEditMapa);

    Texto('n', "Nome:", 5, 250, 40, 1, GUI_ATIVO, 0, NULL);

    EditBox('n', "", 6, 290, 38, 150,GUI_ATIVO, 0, NULL);

  GUI_filhos('f',&tmp_GUI);

  Aba_adicionar(1,tmp_GUI,"Gerenciador de Itens");

  GUI_filhos('i',&tmp_GUI);
    ListaDupla *tmp_GUI2=NULL;

    Aba('n', 1, 0, 0, 200, 200, GUI_ATIVO, 0 ,NULL);
    GUI_filhos('i',&tmp_GUI2);
      Texto('n', "teste2", 1, 12, 30, 1, GUI_ATIVO, EDITBOX_HISTORICO, NULL);
      EditBox('n', "Edit", 2, 5, 50, 85,GUI_ATIVO, 0, NULL);
    GUI_filhos('f',&tmp_GUI2);

    Aba_adicionar(1,tmp_GUI2,"Teste");

    GUI_filhos('i',&tmp_GUI2);
      Botao('n',"teste",1,0,15,100,GUI_ATIVO,NULL);
    GUI_filhos('f',&tmp_GUI2);

    Aba_adicionar(1,tmp_GUI2,"Teste2");

  GUI_filhos('f',&tmp_GUI);

  Aba_adicionar(1,tmp_GUI,"Mágicas");

  GUI_filhos('i',&tmp_GUI);
    GUI_filhos('i',&tmp_GUI);
      Texto('n', "R (0):", 1, 10, 30, 1, GUI_ATIVO, 0, NULL);
      ScrollBar('n',2,70,30,150,255,GUI_ATIVO,SCROLLBAR_HORIZONTAL,NULL);

      Texto('n', "G (0):", 3, 10, 50, 1, GUI_ATIVO, 0, NULL);
      ScrollBar('n',4,70,50,150,255,GUI_ATIVO,SCROLLBAR_HORIZONTAL,NULL);

      Texto('n', "B (0):", 5, 10, 70, 1, GUI_ATIVO, 0, NULL);
      ScrollBar('n',6,70,70,150,255,GUI_ATIVO,SCROLLBAR_HORIZONTAL,NULL);

    GUI_filhos('f',&tmp_GUI);

    GroupBox('n',"Cor ambiente:", tmp_GUI, 1, 5, 10,225,100, GUI_ATIVO, NULL);
  GUI_filhos('f',&tmp_GUI);

  Aba_adicionar(1,tmp_GUI,"Auras");

  GUI_filhos('i',&tmp_GUI);

  GUI_filhos('f',&tmp_GUI);

  Aba_adicionar(1,tmp_GUI,"Particulas");

  char done=0;
  while(done == 0) {
    SDL_Event event;
    ticks=SDL_GetTicks();
    while ( SDL_PollEvent(&event) ) {
      if (event.type == SDL_MOUSEMOTION) {
        mousemovidox=event.motion.x;
        mousemovidoy=event.motion.y;
      }
      else if (event.type == SDL_QUIT)  { done = 1; break; }
      else if (event.type == SDL_KEYDOWN) {
        if (event.key.keysym.sym == SDLK_ESCAPE) { done=1; break; }
      }

      GUI_Evento(&event, 0, 0,'p');
    }

    GUI_Depois();

    DrawScene();

    if ( SDL_GetTicks()-ticks < FRAMES_PER_SECOND ) { SDL_Delay(FRAMES_PER_SECOND - (SDL_GetTicks()-ticks)); }
  }

  GUI_libera(&prim_GUI);
  deleteFonte(&fontGUI);
  LightMap_delete();

  return 0;
}
