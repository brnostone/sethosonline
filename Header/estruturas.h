#ifndef ESTRUTURAS_H_
#define ESTRUTURAS_H_

#define MUDAR_ID 1
#define NAO_MUDAR_ID 0

#define ADD_CERTO 2

typedef struct lista {
  int id;
  void *d;
  struct lista *prox;
} Lista;

typedef struct listaDupla {
  int id;
  void *d;
  struct listaDupla *prox;
  struct listaDupla *ant;
} ListaDupla;


struct pilhaElement {
  struct componentes *atualComp;
  ListaDupla *primComp;
};

typedef struct {
  void **val;
  int topo;
  int tamanhoMaximo;
} PILHA_S;


void *lista_acao(char acao, Lista **prim_lista, int id, int opcao, int tamanho);
void *listaDupla_acao(char acao, ListaDupla **prim_lista, int id, int opcao, int tamanho);

void limpaPilha(PILHA_S *p);
PILHA_S *cria_pilha(int tamanho);

void empilha(PILHA_S *p,void *dado);
void *desempilha(PILHA_S *p);

#endif /* ESTRUTURAS_H_ */

