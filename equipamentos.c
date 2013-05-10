#include "Header/opengl.h"
#include "Header/personagem.h"
#include "Header/magicas.h"
#include "Header/menusjogo.h"
#include "Header/log.h"
#include "Header/caracteristicas.h"
#include "Header/equipamentos.h"

char carregarar=0;

int sizearmos(char type,char posicao) {
  if (((type>=4) && (type<=8)) || (type==14) || (type==16))
    return posicao=='x'? 0:1;
  else if ((type<4) || (type==17))
    return posicao=='x'? 1:1;
  else
    return posicao=='x'? 0:0;
}

void nomesdositens(int tipo, int qual, int add, char *nomeItem) {
  if (tipo==1) {
   if (qual==1) { strcpy(nomeItem,"Capus\0"); }
   else if (qual==2) { strcpy(nomeItem,"Helm Simples de Latão\0"); }
   else if (qual==3) { strcpy(nomeItem,"Helm Simples de Aço\0"); }
   else if (qual==4) { strcpy(nomeItem,"Helm Simples de Ouro\0"); }
   else if (qual==5) { strcpy(nomeItem,"Helm Meia de Latão\0"); }
   else if (qual==6) { strcpy(nomeItem,"Helm Meia de Aço\0"); }
   else if (qual==7) { strcpy(nomeItem,"Helm Meia de Ouro\0"); }
   else if (qual==8) { strcpy(nomeItem,"Helm Vikin de Latão\0"); }
   else if (qual==9) { strcpy(nomeItem,"Helm Vikin de Aço\0"); }
   else if (qual==10) { strcpy(nomeItem,"Helm Vikin de Ouro\0"); }
   else if (qual==11) { strcpy(nomeItem,"Helm General de Latão\0"); }
   else if (qual==12) { strcpy(nomeItem,"Helm General de Aço\0"); }
   else if (qual==13) { strcpy(nomeItem,"Helm General de Ouro\0"); }
   else if (qual==14) { strcpy(nomeItem,"Helm Grande de Latão\0"); }
   else if (qual==15) { strcpy(nomeItem,"Helm Grande de Aço\0"); }
   else if (qual==16) { strcpy(nomeItem,"Helm Grande de Ouro\0"); }
  }
  else if (tipo==2) {
   if (qual==1) { strcpy(nomeItem,"Malha de Cobre\0"); }
   else if (qual==2) { strcpy(nomeItem,"Malha de Aço\0"); }
   else if (qual==3) { strcpy(nomeItem,"Malha de Ouro\0"); }
   else if (qual==4) { strcpy(nomeItem,"Malha de Titanio\0"); }
   else if (qual==5) { strcpy(nomeItem,"Peitoral de Latão\0"); }
   else if (qual==6) { strcpy(nomeItem,"Peitoral de Cobre\0"); }
   else if (qual==7) { strcpy(nomeItem,"Peitoral de Ferro\0"); }
   else if (qual==8) { strcpy(nomeItem,"Peitoral de Aço\0"); }
   else if (qual==9) { strcpy(nomeItem,"Peitoral de Ouro\0"); }
   else if (qual==10) { strcpy(nomeItem,"Peitoral de Escama de Dragão\0"); }
  }
  else if (tipo==3) {
    if (qual==1) { strcpy(nomeItem,"Escudo de Plastico\0"); }
    else if (qual==2) { strcpy(nomeItem,"Escudo de Madeira\0"); }
    else if (qual==3) { strcpy(nomeItem,"Escudo de Madeira Reforcada\0"); }
    else if (qual==4) { strcpy(nomeItem,"Escudo de Madeira Nobre\0"); }
    else if (qual==5) { strcpy(nomeItem,"Escudo de Ferro\0"); }
    else if (qual==6) { strcpy(nomeItem,"Escudo de Aço\0"); }
    else if (qual==7) { strcpy(nomeItem,"Escudo de Ouro\0"); }
    else if (qual==8) { strcpy(nomeItem,"Escudo Grande de Cobre\0"); }
    else if (qual==9) { strcpy(nomeItem,"Escudo Grande de Ferro\0"); }
    else if (qual==10) { strcpy(nomeItem,"Escudo Grande de Ouro\0"); }
  }
  else if (tipo==4) {
    if (qual==1) { strcpy(nomeItem,"Clava Simples\0"); }
    else if (qual==2) { strcpy(nomeItem,"Clava com Espinhos\0"); }
    else if (qual==3) { strcpy(nomeItem,"Clava com Medieval\0"); }
    else if (qual==4) { strcpy(nomeItem,"Clava com ponta de Ferro\0"); }
    else if (qual==5) { strcpy(nomeItem,"Clava com Espinhos de Ferro\0"); }
  }
  else if (tipo==5) {
    if (qual==1) { strcpy(nomeItem,"Machado Simples\0"); }
    else if (qual==2) { strcpy(nomeItem,"Machado Medio\0"); }
    else if (qual==3) { strcpy(nomeItem,"Machado Grande\0"); }
    else if (qual==4) { strcpy(nomeItem,"Machado de Guerra\0"); }
    else if (qual==5) { strcpy(nomeItem,"Machado Duplo\0"); }
  }
  else if (tipo==6) {
    if (qual==1) { strcpy(nomeItem,"Espada Simples\0"); }
    else if (qual==2) { strcpy(nomeItem,"Espada Curva\0"); }
    else if (qual==3) { strcpy(nomeItem,"Facão Curvo\0"); }
    else if (qual==4) { strcpy(nomeItem,"Espada Comprida\0"); }
    else if (qual==5) { strcpy(nomeItem,"Espada Torta\0"); }
  }
  else if (tipo==7) {
    if (qual==1) { strcpy(nomeItem,"Staff\0"); }
    else if (qual==2) { strcpy(nomeItem,"Staff\0"); }
    else if (qual==3) { strcpy(nomeItem,"Staff\0"); }
    else if (qual==4) { strcpy(nomeItem,"Staff\0"); }
    else if (qual==5) { strcpy(nomeItem,"Staff\0"); }
  }
  else if (tipo==8) {
    if (qual==1) { strcpy(nomeItem,"Arco Simples\0"); }
    else if (qual==2) { strcpy(nomeItem,"Arco Pequeno\0"); }
    else if (qual==3) { strcpy(nomeItem,"Arco Longo\0"); }
    else if (qual==4) { strcpy(nomeItem,"Arco Supremo\0"); }
    else if (qual==5) { strcpy(nomeItem,"Arco Divino\0"); }
  }
  else if (tipo==9) {
    strcpy(nomeItem,"Amuleto\0");
  }
  else if (tipo==10) {
    strcpy(nomeItem,"Anel\0");
  }
  else if (tipo==11) {
    strcpy(nomeItem,"Bracelete\0");
  }
  else if (tipo==12) {
    strcpy(nomeItem,"Luvas\0");
  }
  else if (tipo==13) {
    strcpy(nomeItem,"Botas\0");
  }
  else if (tipo==14) {
    strcpy(nomeItem,"Capa\0");
  }
  else if (tipo==15) {
    if (qual==1) { strcpy(nomeItem,"Poção de Vida\0"); }
    else if (qual==2) { strcpy(nomeItem,"Poção de Magia\0"); }
    else if (qual==3) { strcpy(nomeItem,"Poção de Estamina\0"); }
    else if (qual==4) { strcpy(nomeItem,"Poção Grande de Vida\0"); }
    else if (qual==5) { strcpy(nomeItem,"Poção Grande de Magia\0"); }
    else if (qual==6) { strcpy(nomeItem,"Poção Grande de Estamina\0"); }
    else if (qual==7) { strcpy(nomeItem,"Caixa mágica\0"); }
    else if (qual==8) { strcpy(nomeItem,"Caixa mágica\0"); }
    else if (qual==9) { strcpy(nomeItem,"Caixa mágica\0"); }
    else if (qual==10) { strcpy(nomeItem,"Caixa mágica\0"); }
    else if (qual==11) { strcpy(nomeItem,"Caixa mágica\0"); }
    else if (qual==12) { strcpy(nomeItem,"Caixa mágica\0"); }
    else if (qual==13) { strcpy(nomeItem,"Scroll Cinza\0"); }
    else if (qual==14) { strcpy(nomeItem,"Scroll Vermelho\0"); }
    else if (qual==15) { strcpy(nomeItem,"Scroll Azul\0"); }
    else if (qual==16) { strcpy(nomeItem,"Scroll Amarelo\0"); }
    else if (qual==17) { strcpy(nomeItem,"Scroll Verde\0"); }
    else if (qual==18) { strcpy(nomeItem,"Scroll Rosa\0"); }
    else if (qual==19) { strcpy(nomeItem,"Scroll Branco\0"); }
    else if (qual==20) { strcpy(nomeItem,"Pessego\0"); }
    else if (qual==21) { strcpy(nomeItem,"Cacho de Uva\0"); }
  }
  else if (tipo==16) {
    if (qual==1) { strcpy(nomeItem,"Vara de Pesca\0"); }
  }
  else if (tipo==17) {
    if (qual==1) { strcpy(nomeItem,"Peixe\0"); }
  }
  else if (tipo==53) {
    if (qual==1) { sprintf(nomeItem,"%d Gold",add); }
  }
}

