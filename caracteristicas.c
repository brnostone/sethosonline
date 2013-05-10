#include <stdio.h>
#include <string.h>

#include "Header/magicas.h"
#include "Header/caracteristicas.h"

//TODO: Remover tudo isto e usar arquivo com o editor

int tamanhoObjetos(char tipo,char oq) {
  int retorno=0;

  if (tipo==1) {
    if (oq=='x') retorno=64;
    else if (oq=='y') retorno=71;
    else if ((oq=='w') || (oq=='h')) retorno=128;
  }
  else if (tipo==2) {
    if (oq=='x') retorno=30;
    else if (oq=='y') retorno=78;
    else if ((oq=='w') || (oq=='h')) retorno=128;
  }
  else if (tipo==3) {
    if (oq=='x') retorno=0;
    else if (oq=='y') retorno=70;
    else if (oq=='w') retorno=64;
    else if (oq=='h') retorno=96;
  }
  else if (tipo==4) {
    if (oq=='x') retorno=0;
    else if (oq=='y') retorno=75;
    else if (oq=='w') retorno=96;
    else if (oq=='h') retorno=128;
  }
  else if (tipo==5) {
    if (oq=='x') retorno=0;
    else if (oq=='y') retorno=48;
    else if (oq=='w') retorno=96;
    else if (oq=='h') retorno=96;
  }
  else if (tipo==6) {
    if (oq=='x') retorno=0;
    else if (oq=='y') retorno=24;
    else if (oq=='w') retorno=64;
    else if (oq=='h') retorno=64;
  }
  else if (tipo==7) {
    if (oq=='x') retorno=64;
    else if (oq=='y') retorno=70;
    else if (oq=='w') retorno=128;
    else if (oq=='h') retorno=96;
  }
  return retorno;
}

int tamanhoParedes(int tipo,char oq) {
  int retorno=0;
  if (tipo==1) {
    if (oq=='x') retorno=0;
    else if (oq=='y') retorno=105;
    else if (oq=='w') retorno=64;
    else if (oq=='h') retorno=160;
  }
  if (tipo==2) {
    if (oq=='x') retorno=0;
    else if (oq=='y') retorno=141;
    else if (oq=='w') retorno=64;
    else if (oq=='h') retorno=196;
  }
  if (tipo==3) {
    if (oq=='x') retorno=0;
    else if (oq=='y') retorno=115;
    else if (oq=='w') retorno=64;
    else if (oq=='h') retorno=170;
  }
  return retorno;
}

int tamanhoCasa(char tipo,char oq) {
  int retorno=0;
  if (tipo==1) {
    if (oq=='x') retorno=114;
    else if (oq=='y') retorno=135;
    else if (oq=='w') retorno=178;
    else if (oq=='h') retorno=183;
  }
  else if (tipo==2) {
    if (oq=='x') retorno=184;
    else if (oq=='y') retorno=140;
    else if (oq=='w') retorno=248;
    else if (oq=='h') retorno=236;
  }
  return retorno;
}

int tamanhoInteracao(char tipo,char oq) {
  int retorno=0;
  if (tipo==1) {
    if (oq=='x') retorno=0;
    else if (oq=='y') retorno=20;
    else if (oq=='w') retorno=64;
    else if (oq=='h') retorno=64;

//referente a area de atuacao da Interacao
    else if (oq=='a') retorno=0; //mais x
    else if (oq=='b') retorno=0; //mais y
    else if (oq=='q') retorno=4; //quadrados
  }
  else if (tipo==2) {
    if (oq=='x') retorno=16;
    else if (oq=='y') retorno=36;
    else if (oq=='w') retorno=96;
    else if (oq=='h') retorno=96;

    else if (oq=='a') retorno=-1; //mais x
    else if (oq=='b') retorno=-1; //mais y
    else if (oq=='q') retorno=8; //quadrados
  }
  return retorno;
}

