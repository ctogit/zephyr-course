#pragma once

#include <zephyr/device.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/toolchain.h>

#ifdef __cplusplus
extern "C" {
#endif

/* API DEL DRIVER*/
__subsystem struct our_sensor_driver_api {
    struct sensor_driver_api sensor_api;

    int (*set_blink)(const struct device *dev, bool enable);
};

/* WRAPPER PÚBLICO*/
static inline int our_sensor_set_blink(const struct device *dev, bool enable){
    return DEVICE_API_GET(our_sensor, dev)->set_blink(dev, enable);
}

#ifdef __cplusplus
}
#endif