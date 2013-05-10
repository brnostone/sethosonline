#ifndef FONTE_H_
#define FONTE_H_

  #include <stdarg.h>
  #include <GL/gl.h>
  #include <SDL/SDL.h>

  typedef struct {
    GLuint textura;
    int width;
  } FonteChar;

  typedef struct {
    int altura;
    FonteChar *chars;
    GLuint list_base;
  } Fonte;

  int larguraTexto(Fonte *fonte, char *fmt, ...);
  int alturaTexto(Fonte *fonte);

  Fonte *carregar_fonte(const char *fname, unsigned int tamanho);
  void deleteFonte(Fonte **fonte);

  void DrawText(Fonte *fonte, unsigned char r, unsigned char g, unsigned char b, unsigned char a, char qualidade, int x, int y, char *text, ...);
  void Draw_TextEmo(Fonte *fonte, unsigned char cor1, unsigned char cor2, unsigned char cor3, unsigned char cor4, char qualidade, int x, int y, char *text, ...);

#endif /* FONTE_H_ */

