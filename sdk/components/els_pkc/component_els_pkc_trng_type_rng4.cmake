# Add set(CONFIG_USE_component_els_pkc_trng_type_rng4 true) in config.cmake to use this component

include_guard(GLOBAL)
message("${CMAKE_CURRENT_LIST_FILE} component is included.")

if(CONFIG_USE_component_els_pkc_trng)

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}/src/comps/mcuxClTrng/src/mcuxClTrng_RNG4.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/.
  ${CMAKE_CURRENT_LIST_DIR}/src/comps/mcuxClTrng/inc
  ${CMAKE_CURRENT_LIST_DIR}/src/comps/mcuxClTrng/inc/internal
)

else()

message(SEND_ERROR "component_els_pkc_trng_type_rng4 dependency does not meet, please check ${CMAKE_CURRENT_LIST_FILE}.")

endif()