void nomedasmagicas(char opcao, char qual, char *nomeMagic) {
  //Nome
  if (opcao==1) {
    if (qual==1) strcpy(nomeMagic,"Magica da Neblina");
    else if (qual==2) strcpy(nomeMagic,"Magica do Fogo");
    else if (qual==3) strcpy(nomeMagic,"Magica do Fogo Azul");
    else if (qual==4) strcpy(nomeMagic,"Magica da Bola de Energia");
    else if (qual==5) strcpy(nomeMagic,"Magica do Tornado Folha");
    else if (qual==6) strcpy(nomeMagic,"Magica da Vida");
    else if (qual==7) strcpy(nomeMagic,"Magica da Paz");
  }
  //Mana
  else if (opcao==2) {
  }
  //Dano
  //level
}

int imagemdereset(char qual,char acao) {
  char retorno=0;
  if (qual==1) {
    if ((acao==1) || (acao==2) || (acao==4)) { retorno=8; }
    else if ((acao==3) || (acao==5) || (acao==6)) { retorno=6; }
    else if (acao==7) { retorno=9; }
  }
  else if (qual==2) {
    if ((acao==1) || (acao==2)) { retorno=8; }
    else if ((acao==3) || (acao==5) || (acao==6)) { retorno=6; }
    else if (acao==4) { retorno=12; }
    else if (acao==7) { retorno=9; }
  }
  else if (qual==3) {
    if ((acao==1) || (acao==2)) { retorno=8; }
    else if ((acao==3) || (acao==5) || (acao==6)) { retorno=6; }
    else if (acao==4) { retorno=10; }
    else if (acao==7) { retorno=9; }
  }
  else if (qual==4) {
    if ((acao==1) || (acao==2)) { retorno=8; }
    else if ((acao==3) || (acao==5) || (acao==6)) { retorno=6; }
    else if (acao==4) { retorno=12; }
    else if (acao==7) { retorno=9; }
    else if (acao==8) { retorno=9; }
  }
  else if (qual==5) {
    if ((acao==1) || (acao==2)) { retorno=8; }
    else if ((acao==3) || (acao==5) || (acao==6)) { retorno=6; }
    else if (acao==4) { retorno=12; }
    else if (acao==7) { retorno=9; }
  }
  else if (qual==6) {
    if ((acao==1) || (acao==2)) { retorno=8; }
    else if ((acao==3) || (acao==5) || (acao==6)) { retorno=6; }
    else if (acao==4) { retorno=12; }
    else if (acao==7) { retorno=9; }
  }
  else if (qual==7) {
    if ((acao==1) || (acao==2)) { retorno=8; }
    else if ((acao==3) || (acao==5) || (acao==6)) { retorno=6; }
    else if (acao==4) { retorno=12; }
    else if (acao==7) { retorno=9; }
  }
  return retorno;
}

int monstroimreset(char qual,char acao) {
  char retorno=0;
  if (qual==1) {
    if (acao==0) { retorno=1; }
    else if (acao==2) { retorno=12; }
    else if (acao==4) { retorno=13; }
    else { retorno=8; }
  }
  else if (qual==2) {
    if (acao==0) { retorno=1; }
    else if (acao==3) { retorno=6; }
    else if ((acao==4) || (acao==2)) { retorno=9; }
    else { retorno=8; }
  }
  else if (qual==3) {
    if (acao==0) { retorno=1; }
    else if (acao==4) { retorno=9; }
    else { retorno=8; }
  }
  return retorno;
}

int imagtamonstro(char qual,char acao) {
  int retorno=1;
  if (qual==1) { retorno=((acao==4)?2:1); }
  else if (qual==2) { retorno=1; }
  else if (qual==3) { retorno=1; }
  else if (qual==4) { retorno=2; }
  return retorno;
}

int imagemtamanho(char qual,char acao) {
  int retorno=0;
  if (qual==1) retorno=1;
  else if (qual==2) retorno=1;
//  else if (qual==2) { if ((personagem.acao!=4) && (personagem.acao!=7)) { retorno=1; } else { retorno=2; } }
  else if (qual==3) retorno=1;
  else if (qual==4) retorno=1;
  else if (qual==5) retorno=1;
  else if (qual==6) retorno=1;
  else if (qual==7) retorno=1;
  return retorno;
}

