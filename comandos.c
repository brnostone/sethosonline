#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

#include "Header/msgs.h"
#include "Header/global.h"
#include "Header/log.h"
#include "Header/comandos.h"

int OcorreuErro;

void ErrorPrim(char *msgerro) {
  if (!OcorreuErro)
    Error(msgerro, ERRO_AVISO);

  OcorreuErro=1;
}

double realizarcont(double n1,char tipo, double n2) {
  if (tipo=='+') n1+=n2;                      //soma
  else if (tipo=='-') n1-=n2;                 //subtracao
  else if (tipo=='*') n1*=n2;                 //multiplicacao
  else if (tipo=='/') { if (n2) n1/=n2; else ErrorPrim("Divisão por zero"); } //divisao
  else if (tipo=='%') n1=(int)(n1)%(int)(n2); //modulo
  else if (tipo=='^') n1=pow(n1,n2);          //potencia
  else if (tipo=='r') n1=pow(n2,1.0f/n1);     //raiz
  else if (tipo=='&') n1=(int)(n1)&(int)(n2); //and
  else if (tipo=='|') n1=(int)(n1)|(int)(n2); //or
  else if (tipo=='>') n1=(int)(n1)>>(int)(n2);//desloca os bits para direita
  else if (tipo=='<') n1=(int)(n1)<<(int)(n2);//desloca os bits para esquerda
  return n1;
}

int prioridades(char tipo) {
  //prioridade de execucao
  switch(tipo) {
    case '&':
      case '|':
        case '>':
          case '<':
            return 1;
    case '+':
      case '-':
        return 2;
    case '*':
      case '/':
        case '%':
          return 3;
    case '^':
      case 'r':
        return 4;
    default: { if (tipo!='\0') ErrorPrim("Operador invalido"); return -1; }
  }
}

double funcmat(char *var) {
  //cria as variaveis e zera todas
  char expresaodiv[100];
  char temp[30],prioridade,tipo[20],anteopr=1;
  int x=0,y=0,volta,contparnt=0,contposf=0,contposi=0;
  double numero[20];

  memset(numero,0.0f,sizeof(numero));
  memset(tipo,'\0',sizeof(tipo));
  memset(expresaodiv,'\0',sizeof(expresaodiv));

  //se tiver parenteses chama a I_EXEC_funcmat denovo e separa os numeros dos operadores
  for (;*var!='\0';var++,contposf++) {
    if (y>=20) ErrorPrim("Limite de operacoes ultrapassado");
    if ((*var==' ') || (*var=='\'')) continue;
    if (((isdigit(*var)) || (*var=='.') || ((anteopr>0) && ((*var=='-') || (*var=='+')))) && (!contparnt)) {
      if (anteopr==-1 ) ErrorPrim("Sintaxe errada, falta de operador depois do parenteses");
      if (x>=30) ErrorPrim("Numero muito grande");
      temp[x++]=*var;
      anteopr=0;
    }
    else if (*var=='(') {
      if (anteopr<=0) ErrorPrim("Sintaxe errada, falta de operador antes do operador");
      if (!contparnt) contposi=contposf;
      contparnt++;
    }
    else if (*var==')') {
      contparnt--;
      if (contparnt<0) ErrorPrim("Sintaxe errada, possue muitos ')'");
      if (!contparnt) {
        var=var-(contposf-contposi-1);
        memcpy(expresaodiv,var,contposf-contposi-1);
        sprintf(temp,"%.5f",funcmat(expresaodiv));
        memset(expresaodiv,'\0',sizeof(expresaodiv));

        var=var+(contposf-contposi-1);
        x=strlen(temp)+1;
        anteopr=-1;
      }
    }
    else if (!contparnt) {
      if (anteopr==1) ErrorPrim("Expressao invalido, operador com operador");
      temp[x]='\0'; x=0;
      numero[y]=atof(temp);
      tipo[y++]=*var; anteopr=1;
    }
  }
  if (contparnt>0) ErrorPrim("Sintaxe errada, possue muitos '('");
  temp[x]='\0';
  numero[y]=atof(temp);

  //executa as operacoes primeiro as com prioridade maior
  for (prioridade=4;prioridade>0;prioridade--) {
    for (x=0;x<=strlen(tipo);x++) {
      if (prioridades(tipo[x])==prioridade) {
        numero[x]=realizarcont(numero[x],tipo[x],numero[x+1]);
        for (volta=x;volta<(strlen(tipo));volta++) { tipo[volta]=tipo[volta+1]; numero[volta+1]=numero[volta+2]; }
        tipo[volta]='\0';
        numero[volta]=0.0f;
        x--;
      }
    }
  }

  return numero[0];
}

void comandos(char *comand) {
  char entrStr[256];

  strncpy(entrStr,comand,255);

  char *str;
  str=strtok( entrStr, " " );

  if (!strcmp(str,"/calc")) {
    OcorreuErro=0;
    str=strtok( NULL, " " );
    if (str) {
      double resultconta=funcmat(str);
      if (!OcorreuErro)
        Msgs_adicionar(17,"%.2lf",resultconta);
    }
  }
  else if (!strcmp(str,"/exit"))
    done=1;
  else if (!strcmp(str,"/t"))
    Msgs_adicionar(1,NULL);
  else
    Error("Comando inexistente.",ERRO_AVISO);
}
