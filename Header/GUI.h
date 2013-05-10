#ifndef GUI_H_
#define GUI_H_

  #include "opengl.h"
  #include "fonte.h"
  #include "estruturas.h"


  #define GUI_ATIVO 1
  #define GUI_INATIVO 0

  #define SCROLL_INVERSO 2
  #define SCROLLBAR_HORIZONTAL 4
  #define SCROLLBAR_VERTICAL 8

  #define LISTBOX_FUNDOTRANS 16
  #define LISTBOX_SEMBORDA 32

  #define TEXTO_EMOTICO 4

  #define EDITBOX_HISTORICO 8
  #define EDITBOX_NUMERICO 16
  #define EDITBOX_PASSWORD 32

  #define JANELA_NAOFECHAR 8
  #define JANELA_MOVEALL 32
  #define JANELA_CENTRALIZADA 64

  #define IMAGEM_DELETAR 64

  #define FUNCAODESENHO_BORDA 8

  #define QUADRADO_PREENCHIDO 2

  #define SCROLL_LISTBOX 15

  enum TipoEvento {
    TECLA_DOWN=1,
    TECLA_UP,
    MOUSE_MOVE,
    MOUSE_DOWN_LEFT,
    MOUSE_UP_LEFT,
    MOUSE_DOWN_RIGHT,
    MOUSE_UP_RIGHT
  };

  typedef struct {
    int id;
    int x;
    int y;
    enum TipoEvento acao;
    SDLKey sym;
    struct componentes *dados;
  } GUIParms;

  typedef struct {
    int elemtClick;
    int quantElementos;
    int barraPosicaoRol;
    char inverso;

    float barraPosicaoVer;
  } ScrollElmt;

  typedef struct {
    int larguraLen;

    ScrollElmt scroll;

    Lista *listElementos;
  } ListboxVarAux;

  struct componenteItem {
    char *texto;
    unsigned char r;
    unsigned char g;
    unsigned char b;
    char qualidade;
  };

  struct listaAbas {
    char *label;
    ListaDupla *filhos;
    int largura;
  };

  enum ComponenteTipo {
    EDITBOX=1,
    BOTAO,
    LISTBOX,
    SCROLLBAR,
    CHECKBOX,
    RADIOBUTTON,
    GROUPBOX,
    PROGRESSBAR,
    COMBOBOX,
    TEXTO,
    IMAGEM,
    QUADRADO,
    FUNCAODESENHO,
    JANELA,
    GRUPO,
    ABA,
    OCULTO
  };

  struct componentes {
    int id;

    int x;
    int y;
    unsigned int w;
    unsigned int h;

    enum ComponenteTipo tipo;

    int larguraLenMax;

    int opt;
    int opt2;
    int opt3;

    int quantidade;

    int cursor;
    int ativo;

    unsigned char r;
    unsigned char g;
    unsigned char b;

    char *label;
    int (*funcao)(GUIParms *);

    Fonte *fonte;
    void *aux;
  };

  Fonte *fontGUI;
  Textura *gui_i;

  ListaDupla *prim_GUI;

  int guiIdGeral;
  struct componentes *componenteAtual;

  int Componente_Acao(int id,char acao);
  void GUI_pilha(char oq);
  void drawRepetir(Textura *img, int x, int y, int w, int h,int x2, int y2, int w2, int h2);
  int GUI_BuscaElem(int id, int tipo);
  void GUI_libera(ListaDupla **lista);
  void GUI_setecionar(int id);

  void GUI_MudarCor(int id, unsigned char r, unsigned char g, unsigned char b);
  void GUI_MudarFonte(int id, Fonte *fonte);

  ListaDupla **GUI_AbrirFilho(int id);
  void GUI_FecharFilho(ListaDupla **primComp);

  void GUI_AbrirPai();
  void GUI_FecharPai();

  void EditBox(char oq, char *label,int id, int x, int y, unsigned int w, int ativo, int opt, void *funcao);
  void EditBox_SalvaHistorico(int id);

  void Botao(char oq, char *label, int id, int x, int y, unsigned int w, int ativo, void *funcao);

  void ListBox(char oq, int id, int x, int y, unsigned int w, unsigned int h, int ativo, int opt, void *funcao);
  void ListBox_Adicionar(int id, unsigned char r,unsigned char g,unsigned char b, char qualid, char *texto, ...);

  void ScrollBar(char oq, int id, int x, int y, unsigned int tamanho, int quantidade, int ativo, int opt, void *funcao);
  void Scroll_setTamanho(int id, int tamanho);
  void Scroll_setPosicao(int id, int posicao);
  int Scroll_getPosicao(int id);


  void CheckBox(char oq, char *label, int id, int x, int y, int sel, int ativo, void *funcao);
  void CheckBox_setSelect(int id, int sel);
  int CheckBox_isSelect(int id);

  void RadioButton(char oq, char *label, int id, int grupo, int x, int y, int ativo,void *funcao);
  int RadioButton_Select(int id);
  int RadioButton_getSelect(int grupo);

  void GroupBox(char oq, char *label, ListaDupla *filhos, int id, int x, int y, int w, int h, int ativo, void *funcao);

  void ProgressBar(char oq, int id, int x, int y, int w, int percentatual, int percentmax, int ativo, void *funcao);
  void ProgressBar_setValor(int id, int valor);
  int ProgressBar_getValor(int id);

  void ComboBox(char oq, int id, int x, int y, unsigned int w, int ativo,int opt, void *funcao);
  void ComboBox_Adicionar(int id, unsigned char r,unsigned char g,unsigned char b, char qualid, char *texto, ...);
  void ComboBox_Limpar(int id);
  void ComboBox_Seleciona(int id, int elemento);
  int ComboBox_getValor(int id);

  void Texto(char oq, char *label, int id, int x, int y, int qualidade, int ativo, int opt, void *funcao);

  void Imagem(char oq, int id, Textura *img, int x, int y, int w, int h, int x2, int y2, int ativo, int opt, void *funcao);

  void Quadrado(char oq, int id, int x, int y, int w, int h, int ativo, int opt, void *funcao);

  void FuncaoDesenho(char oq, int id, void (*funcDes)(), int x, int y, int w, int h, int ativo, int opt, void *funcao);

  void Janela(char oq, char *label, ListaDupla *filhos, int id, int x, int y, int w, int h, int ativo, int opt, void *funcao);
  int Janela_getPai();
  void Janela_fechar();
  void Janela_botaoFechar(GUIParms *parm);

  void Grupo(char oq, ListaDupla *filhos, int id, int x, int y, int w, int h, int ativo, int opt, void *funcao);

  void Aba(char oq, int id, int x, int y, int w, int h, int ativo, int opt, void *funcao);
  void Aba_adicionar(int id, ListaDupla *elementos, char *texto, ...);

  void Oculto(char oq, int id, int opt, int opt2, int opt3, void *aux);

  void GUI_filhos(char oq, ListaDupla **elementos);

  void GUI_Iniciar();
  void GUI_Depois();
  void GUI_Draw(int x, int y, ListaDupla *primElemento);
  int GUI_Evento(SDL_Event *event, int guiX, int guiY, char tipo);

  //geral

  char *GUI_getLabel(int id);
  void GUI_setLabel(int id, char *msg, ...);

  int GUI_getTamanho(int id, char qual);

  void GUI_setAtivo(int id, int ativo);
  int GUI_isAtivo(int id);

  void GUI_setPosicao(int id, int x, int y);
  void GUI_setTamanho(int id, int w, int h);

#endif /* GUI_H_ */
