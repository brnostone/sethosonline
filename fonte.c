#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>

#include "Header/global.h"
#include "Header/opengl.h"
#include "Header/log.h"
#include "Header/fonte.h"

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
    Error("abrir fonte",ERRO_LOG);
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

void DrawTextFT(const Fonte *ft_font, float x, float y, const char *text)  {
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

void Draw_TextEmo(Fonte *fonte, unsigned char r,unsigned char g, unsigned char b, unsigned char a, char qualidade, int x, int y, char *msg, ...) {
  char *str2 = NULL,tempoao[256],tempoao2[256],chartemp;
  int w,addsmile=0,NumLetras=0;

  va_list ap;

  if (msg == NULL) return;

  va_start(ap, msg);
    vsprintf(tempoao, msg, ap);
  va_end(ap);

  DrawText(fonte,r,g,b,a,qualidade,x,y,"%s",tempoao);

  strcpy(tempoao2,tempoao);
  msg=tempoao2;
  str2 = strtok( tempoao, " " );
  while( str2 != NULL ) {
    if (strlen(str2)==2) {
      if (str2[0]==':') {
        if(str2[1]==')') addsmile=1;
        else if(str2[1]=='(') addsmile=76;
        else if(str2[1]=='D') addsmile=91;
        else if(str2[1]=='o') addsmile=31;
        else if(str2[1]=='O') addsmile=31;
        else if(str2[1]=='p') addsmile=136;
        else if(str2[1]=='P') addsmile=136;
        else if(str2[1]=='s') addsmile=106;
        else if(str2[1]=='S') addsmile=106;
        else if(str2[1]=='~') addsmile=151;
        else if(str2[1]=='|') addsmile=181;
        else if(str2[1]=='/') addsmile=196;
        else if(str2[1]=='$') addsmile=211;
        else addsmile=0;
      }
      else if (str2[0]=='6') {
        if(str2[1]==')') addsmile=121;
        else if(str2[1]=='(') addsmile=166;
        else addsmile=0;
      }
      else {
        if(!strcmp(str2,";)")) addsmile=16;
        else if(!strcmp(str2,"B)")) addsmile=46;
        else if(!strcmp(str2,"8|")) addsmile=61;
        else addsmile=0;
      }
      if (addsmile!=0) {
        chartemp=msg[NumLetras];
        msg[NumLetras]='\0';

        w=larguraTexto(fonte,"%s",msg);
        if (w == -1)
          printf("ERRO chat\n");
        else
          DrawIMG_RGBA(emoticon,w+x-2,y-1,15,15,addsmile-1,0,255,255,255,a);

        msg[NumLetras]=chartemp;
      }
      NumLetras+=3;
    }
    else { NumLetras+=strlen(str2)+1; }
    str2 = strtok( NULL, " " );
  }
  free(str2);
}
