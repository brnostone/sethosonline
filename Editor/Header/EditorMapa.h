#ifndef EDITORMAPA_H_
#define EDITORMAPA_H_

  #include "GUI.h"

  void InitEditMap();

  void drawEditMapa();
  void eventEditMapa(GUIParms *parm);

  void drawSelectObj();
  void eventSelectObj(GUIParms *parm);

  void carregarMapa(GUIParms *parm);
  void redimencionarMapa(GUIParms *parm);

  void selectOpcao(GUIParms *parm);
  void selectTipo(GUIParms *parm);

  void salvarMapa(GUIParms *parm);

  void cancelPortal(GUIParms *parm);
  void salvarPortal(GUIParms *parm);

  void EditLighAtivo(GUIParms *parm);

  void EditLighAtualizaLight();
  void EditLighNovaLight(GUIParms *parm);
  void EditLight_setColor(GUIParms *parm);
  void EditLighAtualizaCor(GUIParms *parm);

  void exportarLightMap(GUIParms *parm);
  void importarLightMap(GUIParms *parm);

  void drawEditLighFerramentas();
  void EditLighFerramentas(GUIParms *parm);

#endif /* EDITORMAPA_H_ */

