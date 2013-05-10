#include <math.h>

#include "Header/global.h"
#include "Header/mapas.h"
#include "Header/pesca.h"
#include "Header/colisao.h"
#include "Header/personagem.h"
#include "Header/particulas.h"
#include "Header/magicas.h"
#include "Header/flechas.h"
#include "Header/animais.h"
#include "Header/monstros.h"
#include "Header/menusjogo.h"
#include "Header/menus.h"
#include "Header/msgs.h"
#include "Header/equipamentos.h"
#include "Header/interacao.h"
#include "Header/load.h"
#include "Header/chat.h"
#include "Header/GUI.h"
#include "Header/guiitens.h"
#include "Header/ataca.h"
#include "Header/log.h"
#include "Header/tela_jogo.h"

char ligadoasdsa=0, ligadoasdsa2=0;
float itemmostrar;
char enterpress=0;
int mouseencima=0;

void Tela_Jogo_DrawScene() {
  char strTmp[256];

    criarmap();

    Draw_Boias();

    #ifdef DEBUG
      criarmap3();
      fillRectangle(personagem.pathFind.atualX*16-xpos,personagem.pathFind.atualY*16-ypos,16,16,200,200,200,255);
      if ((personagem.pathFind.destinoX!=personagem.pathFind.atualX) || (personagem.pathFind.destinoY!=personagem.pathFind.atualY))
      fillRectangle(personagem.pathFind.destinoX*16-xpos,personagem.pathFind.destinoY*16-ypos,16,16,0,0,200,255);

      int temp=0;
      for (temp=0;temp*16<600;temp++) {fillRectangle(0,temp*16-ypos%48,800,1,0,0,0,255);}
      for (temp=0;temp*16<=800;temp++) {fillRectangle(temp*16-xpos%64,0,1,600,0,0,0,255);}
    #endif

    criarmap2();

    int tempasda;
    for (tempasda=0;tempasda<31;tempasda++) {
      if (DanoTirado[tempasda].ativado==1) {
        if (DanoTirado[tempasda].valor!=-1) {
          if (DanoTirado[tempasda].tipo==1)
            DrawText(font2,250,250,150,((DanoTirado[tempasda].alfa>=0)?250:250+DanoTirado[tempasda].alfa),4,DanoTirado[tempasda].posx-xpos,DanoTirado[tempasda].posy-ypos,"%d",DanoTirado[tempasda].valor);
          else
            DrawText(font2,250,133,83,((DanoTirado[tempasda].alfa>=0)?250:250+DanoTirado[tempasda].alfa),4,DanoTirado[tempasda].posx-xpos,DanoTirado[tempasda].posy-ypos,"%d",DanoTirado[tempasda].valor);
        }
        else
          DrawText(font2,200,200,200,((DanoTirado[tempasda].alfa>=0)?250:250+DanoTirado[tempasda].alfa),4,DanoTirado[tempasda].posx-xpos-8,DanoTirado[tempasda].posy-ypos,"miss");

        if (DanoTirado[tempasda].alfa>0) { DanoTirado[tempasda].posy-=5; } else { DanoTirado[tempasda].posy-=1; }
        DanoTirado[tempasda].alfa-=50;
        if (DanoTirado[tempasda].alfa<=-250) { DanoTirado[tempasda].ativado=0; }
      }
    }

    //FIXME: Verificar isto
   //Mostra o nome do item quando o mouse estiver em cima.
    if (mouseencima==1) {
      int postemploy=(int)((mousemovidoy+ypos)/48);
      int postemplox=(int)((mousemovidox+xpos)/64);
      if (itenschao[0][postemploy][postemplox]) {
        nomesdositens(itenschao[0][postemploy][postemplox], itenschao[1][postemploy][postemplox], itenschao[2][postemploy][postemplox], strTmp);

        int largura=larguraTexto(font,"%s",strTmp);
        int altura=alturaTexto(font);

        fillRectangle(mousemovidox-largura/2-3,mousemovidoy-15,largura+6,altura,0,0,0,120);

        if (equimaent(itenschao[0][postemploy][postemplox],itenschao[1][postemploy][postemplox],itenschao[2][postemploy][postemplox],2,0))
          DrawText(font,92,250,133,255,1,mousemovidox-largura/2,mousemovidoy-15,"%s",strTmp);
        else
          DrawText(font,250,250,250,255,1,mousemovidox-largura/2,mousemovidoy-15,"%s",strTmp);
      }
    }
    else if (mouseencima&2) {
      int postemploy=(int)((mousemovidoy+ypos)/48);
      int postemplox=(int)((mousemovidox+xpos)/64);
      int xpos2=(xpos/64),ypos2=(ypos/48);
      int tempx2,tempy2,w3,h3;
      int cirarmpx,cirarmpy;

      mouseencima&=2;
      for (cirarmpy=0;cirarmpy<=13;cirarmpy++) {
        for (cirarmpx=0;cirarmpx<=13;cirarmpx++) {
          if ((cirarmpx+xpos2<map_sizex) && (cirarmpy+ypos2<map_sizey)) {
            if (itenschao[0][cirarmpy+ypos2][cirarmpx+xpos2]) {
              tempx2=(cirarmpx*64)-xpos%64;
              tempy2=(cirarmpy*48)-ypos%48;
              if ((mouseverondeclia(tempx2,tempx2+64,tempy2,tempy2+48)) && (itenschao[0][postemploy][postemplox])) {
                nomesdositens(itenschao[0][postemploy][postemplox],itenschao[1][postemploy][postemplox],itenschao[2][postemploy][postemplox],strTmp);

                w3=larguraTexto(font,"%s",strTmp);
                h3=alturaTexto(font);

                fillRectangle(mousemovidox-w3/2-3,mousemovidoy-15,w3+6,h3,0,0,0,120);

                if (equimaent(itenschao[0][postemploy][postemplox],itenschao[1][postemploy][postemplox],itenschao[2][postemploy][postemplox],2,0))
                  DrawText(font,92,250,133,255,1,mousemovidox-w3/2,mousemovidoy-15,"%s",strTmp);
                else
                  DrawText(font,250,250,250,255,1,mousemovidox-w3/2,mousemovidoy-15,"%s",strTmp);
              }
              else {
                nomesdositens(itenschao[0][cirarmpy+ypos2][cirarmpx+xpos2],itenschao[1][cirarmpy+ypos2][cirarmpx+xpos2],itenschao[2][cirarmpy+ypos2][cirarmpx+xpos2],strTmp);

                w3=larguraTexto(font,"%s",strTmp);
                h3=alturaTexto(font);

                fillRectangle(tempx2+32-w3/2-3,tempy2,w3+6,h3,0,0,0,120);

                if (equimaent(itenschao[0][cirarmpy+ypos2][cirarmpx+xpos2],itenschao[1][cirarmpy+ypos2][cirarmpx+xpos2],itenschao[2][cirarmpy+ypos2][cirarmpx+xpos2],2,0))
                  DrawText(font,92,250,133,255,1,tempx2+32-w3/2,tempy2,"%s",strTmp);
                else
                  DrawText(font,250,250,250,255,1,tempx2+32-w3/2,tempy2,"%s",strTmp);
              }
            }
          }
        }
      }
    }

    Draw_Particulas();

    Draw_Baloes();

    Draw_Inventario();
    Draw_Bau();
    Draw_MenuMagica();
    Draw_CharInfo();
    Draw_MenuVenda();

    int tempsa=83-(personagem.vida*83)/100;
    DrawIMG(barraquantid,12,507+tempsa,83,83-tempsa,0,tempsa);
    DrawIMG(barraquantid,708,507,83,83,83,0);
    DrawIMG(barra,0,504,800,96,0,0);

    if (magicasel) DrawIMG(magicasbotao,617,548,37,37,(magicasel-1)*37,0);

    if (meusstatsua.experiencia>0) {
      int temppos=(meusstatsua.nextlevelexp*482)/(proximolevelexp-(meusstatsua.experiencia-meusstatsua.nextlevelexp));
      fillRectangle(113,540,temppos,1,128,128,64,255);
      fillRectangle(113,541,temppos,2,174,174,94,255);
      fillRectangle(113,543,temppos,1,192,192,133,255);
      fillRectangle(113,544,temppos,1,202,202,151,255);
    }

    if (janechaton) {
      DrawIMG(botaopress, 491, 555,74,16,0,32);

    }
    if ((personagem.qual==7) && (personagem.acao==9)) {
      if ((boias[1].acao==1) && (boias[1].ativa==1)) {
        DrawIMG(barrapesca,278,132,245,26,0,0);
        DrawIMG(cursorpesca,(int)(280+(225*pescapucha)/100),125,16,17,0,0);
      }
    }

    int tempsadaa;
    for (tempsadaa=0;tempsadaa<8;tempsadaa++) {
      if (itemlocalrapido[0][tempsadaa]) { itemjuntomouse(112+30*tempsadaa,557,15,itemlocalrapido[0][tempsadaa],itemlocalrapido[1][tempsadaa]); }
    }


    if (charmenuon)
      DrawIMG(botaopress, 412, 573,74,16,0,16);

    if (inventarioon)
      DrawIMG(botaopress, 412, 555,74,16,0,0);


    if ((inventarioon==1) || (mousemovidoy>=534) || ((mouseverondeclia(293,496,147,350)) && (mostrarmenu==1))) {
      if (carregarar==0) {
        if ((itemmostrar*1000<=SDL_GetTicks()) && (itemmostrar!=0)) { ligadoasdsa=1; ligadoasdsa2=1; }
        if (ligadoasdsa==1) {
          if (mouseverondeclia(588,791,295,498)) { if (itens[(mousemovidoy-296)/29][(mousemovidox-589)/29] !=0) { janeladeinfo(mousemovidox,mousemovidoy,itemnumeroeh[itens[(mousemovidoy-296)/29][(mousemovidox-589)/29]][0],itemnumeroeh[itens[(mousemovidoy-296)/29][(mousemovidox-589)/29]][1],itemnumeroeh[itens[(mousemovidoy-296)/29][(mousemovidox-589)/29]][2]); } }
          else if (mouseverondeclia(110,346,553,579)) { if (itemlocalrapido[0][(int)(mousemovidox-109)/30]!=0) { janeladeinfo(mousemovidox,mousemovidoy,15,itemlocalrapido[0][(mousemovidox-109)/30],itemlocalrapido[1][(mousemovidox-109)/30]); } }
          else if ((mouseverondeclia(293,496,147,350)) && (mostrarmenu==1)) { int numeroitennm; if ((numeroitennm=vendetrocatemp[(mousemovidoy-148)/29][(mousemovidox-294)/29]) != 0) { janeladeinfo(mousemovidox,mousemovidoy,itemvende_temp[numeroitennm][0],itemvende_temp[numeroitennm][1],itemvende_temp[numeroitennm][2]); } }
          else {
            int contarempaoe;

            for (contarempaoe=1; contarempaoe <= 12; contarempaoe++) {
              if (mouseverondeclia(opcoesdeitens(contarempaoe,'x',0),opcoesdeitens(contarempaoe,'x',0)+opcoesdeitens(contarempaoe,'w',0),opcoesdeitens(contarempaoe,'y',0),opcoesdeitens(contarempaoe,'y',0)+opcoesdeitens(contarempaoe,'h',0))) {
                if (opcoesdeitens(contarempaoe,'a',0)!=0) { janeladeinfo(mousemovidox,mousemovidoy,opcoesdeitens(contarempaoe,'b',0),opcoesdeitens(contarempaoe,'a',0),opcoesdeitens(contarempaoe,'c',0)); }
                contarempaoe=16;
              }
            }
          }
        }
      }
    }

//--------------------------------------------------

    Draw_MsgChat();
    Draw_TutoPesca();
    Draw_Menu();

    /*if (CursorUsando[0]==1) {
      if (monsterlacao(CursorUsando[1],'s')) {
        draw_quadrado(250,0,250,monstroatual->x+((imagtamonstro(monstroatual->qual,monstroatual->acao)==1)?45:29)-xpos-1,monstroatual->y+((imagtamonstro(monstroatual->qual,monstroatual->acao)==1)?79:63)-ypos-1,3,3);
      }
    }*/

//--------------------------------------------------

  if (carregarar) { itemjuntomouse(mousemovidox-(sizearmos(itemnamao[0],'x')==1? 14:2),mousemovidoy-(sizearmos(itemnamao[0],'y')==1? 10:2),itemnamao[0],itemnamao[1],itemnamao[2]); }

  int t = SDL_GetTicks();
  static int temetaiias = 0;

//TODO: AURAS FAZER UMA COISA MAIS DECENTE AQUI
  if (temetaiias<=t/100) {
    if (personagem.levelup>=0) { if (personagem.levelup<20) { personagem.levelup++; temetaiias=(t/100)+1; } else { personagem.levelup=-1; } }
    if (personagem.aura!=0) {
      if (personagem.aura==1) {
        if (personagem.auramom==0) {
          personagem.auraimagem++;
          if (personagem.auraimagem>=6)
            personagem.auramom=1;
        }
        else {
          personagem.auraimagem--;
          if (personagem.auraimagem<0) {
            personagem.auraimagem=1;
            personagem.auramom=0;
          }
        }
        temetaiias=(t/100)+3;
      }
      else if (personagem.aura==2) { personagem.auraimagem++; if (personagem.auraimagem>=16) { personagem.auraimagem=0; } temetaiias=(t/100)+2; }
      else if (personagem.aura==3) { if (personagem.auramom==0) { personagem.auraimagem++; if (personagem.auraimagem>=6) { personagem.auramom=1; } } else { personagem.auraimagem--; if (personagem.auraimagem<0) { personagem.auraimagem=1; personagem.auramom=0; } } temetaiias=(t/100)+3; }
      else if (personagem.aura==4) { personagem.auraimagem++; if (personagem.auraimagem>=6) { personagem.auraimagem=0; } temetaiias=(t/100)+3; }
      else if (personagem.aura==5) { personagem.auraimagem++; if (personagem.auraimagem>=5) { personagem.auraimagem=0; } temetaiias=(t/100)+3; }
      else if (personagem.aura==6) { if (personagem.auramom==0) { personagem.auraimagem++; if (personagem.auraimagem>=5) { personagem.auramom=1; } } else { personagem.auraimagem--; if (personagem.auraimagem<0) { personagem.auraimagem=1; personagem.auramom=0; } } temetaiias=(t/100)+2; }
    }
  }
}

