#include <GL/gl.h>
#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>

#include "Header/fonte.h"
#include "Header/opengl.h"

int larguraTexto(Fonte *fonte, char *fmt, ...) {
  if ((fonte == NULL) || (fmt == NULL)) return -1;
	char texto[256];
	va_list	ap;

  va_start(ap, fmt);
    vsprintf(texto, fmt, ap);
  va_end(ap);

  int tamanho=0;
  int len=strlen(texto);
  int percorre;
  unsigned char ch;

  for (percorre=0; percorre<len ;percorre++) {
    ch=texto[percorre];

    tamanho+=fonte->chars[ch].width;
  }

  return tamanho;
}

int alturaTexto(Fonte *fonte) {
  if (fonte == NULL) return -1;

  return fonte->altura;
}

void make_dlist(TTF_Font *font, unsigned char ch, GLuint list_base, FonteChar *chars ) {
  char texto[5];

  SDL_Surface *text_surface;
  SDL_Color clrFg = {255,255,255,255};

  sprintf(texto,"%c",ch);

  text_surface=TTF_RenderText_Blended(font,texto, clrFg);

  if (!text_surface) return;
  SDL_Surface *Surface = convertToStandardFormat(text_surface);

	int width;
	int height;

	Uint32 *pixels = texturaPotencia2(Surface->pixels, Surface->w, Surface->h, &width, &height);

  glBindTexture( GL_TEXTURE_2D, chars->textura);

  glTexImage2D(GL_TEXTURE_2D, 0, 4, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixels);

  glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER, GL_NEAREST);

  free(pixels);

  SDL_FreeSurface(text_surface);

  chars->width=Surface->w;

	glNewList(list_base+ch,GL_COMPILE);

	glBindTexture(GL_TEXTURE_2D,chars->textura);

  glPushMatrix();

	float	x=(float)Surface->w / (float)width,
			y=(float)Surface->h / (float)height;

	glBegin(GL_QUADS);
    glTexCoord2d(0,0); glVertex2f(0,0);
    glTexCoord2d(0,y); glVertex2f(0,Surface->h);
    glTexCoord2d(x,y); glVertex2f(Surface->w,Surface->h);
    glTexCoord2d(x,0); glVertex2f(Surface->w,0);
	glEnd();

	glPopMatrix();

	glTranslatef(chars->width ,0,0);

	glEndList();

	SDL_FreeSurface(Surface);
}

Fonte *carregar_fonte(const char *fname, unsigned int tamanho) {
  TTF_Font *fontSDL=TTF_OpenFont(fname,tamanho);
  if (!fontSDL) {
    printf("Erro ao abrir fonte\n");
    return NULL;
  }

  Fonte *fonte=(Fonte *) calloc(1,sizeof(Fonte));

	fonte->chars = (FonteChar *) calloc(256,sizeof(FonteChar));

  TTF_SizeText(fontSDL,"A",NULL,&fonte->altura);

	fonte->list_base=glGenLists(255);

	unsigned char i;
	for (i=0; i<255 ;i++) {
    glGenTextures( 1, &fonte->chars[i].textura );
		make_dlist(fontSDL,i,fonte->list_base,&fonte->chars[i]);
	}

  TTF_CloseFont(fontSDL);

	return fonte;
}

void deleteFonte(Fonte **fonte) {
  if (fonte == NULL) return;

	glDeleteLists((*fonte)->list_base,255);

  unsigned char i;
	for (i=0; i<255 ;i++) {
    glDeleteTextures(1,&(*fonte)->chars[i].textura);
	}

	free((*fonte)->chars);
  free(*fonte);

  *fonte=NULL;
}

void DrawTextFT(const Fonte *ft_font, float x, float y, const char *text) {
	GLuint font=ft_font->list_base;

	if (text == NULL)
		return;

	glListBase(font);

	float modelview_matrix[16];
	glGetFloatv(GL_MODELVIEW_MATRIX, modelview_matrix);

  glPushMatrix();
  glLoadIdentity();

  glTranslatef(x,y,0);
	glMultMatrixf(modelview_matrix);

	glCallLists(strlen(text), GL_UNSIGNED_BYTE, text);

	glPopMatrix();
}

void DrawText(Fonte *fonte, unsigned char r,unsigned  char g,unsigned  char b,unsigned  char a, char qualidade,int x, int y, char *text, ... ) {
  trocarTextura(-1);
  char texto[256];
  va_list ap;

  if (text == NULL) return;

  va_start(ap, text);
  vsprintf(texto, text, ap);
  va_end(ap);

  if (texto[0] == '\0') return;

  if (qualidade>1) {
    if (qualidade>=8) glColor4ub(0, 0, 0, a);
    else if (qualidade>=6) glColor4ub(220, 220, 220, a);
    else if (qualidade>=4) glColor4ub(50, 50, 50, a);
    else if (qualidade>=2) glColor4ub(100, 100, 100, a);

    DrawTextFT(fonte,x+1,y+1,texto);
  }

  glColor4ub(r, g, b, a);

  DrawTextFT(fonte,x,y,texto);

  glColor4ub(255, 255, 255, 255);
}

void Draw_TextEmo(Fonte *fonte, unsigned char cor1,unsigned  char cor2,unsigned  char cor3,unsigned  char cor4, char qualidade,int x, int y, char *text, ... ) {
  printf("DrawTextEmo\n");
}
