#pragma once

#include <zephyr/device.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/toolchain.h>

#ifdef __cplusplus
extern "C" {
#endif

/* API DEL DRIVER*/
__subsystem struct our_driver_api { // definición de mi api
    int (*set_state)(const struct device *dev, bool state);
    //bool (*get_state)(const struct device *dev);
    //int (*get_gpio)(const struct device *dev);
};

//static inline our_driver_get_gpio(const struct device *dev){
//    return DEVICE_API_GET(our, dev)->get_gpio(dev);
//}

/* WRAPPER PÚBLICO*/
static inline int our_driver_set_state(const struct device *dev, bool state){
    return DEVICE_API_GET(our, dev)->set_state(dev, state);
}

//static inline our_driver_get_state(const struct device *dev){
//    return DEVICE_API_GET(our, dev)->get_state(dev);
//}

#ifdef __cplusplus
}
#endif