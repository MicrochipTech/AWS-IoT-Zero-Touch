/*
 * Copyright (C) 2006-2016 wolfSSL Inc.  All rights reserved.
 *
 * This license is only for commercial evaluation purposes.  
 * 
 * Redistribution of the source and binary forms, with or without
 * modification, is not permitted.
 * 
 * To obtain a commercial license from wolfSSL for redistribution please contact licensing @wolfssl.com
 *
 * THIS SOFTWARE IS PROVIDED BY WOLFSSL "AS IS" AND ANY EXPRESS OR IMPLIED
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT ARE
 * EXPRESSLY AND SPECIFICALLY DISCLAIMED. IN NO EVENT SHALL WOLFSSL BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
 * STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
 * ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 * Contact licensing@wolfssl.com with any questions or comments.
 *
 * http://www.wolfssl.com
 */



#ifndef WOLF_CRYPT_DES3_H
#define WOLF_CRYPT_DES3_H

#include <wolfssl/wolfcrypt/types.h>

#ifndef NO_DES3

#ifdef HAVE_FIPS
/* included for fips @wc_fips */
#include <cyassl/ctaocrypt/des3.h>
#endif

#ifdef __cplusplus
    extern "C" {
#endif

#ifndef HAVE_FIPS /* to avoid redefinition of macros */
#define WOLFSSL_3DES_CAVIUM_MAGIC 0xBEEF0003

enum {
    DES_ENC_TYPE    = 2,     /* cipher unique type */
    DES3_ENC_TYPE   = 3,     /* cipher unique type */
    DES_BLOCK_SIZE  = 8,
    DES_KS_SIZE     = 32,

    DES_ENCRYPTION  = 0,
    DES_DECRYPTION  = 1
};

#define DES_IVLEN 8
#define DES_KEYLEN 8
#define DES3_IVLEN 8
#define DES3_KEYLEN 24


#ifdef STM32F2_CRYPTO
enum {
    DES_CBC = 0,
    DES_ECB = 1
};
#endif


/* DES encryption and decryption */
typedef struct Des {
    word32 reg[DES_BLOCK_SIZE / sizeof(word32)];      /* for CBC mode */
    word32 tmp[DES_BLOCK_SIZE / sizeof(word32)];      /* same         */
    word32 key[DES_KS_SIZE];
} Des;


/* DES3 encryption and decryption */
typedef struct Des3 {
    word32 key[3][DES_KS_SIZE];
    word32 reg[DES_BLOCK_SIZE / sizeof(word32)];      /* for CBC mode */
    word32 tmp[DES_BLOCK_SIZE / sizeof(word32)];      /* same         */
#ifdef HAVE_CAVIUM
    int     devId;           /* nitrox device id */
    word32  magic;           /* using cavium magic */
    word64  contextHandle;   /* nitrox context memory handle */
#endif
} Des3;
#endif /* HAVE_FIPS */

WOLFSSL_API int  wc_Des_SetKey(Des* des, const byte* key,
                               const byte* iv, int dir);
WOLFSSL_API void wc_Des_SetIV(Des* des, const byte* iv);
WOLFSSL_API int  wc_Des_CbcEncrypt(Des* des, byte* out,
                                   const byte* in, word32 sz);
WOLFSSL_API int  wc_Des_CbcDecrypt(Des* des, byte* out,
                                   const byte* in, word32 sz);
WOLFSSL_API int  wc_Des_EcbEncrypt(Des* des, byte* out,
                                   const byte* in, word32 sz);

WOLFSSL_API int  wc_Des3_SetKey(Des3* des, const byte* key,
                                const byte* iv,int dir);
WOLFSSL_API int  wc_Des3_SetIV(Des3* des, const byte* iv);
WOLFSSL_API int  wc_Des3_CbcEncrypt(Des3* des, byte* out,
                                    const byte* in,word32 sz);
WOLFSSL_API int  wc_Des3_CbcDecrypt(Des3* des, byte* out,
                                    const byte* in,word32 sz);

#ifdef HAVE_CAVIUM
    WOLFSSL_API int  wc_Des3_InitCavium(Des3*, int);
    WOLFSSL_API void wc_Des3_FreeCavium(Des3*);
#endif

#ifdef __cplusplus
    } /* extern "C" */
#endif

#endif /* NO_DES3 */
#endif /* WOLF_CRYPT_DES3_H */