int equimaent(int type,int qual,int add,char bnoius,char oq) {
  int reuteron=0;
  //Helm
  if (type==1) {
    if (qual==7){
      if (bnoius==1) {
        if (oq==0) { reuteron=2; } else if (oq==1) { reuteron=20; } else if (oq==2) { reuteron=10; }
      }
      else if (bnoius==2) {
       if (oq==0) { reuteron=1; } else if (oq==3) { reuteron=1; }
      }
      else if (bnoius==3) { reuteron=25; }
      else { reuteron=40; }
    }
    if (qual==2){
      if (bnoius==1) {
        if (oq==0) { reuteron=0; } else if (oq==1) { reuteron=20; } else if (oq==2) { reuteron=10; }
      }
      else if (bnoius==2) {
       if (oq==0) { reuteron=0; }
      }
      else if (bnoius==3) { reuteron=5; }
      else { reuteron=20; }
    }
    if (qual==3){
      if (bnoius==1) {
        if (oq==0) { reuteron=3; } else if (oq==1) { reuteron=15; } else if (oq==2) { reuteron=25; } else if (oq==4) { reuteron=20; }
      }
      else if (bnoius==2) {
       if (oq==1) { reuteron=0; } else if (oq==2) { reuteron=2; }
      }
      else if (bnoius==3) { reuteron=15; }
      else { reuteron=35; }
    }
  }
  //Armor
  else if (type==2) {
    if (qual==3){
      if (bnoius==1) {
        if (oq==0) { reuteron=2; } else if (oq==1) { reuteron=50; } else if (oq==3) { reuteron=20; }
      }
      else if (bnoius==2) {
       if (oq==0) { reuteron=2; } else if (oq==1) { reuteron=10; } else if (oq==2) { reuteron=5; }
      }
      else if (bnoius==3) { reuteron=40; }
      else { reuteron=150; }
    }
  }
  //Escudo
  else if (type==3) {
    if (qual==2){
      if (bnoius==1) {
        if (oq==0) { reuteron=2; } else if (oq==1) { reuteron=20; } else if (oq==2) { reuteron=10; }
      }
      else if (bnoius==2) {
       if (oq==1) { reuteron=0; } //else if (oq==2) { reuteron=2; }
      }
      else if (bnoius==3) { reuteron=5; }
      else { reuteron=25; }
    }
  }
  if ((type>=4) && (type<=8)) {
      if (bnoius==1) {
        if (oq==0) { reuteron=0; }
      }
      else if (bnoius==2) {
       if (oq==1) { reuteron=0; }
      }
      else if (bnoius==3) { reuteron=5; }
      else { reuteron=28; }
  }
  //Itens
  else if (type==15) {
    /* TODO: verificar isto aqui*/
    if (qual==1) {
      if (bnoius==1) { reuteron=0; }
      if (bnoius==2) { if (oq==0) { reuteron=0; } else if (oq==1) { reuteron=50; } }
    }
    else if (qual==2) {
      if (bnoius==1) { reuteron=0; }
      if (bnoius==2) { if (oq==0) { reuteron=0; } else if (oq==2) { reuteron=50; } }
    }
    else if (qual==3) {
      if (bnoius==1) { reuteron=0; }
      if (bnoius==2) { if (oq==0) { reuteron=0; } else if (oq==3) { reuteron=50; } }
    }
    else if (qual==4) {
      if (bnoius==1) { reuteron=0; }
      if (bnoius==2) { if (oq==0) { reuteron=0; } else if (oq==1) { reuteron=150; } }
    }
    else if (qual==5) {
      if (bnoius==1) { reuteron=0; }
      if (bnoius==2) { if (oq==0) { reuteron=0; } else if (oq==2) { reuteron=150; } }
    }
    else if (qual==6) {
      if (bnoius==1) { reuteron=0; }
      if (bnoius==2) { if (oq==0) { reuteron=0; } else if (oq==3) { reuteron=150; } }
    }
    /*else if (qual==7) {
      if (bnoius==1) { reuteron=0; }
      if (bnoius==2) { if (oq==0) { reuteron=0; } else if (oq==4) { reuteron=1; strcpy(temasda4g,"Portal para cidade."); } }
    }
    else if (qual==8) {
      if (bnoius==1) { reuteron=0; }
      if (bnoius==2) { if (oq==0) { reuteron=0; } else if (oq==4) { reuteron=1; strcpy(temasda4g,"Portal para cidade."); } }
    }
    else if (qual==9) {
      if (bnoius==1) { reuteron=0; }
      if (bnoius==2) { if (oq==0) { reuteron=0; } else if (oq==4) { reuteron=1; strcpy(temasda4g,"Portal para cidade."); } }
    }
    else if (qual==10) {
      if (bnoius==1) { reuteron=0; }
      if (bnoius==2) { if (oq==0) { reuteron=0; } else if (oq==4) { reuteron=1; strcpy(temasda4g,"Portal para cidade."); } }
    }
    else if (qual==11) {
      if (bnoius==1) { reuteron=0; }
      if (bnoius==2) { if (oq==0) { reuteron=0; } else if (oq==4) { reuteron=1; strcpy(temasda4g,"Portal para cidade."); } }
    }
    else if (qual==12) {
      if (bnoius==1) { reuteron=0; }
      if (bnoius==2) { if (oq==0) { reuteron=0; } else if (oq==4) { reuteron=1; strcpy(temasda4g,"Portal para cidade."); } }
    }
    else if (qual==13) {
      if (bnoius==1) { reuteron=0; }
      if (bnoius==2) { if (oq==0) { reuteron=0; } else if (oq==4) { reuteron=1; nomedasmagicas(1,1); } }
    }
    else if (qual==14) {
      if (bnoius==1) { reuteron=0; }
      if (bnoius==2) { if (oq==0) { reuteron=0; } else if (oq==4) { reuteron=1; nomedasmagicas(1,2); } }
    }
    else if (qual==15) {
      if (bnoius==1) { reuteron=0; }
      if (bnoius==2) { if (oq==0) { reuteron=0; } else if (oq==4) { reuteron=1; nomedasmagicas(1,3); } }
    }
    else if (qual==16) {
      if (bnoius==1) { reuteron=0; }
      if (bnoius==2) { if (oq==0) { reuteron=0; } else if (oq==4) { reuteron=1; nomedasmagicas(1,4); } }
    }
    else if (qual==17) {
      if (bnoius==1) { reuteron=0; }
      if (bnoius==2) { if (oq==0) { reuteron=0; } else if (oq==4) { reuteron=1; nomedasmagicas(1,5); } }
    }
    else if (qual==18) {
      if (bnoius==1) { reuteron=0; }
      if (bnoius==2) { if (oq==0) { reuteron=0; } else if (oq==4) { reuteron=1; nomedasmagicas(1,6); } }
    }
    else if (qual==19) {
      if (bnoius==1) { reuteron=0; }
      if (bnoius==2) { if (oq==0) { reuteron=0; } else if (oq==4) { reuteron=1; nomedasmagicas(1,7); } }
    }*/
    else if (qual==20) {
      if (bnoius==1) { reuteron=0; }
      if (bnoius==2) { if (oq==0) { reuteron=0; } else if (oq==1) { reuteron=15; } }
    }
    else if (qual==21) {
      if (bnoius==1) { reuteron=0; }
      if (bnoius==2) { if (oq==0) { reuteron=0; } else if (oq==1) { reuteron=40; } }
    }
  }
  //vara
  else if (type==16) {
      if (bnoius==1) {
        if (oq==0) { reuteron=0; }
      }
      else if (bnoius==2) {
       if (oq==1) { reuteron=0; }
      }
      else if (bnoius==3) { reuteron=0; }
      else { reuteron=30; }
  }
  //itens2
  else if (type==17) {
    if (qual==1) {
      if (bnoius==1) { reuteron=0; }
      if (bnoius==2) { if (oq==0) { reuteron=0; } else if (oq==1) { reuteron=50; } }
    }
  }
  return reuteron;
}

