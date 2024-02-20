/*
 *  Functions to delegate cryptographic operations to an available
 *  and appropriate accelerator.
 *  Warning: This file is now auto-generated.
 */
/*  Copyright The Mbed TLS Contributors
 *  SPDX-License-Identifier: Apache-2.0
 *
 *  Licensed under the Apache License, Version 2.0 (the "License"); you may
 *  not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *  http://www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS, WITHOUT
 *  WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 */


/* BEGIN-common headers */
#include "common.h"
#include "psa_crypto_aead.h"
#include "psa_crypto_cipher.h"
#include "psa_crypto_core.h"
#include "psa_crypto_driver_wrappers.h"
#include "psa_crypto_hash.h"
#include "psa_crypto_mac.h"
#include "psa_crypto_pake.h"
#include "psa_crypto_rsa.h"

#include "mbedtls/platform.h"
/* END-common headers */

#if defined(MBEDTLS_PSA_CRYPTO_C)

/* BEGIN-driver headers */
#if defined(MBEDTLS_PSA_CRYPTO_DRIVERS)
/* Headers for mbedtls_test opaque driver */
#if defined(PSA_CRYPTO_DRIVER_TEST)
#include "test/drivers/test_driver.h"

#endif
/* Headers for mbedtls_test transparent driver */
#if defined(PSA_CRYPTO_DRIVER_TEST)
#include "test/drivers/test_driver.h"

#endif

#if defined(PSA_CRYPTO_DRIVER_CC3XX)                  //NXP TFM --- BEGIN ---
#ifndef PSA_CRYPTO_DRIVER_PRESENT
#define PSA_CRYPTO_DRIVER_PRESENT
#endif
#ifndef PSA_CRYPTO_ACCELERATOR_DRIVER_PRESENT
#define PSA_CRYPTO_ACCELERATOR_DRIVER_PRESENT
#endif
#include "cc3xx.h"
#endif /* PSA_CRYPTO_DRIVER_CC3XX */

/* Include TF-M builtin key driver */
#if defined(PSA_CRYPTO_DRIVER_TFM_BUILTIN_KEY_LOADER)
#ifndef PSA_CRYPTO_DRIVER_PRESENT
#define PSA_CRYPTO_DRIVER_PRESENT
#endif
#ifndef PSA_CRYPTO_ACCELERATOR_DRIVER_PRESENT
#define PSA_CRYPTO_ACCELERATOR_DRIVER_PRESENT
#endif
#include "tfm_crypto_defs.h"
#include "tfm_builtin_key_loader.h"
#endif /* PSA_CRYPTO_DRIVER_TFM_BUILTIN_KEY_LOADER */   //NXP TFM  --- END ---

#endif /* MBEDTLS_PSA_CRYPTO_DRIVERS */
/* END-driver headers */

/* Auto-generated values depending on which drivers are registered.
 * ID 0 is reserved for unallocated operations.
 * ID 1 is reserved for the Mbed TLS software driver. */
/* BEGIN-driver id definition */
#define PSA_CRYPTO_MBED_TLS_DRIVER_ID (1)
#define MBEDTLS_TEST_OPAQUE_DRIVER_ID (2)
#define MBEDTLS_TEST_TRANSPARENT_DRIVER_ID (3)
#if defined(PSA_CRYPTO_DRIVER_CC3XX)                      //NXP TFM --- BEGIN ---
#define PSA_CRYPTO_CC3XX_DRIVER_ID (4)
#endif /* PSA_CRYPTO_DRIVER_CC3XX */
#if defined(PSA_CRYPTO_DRIVER_TFM_BUILTIN_KEY_LOADER)
#define PSA_CRYPTO_TFM_BUILTIN_KEY_LOADER_DRIVER_ID (5)
#endif /* PSA_CRYPTO_DRIVER_TFM_BUILTIN_KEY_LOADER */     //NXP TFM  --- END ---

/* END-driver id */

/* BEGIN-Common Macro definitions */

/* END-Common Macro definitions */

/* Support the 'old' SE interface when asked to */
#if defined(MBEDTLS_PSA_CRYPTO_SE_C)
/* PSA_CRYPTO_DRIVER_PRESENT is defined when either a new-style or old-style
 * SE driver is present, to avoid unused argument errors at compile time. */
#ifndef PSA_CRYPTO_DRIVER_PRESENT
#define PSA_CRYPTO_DRIVER_PRESENT
#endif
#include "psa_crypto_se.h"
#endif

psa_status_t psa_driver_wrapper_init( void )
{
    psa_status_t status = PSA_ERROR_CORRUPTION_DETECTED;

#if defined(PSA_CRYPTO_DRIVER_TFM_BUILTIN_KEY_LOADER)      //NXP TFM --- BEGIN ---
    status = tfm_builtin_key_loader_init();
    if (status != PSA_SUCCESS)
        return ( status );
#endif /* PSA_CRYPTO_DRIVER_TFM_BUILTIN_KEY_LOADER */      //NXP TFM  --- END ---

#if defined(PSA_CRYPTO_DRIVER_CC3XX)                       //NXP TFM --- BEGIN ---
    status = cc3xx_init();                                 
    if (status != PSA_SUCCESS)                             
        return ( status );                                 //NXP TFM  --- END ---
#endif

#if defined(MBEDTLS_PSA_CRYPTO_SE_C)
    status = psa_init_all_se_drivers( );
    if( status != PSA_SUCCESS )
        return( status );
#endif

#if defined(PSA_CRYPTO_DRIVER_TEST)
    status = mbedtls_test_transparent_init( );
    if( status != PSA_SUCCESS )
        return( status );

    status = mbedtls_test_opaque_init( );
    if( status != PSA_SUCCESS )
        return( status );
#endif

    (void) status;
    return( PSA_SUCCESS );
}

void psa_driver_wrapper_free( void )
{
#if defined(PSA_CRYPTO_DRIVER_CC3XX)                 //NXP TFM --- BEGIN ---
    (void)cc3xx_free();
#endif                                               //NXP TFM --- END ---

#if defined(MBEDTLS_PSA_CRYPTO_SE_C)
    /* Unregister all secure element drivers, so that we restart from
     * a pristine state. */
    psa_unregister_all_se_drivers( );
#endif /* MBEDTLS_PSA_CRYPTO_SE_C */

#if defined(PSA_CRYPTO_DRIVER_TEST)
    mbedtls_test_transparent_free( );
    mbedtls_test_opaque_free( );
#endif
}

/* Start delegation functions */
psa_status_t psa_driver_wrapper_sign_message(
    const psa_key_attributes_t *attributes,
    const uint8_t *key_buffer,
    size_t key_buffer_size,
    psa_algorithm_t alg,
    const uint8_t *input,
    size_t input_length,
    uint8_t *signature,
    size_t signature_size,
    size_t *signature_length )
{
    psa_status_t status = PSA_ERROR_CORRUPTION_DETECTED;
    psa_key_location_t location =
        PSA_KEY_LIFETIME_GET_LOCATION( attributes->core.lifetime );

    switch( location )
    {
        case PSA_KEY_LOCATION_LOCAL_STORAGE:
#if defined(PSA_CRYPTO_DRIVER_TFM_BUILTIN_KEY_LOADER)             //NXP TFM --- BEGIN ---
        case TFM_BUILTIN_KEY_LOADER_KEY_LOCATION:                 
#endif /* defined(PSA_CRYPTO_DRIVER_TFM_BUILTIN_KEY_LOADER) */    //NXP TFM --- END ---
            /* Key is stored in the slot in export representation, so
             * cycle through all known transparent accelerators */
#if defined(PSA_CRYPTO_ACCELERATOR_DRIVER_PRESENT)
#if defined(PSA_CRYPTO_DRIVER_TEST)
            status = mbedtls_test_transparent_signature_sign_message(
                        attributes,
                        key_buffer,
                        key_buffer_size,
                        alg,
                        input,
                        input_length,
                        signature,
                        signature_size,
                        signature_length );
            /* Declared with fallback == true */
            if( status != PSA_ERROR_NOT_SUPPORTED )
                return( status );
#endif /* PSA_CRYPTO_DRIVER_TEST */
#if defined(PSA_CRYPTO_DRIVER_CC3XX)                                      //NXP TFM --- BEGIN ---
            status = cc3xx_sign_message(
                        attributes,
                        key_buffer,
                        key_buffer_size,
                        alg,
                        input,
                        input_length,
                        signature,
                        signature_size,
                        signature_length );
            return( status );
#endif /* PSA_CRYPTO_DRIVER_CC3XX */
#endif /* PSA_CRYPTO_ACCELERATOR_DRIVER_PRESENT */
#if !defined(PSA_CRYPTO_DRIVER_CC3XX)
            /* Fell through, meaning no accelerator supports this operation */
            return( psa_sign_message_builtin( attributes,
                                      key_buffer,
                                      key_buffer_size,
                                      alg,
                                      input,
                                      input_length,
                                      signature,
                                      signature_size,
                                      signature_length ) );
#endif /* PSA_CRYPTO_DRIVER_CC3XX */                                      //NXP TFM --- END ---
        /* Add cases for opaque driver here */
#if defined(PSA_CRYPTO_ACCELERATOR_DRIVER_PRESENT)
#if defined(PSA_CRYPTO_DRIVER_TEST)
        case PSA_CRYPTO_TEST_DRIVER_LOCATION:
            status = mbedtls_test_opaque_signature_sign_message(
                        attributes,
                        key_buffer,
                        key_buffer_size,
                        alg,
                        input,
                        input_length,
                        signature,
                        signature_size,
                        signature_length );
            if( status != PSA_ERROR_NOT_SUPPORTED )
                return( status );
            break;
#endif /* PSA_CRYPTO_DRIVER_TEST */
#endif /* PSA_CRYPTO_ACCELERATOR_DRIVER_PRESENT */
        default:
            /* Key is declared with a lifetime not known to us */
            (void)status;
            return( PSA_ERROR_INVALID_ARGUMENT );     // NXP TFM 
    }

    return status;      //NXP TFM
}

psa_status_t psa_driver_wrapper_verify_message(
    const psa_key_attributes_t *attributes,
    const uint8_t *key_buffer,
    size_t key_buffer_size,
    psa_algorithm_t alg,
    const uint8_t *input,
    size_t input_length,
    const uint8_t *signature,
    size_t signature_length )
{
    psa_status_t status = PSA_ERROR_CORRUPTION_DETECTED;
    psa_key_location_t location =
        PSA_KEY_LIFETIME_GET_LOCATION( attributes->core.lifetime );

    switch( location )
    {
        case PSA_KEY_LOCATION_LOCAL_STORAGE:
#if defined(PSA_CRYPTO_DRIVER_TFM_BUILTIN_KEY_LOADER)             //NXP TFM --- BEGIN ---
        case TFM_BUILTIN_KEY_LOADER_KEY_LOCATION:                 
#endif /* defined(PSA_CRYPTO_DRIVER_TFM_BUILTIN_KEY_LOADER) */    //NXP TFM --- END ---
            /* Key is stored in the slot in export representation, so
             * cycle through all known transparent accelerators */
#if defined(PSA_CRYPTO_ACCELERATOR_DRIVER_PRESENT)
#if defined(PSA_CRYPTO_DRIVER_TEST)
            status = mbedtls_test_transparent_signature_verify_message(
                        attributes,
                        key_buffer,
                        key_buffer_size,
                        alg,
                        input,
                        input_length,
                        signature,
                        signature_length );
            /* Declared with fallback == true */
            if( status != PSA_ERROR_NOT_SUPPORTED )
                return( status );
#endif /* PSA_CRYPTO_DRIVER_TEST */
#if defined(PSA_CRYPTO_DRIVER_CC3XX)                           //NXP TFM --- BEGIN ---
            status = cc3xx_verify_message(
                        attributes,
                        key_buffer,
                        key_buffer_size,
                        alg,
                        input,
                        input_length,
                        signature,
                        signature_length );
            return( status );
#endif /* PSA_CRYPTO_DRIVER_CC3XX */
#endif /* PSA_CRYPTO_ACCELERATOR_DRIVER_PRESENT */
#if !defined(PSA_CRYPTO_DRIVER_CC3XX)
            /* Fell through, meaning no accelerator supports this operation */
            return( psa_verify_message_builtin( attributes,
                                        key_buffer,
                                        key_buffer_size,
                                        alg,
                                        input,
                                        input_length,
                                        signature,
                                        signature_length ) );
#endif /* PSA_CRYPTO_DRIVER_CC3XX */                          //NXP TFM --- END ---
        /* Add cases for opaque driver here */
#if defined(PSA_CRYPTO_ACCELERATOR_DRIVER_PRESENT)
#if defined(PSA_CRYPTO_DRIVER_TEST)
        case PSA_CRYPTO_TEST_DRIVER_LOCATION:
            return( mbedtls_test_opaque_signature_verify_message(
                        attributes,
                        key_buffer,
                        key_buffer_size,
                        alg,
                        input,
                        input_length,
                        signature,
                        signature_length ) );
            if( status != PSA_ERROR_NOT_SUPPORTED )
                return( status );
            break;
#endif /* PSA_CRYPTO_DRIVER_TEST */
#endif /* PSA_CRYPTO_ACCELERATOR_DRIVER_PRESENT */
        default:
            /* Key is declared with a lifetime not known to us */
            (void)status;
            return( PSA_ERROR_INVALID_ARGUMENT );         //NXP TFM
    }
    return status;                                        //NXP TFM
}

psa_status_t psa_driver_wrapper_sign_hash(
    const psa_key_attributes_t *attributes,
    const uint8_t *key_buffer, size_t key_buffer_size,
    psa_algorithm_t alg, const uint8_t *hash, size_t hash_length,
    uint8_t *signature, size_t signature_size, size_t *signature_length )
{
    /* Try dynamically-registered SE interface first */
#if defined(MBEDTLS_PSA_CRYPTO_SE_C)
    const psa_drv_se_t *drv;
    psa_drv_se_context_t *drv_context;

    if( psa_get_se_driver( attributes->core.lifetime, &drv, &drv_context ) )
    {
        if( drv->asymmetric == NULL ||
            drv->asymmetric->p_sign == NULL )
        {
            /* Key is defined in SE, but we have no way to exercise it */
            return( PSA_ERROR_NOT_SUPPORTED );
        }
        return( drv->asymmetric->p_sign(
                    drv_context, *( (psa_key_slot_number_t *)key_buffer ),
                    alg, hash, hash_length,
                    signature, signature_size, signature_length ) );
    }
#endif /* MBEDTLS_PSA_CRYPTO_SE_C */

    psa_status_t status = PSA_ERROR_CORRUPTION_DETECTED;
    psa_key_location_t location =
        PSA_KEY_LIFETIME_GET_LOCATION( attributes->core.lifetime );

    switch( location )
    {
        case PSA_KEY_LOCATION_LOCAL_STORAGE:
#if defined(PSA_CRYPTO_DRIVER_TFM_BUILTIN_KEY_LOADER)             //NXP TFM --- BEGIN ---
        case TFM_BUILTIN_KEY_LOADER_KEY_LOCATION:                 
#endif /* defined(PSA_CRYPTO_DRIVER_TFM_BUILTIN_KEY_LOADER) */    //NXP TFM --- END ---
            /* Key is stored in the slot in export representation, so
             * cycle through all known transparent accelerators */
#if defined(PSA_CRYPTO_ACCELERATOR_DRIVER_PRESENT)
#if defined(PSA_CRYPTO_DRIVER_TEST)
            status = mbedtls_test_transparent_signature_sign_hash( attributes,
                                                           key_buffer,
                                                           key_buffer_size,
                                                           alg,
                                                           hash,
                                                           hash_length,
                                                           signature,
                                                           signature_size,
                                                           signature_length );
            /* Declared with fallback == true */
            if( status != PSA_ERROR_NOT_SUPPORTED )
                return( status );
#endif /* PSA_CRYPTO_DRIVER_TEST */
#if defined(PSA_CRYPTO_DRIVER_CC3XX)                            //NXP TFM --- BEGIN ---
            status = cc3xx_sign_hash( attributes,
                                      key_buffer,
                                      key_buffer_size,
                                      alg,
                                      hash,
                                      hash_length,
                                      signature,
                                      signature_size,
                                      signature_length );
            return( status );
#endif /* PSA_CRYPTO_DRIVER_CC3XX */
#endif /* PSA_CRYPTO_ACCELERATOR_DRIVER_PRESENT */
#if !defined(PSA_CRYPTO_DRIVER_CC3XX)
            /* Fell through, meaning no accelerator supports this operation */
            return( psa_sign_hash_builtin( attributes,
                                           key_buffer,
                                           key_buffer_size,
                                           alg,
                                           hash,
                                           hash_length,
                                           signature,
                                           signature_size,
                                           signature_length ) );
#endif /* PSA_CRYPTO_DRIVER_CC3XX */                            //NXP TFM --- END ---
        /* Add cases for opaque driver here */
#if defined(PSA_CRYPTO_ACCELERATOR_DRIVER_PRESENT)
#if defined(PSA_CRYPTO_DRIVER_TEST)
        case PSA_CRYPTO_TEST_DRIVER_LOCATION:
            return( mbedtls_test_opaque_signature_sign_hash( attributes,
                                                             key_buffer,
                                                             key_buffer_size,
                                                             alg,
                                                             hash,
                                                             hash_length,
                                                             signature,
                                                             signature_size,
                                                             signature_length ) );
#endif /* PSA_CRYPTO_DRIVER_TEST */
#endif /* PSA_CRYPTO_ACCELERATOR_DRIVER_PRESENT */
        default:
            /* Key is declared with a lifetime not known to us */
            (void)status;
            return( PSA_ERROR_INVALID_ARGUMENT );
    }
}

