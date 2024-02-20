# Add set(CONFIG_USE_component_els_pkc_platform_lpc true) in config.cmake to use this component

include_guard(GLOBAL)
message("${CMAKE_CURRENT_LIST_FILE} component is included.")

if((CONFIG_DEVICE_ID STREQUAL LPC55S36) AND CONFIG_USE_component_els_pkc AND CONFIG_USE_component_els_pkc_standalone_gdet)

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}/src/platforms/lpc/mcux_els.c
  ${CMAKE_CURRENT_LIST_DIR}/src/platforms/lpc/mcux_pkc.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/.
  ${CMAKE_CURRENT_LIST_DIR}/src/platforms/lpc
  ${CMAKE_CURRENT_LIST_DIR}/src/platforms/lpc/inc
)

else()

message(SEND_ERROR "component_els_pkc_platform_lpc dependency does not meet, please check ${CMAKE_CURRENT_LIST_FILE}.")

endif()