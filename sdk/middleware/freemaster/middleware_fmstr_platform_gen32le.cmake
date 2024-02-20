# Add set(CONFIG_USE_middleware_fmstr_platform_gen32le true) in config.cmake to use this component

include_guard(GLOBAL)
message("${CMAKE_CURRENT_LIST_FILE} component is included.")

if(CONFIG_USE_middleware_fmstr AND CONFIG_USE_middleware_fmstr_npw_cfg_gen32le)

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}/src/drivers/mcuxsdk/can/freemaster_flexcan.c
  ${CMAKE_CURRENT_LIST_DIR}/src/drivers/mcuxsdk/can/freemaster_mscan.c
  ${CMAKE_CURRENT_LIST_DIR}/src/drivers/mcuxsdk/can/freemaster_mcan.c
  ${CMAKE_CURRENT_LIST_DIR}/src/drivers/mcuxsdk/serial/freemaster_serial_uart.c
  ${CMAKE_CURRENT_LIST_DIR}/src/drivers/mcuxsdk/serial/freemaster_serial_lpsci.c
  ${CMAKE_CURRENT_LIST_DIR}/src/drivers/mcuxsdk/serial/freemaster_serial_lpuart.c
  ${CMAKE_CURRENT_LIST_DIR}/src/drivers/mcuxsdk/serial/freemaster_serial_usart.c
  ${CMAKE_CURRENT_LIST_DIR}/src/drivers/mcuxsdk/serial/freemaster_serial_miniusart.c
  ${CMAKE_CURRENT_LIST_DIR}/src/drivers/mcuxsdk/serial/freemaster_serial_usb.c
  ${CMAKE_CURRENT_LIST_DIR}/src/drivers/mcuxsdk/network/freemaster_net_segger_rtt.c
  ${CMAKE_CURRENT_LIST_DIR}/src/drivers/mcuxsdk/network/freemaster_net_lwip_udp.c
  ${CMAKE_CURRENT_LIST_DIR}/src/drivers/mcuxsdk/network/freemaster_net_lwip_tcp.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/src/platforms/gen32le
  ${CMAKE_CURRENT_LIST_DIR}/src/drivers/mcuxsdk/can
  ${CMAKE_CURRENT_LIST_DIR}/src/drivers/mcuxsdk/serial
)

else()

message(SEND_ERROR "middleware_fmstr_platform_gen32le dependency does not meet, please check ${CMAKE_CURRENT_LIST_FILE}.")

endif()