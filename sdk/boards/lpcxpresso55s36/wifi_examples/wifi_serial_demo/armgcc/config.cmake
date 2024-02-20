# config to select component, the format is CONFIG_USE_${component}
# Please refer to cmake files below to get available components:
#  ${SdkRootDirPath}/devices/LPC55S36/all_lib_device.cmake

set(CONFIG_COMPILER gcc)
set(CONFIG_TOOLCHAIN armgcc)
set(CONFIG_USE_COMPONENT_CONFIGURATION false)
set(CONFIG_USE_middleware_freertos-kernel_cm33_non_trustzone true)
set(CONFIG_USE_component_serial_mwm_usart true)
set(CONFIG_USE_component_serial_mwm true)
set(CONFIG_USE_middleware_freertos-kernel_heap_4 true)
set(CONFIG_USE_middleware_freertos-kernel true)
set(CONFIG_USE_driver_clock true)
set(CONFIG_USE_driver_common true)
set(CONFIG_USE_device_LPC55S36_CMSIS true)
set(CONFIG_USE_device_LPC55S36_startup true)
set(CONFIG_USE_driver_flexcomm_usart true)
set(CONFIG_USE_driver_flexcomm true)
set(CONFIG_USE_driver_lpc_iocon true)
set(CONFIG_USE_driver_lpc_gpio true)
set(CONFIG_USE_driver_power true)
set(CONFIG_USE_utility_assert true)
set(CONFIG_USE_utility_debug_console true)
set(CONFIG_USE_component_usart_adapter true)
set(CONFIG_USE_component_serial_manager_uart true)
set(CONFIG_USE_component_serial_manager true)
set(CONFIG_USE_component_lists true)
set(CONFIG_USE_utilities_misc_utilities true)
set(CONFIG_USE_driver_flexcomm_usart_freertos true)
set(CONFIG_USE_middleware_freertos-kernel_template true)
set(CONFIG_USE_middleware_freertos-kernel_extension true)
set(CONFIG_USE_driver_reset true)
set(CONFIG_USE_CMSIS_Include_core_cm true)
set(CONFIG_USE_device_LPC55S36_system true)
set(CONFIG_CORE cm33)
set(CONFIG_DEVICE LPC55S36)
set(CONFIG_BOARD lpcxpresso55s36)
set(CONFIG_KIT lpcxpresso55s36)
set(CONFIG_DEVICE_ID LPC55S36)
set(CONFIG_FPU SP_FPU)
set(CONFIG_DSP DSP)
