function(set_library LIBRARY_TYPE LANGUAGE)
set(EXTRADEFINES " -fstack-usage ")

if(${LIBRARY_TYPE} STREQUAL "REDLIB")
    set(SPECS "-specs=redlib.specs" PARENT_SCOPE)
    set(EXTRADEFINES "${EXTRADEFINES} -D__REDLIB__")
    set(TARGET_LINK_SYSTEM_LIBRARIES "-lcr_c -lcr_eabihelpers -lgcc" PARENT_SCOPE)
elseif(${LIBRARY_TYPE} STREQUAL "NEWLIB")
    set(EXTRADEFINES "${EXTRADEFINES} -D__NEWLIB__")
    if(${LANGUAGE} STREQUAL "CPP")
        set(TARGET_LINK_SYSTEM_LIBRARIES "-lstdc++ crti.o crtn.o crtbegin.o crtend.o" PARENT_SCOPE)
    else()
        set(TARGET_LINK_SYSTEM_LIBRARIES "-lgcc -lc -lm" PARENT_SCOPE)
    endif()
elseif(${LIBRARY_TYPE} STREQUAL "NEWLIB_NANO")
    set(SPECS "--specs=nano.specs" PARENT_SCOPE)
    set(EXTRADEFINES "${EXTRADEFINES} -D__NEWLIB__")
    if(${LANGUAGE} STREQUAL "CPP")
        set(TARGET_LINK_SYSTEM_LIBRARIES "-lstdc++_nano crti.o crtn.o crtbegin.o crtend.o" PARENT_SCOPE)
    else()
        set(TARGET_LINK_SYSTEM_LIBRARIES "-lgcc -lc_nano -lm" PARENT_SCOPE)
    endif()
endif()

set(CMAKE_ASM_FLAGS " ${CMAKE_ASM_FLAGS} ${EXTRADEFINES}" PARENT_SCOPE)
set(CMAKE_C_FLAGS " ${CMAKE_C_FLAGS} ${EXTRADEFINES}" PARENT_SCOPE)
set(CMAKE_CXX_FLAGS " ${CMAKE_CXX_FLAGS} ${EXTRADEFINES}" PARENT_SCOPE)
endfunction()

function(set_floating_point FPU_TYPE FPU_ABI)
if(${FPU_TYPE} MATCHES "FPV4-SP-D16")
    set(FPU "-fsingle-precision-constant -mfpu=fpv4-sp-d16")
elseif(${FPU_TYPE} MATCHES "FPV5-D16")
    set(FPU "-fsingle-precision-constant -mfpu=fpv5-d16")
elseif(${FPU_TYPE} MATCHES "FPV5-SP-D16")
    set(FPU "-fsingle-precision-constant -mfpu=fpv5-sp-d16")
endif()
if(${FPU_ABI} MATCHES "HARD")
    set(FPU "${FPU} -mfloat-abi=hard" PARENT_SCOPE)
elseif(${FPU_ABI} MATCHES "SOFT")
    set(FPU "${FPU} -mfloat-abi=softfp" PARENT_SCOPE)
else()
    set(FPU "${FPU}" PARENT_SCOPE)
endif()
endfunction()

function(set_debug_console DEBUG_CONSOLE LIBRARY_TYPE)
if(${DEBUG_CONSOLE} MATCHES "SEMIHOST")
    set(DEBUG_CONSOLE_CONFIG "-DSDK_DEBUGCONSOLE=0 -DSDK_USE_SYSCALL_STUB=0" PARENT_SCOPE)
else()
    set(DEBUG_CONSOLE_CONFIG "-DSDK_DEBUGCONSOLE=1" PARENT_SCOPE)
endif()

if(${LIBRARY_TYPE} STREQUAL "NEWLIB" OR ${LIBRARY_TYPE} STREQUAL "NEWLIB_NANO")
    if(${DEBUG_CONSOLE} STREQUAL "SEMIHOST")
        set(TARGET_LINK_SYSTEM_LIBRARIES "${TARGET_LINK_SYSTEM_LIBRARIES} -lcr_newlib_semihost" PARENT_SCOPE)
    elseif(${DEBUG_CONSOLE} STREQUAL "UART" OR ${DEBUG_CONSOLE} STREQUAL "NOHOST")
        set(TARGET_LINK_SYSTEM_LIBRARIES "${TARGET_LINK_SYSTEM_LIBRARIES} -lcr_newlib_nohost" PARENT_SCOPE)
    elseif(${DEBUG_CONSOLE} STREQUAL "NONE")
        set(TARGET_LINK_SYSTEM_LIBRARIES "${TARGET_LINK_SYSTEM_LIBRARIES} -lcr_newlib_none" PARENT_SCOPE)
    endif()