psa_status_t psa_driver_wrapper_verify_hash(
    const psa_key_attributes_t *attributes,
    const uint8_t *key_buffer, size_t key_buffer_size,
    psa_algorithm_t alg, const uint8_t *hash, size_t hash_length,
    const uint8_t *signature, size_t signature_length )
{
    /* Try dynamically-registered SE interface first */
#if defined(MBEDTLS_PSA_CRYPTO_SE_C)
    const psa_drv_se_t *drv;
    psa_drv_se_context_t *drv_context;

    if( psa_get_se_driver( attributes->core.lifetime, &drv, &drv_context ) )
    {
        if( drv->asymmetric == NULL ||
            drv->asymmetric->p_verify == NULL )
        {
            /* Key is defined in SE, but we have no way to exercise it */
            return( PSA_ERROR_NOT_SUPPORTED );
        }
        return( drv->asymmetric->p_verify(
                    drv_context, *( (psa_key_slot_number_t *)key_buffer ),
                    alg, hash, hash_length,
                    signature, signature_length ) );
    }
#endif /* MBEDTLS_PSA_CRYPTO_SE_C */

    psa_status_t status = PSA_ERROR_CORRUPTION_DETECTED;
    psa_key_location_t location =
        PSA_KEY_LIFETIME_GET_LOCATION( attributes->core.lifetime );

    switch( location )
    {
        case PSA_KEY_LOCATION_LOCAL_STORAGE:
#if defined(PSA_CRYPTO_DRIVER_TFM_BUILTIN_KEY_LOADER)              //NXP TFM --- BEGIN ---
        case TFM_BUILTIN_KEY_LOADER_KEY_LOCATION:
#endif /* defined(PSA_CRYPTO_DRIVER_TFM_BUILTIN_KEY_LOADER) */
            /* Key is stored in the slot in export representation, so
             * cycle through all known transparent accelerators */
#if defined(PSA_CRYPTO_ACCELERATOR_DRIVER_PRESENT)
#if defined(PSA_CRYPTO_DRIVER_CC3XX)
            status = cc3xx_verify_hash( attributes,
                                        key_buffer,
                                        key_buffer_size,
                                        alg,
                                        hash,
                                        hash_length,
                                        signature,
                                        signature_length );
            return( status );
#endif /* PSA_CRYPTO_DRIVER_CC3XX */                               //NXP TFM --- END ---
#if defined(PSA_CRYPTO_DRIVER_TEST)
            status = mbedtls_test_transparent_signature_verify_hash(
                         attributes,
                         key_buffer,
                         key_buffer_size,
                         alg,
                         hash,
                         hash_length,
                         signature,
                         signature_length );
            /* Declared with fallback == true */
            if( status != PSA_ERROR_NOT_SUPPORTED )
                return( status );
#endif /* PSA_CRYPTO_DRIVER_TEST */
#endif /* PSA_CRYPTO_ACCELERATOR_DRIVER_PRESENT */
#if !defined(PSA_CRYPTO_DRIVER_CC3XX)                           //NXP TFM --- BEGIN ---
            return( psa_verify_hash_builtin( attributes,
                                             key_buffer,
                                             key_buffer_size,
                                             alg,
                                             hash,
                                             hash_length,
                                             signature,
                                             signature_length ) );
#endif /* PSA_CRYPTO_DRIVER_CC3XX */                            //NXP TFM --- END ---
        /* Add cases for opaque driver here */
#if defined(PSA_CRYPTO_ACCELERATOR_DRIVER_PRESENT)
#if defined(PSA_CRYPTO_DRIVER_TEST)
        case PSA_CRYPTO_TEST_DRIVER_LOCATION:
            return( mbedtls_test_opaque_signature_verify_hash( attributes,
                                                               key_buffer,
                                                               key_buffer_size,
                                                               alg,
                                                               hash,
                                                               hash_length,
                                                               signature,
                                                               signature_length ) );
#endif /* PSA_CRYPTO_DRIVER_TEST */
#endif /* PSA_CRYPTO_ACCELERATOR_DRIVER_PRESENT */
        default:
            /* Key is declared with a lifetime not known to us */
            (void)status;
            return( PSA_ERROR_INVALID_ARGUMENT );
    }
}

uint32_t psa_driver_wrapper_sign_hash_get_num_ops(
    psa_sign_hash_interruptible_operation_t *operation )
{
    switch( operation->id )
    {
        /* If uninitialised, return 0, as no work can have been done. */
        case 0:
            return 0;

        case PSA_CRYPTO_MBED_TLS_DRIVER_ID:
            return(mbedtls_psa_sign_hash_get_num_ops(&operation->ctx.mbedtls_ctx));

#if defined(PSA_CRYPTO_ACCELERATOR_DRIVER_PRESENT)
#if defined(PSA_CRYPTO_DRIVER_TEST)
            /* Add test driver tests here */

#endif /* PSA_CRYPTO_DRIVER_TEST */
#endif /* PSA_CRYPTO_ACCELERATOR_DRIVER_PRESENT */
    }

    return( PSA_ERROR_INVALID_ARGUMENT );
}

uint32_t psa_driver_wrapper_verify_hash_get_num_ops(
    psa_verify_hash_interruptible_operation_t *operation )
{
    switch( operation->id )
    {
        /* If uninitialised, return 0, as no work can have been done. */
        case 0:
            return 0;

        case PSA_CRYPTO_MBED_TLS_DRIVER_ID:
            return (mbedtls_psa_verify_hash_get_num_ops(&operation->ctx.mbedtls_ctx));

#if defined(PSA_CRYPTO_ACCELERATOR_DRIVER_PRESENT)
#if defined(PSA_CRYPTO_DRIVER_TEST)
            /* Add test driver tests here */

#endif /* PSA_CRYPTO_DRIVER_TEST */
#endif /* PSA_CRYPTO_ACCELERATOR_DRIVER_PRESENT */

    }

    return( PSA_ERROR_INVALID_ARGUMENT );
}

psa_status_t psa_driver_wrapper_sign_hash_start(
    psa_sign_hash_interruptible_operation_t *operation,
    const psa_key_attributes_t *attributes, const uint8_t *key_buffer,
    size_t key_buffer_size, psa_algorithm_t alg,
    const uint8_t *hash, size_t hash_length )
{
    psa_status_t status = PSA_ERROR_CORRUPTION_DETECTED;
    psa_key_location_t location =
                                  PSA_KEY_LIFETIME_GET_LOCATION(
                                                    attributes->core.lifetime );

    switch( location )
    {
        case PSA_KEY_LOCATION_LOCAL_STORAGE:
            /* Key is stored in the slot in export representation, so
             * cycle through all known transparent accelerators */

#if defined(PSA_CRYPTO_ACCELERATOR_DRIVER_PRESENT)
#if defined(PSA_CRYPTO_DRIVER_TEST)

            /* Add test driver tests here */

            /* Declared with fallback == true */

#endif /* PSA_CRYPTO_DRIVER_TEST */
#endif /* PSA_CRYPTO_ACCELERATOR_DRIVER_PRESENT */

            /* Fell through, meaning no accelerator supports this operation */
            operation->id = PSA_CRYPTO_MBED_TLS_DRIVER_ID;
            return( mbedtls_psa_sign_hash_start( &operation->ctx.mbedtls_ctx,
                                                 attributes,
                                                 key_buffer, key_buffer_size,
                                                 alg, hash, hash_length ) );
            break;

            /* Add cases for opaque driver here */

        default:
            /* Key is declared with a lifetime not known to us */
            ( void ) status;
            return( PSA_ERROR_INVALID_ARGUMENT );
    }

    ( void ) operation;
    ( void ) key_buffer;
    ( void ) key_buffer_size;
    ( void ) alg;
    ( void ) hash;
    ( void ) hash_length;

        return( status );
}

psa_status_t psa_driver_wrapper_sign_hash_complete(
    psa_sign_hash_interruptible_operation_t *operation,
    uint8_t *signature, size_t signature_size,
    size_t *signature_length )
{
    switch( operation->id )
    {
        case PSA_CRYPTO_MBED_TLS_DRIVER_ID:
            return( mbedtls_psa_sign_hash_complete( &operation->ctx.mbedtls_ctx,
                                                    signature, signature_size,
                                                    signature_length ) );

#if defined(PSA_CRYPTO_ACCELERATOR_DRIVER_PRESENT)
#if defined(PSA_CRYPTO_DRIVER_TEST)
            /* Add test driver tests here */

#endif /* PSA_CRYPTO_DRIVER_TEST */
#endif /* PSA_CRYPTO_ACCELERATOR_DRIVER_PRESENT */
    }

    ( void ) signature;
    ( void ) signature_size;
    ( void ) signature_length;

    return( PSA_ERROR_INVALID_ARGUMENT );
}

psa_status_t psa_driver_wrapper_sign_hash_abort(
    psa_sign_hash_interruptible_operation_t *operation )
{
    switch( operation->id )
    {
        case PSA_CRYPTO_MBED_TLS_DRIVER_ID:
            return( mbedtls_psa_sign_hash_abort( &operation->ctx.mbedtls_ctx ) );

#if defined(PSA_CRYPTO_ACCELERATOR_DRIVER_PRESENT)
#if defined(PSA_CRYPTO_DRIVER_TEST)
            /* Add test driver tests here */

#endif /* PSA_CRYPTO_DRIVER_TEST */
#endif /* PSA_CRYPTO_ACCELERATOR_DRIVER_PRESENT */
    }

    return( PSA_ERROR_INVALID_ARGUMENT );
}

psa_status_t psa_driver_wrapper_verify_hash_start(
    psa_verify_hash_interruptible_operation_t *operation,
    const psa_key_attributes_t *attributes, const uint8_t *key_buffer,
    size_t key_buffer_size, psa_algorithm_t alg,
    const uint8_t *hash, size_t hash_length,
    const uint8_t *signature, size_t signature_length )
{

    psa_status_t status = PSA_ERROR_CORRUPTION_DETECTED;
    psa_key_location_t location = PSA_KEY_LIFETIME_GET_LOCATION(
                                                    attributes->core.lifetime );

    switch( location )
    {
        case PSA_KEY_LOCATION_LOCAL_STORAGE:
            /* Key is stored in the slot in export representation, so
             * cycle through all known transparent accelerators */

#if defined(PSA_CRYPTO_ACCELERATOR_DRIVER_PRESENT)
#if defined(PSA_CRYPTO_DRIVER_TEST)

            /* Add test driver tests here */

            /* Declared with fallback == true */

#endif /* PSA_CRYPTO_DRIVER_TEST */
#endif /* PSA_CRYPTO_ACCELERATOR_DRIVER_PRESENT */

            /* Fell through, meaning no accelerator supports this operation */
            operation->id = PSA_CRYPTO_MBED_TLS_DRIVER_ID;
            return( mbedtls_psa_verify_hash_start( &operation->ctx.mbedtls_ctx,
                                                   attributes,
                                                   key_buffer, key_buffer_size,
                                                   alg, hash, hash_length,
                                                   signature, signature_length
                                                   ) );
            break;

            /* Add cases for opaque driver here */

        default:
            /* Key is declared with a lifetime not known to us */
            ( void ) status;
            return( PSA_ERROR_INVALID_ARGUMENT );
    }

    ( void ) operation;
    ( void ) key_buffer;
    ( void ) key_buffer_size;
    ( void ) alg;
    ( void ) hash;
    ( void ) hash_length;
    ( void ) signature;
    ( void ) signature_length;

    return( status );
}

psa_status_t psa_driver_wrapper_verify_hash_complete(
    psa_verify_hash_interruptible_operation_t *operation )
{
    switch( operation->id )
    {
        case PSA_CRYPTO_MBED_TLS_DRIVER_ID:
            return( mbedtls_psa_verify_hash_complete(
                                                     &operation->ctx.mbedtls_ctx
                                                     ) );

#if defined(PSA_CRYPTO_ACCELERATOR_DRIVER_PRESENT)
#if defined(PSA_CRYPTO_DRIVER_TEST)
            /* Add test driver tests here */

#endif /* PSA_CRYPTO_DRIVER_TEST */
#endif /* PSA_CRYPTO_ACCELERATOR_DRIVER_PRESENT */
    }

    return( PSA_ERROR_INVALID_ARGUMENT );
}

psa_status_t psa_driver_wrapper_verify_hash_abort(
    psa_verify_hash_interruptible_operation_t *operation )
{
    switch( operation->id )
    {
        case PSA_CRYPTO_MBED_TLS_DRIVER_ID:
            return( mbedtls_psa_verify_hash_abort( &operation->ctx.mbedtls_ctx
                                                 ) );

#if defined(PSA_CRYPTO_ACCELERATOR_DRIVER_PRESENT)
#if defined(PSA_CRYPTO_DRIVER_TEST)
            /* Add test driver tests here */

#endif /* PSA_CRYPTO_DRIVER_TEST */
#endif /* PSA_CRYPTO_ACCELERATOR_DRIVER_PRESENT */
    }

    return( PSA_ERROR_INVALID_ARGUMENT );
}

/** Calculate the key buffer size required to store the key material of a key
 *  associated with an opaque driver from input key data.
 *
 * \param[in] attributes        The key attributes
 * \param[in] data              The input key data.
 * \param[in] data_length       The input data length.
 * \param[out] key_buffer_size  Minimum buffer size to contain the key material.
 *
 * \retval #PSA_SUCCESS \emptydescription
 * \retval #PSA_ERROR_INVALID_ARGUMENT \emptydescription
 * \retval #PSA_ERROR_NOT_SUPPORTED \emptydescription
 */
psa_status_t psa_driver_wrapper_get_key_buffer_size_from_key_data(
    const psa_key_attributes_t *attributes,
    const uint8_t *data,
    size_t data_length,
    size_t *key_buffer_size )
{
    psa_key_location_t location =
        PSA_KEY_LIFETIME_GET_LOCATION( attributes->core.lifetime );
    psa_key_type_t key_type = attributes->core.type;

    *key_buffer_size = 0;
    switch( location )
    {
#if defined(PSA_CRYPTO_DRIVER_TEST)
        case PSA_CRYPTO_TEST_DRIVER_LOCATION:
            *key_buffer_size = mbedtls_test_opaque_size_function( key_type,
                                     PSA_BYTES_TO_BITS( data_length ) );
            return( ( *key_buffer_size != 0 ) ?
                    PSA_SUCCESS : PSA_ERROR_NOT_SUPPORTED );
#endif /* PSA_CRYPTO_DRIVER_TEST */

        default:
            (void)key_type;
            (void)data;
            (void)data_length;
            return( PSA_ERROR_INVALID_ARGUMENT );
    }
}

/** Get the key buffer size required to store the key material of a key
 *  associated with an opaque driver.
 *
 * \param[in] attributes  The key attributes.
 * \param[out] key_buffer_size  Minimum buffer size to contain the key material
 *
 * \retval #PSA_SUCCESS
 *         The minimum size for a buffer to contain the key material has been
 *         returned successfully.
 * \retval #PSA_ERROR_NOT_SUPPORTED
 *         The type and/or the size in bits of the key or the combination of
 *         the two is not supported.
 * \retval #PSA_ERROR_INVALID_ARGUMENT
 *         The key is declared with a lifetime not known to us.
 */
psa_status_t psa_driver_wrapper_get_key_buffer_size(
    const psa_key_attributes_t *attributes,
    size_t *key_buffer_size )
{
    psa_key_location_t location = PSA_KEY_LIFETIME_GET_LOCATION( attributes->core.lifetime );
    psa_key_type_t key_type = attributes->core.type;
    size_t key_bits = attributes->core.bits;

    *key_buffer_size = 0;
    switch( location )
    {
#if defined(PSA_CRYPTO_DRIVER_TEST)
        case PSA_CRYPTO_TEST_DRIVER_LOCATION:
#if defined(MBEDTLS_PSA_CRYPTO_BUILTIN_KEYS)
            /* Emulate property 'builtin_key_size' */
            if( psa_key_id_is_builtin(
                    MBEDTLS_SVC_KEY_ID_GET_KEY_ID(
                        psa_get_key_id( attributes ) ) ) )
            {
                *key_buffer_size = sizeof( psa_drv_slot_number_t );
                return( PSA_SUCCESS );
            }
#endif /* MBEDTLS_PSA_CRYPTO_BUILTIN_KEYS */
            *key_buffer_size = mbedtls_test_opaque_size_function( key_type,
                                                                  key_bits );
            return( ( *key_buffer_size != 0 ) ?
                    PSA_SUCCESS : PSA_ERROR_NOT_SUPPORTED );
#endif /* PSA_CRYPTO_DRIVER_TEST */
#if defined(PSA_CRYPTO_DRIVER_TFM_BUILTIN_KEY_LOADER)                                      //NXP TFM --- BEGIN ---
        case TFM_BUILTIN_KEY_LOADER_KEY_LOCATION:                                          
            return tfm_builtin_key_loader_get_key_buffer_size(psa_get_key_id(attributes),  
                                                              key_buffer_size);            
#endif /* PSA_CRYPTO_DRIVER_TFM_BUILTIN_KEY_LOADER */                                      //NXP TFM --- END ---
        default:
            (void)key_type;
            (void)key_bits;
            return( PSA_ERROR_INVALID_ARGUMENT );
    }
}

psa_status_t psa_driver_wrapper_generate_key(
    const psa_key_attributes_t *attributes,
    uint8_t *key_buffer, size_t key_buffer_size, size_t *key_buffer_length )
{
    psa_status_t status = PSA_ERROR_CORRUPTION_DETECTED;
    psa_key_location_t location =
        PSA_KEY_LIFETIME_GET_LOCATION(attributes->core.lifetime);

    /* Try dynamically-registered SE interface first */
#if defined(MBEDTLS_PSA_CRYPTO_SE_C)
    const psa_drv_se_t *drv;
    psa_drv_se_context_t *drv_context;

    if( psa_get_se_driver( attributes->core.lifetime, &drv, &drv_context ) )
    {
        size_t pubkey_length = 0; /* We don't support this feature yet */
        if( drv->key_management == NULL ||
            drv->key_management->p_generate == NULL )
        {
            /* Key is defined as being in SE, but we have no way to generate it */
            return( PSA_ERROR_NOT_SUPPORTED );
        }
        return( drv->key_management->p_generate(
            drv_context,
            *( (psa_key_slot_number_t *)key_buffer ),
            attributes, NULL, 0, &pubkey_length ) );
    }
#endif /* MBEDTLS_PSA_CRYPTO_SE_C */

    switch( location )
    {
        case PSA_KEY_LOCATION_LOCAL_STORAGE:
#if defined(PSA_CRYPTO_DRIVER_TFM_BUILTIN_KEY_LOADER)                //NXP TFM --- BEGIN ---
        case TFM_BUILTIN_KEY_LOADER_KEY_LOCATION:
#endif /* defined(PSA_CRYPTO_DRIVER_TFM_BUILTIN_KEY_LOADER) */       //NXP TFM --- END ---
#if defined(PSA_CRYPTO_ACCELERATOR_DRIVER_PRESENT)
            /* Transparent drivers are limited to generating asymmetric keys */
            if( PSA_KEY_TYPE_IS_ASYMMETRIC( attributes->core.type ) )
            {
            /* Cycle through all known transparent accelerators */
#if defined(PSA_CRYPTO_DRIVER_CC3XX)                                 //NXP TFM --- BEGIN ---
                status = cc3xx_generate_key(
                    attributes, key_buffer, key_buffer_size,
                    key_buffer_length );
                break;
#endif /* PSA_CRYPTO_DRIVER_CC3XX */                                 //NXP TFM --- END ---
#if defined(PSA_CRYPTO_DRIVER_TEST)
                status = mbedtls_test_transparent_generate_key(
                    attributes, key_buffer, key_buffer_size,
                    key_buffer_length );
                /* Declared with fallback == true */
                if( status != PSA_ERROR_NOT_SUPPORTED )
                    break;
#endif /* PSA_CRYPTO_DRIVER_TEST */
            }
#endif /* PSA_CRYPTO_ACCELERATOR_DRIVER_PRESENT */

            /* Software fallback */
            status = psa_generate_key_internal(
                attributes, key_buffer, key_buffer_size, key_buffer_length );
            break;

        /* Add cases for opaque driver here */
#if defined(PSA_CRYPTO_ACCELERATOR_DRIVER_PRESENT)
#if defined(PSA_CRYPTO_DRIVER_TEST)
        case PSA_CRYPTO_TEST_DRIVER_LOCATION:
            status = mbedtls_test_opaque_generate_key(
                attributes, key_buffer, key_buffer_size, key_buffer_length );
            break;
#endif /* PSA_CRYPTO_DRIVER_TEST */
#endif /* PSA_CRYPTO_ACCELERATOR_DRIVER_PRESENT */

        default:
            /* Key is declared with a lifetime not known to us */
            status = PSA_ERROR_INVALID_ARGUMENT;
            break;
    }

    return( status );
}

