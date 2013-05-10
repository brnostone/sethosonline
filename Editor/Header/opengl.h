#ifndef OPENGL_H_
#define OPENGL_H_

  #include <GL/gl.h>
  #include <SDL/SDL.h>

  enum TipoImagem {
    IMG_NORMAL=1,
    IMG_ALPHA,
    IMG_FUNDOROSA
  };

  typedef struct {
    GLuint id;
    int w;
    int h;

    char alpha;
  } Textura;


  int next_p2(int a);
  void trocarTextura(GLuint textId);
  SDL_Surface* convertToStandardFormat(SDL_Surface* surface);
  Uint32 *texturaPotencia2(Uint32 *pixels, int w, int h, int *width, int *height);

  void deleteTextura(Textura **textura);

  Textura *carregar_memoria(Uint32 *pixels, int w, int h, char alpha);
  Textura *carregar_img(enum TipoImagem tipo, char *text, ... );

  void DrawIMG(Textura *textura, int dstX, int dstY, int width, int height, int srcX, int srcY);
  void DrawIMG_RGBA(Textura *textura, int dstX, int dstY, int width, int height, int srcX, int srcY, unsigned char r, unsigned char g, unsigned char b, unsigned char a);

  void DrawPixel(int x, int y, unsigned char r, unsigned char g, unsigned char b, unsigned char a);
  void drawLine(int x1, int y1, int x2, int y2, unsigned char r, unsigned char g, unsigned char b, unsigned char a);
  void drawRectangle(int x, int y, int w, int h, unsigned char r, unsigned char g, unsigned char b, unsigned char a);
  void fillRectangle(int x, int y, int w, int h, unsigned char r, unsigned char g, unsigned char b, unsigned char a);


#endif /* OPENGL_H_ */
