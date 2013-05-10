#include <GL/gl.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>

#include "Header/fonte.h"
#include "Header/opengl.h"
#include "Header/global.h"
#include "Header/LightMap.h"

unsigned char *mapLightMap=NULL;

void LightMap_delete() {
  if (mapLightMap)
    free(mapLightMap);

  glDeleteTextures(1, &lightmap.textura);
}

void LightMap_aloca(int width, int height) {
  //TODO: redimencionar lightmap sem perder o valor anterior

  mapLightMap=(unsigned char *) calloc(width * height * 3, sizeof(unsigned char));
}

void LightMap_carregar(int w, int h, unsigned char cor[3], unsigned char *pixels) {
  int x,y;
  int i;

  if (lightmap.textura == 0)
    glGenTextures(1, &lightmap.textura);

  int width = next_p2(mapWidth+2);
  int height = next_p2(mapHeight+2);

  if (mapLightMap != NULL)
    free(mapLightMap);

  LightMap_aloca(width, height);

  for(y=0; y < height ;y++) {
    for(x=0; x < width*3 ;x++) {
      i=x + y * width*3;

      if (pixels != NULL)
        mapLightMap[i] = (x>=w*3 || y>=h) ? cor[i%3] : pixels[x + y*w*3];
      else
        mapLightMap[i] = cor[i%3];
    }
  }

  lightmap.width=width;
  lightmap.height=height;

  glBindTexture(GL_TEXTURE_2D, lightmap.textura);
  glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
  glTexImage2D(GL_TEXTURE_2D, 0, 3, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, mapLightMap);
}

void calcLighPos(int objX, int objY, int objW, int objH, float w, float h, float lighPos[4][2]) {
  int srcX=objX+16;
  int srcY=objY+16;

  float texX1 = srcX / w;
  float texY1 = srcY / h;
  float texX2 = (srcX+objW) / w;
  float texY2 = (srcY+objH) / h;

  lighPos[0][0]=texX1;
  lighPos[0][1]=texY1;

  lighPos[1][0]=texX1;
  lighPos[1][1]=texY2;

  lighPos[2][0]=texX2;
  lighPos[2][1]=texY2;

  lighPos[3][0]=texX2;
  lighPos[3][1]=texY1;
}

void DrawImg_LightMap(Textura *textura, int dstX, int dstY, int width, int height, int srcX, int srcY) {
  static float lighPos[4][2];

  if ((textura->w < width) || (textura->h < height)) printf("tamanho errado\n");

  glActiveTextureARB(GL_TEXTURE0_ARB);
  trocarTextura(textura->id);
  glActiveTextureARB(GL_TEXTURE1_ARB);

  if (lightmap.ativo)
    glEnable(GL_TEXTURE_2D);

  trocarTextura(lightmap.textura);

  float texX1 = srcX / (float)textura->w;
  float texY1 = srcY / (float)textura->h;
  float texX2 = (srcX+width) / (float)textura->w;
  float texY2 = (srcY+height) / (float)textura->h;

  calcLighPos(dstX+xpos*64,dstY+ypos*48,width,height,lightmap.width*16,lightmap.height*16,lighPos);

  glBegin(GL_QUADS);
    glMultiTexCoord2fARB(GL_TEXTURE0_ARB, texX1, texY1);
    glMultiTexCoord2fvARB(GL_TEXTURE1_ARB, lighPos[0]);
    glVertex3i(dstX,dstY,0);

    glMultiTexCoord2fARB(GL_TEXTURE0_ARB, texX1, texY2);
    glMultiTexCoord2fvARB(GL_TEXTURE1_ARB, lighPos[1]);
    glVertex3i(dstX,dstY + height,0);

    glMultiTexCoord2fARB(GL_TEXTURE0_ARB, texX2, texY2);
    glMultiTexCoord2fvARB(GL_TEXTURE1_ARB, lighPos[2]);
    glVertex3i(dstX + width,dstY + height,0);

    glMultiTexCoord2fARB(GL_TEXTURE0_ARB, texX2, texY1);
    glMultiTexCoord2fvARB(GL_TEXTURE1_ARB, lighPos[3]);
    glVertex3i(dstX + width,dstY,0);
  glEnd();

  glActiveTextureARB(GL_TEXTURE1_ARB);
  glDisable(GL_TEXTURE_2D);
  glActiveTextureARB(GL_TEXTURE0_ARB);
}

unsigned char LightMap_getColor(int x, int y, int cor) {
  if ((!lightmap.ativo) || (lightmap.width <= x) || (lightmap.height <= y)) return 255;

  return mapLightMap[y * lightmap.width * 3 + x * 3 + cor];
}

Uint32 LightMap_getMapColor(SDL_PixelFormat *format, int x, int y) {
  return SDL_MapRGB(format, LightMap_getColor(x, y, 0), LightMap_getColor(x, y, 1), LightMap_getColor(x, y, 2));
}

void LightMap_atualizar() {
  //glDeleteTextures(1, &lightmap.textura);

  trocarTextura(lightmap.textura);

  glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, lightmap.width, lightmap.height, GL_RGB, GL_UNSIGNED_BYTE, mapLightMap);
}
