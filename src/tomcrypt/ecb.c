#include "mycrypt.h"

#ifdef ECB

int ecb_start(int cipher, const unsigned char *key, int keylen, int num_rounds, symmetric_ECB *ecb)
{
   if (cipher_is_valid(cipher) == CRYPT_ERROR) {
      return CRYPT_ERROR;
   }
   ecb->cipher = cipher;
   ecb->blocklen = cipher_descriptor[cipher].block_length;
   return cipher_descriptor[cipher].setup(key, keylen, num_rounds, &ecb->key);
}

void ecb_encrypt(const unsigned char *pt, unsigned char *ct, symmetric_ECB *ecb)
{
   cipher_descriptor[ecb->cipher].ecb_encrypt(pt, ct, &ecb->key);
}

void ecb_decrypt(const unsigned char *ct, unsigned char *pt, symmetric_ECB *ecb)
{
   cipher_descriptor[ecb->cipher].ecb_decrypt(ct, pt, &ecb->key);
}

#endif


static const char *ID_TAG = "ecb.c"; 
 