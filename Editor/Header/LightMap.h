#ifndef LIGHTMAP_H_
#define LIGHTMAP_H_

  struct Lightmap {
    GLuint textura;
    char ativo;

    int width;
    int height;
  } lightmap;

  unsigned char *mapLightMap;

  void LightMap_aloca(int width, int height);
  void LightMap_delete();

  void LightMap_carregar(int w, int h, unsigned char cor[3], unsigned char *pixels);

  void DrawImg_LightMap(Textura *textura, int dstX, int dstY, int width, int height, int srcX, int srcY);

  unsigned char LightMap_getColor(int x, int y, int cor);
  Uint32 LightMap_getMapColor(SDL_PixelFormat *format, int x, int y);

  void LightMap_atualizar();

#endif /* LIGHTMAP_H_ */

