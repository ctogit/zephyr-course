#define DT_DRV_COMPAT our_driver

#include <zephyr/kernel.h>
#include <zephyr/device.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/sys/util.h>

#include <our_driver.h>

struct our_driver_config {
    struct gpio_dt_spec pin;
};

struct our_driver_data {
    bool state;
};

/* IMPLEMENTACIÓN DEL CALLBACK: la llama el wrapper */
static int our_driver_set_state_impl(const struct device *dev, bool state)
{
    const struct our_driver_config *config = dev->config;
    struct our_driver_data *data = dev->data;

    int ret = gpio_pin_set_dt(&config->pin, state);
    if (ret < 0)
        return ret;

    data->state = state;
    return 0;
}

/* CONECTAMOS API CON IMPLEMENTACIÓN */
//static DEVICE_API(our, our_driver_api) our_driver_api_funcs = {
//    .set_state = our_driver_set_state_impl,
//};
static const struct our_driver_api our_driver_api_funcs = {
    .set_state = our_driver_set_state_impl,
};

static int our_driver_init(const struct device *dev)
{  
    const struct our_driver_config *config = dev->config;
    if(!gpio_is_ready_dt(&config->pin)) {
        return -ENODEV;
    }
    gpio_pin_configure_dt(&config->pin, GPIO_OUTPUT_INACTIVE);
    if (IS_ENABLED(CONFIG_OUR_DRIVER_INIT_STATE)) {
        our_driver_set_state(dev, false);
    }
    return 0;
}


#define OUR_DRIVER_DEFINE(inst)                         \
    static struct our_driver_data data_##inst = {       \
        .state = false                                  \
    };                                                  \
    static struct our_driver_config config_##inst = {   \
        .pin = GPIO_DT_SPEC_INST_GET(inst, pin_gpios),  \
    };                                                  \
                                                        \
    DEVICE_DT_INST_DEFINE(inst,                         \
                        our_driver_init,                \
                        NULL,                           \
                        &data_##inst,                   \
                        &config_##inst,                 \
                        POST_KERNEL,                    \
                        CONFIG_APPLICATION_INIT_PRIORITY,\
                        &our_driver_api_funcs);         

DT_INST_FOREACH_STATUS_OKAY(OUR_DRIVER_DEFINE)