int Info_Magic(int tipo,char oq) {
  int retorno=0;
  //Magica da Neblina
  if (tipo==1) {
    if (oq=='w') { retorno=96; }      //tamanho w
    else if (oq=='h') { retorno=96; } //tamanho h
    else if (oq=='n') { retorno=15; } //numero de imagens

    else if (oq=='k') { retorno=0; }  //velocidade do dano *100mm

    else if (oq=='x') { retorno=40; } //prioridade x
    else if (oq=='y') { retorno=96; } //prioridade y
    else if (oq==1) { retorno=48; }   //adicional na inicialização do x
    else if (oq==2) { retorno=48; }   //adicional na inicialização do y

    else if (oq=='m') { retorno=1; }  //se desaparece ao colidir com mostro
    else if (oq=='p') { retorno=0; }  //se deleta direto quando colide com a parede

    else if (oq=='v') { retorno=15; } //velocidade
    else if (oq=='s') { retorno=0; }  //status inicial do delete

    else if (oq=='t') { retorno=1; }  //tipo
    else if (oq=='i') { retorno=0; }  //imagem de reset delete 0

    else if (oq=='d') { retorno=0; }  //se continua sugando apos delete=1
  }
  //Magica do Fogo
  else if (tipo==2) {
    if (oq=='w') { retorno=34; }      //tamanho w
    else if (oq=='h') { retorno=64; } //tamanho h
    else if (oq=='n') { retorno=59; } //numero de imagens

    else if (oq=='k') { retorno=4; }  //velocidade do dano *100mm

    else if (oq=='x') { retorno=0; }  //prioridade x
    else if (oq=='y') { retorno=81; } //prioridade y
    else if (oq==1) { retorno=0; }    //adicional na inicialização do x
    else if (oq==2) { retorno=0; }    //adicional na inicialização do y

    else if (oq=='m') { retorno=0; }  //se desaparece ao colidir com mostro
    else if (oq=='p') { retorno=1; }  //se deleta direto quando colide com a parede

    else if (oq=='v') { retorno=0; }  //velocidade
    else if (oq=='s') { retorno=1; }  //status inicial do delete

    else if (oq=='t') { retorno=1; }  //tipo
    else if (oq=='i') { retorno=0; }  //imagem de reset delete 0

    else if (oq=='d') { retorno=1; }  //se continua sugando apos delete=1
  }
  //Magica do Fogo Azul
  else if (tipo==3) {
    if (oq=='w') { retorno=24; }      //tamanho w
    else if (oq=='h') { retorno=64; } //tamanho h
    else if (oq=='n') { retorno=29; } //numero de imagens

    else if (oq=='k') { retorno=2; }  //velocidade do dano *100mm

    else if (oq=='x') { retorno=7; }  //prioridade x
    else if (oq=='y') { retorno=39; } //prioridade y
    else if (oq==1) { retorno=0; }    //adicional na inicialização do x
    else if (oq==2) { retorno=14; }   //adicional na inicialização do y

    else if (oq=='m') { retorno=0; }  //se desaparece ao colidir com mostro
    else if (oq=='p') { retorno=1; }  //se deleta direto quando colide com a parede


    else if (oq=='v') { retorno=15; } //velocidade
    else if (oq=='s') { retorno=1; }  //status inicial do delete

    else if (oq=='t') { retorno=1; }  //tipo
    else if (oq=='i') { retorno=29; }  //imagem de reset delete 0

    else if (oq=='d') { retorno=1; }  //se continua sugando apos delete=1
  }
  //Magica da Bola de Energia
  else if (tipo==4) {
    if (oq=='w') { retorno=20; }      //tamanho w
    else if (oq=='h') { retorno=20; } //tamanho h
    else if (oq=='n') { retorno=6; }  //numero de imagens

    else if (oq=='k') { retorno=0; }  //velocidade do dano *100mm

    else if (oq=='x') { retorno=0; }  //prioridade x
    else if (oq=='y') { retorno=64; } //prioridade y
    else if (oq==1) { retorno=5; }    //adicional na inicialização do x
    else if (oq==2) { retorno=5; }    //adicional na inicialização do y

    else if (oq=='m') { retorno=0; }  //se desaparece ao colidir com mostro
    else if (oq=='p') { retorno=1; }  //se deleta direto quando colide com a parede

    else if (oq=='v') { retorno=15; } //velocidade
    else if (oq=='s') { retorno=0; }  //status inicial do delete

    else if (oq=='t') { retorno=0; }  //tipo
    else if (oq=='i') { retorno=6; }  //imagem de reset delete 0

    else if (oq=='d') { retorno=0; }  //se continua sugando apos delete=1
  }
  //Magica do Tornado Folha
  else if (tipo==5) {
    if (oq=='w') { retorno=64; }      //tamanho w
    else if (oq=='h') { retorno=96; } //tamanho h
    else if (oq=='n') { retorno=23; } //numero de imagens

    else if (oq=='k') { retorno=0; }  //velocidade do dano *100mm

    else if (oq=='x') { retorno=0; }  //prioridade x
    else if (oq=='y') { retorno=64; } //prioridade y
    else if (oq==1) { retorno=30; }   //adicional na inicialização do x
    else if (oq==2) { retorno=36; }   //adicional na inicialização do y

    else if (oq=='m') { retorno=1; }  //se desaparece ao colidir com mostro
    else if (oq=='p') { retorno=1; }  //se deleta direto quando colide com a parede

    else if (oq=='v') { retorno=10; } //velocidade
    else if (oq=='s') { retorno=0; }  //status inicial do delete

    else if (oq=='t') { retorno=0; }  //tipo
    else if (oq=='i') { retorno=23; } //imagem de reset delete 0

    else if (oq=='d') { retorno=0; }  //se continua sugando apos delete=1
  }
  else{
    if ((magicatual!=NULL) && (!magicatual->deletar)) {
      magicatual->deletar=1;
      printf("Deletar\n");
    }
  }
  return retorno;
}


