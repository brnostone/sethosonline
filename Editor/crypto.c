/*
 * crypto.c
 *
 *  Created on: 22/10/2009
 *      Author: bruno
 */

#include <string.h>

#include "Header/crypto.h"

int psed_rand(int random_seed) {
  random_seed=random_seed * 1103515245 + 12345;
  return (unsigned int) (random_seed / 65536) % 32768;
}

void Crypto_geradorkey(int numkeyant, int *chave) {
  int contatemp;
  memset(chave, '\0', sizeof(chave));
  for (contatemp=0; contatemp < 13; contatemp++) {
    numkeyant=psed_rand(numkeyant) % 100;
    chave[contatemp]=numkeyant;
  }
}

int Crypto_uchar(unsigned char caracter, int *chave, int *chave2, unsigned int incre) {
  int cryptoChar=0;

  cryptoChar=(~((int)(((int)(caracter)^chave2[incre%13])^(incre%10))*((incre%2)+1))*-1)^(int)(incre-(incre%30));
  cryptoChar^=chave[incre%13];
  if (incre&1) cryptoChar=(~(cryptoChar^0x4A2))*-1;
  else cryptoChar<<=1;

  return cryptoChar;
}


unsigned char Decrypto_uchar(int charCodif, int *chave, int *chave2, unsigned int incre) {
  int cryptoChar=charCodif;

  if (incre&1) cryptoChar=(~(cryptoChar*-1))^0x4A2;
  else cryptoChar>>=1;
  cryptoChar^=chave[incre%13];
  cryptoChar=(int)((~((cryptoChar^(incre-(incre%30)))*-1))/((incre%2)+1));
  cryptoChar=(cryptoChar^(incre%10))^chave2[incre%13];

  return (unsigned char)(cryptoChar);
}
