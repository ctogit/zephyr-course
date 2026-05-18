if(CONFIG_OUR_SENSOR)
    target_sources(app PRIVATE our_sensor.c)
endif()
target_include_directories(app PRIVATE include)

