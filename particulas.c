#include <stdlib.h>

#include "Header/global.h"
#include "Header/opengl.h"
#include "Header/mapas.h"
#include "Header/particulas.h"

#define NUM_PARICULA_FOGO 25
#define NUM_PARICULA_FIREBALL 30

typedef struct {
 float life;
 float fade;

 float x;
 float y;

 float xi;
 float yi;
} particula_s;

struct {
  char qual;
  char ativa;

  int id;

  int numeroparticula;
  int posicaox;
  int posicaoy;

  int temetaiias;
  particula_s *qualdetas;
} particula;

/*void resetparticulas(particula_s *particulas, int numparticula,int x,int y,int xi,int yi,float fade) {
particulas[numparticula].life=1.0f;
particulas[numparticula].fade=fade;
particulas[numparticula].x=x;
particulas[numparticula].y=y;

particulas[numparticula].xi=xi;
particulas[numparticula].yi=yi;
}

int checarnumepartic(char qual) {
  switch(qual) {
   case 1: { return NUM_PARICULA_FOGO; break; }
   case 2: { return NUM_PARICULA_FOGO; break; }
   case 3: { return NUM_PARICULA_FIREBALL; break; }
   case 4: { return NUM_PARICULA_FOGO; break; }
  }
}

float infsobreparticuas(char oq,char qual, int numero) {
  float retrunaon2;
  if (oq==2) {
    switch(qual) {
      case 1: { if (particula.temetaiias<=SDL_GetTicks()/100) { particula.numeroparticula2++; if (particula.numeroparticula<=particula.numeroparticula2) { particula.ativa=0; } } else { resetparticulas(particula.qualdetas,numero,particula.posicaox+(int)(rand()%30),particula.posicaoy+(int)(rand()%15),0,0,(float) (rand()%5)/50.0f+0.03f); } break; }
      case 2: { if (particula.temetaiias<=SDL_GetTicks()/100) { particula.numeroparticula2++; if (particula.numeroparticula<=particula.numeroparticula2) { particula.ativa=0; } } else { resetparticulas(particula.qualdetas,numero,particula.posicaox+(int)(rand()%30),particula.posicaoy+(int)(rand()%15),0,0,(float) (rand()%5)/50.0f+0.03f); } break; }
      case 3: { resetparticulas(particula.qualdetas,numero,particula.posicaox,particula.posicaoy+(int)(rand()%15),0,0,(float) (rand()%5)/50.0f+0.04f); break; }
      case 4: { if (particula.temetaiias<=SDL_GetTicks()/100) { particula.numeroparticula2++; if (particula.numeroparticula<=particula.numeroparticula2) { particula.ativa=0; } } else { resetparticulas(particula.qualdetas,numero,particula.posicaox+(int)(rand()%30),particula.posicaoy+(int)(rand()%15),0,0,(float) (rand()%5)/50.0f+0.03f); } break; }
    }
  }
  if (oq==3) {
    switch(qual) {
      case 1: { retrunaon2=17; break; }
      case 2: { retrunaon2=17; break; }
      case 3: { retrunaon2=22; break; }
    }
    return retrunaon2;
  }
  if (oq==4) {
    switch(qual) {
      case 1: { retrunaon2=17; break; }
      case 2: { retrunaon2=17; break; }
      case 3: { retrunaon2=22; break; }
    }
    return retrunaon2;
  }
  else if (oq==5) {
    switch(qual) {
      case 1: { if (numero!='a') { particula.qualdetas[numero].y-=2; } break; }
      case 2: { if (numero!='a') { particula.qualdetas[numero].y-=2; } break; }
      case 3: { if (numero=='a') { particula.posicaox+=5; } break; }
    }
  }
  else if (oq==6) {
    switch(qual) {
     case 1: { retrunaon2=0; break; }
     case 2: { retrunaon2=0; break; }
     case 3: { retrunaon2=0; break; }
    }
    return retrunaon2;
  }
  if (oq==7) {
    switch(qual) {
      case 1: { retrunaon2=0; break; }
      case 2: { retrunaon2=1; break; }
      case 3: { retrunaon2=2; break; }
    }
    return retrunaon2;
  }
}

void criaparticulas(char qual,int id,int posicaox,int posicaoy) {
  particula.id=id;
  particula.qual=qual;
  particula.ativa=1;
  particula.posicaox=posicaox;
  particula.posicaoy=posicaoy;
  particula.numeroparticula=checarnumepartic(qual);
  particula.temetaiias=temetaiias=(SDL_GetTicks()/100)+25;
  particula.numeroparticula2=0;
  particula.qualdetas = (particula_s *)malloc (sizeof (particula_s) * particula.numeroparticula);
  int numparticula=0;
  while (numparticula < particula.numeroparticula) {
    infsobreparticuas(2,particula.qual,numparticula);
    numparticula++;
  }
}

int draw_particulas2() {
  infsobreparticuas(5,particula.qual,'a');
  int numparticula=0;
  while (numparticula < particula.numeroparticula) {
    DrawIMG(particulas[(int)(infsobreparticuas(7,particula.qual,numparticula))], particula.qualdetas[numparticula].x-xpos, particula.qualdetas[numparticula].y-ypos,(int)(infsobreparticuas(3,particula.qual,numparticula)),(int)(infsobreparticuas(4,particula.qual,numparticula)),0,0);

    particula.qualdetas[numparticula].life -= particula.qualdetas[numparticula].fade;

    infsobreparticuas(5,particula.qual,numparticula);

    if (particula.qualdetas[numparticula].life <= 0.0f ) {
      infsobreparticuas(2,particula.qual,numparticula);
    }
    numparticula++;
  }
}

*/