int Info_Colid_Magic(int tipo,char cat,char oq) {
  int retorno=0;
  //Magica da Neblina
  if (tipo==1) {
    //meio da Area de Colisao
    if (cat=='m') {
      if (oq=='x') retorno=3;
      else if (oq=='y') retorno=6;
    }
    //Area de Colisao
    else if (cat=='t') {
      if (oq=='x') retorno=1;
      else if (oq=='y') retorno=0;
    }
  }
  //Magica do Fogo
  else if (tipo==2) {
    //meio da Area de Colisao
    if (cat=='m') {
      if (oq=='x') retorno=1;
      else if (oq=='y') retorno=3;
    }
    //Area de Colisao
    else if (cat=='t') {
      if (oq=='x') retorno=1;
      else if (oq=='y') retorno=0;
    }
  }
  //Magica do Fogo Azul
  else if (tipo==3) {
    //meio da Area de Colisao
    if (cat=='m') {
      if (oq=='x') retorno=0;
      else if (oq=='y') retorno=2;
    }
    //Area de Colisao
    else if (cat=='t') {
      if (oq=='x') retorno=0;
      else if (oq=='y') retorno=0;
    }
    else if (cat=='a') {
      if (oq=='x') retorno=10;
    }
  }
  //Magica da Bola de Energia
  else if (tipo==4) {
    //meio da Area de Colisao
    if (cat=='m') {
      if (oq=='x') retorno=0;
      else if (oq=='y') retorno=0;
    }
    //Area de Colisao
    else if (cat=='t') {
      if (oq=='x') retorno=0;
      else if (oq=='y') retorno=0;
    }
  }
  //Magica do Tornado Folha
  else if (tipo==5) {
    //meio da Area de Colisao
    if (cat=='m') {
      if (oq=='x') retorno=2;
      else if (oq=='y') retorno=5;
    }
    //Area de Colisao
    else if (cat=='t') {
      if (oq=='x') retorno=1;
      else if (oq=='y') retorno=1;
    }
  }
  return retorno;
}
