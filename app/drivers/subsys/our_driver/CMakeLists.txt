#if(CONFIG_OUR_DRIVER)
#    target_sources(app PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/our_driver.c)
#endif()
#zephyr_include_directories(include)

#zephyr_library()

#zephyr_library_sources_ifdef(CONFIG_OUR_DRIVER our_driver.c)

#zephyr_include_directories(include)
target_sources(app PRIVATE our_driver.c)
target_include_directories(app PRIVATE include)