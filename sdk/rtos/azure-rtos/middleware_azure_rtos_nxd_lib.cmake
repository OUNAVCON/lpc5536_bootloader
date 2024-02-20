# Add set(CONFIG_USE_middleware_azure_rtos_nxd_lib true) in config.cmake to use this component

include_guard(GLOBAL)
message("${CMAKE_CURRENT_LIST_FILE} component is included.")

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}/netxduo/common/netxduo_common_source.c
  ${CMAKE_CURRENT_LIST_DIR}/netxduo/crypto_libraries/src/nx_crypto_3des.c
  ${CMAKE_CURRENT_LIST_DIR}/netxduo/crypto_libraries/src/nx_crypto_aes.c
  ${CMAKE_CURRENT_LIST_DIR}/netxduo/crypto_libraries/src/nx_crypto_cbc.c
  ${CMAKE_CURRENT_LIST_DIR}/netxduo/crypto_libraries/src/nx_crypto_ccm.c
  ${CMAKE_CURRENT_LIST_DIR}/netxduo/crypto_libraries/src/nx_crypto_ctr.c
  ${CMAKE_CURRENT_LIST_DIR}/netxduo/crypto_libraries/src/nx_crypto_des.c
  ${CMAKE_CURRENT_LIST_DIR}/netxduo/crypto_libraries/src/nx_crypto_dh.c
  ${CMAKE_CURRENT_LIST_DIR}/netxduo/crypto_libraries/src/nx_crypto_drbg.c
  ${CMAKE_CURRENT_LIST_DIR}/netxduo/crypto_libraries/src/nx_crypto_ec.c
  ${CMAKE_CURRENT_LIST_DIR}/netxduo/crypto_libraries/src/nx_crypto_ec_secp192r1_fixed_points.c
  ${CMAKE_CURRENT_LIST_DIR}/netxduo/crypto_libraries/src/nx_crypto_ec_secp224r1_fixed_points.c
  ${CMAKE_CURRENT_LIST_DIR}/netxduo/crypto_libraries/src/nx_crypto_ec_secp256r1_fixed_points.c
  ${CMAKE_CURRENT_LIST_DIR}/netxduo/crypto_libraries/src/nx_crypto_ec_secp384r1_fixed_points.c
  ${CMAKE_CURRENT_LIST_DIR}/netxduo/crypto_libraries/src/nx_crypto_ec_secp521r1_fixed_points.c
  ${CMAKE_CURRENT_LIST_DIR}/netxduo/crypto_libraries/src/nx_crypto_ecdh.c
  ${CMAKE_CURRENT_LIST_DIR}/netxduo/crypto_libraries/src/nx_crypto_ecdsa.c
  ${CMAKE_CURRENT_LIST_DIR}/netxduo/crypto_libraries/src/nx_crypto_ecjpake.c
  ${CMAKE_CURRENT_LIST_DIR}/netxduo/crypto_libraries/src/nx_crypto_gcm.c
  ${CMAKE_CURRENT_LIST_DIR}/netxduo/crypto_libraries/src/nx_crypto_generic_ciphersuites.c
  ${CMAKE_CURRENT_LIST_DIR}/netxduo/crypto_libraries/src/nx_crypto_hkdf.c
  ${CMAKE_CURRENT_LIST_DIR}/netxduo/crypto_libraries/src/nx_crypto_hmac.c
  ${CMAKE_CURRENT_LIST_DIR}/netxduo/crypto_libraries/src/nx_crypto_hmac_md5.c
  ${CMAKE_CURRENT_LIST_DIR}/netxduo/crypto_libraries/src/nx_crypto_hmac_sha1.c
  ${CMAKE_CURRENT_LIST_DIR}/netxduo/crypto_libraries/src/nx_crypto_hmac_sha2.c
  ${CMAKE_CURRENT_LIST_DIR}/netxduo/crypto_libraries/src/nx_crypto_hmac_sha5.c
  ${CMAKE_CURRENT_LIST_DIR}/netxduo/crypto_libraries/src/nx_crypto_huge_number.c
  ${CMAKE_CURRENT_LIST_DIR}/netxduo/crypto_libraries/src/nx_crypto_huge_number_extended.c
  ${CMAKE_CURRENT_LIST_DIR}/netxduo/crypto_libraries/src/nx_crypto_initialize.c
  ${CMAKE_CURRENT_LIST_DIR}/netxduo/crypto_libraries/src/nx_crypto_md5.c
  ${CMAKE_CURRENT_LIST_DIR}/netxduo/crypto_libraries/src/nx_crypto_method_self_test.c
  ${CMAKE_CURRENT_LIST_DIR}/netxduo/crypto_libraries/src/nx_crypto_method_self_test_3des.c
  ${CMAKE_CURRENT_LIST_DIR}/netxduo/crypto_libraries/src/nx_crypto_method_self_test_aes.c
  ${CMAKE_CURRENT_LIST_DIR}/netxduo/crypto_libraries/src/nx_crypto_method_self_test_des.c
  ${CMAKE_CURRENT_LIST_DIR}/netxduo/crypto_libraries/src/nx_crypto_method_self_test_drbg.c
  ${CMAKE_CURRENT_LIST_DIR}/netxduo/crypto_libraries/src/nx_crypto_method_self_test_ecdh.c
  ${CMAKE_CURRENT_LIST_DIR}/netxduo/crypto_libraries/src/nx_crypto_method_self_test_ecdsa.c
  ${CMAKE_CURRENT_LIST_DIR}/netxduo/crypto_libraries/src/nx_crypto_method_self_test_hmac_md5.c
  ${CMAKE_CURRENT_LIST_DIR}/netxduo/crypto_libraries/src/nx_crypto_method_self_test_hmac_sha.c
  ${CMAKE_CURRENT_LIST_DIR}/netxduo/crypto_libraries/src/nx_crypto_method_self_test_md5.c
  ${CMAKE_CURRENT_LIST_DIR}/netxduo/crypto_libraries/src/nx_crypto_method_self_test_pkcs1.c
  ${CMAKE_CURRENT_LIST_DIR}/netxduo/crypto_libraries/src/nx_crypto_method_self_test_prf.c
  ${CMAKE_CURRENT_LIST_DIR}/netxduo/crypto_libraries/src/nx_crypto_method_self_test_rsa.c
  ${CMAKE_CURRENT_LIST_DIR}/netxduo/crypto_libraries/src/nx_crypto_method_self_test_sha.c
  ${CMAKE_CURRENT_LIST_DIR}/netxduo/crypto_libraries/src/nx_crypto_methods.c
  ${CMAKE_CURRENT_LIST_DIR}/netxduo/crypto_libraries/src/nx_crypto_null_cipher.c
  ${CMAKE_CURRENT_LIST_DIR}/netxduo/crypto_libraries/src/nx_crypto_phash.c
  ${CMAKE_CURRENT_LIST_DIR}/netxduo/crypto_libraries/src/nx_crypto_pkcs1_v1.5.c
  ${CMAKE_CURRENT_LIST_DIR}/netxduo/crypto_libraries/src/nx_crypto_rsa.c
  ${CMAKE_CURRENT_LIST_DIR}/netxduo/crypto_libraries/src/nx_crypto_sha1.c
  ${CMAKE_CURRENT_LIST_DIR}/netxduo/crypto_libraries/src/nx_crypto_sha2.c
  ${CMAKE_CURRENT_LIST_DIR}/netxduo/crypto_libraries/src/nx_crypto_sha5.c
  ${CMAKE_CURRENT_LIST_DIR}/netxduo/crypto_libraries/src/nx_crypto_tls_prf_1.c
  ${CMAKE_CURRENT_LIST_DIR}/netxduo/crypto_libraries/src/nx_crypto_tls_prf_sha256.c
  ${CMAKE_CURRENT_LIST_DIR}/netxduo/crypto_libraries/src/nx_crypto_tls_prf_sha384.c
  ${CMAKE_CURRENT_LIST_DIR}/netxduo/crypto_libraries/src/nx_crypto_tls_prf_sha512.c
  ${CMAKE_CURRENT_LIST_DIR}/netxduo/crypto_libraries/src/nx_crypto_xcbc_mac.c
  ${CMAKE_CURRENT_LIST_DIR}/netxduo/nx_secure/src/nx_secure_crypto_method_self_test_3des.c
  ${CMAKE_CURRENT_LIST_DIR}/netxduo/nx_secure/src/nx_secure_crypto_method_self_test_aes.c
  ${CMAKE_CURRENT_LIST_DIR}/netxduo/nx_secure/src/nx_secure_crypto_method_self_test_des.c
  ${CMAKE_CURRENT_LIST_DIR}/netxduo/nx_secure/src/nx_secure_crypto_method_self_test_hmac_md5.c
  ${CMAKE_CURRENT_LIST_DIR}/netxduo/nx_secure/src/nx_secure_crypto_method_self_test_hmac_sha.c
  ${CMAKE_CURRENT_LIST_DIR}/netxduo/nx_secure/src/nx_secure_crypto_method_self_test_md5.c
  ${CMAKE_CURRENT_LIST_DIR}/netxduo/nx_secure/src/nx_secure_crypto_method_self_test_prf.c
  ${CMAKE_CURRENT_LIST_DIR}/netxduo/nx_secure/src/nx_secure_crypto_method_self_test_rsa.c
  ${CMAKE_CURRENT_LIST_DIR}/netxduo/nx_secure/src/nx_secure_crypto_method_self_test_sha.c
  ${CMAKE_CURRENT_LIST_DIR}/netxduo/nx_secure/src/nx_secure_crypto_rng_self_test.c
  ${CMAKE_CURRENT_LIST_DIR}/netxduo/nx_secure/src/nx_secure_crypto_table_self_test.c
  ${CMAKE_CURRENT_LIST_DIR}/netxduo/nx_secure/src/nx_secure_dtls_allocate_handshake_packet.c
  ${CMAKE_CURRENT_LIST_DIR}/netxduo/nx_secure/src/nx_secure_dtls_client_handshake.c
  ${CMAKE_CURRENT_LIST_DIR}/netxduo/nx_secure/src/nx_secure_dtls_client_protocol_version_override.c
  ${CMAKE_CURRENT_LIST_DIR}/netxduo/nx_secure/src/nx_secure_dtls_client_session_start.c
  ${CMAKE_CURRENT_LIST_DIR}/netxduo/nx_secure/src/nx_secure_dtls_ecc_initialize.c
  ${CMAKE_CURRENT_LIST_DIR}/netxduo/nx_secure/src/nx_secure_dtls_hash_record.c
  ${CMAKE_CURRENT_LIST_DIR}/netxduo/nx_secure/src/nx_secure_dtls_initialize.c
  ${CMAKE_CURRENT_LIST_DIR}/netxduo/nx_secure/src/nx_secure_dtls_packet_allocate.c
  ${CMAKE_CURRENT_LIST_DIR}/netxduo/nx_secure/src/nx_secure_dtls_process_clienthello.c
  ${CMAKE_CURRENT_LIST_DIR}/netxduo/nx_secure/src/nx_secure_dtls_process_handshake_header.c
  ${CMAKE_CURRENT_LIST_DIR}/netxduo/nx_secure/src/nx_secure_dtls_process_header.c
  ${CMAKE_CURRENT_LIST_DIR}/netxduo/nx_secure/src/nx_secure_dtls_process_helloverifyrequest.c
  ${CMAKE_CURRENT_LIST_DIR}/netxduo/nx_secure/src/nx_secure_dtls_process_record.c
  ${CMAKE_CURRENT_LIST_DIR}/netxduo/nx_secure/src/nx_secure_dtls_psk_add.c
  ${CMAKE_CURRENT_LIST_DIR}/netxduo/nx_secure/src/nx_secure_dtls_receive_callback.c
  ${CMAKE_CURRENT_LIST_DIR}/netxduo/nx_secure/src/nx_secure_dtls_retransmit.c
  ${CMAKE_CURRENT_LIST_DIR}/netxduo/nx_secure/src/nx_secure_dtls_retransmit_queue_flush.c
  ${CMAKE_CURRENT_LIST_DIR}/netxduo/nx_secure/src/nx_secure_dtls_send_clienthello.c
  ${CMAKE_CURRENT_LIST_DIR}/netxduo/nx_secure/src/nx_secure_dtls_send_handshake_record.c
  ${CMAKE_CURRENT_LIST_DIR}/netxduo/nx_secure/src/nx_secure_dtls_send_helloverifyrequest.c
  ${CMAKE_CURRENT_LIST_DIR}/netxduo/nx_secure/src/nx_secure_dtls_send_record.c
  ${CMAKE_CURRENT_LIST_DIR}/netxduo/nx_secure/src/nx_secure_dtls_send_serverhello.c
  ${CMAKE_CURRENT_LIST_DIR}/netxduo/nx_secure/src/nx_secure_dtls_server_create.c
  ${CMAKE_CURRENT_LIST_DIR}/netxduo/nx_secure/src/nx_secure_dtls_server_delete.c
  ${CMAKE_CURRENT_LIST_DIR}/netxduo/nx_secure/src/nx_secure_dtls_server_ecc_initialize.c
  ${CMAKE_CURRENT_LIST_DIR}/netxduo/nx_secure/src/nx_secure_dtls_server_handshake.c
  ${CMAKE_CURRENT_LIST_DIR}/netxduo/nx_secure/src/nx_secure_dtls_server_local_certificate_add.c
  ${CMAKE_CURRENT_LIST_DIR}/netxduo/nx_secure/src/nx_secure_dtls_server_local_certificate_remove.c
  ${CMAKE_CURRENT_LIST_DIR}/netxduo/nx_secure/src/nx_secure_dtls_server_notify_set.c
  ${CMAKE_CURRENT_LIST_DIR}/netxduo/nx_secure/src/nx_secure_dtls_server_protocol_version_override.c
  ${CMAKE_CURRENT_LIST_DIR}/netxduo/nx_secure/src/nx_secure_dtls_server_psk_add.c
  ${CMAKE_CURRENT_LIST_DIR}/netxduo/nx_secure/src/nx_secure_dtls_server_session_send.c
  ${CMAKE_CURRENT_LIST_DIR}/netxduo/nx_secure/src/nx_secure_dtls_server_session_start.c
  ${CMAKE_CURRENT_LIST_DIR}/netxduo/nx_secure/src/nx_secure_dtls_server_start.c
  ${CMAKE_CURRENT_LIST_DIR}/netxduo/nx_secure/src/nx_secure_dtls_server_stop.c
  ${CMAKE_CURRENT_LIST_DIR}/netxduo/nx_secure/src/nx_secure_dtls_server_trusted_certificate_add.c
  ${CMAKE_CURRENT_LIST_DIR}/netxduo/nx_secure/src/nx_secure_dtls_server_trusted_certificate_remove.c
  ${CMAKE_CURRENT_LIST_DIR}/netxduo/nx_secure/src/nx_secure_dtls_server_x509_client_verify_configure.c
  ${CMAKE_CURRENT_LIST_DIR}/netxduo/nx_secure/src/nx_secure_dtls_server_x509_client_verify_disable.c
  ${CMAKE_CURRENT_LIST_DIR}/netxduo/nx_secure/src/nx_secure_dtls_session_cache.c
  ${CMAKE_CURRENT_LIST_DIR}/netxduo/nx_secure/src/nx_secure_dtls_session_client_info_get.c
  ${CMAKE_CURRENT_LIST_DIR}/netxduo/nx_secure/src/nx_secure_dtls_session_create.c
  ${CMAKE_CURRENT_LIST_DIR}/netxduo/nx_secure/src/nx_secure_dtls_session_delete.c
  ${CMAKE_CURRENT_LIST_DIR}/netxduo/nx_secure/src/nx_secure_dtls_session_end.c
  ${CMAKE_CURRENT_LIST_DIR}/netxduo/nx_secure/src/nx_secure_dtls_session_local_certificate_add.c
  ${CMAKE_CURRENT_LIST_DIR}/netxduo/nx_secure/src/nx_secure_dtls_session_local_certificate_remove.c
  ${CMAKE_CURRENT_LIST_DIR}/netxduo/nx_secure/src/nx_secure_dtls_session_receive.c
  ${CMAKE_CURRENT_LIST_DIR}/netxduo/nx_secure/src/nx_secure_dtls_session_reset.c
  ${CMAKE_CURRENT_LIST_DIR}/netxduo/nx_secure/src/nx_secure_dtls_session_send.c
  ${CMAKE_CURRENT_LIST_DIR}/netxduo/nx_secure/src/nx_secure_dtls_session_sliding_window_check.c
  ${CMAKE_CURRENT_LIST_DIR}/netxduo/nx_secure/src/nx_secure_dtls_session_sliding_window_update.c
  ${CMAKE_CURRENT_LIST_DIR}/netxduo/nx_secure/src/nx_secure_dtls_session_start.c
  ${CMAKE_CURRENT_LIST_DIR}/netxduo/nx_secure/src/nx_secure_dtls_session_trusted_certificate_add.c
  ${CMAKE_CURRENT_LIST_DIR}/netxduo/nx_secure/src/nx_secure_dtls_session_trusted_certificate_remove.c
  ${CMAKE_CURRENT_LIST_DIR}/netxduo/nx_secure/src/nx_secure_dtls_verify_mac.c
  ${CMAKE_CURRENT_LIST_DIR}/netxduo/nx_secure/src/nx_secure_generate_client_key_exchange.c
  ${CMAKE_CURRENT_LIST_DIR}/netxduo/nx_secure/src/nx_secure_generate_master_secret.c
  ${CMAKE_CURRENT_LIST_DIR}/netxduo/nx_secure/src/nx_secure_generate_premaster_secret.c
  ${CMAKE_CURRENT_LIST_DIR}/netxduo/nx_secure/src/nx_secure_generate_server_key_exchange.c
  ${CMAKE_CURRENT_LIST_DIR}/netxduo/nx_secure/src/nx_secure_generate_session_keys.c
  ${CMAKE_CURRENT_LIST_DIR}/netxduo/nx_secure/src/nx_secure_module_hash_compute.c
  ${CMAKE_CURRENT_LIST_DIR}/netxduo/nx_secure/src/nx_secure_process_client_key_exchange.c
  ${CMAKE_CURRENT_LIST_DIR}/netxduo/nx_secure/src/nx_secure_process_server_key_exchange.c
  ${CMAKE_CURRENT_LIST_DIR}/netxduo/nx_secure/src/nx_secure_remote_certificate_verify.c
  ${CMAKE_CURRENT_LIST_DIR}/netxduo/nx_secure/src/nx_secure_session_keys_set.c
  ${CMAKE_CURRENT_LIST_DIR}/netxduo/nx_secure/src/nx_secure_tls_1_3_client_handshake.c
  ${CMAKE_CURRENT_LIST_DIR}/netxduo/nx_secure/src/nx_secure_tls_1_3_crypto_init.c
  ${CMAKE_CURRENT_LIST_DIR}/netxduo/nx_secure/src/nx_secure_tls_1_3_finished_hash_generate.c
  ${CMAKE_CURRENT_LIST_DIR}/netxduo/nx_secure/src/nx_secure_tls_1_3_generate_keys.c
  ${CMAKE_CURRENT_LIST_DIR}/netxduo/nx_secure/src/nx_secure_tls_1_3_server_handshake.c
  ${CMAKE_CURRENT_LIST_DIR}/netxduo/nx_secure/src/nx_secure_tls_1_3_session_keys_set.c
  ${CMAKE_CURRENT_LIST_DIR}/netxduo/nx_secure/src/nx_secure_tls_1_3_transcript_hash_save.c
  ${CMAKE_CURRENT_LIST_DIR}/netxduo/nx_secure/src/nx_secure_tls_active_certificate_set.c
  ${CMAKE_CURRENT_LIST_DIR}/netxduo/nx_secure/src/nx_secure_tls_allocate_handshake_packet.c
  ${CMAKE_CURRENT_LIST_DIR}/netxduo/nx_secure/src/nx_secure_tls_check_protocol_version.c
  ${CMAKE_CURRENT_LIST_DIR}/netxduo/nx_secure/src/nx_secure_tls_ciphersuite_lookup.c
  ${CMAKE_CURRENT_LIST_DIR}/netxduo/nx_secure/src/nx_secure_tls_client_handshake.c
  ${CMAKE_CURRENT_LIST_DIR}/netxduo/nx_secure/src/nx_secure_tls_client_psk_set.c
  ${CMAKE_CURRENT_LIST_DIR}/netxduo/nx_secure/src/nx_secure_tls_ecc_generate_keys.c
  ${CMAKE_CURRENT_LIST_DIR}/netxduo/nx_secure/src/nx_secure_tls_ecc_initialize.c
  ${CMAKE_CURRENT_LIST_DIR}/netxduo/nx_secure/src/nx_secure_tls_find_curve_method.c
  ${CMAKE_CURRENT_LIST_DIR}/netxduo/nx_secure/src/nx_secure_tls_finished_hash_generate.c
  ${CMAKE_CURRENT_LIST_DIR}/netxduo/nx_secure/src/nx_secure_tls_generate_keys.c
  ${CMAKE_CURRENT_LIST_DIR}/netxduo/nx_secure/src/nx_secure_tls_generate_premaster_secret.c
  ${CMAKE_CURRENT_LIST_DIR}/netxduo/nx_secure/src/nx_secure_tls_handshake_hash_init.c
  ${CMAKE_CURRENT_LIST_DIR}/netxduo/nx_secure/src/nx_secure_tls_handshake_hash_update.c
  ${CMAKE_CURRENT_LIST_DIR}/netxduo/nx_secure/src/nx_secure_tls_handshake_process.c
  ${CMAKE_CURRENT_LIST_DIR}/netxduo/nx_secure/src/nx_secure_tls_hash_record.c
  ${CMAKE_CURRENT_LIST_DIR}/netxduo/nx_secure/src/nx_secure_tls_initialize.c
  ${CMAKE_CURRENT_LIST_DIR}/netxduo/nx_secure/src/nx_secure_tls_key_material_init.c
  ${CMAKE_CURRENT_LIST_DIR}/netxduo/nx_secure/src/nx_secure_tls_local_certificate_add.c
  ${CMAKE_CURRENT_LIST_DIR}/netxduo/nx_secure/src/nx_secure_tls_local_certificate_find.c
  ${CMAKE_CURRENT_LIST_DIR}/netxduo/nx_secure/src/nx_secure_tls_local_certificate_remove.c
  ${CMAKE_CURRENT_LIST_DIR}/netxduo/nx_secure/src/nx_secure_tls_map_error_to_alert.c
  ${CMAKE_CURRENT_LIST_DIR}/netxduo/nx_secure/src/nx_secure_tls_metadata_size_calculate.c
  ${CMAKE_CURRENT_LIST_DIR}/netxduo/nx_secure/src/nx_secure_tls_newest_supported_version.c
  ${CMAKE_CURRENT_LIST_DIR}/netxduo/nx_secure/src/nx_secure_tls_packet_allocate.c
  ${CMAKE_CURRENT_LIST_DIR}/netxduo/nx_secure/src/nx_secure_tls_packet_release.c
  ${CMAKE_CURRENT_LIST_DIR}/netxduo/nx_secure/src/nx_secure_tls_process_certificate_request.c
  ${CMAKE_CURRENT_LIST_DIR}/netxduo/nx_secure/src/nx_secure_tls_process_certificate_verify.c
  ${CMAKE_CURRENT_LIST_DIR}/netxduo/nx_secure/src/nx_secure_tls_process_changecipherspec.c
  ${CMAKE_CURRENT_LIST_DIR}/netxduo/nx_secure/src/nx_secure_tls_process_client_key_exchange.c
  ${CMAKE_CURRENT_LIST_DIR}/netxduo/nx_secure/src/nx_secure_tls_process_clienthello.c
  ${CMAKE_CURRENT_LIST_DIR}/netxduo/nx_secure/src/nx_secure_tls_process_clienthello_extensions.c
  ${CMAKE_CURRENT_LIST_DIR}/netxduo/nx_secure/src/nx_secure_tls_process_encrypted_extensions.c
  ${CMAKE_CURRENT_LIST_DIR}/netxduo/nx_secure/src/nx_secure_tls_process_finished.c
  ${CMAKE_CURRENT_LIST_DIR}/netxduo/nx_secure/src/nx_secure_tls_process_handshake_header.c
  ${CMAKE_CURRENT_LIST_DIR}/netxduo/nx_secure/src/nx_secure_tls_process_header.c
  ${CMAKE_CURRENT_LIST_DIR}/netxduo/nx_secure/src/nx_secure_tls_process_newsessionticket.c
  ${CMAKE_CURRENT_LIST_DIR}/netxduo/nx_secure/src/nx_secure_tls_process_record.c
  ${CMAKE_CURRENT_LIST_DIR}/netxduo/nx_secure/src/nx_secure_tls_process_remote_certificate.c
  ${CMAKE_CURRENT_LIST_DIR}/netxduo/nx_secure/src/nx_secure_tls_process_server_key_exchange.c
  ${CMAKE_CURRENT_LIST_DIR}/netxduo/nx_secure/src/nx_secure_tls_process_serverhello.c
  ${CMAKE_CURRENT_LIST_DIR}/netxduo/nx_secure/src/nx_secure_tls_process_serverhello_extensions.c
  ${CMAKE_CURRENT_LIST_DIR}/netxduo/nx_secure/src/nx_secure_tls_protocol_version_get.c
  ${CMAKE_CURRENT_LIST_DIR}/netxduo/nx_secure/src/nx_secure_tls_psk_add.c
  ${CMAKE_CURRENT_LIST_DIR}/netxduo/nx_secure/src/nx_secure_tls_psk_binder_generate.c
  ${CMAKE_CURRENT_LIST_DIR}/netxduo/nx_secure/src/nx_secure_tls_psk_find.c
  ${CMAKE_CURRENT_LIST_DIR}/netxduo/nx_secure/src/nx_secure_tls_psk_identity_find.c
  ${CMAKE_CURRENT_LIST_DIR}/netxduo/nx_secure/src/nx_secure_tls_record_hash_calculate.c
  ${CMAKE_CURRENT_LIST_DIR}/netxduo/nx_secure/src/nx_secure_tls_record_hash_initialize.c
  ${CMAKE_CURRENT_LIST_DIR}/netxduo/nx_secure/src/nx_secure_tls_record_hash_update.c
  ${CMAKE_CURRENT_LIST_DIR}/netxduo/nx_secure/src/nx_secure_tls_record_payload_decrypt.c
  ${CMAKE_CURRENT_LIST_DIR}/netxduo/nx_secure/src/nx_secure_tls_record_payload_encrypt.c
  ${CMAKE_CURRENT_LIST_DIR}/netxduo/nx_secure/src/nx_secure_tls_remote_certificate_allocate.c
  ${CMAKE_CURRENT_LIST_DIR}/netxduo/nx_secure/src/nx_secure_tls_remote_certificate_buffer_allocate.c
  ${CMAKE_CURRENT_LIST_DIR}/netxduo/nx_secure/src/nx_secure_tls_remote_certificate_free.c
  ${CMAKE_CURRENT_LIST_DIR}/netxduo/nx_secure/src/nx_secure_tls_remote_certificate_free_all.c
  ${CMAKE_CURRENT_LIST_DIR}/netxduo/nx_secure/src/nx_secure_tls_remote_certificate_verify.c
  ${CMAKE_CURRENT_LIST_DIR}/netxduo/nx_secure/src/nx_secure_tls_send_alert.c
  ${CMAKE_CURRENT_LIST_DIR}/netxduo/nx_secure/src/nx_secure_tls_send_certificate.c
  ${CMAKE_CURRENT_LIST_DIR}/netxduo/nx_secure/src/nx_secure_tls_send_certificate_request.c
  ${CMAKE_CURRENT_LIST_DIR}/netxduo/nx_secure/src/nx_secure_tls_send_certificate_verify.c
  ${CMAKE_CURRENT_LIST_DIR}/netxduo/nx_secure/src/nx_secure_tls_send_changecipherspec.c
  ${CMAKE_CURRENT_LIST_DIR}/netxduo/nx_secure/src/nx_secure_tls_send_client_key_exchange.c
  ${CMAKE_CURRENT_LIST_DIR}/netxduo/nx_secure/src/nx_secure_tls_send_clienthello.c
  ${CMAKE_CURRENT_LIST_DIR}/netxduo/nx_secure/src/nx_secure_tls_send_clienthello_extensions.c
  ${CMAKE_CURRENT_LIST_DIR}/netxduo/nx_secure/src/nx_secure_tls_send_encrypted_extensions.c
  ${CMAKE_CURRENT_LIST_DIR}/netxduo/nx_secure/src/nx_secure_tls_send_finished.c
  ${CMAKE_CURRENT_LIST_DIR}/netxduo/nx_secure/src/nx_secure_tls_send_handshake_record.c
  ${CMAKE_CURRENT_LIST_DIR}/netxduo/nx_secure/src/nx_secure_tls_send_hellorequest.c
  ${CMAKE_CURRENT_LIST_DIR}/netxduo/nx_secure/src/nx_secure_tls_send_newsessionticket.c
  ${CMAKE_CURRENT_LIST_DIR}/netxduo/nx_secure/src/nx_secure_tls_send_record.c
  ${CMAKE_CURRENT_LIST_DIR}/netxduo/nx_secure/src/nx_secure_tls_send_server_key_exchange.c
  ${CMAKE_CURRENT_LIST_DIR}/netxduo/nx_secure/src/nx_secure_tls_send_serverhello.c
  ${CMAKE_CURRENT_LIST_DIR}/netxduo/nx_secure/src/nx_secure_tls_send_serverhello_extensions.c
  ${CMAKE_CURRENT_LIST_DIR}/netxduo/nx_secure/src/nx_secure_tls_server_certificate_add.c
  ${CMAKE_CURRENT_LIST_DIR}/netxduo/nx_secure/src/nx_secure_tls_server_certificate_find.c
  ${CMAKE_CURRENT_LIST_DIR}/netxduo/nx_secure/src/nx_secure_tls_server_certificate_remove.c
  ${CMAKE_CURRENT_LIST_DIR}/netxduo/nx_secure/src/nx_secure_tls_server_handshake.c
  ${CMAKE_CURRENT_LIST_DIR}/netxduo/nx_secure/src/nx_secure_tls_session_alert_value_get.c
  ${CMAKE_CURRENT_LIST_DIR}/netxduo/nx_secure/src/nx_secure_tls_session_certificate_callback_set.c
  ${CMAKE_CURRENT_LIST_DIR}/netxduo/nx_secure/src/nx_secure_tls_session_client_callback_set.c
  ${CMAKE_CURRENT_LIST_DIR}/netxduo/nx_secure/src/nx_secure_tls_session_client_verify_disable.c
  ${CMAKE_CURRENT_LIST_DIR}/netxduo/nx_secure/src/nx_secure_tls_session_client_verify_enable.c
  ${CMAKE_CURRENT_LIST_DIR}/netxduo/nx_secure/src/nx_secure_tls_session_create.c
  ${CMAKE_CURRENT_LIST_DIR}/netxduo/nx_secure/src/nx_secure_tls_session_create_ext.c
  ${CMAKE_CURRENT_LIST_DIR}/netxduo/nx_secure/src/nx_secure_tls_session_delete.c
  ${CMAKE_CURRENT_LIST_DIR}/netxduo/nx_secure/src/nx_secure_tls_session_end.c
  ${CMAKE_CURRENT_LIST_DIR}/netxduo/nx_secure/src/nx_secure_tls_session_iv_size_get.c
  ${CMAKE_CURRENT_LIST_DIR}/netxduo/nx_secure/src/nx_secure_tls_session_keys_set.c
  ${CMAKE_CURRENT_LIST_DIR}/netxduo/nx_secure/src/nx_secure_tls_session_packet_buffer_set.c
  ${CMAKE_CURRENT_LIST_DIR}/netxduo/nx_secure/src/nx_secure_tls_session_packet_pool_set.c
  ${CMAKE_CURRENT_LIST_DIR}/netxduo/nx_secure/src/nx_secure_tls_session_protocol_version_override.c
  ${CMAKE_CURRENT_LIST_DIR}/netxduo/nx_secure/src/nx_secure_tls_session_receive.c
  ${CMAKE_CURRENT_LIST_DIR}/netxduo/nx_secure/src/nx_secure_tls_session_receive_records.c
  ${CMAKE_CURRENT_LIST_DIR}/netxduo/nx_secure/src/nx_secure_tls_session_renegotiate.c
  ${CMAKE_CURRENT_LIST_DIR}/netxduo/nx_secure/src/nx_secure_tls_session_renegotiate_callback_set.c
  ${CMAKE_CURRENT_LIST_DIR}/netxduo/nx_secure/src/nx_secure_tls_session_reset.c
  ${CMAKE_CURRENT_LIST_DIR}/netxduo/nx_secure/src/nx_secure_tls_session_send.c
  ${CMAKE_CURRENT_LIST_DIR}/netxduo/nx_secure/src/nx_secure_tls_session_server_callback_set.c
  ${CMAKE_CURRENT_LIST_DIR}/netxduo/nx_secure/src/nx_secure_tls_session_sni_extension_parse.c
  ${CMAKE_CURRENT_LIST_DIR}/netxduo/nx_secure/src/nx_secure_tls_session_sni_extension_set.c
  ${CMAKE_CURRENT_LIST_DIR}/netxduo/nx_secure/src/nx_secure_tls_session_start.c
  ${CMAKE_CURRENT_LIST_DIR}/netxduo/nx_secure/src/nx_secure_tls_session_time_function_set.c
  ${CMAKE_CURRENT_LIST_DIR}/netxduo/nx_secure/src/nx_secure_tls_session_x509_client_verify_configure.c
  ${CMAKE_CURRENT_LIST_DIR}/netxduo/nx_secure/src/nx_secure_tls_shutdown.c
  ${CMAKE_CURRENT_LIST_DIR}/netxduo/nx_secure/src/nx_secure_tls_trusted_certificate_add.c
  ${CMAKE_CURRENT_LIST_DIR}/netxduo/nx_secure/src/nx_secure_tls_trusted_certificate_remove.c
  ${CMAKE_CURRENT_LIST_DIR}/netxduo/nx_secure/src/nx_secure_tls_verify_mac.c
  ${CMAKE_CURRENT_LIST_DIR}/netxduo/nx_secure/src/nx_secure_trusted_certificate_add.c
  ${CMAKE_CURRENT_LIST_DIR}/netxduo/nx_secure/src/nx_secure_verify_mac.c
  ${CMAKE_CURRENT_LIST_DIR}/netxduo/nx_secure/src/nx_secure_x509.c
  ${CMAKE_CURRENT_LIST_DIR}/netxduo/nx_secure/src/nx_secure_x509_asn1_tlv_block_parse.c
  ${CMAKE_CURRENT_LIST_DIR}/netxduo/nx_secure/src/nx_secure_x509_certificate_chain_verify.c
  ${CMAKE_CURRENT_LIST_DIR}/netxduo/nx_secure/src/nx_secure_x509_certificate_initialize.c
  ${CMAKE_CURRENT_LIST_DIR}/netxduo/nx_secure/src/nx_secure_x509_certificate_list_add.c
  ${CMAKE_CURRENT_LIST_DIR}/netxduo/nx_secure/src/nx_secure_x509_certificate_list_find.c
  ${CMAKE_CURRENT_LIST_DIR}/netxduo/nx_secure/src/nx_secure_x509_certificate_list_remove.c
  ${CMAKE_CURRENT_LIST_DIR}/netxduo/nx_secure/src/nx_secure_x509_certificate_revocation_list_parse.c
  ${CMAKE_CURRENT_LIST_DIR}/netxduo/nx_secure/src/nx_secure_x509_certificate_verify.c
  ${CMAKE_CURRENT_LIST_DIR}/netxduo/nx_secure/src/nx_secure_x509_common_name_dns_check.c
  ${CMAKE_CURRENT_LIST_DIR}/netxduo/nx_secure/src/nx_secure_x509_crl_revocation_check.c
  ${CMAKE_CURRENT_LIST_DIR}/netxduo/nx_secure/src/nx_secure_x509_crl_verify.c
  ${CMAKE_CURRENT_LIST_DIR}/netxduo/nx_secure/src/nx_secure_x509_distinguished_name_compare.c
  ${CMAKE_CURRENT_LIST_DIR}/netxduo/nx_secure/src/nx_secure_x509_distinguished_name_parse.c
  ${CMAKE_CURRENT_LIST_DIR}/netxduo/nx_secure/src/nx_secure_x509_dns_name_initialize.c
  ${CMAKE_CURRENT_LIST_DIR}/netxduo/nx_secure/src/nx_secure_x509_ec_private_key_parse.c
  ${CMAKE_CURRENT_LIST_DIR}/netxduo/nx_secure/src/nx_secure_x509_expiration_check.c
  ${CMAKE_CURRENT_LIST_DIR}/netxduo/nx_secure/src/nx_secure_x509_extended_key_usage_extension_parse.c
  ${CMAKE_CURRENT_LIST_DIR}/netxduo/nx_secure/src/nx_secure_x509_extension_find.c
  ${CMAKE_CURRENT_LIST_DIR}/netxduo/nx_secure/src/nx_secure_x509_find_certificate_methods.c
  ${CMAKE_CURRENT_LIST_DIR}/netxduo/nx_secure/src/nx_secure_x509_find_curve_method.c
  ${CMAKE_CURRENT_LIST_DIR}/netxduo/nx_secure/src/nx_secure_x509_free_certificate_get.c
  ${CMAKE_CURRENT_LIST_DIR}/netxduo/nx_secure/src/nx_secure_x509_key_usage_extension_parse.c
  ${CMAKE_CURRENT_LIST_DIR}/netxduo/nx_secure/src/nx_secure_x509_local_certificate_find.c
  ${CMAKE_CURRENT_LIST_DIR}/netxduo/nx_secure/src/nx_secure_x509_local_device_certificate_get.c
  ${CMAKE_CURRENT_LIST_DIR}/netxduo/nx_secure/src/nx_secure_x509_oid_parse.c
  ${CMAKE_CURRENT_LIST_DIR}/netxduo/nx_secure/src/nx_secure_x509_pkcs1_rsa_private_key_parse.c
  ${CMAKE_CURRENT_LIST_DIR}/netxduo/nx_secure/src/nx_secure_x509_pkcs7_decode.c
  ${CMAKE_CURRENT_LIST_DIR}/netxduo/nx_secure/src/nx_secure_x509_remote_endpoint_certificate_get.c
  ${CMAKE_CURRENT_LIST_DIR}/netxduo/nx_secure/src/nx_secure_x509_store_certificate_add.c
  ${CMAKE_CURRENT_LIST_DIR}/netxduo/nx_secure/src/nx_secure_x509_store_certificate_find.c
  ${CMAKE_CURRENT_LIST_DIR}/netxduo/nx_secure/src/nx_secure_x509_store_certificate_remove.c
  ${CMAKE_CURRENT_LIST_DIR}/netxduo/nx_secure/src/nx_secure_x509_subject_alt_names_find.c
  ${CMAKE_CURRENT_LIST_DIR}/netxduo/nx_secure/src/nx_secure_x509_wildcard_compare.c
  ${CMAKE_CURRENT_LIST_DIR}/netxduo/nx_secure/src/nxe_secure_dtls_client_protocol_version_override.c
  ${CMAKE_CURRENT_LIST_DIR}/netxduo/nx_secure/src/nxe_secure_dtls_client_session_start.c
  ${CMAKE_CURRENT_LIST_DIR}/netxduo/nx_secure/src/nxe_secure_dtls_ecc_initialize.c
  ${CMAKE_CURRENT_LIST_DIR}/netxduo/nx_secure/src/nxe_secure_dtls_packet_allocate.c
  ${CMAKE_CURRENT_LIST_DIR}/netxduo/nx_secure/src/nxe_secure_dtls_psk_add.c
  ${CMAKE_CURRENT_LIST_DIR}/netxduo/nx_secure/src/nxe_secure_dtls_server_create.c
  ${CMAKE_CURRENT_LIST_DIR}/netxduo/nx_secure/src/nxe_secure_dtls_server_delete.c
  ${CMAKE_CURRENT_LIST_DIR}/netxduo/nx_secure/src/nxe_secure_dtls_server_ecc_initialize.c
  ${CMAKE_CURRENT_LIST_DIR}/netxduo/nx_secure/src/nxe_secure_dtls_server_local_certificate_add.c
  ${CMAKE_CURRENT_LIST_DIR}/netxduo/nx_secure/src/nxe_secure_dtls_server_local_certificate_remove.c
  ${CMAKE_CURRENT_LIST_DIR}/netxduo/nx_secure/src/nxe_secure_dtls_server_notify_set.c
  ${CMAKE_CURRENT_LIST_DIR}/netxduo/nx_secure/src/nxe_secure_dtls_server_protocol_version_override.c
  ${CMAKE_CURRENT_LIST_DIR}/netxduo/nx_secure/src/nxe_secure_dtls_server_psk_add.c
  ${CMAKE_CURRENT_LIST_DIR}/netxduo/nx_secure/src/nxe_secure_dtls_server_session_send.c
  ${CMAKE_CURRENT_LIST_DIR}/netxduo/nx_secure/src/nxe_secure_dtls_server_session_start.c
  ${CMAKE_CURRENT_LIST_DIR}/netxduo/nx_secure/src/nxe_secure_dtls_server_start.c
  ${CMAKE_CURRENT_LIST_DIR}/netxduo/nx_secure/src/nxe_secure_dtls_server_stop.c
  ${CMAKE_CURRENT_LIST_DIR}/netxduo/nx_secure/src/nxe_secure_dtls_server_trusted_certificate_add.c
  ${CMAKE_CURRENT_LIST_DIR}/netxduo/nx_secure/src/nxe_secure_dtls_server_trusted_certificate_remove.c
  ${CMAKE_CURRENT_LIST_DIR}/netxduo/nx_secure/src/nxe_secure_dtls_server_x509_client_verify_configure.c
  ${CMAKE_CURRENT_LIST_DIR}/netxduo/nx_secure/src/nxe_secure_dtls_server_x509_client_verify_disable.c
  ${CMAKE_CURRENT_LIST_DIR}/netxduo/nx_secure/src/nxe_secure_dtls_session_client_info_get.c
  ${CMAKE_CURRENT_LIST_DIR}/netxduo/nx_secure/src/nxe_secure_dtls_session_create.c
  ${CMAKE_CURRENT_LIST_DIR}/netxduo/nx_secure/src/nxe_secure_dtls_session_delete.c
  ${CMAKE_CURRENT_LIST_DIR}/netxduo/nx_secure/src/nxe_secure_dtls_session_end.c
  ${CMAKE_CURRENT_LIST_DIR}/netxduo/nx_secure/src/nxe_secure_dtls_session_local_certificate_add.c
  ${CMAKE_CURRENT_LIST_DIR}/netxduo/nx_secure/src/nxe_secure_dtls_session_local_certificate_remove.c
  ${CMAKE_CURRENT_LIST_DIR}/netxduo/nx_secure/src/nxe_secure_dtls_session_receive.c
  ${CMAKE_CURRENT_LIST_DIR}/netxduo/nx_secure/src/nxe_secure_dtls_session_reset.c
  ${CMAKE_CURRENT_LIST_DIR}/netxduo/nx_secure/src/nxe_secure_dtls_session_send.c
  ${CMAKE_CURRENT_LIST_DIR}/netxduo/nx_secure/src/nxe_secure_dtls_session_start.c
  ${CMAKE_CURRENT_LIST_DIR}/netxduo/nx_secure/src/nxe_secure_dtls_session_trusted_certificate_add.c
  ${CMAKE_CURRENT_LIST_DIR}/netxduo/nx_secure/src/nxe_secure_dtls_session_trusted_certificate_remove.c
  ${CMAKE_CURRENT_LIST_DIR}/netxduo/nx_secure/src/nxe_secure_tls_active_certificate_set.c
  ${CMAKE_CURRENT_LIST_DIR}/netxduo/nx_secure/src/nxe_secure_tls_client_psk_set.c
  ${CMAKE_CURRENT_LIST_DIR}/netxduo/nx_secure/src/nxe_secure_tls_local_certificate_add.c
  ${CMAKE_CURRENT_LIST_DIR}/netxduo/nx_secure/src/nxe_secure_tls_local_certificate_find.c
  ${CMAKE_CURRENT_LIST_DIR}/netxduo/nx_secure/src/nxe_secure_tls_local_certificate_remove.c
  ${CMAKE_CURRENT_LIST_DIR}/netxduo/nx_secure/src/nxe_secure_tls_metadata_size_calculate.c
  ${CMAKE_CURRENT_LIST_DIR}/netxduo/nx_secure/src/nxe_secure_tls_packet_allocate.c
  ${CMAKE_CURRENT_LIST_DIR}/netxduo/nx_secure/src/nxe_secure_tls_psk_add.c
  ${CMAKE_CURRENT_LIST_DIR}/netxduo/nx_secure/src/nxe_secure_tls_remote_certificate_allocate.c
  ${CMAKE_CURRENT_LIST_DIR}/netxduo/nx_secure/src/nxe_secure_tls_remote_certificate_buffer_allocate.c
  ${CMAKE_CURRENT_LIST_DIR}/netxduo/nx_secure/src/nxe_secure_tls_remote_certificate_free_all.c
  ${CMAKE_CURRENT_LIST_DIR}/netxduo/nx_secure/src/nxe_secure_tls_server_certificate_add.c
  ${CMAKE_CURRENT_LIST_DIR}/netxduo/nx_secure/src/nxe_secure_tls_server_certificate_find.c
  ${CMAKE_CURRENT_LIST_DIR}/netxduo/nx_secure/src/nxe_secure_tls_server_certificate_remove.c
  ${CMAKE_CURRENT_LIST_DIR}/netxduo/nx_secure/src/nxe_secure_tls_session_alert_value_get.c
  ${CMAKE_CURRENT_LIST_DIR}/netxduo/nx_secure/src/nxe_secure_tls_session_certificate_callback_set.c
  ${CMAKE_CURRENT_LIST_DIR}/netxduo/nx_secure/src/nxe_secure_tls_session_client_callback_set.c
  ${CMAKE_CURRENT_LIST_DIR}/netxduo/nx_secure/src/nxe_secure_tls_session_client_verify_disable.c
  ${CMAKE_CURRENT_LIST_DIR}/netxduo/nx_secure/src/nxe_secure_tls_session_client_verify_enable.c
  ${CMAKE_CURRENT_LIST_DIR}/netxduo/nx_secure/src/nxe_secure_tls_session_create.c
  ${CMAKE_CURRENT_LIST_DIR}/netxduo/nx_secure/src/nxe_secure_tls_session_delete.c
  ${CMAKE_CURRENT_LIST_DIR}/netxduo/nx_secure/src/nxe_secure_tls_session_end.c
  ${CMAKE_CURRENT_LIST_DIR}/netxduo/nx_secure/src/nxe_secure_tls_session_packet_buffer_set.c
  ${CMAKE_CURRENT_LIST_DIR}/netxduo/nx_secure/src/nxe_secure_tls_session_packet_pool_set.c
  ${CMAKE_CURRENT_LIST_DIR}/netxduo/nx_secure/src/nxe_secure_tls_session_protocol_version_override.c
  ${CMAKE_CURRENT_LIST_DIR}/netxduo/nx_secure/src/nxe_secure_tls_session_receive.c
  ${CMAKE_CURRENT_LIST_DIR}/netxduo/nx_secure/src/nxe_secure_tls_session_renegotiate.c
  ${CMAKE_CURRENT_LIST_DIR}/netxduo/nx_secure/src/nxe_secure_tls_session_renegotiate_callback_set.c
  ${CMAKE_CURRENT_LIST_DIR}/netxduo/nx_secure/src/nxe_secure_tls_session_reset.c
  ${CMAKE_CURRENT_LIST_DIR}/netxduo/nx_secure/src/nxe_secure_tls_session_send.c
  ${CMAKE_CURRENT_LIST_DIR}/netxduo/nx_secure/src/nxe_secure_tls_session_server_callback_set.c
  ${CMAKE_CURRENT_LIST_DIR}/netxduo/nx_secure/src/nxe_secure_tls_session_sni_extension_parse.c
  ${CMAKE_CURRENT_LIST_DIR}/netxduo/nx_secure/src/nxe_secure_tls_session_sni_extension_set.c
  ${CMAKE_CURRENT_LIST_DIR}/netxduo/nx_secure/src/nxe_secure_tls_session_start.c
  ${CMAKE_CURRENT_LIST_DIR}/netxduo/nx_secure/src/nxe_secure_tls_session_time_function_set.c
  ${CMAKE_CURRENT_LIST_DIR}/netxduo/nx_secure/src/nxe_secure_tls_session_x509_client_verify_configure.c
  ${CMAKE_CURRENT_LIST_DIR}/netxduo/nx_secure/src/nxe_secure_tls_trusted_certificate_add.c
  ${CMAKE_CURRENT_LIST_DIR}/netxduo/nx_secure/src/nxe_secure_tls_trusted_certificate_remove.c
  ${CMAKE_CURRENT_LIST_DIR}/netxduo/nx_secure/src/nxe_secure_x509_certificate_initialize.c
  ${CMAKE_CURRENT_LIST_DIR}/netxduo/nx_secure/src/nxe_secure_x509_common_name_dns_check.c
  ${CMAKE_CURRENT_LIST_DIR}/netxduo/nx_secure/src/nxe_secure_x509_crl_revocation_check.c
  ${CMAKE_CURRENT_LIST_DIR}/netxduo/nx_secure/src/nxe_secure_x509_dns_name_initialize.c
  ${CMAKE_CURRENT_LIST_DIR}/netxduo/nx_secure/src/nxe_secure_x509_extended_key_usage_extension_parse.c
  ${CMAKE_CURRENT_LIST_DIR}/netxduo/nx_secure/src/nxe_secure_x509_extension_find.c
  ${CMAKE_CURRENT_LIST_DIR}/netxduo/nx_secure/src/nxe_secure_x509_key_usage_extension_parse.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/threadx/common/inc
  ${CMAKE_CURRENT_LIST_DIR}/filex/common/inc
  ${CMAKE_CURRENT_LIST_DIR}/netxduo/common/inc
  ${CMAKE_CURRENT_LIST_DIR}/netxduo/crypto_libraries/inc
  ${CMAKE_CURRENT_LIST_DIR}/netxduo/nx_secure/inc
  ${CMAKE_CURRENT_LIST_DIR}/netxduo/nx_secure/ports
)

