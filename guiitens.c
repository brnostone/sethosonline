#include <stdio.h>

#include "Header/equipamentos.h"
#include "Header/guiitens.h"

  int itens[7][7]={
    {0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0}
  };

  int vendetrocatemp[7][7]={
    {0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0}
  };

  int itensbau[14][7]={
    {0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0}
  };

// GUI: Inventario

void colocaritem(char x,char y,int type,int qual,int add,char opcao) {
  if (x>6) x=6;
  if (opcao==3) {
    if (y>13) y=13;
  }
  else if (y>6) y=6;

  int *local=NULL,percorrey,percorrex;

  numeroitem[opcao-1]++;

  if (opcao==1)
    local=&itemnumeroeh[numeroitem[0]][0];
  else if (opcao==2)
    local=&itemvende_temp[numeroitem[1]][0];
  else if (opcao==3)
    local=&itembau_numero[numeroitem[2]][0];

  local[0]=type;
  local[1]=qual;
  local[2]=add;

  for (percorrey=y; percorrey<=sizearmos(type,'y')+y ;percorrey++) {
    for (percorrex=x; percorrex<=sizearmos(type,'x')+x ;percorrex++) {
      if (opcao==1) { itens[percorrey][percorrex]=numeroitem[0]; }
      else if (opcao==2) { vendetrocatemp[percorrey][percorrex]=numeroitem[1]; }
      else if (opcao==3) { itensbau[percorrey][percorrex]=numeroitem[2]; }
    }
  }
}

int checarsecabe(char x,char y,char w,char h,char qual) {
  int percorrey,percorrex,quant=0,ante=0;
  if ((x+w>=7) || (y+h>=((qual==3)?14:7)) || (x<0) || (y<0)) return 2;

  for (percorrey=y; percorrey<=h+y ;percorrey++) {
    for (percorrex=x; percorrex<=w+x ;percorrex++) {
      if (qual==1) {
        if (itens[percorrey][percorrex]) {
          if (ante!=itens[percorrey][percorrex])
            quant++;
          ante=itens[percorrey][percorrex];
          numeroitennm2=ante;
        }
      }
      else if (qual==2) {
        if (vendetrocatemp[percorrey][percorrex]) {
          if (ante!=vendetrocatemp[percorrey][percorrex])
            quant++;
          ante=vendetrocatemp[percorrey][percorrex];
          numeroitennm2=ante;
        }
      }
      else if (qual==3) {
        if (itensbau[percorrey][percorrex]) {
          if (ante!=itensbau[percorrey][percorrex])
            quant++;
          ante=itensbau[percorrey][percorrex];
          numeroitennm2=ante;
        }
      }
    }
  }
  return quant;
}

void retiraritem(int numero,int opcao) {
  int ppppy,pppph,ppppx,tempeaes;

  pppph=((opcao==3)?14:7);

  for (ppppy=0;ppppy<pppph;ppppy++) {
    for (ppppx=0;ppppx<7;ppppx++) {
      if (opcao==1) {
        if (itens[ppppy][ppppx]==numero) {
          itemnumeroeh[itens[ppppy][ppppx]][0]=0;
          itemnumeroeh[itens[ppppy][ppppx]][1]=0;
          itemnumeroeh[itens[ppppy][ppppx]][2]=0;
          itens[ppppy][ppppx]=0;
        }
      }
      else if (opcao==3) {
        if (itensbau[ppppy][ppppx]==numero) {
          itembau_numero[itensbau[ppppy][ppppx]][0]=0;
          itembau_numero[itensbau[ppppy][ppppx]][1]=0;
          itembau_numero[itensbau[ppppy][ppppx]][2]=0;
          itensbau[ppppy][ppppx]=0;
        }
      }
    }
  }

  for (tempeaes=numero;tempeaes<=numeroitem[opcao-1];tempeaes++) {
    for (ppppy=0;ppppy<pppph;ppppy++) {
      for (ppppx=0;ppppx<7;ppppx++) {
        if (opcao==1) {
          if (itens[ppppy][ppppx]==tempeaes) {
            itemnumeroeh[itens[ppppy][ppppx]-1][0]=itemnumeroeh[itens[ppppy][ppppx]][0];
            itemnumeroeh[itens[ppppy][ppppx]-1][1]=itemnumeroeh[itens[ppppy][ppppx]][1];
            itemnumeroeh[itens[ppppy][ppppx]-1][2]=itemnumeroeh[itens[ppppy][ppppx]][2];
            itens[ppppy][ppppx]--;
          }
        }
        else if (opcao==3) {
          if (itensbau[ppppy][ppppx]==tempeaes) {
            itembau_numero[itensbau[ppppy][ppppx]-1][0]=itembau_numero[itensbau[ppppy][ppppx]][0];
            itembau_numero[itensbau[ppppy][ppppx]-1][1]=itembau_numero[itensbau[ppppy][ppppx]][1];
            itembau_numero[itensbau[ppppy][ppppx]-1][2]=itembau_numero[itensbau[ppppy][ppppx]][2];
            itensbau[ppppy][ppppx]--;
          }
        }
      }
    }
  }
  numeroitem[opcao-1]--;
}

