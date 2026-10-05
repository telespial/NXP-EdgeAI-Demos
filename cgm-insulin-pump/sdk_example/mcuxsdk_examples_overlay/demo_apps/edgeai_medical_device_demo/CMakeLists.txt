cmake_minimum_required(VERSION 3.22.0)

include(${SdkRootDirPath}/cmake/extension/mcux.cmake)

project(edgeai_medical_device_demo LANGUAGES C CXX ASM PROJECT_BOARD_PORT_PATH ${board_root}/${board}/demo_apps/edgeai_medical_device_demo)

include(${SdkRootDirPath}/CMakeLists.txt)

if(DEFINED ENV{EDGEAI_MEDICAL_DEVICE_DEMO_ROOT})
    set(EDGEAI_ROOT "$ENV{EDGEAI_MEDICAL_DEVICE_DEMO_ROOT}")
else()
    get_filename_component(EDGEAI_ROOT "${SdkRootDirPath}/../.." ABSOLUTE)
endif()

mcux_add_source(
    BASE_PATH ${EDGEAI_ROOT}
    SOURCES src/gauge_style.c
            src/power_data_source.c
            src/cgm_preprocess.c
            src/gauge_render.c
            src/fxls8974cf.c
            src/ext_flash_recorder.c
            src/anomaly_engine.c
            src/eil_profile.c
            src/par_lcd_s035.c
            src/text5x7.c
)

if(EDGEAI_TIMEBASE_TEST_MODE)
    mcux_add_source(
        BASE_PATH ${EDGEAI_ROOT}
        SOURCES src/timebase_test_main.c
    )
else()
    mcux_add_source(
        BASE_PATH ${EDGEAI_ROOT}
        SOURCES src/edgeai_medical_device_demo.c
    )
endif()

mcux_add_include(
    BASE_PATH ${EDGEAI_ROOT}
    INCLUDES src
)

mcux_add_source(
    BASE_PATH ${SdkRootDirPath}
    SOURCES components/touch/gt911/fsl_gt911.c
            drivers/ostimer/fsl_ostimer.c
)

mcux_add_include(
    BASE_PATH ${SdkRootDirPath}
    INCLUDES drivers/ostimer
)

mcux_add_include(
    BASE_PATH ${SdkRootDirPath}
    INCLUDES components/touch/gt911
)

include(${SdkRootDirPath}/${board_root}/${board}/demo_apps/edgeai_medical_device_demo/reconfig.cmake OPTIONAL)

option(EDGEAI_SENSOR_SCAN_MODE "Build firmware in UART-only sensor scan mode" OFF)
option(EDGEAI_SHIELD_SCAN_DIAG "Enable broad shield datastream diagnostics" OFF)
option(EDGEAI_SHIELD_SENSOR_SCAN_LOG "Enable shield sensor probe logging" OFF)
option(EDGEAI_TIMEBASE_TEST_MODE "Build firmware in 32k crystal elapsed-time test mode" OFF)

if(EDGEAI_SENSOR_SCAN_MODE)
    add_compile_definitions(EDGEAI_SENSOR_SCAN_MODE=1)
endif()
if(EDGEAI_SHIELD_SCAN_DIAG)
    add_compile_definitions(EDGEAI_ENABLE_SHIELD_SCAN_DIAG=1)
endif()
if(EDGEAI_SHIELD_SENSOR_SCAN_LOG)
    add_compile_definitions(EDGEAI_ENABLE_SHIELD_SENSOR_SCAN_LOG=1)
endif()
if(EDGEAI_TIMEBASE_TEST_MODE)
    add_compile_definitions(EDGEAI_TIMEBASE_TEST_MODE=1)
endif()

mcux_convert_binary(BINARY ${APPLICATION_BINARY_DIR}/${MCUX_SDK_PROJECT_NAME}.bin)