int UsarItem(int tipo,int qual,int add) {
  if (tipo==15) {
    if ((qual==1) || (qual==4) || (qual==20) || (qual==21)) {
      personagem.vida+=equimaent(15,qual,add,2,1);
      if (personagem.vida>100) { personagem.vida=100; }
    }
    else if ((qual==2) || (qual==5)) {
      meusstatsua.mana+=equimaent(15,qual,add,2,1);
      if (meusstatsua.mana>100) { meusstatsua.mana=100; }
    }
    else if ((qual==3) || (qual==6)) {
      meusstatsua.estamina+=equimaent(15,qual,add,2,1);
      if (meusstatsua.estamina>100) { meusstatsua.estamina=100; }
    }
    else if (qual>=13) {
      int percorrer;
      for (percorrer=0; percorrer<MagicNumAtual ;percorrer++)
        if (minhasmagicas[percorrer].nummagic==qual-12) break;

      if (percorrer>=MagicNumAtual)
        minhasmagicas[MagicNumAtual++].nummagic=qual-12;
      else {
        Error("Você já possue esta mágica.",ERRO_AVISO);
        return 0;
      }
    }
  }
  else if (tipo==17) {
    if (qual==1) {
      personagem.vida+=equimaent(15,qual,add,2,1);
      if (personagem.vida>100) { personagem.vida=100; }
    }
  }
  else
    return 0;

  return 1;
}

