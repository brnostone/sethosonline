#ifndef AGRUPADOR_H_
#define AGRUPADOR_H_

Textura *fundoAlpha;

void drawAgrupAnim();
void drawAgrupImg();

void eventAgrupImg(GUIParms *parm);
void AgrupAnalizar(GUIParms *parm);

void AgrupRemoveFundo(GUIParms *parm);
void AgrupCorSombra(GUIParms *parm);
void AgrupConfigPasta(GUIParms *parm);

void AgrupCarregar(GUIParms *parm);
void AgrupSalvar(GUIParms *parm);

#endif /* AGRUPADOR_H_ */
