# Add set(CONFIG_USE_driver_soc_mipi_dsi true) in config.cmake to use this component

include_guard(GLOBAL)
message("${CMAKE_CURRENT_LIST_FILE} component is included.")

if(CONFIG_USE_driver_common AND (CONFIG_DEVICE_ID STREQUAL MIMXRT1176xxxxx))

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
${CMAKE_CURRENT_LIST_DIR}/
)

else()

message(SEND_ERROR "driver_soc_mipi_dsi.MIMXRT1176 dependency does not meet, please check ${CMAKE_CURRENT_LIST_FILE}.")

endif()