psa_status_t psa_driver_wrapper_import_key(
    const psa_key_attributes_t *attributes,
    const uint8_t *data,
    size_t data_length,
    uint8_t *key_buffer,
    size_t key_buffer_size,
    size_t *key_buffer_length,
    size_t *bits )
{

    psa_status_t status = PSA_ERROR_CORRUPTION_DETECTED;
    psa_key_location_t location = PSA_KEY_LIFETIME_GET_LOCATION(
                                      psa_get_key_lifetime( attributes ) );

    /* Try dynamically-registered SE interface first */
#if defined(MBEDTLS_PSA_CRYPTO_SE_C)
    const psa_drv_se_t *drv;
    psa_drv_se_context_t *drv_context;

    if( psa_get_se_driver( attributes->core.lifetime, &drv, &drv_context ) )
    {
        if( drv->key_management == NULL ||
            drv->key_management->p_import == NULL )
            return( PSA_ERROR_NOT_SUPPORTED );

        /* The driver should set the number of key bits, however in
         * case it doesn't, we initialize bits to an invalid value. */
        *bits = PSA_MAX_KEY_BITS + 1;
        status = drv->key_management->p_import(
            drv_context,
            *( (psa_key_slot_number_t *)key_buffer ),
            attributes, data, data_length, bits );

        if( status != PSA_SUCCESS )
            return( status );

        if( (*bits) > PSA_MAX_KEY_BITS )
            return( PSA_ERROR_NOT_SUPPORTED );

        return( PSA_SUCCESS );
    }
#endif /* PSA_CRYPTO_SE_C */

    switch( location )
    {
        case PSA_KEY_LOCATION_LOCAL_STORAGE:
#if defined(PSA_CRYPTO_DRIVER_TFM_BUILTIN_KEY_LOADER)               //NXP TFM --- BEGIN ---
        case TFM_BUILTIN_KEY_LOADER_KEY_LOCATION:                   
#endif /* defined(PSA_CRYPTO_DRIVER_TFM_BUILTIN_KEY_LOADER) */      //NXP TFM --- END ---
            /* Key is stored in the slot in export representation, so
             * cycle through all known transparent accelerators */
#if defined(PSA_CRYPTO_ACCELERATOR_DRIVER_PRESENT)

#if (defined(PSA_CRYPTO_DRIVER_TEST) )
            status = mbedtls_test_transparent_import_key
                (attributes,
                                data,
                                data_length,
                                key_buffer,
                                key_buffer_size,
                                key_buffer_length,
                                bits
            );

            if( status != PSA_ERROR_NOT_SUPPORTED )
                return( status );
#endif


#endif /* PSA_CRYPTO_ACCELERATOR_DRIVER_PRESENT */

            /* Fell through, meaning no accelerator supports this operation */
            return( psa_import_key_into_slot( attributes,
                                              data, data_length,
                                              key_buffer, key_buffer_size,
                                              key_buffer_length, bits ) );
        /* Add cases for opaque driver here */
#if defined(PSA_CRYPTO_ACCELERATOR_DRIVER_PRESENT)

#if (defined(PSA_CRYPTO_DRIVER_TEST) )
        case 0x7fffff:
            return( mbedtls_test_opaque_import_key
            (attributes,
                            data,
                            data_length,
                            key_buffer,
                            key_buffer_size,
                            key_buffer_length,
                            bits
        ));
#endif


#endif /* PSA_CRYPTO_ACCELERATOR_DRIVER_PRESENT */
        default:
            (void)status;
            return( PSA_ERROR_INVALID_ARGUMENT );
    }

}

psa_status_t psa_driver_wrapper_export_key(
    const psa_key_attributes_t *attributes,
    const uint8_t *key_buffer, size_t key_buffer_size,
    uint8_t *data, size_t data_size, size_t *data_length )

{

    psa_status_t status = PSA_ERROR_INVALID_ARGUMENT;
    psa_key_location_t location = PSA_KEY_LIFETIME_GET_LOCATION(
                                      psa_get_key_lifetime( attributes ) );

    /* Try dynamically-registered SE interface first */
#if defined(MBEDTLS_PSA_CRYPTO_SE_C)
    const psa_drv_se_t *drv;
    psa_drv_se_context_t *drv_context;

    if( psa_get_se_driver( attributes->core.lifetime, &drv, &drv_context ) )
    {
        if( ( drv->key_management == NULL   ) ||
            ( drv->key_management->p_export == NULL ) )
        {
            return( PSA_ERROR_NOT_SUPPORTED );
        }

        return( drv->key_management->p_export(
                     drv_context,
                     *( (psa_key_slot_number_t *)key_buffer ),
                     data, data_size, data_length ) );
    }
#endif /* PSA_CRYPTO_SE_C */

    switch( location )
    {
        case PSA_KEY_LOCATION_LOCAL_STORAGE:
#if defined(PSA_CRYPTO_DRIVER_TFM_BUILTIN_KEY_LOADER)               //NXP TFM --- BEGIN ---
        case TFM_BUILTIN_KEY_LOADER_KEY_LOCATION:                   
#endif /* defined(PSA_CRYPTO_DRIVER_TFM_BUILTIN_KEY_LOADER) */      //NXP TFM --- END ---
            return( psa_export_key_internal( attributes,
                                             key_buffer,
                                             key_buffer_size,
                                             data,
                                             data_size,
                                             data_length ) );

        /* Add cases for opaque driver here */
#if defined(PSA_CRYPTO_ACCELERATOR_DRIVER_PRESENT)

#if (defined(PSA_CRYPTO_DRIVER_TEST) )
        case 0x7fffff:
            return( mbedtls_test_opaque_export_key
            (attributes,
                            key_buffer,
                            key_buffer_size,
                            data,
                            data_size,
                            data_length
        ));
#endif


#endif /* PSA_CRYPTO_ACCELERATOR_DRIVER_PRESENT */
        default:
            /* Key is declared with a lifetime not known to us */
            return( status );
    }

}

psa_status_t psa_driver_wrapper_export_public_key(
    const psa_key_attributes_t *attributes,
    const uint8_t *key_buffer, size_t key_buffer_size,
    uint8_t *data, size_t data_size, size_t *data_length )

{

    psa_status_t status = PSA_ERROR_INVALID_ARGUMENT;
    psa_key_location_t location = PSA_KEY_LIFETIME_GET_LOCATION(
                                      psa_get_key_lifetime( attributes ) );

    /* Try dynamically-registered SE interface first */
#if defined(MBEDTLS_PSA_CRYPTO_SE_C)
    const psa_drv_se_t *drv;
    psa_drv_se_context_t *drv_context;

    if( psa_get_se_driver( attributes->core.lifetime, &drv, &drv_context ) )
    {
        if( ( drv->key_management == NULL ) ||
            ( drv->key_management->p_export_public == NULL ) )
        {
            return( PSA_ERROR_NOT_SUPPORTED );
        }

        return( drv->key_management->p_export_public(
                    drv_context,
                    *( (psa_key_slot_number_t *)key_buffer ),
                    data, data_size, data_length ) );
    }
#endif /* MBEDTLS_PSA_CRYPTO_SE_C */

    switch( location )
    {
        case PSA_KEY_LOCATION_LOCAL_STORAGE:
#if defined(PSA_CRYPTO_DRIVER_TFM_BUILTIN_KEY_LOADER)               //NXP TFM --- BEGIN ---
        case TFM_BUILTIN_KEY_LOADER_KEY_LOCATION:                  
#endif /* defined(PSA_CRYPTO_DRIVER_TFM_BUILTIN_KEY_LOADER) */      //NXP TFM --- END ---
            /* Key is stored in the slot in export representation, so
             * cycle through all known transparent accelerators */
#if defined(PSA_CRYPTO_ACCELERATOR_DRIVER_PRESENT)

#if (defined(PSA_CRYPTO_DRIVER_TEST) )
            status = mbedtls_test_transparent_export_public_key
                (attributes,
                                key_buffer,
                                key_buffer_size,
                                data,
                                data_size,
                                data_length
            );

            if( status != PSA_ERROR_NOT_SUPPORTED )
                return( status );
#endif
#if defined(PSA_CRYPTO_DRIVER_CC3XX)                               //NXP TFM --- BEGIN ---
            status = cc3xx_export_public_key(
                         attributes,
                         key_buffer,
                         key_buffer_size,
                         data,
                         data_size,
                         data_length );
            return( status );
#endif /* PSA_CRYPTO_DRIVER_CC3XX */                                //NXP TFM --- END ---

#endif /* PSA_CRYPTO_ACCELERATOR_DRIVER_PRESENT */
#if !defined(PSA_CRYPTO_DRIVER_CC3XX)                              //NXP TFM --- BEGIN ---
            /* Fell through, meaning no accelerator supports this operation */
            return( psa_export_public_key_internal( attributes,
                                                    key_buffer,
                                                    key_buffer_size,
                                                    data,
                                                    data_size,
                                                    data_length ) );
#endif /* PSA_CRYPTO_DRIVER_CC3XX */                               //NXP TFM --- END ---
        /* Add cases for opaque driver here */
#if defined(PSA_CRYPTO_ACCELERATOR_DRIVER_PRESENT)

#if (defined(PSA_CRYPTO_DRIVER_TEST) )
        case 0x7fffff:
            return( mbedtls_test_opaque_export_public_key
            (attributes,
                            key_buffer,
                            key_buffer_size,
                            data,
                            data_size,
                            data_length
        ));
#endif


#endif /* PSA_CRYPTO_ACCELERATOR_DRIVER_PRESENT */
        default:
            /* Key is declared with a lifetime not known to us */
            return( status );
    }

}

psa_status_t psa_driver_wrapper_get_builtin_key(
    psa_drv_slot_number_t slot_number,
    psa_key_attributes_t *attributes,
    uint8_t *key_buffer, size_t key_buffer_size, size_t *key_buffer_length )
{

    psa_key_location_t location = PSA_KEY_LIFETIME_GET_LOCATION( attributes->core.lifetime );
    switch( location )
    {
#if defined(PSA_CRYPTO_DRIVER_TEST)

#if (defined(PSA_CRYPTO_DRIVER_TEST) )
        case 0x7fffff:
            return( mbedtls_test_opaque_get_builtin_key
            (slot_number,
                            attributes,
                            key_buffer,
                            key_buffer_size,
                            key_buffer_length
        ));
#endif


#endif /* PSA_CRYPTO_DRIVER_TEST */
#if defined(PSA_CRYPTO_DRIVER_TFM_BUILTIN_KEY_LOADER)                         //NXP TFM --- BEGIN ---
        case TFM_BUILTIN_KEY_LOADER_KEY_LOCATION:
            return( tfm_builtin_key_loader_get_builtin_key(
                        slot_number,
                        attributes,
                        key_buffer, key_buffer_size, key_buffer_length ) );
#endif /* PSA_CRYPTO_DRIVER_TFM_BUILTIN_KEY_LOADER */                         //NXP TFM --- END ---
        default:
            (void) slot_number;
            (void) key_buffer;
            (void) key_buffer_size;
            (void) key_buffer_length;
            return( PSA_ERROR_DOES_NOT_EXIST );
    }

}

psa_status_t psa_driver_wrapper_copy_key(
    psa_key_attributes_t *attributes,
    const uint8_t *source_key, size_t source_key_length,
    uint8_t *target_key_buffer, size_t target_key_buffer_size,
    size_t *target_key_buffer_length )
{

    psa_status_t status = PSA_ERROR_CORRUPTION_DETECTED;
    psa_key_location_t location =
        PSA_KEY_LIFETIME_GET_LOCATION( attributes->core.lifetime );

#if defined(MBEDTLS_PSA_CRYPTO_SE_C)
    const psa_drv_se_t *drv;
    psa_drv_se_context_t *drv_context;

    if( psa_get_se_driver( attributes->core.lifetime, &drv, &drv_context ) )
    {
        /* Copying to a secure element is not implemented yet. */
        return( PSA_ERROR_NOT_SUPPORTED );
    }
#endif /* MBEDTLS_PSA_CRYPTO_SE_C */

    switch( location )
    {
#if defined(PSA_CRYPTO_ACCELERATOR_DRIVER_PRESENT)

#if (defined(PSA_CRYPTO_DRIVER_TEST) )
        case 0x7fffff:
            return( mbedtls_test_opaque_copy_key
            (attributes,
                            source_key,
                            source_key_length,
                            target_key_buffer,
                            target_key_buffer_size,
                            target_key_buffer_length
        ));
#endif


#endif /* PSA_CRYPTO_ACCELERATOR_DRIVER_PRESENT */
        default:
            (void)source_key;
            (void)source_key_length;
            (void)target_key_buffer;
            (void)target_key_buffer_size;
            (void)target_key_buffer_length;
            status = PSA_ERROR_INVALID_ARGUMENT;
    }
    return( status );

}

/*
 * Cipher functions
 */
psa_status_t psa_driver_wrapper_cipher_encrypt(
    const psa_key_attributes_t *attributes,
    const uint8_t *key_buffer,
    size_t key_buffer_size,
    psa_algorithm_t alg,
    const uint8_t *iv,
    size_t iv_length,
    const uint8_t *input,
    size_t input_length,
    uint8_t *output,
    size_t output_size,
    size_t *output_length )
{
    psa_status_t status = PSA_ERROR_CORRUPTION_DETECTED;
    psa_key_location_t location =
        PSA_KEY_LIFETIME_GET_LOCATION( attributes->core.lifetime );

    switch( location )
    {
        case PSA_KEY_LOCATION_LOCAL_STORAGE:
#if defined(PSA_CRYPTO_DRIVER_TFM_BUILTIN_KEY_LOADER)                          //NXP TFM --- BEGIN ---
        case TFM_BUILTIN_KEY_LOADER_KEY_LOCATION:                              
#endif /* defined(PSA_CRYPTO_DRIVER_TFM_BUILTIN_KEY_LOADER) */                 //NXP TFM --- END ---
            /* Key is stored in the slot in export representation, so
             * cycle through all known transparent accelerators */
#if defined(PSA_CRYPTO_ACCELERATOR_DRIVER_PRESENT)
#if defined(PSA_CRYPTO_DRIVER_TEST)
            status = mbedtls_test_transparent_cipher_encrypt( attributes,
                                                              key_buffer,
                                                              key_buffer_size,
                                                              alg,
                                                              iv,
                                                              iv_length,
                                                              input,
                                                              input_length,
                                                              output,
                                                              output_size,
                                                              output_length );
            /* Declared with fallback == true */
            if( status != PSA_ERROR_NOT_SUPPORTED )
                return( status );
#endif /* PSA_CRYPTO_DRIVER_TEST */
#if defined(PSA_CRYPTO_DRIVER_CC3XX)                           //NXP TFM --- BEGIN ---
            status = cc3xx_cipher_encrypt( attributes,
                                           key_buffer,
                                           key_buffer_size,
                                           alg,
                                           iv,
                                           iv_length,
                                           input,
                                           input_length,
                                           output,
                                           output_size,
                                           output_length );
            return( status );
#endif /* PSA_CRYPTO_DRIVER_CC3XX */                            //NXP TFM --- END ---
#endif /* PSA_CRYPTO_ACCELERATOR_DRIVER_PRESENT */

#if defined(MBEDTLS_PSA_BUILTIN_CIPHER) && !defined(PSA_CRYPTO_DRIVER_CC3XX)  //NXP TFM
            return( mbedtls_psa_cipher_encrypt( attributes,
                                                key_buffer,
                                                key_buffer_size,
                                                alg,
                                                iv,
                                                iv_length,
                                                input,
                                                input_length,
                                                output,
                                                output_size,
                                                output_length ) );
#else
            return( PSA_ERROR_NOT_SUPPORTED );
#endif

        /* Add cases for opaque driver here */
#if defined(PSA_CRYPTO_ACCELERATOR_DRIVER_PRESENT)
#if defined(PSA_CRYPTO_DRIVER_TEST)
        case PSA_CRYPTO_TEST_DRIVER_LOCATION:
            return( mbedtls_test_opaque_cipher_encrypt( attributes,
                                                        key_buffer,
                                                        key_buffer_size,
                                                        alg,
                                                        iv,
                                                        iv_length,
                                                        input,
                                                        input_length,
                                                        output,
                                                        output_size,
                                                        output_length ) );
#endif /* PSA_CRYPTO_DRIVER_TEST */
#endif /* PSA_CRYPTO_ACCELERATOR_DRIVER_PRESENT */

        default:
            /* Key is declared with a lifetime not known to us */
            (void)status;
            (void)key_buffer;
            (void)key_buffer_size;
            (void)alg;
            (void)iv;
            (void)iv_length;
            (void)input;
            (void)input_length;
            (void)output;
            (void)output_size;
            (void)output_length;
            return( PSA_ERROR_INVALID_ARGUMENT );
    }
}

