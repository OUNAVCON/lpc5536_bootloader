/*--------------------------------------------------------------------------*/
/* Copyright 2021-2023 NXP                                                  */
/*                                                                          */
/* NXP Confidential. This software is owned or controlled by NXP and may    */
/* only be used strictly in accordance with the applicable license terms.   */
/* By expressly accepting such terms or by downloading, installing,         */
/* activating and/or otherwise using the software, you are agreeing that    */
/* you have read, and that you agree to comply with and are bound by, such  */
/* license terms. If you do not agree to be bound by the applicable license */
/* terms, then you may not retain, install, activate or otherwise use the   */
/* software.                                                                */
/*--------------------------------------------------------------------------*/

#ifndef MCUXCLRANDOMMODES_PRIVATE_CTRDRBG_H_
#define MCUXCLRANDOMMODES_PRIVATE_CTRDRBG_H_

#include <mcuxClConfig.h> // Exported features flags header

#include <mcuxClAes.h>
#include <internal/mcuxClRandom_Internal_Types.h>
#include <internal/mcuxClRandomModes_Private_Drbg.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Mode descriptor related defines for CTR_DRBGs */
#define MCUXCLRANDOMMODES_SECURITYSTRENGTH_CTR_DRBG_AES128 (128u)
#define MCUXCLRANDOMMODES_SECURITYSTRENGTH_CTR_DRBG_AES192 (192u)
#define MCUXCLRANDOMMODES_SECURITYSTRENGTH_CTR_DRBG_AES256 (256u)

#define MCUXCLRANDOMMODES_SEEDLEN_CTR_DRBG_AES128 (32u)
#define MCUXCLRANDOMMODES_SEEDLEN_CTR_DRBG_AES192 (40u)
#define MCUXCLRANDOMMODES_SEEDLEN_CTR_DRBG_AES256 (48u)

#if defined(MCUXCL_FEATURE_RANDOMMODES_DERIVATION_FUNCTION)
#define MCUXCLRANDOMMODES_ENTROPYINPUT_SIZE_INIT_CTR_DRBG_AES128 (39u)
#define MCUXCLRANDOMMODES_ENTROPYINPUT_SIZE_INIT_CTR_DRBG_AES192 (55u)
#define MCUXCLRANDOMMODES_ENTROPYINPUT_SIZE_INIT_CTR_DRBG_AES256 (71u)
#define MCUXCLRANDOMMODES_ENTROPYINPUT_SIZE_RESEED_CTR_DRBG_AES128  (23u)
#define MCUXCLRANDOMMODES_ENTROPYINPUT_SIZE_RESEED_CTR_DRBG_AES192  (39u)
#define MCUXCLRANDOMMODES_ENTROPYINPUT_SIZE_RESEED_CTR_DRBG_AES256  (55u)
#endif

#define MCUXCLRANDOMMODES_RESEED_INTERVAL_CTR_DRBG_AES128 (0x0001000000000000u)
#define MCUXCLRANDOMMODES_RESEED_INTERVAL_CTR_DRBG_AES192 (0x0001000000000000u)
#define MCUXCLRANDOMMODES_RESEED_INTERVAL_CTR_DRBG_AES256 (0x0001000000000000u)

/* Internal structure of a CTR_DRBG AES128 random context */
typedef struct
{
    MCUXCLRANDOMMODES_CONTEXT_DRBG_ENTRIES
    uint32_t key[MCUXCLAES_AES128_KEY_SIZE_IN_WORDS];
    uint32_t counterV[MCUXCLAES_BLOCK_SIZE_IN_WORDS];
} mcuxClRandomModes_Context_CtrDrbg_Aes128_t;

/* Internal structure of a CTR_DRBG AES192 random context */
#define MCUXCLRANDOMMODES_CONTEXT_CTR_DRBG_AES192_SIZE_KEY_IN_WORDS (6u)
typedef struct
{
    MCUXCLRANDOMMODES_CONTEXT_DRBG_ENTRIES
    uint32_t key[MCUXCLRANDOMMODES_CONTEXT_CTR_DRBG_AES192_SIZE_KEY_IN_WORDS];
    uint32_t counterV[MCUXCLAES_BLOCK_SIZE_IN_WORDS];
} mcuxClRandomModes_Context_CtrDrbg_Aes192_t;

