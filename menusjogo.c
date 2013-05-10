#include "Header/global.h"
#include "Header/opengl.h"
#include "Header/equipamentos.h"
#include "Header/personagem.h"
#include "Header/guiitens.h"
#include "Header/npcs.h"
#include "Header/magicas.h"
#include "Header/caracteristicas.h"
#include "Header/menusjogo.h"

char janechaton=0;
char inventarioon=0;
char charmenuon=0;
char mostrarmenu=0;
char BauMenuOn=0;
char MagicMenuOn=0;

void Draw_Inventario() {
    if (inventarioon) {
      char colocaaura[49];
      int w2,temp_x,temp_y,quant_itens,tipoequip,qualequip,addequip;

      DrawIMG(inventario,578,0,224,600,0,0);

      w2=larguraTexto(font,"%d",meusstatsua.dinheiro);
      DrawText(font,0,0,0,255,1,708-w2,509,"%d",meusstatsua.dinheiro);

      colocaritens();

      // marca os quadrados escuros
      if ((numeroitem[0]>0) || (carregarar==1)) {
        for(temp_y=0;temp_y<7;temp_y++) {
          for(temp_x=0;temp_x<7;temp_x++) {
            if(itens[temp_y][temp_x])
              fillRectangle(temp_x*28+589+temp_x,temp_y*28+296+temp_y,28,28,65,65,65,255);

            if ((carregarar==1) && (mouseverondeclia(588,791,295,498))) {
              if ((temp_x >= (mousemovidox-589)/29) && (temp_x <= (mousemovidox-589)/29+sizearmos(itemnamao[0],'x')) && (temp_y >= (mousemovidoy-296)/29) && (temp_y <= (mousemovidoy-296)/29+sizearmos(itemnamao[0],'y'))) {
                quant_itens=checarsecabe((mousemovidox-589)/29,(mousemovidoy-296)/29,sizearmos(itemnamao[0],'x'),sizearmos(itemnamao[0],'y'),1);

                if (quant_itens) {
                  if (quant_itens==1) fillRectangle(temp_x*28+589+temp_x,temp_y*28+296+temp_y,28,28,100,250,100,255);
                  else fillRectangle(temp_x*28+589+temp_x,temp_y*28+296+temp_y,28,28,250,100,100,255);
                }
                else fillRectangle(temp_x*28+589+temp_x,temp_y*28+296+temp_y,28,28,0,155,255,255);
              }
            }
          }
        }

        //Mostra itens que estao no inventario
        memset(colocaaura, 0, sizeof(colocaaura));
        for(temp_y=0;temp_y<7;temp_y++) {
          for(temp_x=0;temp_x<7;temp_x++) {
            tipoequip=itemnumeroeh[itens[temp_y][temp_x]][0];
            qualequip=itemnumeroeh[itens[temp_y][temp_x]][1];
            addequip=itemnumeroeh[itens[temp_y][temp_x]][2];

            if ((colocaaura[itens[temp_y][temp_x]]==0) && (itens[temp_y][temp_x]!=0)) {
              colocaaura[itens[temp_y][temp_x]]=1;
              itemjuntomouse(589+temp_x*28+2+temp_x,296+temp_y*28+5+temp_y,tipoequip,qualequip,addequip);
            }

            if (equimaent(tipoequip,qualequip,addequip,1,0)) {
              if ((meusstatsua.forca < equimaent(tipoequip,qualequip,addequip,1,1)) || (meusstatsua.agilidade < equimaent(tipoequip,qualequip,addequip,1,2)) || (meusstatsua.vitalidade < equimaent(tipoequip,qualequip,addequip,1,3)) || (meusstatsua.inteligencia < equimaent(tipoequip,qualequip,addequip,1,4)))
                fillRectangle(temp_x*29+588,temp_y*29+295,29,29,250,50,30,62);
            }
          }
        }
      }
    }
}