psa_status_t psa_driver_wrapper_cipher_decrypt(
    const psa_key_attributes_t *attributes,
    const uint8_t *key_buffer,
    size_t key_buffer_size,
    psa_algorithm_t alg,
    const uint8_t *input,
    size_t input_length,
    uint8_t *output,
    size_t output_size,
    size_t *output_length )
{
    psa_status_t status = PSA_ERROR_CORRUPTION_DETECTED;
    psa_key_location_t location =
        PSA_KEY_LIFETIME_GET_LOCATION( attributes->core.lifetime );

    switch( location )
    {
        case PSA_KEY_LOCATION_LOCAL_STORAGE:
#if defined(PSA_CRYPTO_DRIVER_TFM_BUILTIN_KEY_LOADER)                          //NXP TFM --- BEGIN ---
        case TFM_BUILTIN_KEY_LOADER_KEY_LOCATION:                              
#endif /* defined(PSA_CRYPTO_DRIVER_TFM_BUILTIN_KEY_LOADER) */                 //NXP TFM --- END ---
            /* Key is stored in the slot in export representation, so
             * cycle through all known transparent accelerators */
#if defined(PSA_CRYPTO_ACCELERATOR_DRIVER_PRESENT)
#if defined(PSA_CRYPTO_DRIVER_TEST)
            status = mbedtls_test_transparent_cipher_decrypt( attributes,
                                                              key_buffer,
                                                              key_buffer_size,
                                                              alg,
                                                              input,
                                                              input_length,
                                                              output,
                                                              output_size,
                                                              output_length );
            /* Declared with fallback == true */
            if( status != PSA_ERROR_NOT_SUPPORTED )
                return( status );
#endif /* PSA_CRYPTO_DRIVER_TEST */
#if defined(PSA_CRYPTO_DRIVER_CC3XX)                           //NXP TFM --- BEGIN ---
            status = cc3xx_cipher_decrypt( attributes,
                                           key_buffer,
                                           key_buffer_size,
                                           alg,
                                           input,
                                           input_length,
                                           output,
                                           output_size,
                                           output_length );
            return( status );
#endif /* PSA_CRYPTO_DRIVER_CC3XX */                             //NXP TFM --- END ---
#endif /* PSA_CRYPTO_ACCELERATOR_DRIVER_PRESENT */

#if defined(MBEDTLS_PSA_BUILTIN_CIPHER) && !defined(PSA_CRYPTO_DRIVER_CC3XX) //NXP TFM
            return( mbedtls_psa_cipher_decrypt( attributes,
                                                key_buffer,
                                                key_buffer_size,
                                                alg,
                                                input,
                                                input_length,
                                                output,
                                                output_size,
                                                output_length ) );
#else
            return( PSA_ERROR_NOT_SUPPORTED );
#endif

        /* Add cases for opaque driver here */
#if defined(PSA_CRYPTO_ACCELERATOR_DRIVER_PRESENT)
#if defined(PSA_CRYPTO_DRIVER_TEST)
        case PSA_CRYPTO_TEST_DRIVER_LOCATION:
            return( mbedtls_test_opaque_cipher_decrypt( attributes,
                                                        key_buffer,
                                                        key_buffer_size,
                                                        alg,
                                                        input,
                                                        input_length,
                                                        output,
                                                        output_size,
                                                        output_length ) );
#endif /* PSA_CRYPTO_DRIVER_TEST */
#endif /* PSA_CRYPTO_ACCELERATOR_DRIVER_PRESENT */

        default:
            /* Key is declared with a lifetime not known to us */
            (void)status;
            (void)key_buffer;
            (void)key_buffer_size;
            (void)alg;
            (void)input;
            (void)input_length;
            (void)output;
            (void)output_size;
            (void)output_length;
            return( PSA_ERROR_INVALID_ARGUMENT );
    }
}

psa_status_t psa_driver_wrapper_cipher_encrypt_setup(
    psa_cipher_operation_t *operation,
    const psa_key_attributes_t *attributes,
    const uint8_t *key_buffer, size_t key_buffer_size,
    psa_algorithm_t alg )
{
    psa_status_t status = PSA_ERROR_CORRUPTION_DETECTED;
    psa_key_location_t location =
        PSA_KEY_LIFETIME_GET_LOCATION( attributes->core.lifetime );

    switch( location )
    {
        case PSA_KEY_LOCATION_LOCAL_STORAGE:
#if defined(PSA_CRYPTO_DRIVER_TFM_BUILTIN_KEY_LOADER)                          //NXP TFM --- BEGIN ---
        case TFM_BUILTIN_KEY_LOADER_KEY_LOCATION:                              
#endif /* defined(PSA_CRYPTO_DRIVER_TFM_BUILTIN_KEY_LOADER) */                 //NXP TFM --- END ---
            /* Key is stored in the slot in export representation, so
             * cycle through all known transparent accelerators */
#if defined(PSA_CRYPTO_ACCELERATOR_DRIVER_PRESENT)
#if defined(PSA_CRYPTO_DRIVER_TEST)
            status = mbedtls_test_transparent_cipher_encrypt_setup(
                &operation->ctx.transparent_test_driver_ctx,
                attributes,
                key_buffer,
                key_buffer_size,
                alg );
            /* Declared with fallback == true */
            if( status == PSA_SUCCESS )
                operation->id = MBEDTLS_TEST_TRANSPARENT_DRIVER_ID;

            if( status != PSA_ERROR_NOT_SUPPORTED )
                return( status );
#endif /* PSA_CRYPTO_DRIVER_TEST */
#if defined(PSA_CRYPTO_DRIVER_CC3XX)                                          //NXP TFM --- BEGIN ---
            status = cc3xx_cipher_encrypt_setup(
                &operation->ctx.cc3xx_driver_ctx,
                attributes,
                key_buffer,
                key_buffer_size,
                alg );
            operation->id = PSA_CRYPTO_CC3XX_DRIVER_ID;
            return( status );
#endif /* PSA_CRYPTO_DRIVER_CC3XX */                                          //NXP TFM --- END ---
#endif /* PSA_CRYPTO_ACCELERATOR_DRIVER_PRESENT */
#if defined(MBEDTLS_PSA_BUILTIN_CIPHER) && !defined(PSA_CRYPTO_DRIVER_CC3XX)  //NXP TFM
            /* Fell through, meaning no accelerator supports this operation */
            status = mbedtls_psa_cipher_encrypt_setup( &operation->ctx.mbedtls_ctx,
                                                       attributes,
                                                       key_buffer,
                                                       key_buffer_size,
                                                       alg );
            if( status == PSA_SUCCESS )
                operation->id = PSA_CRYPTO_MBED_TLS_DRIVER_ID;

            if( status != PSA_ERROR_NOT_SUPPORTED )
                return( status );
#endif /* MBEDTLS_PSA_BUILTIN_CIPHER */
            return( PSA_ERROR_NOT_SUPPORTED );

        /* Add cases for opaque driver here */
#if defined(PSA_CRYPTO_ACCELERATOR_DRIVER_PRESENT)
#if defined(PSA_CRYPTO_DRIVER_TEST)
        case PSA_CRYPTO_TEST_DRIVER_LOCATION:
            status = mbedtls_test_opaque_cipher_encrypt_setup(
                &operation->ctx.opaque_test_driver_ctx,
                attributes,
                key_buffer, key_buffer_size,
                alg );

            if( status == PSA_SUCCESS )
                operation->id = MBEDTLS_TEST_OPAQUE_DRIVER_ID;

            return( status );
#endif /* PSA_CRYPTO_DRIVER_TEST */
#endif /* PSA_CRYPTO_ACCELERATOR_DRIVER_PRESENT */
        default:
            /* Key is declared with a lifetime not known to us */
            (void)status;
            (void)operation;
            (void)key_buffer;
            (void)key_buffer_size;
            (void)alg;
            return( PSA_ERROR_INVALID_ARGUMENT );
    }
}

psa_status_t psa_driver_wrapper_cipher_decrypt_setup(
    psa_cipher_operation_t *operation,
    const psa_key_attributes_t *attributes,
    const uint8_t *key_buffer, size_t key_buffer_size,
    psa_algorithm_t alg )
{
    psa_status_t status = PSA_ERROR_INVALID_ARGUMENT;
    psa_key_location_t location =
        PSA_KEY_LIFETIME_GET_LOCATION( attributes->core.lifetime );

    switch( location )
    {
        case PSA_KEY_LOCATION_LOCAL_STORAGE:
#if defined(PSA_CRYPTO_DRIVER_TFM_BUILTIN_KEY_LOADER)                          //NXP TFM --- BEGIN ---
        case TFM_BUILTIN_KEY_LOADER_KEY_LOCATION:                              
#endif /* defined(PSA_CRYPTO_DRIVER_TFM_BUILTIN_KEY_LOADER) */                 //NXP TFM --- END ---
            /* Key is stored in the slot in export representation, so
             * cycle through all known transparent accelerators */
#if defined(PSA_CRYPTO_ACCELERATOR_DRIVER_PRESENT)
#if defined(PSA_CRYPTO_DRIVER_TEST)
            status = mbedtls_test_transparent_cipher_decrypt_setup(
                &operation->ctx.transparent_test_driver_ctx,
                attributes,
                key_buffer,
                key_buffer_size,
                alg );
            /* Declared with fallback == true */
            if( status == PSA_SUCCESS )
                operation->id = MBEDTLS_TEST_TRANSPARENT_DRIVER_ID;

            if( status != PSA_ERROR_NOT_SUPPORTED )
                return( status );
#endif /* PSA_CRYPTO_DRIVER_TEST */
#if defined(PSA_CRYPTO_DRIVER_CC3XX)                                         //NXP TFM --- BEGIN ---
            status = cc3xx_cipher_decrypt_setup(
                &operation->ctx.cc3xx_driver_ctx,
                attributes,
                key_buffer,
                key_buffer_size,
                alg );
            operation->id = PSA_CRYPTO_CC3XX_DRIVER_ID;
            return( status );
#endif /* PSA_CRYPTO_DRIVER_CC3XX */                                         //NXP TFM --- END ---
#endif /* PSA_CRYPTO_ACCELERATOR_DRIVER_PRESENT */
#if defined(MBEDTLS_PSA_BUILTIN_CIPHER) && !defined(PSA_CRYPTO_DRIVER_CC3XX) //NXP TFM
            /* Fell through, meaning no accelerator supports this operation */
            status = mbedtls_psa_cipher_decrypt_setup( &operation->ctx.mbedtls_ctx,
                                                       attributes,
                                                       key_buffer,
                                                       key_buffer_size,
                                                       alg );
            if( status == PSA_SUCCESS )
                operation->id = PSA_CRYPTO_MBED_TLS_DRIVER_ID;

            return( status );
#else /* MBEDTLS_PSA_BUILTIN_CIPHER */
            return( PSA_ERROR_NOT_SUPPORTED );
#endif /* MBEDTLS_PSA_BUILTIN_CIPHER */

        /* Add cases for opaque driver here */
#if defined(PSA_CRYPTO_ACCELERATOR_DRIVER_PRESENT)
#if defined(PSA_CRYPTO_DRIVER_TEST)
        case PSA_CRYPTO_TEST_DRIVER_LOCATION:
            status = mbedtls_test_opaque_cipher_decrypt_setup(
                         &operation->ctx.opaque_test_driver_ctx,
                         attributes,
                         key_buffer, key_buffer_size,
                         alg );

            if( status == PSA_SUCCESS )
                operation->id = MBEDTLS_TEST_OPAQUE_DRIVER_ID;

            return( status );
#endif /* PSA_CRYPTO_DRIVER_TEST */
#endif /* PSA_CRYPTO_ACCELERATOR_DRIVER_PRESENT */
        default:
            /* Key is declared with a lifetime not known to us */
            (void)status;
            (void)operation;
            (void)key_buffer;
            (void)key_buffer_size;
            (void)alg;
            return( PSA_ERROR_INVALID_ARGUMENT );
    }
}

psa_status_t psa_driver_wrapper_cipher_set_iv(
    psa_cipher_operation_t *operation,
    const uint8_t *iv,
    size_t iv_length )
{
    switch( operation->id )
    {
#if defined(MBEDTLS_PSA_BUILTIN_CIPHER) && !defined(PSA_CRYPTO_DRIVER_CC3XX)  //NXP TFM
        case PSA_CRYPTO_MBED_TLS_DRIVER_ID:
            return( mbedtls_psa_cipher_set_iv( &operation->ctx.mbedtls_ctx,
                                               iv,
                                               iv_length ) );
#endif

#if defined(PSA_CRYPTO_ACCELERATOR_DRIVER_PRESENT)
#if defined(PSA_CRYPTO_DRIVER_TEST)
        case MBEDTLS_TEST_TRANSPARENT_DRIVER_ID:
            return( mbedtls_test_transparent_cipher_set_iv(
                        &operation->ctx.transparent_test_driver_ctx,
                        iv, iv_length ) );

        case MBEDTLS_TEST_OPAQUE_DRIVER_ID:
            return( mbedtls_test_opaque_cipher_set_iv(
                        &operation->ctx.opaque_test_driver_ctx,
                        iv, iv_length ) );
#endif /* PSA_CRYPTO_DRIVER_TEST */
#if defined(PSA_CRYPTO_DRIVER_CC3XX)                   //NXP TFM --- BEGIN ---
        case PSA_CRYPTO_CC3XX_DRIVER_ID:
            return( cc3xx_cipher_set_iv(
                        &operation->ctx.cc3xx_driver_ctx,
                        iv, iv_length ) );
#endif /* PSA_CRYPTO_DRIVER_CC3XX */                   //NXP TFM --- END ---
#endif /* PSA_CRYPTO_ACCELERATOR_DRIVER_PRESENT */
    }

    (void)iv;
    (void)iv_length;

    return( PSA_ERROR_INVALID_ARGUMENT );
}

psa_status_t psa_driver_wrapper_cipher_update(
    psa_cipher_operation_t *operation,
    const uint8_t *input,
    size_t input_length,
    uint8_t *output,
    size_t output_size,
    size_t *output_length )
{
    switch( operation->id )
    {
#if defined(MBEDTLS_PSA_BUILTIN_CIPHER) && !defined(PSA_CRYPTO_DRIVER_CC3XX) //NXP TFM
        case PSA_CRYPTO_MBED_TLS_DRIVER_ID:
            return( mbedtls_psa_cipher_update( &operation->ctx.mbedtls_ctx,
                                               input,
                                               input_length,
                                               output,
                                               output_size,
                                               output_length ) );
#endif

#if defined(PSA_CRYPTO_ACCELERATOR_DRIVER_PRESENT)
#if defined(PSA_CRYPTO_DRIVER_TEST)
        case MBEDTLS_TEST_TRANSPARENT_DRIVER_ID:
            return( mbedtls_test_transparent_cipher_update(
                        &operation->ctx.transparent_test_driver_ctx,
                        input, input_length,
                        output, output_size, output_length ) );

        case MBEDTLS_TEST_OPAQUE_DRIVER_ID:
            return( mbedtls_test_opaque_cipher_update(
                        &operation->ctx.opaque_test_driver_ctx,
                        input, input_length,
                        output, output_size, output_length ) );
#endif /* PSA_CRYPTO_DRIVER_TEST */
#if defined(PSA_CRYPTO_DRIVER_CC3XX)                       //NXP TFM --- BEGIN ---
        case PSA_CRYPTO_CC3XX_DRIVER_ID:
            return( cc3xx_cipher_update(
                        &operation->ctx.cc3xx_driver_ctx,
                        input, input_length,
                        output, output_size, output_length ) );
#endif /* PSA_CRYPTO_DRIVER_CC3XX */                       //NXP TFM --- END ---
#endif /* PSA_CRYPTO_ACCELERATOR_DRIVER_PRESENT */
    }

    (void)input;
    (void)input_length;
    (void)output;
    (void)output_size;
    (void)output_length;

    return( PSA_ERROR_INVALID_ARGUMENT );
}

psa_status_t psa_driver_wrapper_cipher_finish(
    psa_cipher_operation_t *operation,
    uint8_t *output,
    size_t output_size,
    size_t *output_length )
{
    switch( operation->id )
    {
#if defined(MBEDTLS_PSA_BUILTIN_CIPHER) && !defined(PSA_CRYPTO_DRIVER_CC3XX)  //NXP TFM
        case PSA_CRYPTO_MBED_TLS_DRIVER_ID:
            return( mbedtls_psa_cipher_finish( &operation->ctx.mbedtls_ctx,
                                               output,
                                               output_size,
                                               output_length ) );
#endif

#if defined(PSA_CRYPTO_ACCELERATOR_DRIVER_PRESENT)
#if defined(PSA_CRYPTO_DRIVER_TEST)
        case MBEDTLS_TEST_TRANSPARENT_DRIVER_ID:
            return( mbedtls_test_transparent_cipher_finish(
                        &operation->ctx.transparent_test_driver_ctx,
                        output, output_size, output_length ) );

        case MBEDTLS_TEST_OPAQUE_DRIVER_ID:
            return( mbedtls_test_opaque_cipher_finish(
                        &operation->ctx.opaque_test_driver_ctx,
                        output, output_size, output_length ) );
#endif /* PSA_CRYPTO_DRIVER_TEST */
#if defined(PSA_CRYPTO_DRIVER_CC3XX)                                       //NXP TFM --- BEGIN ---
        case PSA_CRYPTO_CC3XX_DRIVER_ID:
            return( cc3xx_cipher_finish(
                        &operation->ctx.cc3xx_driver_ctx,
                        output, output_size, output_length ) );
#endif /* PSA_CRYPTO_DRIVER_CC3XX*/                                        //NXP TFM --- END ---
#endif /* PSA_CRYPTO_ACCELERATOR_DRIVER_PRESENT */
    }

    (void)output;
    (void)output_size;
    (void)output_length;

    return( PSA_ERROR_INVALID_ARGUMENT );
}

