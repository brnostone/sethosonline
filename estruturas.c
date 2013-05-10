#include <stdio.h>
#include <stdlib.h>

#include "Header/estruturas.h"

void arrumar_lista(Lista *l) {
  int novo_id=1;
  for (; l!=NULL; l=l->prox) {
    l->id=novo_id++;
  }
}

void *lista_acao(char acao, Lista **prim_lista, int id, int opcao, int tamanho) {
  Lista *atual_lista=NULL;

  if (id<=0) {
    printf("ERRO: Id lista\n");
    exit(0);
  }

  if (acao=='n') {
    if (opcao&ADD_CERTO) {
      atual_lista = (Lista *) malloc(sizeof(Lista));
      atual_lista->d = (void *) malloc(tamanho);
      atual_lista->id = id;
      atual_lista->prox = NULL;

      if (*prim_lista!=NULL) {
        Lista *t=*prim_lista;
        while (t->prox!=NULL) t=t->prox;

        t->prox=atual_lista;
      }
      else *prim_lista=atual_lista;
    }
    else {
      atual_lista = (Lista *) malloc(sizeof(Lista));
      atual_lista->d = (void *) malloc(tamanho);
      atual_lista->id = id;
      atual_lista->prox = *prim_lista;
      *prim_lista=atual_lista;
    }
    if (opcao&MUDAR_ID) arrumar_lista(*prim_lista);
  }
  else if (acao=='d') {
    Lista *ant = NULL;        /*  ponteiro para elemento anterior */
    Lista *p = *prim_lista;   /* ponteiro para percorrer a lista*/
    /* procura elemento na lista, guardando anterior */
    while ((p != NULL) && (p->id != id)) {
       ant = p;
       p = p->prox;
    }
    /* verifica se achou elemento */
    if (p == NULL)
       return NULL;
    /* retira elemento */
    if (ant == NULL) {
       /* retira elemento do inicio */
       *prim_lista = p->prox;
    }
    else {
       /* retira elemento do meio da lista */
       ant->prox = p->prox;
    }
    free(p->d);
    p->d=NULL;
    free(p);
    p=NULL;
    atual_lista=*prim_lista;

    if (opcao&MUDAR_ID) arrumar_lista(*prim_lista);
  }
  else if (acao=='s') {
    for (atual_lista=*prim_lista; atual_lista!=NULL; atual_lista=atual_lista->prox) {
      if (atual_lista->id == id) {
        return atual_lista->d;
      }
    }

    if (opcao&MUDAR_ID) arrumar_lista(*prim_lista);

    atual_lista=NULL;
  }
  else printf("ERRO: Opção invalida lista\n");

  if (atual_lista != NULL)
    return atual_lista->d;
  else
    return NULL;
}

void arrumar_listaDupla(ListaDupla *l) {
  int novo_id=1;
  for (; l!=NULL; l=l->prox) {
    l->id=novo_id++;
  }
}

