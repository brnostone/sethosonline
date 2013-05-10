#include <GL/gl.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>

#include "Header/fonte.h"
#include "Header/log.h"
#include "Header/opengl.h"

int next_p2(int a) {
	int rval=2;
	while(rval<a) rval<<=1;
	return rval;
}

Uint32 *texturaPotencia2(Uint32 *pixels, int w, int h, int *width, int *height) {
  int j, i;

  *width = next_p2(w);
	*height = next_p2(h);

 	Uint32 *expanded_data = (Uint32 *) malloc(*width * *height * sizeof(Uint32));

	for(j=0; j < *height;j++) {
		for(i=0; i < *width; i++){
			expanded_data[i + j * *width] = (i>=w || j>=h) ?	0 : pixels[i + j*w];
		}
	}

	return expanded_data;
}

void trocarTextura(GLuint textId) {
  static GLuint texturaAtual=-1;

  if (texturaAtual != textId) {
    if (textId!=-1)
      glBindTexture(GL_TEXTURE_2D, textId );

    texturaAtual = textId;
  }
}

void deleteTextura(Textura **textura) {
  if (textura == NULL) return;

  glDeleteTextures(1, &(*textura)->id);
  free(*textura);

  *textura=NULL;
}

SDL_Surface* convertToStandardFormat(SDL_Surface* surface) {
  Uint32 rmask, gmask, bmask, amask;
#if SDL_BYTEORDER == SDL_BIG_ENDIAN
  rmask = 0xff000000;
  gmask = 0x00ff0000;
  bmask = 0x0000ff00;
  amask = 0x000000ff;
#else
  rmask = 0x000000ff;
  gmask = 0x0000ff00;
  bmask = 0x00ff0000;
  amask = 0xff000000;
#endif

  SDL_Surface *colorSurface = SDL_CreateRGBSurface(SDL_SWSURFACE, 0, 0, 32, rmask, gmask, bmask, amask);

  SDL_Surface *tmp = NULL;

  if (colorSurface != NULL) {
    tmp = SDL_ConvertSurface(surface, colorSurface->format, SDL_SWSURFACE);
    SDL_FreeSurface(colorSurface);
  }

  return tmp;
}

Textura *carregar_memoria(Uint32 *pixels, int w, int h, char alpha) {
  Textura *textura=(Textura *) calloc(1,sizeof(Textura));
  GLuint texture;

  glPixelStorei(GL_UNPACK_ALIGNMENT,4);

  glGenTextures(1,&texture);
  glBindTexture(GL_TEXTURE_2D,texture);

  int width;
	int height;

	Uint32 *expanded_data = texturaPotencia2(pixels, w, h, &width, &height);

  glTexImage2D(GL_TEXTURE_2D, 0, 4, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, expanded_data);

  glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER, GL_NEAREST);

  textura->id=texture;
  textura->w=width;
  textura->h=height;
  textura->alpha=alpha;

  free(expanded_data);

  return textura;
}

Textura *carregar_img(enum TipoImagem tipo, char *text, ... ) {
  char imagem[256];

  va_list ap;

  if (text == NULL) return 0;

  va_start(ap, text);
  vsprintf(imagem, text, ap);
  va_end(ap);

  if (imagem[0] == '\0') return 0;

  SDL_Surface *loadedSurface = IMG_Load(imagem);

  if (loadedSurface == NULL) {
    logtemp=1;
    //logging(3,"Incapaz de carregar a imagem: %s", imagem);

    return NULL;
  }

  SDL_Surface *Surface = convertToStandardFormat(loadedSurface);

  SDL_FreeSurface(loadedSurface);

  if (tipo == IMG_FUNDOROSA) {
    int percorreX;
    int percorreY;

    Uint32 *pixels=(Uint32 *) Surface->pixels;

#ifdef __BIG_ENDIAN__
        const unsigned int magicPink = 0xff00ffff;
#else
        const unsigned int magicPink = 0xffff00ff;
#endif

		for (percorreY=0; percorreY < Surface->h ; percorreY++) {
			for (percorreX = 0; percorreX < Surface->w; percorreX++) {
        if (pixels[percorreX + percorreY * Surface->w] == magicPink)
          pixels[percorreX + percorreY * Surface->w] = 0x00000000;
			}
		}
  }

  Textura *retorno=carregar_memoria(Surface->pixels,Surface->w, Surface->h,(tipo != IMG_NORMAL));

  SDL_FreeSurface(Surface);

  return retorno;
}