psa_status_t psa_driver_wrapper_cipher_abort(
    psa_cipher_operation_t *operation )
{
    psa_status_t status = PSA_ERROR_CORRUPTION_DETECTED;

    switch( operation->id )
    {
#if defined(MBEDTLS_PSA_BUILTIN_CIPHER) && !defined(PSA_CRYPTO_DRIVER_CC3XX)   //NXP TFM
        case PSA_CRYPTO_MBED_TLS_DRIVER_ID:
            return( mbedtls_psa_cipher_abort( &operation->ctx.mbedtls_ctx ) );
#endif

#if defined(PSA_CRYPTO_ACCELERATOR_DRIVER_PRESENT)
#if defined(PSA_CRYPTO_DRIVER_TEST)
        case MBEDTLS_TEST_TRANSPARENT_DRIVER_ID:
            status = mbedtls_test_transparent_cipher_abort(
                         &operation->ctx.transparent_test_driver_ctx );
            mbedtls_platform_zeroize(
                &operation->ctx.transparent_test_driver_ctx,
                sizeof( operation->ctx.transparent_test_driver_ctx ) );
            return( status );

        case MBEDTLS_TEST_OPAQUE_DRIVER_ID:
            status = mbedtls_test_opaque_cipher_abort(
                         &operation->ctx.opaque_test_driver_ctx );
            mbedtls_platform_zeroize(
                &operation->ctx.opaque_test_driver_ctx,
                sizeof( operation->ctx.opaque_test_driver_ctx ) );
            return( status );
#endif /* PSA_CRYPTO_DRIVER_TEST */
#if defined(PSA_CRYPTO_DRIVER_CC3XX)                         //NXP TFM --- BEGIN ---
        case PSA_CRYPTO_CC3XX_DRIVER_ID:
            status = cc3xx_cipher_abort(
                         &operation->ctx.cc3xx_driver_ctx );
            mbedtls_platform_zeroize(
                &operation->ctx.cc3xx_driver_ctx,
                sizeof( operation->ctx.cc3xx_driver_ctx ) );
            return( status );
#endif /* PSA_CRYPTO_DRIVER_CC3XX */                         //NXP TFM --- END ---
#endif /* PSA_CRYPTO_ACCELERATOR_DRIVER_PRESENT */
    }

    (void)status;
    return( PSA_ERROR_INVALID_ARGUMENT );
}

/*
 * Hashing functions
 */
psa_status_t psa_driver_wrapper_hash_compute(
    psa_algorithm_t alg,
    const uint8_t *input,
    size_t input_length,
    uint8_t *hash,
    size_t hash_size,
    size_t *hash_length)
{
    psa_status_t status = PSA_ERROR_CORRUPTION_DETECTED;

    /* Try accelerators first */
#if defined(PSA_CRYPTO_ACCELERATOR_DRIVER_PRESENT)        //NXP TFM
#if defined(PSA_CRYPTO_DRIVER_TEST)
    status = mbedtls_test_transparent_hash_compute(
                alg, input, input_length, hash, hash_size, hash_length );
    if( status != PSA_ERROR_NOT_SUPPORTED )
        return( status );
#endif /* PSA_CRYPTO_DRIVER_TEST */
#if defined(PSA_CRYPTO_DRIVER_CC3XX)                      //NXP TFM --- BEGIN ---
    status = cc3xx_hash_compute(alg, input, input_length, hash, hash_size,
            hash_length);
    return status;
#endif /* defined(PSA_CRYPTO_DRIVER_CC3XX) */             //NXP TFM --- END ---
#endif /* PSA_CRYPTO_ACCELERATOR_DRIVER_PRESENT */
    /* If software fallback is compiled in, try fallback */
#if defined(MBEDTLS_PSA_BUILTIN_HASH) && !defined(PSA_CRYPTO_DRIVER_CC3XX)   //NXP TFM
    status = mbedtls_psa_hash_compute( alg, input, input_length,
                                       hash, hash_size, hash_length );
    if( status != PSA_ERROR_NOT_SUPPORTED )
        return( status );
#endif
    (void) status;
    (void) alg;
    (void) input;
    (void) input_length;
    (void) hash;
    (void) hash_size;
    (void) hash_length;

    return( PSA_ERROR_NOT_SUPPORTED );
}

psa_status_t psa_driver_wrapper_hash_setup(
    psa_hash_operation_t *operation,
    psa_algorithm_t alg )
{
    psa_status_t status = PSA_ERROR_CORRUPTION_DETECTED;

    /* Try setup on accelerators first */
#if defined(PSA_CRYPTO_ACCELERATOR_DRIVER_PRESENT)   //NXP TFM
#if defined(PSA_CRYPTO_DRIVER_TEST)
    status = mbedtls_test_transparent_hash_setup(
                &operation->ctx.test_driver_ctx, alg );
    if( status == PSA_SUCCESS )
        operation->id = MBEDTLS_TEST_TRANSPARENT_DRIVER_ID;

    if( status != PSA_ERROR_NOT_SUPPORTED )
        return( status );
#endif /* PSA_CRYPTO_DRIVER_TEST */
#if defined(PSA_CRYPTO_DRIVER_CC3XX)                 //NXP TFM --- BEGIN ---
    status = cc3xx_hash_setup(&operation->ctx.cc3xx_driver_ctx, alg);
    operation->id = PSA_CRYPTO_CC3XX_DRIVER_ID;
    return( status );
#endif /* PSA_CRYPTO_DRIVER_CC3XX */                 //NXP TFM --- END ---
#endif /* PSA_CRYPTO_ACCELERATOR_DRIVER_PRESENT */

#if defined(MBEDTLS_PSA_BUILTIN_HASH) && !defined(PSA_CRYPTO_DRIVER_CC3XX)   //NXP TFM
    /* If software fallback is compiled in, try fallback */
    status = mbedtls_psa_hash_setup( &operation->ctx.mbedtls_ctx, alg );
    if( status == PSA_SUCCESS )
        operation->id = PSA_CRYPTO_MBED_TLS_DRIVER_ID;

    if( status != PSA_ERROR_NOT_SUPPORTED )
        return( status );
#endif
    /* Nothing left to try if we fall through here */
    (void) status;
    (void) operation;
    (void) alg;
    return( PSA_ERROR_NOT_SUPPORTED );
}

psa_status_t psa_driver_wrapper_hash_clone(
    const psa_hash_operation_t *source_operation,
    psa_hash_operation_t *target_operation )
{
    switch( source_operation->id )
    {
#if defined(PSA_CRYPTO_ACCELERATOR_DRIVER_PRESENT)            //NXP TFM
#if defined(PSA_CRYPTO_DRIVER_TEST)
        case MBEDTLS_TEST_TRANSPARENT_DRIVER_ID:
            target_operation->id = MBEDTLS_TEST_TRANSPARENT_DRIVER_ID;
            return( mbedtls_test_transparent_hash_clone(
                        &source_operation->ctx.test_driver_ctx,
                        &target_operation->ctx.test_driver_ctx ) );
#endif /* PSA_CRYPTO_DRIVER_TEST */
#if defined(PSA_CRYPTO_DRIVER_CC3XX)                       //NXP TFM --- BEGIN ---
        case PSA_CRYPTO_CC3XX_DRIVER_ID:
            target_operation->id = PSA_CRYPTO_CC3XX_DRIVER_ID;
            return( cc3xx_hash_clone(
                        &source_operation->ctx.cc3xx_driver_ctx,
                        &target_operation->ctx.cc3xx_driver_ctx ) );

#endif /* PSA_CRYPTO_DRIVER_CC3XX */
#endif /* PSA_CRYPTO_ACCELERATOR_DRIVER_PRESENT */
#if defined(MBEDTLS_PSA_BUILTIN_HASH) && !defined(PSA_CRYPTO_DRIVER_CC3XX)
        case PSA_CRYPTO_MBED_TLS_DRIVER_ID:
            target_operation->id = PSA_CRYPTO_MBED_TLS_DRIVER_ID;
            return( mbedtls_psa_hash_clone( &source_operation->ctx.mbedtls_ctx,
                                            &target_operation->ctx.mbedtls_ctx ) );
#endif                                                     //NXP TFM --- END ---
        default:
            (void) target_operation;
            return( PSA_ERROR_BAD_STATE );
    }
}

psa_status_t psa_driver_wrapper_hash_update(
    psa_hash_operation_t *operation,
    const uint8_t *input,
    size_t input_length )
{
    switch( operation->id )
    {
#if defined(PSA_CRYPTO_ACCELERATOR_DRIVER_PRESENT)      //NXP TFM
#if defined(PSA_CRYPTO_DRIVER_TEST)
        case MBEDTLS_TEST_TRANSPARENT_DRIVER_ID:
            return( mbedtls_test_transparent_hash_update(
                        &operation->ctx.test_driver_ctx,
                        input, input_length ) );
#endif /* PSA_CRYPTO_DRIVER_TEST */
#if defined(PSA_CRYPTO_DRIVER_CC3XX)                    //NXP TFM --- BEGIN ---
        case PSA_CRYPTO_CC3XX_DRIVER_ID:
            return( cc3xx_hash_update(
                        &operation->ctx.cc3xx_driver_ctx,
                        input, input_length ) );
#endif /* PSA_CRYPTO_DRIVER_CC3XX */
#endif /* PSA_CRYPTO_ACCELERATOR_DRIVER_PRESENT */
#if defined(MBEDTLS_PSA_BUILTIN_HASH) && !defined(PSA_CRYPTO_DRIVER_CC3XX)
        case PSA_CRYPTO_MBED_TLS_DRIVER_ID:
            return( mbedtls_psa_hash_update( &operation->ctx.mbedtls_ctx,
                                             input, input_length ) );
#endif                                                  //NXP TFM --- END ---
        default:
            (void) input;
            (void) input_length;
            return( PSA_ERROR_BAD_STATE );
    }
}

psa_status_t psa_driver_wrapper_hash_finish(
    psa_hash_operation_t *operation,
    uint8_t *hash,
    size_t hash_size,
    size_t *hash_length )
{
    switch( operation->id )
    {
#if defined(PSA_CRYPTO_ACCELERATOR_DRIVER_PRESENT)        //NXP TFM
#if defined(PSA_CRYPTO_DRIVER_TEST)
        case MBEDTLS_TEST_TRANSPARENT_DRIVER_ID:
            return( mbedtls_test_transparent_hash_finish(
                        &operation->ctx.test_driver_ctx,
                        hash, hash_size, hash_length ) );
#endif /* PSA_CRYPTO_DRIVER_TEST */
#if defined(PSA_CRYPTO_DRIVER_CC3XX)                     //NXP TFM --- BEGIN ---
        case PSA_CRYPTO_CC3XX_DRIVER_ID:
            return( cc3xx_hash_finish(
                        &operation->ctx.cc3xx_driver_ctx,
                        hash, hash_size, hash_length ) );
#endif /* PSA_CRYPTO_DRIVER_CC3XX */
#endif /* PSA_CRYPTO_ACCELERATOR_DRIVER_PRESENT */
#if defined(MBEDTLS_PSA_BUILTIN_HASH) && !defined(PSA_CRYPTO_DRIVER_CC3XX)
        case PSA_CRYPTO_MBED_TLS_DRIVER_ID:
            return( mbedtls_psa_hash_finish( &operation->ctx.mbedtls_ctx,
                                             hash, hash_size, hash_length ) );
#endif                                                   //NXP TFM --- END ---
        default:
            (void) hash;
            (void) hash_size;
            (void) hash_length;
            return( PSA_ERROR_BAD_STATE );
    }
}

psa_status_t psa_driver_wrapper_hash_abort(
    psa_hash_operation_t *operation )
{
    switch( operation->id )
    {
#if defined(PSA_CRYPTO_ACCELERATOR_DRIVER_PRESENT)       //NXP TFM
#if defined(PSA_CRYPTO_DRIVER_TEST)
        case MBEDTLS_TEST_TRANSPARENT_DRIVER_ID:
            return( mbedtls_test_transparent_hash_abort(
                        &operation->ctx.test_driver_ctx ) );
#endif /* PSA_CRYPTO_DRIVER_TEST */
#if defined(PSA_CRYPTO_DRIVER_CC3XX)                     //NXP TFM --- BEGIN ---
        case PSA_CRYPTO_CC3XX_DRIVER_ID:
            return( cc3xx_hash_abort(
                        &operation->ctx.cc3xx_driver_ctx ) );
#endif /* PSA_CRYPTO_DRIVER_CC3XX */
#endif /* PSA_CRYPTO_ACCELERATOR_DRIVER_PRESENT */
#if defined(MBEDTLS_PSA_BUILTIN_HASH) && !defined(PSA_CRYPTO_DRIVER_CC3XX)
        case PSA_CRYPTO_MBED_TLS_DRIVER_ID:
            return( mbedtls_psa_hash_abort( &operation->ctx.mbedtls_ctx ) );
#endif                                                  //NXP TFM --- END ---
        default:
            return( PSA_ERROR_BAD_STATE );
    }
}

psa_status_t psa_driver_wrapper_aead_encrypt(
    const psa_key_attributes_t *attributes,
    const uint8_t *key_buffer, size_t key_buffer_size,
    psa_algorithm_t alg,
    const uint8_t *nonce, size_t nonce_length,
    const uint8_t *additional_data, size_t additional_data_length,
    const uint8_t *plaintext, size_t plaintext_length,
    uint8_t *ciphertext, size_t ciphertext_size, size_t *ciphertext_length )
{
    psa_status_t status = PSA_ERROR_CORRUPTION_DETECTED;
    psa_key_location_t location =
        PSA_KEY_LIFETIME_GET_LOCATION( attributes->core.lifetime );

    switch( location )
    {
        case PSA_KEY_LOCATION_LOCAL_STORAGE:
#if defined(PSA_CRYPTO_DRIVER_TFM_BUILTIN_KEY_LOADER)                          //NXP TFM
        case TFM_BUILTIN_KEY_LOADER_KEY_LOCATION:                              //NXP TFM
#endif /* defined(PSA_CRYPTO_DRIVER_TFM_BUILTIN_KEY_LOADER) */                 //NXP TFM
            /* Key is stored in the slot in export representation, so
             * cycle through all known transparent accelerators */

#if defined(PSA_CRYPTO_ACCELERATOR_DRIVER_PRESENT)
#if defined(PSA_CRYPTO_DRIVER_TEST)
            status = mbedtls_test_transparent_aead_encrypt(
                         attributes, key_buffer, key_buffer_size,
                         alg,
                         nonce, nonce_length,
                         additional_data, additional_data_length,
                         plaintext, plaintext_length,
                         ciphertext, ciphertext_size, ciphertext_length );
            /* Declared with fallback == true */
            if( status != PSA_ERROR_NOT_SUPPORTED )
                return( status );
#endif /* PSA_CRYPTO_DRIVER_TEST */
#if defined(PSA_CRYPTO_DRIVER_CC3XX)                               //NXP TFM --- BEGIN ---
            status = cc3xx_aead_encrypt(
                        attributes, key_buffer, key_buffer_size,
                        alg,
                        nonce, nonce_length,
                        additional_data, additional_data_length,
                        plaintext, plaintext_length,
                        ciphertext, ciphertext_size, ciphertext_length );

            return( status );
#endif /* PSA_CRYPTO_DRIVER_CC3XX */
#endif /* PSA_CRYPTO_ACCELERATOR_DRIVER_PRESENT */
#if !defined(PSA_CRYPTO_DRIVER_CC3XX)
            /* Fell through, meaning no accelerator supports this operation */
            return( mbedtls_psa_aead_encrypt(
                        attributes, key_buffer, key_buffer_size,
                        alg,
                        nonce, nonce_length,
                        additional_data, additional_data_length,
                        plaintext, plaintext_length,
                        ciphertext, ciphertext_size, ciphertext_length ) );
#endif /* PSA_CRYPTO_DRIVER_CC3XX */                                //NXP TFM --- END ---
        /* Add cases for opaque driver here */

        default:
            /* Key is declared with a lifetime not known to us */
            (void)status;
            return( PSA_ERROR_INVALID_ARGUMENT );
    }
}

psa_status_t psa_driver_wrapper_aead_decrypt(
    const psa_key_attributes_t *attributes,
    const uint8_t *key_buffer, size_t key_buffer_size,
    psa_algorithm_t alg,
    const uint8_t *nonce, size_t nonce_length,
    const uint8_t *additional_data, size_t additional_data_length,
    const uint8_t *ciphertext, size_t ciphertext_length,
    uint8_t *plaintext, size_t plaintext_size, size_t *plaintext_length )
{
    psa_status_t status = PSA_ERROR_CORRUPTION_DETECTED;
    psa_key_location_t location =
        PSA_KEY_LIFETIME_GET_LOCATION( attributes->core.lifetime );

    switch( location )
    {
        case PSA_KEY_LOCATION_LOCAL_STORAGE:
#if defined(PSA_CRYPTO_DRIVER_TFM_BUILTIN_KEY_LOADER)                          //NXP TFM --- BEGIN ---
        case TFM_BUILTIN_KEY_LOADER_KEY_LOCATION:                             
#endif /* defined(PSA_CRYPTO_DRIVER_TFM_BUILTIN_KEY_LOADER) */                 //NXP TFM --- END ---
            /* Key is stored in the slot in export representation, so
             * cycle through all known transparent accelerators */

#if defined(PSA_CRYPTO_ACCELERATOR_DRIVER_PRESENT)
#if defined(PSA_CRYPTO_DRIVER_TEST)
            status = mbedtls_test_transparent_aead_decrypt(
                        attributes, key_buffer, key_buffer_size,
                        alg,
                        nonce, nonce_length,
                        additional_data, additional_data_length,
                        ciphertext, ciphertext_length,
                        plaintext, plaintext_size, plaintext_length );
            /* Declared with fallback == true */
            if( status != PSA_ERROR_NOT_SUPPORTED )
                return( status );
#endif /* PSA_CRYPTO_DRIVER_TEST */
#if defined(PSA_CRYPTO_DRIVER_CC3XX)                                 //NXP TFM --- BEGIN ---
            status = cc3xx_aead_decrypt(
                        attributes, key_buffer, key_buffer_size,
                        alg,
                        nonce, nonce_length,
                        additional_data, additional_data_length,
                        ciphertext, ciphertext_length,
                        plaintext, plaintext_size, plaintext_length );

            return( status );
#endif /* PSA_CRYPTO_DRIVER_CC3XX */
#endif /* PSA_CRYPTO_ACCELERATOR_DRIVER_PRESENT */
#if !defined(PSA_CRYPTO_DRIVER_CC3XX)
            /* Fell through, meaning no accelerator supports this operation */
            return( mbedtls_psa_aead_decrypt(
                        attributes, key_buffer, key_buffer_size,
                        alg,
                        nonce, nonce_length,
                        additional_data, additional_data_length,
                        ciphertext, ciphertext_length,
                        plaintext, plaintext_size, plaintext_length ) );
#endif /* PSA_CRYPTO_DRIVER_CC3XX */                                 //NXP TFM --- END ---
        /* Add cases for opaque driver here */

        default:
            /* Key is declared with a lifetime not known to us */
            (void)status;
            return( PSA_ERROR_INVALID_ARGUMENT );
    }
}