void UsarItemLocalRap(int id) {
  if (itemlocalrapido[0][id]==0) {
    if ((itemnamao[0]==15) && (carregarar==1)) {
      itemlocalrapido[0][id]=itemnamao[1];
      itemlocalrapido[1][id]=itemnamao[2];
      carregarar=0;
      itemnamao[0]=0;
      itemnamao[1]=0;
      itemnamao[2]=0;
    }
  }
  else {
    if (carregarar==0) {
      itemnamao[0]=15;
      itemnamao[1]=itemlocalrapido[0][id];
      itemnamao[2]=itemlocalrapido[1][id];
      itemlocalrapido[0][id]=0;
      itemlocalrapido[1][id]=0;
      carregarar=1;
    }
    else {
      if ((itemnamao[0]==15) && (carregarar==1)) {
        int tempada=itemnamao[1];
        itemnamao[1]=itemlocalrapido[0][id];
        itemlocalrapido[0][id]=tempada;
        tempada=itemnamao[2];
        itemnamao[2]=itemlocalrapido[1][id];
        itemlocalrapido[1][id]=tempada;
      }
    }
  }
}

void Criar_Janela(int x, int y,int w,int h,char tipo) {
  fillRectangle(x,y,w,h,128,128,128,255);
  drawRectangle(x,y,w,h,50,50,50,255);

  if (tipo==1)
    drawLine(x+8,y+17,x+w-7,y+17,98,98,98,255);
}