void Draw_Bau() {
  if (BauMenuOn) {
    int temp_x,temp_y,tipoequip,qualequip,addequip,quant_itens;
    char colocaaura[98];

    DrawIMG(baumenu,355,0,223,537,0,0);
    memset(colocaaura, 0, sizeof(colocaaura));

    // marca os quadrados escuros
    if ((numeroitem[2]>0) || (carregarar==1)) {
      for (temp_y=0; temp_y<14 ;temp_y++) {
        for (temp_x=0; temp_x<7 ;temp_x++) {
          if (itensbau[temp_y][temp_x])
            fillRectangle(temp_x*28+365+temp_x,temp_y*28+64+temp_y,28,28,65,65,65,255);

          if ((carregarar==1) && (mouseverondeclia(364,567,63,469))) {
            if ((temp_x >= (mousemovidox-365)/29) && (temp_x <= (mousemovidox-365)/29+sizearmos(itemnamao[0],'x')) && (temp_y >= (mousemovidoy-64)/29) && (temp_y <= (mousemovidoy-64)/29+sizearmos(itemnamao[0],'y'))) {
              quant_itens=checarsecabe((mousemovidox-365)/29,(mousemovidoy-64)/29,sizearmos(itemnamao[0],'x'),sizearmos(itemnamao[0],'y'),3);

              if (quant_itens) {
                if (quant_itens==1) fillRectangle(temp_x*28+365+temp_x,temp_y*28+64+temp_y,28,28,100,250,100,255);
                else fillRectangle(temp_x*28+365+temp_x,temp_y*28+64+temp_y,28,28,250,100,100,255);
              }
              else fillRectangle(temp_x*28+365+temp_x,temp_y*28+64+temp_y,28,28,0,155,255,255);
            }
          }
        }
      }
      //Mostra icones no bau
      for (temp_y=0; temp_y<14 ;temp_y++) {
        for (temp_x=0; temp_x<7 ;temp_x++) {
          tipoequip=itembau_numero[itensbau[temp_y][temp_x]][0];
          qualequip=itembau_numero[itensbau[temp_y][temp_x]][1];
          addequip=itembau_numero[itensbau[temp_y][temp_x]][2];

          if ((colocaaura[itensbau[temp_y][temp_x]]==0) && (itensbau[temp_y][temp_x]!=0)) {
            colocaaura[itensbau[temp_y][temp_x]]=1;
            itemjuntomouse(365+temp_x*28+2+temp_x,64+temp_y*28+5+temp_y,tipoequip,qualequip,addequip);
          }

          if (equimaent(tipoequip,qualequip,addequip,1,0)) {
            if ((meusstatsua.forca < equimaent(tipoequip,qualequip,addequip,1,1)) || (meusstatsua.agilidade < equimaent(tipoequip,qualequip,addequip,1,2)) || (meusstatsua.vitalidade < equimaent(tipoequip,qualequip,addequip,1,3)) || (meusstatsua.inteligencia < equimaent(tipoequip,qualequip,addequip,1,4)))
              fillRectangle(temp_x*29+364,temp_y*29+63,29,29,250,50,30,62);
          }
        }
      }
    }
  }
  else {
    int qual;
    for (qual=0;qual<NUM_NPCS;qual++) {
      if ((npcs[qual].acao==1) && (npcs[qual].tipo==4)) npcs[qual].acao=2;
    }
  }
}

void Draw_MenuMagica() {
     if (MagicMenuOn) {
       int percorremagic;
       char nomeMagic[256];

       DrawIMG(magicmenu,578,0,224,600,0,0);

       for (percorremagic=0;percorremagic<MagicNumAtual;percorremagic++) {
         if (minhasmagicas[percorremagic].nummagic) {
           DrawIMG(magicasbotao,594,51+percorremagic*60,37,37,(minhasmagicas[percorremagic].nummagic-1)*37,0);
           nomedasmagicas(1,minhasmagicas[percorremagic].nummagic,nomeMagic);
           DrawText(font,250,250,250,255,3,640,51+percorremagic*60,"%s",nomeMagic);
           DrawText(font,250,250,250,255,3,640,63+percorremagic*60,"Level: 1");
           DrawText(font,250,250,250,255,3,640,75+percorremagic*60,"Dano: 4-8");
         }
         else percorremagic=MagicNumAtual;
       }
    }
}