elseif(${LIBRARY_TYPE} STREQUAL "REDLIB")
    if(${DEBUG_CONSOLE} STREQUAL "SEMIHOST")
        set(TARGET_LINK_SYSTEM_LIBRARIES "${TARGET_LINK_SYSTEM_LIBRARIES} -lcr_semihost" PARENT_SCOPE)
    elseif(${DEBUG_CONSOLE} STREQUAL "SEMIHOST_NF")
        set(TARGET_LINK_SYSTEM_LIBRARIES "${TARGET_LINK_SYSTEM_LIBRARIES} -lcr_semihost_nf" PARENT_SCOPE)
    elseif(${DEBUG_CONSOLE} STREQUAL "SEMIHOST_MB")
        set(TARGET_LINK_SYSTEM_LIBRARIES "${TARGET_LINK_SYSTEM_LIBRARIES} -lcr_semihost_mb" PARENT_SCOPE)
    elseif(${DEBUG_CONSOLE} STREQUAL "SEMIHOST_MB_NF")
        set(TARGET_LINK_SYSTEM_LIBRARIES "${TARGET_LINK_SYSTEM_LIBRARIES} -lcr_semihost_mb_nf" PARENT_SCOPE)
    elseif(${DEBUG_CONSOLE} STREQUAL "UART" OR ${DEBUG_CONSOLE} STREQUAL "NOHOST_NF" OR ${DEBUG_CONSOLE} STREQUAL "NOHOST")
        set(TARGET_LINK_SYSTEM_LIBRARIES "${TARGET_LINK_SYSTEM_LIBRARIES} -lcr_nohost_nf" PARENT_SCOPE)
    endif()
endif()
endfunction()

function(include_if_use module)
    set(MATCHED false)
    if(${CONFIG_USE_${module}})
        set(MATCHED true)
    endif()
    # In case that module file name has device/board/kit suffix
    if(NOT MATCHED)
        string(REGEX REPLACE ".${CONFIG_DEVICE}$" "" replVar ${module})
        if(${CONFIG_USE_${replVar}})
            set(MATCHED true)
        endif()
    endif()
    if(NOT MATCHED)
        string(REGEX REPLACE ".${CONFIG_BOARD}$" "" replVar ${module})
        if(${CONFIG_USE_${replVar}})
            set(MATCHED true)
        endif()
    endif()
    if(NOT MATCHED)
        string(REGEX REPLACE ".${CONFIG_KIT}$" "" replVar ${module})
        if(${CONFIG_USE_${replVar}})
            set(MATCHED true)
        endif()
    endif()

    if(MATCHED)
        include(${module} OPTIONAL RESULT_VARIABLE loaded_file)
        if(EXISTS ${loaded_file})
            return()
        else()
            message(SEND_ERROR "${module}.cmake does not exist.")
        endif()
    endif()
endfunction()

function(add_config_file CONFIG_FILE INCLUDE_PATH MODULE_NAME)
    get_target_property(PROJECT_SOURCES ${MCUX_SDK_PROJECT_NAME} SOURCES)
    get_filename_component(BASE_NAME ${CONFIG_FILE} NAME)

    foreach(PROJ_FILE ${PROJECT_SOURCES})
        string(FIND "${PROJ_FILE}" "${BASE_NAME}" CONFIG_FILE_INDEX)
        if(${CONFIG_FILE_INDEX} GREATER -1)
            get_source_file_property(CONFIG_FILE_PROPERTY "${PROJ_FILE}" COMPONENT_CONFIG_FILE)
            if(${CONFIG_FILE_PROPERTY} MATCHES "(^${MODULE_NAME}$)|(^${MODULE_NAME} )|( ${MODULE_NAME} )|( ${MODULE_NAME}$)")
                message("Skip ${CONFIG_FILE} in ${MODULE_NAME} because user-defined file ${PROJ_FILE} has been added into project.")
                return()
            endif()
        endif()
    endforeach()

    message("Use ${CONFIG_FILE} in ${MODULE_NAME}.")
    target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE ${CONFIG_FILE})
    if(NOT ${INCLUDE_PATH} STREQUAL "")
      target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC ${INCLUDE_PATH})
    endif()
endfunction()
