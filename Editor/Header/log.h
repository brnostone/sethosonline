#ifndef LOG_H_
#define LOG_H_

#include <stdarg.h>

enum ErroLevel {
  ERRO_AVISO,
  ERRO_FATAL
};

int logtemp;
void logging(int estado, char *gravar, ...);
void Error(char *msg, enum ErroLevel erLv);

#endif /* LOG_H_ */