void Draw_CharInfo() {
    if (charmenuon) {
      fillRectangle(18,117,184,10,128,128,128,255);
      fillRectangle(17,117,(meusstatsua.nextlevelexp*185)/(proximolevelexp-(meusstatsua.experiencia-meusstatsua.nextlevelexp)),10,0,128,255,255);
      fillRectangle(17+(meusstatsua.nextlevelexp*185)/(proximolevelexp-(meusstatsua.experiencia-meusstatsua.nextlevelexp)),117,1,10,0,0,0,255);

      DrawIMG(charmenu,0,0,224,600,0,0);

      DrawText(font,250,250,250,255,3,55,41,"%s",personagem.nome);
      DrawText(font,250,250,250,255,3,165,41,"%s",personagem.guild);
      DrawText(font,250,250,250,255,3,63,60,"%d",meusstatsua.level);
      DrawText(font,250,250,250,255,3,63,79,"%s","Mago");
      DrawText(font,250,250,250,255,3,106,98,"%d\\%d",meusstatsua.experiencia,proximolevelexp);

      if (meusstatsua.pontos>0) {
        DrawIMG(BotaoEstilo,167,142,42,18,53,((MAX_FORCA>meusstatsua.forca)?((addbotaoclick==1)?17:0):36));
        DrawIMG(BotaoEstilo,167,172,42,18,53,((MAX_AGILIDADE>meusstatsua.agilidade)?((addbotaoclick==2)?17:0):36));
        DrawIMG(BotaoEstilo,167,202,42,18,53,((MAX_VITALIDADE>meusstatsua.vitalidade)?((addbotaoclick==3)?17:0):36));
        DrawIMG(BotaoEstilo,167,232,42,18,53,((MAX_INTELIGENCIA>meusstatsua.inteligencia)?((addbotaoclick==4)?17:0):36));
      }

      int largura=larguraTexto(font,"%d",meusstatsua.forca);
      DrawText(font,0,0,0,255,1,152-largura,145,"%d",meusstatsua.forca);
      DrawText(font,250,250,250,255,1,26,159,"Dano: 5-8");

      largura=larguraTexto(font,"%d",meusstatsua.agilidade);
      DrawText(font,0,0,0,255,1,152-largura,175,"%d",meusstatsua.agilidade);
      DrawText(font,250,250,250,255,1,26,189,"Velocidade: 45");

      largura=larguraTexto(font,"%d",meusstatsua.vitalidade);
      DrawText(font,0,0,0,255,1,152-largura,205,"%d",meusstatsua.vitalidade);
      DrawText(font,250,250,250,255,1,26,219,"Vida: 100/150");

      largura=larguraTexto(font,"%d",meusstatsua.inteligencia);
      DrawText(font,0,0,0,255,1,152-largura,235,"%d",meusstatsua.inteligencia);
      DrawText(font,250,250,250,255,1,26,249,"Dano Mágico: 15-25");
      DrawText(font,250,250,250,255,1,26,262,"Mana: 120/800");

      largura=larguraTexto(font,"%d",meusstatsua.pontos);
      DrawText(font,0,0,0,255,1,122-largura,286,"%d",meusstatsua.pontos);
    }
}

void Draw_MenuVenda() {
    if (mostrarmenu) {
      int colocaaura[49];

      DrawIMG(vendeitem, 278,133,243,243,0,0);

      if (numeroitem[1]>0) {
        int temp,temp2;
        for (temp2=0;temp2<7;temp2++) {
          for (temp=0;temp<7;temp++) {
            if(vendetrocatemp[temp2][temp]!=0)
              fillRectangle(temp*28+294+temp, temp2*28+148+temp2, 28 , 28, 65, 65, 65, 255);
          }
        }
        memset(colocaaura, 0, sizeof(colocaaura));
        temp=0; temp2=0;
        while(temp2<7) {
          while(temp<7) {
            if ((colocaaura[vendetrocatemp[temp2][temp]]==0) && (vendetrocatemp[temp2][temp]!=0)) {
              colocaaura[vendetrocatemp[temp2][temp]]=1;
              itemjuntomouse(294+temp*28+2+temp,148+temp2*28+5+temp2,itemvende_temp[vendetrocatemp[temp2][temp]][0],itemvende_temp[vendetrocatemp[temp2][temp]][1],itemvende_temp[vendetrocatemp[temp2][temp]][2]);
            }
            temp++;
          }
          temp=0;
          temp2++;
        }
      }
    }
}