int colocaritem_procurar(int tipo, int qual, int add) {
  int percorreX,percorreY;
  for (percorreY=0;percorreY<7;percorreY++) {
    for (percorreX=0;percorreX<7;percorreX++) {
      if (checarsecabe(percorreX,percorreY,sizearmos(tipo,'x'),sizearmos(tipo,'y'),1)==0) {
        colocaritem(percorreX,percorreY,tipo,qual,add,1);
        return 1;
      }
    }
  }
  return 0;
}
//GUI: Chat
/*
void lermsg() {
  if (numeroitnes>5) {
    FILE *fp2;
    int quantidadeitens;
    if ((fp2 = fopen("Data/chat.log", "rb" )) == NULL) {
      printf("Erro ao abrir o arquivo: %s\n","Data/chat.log");
      exit(1);
    }
    else {
      fseek( fp2, 61*barrarolation, SEEK_SET );
      if (fp2) {
        for (quantidadeitens=0;(!feof(fp2)) && (quantidadeitens<5);quantidadeitens++) {
          fread(nicktemp[4-quantidadeitens], 11, 1, fp2);
          fread(msgtemp[4-quantidadeitens], 50, 1, fp2);
        }
        if (feof(fp2)) { quantidadeitens--; }
      }
      fclose( fp2 );
    }
  }
}*/

/*void drawmsg(int qual,char oqfazer) {
  if (oqfazer==1) {
    int testsa;
    for (testsa=0;testsa<4;testsa++) {
      mensagensmost[testsa]=mensagensmost[testsa+1];
    }
    if (qual==4) {
      for (testsa=4;testsa>0;testsa--) {
        strcpy(nicktemp[testsa],nicktemp[testsa-1]);
        strcpy(msgtemp[testsa],msgtemp[testsa-1]);
      }
    }
    mensagensmost[4]=qual;
    if (qual==4) {
      strcpy(nicktemp[0],personagem.nome);
      strcpy(msgtemp[0],chatstr);
      FILE *fp2;
      if ((fp2 = fopen("Data/chat.log", "ab" )) == NULL) {
        printf("Erro ao abrir o arquivo: %s\n","Data/chat.log");
        exit(1);
      }
      else {
        fseek( fp2, 0, SEEK_END );
        fwrite(nicktemp[0], 11, 1, fp2);
        fwrite(msgtemp[0], 50, 1, fp2);
        //barraposver=100;
        numeroitnes++;
        //if (numeroitnes>5) { barrarolation=numeroitnes-5; } else { barrarolation=0; }
        //barrarolation2=barrarolation;
        fclose( fp2 );
      }
    }
  }
  else {
    if (mensagensmost[qual]==2) { DrawText(font,0,0,0,255,0,((charmenuon)?229:5),16*qual+5,"Foto salva [Fotos/foto%d.bmp]",nfoto); DrawText(font,109,184,230,255,0,((charmenuon)?228:4),16*qual+4,"Foto salva [Fotos/foto%d.bmp]",nfoto); }
      else if (mensagensmost[qual]==4) {
      if (janechaton==0) {
        char tempmsg[256];
        int w2;

        DrawText(font,0,0,0,255,0,((charmenuon)?229:5),15*qual+5,"<%s> %s",nicktemp[qualmsnapa],msgtemp[qualmsnapa]);

        sprintf(tempmsg,"<%s> ",nicktemp[qualmsnapa]);

        DrawText(font,220,220,220,255,0,((charmenuon)?228:4),15*qual+4,"%s",tempmsg);

        TTF_SizeText(font,tempmsg,&w2,NULL);

        Draw_TextEmo(font,220,220,220,255,0,((charmenuon)?228:4)+w2,15*qual+4,"%s",msgtemp[qualmsnapa]);
        qualmsnapa++;
      }
    }
//    else if (mensagensmost[qual]==5) { DrawText(font,0,0,0,0,0,((charmenuon==1)?229:5),16*qual+5,"Comando inexistente."); DrawText(font,250,112,78,0,0,((charmenuon==1)?228:4),16*qual+4,"Comando inexistente."); }
  }
}*/
