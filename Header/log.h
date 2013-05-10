/*
 * log.h
 *
 *  Created on: 03/10/2009
 *      Author: bruno
 */

#ifndef LOG_H_
#define LOG_H_

  #include <stdarg.h>

  enum ErroLevel {
    ERRO_LOG,
    ERRO_AVISO,
    ERRO_FATAL
  };

  int ticjsja;

  void logging(int estado, char *gravar, ...);
  void Error(char *msg, enum ErroLevel erLv);

#endif /* LOG_H_ */