if((CONFIG_TOOLCHAIN STREQUAL mdk OR CONFIG_TOOLCHAIN STREQUAL iar) AND CONFIG_CORE STREQUAL cm33)
target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/filex/ports/generic/inc
)
endif()

if((CONFIG_TOOLCHAIN STREQUAL mcux OR CONFIG_TOOLCHAIN STREQUAL armgcc) AND CONFIG_CORE STREQUAL cm33)
target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/filex/ports/cortex_m33/gnu/inc
)
endif()

if(CONFIG_TOOLCHAIN STREQUAL iar AND CONFIG_CORE STREQUAL cm33)
target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/threadx/ports/cortex_m33/iar/inc
  ${CMAKE_CURRENT_LIST_DIR}/netxduo/ports/cortex_m33/iar/inc
)
endif()

if(CONFIG_TOOLCHAIN STREQUAL mdk AND CONFIG_CORE STREQUAL cm33)
target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/threadx/ports/cortex_m33/ac6/inc
  ${CMAKE_CURRENT_LIST_DIR}/netxduo/ports/cortex_m33/ac6/inc
)
endif()

if(CONFIG_TOOLCHAIN STREQUAL mcux AND CONFIG_CORE STREQUAL cm33)
target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/threadx/ports/cortex_m33/gnu/inc
  ${CMAKE_CURRENT_LIST_DIR}/netxduo/ports/cortex_m33/gnu/inc
)
endif()

if(CONFIG_USE_COMPONENT_CONFIGURATION)
  message("===>Import configuration from ${CMAKE_CURRENT_LIST_FILE}")

  target_compile_definitions(${MCUX_SDK_PROJECT_NAME} PUBLIC
    -DTX_INCLUDE_USER_DEFINE_FILE
    -DFX_INCLUDE_USER_DEFINE_FILE
    -DNX_INCLUDE_USER_DEFINE_FILE
  )

endif()