psa_status_t psa_driver_wrapper_aead_encrypt_setup(
   psa_aead_operation_t *operation,
   const psa_key_attributes_t *attributes,
   const uint8_t *key_buffer, size_t key_buffer_size,
   psa_algorithm_t alg )
{
    psa_status_t status = PSA_ERROR_CORRUPTION_DETECTED;
    psa_key_location_t location =
        PSA_KEY_LIFETIME_GET_LOCATION( attributes->core.lifetime );

    switch( location )
    {
        case PSA_KEY_LOCATION_LOCAL_STORAGE:
#if defined(PSA_CRYPTO_DRIVER_TFM_BUILTIN_KEY_LOADER)                          //NXP TFM --- BEGIN ---
        case TFM_BUILTIN_KEY_LOADER_KEY_LOCATION:                              
#endif /* defined(PSA_CRYPTO_DRIVER_TFM_BUILTIN_KEY_LOADER) */                 //NXP TFM --- END ---
            /* Key is stored in the slot in export representation, so
             * cycle through all known transparent accelerators */

#if defined(PSA_CRYPTO_ACCELERATOR_DRIVER_PRESENT)
#if defined(PSA_CRYPTO_DRIVER_TEST)
            operation->id = MBEDTLS_TEST_TRANSPARENT_DRIVER_ID;
            status = mbedtls_test_transparent_aead_encrypt_setup(
                        &operation->ctx.transparent_test_driver_ctx,
                        attributes, key_buffer, key_buffer_size,
                        alg );

            /* Declared with fallback == true */
            if( status != PSA_ERROR_NOT_SUPPORTED )
                return( status );
#endif /* PSA_CRYPTO_DRIVER_TEST */
#if defined(PSA_CRYPTO_DRIVER_CC3XX)                              //NXP TFM --- BEGIN ---
            operation->id = PSA_CRYPTO_CC3XX_DRIVER_ID;
            status = cc3xx_aead_encrypt_setup(
                    &operation->ctx.cc3xx_driver_ctx,
                    attributes, key_buffer, key_buffer_size,
                    alg );

            return( status );
#endif /* PSA_CRYPTO_DRIVER_CC3XX */
#endif /* PSA_CRYPTO_ACCELERATOR_DRIVER_PRESENT */
#if !defined(PSA_CRYPTO_DRIVER_CC3XX)
            /* Fell through, meaning no accelerator supports this operation */
            operation->id = PSA_CRYPTO_MBED_TLS_DRIVER_ID;
            status = mbedtls_psa_aead_encrypt_setup(
                        &operation->ctx.mbedtls_ctx, attributes,
                        key_buffer, key_buffer_size,
                        alg );

            return( status );
#endif /* PSA_CRYPTO_DRIVER_CC3XX */                              //NXP TFM --- END ---
        /* Add cases for opaque driver here */

        default:
            /* Key is declared with a lifetime not known to us */
            (void)status;
            return( PSA_ERROR_INVALID_ARGUMENT );
    }
}

psa_status_t psa_driver_wrapper_aead_decrypt_setup(
   psa_aead_operation_t *operation,
   const psa_key_attributes_t *attributes,
   const uint8_t *key_buffer, size_t key_buffer_size,
   psa_algorithm_t alg )
{
    psa_status_t status = PSA_ERROR_CORRUPTION_DETECTED;
    psa_key_location_t location =
        PSA_KEY_LIFETIME_GET_LOCATION( attributes->core.lifetime );

    switch( location )
    {
        case PSA_KEY_LOCATION_LOCAL_STORAGE:
#if defined(PSA_CRYPTO_DRIVER_TFM_BUILTIN_KEY_LOADER)                          //NXP TFM --- BEGIN ---
        case TFM_BUILTIN_KEY_LOADER_KEY_LOCATION:                              
#endif /* defined(PSA_CRYPTO_DRIVER_TFM_BUILTIN_KEY_LOADER) */                 //NXP TFM --- END ---
            /* Key is stored in the slot in export representation, so
             * cycle through all known transparent accelerators */

#if defined(PSA_CRYPTO_ACCELERATOR_DRIVER_PRESENT)
#if defined(PSA_CRYPTO_DRIVER_TEST)
            operation->id = MBEDTLS_TEST_TRANSPARENT_DRIVER_ID;
            status = mbedtls_test_transparent_aead_decrypt_setup(
                        &operation->ctx.transparent_test_driver_ctx,
                        attributes,
                        key_buffer, key_buffer_size,
                        alg );

            /* Declared with fallback == true */
            if( status != PSA_ERROR_NOT_SUPPORTED )
                return( status );
#endif /* PSA_CRYPTO_DRIVER_TEST */
#if defined(PSA_CRYPTO_DRIVER_CC3XX)                        //NXP TFM --- BEGIN ---
            operation->id = PSA_CRYPTO_CC3XX_DRIVER_ID;
            status = cc3xx_aead_decrypt_setup(
                    &operation->ctx.cc3xx_driver_ctx,
                    attributes,
                    key_buffer, key_buffer_size,
                    alg );

            return( status );
#endif /* PSA_CRYPTO_DRIVER_CC3XX */
#endif /* PSA_CRYPTO_ACCELERATOR_DRIVER_PRESENT */
#if !defined(PSA_CRYPTO_DRIVER_CC3XX)
            /* Fell through, meaning no accelerator supports this operation */
            operation->id = PSA_CRYPTO_MBED_TLS_DRIVER_ID;
            status = mbedtls_psa_aead_decrypt_setup(
                        &operation->ctx.mbedtls_ctx,
                        attributes,
                        key_buffer, key_buffer_size,
                        alg );

            return( status );
#endif /* PSA_CRYPTO_DRIVER_CC3XX */                        //NXP TFM --- END ---
        /* Add cases for opaque driver here */

        default:
            /* Key is declared with a lifetime not known to us */
            (void)status;
            return( PSA_ERROR_INVALID_ARGUMENT );
    }
}

psa_status_t psa_driver_wrapper_aead_set_nonce(
   psa_aead_operation_t *operation,
   const uint8_t *nonce,
   size_t nonce_length )
{
    switch( operation->id )
    {
#if defined(MBEDTLS_PSA_BUILTIN_AEAD) && !defined(PSA_CRYPTO_DRIVER_CC3XX) //NXP TFM
        case PSA_CRYPTO_MBED_TLS_DRIVER_ID:
            return( mbedtls_psa_aead_set_nonce( &operation->ctx.mbedtls_ctx,
                                                nonce,
                                                nonce_length ) );

#endif

#if defined(PSA_CRYPTO_ACCELERATOR_DRIVER_PRESENT)
#if defined(PSA_CRYPTO_DRIVER_TEST)
        case MBEDTLS_TEST_TRANSPARENT_DRIVER_ID:
            return( mbedtls_test_transparent_aead_set_nonce(
                         &operation->ctx.transparent_test_driver_ctx,
                         nonce, nonce_length ) );

        /* Add cases for opaque driver here */

#endif /* PSA_CRYPTO_DRIVER_TEST */
#if defined(PSA_CRYPTO_DRIVER_CC3XX)                //NXP TFM --- BEGIN ---
        case PSA_CRYPTO_CC3XX_DRIVER_ID:
            return( cc3xx_aead_set_nonce(
                    &operation->ctx.cc3xx_driver_ctx,
                    nonce, nonce_length ) );

#endif /* PSA_CRYPTO_DRIVER_CC3XX */                //NXP TFM --- END ---
#endif /* PSA_CRYPTO_ACCELERATOR_DRIVER_PRESENT */
    }

    (void)nonce;
    (void)nonce_length;

    return( PSA_ERROR_INVALID_ARGUMENT );
}

psa_status_t psa_driver_wrapper_aead_set_lengths(
   psa_aead_operation_t *operation,
   size_t ad_length,
   size_t plaintext_length )
{
    switch( operation->id )
    {
#if defined(MBEDTLS_PSA_BUILTIN_AEAD) && !defined(PSA_CRYPTO_DRIVER_CC3XX)   //NXP TFM
        case PSA_CRYPTO_MBED_TLS_DRIVER_ID:
            return( mbedtls_psa_aead_set_lengths( &operation->ctx.mbedtls_ctx,
                                                  ad_length,
                                                  plaintext_length ) );

#endif

#if defined(PSA_CRYPTO_ACCELERATOR_DRIVER_PRESENT)
#if defined(PSA_CRYPTO_DRIVER_TEST)
        case MBEDTLS_TEST_TRANSPARENT_DRIVER_ID:
            return( mbedtls_test_transparent_aead_set_lengths(
                        &operation->ctx.transparent_test_driver_ctx,
                        ad_length, plaintext_length ) );

        /* Add cases for opaque driver here */

#endif /* PSA_CRYPTO_DRIVER_TEST */
#if defined(PSA_CRYPTO_DRIVER_CC3XX)                          //NXP TFM --- BEGIN ---
        case PSA_CRYPTO_CC3XX_DRIVER_ID:
            return( cc3xx_aead_set_lengths(
                    &operation->ctx.cc3xx_driver_ctx,
                    ad_length, plaintext_length ) );

#endif /* PSA_CRYPTO_DRIVER_CC3XX */                          //NXP TFM --- END ---
#endif /* PSA_CRYPTO_ACCELERATOR_DRIVER_PRESENT */
    }

    (void)ad_length;
    (void)plaintext_length;

    return( PSA_ERROR_INVALID_ARGUMENT );
}

psa_status_t psa_driver_wrapper_aead_update_ad(
   psa_aead_operation_t *operation,
   const uint8_t *input,
   size_t input_length )
{
    switch( operation->id )
    {
#if defined(MBEDTLS_PSA_BUILTIN_AEAD) && !defined(PSA_CRYPTO_DRIVER_CC3XX) //NXP TFM
        case PSA_CRYPTO_MBED_TLS_DRIVER_ID:
            return( mbedtls_psa_aead_update_ad( &operation->ctx.mbedtls_ctx,
                                                input,
                                                input_length ) );

#endif

#if defined(PSA_CRYPTO_ACCELERATOR_DRIVER_PRESENT)
#if defined(PSA_CRYPTO_DRIVER_TEST)
        case MBEDTLS_TEST_TRANSPARENT_DRIVER_ID:
            return( mbedtls_test_transparent_aead_update_ad(
                        &operation->ctx.transparent_test_driver_ctx,
                        input, input_length ) );

        /* Add cases for opaque driver here */

#endif /* PSA_CRYPTO_DRIVER_TEST */
#if defined(PSA_CRYPTO_DRIVER_CC3XX)                       //NXP TFM --- BEGIN ---
        case PSA_CRYPTO_CC3XX_DRIVER_ID:
            return( cc3xx_aead_update_ad(
                    &operation->ctx.cc3xx_driver_ctx,
                    input, input_length ) );

#endif /* PSA_CRYPTO_DRIVER_CC3XX */                       //NXP TFM --- END ---
#endif /* PSA_CRYPTO_ACCELERATOR_DRIVER_PRESENT */
    }

    (void)input;
    (void)input_length;

    return( PSA_ERROR_INVALID_ARGUMENT );
}

psa_status_t psa_driver_wrapper_aead_update(
   psa_aead_operation_t *operation,
   const uint8_t *input,
   size_t input_length,
   uint8_t *output,
   size_t output_size,
   size_t *output_length )
{
    switch( operation->id )
    {
#if defined(MBEDTLS_PSA_BUILTIN_AEAD) && !defined(PSA_CRYPTO_DRIVER_CC3XX) //NXP TFM
        case PSA_CRYPTO_MBED_TLS_DRIVER_ID:
            return( mbedtls_psa_aead_update( &operation->ctx.mbedtls_ctx,
                                             input, input_length,
                                             output, output_size,
                                             output_length ) );

#endif

#if defined(PSA_CRYPTO_ACCELERATOR_DRIVER_PRESENT)
#if defined(PSA_CRYPTO_DRIVER_TEST)
        case MBEDTLS_TEST_TRANSPARENT_DRIVER_ID:
            return( mbedtls_test_transparent_aead_update(
                        &operation->ctx.transparent_test_driver_ctx,
                        input, input_length, output, output_size,
                        output_length ) );

        /* Add cases for opaque driver here */

#endif /* PSA_CRYPTO_DRIVER_TEST */
#if defined(PSA_CRYPTO_DRIVER_CC3XX)                       //NXP TFM --- BEGIN ---
        case PSA_CRYPTO_CC3XX_DRIVER_ID:
            return( cc3xx_aead_update(
                    &operation->ctx.cc3xx_driver_ctx,
                    input, input_length, output, output_size,
                    output_length ) );

#endif /* PSA_CRYPTO_DRIVER_CC3XX */                      //NXP TFM --- END ---
#endif /* PSA_CRYPTO_ACCELERATOR_DRIVER_PRESENT */
    }

    (void)input;
    (void)input_length;
    (void)output;
    (void)output_size;
    (void)output_length;

    return( PSA_ERROR_INVALID_ARGUMENT );
}

psa_status_t psa_driver_wrapper_aead_finish(
   psa_aead_operation_t *operation,
   uint8_t *ciphertext,
   size_t ciphertext_size,
   size_t *ciphertext_length,
   uint8_t *tag,
   size_t tag_size,
   size_t *tag_length )
{
    switch( operation->id )
    {
#if defined(MBEDTLS_PSA_BUILTIN_AEAD) && !defined(PSA_CRYPTO_DRIVER_CC3XX) //NXP TFM
        case PSA_CRYPTO_MBED_TLS_DRIVER_ID:
            return( mbedtls_psa_aead_finish( &operation->ctx.mbedtls_ctx,
                                             ciphertext,
                                             ciphertext_size,
                                             ciphertext_length, tag,
                                             tag_size, tag_length ) );

#endif

#if defined(PSA_CRYPTO_ACCELERATOR_DRIVER_PRESENT)
#if defined(PSA_CRYPTO_DRIVER_TEST)
        case MBEDTLS_TEST_TRANSPARENT_DRIVER_ID:
            return( mbedtls_test_transparent_aead_finish(
                        &operation->ctx.transparent_test_driver_ctx,
                        ciphertext, ciphertext_size,
                        ciphertext_length, tag, tag_size, tag_length ) );

        /* Add cases for opaque driver here */

#endif /* PSA_CRYPTO_DRIVER_TEST */
#if defined(PSA_CRYPTO_DRIVER_CC3XX)                       //NXP TFM --- BEGIN ---
        case PSA_CRYPTO_CC3XX_DRIVER_ID:
            return( cc3xx_aead_finish(
                    &operation->ctx.cc3xx_driver_ctx,
                    ciphertext, ciphertext_size,
                    ciphertext_length, tag, tag_size, tag_length ) );

#endif /* PSA_CRYPTO_DRIVER_CC3XX */                       //NXP TFM --- END ---
#endif /* PSA_CRYPTO_ACCELERATOR_DRIVER_PRESENT */
    }

    (void)ciphertext;
    (void)ciphertext_size;
    (void)ciphertext_length;
    (void)tag;
    (void)tag_size;
    (void)tag_length;

    return( PSA_ERROR_INVALID_ARGUMENT );
}

psa_status_t psa_driver_wrapper_aead_verify(
   psa_aead_operation_t *operation,
   uint8_t *plaintext,
   size_t plaintext_size,
   size_t *plaintext_length,
   const uint8_t *tag,
   size_t tag_length )
{
    switch( operation->id )
    {
#if defined(MBEDTLS_PSA_BUILTIN_AEAD) && !defined(PSA_CRYPTO_DRIVER_CC3XX)   //NXP TFM
        case PSA_CRYPTO_MBED_TLS_DRIVER_ID:
            {
                psa_status_t status = PSA_ERROR_CORRUPTION_DETECTED;
                uint8_t check_tag[PSA_AEAD_TAG_MAX_SIZE];
                size_t check_tag_length;

                status = mbedtls_psa_aead_finish( &operation->ctx.mbedtls_ctx,
                                                  plaintext,
                                                  plaintext_size,
                                                  plaintext_length,
                                                  check_tag,
                                                  sizeof( check_tag ),
                                                  &check_tag_length );

                if( status == PSA_SUCCESS )
                {
                    if( tag_length != check_tag_length ||
                        mbedtls_psa_safer_memcmp( tag, check_tag, tag_length )
                        != 0 )
                        status = PSA_ERROR_INVALID_SIGNATURE;
                }

                mbedtls_platform_zeroize( check_tag, sizeof( check_tag ) );

                return( status );
            }

#endif /* MBEDTLS_PSA_BUILTIN_AEAD */

#if defined(PSA_CRYPTO_ACCELERATOR_DRIVER_PRESENT)
#if defined(PSA_CRYPTO_DRIVER_TEST)
        case MBEDTLS_TEST_TRANSPARENT_DRIVER_ID:
            return( mbedtls_test_transparent_aead_verify(
                        &operation->ctx.transparent_test_driver_ctx,
                        plaintext, plaintext_size,
                        plaintext_length, tag, tag_length ) );

        /* Add cases for opaque driver here */

#endif /* PSA_CRYPTO_DRIVER_TEST */
#if defined(PSA_CRYPTO_DRIVER_CC3XX)              //NXP TFM --- BEGIN ---
        case PSA_CRYPTO_CC3XX_DRIVER_ID:
            return( cc3xx_aead_verify(
                    &operation->ctx.cc3xx_driver_ctx,
                    plaintext, plaintext_size,
                    plaintext_length, tag, tag_length ) );

#endif /* PSA_CRYPTO_DRIVER_CC3XX */             //NXP TFM --- END ---
#endif /* PSA_CRYPTO_ACCELERATOR_DRIVER_PRESENT */
    }

    (void)plaintext;
    (void)plaintext_size;
    (void)plaintext_length;
    (void)tag;
    (void)tag_length;

    return( PSA_ERROR_INVALID_ARGUMENT );
}

psa_status_t psa_driver_wrapper_aead_abort(
   psa_aead_operation_t *operation )
{
    switch( operation->id )
    {
#if defined(MBEDTLS_PSA_BUILTIN_AEAD) && !defined(PSA_CRYPTO_DRIVER_CC3XX)     //NXP TFM
        case PSA_CRYPTO_MBED_TLS_DRIVER_ID:
            return( mbedtls_psa_aead_abort( &operation->ctx.mbedtls_ctx ) );

#endif /* MBEDTLS_PSA_BUILTIN_AEAD */

#if defined(PSA_CRYPTO_ACCELERATOR_DRIVER_PRESENT)
#if defined(PSA_CRYPTO_DRIVER_TEST)
        case MBEDTLS_TEST_TRANSPARENT_DRIVER_ID:
            return( mbedtls_test_transparent_aead_abort(
               &operation->ctx.transparent_test_driver_ctx ) );

        /* Add cases for opaque driver here */

#endif /* PSA_CRYPTO_DRIVER_TEST */
#if defined(PSA_CRYPTO_DRIVER_CC3XX)               //NXP TFM --- BEGIN ---
    case PSA_CRYPTO_CC3XX_DRIVER_ID:
        return( cc3xx_aead_abort(
                &operation->ctx.cc3xx_driver_ctx ) );

#endif /* PSA_CRYPTO_DRIVER_CC3XX */              //NXP TFM
#endif /* PSA_CRYPTO_ACCELERATOR_DRIVER_PRESENT */
    }

    return( PSA_ERROR_INVALID_ARGUMENT );
}