void janeladeinfo( int x, int y, int tipo, int qual, int add) {
  int w,h,mairotamanho=0,mairotamanho2=0;
  char temasda4g[30];

  nomesdositens(tipo,qual,add,temasda4g);

  w=larguraTexto(font,"%s",temasda4g);
  h=alturaTexto(font);

  if ((w == -1) || (h == -1)) { printf("ERRO\n"); }

  mairotamanho=w+28;
  if (mairotamanho<130) { mairotamanho=130; }
  if (((tipo==15) || (tipo==17)) && (mairotamanho<150)) { mairotamanho=150; }
  mairotamanho2=54+((equimaent(tipo,qual,add,1,0)+((equimaent(tipo,qual,add,1,0)!=0)?1:0)+equimaent(tipo,qual,add,2,0)+((equimaent(tipo,qual,add,2,0)!=0)?1:0))*15);
  if (mostrarmenu==1) { mairotamanho2+=15; }
  x=(x-mairotamanho);
  if (x+mairotamanho<0) { x=(x+mairotamanho); }
  if (y+mairotamanho2>595) { y=(y-mairotamanho2); }
  if (x<0) { x=0; }
  if (y<0) { y=0; }
  Criar_Janela(x,y,mairotamanho,mairotamanho2,1);

  char tempad=0;
  if (equimaent(tipo,qual,add,2,0))
    DrawText(font,92,250,133,250,3,x+8,y+5,"%s",temasda4g);
  else
    DrawText(font,250,250,223,250,3,x+8,y+5,"%s",temasda4g);

  if ((tipo!=15) && (tipo!=17)) {
    if (((tipo>=4) && (tipo<=8)) || (tipo==16))
      DrawText(font,232,232,232,250,3,x+5,y+23,"Ataque: %d",equimaent(tipo,qual,add,3,0));
    else
      DrawText(font,232,232,232,250,3,x+5,y+23,"Defesa: %d",equimaent(tipo,qual,add,3,0));
  }
  else {
    if (equimaent(tipo,qual,add,2,1))
      DrawText(font,232,232,232,250,3,x+5,y+23+tempad*14,"Recupera %d de vida.",equimaent(tipo,qual,add,2,1));
    else if (equimaent(tipo,qual,add,2,2))
      DrawText(font,232,232,232,250,3,x+5,y+23+tempad*14,"Recupera %d de magia.",equimaent(tipo,qual,add,2,2));
    else if (equimaent(tipo,qual,add,2,3))
      DrawText(font,232,232,232,250,3,x+5,y+23+tempad*14,"Recupera %d de estamina.",equimaent(tipo,qual,add,2,3));
    else if (equimaent(tipo,qual,add,2,4)) {
      equimaent(tipo,qual,add,2,4);
      DrawText(font,232,232,232,250,3,x+5,y+23+tempad*14,"%s",temasda4g);
    }
  }
  if ((tipo!=15) && (tipo!=17))
    DrawText(font,232,232,232,250,3,x+5,y+38,"Duração: %d\\%d",20,equimaent(tipo,qual,add,4,1));
  else
    DrawText(font,232,232,232,250,3,x+5,y+38,"Quantidade: %d",add);

  if (equimaent(tipo,qual,add,1,0)) {
    DrawText(font,250,250,223,250,3,x+5,y+53+tempad*15,"Requer:");
    tempad++;
    if (equimaent(tipo,qual,add,1,1)) {
      if (meusstatsua.forca < equimaent(tipo,qual,add,1,1))
        DrawText(font,255,100,100,250,3,x+8,y+54+tempad*14,"Força: %d (%d)",equimaent(tipo,qual,add,1,1),equimaent(tipo,qual,add,1,1)-meusstatsua.forca);
      else
        DrawText(font,232,232,232,250,3,x+8,y+54+tempad*14,"Força: %d",equimaent(tipo,qual,add,1,1));
      tempad++;
    }
    if (equimaent(tipo,qual,add,1,2)) {
      if (meusstatsua.agilidade < equimaent(tipo,qual,add,1,2))
        DrawText(font,255,100,100,250,3,x+8,y+54+tempad*14,"Agilidade: %d (%d)",equimaent(tipo,qual,add,1,2),equimaent(tipo,qual,add,1,2)-meusstatsua.agilidade);
      else
        DrawText(font,232,232,232,250,3,x+8,y+54+tempad*14,"Agilidade: %d",equimaent(tipo,qual,add,1,2));
      tempad++;
    }
    if (equimaent(tipo,qual,add,1,3)) {
      if (meusstatsua.vitalidade < equimaent(tipo,qual,add,1,3))
        DrawText(font,255,100,100,250,3,x+8,y+54+tempad*14,"Vitalidade: %d (%d)",equimaent(tipo,qual,add,1,3),equimaent(tipo,qual,add,1,3)-meusstatsua.vitalidade);
      else
        DrawText(font,232,232,232,250,3,x+8,y+54+tempad*14,"Vitalidade: %d",equimaent(tipo,qual,add,1,3));
      tempad++;
    }
    if (equimaent(tipo,qual,add,1,4)) {
      if (meusstatsua.inteligencia < equimaent(tipo,qual,add,1,4))
        DrawText(font,255,100,100,250,3,x+8,y+54+tempad*14,"Inteligência: %d (%d)",equimaent(tipo,qual,add,1,4),equimaent(tipo,qual,add,1,4)-meusstatsua.inteligencia);
      else
        DrawText(font,232,232,232,250,3,x+8,y+54+tempad*14,"Inteligência: %d",equimaent(tipo,qual,add,1,4));
      tempad++;
    }
  }

  if (equimaent(tipo,qual,add,2,0)) {
    DrawText(font,250,250,223,250,3,x+5,y+53+tempad*15,"Bônus:");
    tempad++;
    if (equimaent(tipo,qual,add,2,1)) { DrawText(font,232,232,232,250,3,x+8,y+54+tempad*14,"+%d de força.",equimaent(tipo,qual,add,2,1)); tempad++; }
    if (equimaent(tipo,qual,add,2,2)) { DrawText(font,232,232,232,250,3,x+8,y+54+tempad*14,"+%d de agilidade.",equimaent(tipo,qual,add,2,2)); tempad++; }
    if (equimaent(tipo,qual,add,2,3)) { DrawText(font,232,232,232,250,3,x+8,y+54+tempad*14,"+%d de vitalidade.",equimaent(tipo,qual,add,2,3)); tempad++; }
    if (equimaent(tipo,qual,add,2,4)) { DrawText(font,232,232,232,250,3,x+8,y+54+tempad*14,"+%d de inteligência.",equimaent(tipo,qual,add,2,4)); tempad++; }
  }
  if (mostrarmenu==1) {
    if (mouseverondeclia(293,496,147,350))
      DrawText(font,250,250,223,250,3,x+5,y+53+tempad*15,"Comprar por: %d",100);
    else
      DrawText(font,250,250,223,250,3,x+5,y+53+tempad*15,"Vender por: %d",50);
  }
}

