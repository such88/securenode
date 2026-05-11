cmake_minimum_required(VERSION 3.20.0)

# Auto-load board-specific overlay if it exists
set(BOARD_OVERLAY ${CMAKE_CURRENT_SOURCE_DIR}/overlays/${BOARD}.overlay)
if(EXISTS ${BOARD_OVERLAY})
    set(DTC_OVERLAY_FILE ${BOARD_OVERLAY})
endif()

# Auto-load board-specific conf if it exists
set(BOARD_CONF ${CMAKE_CURRENT_SOURCE_DIR}/config/${BOARD}.conf)
if(EXISTS ${BOARD_CONF})
    set(CONF_FILE ${CMAKE_CURRENT_SOURCE_DIR}/prj.conf ${BOARD_CONF})
endif()

find_package(Zephyr REQUIRED HINTS $ENV{ZEPHYR_BASE})
project(securenode VERSION 1.0.0)

target_include_directories(app PRIVATE include)
target_sources(app PRIVATE src/main.c)
