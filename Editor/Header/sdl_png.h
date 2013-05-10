#ifndef SDL_PNG_H_
#define SDL_PNG_H_

#define IMG_COMPRESS_OFF 0
#define IMG_COMPRESS_MAX 9
#define IMG_COMPRESS_DEFAULT -1

int IMG_SavePNG(const char *file, SDL_Surface *surf,int compression);

#endif /* SDL_PNG_H_ */