int opcoesdeitens(int qual,char oq,int add) {
  //printf("%d %d %d\n");
  int returonia=0;
  if (qual==1) {
    if (oq=='x') returonia=668;
    else if (oq=='y') returonia=63;
    else if (oq=='w') returonia=45;
    else if (oq=='h') returonia=44;
    else if (oq=='a') returonia=equipamentos.helm[0];
    else if (oq=='b') returonia=1;
    else if (oq=='c') returonia=equipamentos.helm[1];
    else {
      equipamentos.helm[0]=oq;
      equipamentos.helm[1]=add;
    }
  }
  else if (qual==2) {
    if (oq=='x') returonia=660;
    else if (oq=='y') returonia=114;
    else if (oq=='w') returonia=60;
    else if (oq=='h') returonia=60;
    else if (oq=='a') returonia=equipamentos.armor[0];
    else if (oq=='b') returonia=2;
    else if (oq=='c') returonia=equipamentos.armor[1];
    else {
      equipamentos.armor[0]=oq;
      equipamentos.armor[1]=add;
    }
  }
  else if (qual==3) {
    if (oq=='x') returonia=729;
    else if (oq=='y') returonia=114;
    else if (oq=='w') returonia=60;
    else if (oq=='h') returonia=60;
    else if (oq=='a') returonia=equipamentos.mao2[0];
    else if (oq=='b') returonia=3;
    else if (oq=='c') returonia=equipamentos.mao2[1];
    else {
      equipamentos.mao2[0]=oq;
      equipamentos.mao2[1]=add;
    }
  }
  else if (qual==4) {
    if (oq=='x') returonia=591;
    else if (oq=='y') returonia=114;
    else if (oq=='w') returonia=60;
    else if (oq=='h') returonia=60;
    else if (oq=='a') returonia=equipamentos.mao1[0];
    else if (oq=='b') returonia=equipamentos.mao1tipo;
    else if (oq=='c') returonia=equipamentos.mao1[1];
    else {
      equipamentos.mao1[0]=oq;
      equipamentos.mao1[1]=add;
      if (oq==0) equipamentos.mao1tipo=0;
    }
  }
  else if (qual==5) {
    if (oq=='x') returonia=624;
    else if (oq=='y') returonia=79;
    else if (oq=='w') returonia=28;
    else if (oq=='h') returonia=28;
    else if (oq=='a') returonia=equipamentos.amuleto[0];
    else if (oq=='b') returonia=9;
    else if (oq=='c') returonia=equipamentos.amuleto[1];
    else {
      equipamentos.amuleto[0]=oq;
      equipamentos.amuleto[1]=add;
    }
  }
  else if (qual==6) {
    if (oq=='x') returonia=589;
    else if (oq=='y') returonia=229;
    else if (oq=='w') returonia=28;
    else if (oq=='h') returonia=28;
    else if (oq=='a') returonia=equipamentos.anel1[0];
    else if (oq=='b') returonia=10;
    else if (oq=='c') returonia=equipamentos.anel1[1];
    else {
      equipamentos.anel1[0]=oq;
      equipamentos.anel1[1]=add;
    }
  }
  else if (qual==7) {
    if (oq=='x') returonia=763;
    else if (oq=='y') returonia=229;
    else if (oq=='w') returonia=28;
    else if (oq=='h') returonia=28;
    else if (oq=='a') returonia=equipamentos.anel2[0];
    else if (oq=='b') returonia=10;
    else if (oq=='c') returonia=equipamentos.anel2[1];
    else {
      equipamentos.anel2[0]=oq;
      equipamentos.anel2[1]=add;
    }
  }
  else if (qual==8) {
    if (oq=='x') returonia=623;
    else if (oq=='y') returonia=229;
    else if (oq=='w') returonia=28;
    else if (oq=='h') returonia=28;
    else if (oq=='a') returonia=equipamentos.braco1[0];
    else if (oq=='b') returonia=11;
    else if (oq=='c') returonia=equipamentos.braco1[1];
    else {
      equipamentos.braco1[0]=oq;
      equipamentos.braco1[1]=add;
    }
  }
  else if (qual==9) {
    if (oq=='x') returonia=729;
    else if (oq=='y') returonia=229;
    else if (oq=='w') returonia=28;
    else if (oq=='h') returonia=28;
    else if (oq=='a') returonia=equipamentos.braco2[0];
    else if (oq=='b') returonia=11;
    else if (oq=='c') returonia=equipamentos.braco2[1];
    else {
     equipamentos.braco2[0]=oq;
     equipamentos.braco2[1]=add;
    }
  }
  else if (qual==10) {
    if (oq=='x') returonia=606;
    else if (oq=='y') returonia=180;
    else if (oq=='w') returonia=45;
    else if (oq=='h') returonia=44;
    else if (oq=='a') returonia=equipamentos.luvas[0];
    else if (oq=='b') returonia=12;
    else if (oq=='c') returonia=equipamentos.luvas[1];
    else {
      equipamentos.luvas[0]=oq;
      equipamentos.luvas[1]=add;
    }
  }
  else if (qual==11) {
    if (oq=='x') returonia=667;
    else if (oq=='y') returonia=229;
    else if (oq=='w') returonia=45;
    else if (oq=='h') returonia=44;
    else if (oq=='a') returonia=equipamentos.botas[0];
    else if (oq=='b') returonia=13;
    else if (oq=='c') returonia=equipamentos.botas[1];
    else {
      equipamentos.botas[0]=oq; equipamentos.botas[1]=add;
    }
  }
  else if (qual==12) {
    if (oq=='x') returonia=729;
    else if (oq=='y') returonia=47;
    else if (oq=='w') returonia=34;
    else if (oq=='h') returonia=60;
    else if (oq=='a') returonia=equipamentos.capa[0];
    else if (oq=='b') returonia=14;
    else if (oq=='c') returonia=equipamentos.capa[1];
    else {
      equipamentos.capa[0]=oq;
      equipamentos.capa[1]=add;
    }
  }
  return returonia;
}

