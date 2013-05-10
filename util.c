#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Header/global.h"
#include "Header/util.h"

void ListString_adiciona(ListString *listString, char *fmt, ...) {
  if (fmt == NULL) return;
  char texto[256];
  va_list ap;

  va_start(ap, fmt);
    vsprintf(texto, fmt, ap);
  va_end(ap);

  char *newText=(char *) lista_acao('n',listString,1,MUDAR_ID|ADD_CERTO,(strlen(texto) +1) * sizeof(char));

  strcpy(newText,texto);
}

void ListString_limpa(ListString *listString) {
  while (*listString != NULL)
    lista_acao('d',listString,(*listString)->id,MUDAR_ID|ADD_CERTO,0);
}

void ListString_deleta(ListString *listString, int id) {
  lista_acao('d',listString,id,MUDAR_ID|ADD_CERTO,0);
}

char *ListString_get(ListString *listString, int id) {
  return (char *) lista_acao('s',listString,id,MUDAR_ID|ADD_CERTO,0);
}

int ListString_tamanho(ListString listString) {
  int tamanho=0;

  forList (char *, tmp, listString)
    tamanho++;

  return tamanho;
}

ListString ListString_split(char *texto, char *ch) {
  char str[512];
  strncpy(str,texto,512);

  ListString listaSplit=NULL;
  char *pch = strtok(str,ch);

  while (pch != NULL) {
    ListString_adiciona(&listaSplit,"%s",pch);
    pch = strtok(NULL,ch);
  }

  return listaSplit;
}

ListString String_quebraTexto(Fonte *fonte, int tamMax, char *fmt, ...) {
  int w,tamanho,cont,conttemp,linhatamn=0,espaco;
  char subest;

  ListString primString=NULL;
  ListString textoSlipt=NULL;

  if (fmt == NULL) return NULL;
  if (strlen(fmt) > 1024) {
    printf("String muito grande para quebrar.\n");
    return NULL;
  }

  char texto[1024];
  char textoAdd[256];

  va_list ap;

  va_start(ap, fmt);
    vsprintf(texto, fmt, ap);
  va_end(ap);

  espaco=larguraTexto(fonte," ");
  memset(textoAdd,'\0',sizeof(textoAdd));

  textoSlipt=ListString_split(texto,"\n");

  forList (char *, msg, textoSlipt) {
    textoAdd[0]='\0';
    linhatamn=0;

    for (cont=0; cont<strlen(msg) ;cont++) {
      if ((msg[cont] == ' ') || (cont == strlen(msg)-1)) {
        subest=msg[cont];
        conttemp=cont;

        msg[cont]='\0';

        tamanho=strlen(msg)+1;

        w=larguraTexto(fonte,"%s",msg);

        int add=0;

        do {
          if (linhatamn+w+((!linhatamn)?0:espaco) <= tamMax) {
            if (linhatamn) strcat(textoAdd," ");
            strcat(textoAdd,msg);
            linhatamn+=w+((!linhatamn)?0:espaco);
            add=1;
          }
          else {
            if (!linhatamn) {
              if (w > tamMax) {
                int ante=0;
                char temp;
                cont/=2;
                while (1) {
                  temp=msg[cont];
                  msg[cont]='\0';

                  w=larguraTexto(fonte,"%s",msg);

                  msg[cont]=temp;

                  if (w > tamMax) {
                    if (ante>=0) {
                      cont--;
                      ante=-2;
                      continue;
                    }
                    else ante=0;
                    cont/=2;
                  }
                  else if ((w < tamMax) && (ante >= 0)) {
                    ante=w;
                    cont++;
                  }
                  else {
                    subest=temp;
                    msg[cont]='\0';
                    tamanho=strlen(msg);
                    strcpy(textoAdd,msg);
                    msg[conttemp]=' ';
                    break;
                  }
                }
                add=1;
              }
            }

            ListString_adiciona(&primString,"%s",textoAdd);
            textoAdd[0]='\0';
            linhatamn=0;
          }
        } while(!add);

        msg[cont]=subest;
        msg=msg+tamanho;

        cont=0;
      }
    }

    ListString_adiciona(&primString,"%s",textoAdd);
  }

  ListString_limpa(&textoSlipt);
  return primString;
}

char *String_ReplaceAll(char *str, char *old, char *snew) {
  int i, count = 0;
  int newlen = strlen(snew);
  int oldlen = strlen(old);

  for (i = 0; str[i]; ++i)
    if (strstr(&str[i], old) == &str[i])
      ++count, i += oldlen - 1;

  char *ret = (char *) calloc(i + 1 + count * (newlen - oldlen), sizeof(char));
  if (!ret) return NULL;

  i = 0;
  while (*str)
    if (strstr(str, old) == str)
      strcpy(&ret[i], snew),
      i += newlen,
      str += oldlen;
    else
      ret[i++] = *str++;

  ret[i] = '\0';

  return ret;
}

char *String_Param(char *str, char *param) {
  char *ret=NULL;
  if ((param == NULL) || (param[0] == '\0')) {
    ret=calloc(strlen(str)+1, sizeof(char));
    strcpy(ret, str);
  }
  else {
    char *ant=NULL;
    char prmStr[5];
    int cont=1;

    ret=str;
    ListString listStr=ListString_split(param,"#");

    forList (char *, strQuebrada, listStr) {
      sprintf(prmStr,"<%d>",cont++);

      ret=String_ReplaceAll(ret,prmStr,strQuebrada);
      if (ant != NULL) free(ant);
      ant=ret;
    }

    ListString_limpa(&listStr);
  }

  return ret;
}

void putpixel(SDL_Surface *surface, int x, int y, Uint32 pixel) {
    int bpp = surface->format->BytesPerPixel;
    /* Here p is the address to the pixel we want to set */
    Uint8 *p = (Uint8 *)surface->pixels + y * surface->pitch + x * bpp;

    switch(bpp) {
    case 1:
        *p = pixel;
        break;

    case 2:
        *(Uint16 *)p = pixel;
        break;

    case 3:
        if(SDL_BYTEORDER == SDL_BIG_ENDIAN) {
            p[0] = (pixel >> 16) & 0xff;
            p[1] = (pixel >> 8) & 0xff;
            p[2] = pixel & 0xff;
        } else {
            p[0] = pixel & 0xff;
            p[1] = (pixel >> 8) & 0xff;
            p[2] = (pixel >> 16) & 0xff;
        }
        break;

    case 4:
        *(Uint32 *)p = pixel;
        break;
    }
}

Uint32 getpixel(SDL_Surface *surface, int x, int y) {
  int bpp=surface->format->BytesPerPixel;
  /* Here p is the address to the pixel we want to retrieve */
  Uint8 *p=(Uint8 *) surface->pixels + y * surface->pitch + x * bpp;

  switch (bpp) {
  case 1:
    return *p;

  case 2:
    return *(Uint16 *) p;

  case 3:
    if (SDL_BYTEORDER == SDL_BIG_ENDIAN)
      return p[0] << 16 | p[1] << 8 | p[2];
    else
      return p[0] | p[1] << 8 | p[2] << 16;

  case 4:
    return *(Uint32 *) p;

  default:
    return 0; /* shouldn't happen, but avoids warnings */
  }
}

int mouseverondeclia(int tx, int tx2, int ty, int ty2) {
  return ((mousemovidox >= tx && mousemovidox <= tx2) && (mousemovidoy >= ty && mousemovidoy <= ty2));
}
