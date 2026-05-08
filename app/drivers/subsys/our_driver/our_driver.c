#define DT_DRV_COMPAT our_driver

#include <zephyr/kernel.h>
#include <zephyr/device.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/logging/log.h>

#include <our_driver.h>

LOG_MODULE_REGISTER(our_driver, LOG_LEVEL_INF);

struct our_driver_config {
    struct gpio_dt_spec pin;
};

struct our_driver_data {
    bool is_running;
};

static int our_driver_init(const struct device *dev)
{  
    const struct our_driver_config *config = dev->config;
    if(!gpio_is_ready_dt(&config->pin)){
        return 0;
    };
    gpio_pin_configure_dt(&config->pin);
    if(CONFIG_OUR_DRIVER_INIT_STATE == 1){
        our_driver_set_state(dev, false);
    };
    return 0;
};

int our_driver_get_gpio_impl(const struct device *dev)
{
    const struct our_driver_config config = dev->config;
    return config.pin;
};

int our_driver_set_state_impl(const struct device *dev, bool on)
{
    const struct our_driver_config *config = dev->config;
    struct our_driver_data *data = dev->data;
    data = on;
    return gpio_pin_set_state(dev, state);
};

int our_driver_get_state_impl(const struct device* dev)
{
    const struct our_driver_config config = dev->config;
    return config.pin;
};

static DEVICE_API(our, our_driver_api_funcs) = {
    .set_state = our_driver_set_state_impl,
    .get_state = our_driver_get_state_impl,
    .get_gpio = our_driver_get_gpio_impl
};

#define OUR_DRIVER_DEFINE(inst)
    static struct our_driver_data data_##inst = {
            .is_running = false
    };
    static struct our_driver_config config_##inst = {
        .pin = GPIO_DT_SPEC_INST_GET(inst, drive_gpios),
    };

    DEVICE_DT_INST_DEFINE(inst,
                        our_driver_init,
                        NULL,
                        &data_##inst,
                        &config_##inst,
                        POST_KERNEL,
                        CONFIG_APPLICATION_INIT_PRIORITY,
                        &our_driver_api_funcs);

DT_INST_FOREACH_STATUS_OKAY(OUR_DRIVER_DEFINE)