void colocaritens() {
   if (carregarar==1) {
     SDL_Color color;

     int contarempaoe;
     for (contarempaoe=1; contarempaoe<=12 ;contarempaoe++) {
       if (mouseverondeclia(opcoesdeitens(contarempaoe,'x',0),opcoesdeitens(contarempaoe,'x',0)+opcoesdeitens(contarempaoe,'w',0),opcoesdeitens(contarempaoe,'y',0),opcoesdeitens(contarempaoe,'y',0)+opcoesdeitens(contarempaoe,'h',0))) {
         if (contarempaoe==4) {
           if (((itemnamao[0]<4) || (itemnamao[0]>8)) && (itemnamao[0]!=16)) {
             color.r = 255;
             color.g = 100;
             color.b = 100;
           }
           else if ((((itemnamao[0]>=4) && (itemnamao[0]<=8)) || (itemnamao[0]==16)) && (opcoesdeitens(contarempaoe,'a',0)!=0)) {
             color.r = 100;
             color.g = 255;
             color.b = 100;
           }
           else {
             color.r = 0;
             color.g = 155;
             color.b = 255;
           }
         }
         else {
           if (itemnamao[0]!=opcoesdeitens(contarempaoe,'b',0)) {
             color.r = 255;
             color.g = 100;
             color.b = 100;
           }
           else if ((itemnamao[0]==opcoesdeitens(contarempaoe,'b',0)) && (opcoesdeitens(contarempaoe,'a',0)!=0)) {
             color.r = 100;
             color.g = 255;
             color.b = 100;
           }
           else if ((equimaent(itemnamao[0],itemnamao[1],itemnamao[2],1,0)) && ((meusstatsua.forca < equimaent(itemnamao[0],itemnamao[1],itemnamao[2],1,1)) || (meusstatsua.agilidade < equimaent(itemnamao[0],itemnamao[1],itemnamao[2],1,2)) || (meusstatsua.vitalidade < equimaent(itemnamao[0],itemnamao[1],itemnamao[2],1,3)) || (meusstatsua.inteligencia < equimaent(itemnamao[0],itemnamao[1],itemnamao[2],1,4)))) {
             color.r = 250;
             color.g = 163;
             color.b = 22;
           }
           else {
             color.r = 0;
             color.g = 155;
             color.b = 255;
           }
         }

         fillRectangle(opcoesdeitens(contarempaoe,'x',0),opcoesdeitens(contarempaoe,'y',0),opcoesdeitens(contarempaoe,'w',0),opcoesdeitens(contarempaoe,'h',0),color.r,color.g,color.b,255);

         contarempaoe=16;
       }
     }
    }

    if (equipamentos.helm[0]) DrawIMG(helms, 668, 61,48,48,(equipamentos.helm[0]-1)*49+1,1);
    if (equipamentos.armor[0]) DrawIMG(armor, 660, 114,62,62,(equipamentos.armor[0]-1)*63+1,1);
    if (equipamentos.mao2[0]) DrawIMG(escudos, 729, 114,62,62,(equipamentos.mao2[0]-1)*63+1,1);
    if (equipamentos.mao1[0]) {
      if (equipamentos.mao1tipo==4) DrawIMG(clavas, 606, 113,30,62,(equipamentos.mao1[0]-1)*31+1,1);
      else if (equipamentos.mao1tipo==5) DrawIMG(machados, 606, 113,30,62,(equipamentos.mao1[0]-1)*31+1,1);
      else if (equipamentos.mao1tipo==6) DrawIMG(espadas, 606, 113,30,62,(equipamentos.mao1[0]-1)*31+1,1);
      else if (equipamentos.mao1tipo==7) DrawIMG(staffs, 606, 113,30,62,(equipamentos.mao1[0]-1)*31+1,1);
      else if (equipamentos.mao1tipo==8) DrawIMG(arcos, 606, 113,30,62,(equipamentos.mao1[0]-1)*31+1,1);
      else if (equipamentos.mao1tipo==16) DrawIMG(varapesca, 606, 113,30,62,(equipamentos.mao1[0]-1)*31+1,1);
    }

    if (equipamentos.amuleto[0]) DrawIMG(amuletos, 623, 78,30,30,(equipamentos.amuleto[0]-1)*31+1,1);
    if (equipamentos.anel1[0]) DrawIMG(aneis, 588, 228,30,30,(equipamentos.anel1[0]-1)*31+1,1);
    if (equipamentos.anel2[0]) DrawIMG(aneis, 762, 228,30,30,(equipamentos.anel2[0]-1)*31+1,1);
    if (equipamentos.braco1[0]) DrawIMG(braco, 622, 228,30,30,(equipamentos.braco1[0]-1)*31+1,1);
    if (equipamentos.braco2[0]) DrawIMG(braco, 728, 228,30,30,(equipamentos.braco2[0]-1)*31+1,1);
    if (equipamentos.luvas[0]) DrawIMG(luvas, 613, 187,30,30,(equipamentos.luvas[0]-1)*31+1,1);
    if (equipamentos.botas[0]) DrawIMG(botas, 675, 235,30,30,(equipamentos.botas[0]-1)*31+1,1);
    if (equipamentos.capa[0]) DrawIMG(capas, 731, 47,30,62,(equipamentos.capa[0]-1)*31+1,1);
}

