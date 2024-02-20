# Add set(CONFIG_USE_middleware_usb_host_ohci_config_header true) in config.cmake to use this component

include_guard(GLOBAL)
message("${CMAKE_CURRENT_LIST_FILE} component is included.")

if((CONFIG_DEVICE_ID STREQUAL LPC5534 OR CONFIG_DEVICE_ID STREQUAL LPC5536 OR CONFIG_DEVICE_ID STREQUAL LPC55S36))

add_config_file(${CMAKE_CURRENT_LIST_DIR}/output/npw/host_config/ohci/usb_host_config.h ${CMAKE_CURRENT_LIST_DIR}/output/npw/host_config/ohci middleware_usb_host_ohci_config_header)

else()

message(SEND_ERROR "middleware_usb_host_ohci_config_header dependency does not meet, please check ${CMAKE_CURRENT_LIST_FILE}.")

endif()