/*
 * MAC functions
 */
psa_status_t psa_driver_wrapper_mac_compute(
    const psa_key_attributes_t *attributes,
    const uint8_t *key_buffer,
    size_t key_buffer_size,
    psa_algorithm_t alg,
    const uint8_t *input,
    size_t input_length,
    uint8_t *mac,
    size_t mac_size,
    size_t *mac_length )
{
    psa_status_t status = PSA_ERROR_CORRUPTION_DETECTED;
    psa_key_location_t location =
        PSA_KEY_LIFETIME_GET_LOCATION( attributes->core.lifetime );

    switch( location )
    {
        case PSA_KEY_LOCATION_LOCAL_STORAGE:
#if defined(PSA_CRYPTO_DRIVER_TFM_BUILTIN_KEY_LOADER)              //NXP TFM --- BEGIN ---
        case TFM_BUILTIN_KEY_LOADER_KEY_LOCATION:
#endif /* defined(PSA_CRYPTO_DRIVER_TFM_BUILTIN_KEY_LOADER) */     //NXP TFM --- END ---
            /* Key is stored in the slot in export representation, so
             * cycle through all known transparent accelerators */
#if defined(PSA_CRYPTO_ACCELERATOR_DRIVER_PRESENT)
#if defined(PSA_CRYPTO_DRIVER_TEST)
            status = mbedtls_test_transparent_mac_compute(
                attributes, key_buffer, key_buffer_size, alg,
                input, input_length,
                mac, mac_size, mac_length );
            /* Declared with fallback == true */
            if( status != PSA_ERROR_NOT_SUPPORTED )
                return( status );
#endif /* PSA_CRYPTO_DRIVER_TEST */
#if defined(PSA_CRYPTO_DRIVER_CC3XX)                                  //NXP TFM --- BEGIN ---
            status = cc3xx_mac_compute(attributes, key_buffer, key_buffer_size, alg,
                input, input_length,
                mac, mac_size, mac_length);
            return( status );
#endif /* PSA_CRYPTO_DRIVER_CC3XX */                                 //NXP TFM --- END ---
#endif /* PSA_CRYPTO_ACCELERATOR_DRIVER_PRESENT */
#if defined(MBEDTLS_PSA_BUILTIN_MAC) && !defined(PSA_CRYPTO_DRIVER_CC3XX)   //NXP TFM
            /* Fell through, meaning no accelerator supports this operation */
            status = mbedtls_psa_mac_compute(
                attributes, key_buffer, key_buffer_size, alg,
                input, input_length,
                mac, mac_size, mac_length );
            if( status != PSA_ERROR_NOT_SUPPORTED )
                return( status );
#endif /* MBEDTLS_PSA_BUILTIN_MAC */
            return( PSA_ERROR_NOT_SUPPORTED );

        /* Add cases for opaque driver here */
#if defined(PSA_CRYPTO_ACCELERATOR_DRIVER_PRESENT)
#if defined(PSA_CRYPTO_DRIVER_TEST)
        case PSA_CRYPTO_TEST_DRIVER_LOCATION:
            status = mbedtls_test_opaque_mac_compute(
                attributes, key_buffer, key_buffer_size, alg,
                input, input_length,
                mac, mac_size, mac_length );
            return( status );
#endif /* PSA_CRYPTO_DRIVER_TEST */
#endif /* PSA_CRYPTO_ACCELERATOR_DRIVER_PRESENT */
        default:
            /* Key is declared with a lifetime not known to us */
            (void) key_buffer;
            (void) key_buffer_size;
            (void) alg;
            (void) input;
            (void) input_length;
            (void) mac;
            (void) mac_size;
            (void) mac_length;
            (void) status;
            return( PSA_ERROR_INVALID_ARGUMENT );
    }
}

psa_status_t psa_driver_wrapper_mac_sign_setup(
    psa_mac_operation_t *operation,
    const psa_key_attributes_t *attributes,
    const uint8_t *key_buffer,
    size_t key_buffer_size,
    psa_algorithm_t alg )
{
    psa_status_t status = PSA_ERROR_CORRUPTION_DETECTED;
    psa_key_location_t location =
        PSA_KEY_LIFETIME_GET_LOCATION( attributes->core.lifetime );

    switch( location )
    {
        case PSA_KEY_LOCATION_LOCAL_STORAGE:
#if defined(PSA_CRYPTO_DRIVER_TFM_BUILTIN_KEY_LOADER)              //NXP TFM --- BEGIN ---
        case TFM_BUILTIN_KEY_LOADER_KEY_LOCATION:
#endif /* defined(PSA_CRYPTO_DRIVER_TFM_BUILTIN_KEY_LOADER) */     //NXP TFM --- END ---
            /* Key is stored in the slot in export representation, so
             * cycle through all known transparent accelerators */
#if defined(PSA_CRYPTO_ACCELERATOR_DRIVER_PRESENT)
#if defined(PSA_CRYPTO_DRIVER_TEST)
            status = mbedtls_test_transparent_mac_sign_setup(
                &operation->ctx.transparent_test_driver_ctx,
                attributes,
                key_buffer, key_buffer_size,
                alg );
            /* Declared with fallback == true */
            if( status == PSA_SUCCESS )
                operation->id = MBEDTLS_TEST_TRANSPARENT_DRIVER_ID;

            if( status != PSA_ERROR_NOT_SUPPORTED )
                return( status );
#endif /* PSA_CRYPTO_DRIVER_TEST */
#if defined(PSA_CRYPTO_DRIVER_CC3XX)                         //NXP TFM --- BEGIN ---
            status = cc3xx_mac_sign_setup(
                    &operation->ctx.cc3xx_driver_ctx,
                    attributes,
                    key_buffer, key_buffer_size,
                    alg);
            operation->id = PSA_CRYPTO_CC3XX_DRIVER_ID;
            return status;
#endif /* defined(PSA_CRYPTO_DRIVER_CC3XX) */                //NXP TFM --- END ---
#endif /* PSA_CRYPTO_ACCELERATOR_DRIVER_PRESENT */
#if defined(MBEDTLS_PSA_BUILTIN_MAC) && !defined(PSA_CRYPTO_DRIVER_CC3XX) //NXP TFM
            /* Fell through, meaning no accelerator supports this operation */
            status = mbedtls_psa_mac_sign_setup( &operation->ctx.mbedtls_ctx,
                                                 attributes,
                                                 key_buffer, key_buffer_size,
                                                 alg );
            if( status == PSA_SUCCESS )
                operation->id = PSA_CRYPTO_MBED_TLS_DRIVER_ID;

            if( status != PSA_ERROR_NOT_SUPPORTED )
                return( status );
#endif /* MBEDTLS_PSA_BUILTIN_MAC */
            return( PSA_ERROR_NOT_SUPPORTED );

        /* Add cases for opaque driver here */
#if defined(PSA_CRYPTO_ACCELERATOR_DRIVER_PRESENT)
#if defined(PSA_CRYPTO_DRIVER_TEST)
        case PSA_CRYPTO_TEST_DRIVER_LOCATION:
            status = mbedtls_test_opaque_mac_sign_setup(
                &operation->ctx.opaque_test_driver_ctx,
                attributes,
                key_buffer, key_buffer_size,
                alg );

            if( status == PSA_SUCCESS )
                operation->id = MBEDTLS_TEST_OPAQUE_DRIVER_ID;

            return( status );
#endif /* PSA_CRYPTO_DRIVER_TEST */
#endif /* PSA_CRYPTO_ACCELERATOR_DRIVER_PRESENT */
        default:
            /* Key is declared with a lifetime not known to us */
            (void) status;
            (void) operation;
            (void) key_buffer;
            (void) key_buffer_size;
            (void) alg;
            return( PSA_ERROR_INVALID_ARGUMENT );
    }
}

psa_status_t psa_driver_wrapper_mac_verify_setup(
    psa_mac_operation_t *operation,
    const psa_key_attributes_t *attributes,
    const uint8_t *key_buffer,
    size_t key_buffer_size,
    psa_algorithm_t alg )
{
    psa_status_t status = PSA_ERROR_CORRUPTION_DETECTED;
    psa_key_location_t location =
        PSA_KEY_LIFETIME_GET_LOCATION( attributes->core.lifetime );

    switch( location )
    {
        case PSA_KEY_LOCATION_LOCAL_STORAGE:
#if defined(PSA_CRYPTO_DRIVER_TFM_BUILTIN_KEY_LOADER)                   //NXP TFM --- BEGIN ---
        case TFM_BUILTIN_KEY_LOADER_KEY_LOCATION:
#endif /* defined(PSA_CRYPTO_DRIVER_TFM_BUILTIN_KEY_LOADER) */          //NXP TFM --- END ---
            /* Key is stored in the slot in export representation, so
             * cycle through all known transparent accelerators */
#if defined(PSA_CRYPTO_ACCELERATOR_DRIVER_PRESENT)
#if defined(PSA_CRYPTO_DRIVER_TEST)
            status = mbedtls_test_transparent_mac_verify_setup(
                &operation->ctx.transparent_test_driver_ctx,
                attributes,
                key_buffer, key_buffer_size,
                alg );
            /* Declared with fallback == true */
            if( status == PSA_SUCCESS )
                operation->id = MBEDTLS_TEST_TRANSPARENT_DRIVER_ID;

            if( status != PSA_ERROR_NOT_SUPPORTED )
                return( status );
#endif /* PSA_CRYPTO_DRIVER_TEST */
#if defined(PSA_CRYPTO_DRIVER_CC3XX)                      //NXP TFM --- BEGIN ---
            status = cc3xx_mac_verify_setup(
                &operation->ctx.cc3xx_driver_ctx,
                attributes,
                key_buffer, key_buffer_size,
                alg);
            operation->id = PSA_CRYPTO_CC3XX_DRIVER_ID;
            return status;
#endif /* defined(PSA_CRYPTO_DRIVER_CC3XX) */             //NXP TFM --- END ---
#endif /* PSA_CRYPTO_ACCELERATOR_DRIVER_PRESENT */
#if defined(MBEDTLS_PSA_BUILTIN_MAC) && !defined(PSA_CRYPTO_DRIVER_CC3XX)   //NXP TFM
            /* Fell through, meaning no accelerator supports this operation */
            status = mbedtls_psa_mac_verify_setup( &operation->ctx.mbedtls_ctx,
                                                   attributes,
                                                   key_buffer, key_buffer_size,
                                                   alg );
            if( status == PSA_SUCCESS )
                operation->id = PSA_CRYPTO_MBED_TLS_DRIVER_ID;

            if( status != PSA_ERROR_NOT_SUPPORTED )
                return( status );
#endif /* MBEDTLS_PSA_BUILTIN_MAC */
            return( PSA_ERROR_NOT_SUPPORTED );

        /* Add cases for opaque driver here */
#if defined(PSA_CRYPTO_ACCELERATOR_DRIVER_PRESENT)
#if defined(PSA_CRYPTO_DRIVER_TEST)
        case PSA_CRYPTO_TEST_DRIVER_LOCATION:
            status = mbedtls_test_opaque_mac_verify_setup(
                &operation->ctx.opaque_test_driver_ctx,
                attributes,
                key_buffer, key_buffer_size,
                alg );

            if( status == PSA_SUCCESS )
                operation->id = MBEDTLS_TEST_OPAQUE_DRIVER_ID;

            return( status );
#endif /* PSA_CRYPTO_DRIVER_TEST */
#endif /* PSA_CRYPTO_ACCELERATOR_DRIVER_PRESENT */
        default:
            /* Key is declared with a lifetime not known to us */
            (void) status;
            (void) operation;
            (void) key_buffer;
            (void) key_buffer_size;
            (void) alg;
            return( PSA_ERROR_INVALID_ARGUMENT );
    }
}

psa_status_t psa_driver_wrapper_mac_update(
    psa_mac_operation_t *operation,
    const uint8_t *input,
    size_t input_length )
{
    switch( operation->id )
    {
#if defined(MBEDTLS_PSA_BUILTIN_MAC) && !defined(PSA_CRYPTO_DRIVER_CC3XX)    //NXP TFM
        case PSA_CRYPTO_MBED_TLS_DRIVER_ID:
            return( mbedtls_psa_mac_update( &operation->ctx.mbedtls_ctx,
                                            input, input_length ) );
#endif

#if defined(PSA_CRYPTO_ACCELERATOR_DRIVER_PRESENT)
#if defined(PSA_CRYPTO_DRIVER_TEST)
        case MBEDTLS_TEST_TRANSPARENT_DRIVER_ID:
            return( mbedtls_test_transparent_mac_update(
                        &operation->ctx.transparent_test_driver_ctx,
                        input, input_length ) );

        case MBEDTLS_TEST_OPAQUE_DRIVER_ID:
            return( mbedtls_test_opaque_mac_update(
                        &operation->ctx.opaque_test_driver_ctx,
                        input, input_length ) );
#endif /* PSA_CRYPTO_DRIVER_TEST */
#if defined(PSA_CRYPTO_DRIVER_CC3XX)                //NXP TFM --- BEGIN ---
        case PSA_CRYPTO_CC3XX_DRIVER_ID:
            return(cc3xx_mac_update(&operation->ctx.cc3xx_driver_ctx, input, input_length));
#endif /* defined(PSA_CRYPTO_DRIVER_CC3XX) */       //NXP TFM --- END ---
#endif /* PSA_CRYPTO_ACCELERATOR_DRIVER_PRESENT */
        default:
            (void) input;
            (void) input_length;
            return( PSA_ERROR_INVALID_ARGUMENT );
    }
}

psa_status_t psa_driver_wrapper_mac_sign_finish(
    psa_mac_operation_t *operation,
    uint8_t *mac,
    size_t mac_size,
    size_t *mac_length )
{
    switch( operation->id )
    {
#if defined(MBEDTLS_PSA_BUILTIN_MAC) && !defined(PSA_CRYPTO_DRIVER_CC3XX)  //NXP TFM
        case PSA_CRYPTO_MBED_TLS_DRIVER_ID:
            return( mbedtls_psa_mac_sign_finish( &operation->ctx.mbedtls_ctx,
                                                 mac, mac_size, mac_length ) );
#endif

#if defined(PSA_CRYPTO_ACCELERATOR_DRIVER_PRESENT)
#if defined(PSA_CRYPTO_DRIVER_TEST)
        case MBEDTLS_TEST_TRANSPARENT_DRIVER_ID:
            return( mbedtls_test_transparent_mac_sign_finish(
                        &operation->ctx.transparent_test_driver_ctx,
                        mac, mac_size, mac_length ) );

        case MBEDTLS_TEST_OPAQUE_DRIVER_ID:
            return( mbedtls_test_opaque_mac_sign_finish(
                        &operation->ctx.opaque_test_driver_ctx,
                        mac, mac_size, mac_length ) );
#endif /* PSA_CRYPTO_DRIVER_TEST */
#if defined(PSA_CRYPTO_DRIVER_CC3XX)            //NXP TFM --- BEGIN ---
        case PSA_CRYPTO_CC3XX_DRIVER_ID:
            return(cc3xx_mac_sign_finish(&operation->ctx.cc3xx_driver_ctx,
                        mac, mac_size, mac_length));
#endif /* defined(PSA_CRYPTO_DRIVER_CC3XX) */   //NXP TFM --- END ---
#endif /* PSA_CRYPTO_ACCELERATOR_DRIVER_PRESENT */
        default:
            (void) mac;
            (void) mac_size;
            (void) mac_length;
            return( PSA_ERROR_INVALID_ARGUMENT );
    }
}

psa_status_t psa_driver_wrapper_mac_verify_finish(
    psa_mac_operation_t *operation,
    const uint8_t *mac,
    size_t mac_length )
{
    switch( operation->id )
    {
#if defined(MBEDTLS_PSA_BUILTIN_MAC) && !defined(PSA_CRYPTO_DRIVER_CC3XX)    //NXP TFM
        case PSA_CRYPTO_MBED_TLS_DRIVER_ID:
            return( mbedtls_psa_mac_verify_finish( &operation->ctx.mbedtls_ctx,
                                                   mac, mac_length ) );
#endif

#if defined(PSA_CRYPTO_ACCELERATOR_DRIVER_PRESENT)
#if defined(PSA_CRYPTO_DRIVER_TEST)
        case MBEDTLS_TEST_TRANSPARENT_DRIVER_ID:
            return( mbedtls_test_transparent_mac_verify_finish(
                        &operation->ctx.transparent_test_driver_ctx,
                        mac, mac_length ) );

        case MBEDTLS_TEST_OPAQUE_DRIVER_ID:
            return( mbedtls_test_opaque_mac_verify_finish(
                        &operation->ctx.opaque_test_driver_ctx,
                        mac, mac_length ) );
#endif /* PSA_CRYPTO_DRIVER_TEST */
#if defined(PSA_CRYPTO_DRIVER_CC3XX)                    //NXP TFM --- BEGIN ---
        case PSA_CRYPTO_CC3XX_DRIVER_ID:
            return(cc3xx_mac_verify_finish(
                        &operation->ctx.cc3xx_driver_ctx,
                        mac, mac_length));
#endif /* defined(PSA_CRYPTO_DRIVER_CC3XX) */           //NXP TFM --- END ---
#endif /* PSA_CRYPTO_ACCELERATOR_DRIVER_PRESENT */
        default:
            (void) mac;
            (void) mac_length;
            return( PSA_ERROR_INVALID_ARGUMENT );
    }
}

