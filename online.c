#include "Header/global.h"
#include "Header/guiitens.h"
#include "Header/equipamentos.h"
#include "Header/pesca.h"
#include "Header/personagem.h"
#include "Header/npcs.h"
#include "Header/monstros.h"
#include "Header/animais.h"
#include "Header/mapas.h"
#include "Header/flechas.h"
#include "Header/magicas.h"
#include "Header/online.h"

void addtemporariamente() {
  colocaritem(0,0,1,3,1,1);
  colocaritem(2,0,1,2,1,1);

  colocaritem(4,0,4,1,1,1);
  colocaritem(5,0,5,2,1,1);
  colocaritem(6,0,6,3,1,1);

  colocaritem(4,2,3,2,1,1);
  colocaritem(0,4,7,2,1,1);
  colocaritem(1,4,8,2,1,1);
  colocaritem(2,4,16,1,1,1);


  itemlocalrapido[0][0]=4;
  itemlocalrapido[1][0]=240;

  itemlocalrapido[0][1]=4;
  itemlocalrapido[1][1]=30;

  itemlocalrapido[0][2]=1;
  itemlocalrapido[1][2]=1;

  itemlocalrapido[0][3]=2;
  itemlocalrapido[1][3]=1;

  itemlocalrapido[0][5]=14;
  itemlocalrapido[1][5]=1;

  itemlocalrapido[0][6]=20;
  itemlocalrapido[1][6]=1;
  itemlocalrapido[0][7]=21;
  itemlocalrapido[1][7]=1;

  meusstatsua.forca=30;
  meusstatsua.agilidade=20;
  meusstatsua.inteligencia=22;
  meusstatsua.vitalidade=40;
  meusstatsua.dinheiro=280;
  meusstatsua.experiencia=0;
  meusstatsua.nextlevelexp=0;
  meusstatsua.level=1;
  meusstatsua.pontos=0;

  equipamentos.helm[0]=7;
  equipamentos.armor[0]=3;
  equipamentos.amuleto[0]=3;
  equipamentos.capa[0]=4;
  equipamentos.mao1[0]=0;
  equipamentos.mao2[0]=0;
  equipamentos.mao1tipo=0;
  equipamentos.mao2tipo=0;
  equipamentos.anel1[0]=2;
  equipamentos.anel2[0]=5;
  equipamentos.braco1[0]=1;
  equipamentos.braco2[0]=2;
  equipamentos.luvas[0]=2;
  equipamentos.botas[0]=1;

  personagem.qual=1;
  personagem.acao=0;
  personagem.lado=2;
  personagem.vida=100;
  personagem.nome="Tronix\0";
  personagem.guild="[GM's]\0";
  personagem.type=0;
  personagem.aura=0;
  personagem.auraimagem=0;
  personagem.levelup=-1;
  personagem.balao.ativo=0;
  personagem.pathFind.dest=NULL;
  personagem.pathFind.tipo=PATH_TIPO_PERSONAGEM;
  personagem.pathFind.interacao_id=-1;
}

void objets_mapas(int qual) {
  if (qual == 1) {
  // Esqueleto
    criar_monstros(742,637,2,6,0);
    criar_monstros(1005,702,2,6,0);
    criar_monstros(1005,702,2,6,0);
    criar_monstros(2002,358,2,6,0);
    criar_monstros(1679,557,2,6,0);
    criar_monstros(1263,826,2,6,0);
  // Lobo Marrom

    criar_monstros(2100,1600,3,6,0);
    criar_monstros(2080,1100,3,6,0);
    criar_monstros(1461,476,3,6,0);
    criar_monstros(1889,479,3,6,0);
    criar_monstros(1004,806,3,6,0);
    criar_monstros(1355,1052,3,6,0);
  // Orc
    criar_monstros(1287,192,1,6,0);
    criar_monstros(1546,145,1,6,0);
    criar_monstros(139,139,1,6,0);

  //RATO
    Criar_Animal(100,100,2,0,1);
    Criar_Animal(000,750,4,0,1);
    Criar_Animal(000,550,1,0,1);

    npcs[0].ativo=1;
    npcs[0].tipo=1;
    npcs[0].posx=506;
    npcs[0].posy=208;
    npcs[0].imagem=0;
    npcs[0].acao=0;
    npcs[0].lado=0;
    npcs[0].timetempo=0;

    npcs[1].ativo=1;
    npcs[1].tipo=2;
    npcs[1].posx=965;
    npcs[1].posy=1565;
    /*npcs[1].posx=100;
    npcs[1].posy=155;*/
    npcs[1].imagem=0;
    npcs[1].acao=7;
    npcs[1].lado=7;
    npcs[1].timetempo=0;

    npcs[2].ativo=1;
    npcs[2].tipo=3;
    npcs[2].posx=792;
    npcs[2].posy=416;
    npcs[2].imagem=0;
    npcs[2].acao=0;
    npcs[2].lado=0;
    npcs[2].timetempo=0;

    npcs[3].ativo=1;
    npcs[3].tipo=4;
    npcs[3].posx=165;
    npcs[3].posy=390;
    npcs[3].imagem=0;
    npcs[3].acao=0;
    npcs[3].lado=0;
    npcs[3].timetempo=0;

    boias[0].ativa=1;
    boias[0].x=905;
    boias[0].y=1690;
    boias[0].imagem=0;
    boias[0].idquem=0;
    boias[0].acao=1;

    itenschao[0][1][1]=4;
    itenschao[1][1][1]=2;
    itenschao[0][2][2]=6;
    itenschao[1][2][2]=5;
  }
  else if (qual == 2) {
    criar_monstros(424,464,2,6,0);
    criar_monstros(1048,560,2,6,0);
    criar_monstros(1064,944,2,6,0);

    criar_monstros(792,256,1,6,0);

    npcs[0].ativo=0;
    npcs[1].ativo=0;
    npcs[2].ativo=0;
    npcs[3].ativo=0;
  }
  else if (qual == 3) {
    criar_monstros(808,208,2,6,0);
    criar_monstros(1048,816,2,6,0);
    criar_monstros(1112,944,1,6,0);
    criar_monstros(920,944,2,6,0);
    criar_monstros(872,960,3,6,0);
    criar_monstros(920,944,2,6,0);
    criar_monstros(1384,240,2,6,0);
    criar_monstros(1528,160,2,6,0);
    criar_monstros(1736,864,3,6,0);

    npcs[0].ativo=0;
    npcs[1].ativo=0;
    npcs[2].ativo=0;
    npcs[3].ativo=0;
  }
  else {
    while (arrowacao(1,'s')) { arrowacao(1,'d'); }
    while (magicacao(1,'s')) { magicacao(1,'d'); }
    while (animalacao(1,'s')) { animalacao(1,'d'); }
    monsterlacao(1,'z');

    npcs[0].ativo=0;
    npcs[1].ativo=0;
    npcs[2].ativo=0;
    npcs[3].ativo=0;
  }
}
