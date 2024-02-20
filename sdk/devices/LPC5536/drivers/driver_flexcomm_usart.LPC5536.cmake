# Add set(CONFIG_USE_driver_flexcomm_usart true) in config.cmake to use this component

include_guard(GLOBAL)
message("${CMAKE_CURRENT_LIST_FILE} component is included.")

if(CONFIG_USE_driver_flexcomm AND (CONFIG_DEVICE_ID STREQUAL LPC5536))

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}/fsl_usart.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/.
)

else()

message(SEND_ERROR "driver_flexcomm_usart.LPC5536 dependency does not meet, please check ${CMAKE_CURRENT_LIST_FILE}.")

endif()