cmake_minimum_required(VERSION 3.20.0)

list(APPEND BOARD_ROOT ${CMAKE_CURRENT_SOURCE_DIR})
#list(APPEND DTS_ROOT ${CMAKE_CURRENT_SOURCE_DIR})
#set(KCONFIG_ROOT ${CMAKE_CURRENT_SOURCE_DIR}/Kconfig)

find_package(Zephyr REQUIRED)
project(my_zephyr_app)
target_sources(app PRIVATE src/main.cpp)

#message(FATAL_ERROR "ANTES DEL SUBDIR")
#add_subdirectory(drivers/subsys/our_driver/include)
#message(FATAL_ERROR "DESPUES DEL SUBDIR")