void *listaDupla_acao(char acao, ListaDupla **prim_lista, int id, int opcao, int tamanho) {
  ListaDupla *atual_lista=NULL;

  if (id<=0) {
    printf("ERRO: Id lista\n");
    exit(0);
  }

  if (acao=='n') {
    if (opcao&ADD_CERTO) {
      atual_lista = (ListaDupla *) malloc(sizeof(ListaDupla));
      atual_lista->d = (void *) malloc(tamanho);
      atual_lista->id = id;
      atual_lista->prox = NULL;

      if (*prim_lista!=NULL) {
        ListaDupla *t=*prim_lista;
        while (t->prox!=NULL) t=t->prox;

        t->prox=atual_lista;

        atual_lista->ant=t;
        (*prim_lista)->ant=atual_lista;
      }
      else {
        atual_lista->ant=atual_lista;
        *prim_lista=atual_lista;
      }
    }
    else {
      atual_lista = (ListaDupla *) malloc(sizeof(ListaDupla));
      atual_lista->d = (void *) malloc(tamanho);
      atual_lista->id = id;
      atual_lista->prox = *prim_lista;

      if (*prim_lista != NULL) {
        atual_lista->ant=(*prim_lista)->ant;
        (*prim_lista)->ant=atual_lista;
      }
      else
        atual_lista->ant=atual_lista;

      *prim_lista=atual_lista;
    }

    if (opcao&MUDAR_ID) arrumar_listaDupla(*prim_lista);
  }
  else if (acao=='d') {
    ListaDupla *proxElmt = NULL;
    ListaDupla *ant = NULL;        /*  ponteiro para elemento anterior */
    ListaDupla *p = *prim_lista;   /* ponteiro para percorrer a lista*/
    /* procura elemento na lista, guardando anterior */
    while ((p != NULL) && (p->id != id)) {
       ant = p;
       p = p->prox;
    }
    /* verifica se achou elemento */
    if (p == NULL)
       return NULL;
    /* retira elemento */
    if (ant == NULL) {
      /* retira elemento do inicio */
      proxElmt=p->prox;

      if (proxElmt != NULL)
        proxElmt->ant = p->ant;

      *prim_lista = proxElmt;
    }
    else {
      /* retira elemento do meio ou fim da lista */

      proxElmt=p->prox;

      /* verifica se é do fim */
      if (proxElmt == NULL)
        (*prim_lista)->ant=p->ant;
      else
        proxElmt->ant=ant;

      ant->prox = proxElmt;
    }

    free(p->d);
    p->d=NULL;

    free(p);
    p=NULL;
    atual_lista=*prim_lista;

    if (opcao&MUDAR_ID) arrumar_listaDupla(*prim_lista);
  }
  else if (acao=='s') {
    for (atual_lista=*prim_lista; atual_lista!=NULL; atual_lista=atual_lista->prox) {
      if (atual_lista->id == id) {
        return atual_lista->d;
      }
    }

    if (opcao&MUDAR_ID) arrumar_listaDupla(*prim_lista);

    atual_lista=NULL;
  }
  else if (acao=='u') {
    ListaDupla *ultElmt = NULL;

    int idTmp;
    void *dTmp;

    for (atual_lista=*prim_lista; atual_lista!=NULL; atual_lista=atual_lista->prox) {
      if (atual_lista->id == id) {
        ultElmt=(*prim_lista)->ant;

        if (ultElmt->id != atual_lista->id) {
          dTmp=atual_lista->d;
          idTmp=atual_lista->id;

          atual_lista->d=ultElmt->d;
          atual_lista->id=ultElmt->id;

          ultElmt->d=dTmp;
          ultElmt->id=idTmp;
        }

        return ultElmt->d;
      }
    }

    if (opcao&MUDAR_ID) arrumar_listaDupla(*prim_lista);

    atual_lista=NULL;
  }
  else printf("ERRO: Opção invalida lista\n");

  if (atual_lista != NULL)
    return atual_lista->d;
  else
    return NULL;
}

void limpaPilha(PILHA_S *p) {
  int percorre=0;
  for (percorre=0; percorre < p->tamanhoMaximo ;percorre++) {
    p->val[percorre]=NULL;
  }
  p->topo=0;
}

PILHA_S *cria_pilha(int tamanho) {
  PILHA_S *p=(PILHA_S *) malloc(sizeof(PILHA_S));
  p->val=(void **) calloc(tamanho,sizeof(void *));
  p->topo=0;
  p->tamanhoMaximo=tamanho;
  return p;
}

void empilha(PILHA_S *p,void *dado) {
  if (p->topo < p->tamanhoMaximo)
    p->val[p->topo++]=dado;
  else
    printf("Estorou pilha\n");
}

void *desempilha(PILHA_S *p) {
  if (p->topo>0)
    return p->val[--p->topo];
  else
    return NULL;
}
