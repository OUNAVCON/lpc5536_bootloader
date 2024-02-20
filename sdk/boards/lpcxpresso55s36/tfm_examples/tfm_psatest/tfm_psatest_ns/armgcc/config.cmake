# config to select component, the format is CONFIG_USE_${component}
# Please refer to cmake files below to get available components:
#  ${SdkRootDirPath}/devices/LPC55S36/all_lib_device.cmake

set(CONFIG_COMPILER gcc)
set(CONFIG_TOOLCHAIN armgcc)
set(CONFIG_USE_COMPONENT_CONFIGURATION false)
set(CONFIG_USE_middleware_tfm_ns_profile_medium true)
set(CONFIG_USE_middleware_tfm_ns true)
set(CONFIG_USE_middleware_psatest_ns true)
set(CONFIG_USE_middleware_psatest_ns_initial_attestation true)
set(CONFIG_USE_middleware_psatest_ns_crypto_profile_medium true)
set(CONFIG_USE_middleware_psatest_ns_crypto true)
set(CONFIG_USE_middleware_psatest_ns_internal_trusted_storage true)
set(CONFIG_USE_driver_common true)
set(CONFIG_USE_driver_clock true)
set(CONFIG_USE_driver_power true)
set(CONFIG_USE_driver_reset true)
set(CONFIG_USE_driver_lpc_iocon true)
set(CONFIG_USE_device_LPC55S36_CMSIS true)
set(CONFIG_USE_driver_flexcomm_usart true)
set(CONFIG_USE_driver_flexcomm true)
set(CONFIG_USE_driver_lpc_gpio true)
set(CONFIG_USE_utility_assert true)
set(CONFIG_USE_utility_debug_console true)
set(CONFIG_USE_component_usart_adapter true)
set(CONFIG_USE_component_serial_manager_uart true)
set(CONFIG_USE_component_serial_manager true)
set(CONFIG_USE_component_lists true)
set(CONFIG_USE_utilities_misc_utilities true)
set(CONFIG_USE_middleware_tfmtests_ns true)
set(CONFIG_USE_CMSIS_RTOS2_NonSecure true)
set(CONFIG_USE_middleware_tfm_ns_lpcxpresso55s36 true)
set(CONFIG_USE_CMSIS_Device_API_OSTick true)
set(CONFIG_USE_CMSIS_Device_API_RTOS2 true)
set(CONFIG_USE_middleware_psatest_ns_t_cose true)
set(CONFIG_USE_middleware_tfm_qcbor true)
set(CONFIG_USE_CMSIS_Include_core_cm true)
set(CONFIG_CORE cm33)
set(CONFIG_DEVICE LPC55S36)
set(CONFIG_BOARD lpcxpresso55s36)
set(CONFIG_KIT lpcxpresso55s36)
set(CONFIG_DEVICE_ID LPC55S36)
set(CONFIG_FPU SP_FPU)
set(CONFIG_DSP DSP)
set(CONFIG_TRUSTZONE NO_TZ)