void Tela_jogo_ChatAtivar() {
  enterpress=!enterpress;
  GUI_setAtivo(1,enterpress);
  GUI_setAtivo(2,enterpress);
  GUI_setAtivo(3,enterpress);
}

void Tela_Jogo_Eventos(SDL_Event *event) {
  int numeroitennm;
  if (event->type == SDL_MOUSEMOTION) {
    if (((mouseverondeclia(588,791,295,498)) && (inventarioon==1))  || (itemmostrar==0)) { if (mostrarmenu==1) { itemmostrar=1; } else { itemmostrar=(SDL_GetTicks()/1000)+((ligadoasdsa2==0)?2:1); } ligadoasdsa=0; }
    else if (mouseverondeclia(110,346,553,579)) { if (mostrarmenu==1) { itemmostrar=1; } else { itemmostrar=(SDL_GetTicks()/1000)+((ligadoasdsa2==0)?2:1); } ligadoasdsa=0; }
    else if ((mouseverondeclia(293,496,147,350)) && (mostrarmenu==1)) { itemmostrar=1; ligadoasdsa=0; }
    else {
      char contarempaoe=1;
      if (inventarioon==1) {
        while (contarempaoe<=12) {
          if (mouseverondeclia(opcoesdeitens(contarempaoe,'x',0),opcoesdeitens(contarempaoe,'x',0)+opcoesdeitens(contarempaoe,'w',0),opcoesdeitens(contarempaoe,'y',0),opcoesdeitens(contarempaoe,'y',0)+opcoesdeitens(contarempaoe,'h',0))) {
            if (mostrarmenu==1) itemmostrar=1;
            else itemmostrar=(SDL_GetTicks()/1000)+((ligadoasdsa2==0)?2:1);

            ligadoasdsa=0;
            contarempaoe=16;
          }
          contarempaoe++;
        }
      }
      if ((contarempaoe!=16) && (ligadoasdsa==1)) { ligadoasdsa2=0; ligadoasdsa=0; itemmostrar=0; }
    }
    if (menus.ativo==1) {
      char Temp_Num=Info_Menu('n',1),Temp_Itens;
      int pox,poy;
      poy=300-(Temp_Num*15+54)/2;
      pox=400-Info_Menu('t',1)/2;
      menus.itemsel=0;
      for (Temp_Itens=0;Temp_Itens<Temp_Num;Temp_Itens++) {
        if (mouseverondeclia(pox,pox+Info_Menu('t',1),poy+40+17*Temp_Itens,poy+55+17*Temp_Itens)) {
          menus.itemsel=Temp_Itens+((SDL_GetMouseState(NULL, NULL)&SDL_BUTTON(1))?(Temp_Num+2):1);
        }
      }
      if (mouseverondeclia(pox,pox+Info_Menu('t',1),poy,poy+Temp_Num*15+54)) { return; }
      else if (SDL_GetMouseState(NULL, NULL)&SDL_BUTTON(1)) { menus.ativo=0; }
    }
    else if ((SDL_GetMouseState(NULL, NULL)&SDL_BUTTON(1)) && (estaaandar==1))
      chamarPathFind('m');

//        if ((SDL_GetMouseState(NULL, NULL)&SDL_BUTTON(1)) && (keystate[SDLK_x])) { personagem.lado=arrumaragoliuasd(mousemovidox+xpos,mousemovidoy+ypos); atacar(1); }
//        if (SDL_GetMouseState(NULL, NULL)&SDL_BUTTON(3)) { personagem.lado=arrumaragoliuasd(mousemovidox+xpos,mousemovidoy+ypos); atacar(3); }
}



//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- SDL_MOUSEBUTTONDOWN -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
  if ((event->type == SDL_MOUSEBUTTONDOWN) && ( event->button.button == SDL_BUTTON_RIGHT )) {
    if ((personagem.qual==4) && (magicasel)) {
      if (personagem.acao!=8) { antesaltpress=personagem.acao; personagem.acao=8; personagem.imagem=0; }
      personagem.lado=arrumaragoliuasd(personagem.x+48,personagem.y+68,mousemovidox+xpos,mousemovidoy+ypos);
      atacar(3,0,0);
    }

    if ((inventarioon==1) && (mouseverondeclia(588,791,295,498))) {
      if ((checarsecabe((mousemovidox-589)/29,(mousemovidoy-296)/29,0,0,1)==1) && (!carregarar) && ((numeroitennm=itens[(mousemovidoy-296)/29][(mousemovidox-589)/29]) != 0)) {
        if (mostrarmenu!=1) {
          if ((itemnumeroeh[numeroitennm][0]==15) || (itemnumeroeh[numeroitennm][0]==17)) {
            if (UsarItem(itemnumeroeh[numeroitennm][0],itemnumeroeh[numeroitennm][1],itemnumeroeh[numeroitennm][2])) {
              if (itemnumeroeh[numeroitennm][2]>1) { itemnumeroeh[numeroitennm][2]--; }
              else retiraritem(numeroitennm,1);
            }
          }
        }
        else {
          meusstatsua.dinheiro+=50;
          retiraritem(numeroitennm,1);
        }
      }
    }
    else if (mouseverondeclia(110,346,553,579)) {
      if ((itemlocalrapido[0][(mousemovidox-109)/30]) && (!carregarar)) {
        if (!mostrarmenu) {
          if (UsarItem(15,itemlocalrapido[0][(mousemovidox-109)/30],itemlocalrapido[1][(mousemovidox-109)/30])) {
            if (itemlocalrapido[1][(mousemovidox-109)/30]>1) { itemlocalrapido[1][(mousemovidox-109)/30]--; }
            else {
              itemlocalrapido[0][(mousemovidox-109)/30]=0;
              itemlocalrapido[1][(mousemovidox-109)/30]=0;
            }
          }
        }
        else {
          meusstatsua.dinheiro+=50;
          itemlocalrapido[0][(mousemovidox-109)/30]=0;
          itemlocalrapido[1][(mousemovidox-109)/30]=0;
        }
      }
    }
    else if ((mostrarmenu==1) && (inventarioon==1)) {
      char contarempaoe=1;
      while (contarempaoe<=12) { if (mouseverondeclia(opcoesdeitens(contarempaoe,'x',0),opcoesdeitens(contarempaoe,'x',0)+opcoesdeitens(contarempaoe,'w',0),opcoesdeitens(contarempaoe,'y',0),opcoesdeitens(contarempaoe,'y',0)+opcoesdeitens(contarempaoe,'h',0))) { opcoesdeitens(contarempaoe,0,0); meusstatsua.dinheiro+=50; contarempaoe=16; } contarempaoe++; }
    }
  }


//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- SDL_MOUSEBUTTONUP -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
  if ((event->type == SDL_MOUSEBUTTONUP) && ( event->button.button == SDL_BUTTON_RIGHT )) {
//        if (personagem.qual==4) { movermouse3=0; }
  }

//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- SDL_MOUSEBUTTONDOWN -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
  if ((event->type == SDL_MOUSEBUTTONDOWN) && ( event->button.button == SDL_BUTTON_LEFT )) {
    if (menus.ativo==1) {
      char Temp_Num=Info_Menu('n',1),Temp_Itens;
      int pox,poy;
      poy=300-(Temp_Num*15+54)/2;
      pox=400-Info_Menu('t',1)/2;
      if (mouseverondeclia(pox,pox+Info_Menu('t',1),poy,poy+Temp_Num*15+54)) {
        menus.itemsel=0;
        for (Temp_Itens=0;Temp_Itens<Temp_Num;Temp_Itens++) {
          if (mouseverondeclia(pox,pox+Info_Menu('t',1),poy+40+17*Temp_Itens,poy+55+17*Temp_Itens)) { menus.itemsel=Temp_Itens+Temp_Num+2; }
        }
        return;
      }
      else { menus.ativo=0; }
    }
    if (mouseverondeclia(413,485,556,569)) { if (mostrarmenu==0) { inventarioon=1-inventarioon; MagicMenuOn=0; } if (BauMenuOn) BauMenuOn=0; }
    else if (mouseverondeclia(413,485,574,587)) { charmenuon=1-charmenuon; }
    else if (mouseverondeclia(617,653,548,584)) { if (mostrarmenu==0) { MagicMenuOn=1-MagicMenuOn; inventarioon=0; } if (BauMenuOn) BauMenuOn=0; }
    else if (mouseverondeclia(491,565,555,570)) { janechaton=1-janechaton; GUI_setAtivo(4,janechaton); }
    else if (mouseverondeclia(111,135,554,578)) { UsarItemLocalRap(0); }
    else if (mouseverondeclia(141,165,554,578)) { UsarItemLocalRap(1); }
    else if (mouseverondeclia(171,195,554,578)) { UsarItemLocalRap(2); }
    else if (mouseverondeclia(201,225,554,578)) { UsarItemLocalRap(3); }
    else if (mouseverondeclia(231,255,554,578)) { UsarItemLocalRap(4); }
    else if (mouseverondeclia(261,285,554,578)) { UsarItemLocalRap(5); }
    else if (mouseverondeclia(291,315,554,578)) { UsarItemLocalRap(6); }
    else if (mouseverondeclia(321,345,554,578)) { UsarItemLocalRap(7); }

    if ((inventarioon) && (mousemovidox>=578)) {

       //  *Inicio: Guardar/retirar/atualizar/trocar item no inventario.
      if (mouseverondeclia(588,791,295,498)) {

        //retira item do inventario/atualiza item
        if ((numeroitennm=itens[(mousemovidoy-296)/29][(mousemovidox-589)/29])) {
          //atualiza item
          if (carregarar) {
            int itemtemp=checarsecabe((mousemovidox-589)/29,(mousemovidoy-296)/29,sizearmos(itemnamao[0],'x'),sizearmos(itemnamao[0],'y'),1);
            if ((itemtemp==1) && (itemnamao[0]==itemnumeroeh[numeroitennm][0]) && (itemnamao[1]==itemnumeroeh[numeroitennm][1]) && (((itemnamao[0]==15) && (itemnamao[1]<=6)) || (itemnamao[0]==17))) {
              if (itemnumeroeh[numeroitennm][2]+itemnamao[2]<250) {
                itemnumeroeh[numeroitennm][2]+=itemnamao[2];
                itemnamao[2]=0;
              }
              else {
                itemnamao[2]=itemnumeroeh[numeroitennm][2]+itemnamao[2]-250;
                itemnumeroeh[numeroitennm][2]=250;
              }
              if (itemnamao[2]==0) {
                carregarar=0; itemnamao[0]=0; itemnamao[1]=0; itemnamao[2]=0;
              }
            }
            //troca de item
            else if (itemtemp==1) {
              int itemnamao2[3];
              itemnamao2[0]=itemnumeroeh[numeroitennm2][0];
              itemnamao2[1]=itemnumeroeh[numeroitennm2][1];
              itemnamao2[2]=itemnumeroeh[numeroitennm2][2];

              retiraritem(numeroitennm2,1);
              colocaritem((mousemovidox-589)/29,(mousemovidoy-296)/29,itemnamao[0],itemnamao[1],itemnamao[2],1);

              itemnamao[0]=itemnamao2[0];
              itemnamao[1]=itemnamao2[1];
              itemnamao[2]=itemnamao2[2];
            }
          }
          //retira item
          else {
            itemnamao[0]=itemnumeroeh[numeroitennm][0]; itemnamao[1]=itemnumeroeh[numeroitennm][1]; itemnamao[2]=itemnumeroeh[numeroitennm][2];
            carregarar=1;
            retiraritem(numeroitennm,1);
          }
        }
        //Guarda item no inventario ou troca.
        else if (carregarar) {
          if (itemnamao[0]) {
            int itemtemp=checarsecabe((mousemovidox-589)/29,(mousemovidoy-296)/29,sizearmos(itemnamao[0],'x'),sizearmos(itemnamao[0],'y'),1);
            if (itemtemp<=1) {
              int itemnamao2[3];
              if (itemtemp==1) {
                itemnamao2[0]=itemnumeroeh[numeroitennm2][0];
                itemnamao2[1]=itemnumeroeh[numeroitennm2][1];
                itemnamao2[2]=itemnumeroeh[numeroitennm2][2];
                retiraritem(numeroitennm2,1);
              }
              colocaritem((mousemovidox-589)/29,(mousemovidoy-296)/29,itemnamao[0],itemnamao[1],itemnamao[2],1);
              if (itemtemp==1) {
                itemnamao[0]=itemnamao2[0];
                itemnamao[1]=itemnamao2[1];
                itemnamao[2]=itemnamao2[2];
              }
              else { carregarar=0; itemnamao[0]=0; itemnamao[1]=0; itemnamao[2]=0; }
            }
          }
        }
      }
     //  *Fim: Guardar itens no inventario.

     //  *Inicio: Equipar, retirar, trocar de item.
      int contarempaoe;

      for (contarempaoe=1;contarempaoe<=12;contarempaoe++) {
        if (mouseverondeclia(opcoesdeitens(contarempaoe,'x',0),opcoesdeitens(contarempaoe,'x',0)+opcoesdeitens(contarempaoe,'w',0),opcoesdeitens(contarempaoe,'y',0),opcoesdeitens(contarempaoe,'y',0)+opcoesdeitens(contarempaoe,'h',0))) {
           if (((itemnamao[0]==opcoesdeitens(contarempaoe,'b',0) && (contarempaoe!=4)) || ((((itemnamao[0]>=4) && (itemnamao[0]<=8)) || (itemnamao[0]==16)) && (contarempaoe==4))) && (carregarar==1)) {
            int tipoequip=itemnamao[0],qualequip=itemnamao[1],addequip=itemnamao[2];
            if ((equimaent(tipoequip,qualequip,addequip,1,0)) && ((meusstatsua.forca < equimaent(tipoequip,qualequip,addequip,1,1)) || (meusstatsua.agilidade < equimaent(tipoequip,qualequip,addequip,1,2)) || (meusstatsua.vitalidade < equimaent(tipoequip,qualequip,addequip,1,3)) || (meusstatsua.inteligencia < equimaent(tipoequip,qualequip,addequip,1,4)))) {
                Error("Falta de atributos minímos para utilizar!",ERRO_AVISO);
            }
            else {
              //equipar
              if (opcoesdeitens(contarempaoe,'a',0)==0) {
                opcoesdeitens(contarempaoe,itemnamao[1],itemnamao[2]);
                if (contarempaoe==4) { equipamentos.mao1tipo=itemnamao[0]; if (equipamentos.mao1tipo==5) { personagem.qual=2; } else if (equipamentos.mao1tipo==8) { personagem.qual=3; } else if (equipamentos.mao1tipo==7) { personagem.qual=4; } else if (equipamentos.mao1tipo==4) { personagem.qual=5; } else if (equipamentos.mao1tipo==6) { personagem.qual=6; } else if (equipamentos.mao1tipo==16) { personagem.qual=7; } }
                carregarar=0; itemnamao[0]=0; itemnamao[1]=0; itemnamao[2]=0;
              }
              //trocar com o item na mao
              else {
                int tempada=itemnamao[1],tempada2=itemnamao[2]; itemnamao[1]=opcoesdeitens(contarempaoe,'a',0); itemnamao[2]=opcoesdeitens(contarempaoe,'c',0); opcoesdeitens(contarempaoe,tempada,tempada2);
                if (contarempaoe==4) {
                  tempada2=itemnamao[0]; itemnamao[0]=equipamentos.mao1tipo; equipamentos.mao1tipo=tempada2;
                  if (equipamentos.mao1tipo==5) { personagem.qual=2; } else if (equipamentos.mao1tipo==8) { personagem.qual=3; } else if (equipamentos.mao1tipo==7) { personagem.qual=4; } else if (equipamentos.mao1tipo==4) { personagem.qual=5; } else if (equipamentos.mao1tipo==6) { personagem.qual=6; } else if (equipamentos.mao1tipo==16) { personagem.qual=7; }
                }
              }
            }
          }
          //retirar
          else if ((opcoesdeitens(contarempaoe,'a',0)!=0) && (carregarar==0)) {
            itemnamao[0]=opcoesdeitens(contarempaoe,'b',0); itemnamao[1]=opcoesdeitens(contarempaoe,'a',0); itemnamao[2]=opcoesdeitens(contarempaoe,'c',0);
            opcoesdeitens(contarempaoe,0,0); carregarar=1;
            if (contarempaoe==4) { personagem.qual=1; }
          }
          contarempaoe=16;
        }
      }
     //  *Fim: Equipar, retirar, trocar de item.
    }
    else if ((inventarioon) && (BauMenuOn)) {
      if (mousemovidox>=355) {
        if (mouseverondeclia(364,567,63,469)) {
          //retira item do inventario/atualiza item
          if ((numeroitennm=itensbau[(mousemovidoy-64)/29][(mousemovidox-365)/29])) {
            //atualiza item
            if (carregarar) {
              int itemtemp=checarsecabe((mousemovidox-365)/29,(mousemovidoy-64)/29,sizearmos(itemnamao[0],'x'),sizearmos(itemnamao[0],'y'),3);
              //troca de item
              if (itemtemp==1) {
                int itemnamao2[3];
                itemnamao2[0]=itembau_numero[numeroitennm2][0];
                itemnamao2[1]=itembau_numero[numeroitennm2][1];
                itemnamao2[2]=itembau_numero[numeroitennm2][2];

                retiraritem(numeroitennm2,3);
                colocaritem((mousemovidox-365)/29,(mousemovidoy-64)/29,itemnamao[0],itemnamao[1],itemnamao[2],3);

                itemnamao[0]=itemnamao2[0];
                itemnamao[1]=itemnamao2[1];
                itemnamao[2]=itemnamao2[2];
              }
            }
            //retira item
            else {
              itemnamao[0]=itembau_numero[numeroitennm][0]; itemnamao[1]=itembau_numero[numeroitennm][1]; itemnamao[2]=itembau_numero[numeroitennm][2];
              carregarar=1;
              retiraritem(numeroitennm,3);
            }
          }
          //Guarda item no inventario ou troca.
          else if (carregarar) {
            if (itemnamao[0]) {
              int itemtemp=checarsecabe((mousemovidox-365)/29,(mousemovidoy-64)/29,sizearmos(itemnamao[0],'x'),sizearmos(itemnamao[0],'y'),3);
              if (itemtemp<=1) {
                int itemnamao2[3];
                if (itemtemp==1) {
                  itemnamao2[0]=itembau_numero[numeroitennm2][0];
                  itemnamao2[1]=itembau_numero[numeroitennm2][1];
                  itemnamao2[2]=itembau_numero[numeroitennm2][2];
                  retiraritem(numeroitennm2,3);
                }
                colocaritem((mousemovidox-365)/29,(mousemovidoy-64)/29,itemnamao[0],itemnamao[1],itemnamao[2],3);
                if (itemtemp==1) {
                  itemnamao[0]=itemnamao2[0];
                  itemnamao[1]=itemnamao2[1];
                  itemnamao[2]=itemnamao2[2];
                }
                else { carregarar=0; itemnamao[0]=0; itemnamao[1]=0; itemnamao[2]=0; }
              }
            }
          }
          //  *Fim: Guardar itens no inventario.
        }
      }
      else {
        BauMenuOn=0;
        inventarioon=0;
      }
    }
    else if ((MagicMenuOn) && (mousemovidox>=578)) {
       int percorremagic;
       for (percorremagic=0;percorremagic<MagicNumAtual;percorremagic++) {
         if (mouseverondeclia(594,790,51+percorremagic*60,87+percorremagic*60)) {
           magicasel=minhasmagicas[percorremagic].nummagic;
           MagicMenuOn=0;
         }
       }
    }
    else if ((charmenuon) && (mousemovidox<=224)) {
      if (mouseverondeclia(167,209,142,159)) addbotaoclick=1;
      else if (mouseverondeclia(167,209,172,189)) addbotaoclick=2;
      else if (mouseverondeclia(167,209,202,219)) addbotaoclick=3;
      else if (mouseverondeclia(167,209,232,249)) addbotaoclick=4;
    }
    else if (mousemovidoy>=534) {
    //char ?
    }
    else if ((mostrarmenu) && (mouseverondeclia(279,510,134,364))) {
      if (mouseverondeclia(487,504,134,144)) { mostrarmenu=0; inventarioon=0; }
      else if (mouseverondeclia(293,496,147,350)) {
        if ((itemnamao[0]!=0) && (carregarar!=0)) { carregarar=0; itemnamao[0]=0; itemnamao[1]=0; itemnamao[2]=0; meusstatsua.dinheiro+=50; }
        else if ((checarsecabe((mousemovidox-294)/29,(mousemovidoy-148)/29,0,0,2)==1) && (carregarar==0) && ((numeroitennm=vendetrocatemp[(mousemovidoy-148)/29][(mousemovidox-294)/29]) != 0)) {
          if ((int)meusstatsua.dinheiro-100>=0) {
            if (colocaritem_procurar(itemvende_temp[numeroitennm][0],itemvende_temp[numeroitennm][1],itemvende_temp[numeroitennm][2]))
              meusstatsua.dinheiro-=100;
            else
              Error("Inventário cheio.",ERRO_AVISO);
          }
          else
            Error("Dinheiro insuficiente",ERRO_AVISO);
        }
      }
    }
    else if (mousemovidoy<534) {
      if (((!CursorUsando[0]) || (keystate[SDLK_LSHIFT])) && (itenschao[0][(int)((mousemovidoy+ypos)/48)][(int)((mousemovidox+xpos)/64)])) {
        personagem.SegueOq=3;
        personagem.SegueID=(int)((mousemovidox+xpos)/64);
        SegueIDAux=(int)((mousemovidoy+ypos)/48);
        estaaandar=1;

        pathFindPadrao((mousemovidox+xpos)/16,(mousemovidoy+ypos)/16,&personagem.pathFind);

        personagem.acao=(lctrlpress==1)?2:1;
      }
      else if (((!CursorUsando[0]) || (keystate[SDLK_LSHIFT])) && (carregarar)) {
        int posxtesttemp=(int)((mousemovidox+xpos)/64),posytesttemp=(int)((mousemovidoy+ypos)/48);
        if (!mapobjetos[posytesttemp][posxtesttemp]) {
          if (!mapcaminhar[(int)((mousemovidoy+ypos)/16)][(int)((mousemovidox+xpos)/16)]) {
            itenschao[0][posytesttemp][posxtesttemp]=itemnamao[0];
            itenschao[1][posytesttemp][posxtesttemp]=itemnamao[1];
            itenschao[2][posytesttemp][posxtesttemp]=itemnamao[2];
            carregarar=0;
          }
        }
      }
      else {
        if ((mapcaminhar[(int)((mousemovidoy+ypos)/16)][(int)((mousemovidox+xpos)/16)]==2) && (personagem.qual==7)) {
          personagem.acao=4; personagem.imagem=0;
          boiastemp[0]=mousemovidox+xpos;
          boiastemp[1]=mousemovidoy+ypos;
          float angoloux2=(personagem.x-xpos+50)-mousemovidox;
          float angolouy2=mousemovidoy-(personagem.y-ypos+70);
          float tempfasda2=atan(angolouy2/angoloux2)/M_PI*180;
          int anguloasda2=tempfasda2+((angoloux2<0)?180:((angolouy2<0)?360:0));
          boiastemp2[0]=cos(anguloasda2*M_PI/180)*5.0f;
          boiastemp2[1]=sin(anguloasda2*M_PI/180)*-5.0f;
          personagem.lado=arrumaragoliuasd(personagem.x+48,personagem.y+68,mousemovidox+xpos,mousemovidoy+ypos);
        }
        else {
          estaaandar=1;
          chamarPathFind('c');
        }
      }
    }
  }


//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- SDL_MOUSEBUTTONUP -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
  if ((event->type == SDL_MOUSEBUTTONUP) && ( event->button.button == SDL_BUTTON_LEFT )) {
    estaaandar=0;
    addbotaoclick=0;
    if (charmenuon) {
      if (meusstatsua.pontos>0) {
        meusstatsua.pontos--;
        if ((mouseverondeclia(167,209,142,159)) && (MAX_FORCA>meusstatsua.forca)) meusstatsua.forca++;
        else if ((mouseverondeclia(167,209,172,189)) && (MAX_AGILIDADE>meusstatsua.agilidade)) meusstatsua.agilidade++;
        else if ((mouseverondeclia(167,209,202,219)) && (MAX_VITALIDADE>meusstatsua.vitalidade)) meusstatsua.vitalidade++;
        else if ((mouseverondeclia(167,209,232,249)) && (MAX_INTELIGENCIA>meusstatsua.inteligencia)) meusstatsua.inteligencia++;
        else { meusstatsua.pontos++; }
      }
    }
    if (menus.ativo==1) {
      char Temp_Num=Info_Menu('n',1),Temp_Itens;
      int pox,poy;
      poy=300-(Temp_Num*15+54)/2;
      pox=400-Info_Menu('t',1)/2;
      menus.itemsel=0;
      for (Temp_Itens=0;Temp_Itens<Temp_Num;Temp_Itens++) {
        if (mouseverondeclia(pox,pox+Info_Menu('t',1),poy+40+17*Temp_Itens,poy+55+17*Temp_Itens)) {
          Info_Menu(Temp_Itens+1,2);
        }
      }
    }
  }
  if (event->type == SDL_KEYUP) {
    if (event->key.keysym.sym == SDLK_LCTRL) {
      if ((personagem.acao==2) && (antesaltpress==-1))
        personagem.acao=1;
      lctrlpress=0;
    }
  }
  if (event->type == SDL_KEYDOWN) {
    /*
            if (event->key.keysym.sym == SDLK_UP) { if ((chatAntPosit<5) && (chatstrAntr[chatAntPosit][0]!='\0')) { strcpy(chatstr,chatstrAntr[chatAntPosit]); chatAntPosit++; curosrchar=strlen(chatstr); } }
        else if (event->key.keysym.sym == SDLK_DOWN) { chatAntPosit--; if (chatAntPosit<=0) { chatAntPosit=0; memset(chatstr,'\0',sizeof(chatstr)); curosrchar=0; } else { strcpy(chatstr,chatstrAntr[chatAntPosit-1]); curosrchar=strlen(chatstr); } }
        */
      if ((event->key.keysym.sym == SDLK_RETURN) || (event->key.keysym.sym == SDLK_KP_ENTER)) { Tela_jogo_ChatAtivar(); }
      else if (event->key.keysym.sym == SDLK_1) { personagem.aura=1; personagem.auraimagem=0; }
      else if (event->key.keysym.sym == SDLK_2) { personagem.aura=2; personagem.auraimagem=0; }
      else if (event->key.keysym.sym == SDLK_3) { personagem.aura=3; personagem.auraimagem=0; }
      else if (event->key.keysym.sym == SDLK_4) { personagem.aura=4; personagem.auraimagem=0; }
      else if (event->key.keysym.sym == SDLK_5) { personagem.aura=5; personagem.auraimagem=0; }
      else if (event->key.keysym.sym == SDLK_6) { personagem.aura=6; personagem.auraimagem=0; }
      else if (event->key.keysym.sym == SDLK_7) { Add_Particulas(1,1,50,50); }
      else if (event->key.keysym.sym == SDLK_8) { Add_Particulas(1,1,100,100); }
      else if (event->key.keysym.sym == SDLK_LCTRL) { if ((personagem.acao==1) && (antesaltpress==-1)) { personagem.acao=2; } lctrlpress=1; }
//      else if (event.key.keysym.sym == SDLK_x) { if (SDL_GetMouseState(NULL, NULL)&SDL_BUTTON(1)) { if (personagem.acao!=4) { antesaltpress=personagem.acao; personagem.acao=4; personagem.imagem=0; } personagem.lado=arrumaragoliuasd(mousemovidox+xpos,mousemovidoy+ypos); atacar(1); movermouse=1; } }
      else if (event->key.keysym.sym == SDLK_v) { antesaltpress=personagem.acao; personagem.acao=6; personagem.imagem=0; }
      else if (event->key.keysym.sym == SDLK_d) { antesaltpress=personagem.acao; personagem.acao=3; personagem.imagem=0; }
      else if (event->key.keysym.sym == SDLK_i) { if (mostrarmenu==0) { inventarioon=1-inventarioon; MagicMenuOn=0; } if (BauMenuOn) BauMenuOn=0; }
      else if (event->key.keysym.sym == SDLK_m) { if (mostrarmenu==0) { MagicMenuOn=1-MagicMenuOn; inventarioon=0; } if (BauMenuOn) BauMenuOn=0; }
      else if (event->key.keysym.sym == SDLK_c) { charmenuon=1-charmenuon; }
      else if (event->key.keysym.sym == SDLK_LALT) { mouseencima^=2; }
      else if (event->key.keysym.sym == SDLK_l) { personagem.levelup=0; meusstatsua.pontos+=5; }

      else if (event->key.keysym.sym == SDLK_r) { personagem.vida=100; }
      else if (event->key.keysym.sym == SDLK_p) {
        if (personagem.qual==7) {
          boias[1].x+=boias[1].fx;
          boias[1].y+=boias[1].fy;

          int raioboia=sqrt(pow((int)(boias[1].x)-personagem.x,2)+pow((int)(boias[1].y)-personagem.y,2));
          if (raioboia<=120) { personagem.imagem=3; }
          else if (raioboia<=170) { personagem.imagem=2; }
          else if (raioboia<=220) { personagem.imagem=1; }
          else { personagem.imagem=11; }
          flagpuchou=1;
        }
      }
  }
}

void Tela_Jogo_Depois_Eventos() {
  Personagem_Imagens();

  if (numarrow) deletar_arrow();
  if (nummagic) deletar_magic();

  CheckInteligent();
  interacao_crescer();

  IA_Monstro();
  IA_Pesca();
  IA_Animal();
}

void Tela_Jogo_Iniciar() {
  EditBox('n', NULL, 1, 209, 513, 267, GUI_INATIVO, EDITBOX_HISTORICO|TEXTO_EMOTICO, EditChat);
  EditBox('n', NULL, 2, 478, 513, 85,GUI_INATIVO, 0, EditChat);
  Botao('n', "OK", 3, 566, 513, 25, GUI_INATIVO, ClickChat);
  ListBox('n', 4, 209, 431, 382, 80, GUI_INATIVO, SCROLL_INVERSO|TEXTO_EMOTICO|LISTBOX_FUNDOTRANS, NULL);

  GUI_setecionar(1);
}