void Reset_Particulas(particula_s *particulas2, int numparticula,float x,float y,float xi,float yi,float fade) {
  particulas2[numparticula].life=1.0f;
  particulas2[numparticula].fade=fade;

  particulas2[numparticula].x=x;
  particulas2[numparticula].y=y;

  particulas2[numparticula].xi=xi;
  particulas2[numparticula].yi=yi;
}

int checarnumepartic(char qual) {
  switch(qual) {
   case 1: { return NUM_PARICULA_FOGO; break; }
  }
  return 0;
}

void Inf_Particulas(char oq,char qual, int numero) {
  int retrunaon2;
  if (oq==1) {
    switch(qual) {
      case 1: {
        Reset_Particulas(particula.qualdetas,numero,(float)(particula.posicaox),(float)(particula.posicaoy),(float)(rand()%500)/100.0f+0.8f,(float)(rand()%201)/100.0f-1.0f,(float) (rand()%5)/50.0f+0.18f);
        break;
      }
    }
  }
  else if (oq==2) {
    switch(qual) {
      case 1: { if (numero!='a') { particula.qualdetas[numero].x+=particula.qualdetas[numero].xi; particula.qualdetas[numero].y+=particula.qualdetas[numero].yi; } break; }
    }
  }
  else if (oq=='r') {
    switch(qual) {
      case 1: { retrunaon2=250; break; }
    }
  }
  else if (oq=='g') {
    switch(qual) {
      case 1: { retrunaon2=0; break; }
    }
  }
  else if (oq=='b') {
    switch(qual) {
      case 1: { retrunaon2=0; break; }
    }
  }
//  return retrunaon2;
}

void Add_Particulas(char qual,int id,int posicaox,int posicaoy) {
  particula.id=id;
  particula.qual=qual;
  particula.ativa=1;
  particula.posicaox=posicaox;
  particula.posicaoy=posicaoy;
  particula.numeroparticula=checarnumepartic(qual);
  particula.temetaiias=0;
//  particula.numeroparticula2=0;
  particula.qualdetas = (particula_s *)malloc (sizeof (particula_s) * particula.numeroparticula);
  int numparticula=0;
  while (numparticula < particula.numeroparticula) {
    Inf_Particulas(1,particula.qual,numparticula);
    numparticula++;
  }
  particula.temetaiias=1;
}

void Draw_Particulas() {
  if (particula.ativa==1) {
    Inf_Particulas(2,particula.qual,'a');
    int numparticula=0;
    while (numparticula < particula.numeroparticula) {
      if (particula.qualdetas[numparticula].life > 0.0f ) {
  //    printf("%d %d %d %d\n",particula.qualdetas[numparticula].x-xpos,particula.qualdetas[numparticula].y-ypos,particula.qualdetas[numparticula].x,particula.qualdetas[numparticula].y);
  //      DrawPixel(screen,particula.qualdetas[numparticula].x-xpos,particula.qualdetas[numparticula].y-ypos,infsobreparticuas('r',particula.qual,numparticula),infsobreparticuas('g',particula.qual,numparticula),infsobreparticuas('b',particula.qual,numparticula));
        Inf_Particulas(2,particula.qual,numparticula);

        //DrawIMG_RGBA(particulas[0], (int)(particula.qualdetas[numparticula].x)-xpos,(int)(particula.qualdetas[numparticula].y)-ypos,17,17,0,0,255,255,255,255*particula.qualdetas[numparticula].life);
        DrawPixel((int)(particula.qualdetas[numparticula].x)-xpos,(int)(particula.qualdetas[numparticula].y)-ypos,184,0,0,255);
        particula.qualdetas[numparticula].life -= particula.qualdetas[numparticula].fade;
      }
      numparticula++;
    }
  }
}