void DrawIMG(Textura *textura, int dstX, int dstY, int width, int height, int srcX, int srcY) {
  if ((textura->w < width) || (textura->h < height)) printf("tamanho errado\n");

  trocarTextura(textura->id);

  if (!textura->alpha)
    glDisable(GL_BLEND);

  //glLoadIdentity();

  float texX1 = srcX / (float)textura->w;
  float texY1 = srcY / (float)textura->h;
  float texX2 = (srcX+width) / (float)textura->w;
  float texY2 = (srcY+height) / (float)textura->h;

  glBegin(GL_QUADS);
    glTexCoord2f(texX1, texY1);
    glVertex3i(dstX, dstY, 0);

    glTexCoord2f(texX1, texY2);
    glVertex3i(dstX, dstY + height, 0);

    glTexCoord2f(texX2, texY2);
    glVertex3i(dstX + width, dstY + height, 0);

    glTexCoord2f(texX2, texY1);
    glVertex3i(dstX + width, dstY, 0);
  glEnd();

  if (!textura->alpha)
    glEnable(GL_BLEND);
}

void DrawIMG_RGBA(Textura *textura, int dstX, int dstY, int width, int height, int srcX, int srcY, unsigned char r, unsigned char g, unsigned char b, unsigned char a) {
  glColor4ub(r, g, b, a);

  DrawIMG(textura, dstX,  dstY, width, height, srcX, srcY);

  glColor4ub(255, 255, 255, 255);
}

void DrawPixel(int x, int y, unsigned char r, unsigned char g, unsigned char b, unsigned char a) {
  glColor4ub(r, g, b, a);
  glDisable(GL_TEXTURE_2D);

  glBegin(GL_POINTS);
    glVertex2i(x, y);
  glEnd();

  glEnable(GL_TEXTURE_2D);
  glColor4ub(255, 255, 255, 255);
}

void drawLine(int x1, int y1, int x2, int y2, unsigned char r, unsigned char g, unsigned char b, unsigned char a) {
  glColor4ub(r, g, b, a);
	glDisable(GL_TEXTURE_2D);

  glBegin(GL_LINES);
    glVertex2f(x1 + 0.375f, y1 + 0.375f);
    glVertex2f(x2 + 1.0f - 0.375f, y2 + 1.0f - 0.375f);
  glEnd();

  glEnable(GL_TEXTURE_2D);
  glColor4ub(255, 255, 255, 255);
}

void drawRectangle(int x, int y, int w, int h, unsigned char r, unsigned char g, unsigned char b, unsigned char a) {
  glColor4ub(r, g, b, a);
	glDisable(GL_TEXTURE_2D);

  glBegin(GL_LINE_LOOP);
    glVertex2f(x, y);
    glVertex2f(x + w - 1.0f + 0.375f, y + 0.375f);
    glVertex2f(x + w - 1.0f + 0.375f, y + h);
    glVertex2f(x, y + h);
  glEnd();

  glEnable(GL_TEXTURE_2D);
  glColor4ub(255, 255, 255, 255);
}

void fillRectangle(int x, int y, int w, int h, unsigned char r, unsigned char g, unsigned char b, unsigned char a) {
  glColor4ub(r, g, b, a);
	glDisable(GL_TEXTURE_2D);

  glBegin(GL_QUADS);
    glVertex2i(x, y);
    glVertex2i(x + w, y);
    glVertex2i(x + w, y + h);
    glVertex2i(x, y + h);
  glEnd();

  glEnable(GL_TEXTURE_2D);
  glColor4ub(255, 255, 255, 255);
}