/* Internal structure of a CTR_DRBG AES256 random context */
#define MCUXCLRANDOMMODES_CONTEXT_CTR_DRBG_AES256_SIZE_KEY_IN_WORDS (8u)
typedef struct
{
    MCUXCLRANDOMMODES_CONTEXT_DRBG_ENTRIES
    uint32_t key[MCUXCLRANDOMMODES_CONTEXT_CTR_DRBG_AES256_SIZE_KEY_IN_WORDS];
    uint32_t counterV[MCUXCLAES_BLOCK_SIZE_IN_WORDS];
} mcuxClRandomModes_Context_CtrDrbg_Aes256_t;


/* Internal function prototypes */
MCUX_CSSL_FP_FUNCTION_DECL(mcuxClRandomModes_CtrDrbg_instantiateAlgorithm, mcuxClRandomModes_instantiateAlgorithm_t)
MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClRandom_Status_t) mcuxClRandomModes_CtrDrbg_instantiateAlgorithm(
    mcuxClSession_Handle_t pSession,
    uint8_t *pEntropyInput);
MCUX_CSSL_FP_FUNCTION_DECL(mcuxClRandomModes_CtrDrbg_reseedAlgorithm, mcuxClRandomModes_reseedAlgorithm_t)
MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClRandom_Status_t) mcuxClRandomModes_CtrDrbg_reseedAlgorithm(
    mcuxClSession_Handle_t pSession,
    uint8_t *pEntropyInput);
MCUX_CSSL_FP_FUNCTION_DECL(mcuxClRandomModes_CtrDrbg_generateAlgorithm, mcuxClRandomModes_generateAlgorithm_t)
MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClRandom_Status_t) mcuxClRandomModes_CtrDrbg_generateAlgorithm(
    mcuxClSession_Handle_t pSession,
    uint8_t *pOut,
    uint32_t outLength);

/* Refer to the NIST SP 800-90A 10.3.2 Derivation function using a block cipher algorithm */
MCUX_CSSL_FP_FUNCTION_DECL(mcuxClRandomModes_CtrDrbg_df)
MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClRandom_Status_t) mcuxClRandomModes_CtrDrbg_df(
    mcuxClSession_Handle_t pSession,
    uint8_t *pInputString,
    uint32_t inputStringLen,
    uint32_t outputLen);

/* Refer to the NIST SP 800-90A 10.3.3 BCC and Block_Encrypt */
MCUX_CSSL_FP_FUNCTION_DECL(mcuxClRandomModes_CtrDrbg_bcc)
MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClRandom_Status_t) mcuxClRandomModes_CtrDrbg_bcc(
    mcuxClSession_Handle_t pSession,
    uint32_t const *pKey,
    uint32_t * const pData,
    uint32_t dataLen,
    uint32_t *pOut);

MCUX_CSSL_FP_FUNCTION_DECL(mcuxClRandomModes_CtrDrbg_UpdateState)
MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClRandom_Status_t) mcuxClRandomModes_CtrDrbg_UpdateState(
    mcuxClSession_Handle_t pSession,
    uint32_t *pProvidedData
);

MCUX_CSSL_FP_FUNCTION_DEF(mcuxClRandomModes_CtrDrbg_generateOutput)
MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClRandom_Status_t) mcuxClRandomModes_CtrDrbg_generateOutput(
    mcuxClSession_Handle_t pSession,
    uint8_t *pOut,
    uint32_t outLength);

extern const mcuxClRandomModes_DrbgAlgorithmsDescriptor_t mcuxClRandomModes_DrbgAlgorithmsDescriptor_CtrDrbg;
extern const mcuxClRandomModes_DrbgVariantDescriptor_t mcuxClRandomModes_DrbgVariantDescriptor_CtrDrbg_AES128;
extern const mcuxClRandomModes_DrbgVariantDescriptor_t mcuxClRandomModes_DrbgVariantDescriptor_CtrDrbg_AES192;
extern const mcuxClRandomModes_DrbgVariantDescriptor_t mcuxClRandomModes_DrbgVariantDescriptor_CtrDrbg_AES256;

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* MCUXCLRANDOMMODES_PRIVATE_CTRDRBG_H_ */