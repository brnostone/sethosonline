#ifndef UTIL_H_
#define UTIL_H_

  #include <stdarg.h>
  #include <SDL/SDL.h>

  #include "fonte.h"
  #include "estruturas.h"

  #define forList(Tipo, Var, primListaPer) \
    Tipo Var=NULL; \
    Lista *Var##Percorre; \
    int Var##_Id; \
    for (Var##Percorre=primListaPer; (Var##Percorre!=NULL) && (Var = (Tipo) Var##Percorre->d) && (Var##_Id = Var##Percorre->id); Var##Percorre=Var##Percorre->prox)

  #define forListDupla(Tipo, Var, primListaPer) \
    Tipo Var=NULL; \
    ListaDupla *Var##Percorre; \
    int Var##_Id; \
    for (Var##Percorre=primListaPer; (Var##Percorre!=NULL) && (Var = (Tipo) Var##Percorre->d) && (Var##_Id = Var##Percorre->id); Var##Percorre=Var##Percorre->prox)

  typedef Lista * ListString;

  void ListString_adiciona(ListString *listString, char *fmt, ...);
  void ListString_limpa(ListString *listString);
  void ListString_deleta(ListString *listString, int id);
  char *ListString_get(ListString *listString, int id);
  int ListString_tamanho(ListString listString);
  ListString ListString_split(char *texto, char *ch);
  ListString String_quebraTexto(Fonte *fonte, int tamMax, char *fmt, ...);

  char *String_ReplaceAll(char *str, char *old, char *snew);
  char *String_Param(char *str, char *param);

  void putpixel(SDL_Surface *surface, int x, int y, Uint32 pixel);
  Uint32 getpixel(SDL_Surface *surface, int x, int y);

#endif /* UTIL_H_ */

