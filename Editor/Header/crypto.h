/*
 * crypto.h
 *
 *  Created on: 22/10/2009
 *      Author: bruno
 */

#ifndef CRYPTO_H_
#define CRYPTO_H_

  void Crypto_geradorkey(int numkeyant, int *chave);

  int Crypto_uchar(unsigned char caracter, int *chave, int *chave2, unsigned int incre);
  unsigned char Decrypto_uchar(int charCodif, int *chave, int *chave2, unsigned int incre);

#endif /* CRYPTO_H_ */
