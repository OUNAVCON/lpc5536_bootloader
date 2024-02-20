# Add set(CONFIG_USE_middleware_mc_pmsm_snsless_float true) in config.cmake to use this component

include_guard(GLOBAL)
message("${CMAKE_CURRENT_LIST_FILE} component is included.")

if((CONFIG_CORE STREQUAL cm33) AND CONFIG_USE_middleware_motor_control_pmsm_float_template)

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}/pmsm/pmsm_float/mc_identification/hall_calib.c
  ${CMAKE_CURRENT_LIST_DIR}/pmsm/pmsm_float/mc_identification/ke_measure.c
  ${CMAKE_CURRENT_LIST_DIR}/pmsm/pmsm_float/mc_identification/mech_measure.c
  ${CMAKE_CURRENT_LIST_DIR}/pmsm/pmsm_float/mc_identification/mid_auxiliary.c
  ${CMAKE_CURRENT_LIST_DIR}/pmsm/pmsm_float/mc_identification/mid_mc_api_connector.c
  ${CMAKE_CURRENT_LIST_DIR}/pmsm/pmsm_float/mc_identification/mid_sm_states.c
  ${CMAKE_CURRENT_LIST_DIR}/pmsm/pmsm_float/mc_identification/pp_measure.c
  ${CMAKE_CURRENT_LIST_DIR}/pmsm/pmsm_float/mc_algorithms/pmsm_control.c
  ${CMAKE_CURRENT_LIST_DIR}/pmsm/pmsm_float/state_machine/state_machine.c
  ${CMAKE_CURRENT_LIST_DIR}/pmsm/pmsm_float/mc_state_machine/m1_sm_snsless.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/pmsm/pmsm_float/mc_identification
  ${CMAKE_CURRENT_LIST_DIR}/pmsm/pmsm_float/mc_algorithms
  ${CMAKE_CURRENT_LIST_DIR}/pmsm/pmsm_float/state_machine
  ${CMAKE_CURRENT_LIST_DIR}/pmsm/pmsm_float/mc_state_machine
)

else()

message(SEND_ERROR "middleware_mc_pmsm_snsless_float dependency does not meet, please check ${CMAKE_CURRENT_LIST_FILE}.")

endif()