void itemjuntomouse(int xx,int yy,int tipou,int qual,int add) {
//  *Inicio: Desenha os itens.
  if (tipou==1) DrawIMG(helms, xx, yy,48,48,(qual-1)*48+qual,1);
  else if (tipou==2) DrawIMG(armor, xx-5, yy-5,62,62,(qual-1)*62+qual,1);
  else if (tipou==3) DrawIMG(escudos, xx-5, yy-5,62,62,(qual-1)*62+qual,1);
  else if (tipou==4) DrawIMG(clavas, xx-5, yy-5,30,62,(qual-1)*30+qual,1);
  else if (tipou==5) DrawIMG(machados, xx-5, yy-5,30,62,(qual-1)*30+qual,1);
  else if (tipou==6) DrawIMG(espadas, xx-5, yy-5,30,62,(qual-1)*30+qual,1);
  else if (tipou==7) DrawIMG(staffs, xx-5, yy-5,30,62,(qual-1)*30+qual,1);
  else if (tipou==8) DrawIMG(arcos, xx-5, yy-5,30,62,(qual-1)*30+qual,1);
  else if (tipou==9) DrawIMG(amuletos, xx-3, yy-6,30,30,(qual-1)*30+qual,1);
  else if (tipou==10) DrawIMG(aneis, xx-3, yy-6,30,30,(qual-1)*30+qual,1);
  else if (tipou==11) DrawIMG(braco, xx-3, yy-6,30,30,(qual-1)*30+qual,1);
  else if (tipou==12) DrawIMG(luvas, xx-3, yy-6,30,30,(qual-1)*30+qual,1);
  else if (tipou==13) DrawIMG(botas, xx-3, yy-6,30,30,(qual-1)*30+qual,1);
  else if (tipou==14) DrawIMG(capas, xx-5, yy-5,30,62,(qual-1)*30+qual,1);
  else if (tipou==15) {
    DrawIMG(item, xx-3, yy-6,30,30,(qual-1)*30+qual,1);
    if (add>1) {
      int w=larguraTexto(font,"%d",add);

      DrawText(font2,250,200,0,250,1,xx+26-w, yy+11,"%d",add);
      DrawText(font2,0,0,0,250,1,xx+25-w, yy+10,"%d",add);
    }
  }
  else if (tipou==16) DrawIMG(varapesca, xx-5, yy-5,30,62,(qual-1)*30+qual,1);
  else if (tipou==17) {
    DrawIMG(item2, xx, yy,48,48,(qual-1)*48+qual,1);
    if (add>1) {
      int w=larguraTexto(font,"%d",add);

      DrawText(font2,250,200,0,250,1,xx+56-w, yy+41,"%d",add);
      DrawText(font2,0,0,0,250,1,xx+55-w, yy+40,"%d",add);
    }
  }
//  *Fim: Desenha os itens.
}