psa_status_t psa_driver_wrapper_mac_abort(
    psa_mac_operation_t *operation )
{
    switch( operation->id )
    {
#if defined(MBEDTLS_PSA_BUILTIN_MAC) && !defined(PSA_CRYPTO_DRIVER_CC3XX) //NXP TFM
        case PSA_CRYPTO_MBED_TLS_DRIVER_ID:
            return( mbedtls_psa_mac_abort( &operation->ctx.mbedtls_ctx ) );
#endif

#if defined(PSA_CRYPTO_ACCELERATOR_DRIVER_PRESENT)
#if defined(PSA_CRYPTO_DRIVER_TEST)
        case MBEDTLS_TEST_TRANSPARENT_DRIVER_ID:
            return( mbedtls_test_transparent_mac_abort(
                        &operation->ctx.transparent_test_driver_ctx ) );
        case MBEDTLS_TEST_OPAQUE_DRIVER_ID:
            return( mbedtls_test_opaque_mac_abort(
                        &operation->ctx.opaque_test_driver_ctx ) );
#endif /* PSA_CRYPTO_DRIVER_TEST */
#if defined(PSA_CRYPTO_DRIVER_CC3XX)                 //NXP TFM --- BEGIN ---
        case PSA_CRYPTO_CC3XX_DRIVER_ID:
            return(cc3xx_mac_abort(&operation->ctx.cc3xx_driver_ctx));
#endif /* defined(PSA_CRYPTO_DRIVER_CC3XX) */        //NXP TFM --- END ---
#endif /* PSA_CRYPTO_ACCELERATOR_DRIVER_PRESENT */
        default:
            return( PSA_ERROR_INVALID_ARGUMENT );
    }
}

/*
 * Asymmetric cryptography
 */
psa_status_t psa_driver_wrapper_asymmetric_encrypt(
    const psa_key_attributes_t *attributes, const uint8_t *key_buffer,
    size_t key_buffer_size, psa_algorithm_t alg, const uint8_t *input,
    size_t input_length, const uint8_t *salt, size_t salt_length,
    uint8_t *output, size_t output_size, size_t *output_length )
{
    psa_status_t status = PSA_ERROR_CORRUPTION_DETECTED;
    psa_key_location_t location =
        PSA_KEY_LIFETIME_GET_LOCATION( attributes->core.lifetime );

    switch( location )
    {
        case PSA_KEY_LOCATION_LOCAL_STORAGE:
#if defined(PSA_CRYPTO_DRIVER_TFM_BUILTIN_KEY_LOADER)             //NXP TFM
        case TFM_BUILTIN_KEY_LOADER_KEY_LOCATION:
#endif /* defined(PSA_CRYPTO_DRIVER_TFM_BUILTIN_KEY_LOADER) */
            /* Key is stored in the slot in export representation, so
             * cycle through all known transparent accelerators */
#if defined(PSA_CRYPTO_ACCELERATOR_DRIVER_PRESENT)
#if defined(PSA_CRYPTO_DRIVER_CC3XX)                              //NXP TFM --- BEGIN ---
            status = cc3xx_asymmetric_encrypt( attributes,
                                               key_buffer,
                                               key_buffer_size,
                                               alg,
                                               input,
                                               input_length,
                                               salt,
                                               salt_length,
                                               output,
                                               output_size,
                                               output_length );
            return( status );
#endif  /* PSA_CRYPTO_DRIVER_CC3XX */                            //NXP TFM --- END ---
#if defined(PSA_CRYPTO_DRIVER_TEST)
            status = mbedtls_test_transparent_asymmetric_encrypt( attributes,
                        key_buffer, key_buffer_size, alg, input, input_length,
                        salt, salt_length, output, output_size,
                        output_length );
            /* Declared with fallback == true */
            if( status != PSA_ERROR_NOT_SUPPORTED )
                return( status );
#endif /* PSA_CRYPTO_DRIVER_TEST */
#endif /* PSA_CRYPTO_ACCELERATOR_DRIVER_PRESENT */
#if !defined(PSA_CRYPTO_DRIVER_CC3XX)                       //NXP TFM
            return( mbedtls_psa_asymmetric_encrypt( attributes,
                        key_buffer, key_buffer_size, alg, input, input_length,
                        salt, salt_length, output, output_size, output_length )
                  );
#endif /* PSA_CRYPTO_DRIVER_CC3XX */
        /* Add cases for opaque driver here */
#if defined(PSA_CRYPTO_ACCELERATOR_DRIVER_PRESENT)
#if defined(PSA_CRYPTO_DRIVER_TEST)
        case PSA_CRYPTO_TEST_DRIVER_LOCATION:
            return( mbedtls_test_opaque_asymmetric_encrypt( attributes,
                        key_buffer, key_buffer_size, alg, input, input_length,
                        salt, salt_length, output, output_size, output_length )
                  );
#endif /* PSA_CRYPTO_DRIVER_TEST */
#endif /* PSA_CRYPTO_ACCELERATOR_DRIVER_PRESENT */

        default:
            /* Key is declared with a lifetime not known to us */
            (void)status;
            (void)key_buffer;
            (void)key_buffer_size;
            (void)alg;
            (void)input;
            (void)input_length;
            (void)salt;
            (void)salt_length;
            (void)output;
            (void)output_size;
            (void)output_length;
            return( PSA_ERROR_INVALID_ARGUMENT );
    }
}

psa_status_t psa_driver_wrapper_asymmetric_decrypt(
    const psa_key_attributes_t *attributes, const uint8_t *key_buffer,
    size_t key_buffer_size, psa_algorithm_t alg, const uint8_t *input,
    size_t input_length, const uint8_t *salt, size_t salt_length,
    uint8_t *output, size_t output_size, size_t *output_length )
{
    psa_status_t status = PSA_ERROR_CORRUPTION_DETECTED;
    psa_key_location_t location =
        PSA_KEY_LIFETIME_GET_LOCATION( attributes->core.lifetime );

    switch( location )
    {
        case PSA_KEY_LOCATION_LOCAL_STORAGE:
#if defined(PSA_CRYPTO_DRIVER_TFM_BUILTIN_KEY_LOADER)            //NXP TFM --- BEGIN ---
        case TFM_BUILTIN_KEY_LOADER_KEY_LOCATION:
#endif /* defined(PSA_CRYPTO_DRIVER_TFM_BUILTIN_KEY_LOADER) */   //NXP TFM --- END ---
            /* Key is stored in the slot in export representation, so
             * cycle through all known transparent accelerators */
#if defined(PSA_CRYPTO_ACCELERATOR_DRIVER_PRESENT)
#if defined(PSA_CRYPTO_DRIVER_CC3XX)                             //NXP TFM --- BEGIN ---
            status = cc3xx_asymmetric_decrypt( attributes,
                                               key_buffer,
                                               key_buffer_size,
                                               alg,
                                               input,
                                               input_length,
                                               salt,
                                               salt_length,
                                               output,
                                               output_size,
                                               output_length );
            return( status );
#endif /* PSA_CRYPTO_DRIVER_CC3XX */                             //NXP TFM --- END ---
#if defined(PSA_CRYPTO_DRIVER_TEST)
            status = mbedtls_test_transparent_asymmetric_decrypt( attributes,
                        key_buffer, key_buffer_size, alg, input, input_length,
                        salt, salt_length, output, output_size,
                        output_length );
            /* Declared with fallback == true */
            if( status != PSA_ERROR_NOT_SUPPORTED )
                return( status );
#endif /* PSA_CRYPTO_DRIVER_TEST */
#endif /* PSA_CRYPTO_ACCELERATOR_DRIVER_PRESENT */
#if !defined(PSA_CRYPTO_DRIVER_CC3XX)                            //NXP TFM
            return( mbedtls_psa_asymmetric_decrypt( attributes,
                        key_buffer, key_buffer_size, alg,input, input_length,
                        salt, salt_length, output, output_size,
                        output_length ) );
#endif /* PSA_CRYPTO_DRIVER_CC3XX */
        /* Add cases for opaque driver here */
#if defined(PSA_CRYPTO_ACCELERATOR_DRIVER_PRESENT)
#if defined(PSA_CRYPTO_DRIVER_TEST)
        case PSA_CRYPTO_TEST_DRIVER_LOCATION:
            return( mbedtls_test_opaque_asymmetric_decrypt( attributes,
                        key_buffer, key_buffer_size, alg, input, input_length,
                        salt, salt_length, output, output_size,
                        output_length ) );
#endif /* PSA_CRYPTO_DRIVER_TEST */
#endif /* PSA_CRYPTO_ACCELERATOR_DRIVER_PRESENT */

        default:
            /* Key is declared with a lifetime not known to us */
            (void)status;
            (void)key_buffer;
            (void)key_buffer_size;
            (void)alg;
            (void)input;
            (void)input_length;
            (void)salt;
            (void)salt_length;
            (void)output;
            (void)output_size;
            (void)output_length;
            return( PSA_ERROR_INVALID_ARGUMENT );
    }
}

psa_status_t psa_driver_wrapper_key_agreement(
    const psa_key_attributes_t *attributes,
    const uint8_t *key_buffer,
    size_t key_buffer_size,
    psa_algorithm_t alg,
    const uint8_t *peer_key,
    size_t peer_key_length,
    uint8_t *shared_secret,
    size_t shared_secret_size,
    size_t *shared_secret_length
 )
 {
    psa_status_t status = PSA_ERROR_CORRUPTION_DETECTED;
    psa_key_location_t location =
        PSA_KEY_LIFETIME_GET_LOCATION( attributes->core.lifetime );

    switch( location )
    {
        case PSA_KEY_LOCATION_LOCAL_STORAGE:
            /* Key is stored in the slot in export representation, so
             * cycle through all known transparent accelerators */
#if defined(PSA_CRYPTO_ACCELERATOR_DRIVER_PRESENT)
#if defined(PSA_CRYPTO_DRIVER_TEST)
            status =
                mbedtls_test_transparent_key_agreement( attributes,
                        key_buffer, key_buffer_size, alg, peer_key,
                        peer_key_length, shared_secret, shared_secret_size,
                        shared_secret_length );
            if( status != PSA_ERROR_NOT_SUPPORTED )
                return( status );
#endif /* PSA_CRYPTO_DRIVER_TEST */
#if defined(PSA_CRYPTO_DRIVER_CC3XX)                      //NXP TFM --- BEGIN ---
            status = cc3xx_key_agreement( attributes,
                                          key_buffer,
                                          key_buffer_size,
                                          peer_key,
                                          peer_key_length,
                                          shared_secret,
                                          shared_secret_size,
                                          shared_secret_length,
                                          alg );
            return( status );
#endif /* PSA_CRYPTO_DRIVER_CC3XX */                       //NXP TFM --- END ---
#endif /* PSA_CRYPTO_ACCELERATOR_DRIVER_PRESENT */

            /* Software Fallback */
            status = psa_key_agreement_raw_builtin( attributes,
                                                    key_buffer,
                                                    key_buffer_size,
                                                    alg,
                                                    peer_key,
                                                    peer_key_length,
                                                    shared_secret,
                                                    shared_secret_size,
                                                    shared_secret_length );
            return( status );
#if defined(PSA_CRYPTO_ACCELERATOR_DRIVER_PRESENT)
#if defined(PSA_CRYPTO_DRIVER_TEST)
        case PSA_CRYPTO_TEST_DRIVER_LOCATION:
            return( mbedtls_test_opaque_key_agreement( attributes,
                        key_buffer, key_buffer_size, alg, peer_key,
                        peer_key_length, shared_secret, shared_secret_size,
                        shared_secret_length ) );
#endif /* PSA_CRYPTO_DRIVER_TEST */
#endif /* PSA_CRYPTO_ACCELERATOR_DRIVER_PRESENT */

        default:
            (void) attributes;
            (void) key_buffer;
            (void) key_buffer_size;
            (void) peer_key;
            (void) peer_key_length;
            (void) shared_secret;
            (void) shared_secret_size;
            (void) shared_secret_length;
            return( PSA_ERROR_NOT_SUPPORTED );

    }
 }

psa_status_t psa_driver_wrapper_pake_setup(
    psa_pake_operation_t *operation,
    const psa_crypto_driver_pake_inputs_t *inputs )
{
    psa_status_t status = PSA_ERROR_CORRUPTION_DETECTED;

    psa_key_location_t location =
            PSA_KEY_LIFETIME_GET_LOCATION( psa_get_key_lifetime( &inputs->attributes ) );

    switch( location )
    {
        case PSA_KEY_LOCATION_LOCAL_STORAGE:
            /* Key is stored in the slot in export representation, so
             * cycle through all known transparent accelerators */
#if defined(PSA_CRYPTO_ACCELERATOR_DRIVER_PRESENT)
#if defined(PSA_CRYPTO_DRIVER_TEST)
            status = mbedtls_test_transparent_pake_setup(
                        &operation->data.ctx.transparent_test_driver_ctx,
                        inputs );
            if( status == PSA_SUCCESS )
                operation->id = MBEDTLS_TEST_TRANSPARENT_DRIVER_ID;
            /* Declared with fallback == true */
            if( status != PSA_ERROR_NOT_SUPPORTED )
                return( status );
#endif /* PSA_CRYPTO_DRIVER_TEST */
#endif /* PSA_CRYPTO_ACCELERATOR_DRIVER_PRESENT */
#if defined(MBEDTLS_PSA_BUILTIN_PAKE)
            status = mbedtls_psa_pake_setup( &operation->data.ctx.mbedtls_ctx,
                        inputs );
            if( status == PSA_SUCCESS )
                operation->id = PSA_CRYPTO_MBED_TLS_DRIVER_ID;
            return status;
#endif
            return( PSA_ERROR_NOT_SUPPORTED );
        /* Add cases for opaque driver here */
        default:
            /* Key is declared with a lifetime not known to us */
            (void)operation;
            (void)inputs;
            (void)status;
            return( PSA_ERROR_INVALID_ARGUMENT );
    }
}
psa_status_t psa_driver_wrapper_pake_output(
    psa_pake_operation_t *operation,
    psa_crypto_driver_pake_step_t step,
    uint8_t *output,
    size_t output_size,
    size_t *output_length )
{
    switch( operation->id )
    {
#if defined(MBEDTLS_PSA_BUILTIN_PAKE)
        case PSA_CRYPTO_MBED_TLS_DRIVER_ID:
            return( mbedtls_psa_pake_output( &operation->data.ctx.mbedtls_ctx, step,
                                             output, output_size, output_length ) );
#endif /* MBEDTLS_PSA_BUILTIN_PAKE */

#if defined(PSA_CRYPTO_ACCELERATOR_DRIVER_PRESENT)
#if defined(PSA_CRYPTO_DRIVER_TEST)
        case MBEDTLS_TEST_TRANSPARENT_DRIVER_ID:
            return( mbedtls_test_transparent_pake_output(
                        &operation->data.ctx.transparent_test_driver_ctx,
                        step, output, output_size, output_length ) );
#endif /* PSA_CRYPTO_DRIVER_TEST */
#endif /* PSA_CRYPTO_ACCELERATOR_DRIVER_PRESENT */
        default:
            (void) step;
            (void) output;
            (void) output_size;
            (void) output_length;
            return( PSA_ERROR_INVALID_ARGUMENT );
    }
}

psa_status_t psa_driver_wrapper_pake_input(
    psa_pake_operation_t *operation,
    psa_crypto_driver_pake_step_t step,
    const uint8_t *input,
    size_t input_length )
{
    switch( operation->id )
    {
#if defined(MBEDTLS_PSA_BUILTIN_PAKE)
        case PSA_CRYPTO_MBED_TLS_DRIVER_ID:
            return( mbedtls_psa_pake_input( &operation->data.ctx.mbedtls_ctx,
                                            step, input,
                                            input_length ) );
#endif /* MBEDTLS_PSA_BUILTIN_PAKE */

#if defined(PSA_CRYPTO_ACCELERATOR_DRIVER_PRESENT)
#if defined(PSA_CRYPTO_DRIVER_TEST)
        case MBEDTLS_TEST_TRANSPARENT_DRIVER_ID:
            return( mbedtls_test_transparent_pake_input(
                        &operation->data.ctx.transparent_test_driver_ctx,
                        step,
                        input, input_length ) );
#endif /* PSA_CRYPTO_DRIVER_TEST */
#endif /* PSA_CRYPTO_ACCELERATOR_DRIVER_PRESENT */
        default:
            (void) step;
            (void) input;
            (void) input_length;
            return( PSA_ERROR_INVALID_ARGUMENT );
    }
}

psa_status_t psa_driver_wrapper_pake_get_implicit_key(
    psa_pake_operation_t *operation,
    uint8_t *output, size_t output_size,
    size_t *output_length )
{
    switch( operation->id )
    {
#if defined(MBEDTLS_PSA_BUILTIN_PAKE)
        case PSA_CRYPTO_MBED_TLS_DRIVER_ID:
            return( mbedtls_psa_pake_get_implicit_key( &operation->data.ctx.mbedtls_ctx,
                                                       output, output_size, output_length ) );
#endif /* MBEDTLS_PSA_BUILTIN_PAKE */

#if defined(PSA_CRYPTO_ACCELERATOR_DRIVER_PRESENT)
#if defined(PSA_CRYPTO_DRIVER_TEST)
        case MBEDTLS_TEST_TRANSPARENT_DRIVER_ID:
            return( mbedtls_test_transparent_pake_get_implicit_key(
                        &operation->data.ctx.transparent_test_driver_ctx,
                        output, output_size, output_length ) );
#endif /* PSA_CRYPTO_DRIVER_TEST */
#endif /* PSA_CRYPTO_ACCELERATOR_DRIVER_PRESENT */
        default:
            (void) output;
            (void) output_size;
            (void) output_length;
            return( PSA_ERROR_INVALID_ARGUMENT );
    }
}

psa_status_t psa_driver_wrapper_pake_abort(
    psa_pake_operation_t * operation )
{
    switch( operation->id )
    {
#if defined(MBEDTLS_PSA_BUILTIN_PAKE)
        case PSA_CRYPTO_MBED_TLS_DRIVER_ID:
            return( mbedtls_psa_pake_abort( &operation->data.ctx.mbedtls_ctx ) );
#endif /* MBEDTLS_PSA_BUILTIN_PAKE */

#if defined(PSA_CRYPTO_ACCELERATOR_DRIVER_PRESENT)
#if defined(PSA_CRYPTO_DRIVER_TEST)
        case MBEDTLS_TEST_TRANSPARENT_DRIVER_ID:
            return( mbedtls_test_transparent_pake_abort(
                        &operation->data.ctx.transparent_test_driver_ctx ) );
#endif /* PSA_CRYPTO_DRIVER_TEST */
#endif /* PSA_CRYPTO_ACCELERATOR_DRIVER_PRESENT */
        default:
            return( PSA_ERROR_INVALID_ARGUMENT );
    }
}

#endif /* MBEDTLS_PSA_CRYPTO_C */
