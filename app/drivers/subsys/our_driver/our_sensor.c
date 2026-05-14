#define DT_DRV_COMPAT our_sensor

#include <zephyr/kernel.h>
#include <zephyr/device.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/sys/util.h>

#include <zephyr/drivers/sensor.h>

struct our_sensor_config {
    struct gpio_dt_spec pin;
};

struct our_sensor_data {
    bool state;
};

/* MIS IMPLEMENTACIONES PRIVADAS DEL SENSOR "LED" */
static int our_sensor_sample_fetch(const struct device *dev, enum sensor_channel chan)
{
    const struct our_sensor_config *config = dev->config;
    struct our_sensor_data *data = dev->data;

    data->state = !data->state;
    int ret = gpio_pin_set_dt(&config->pin, data->state);
    if (ret < 0)
        return ret;

    return 0;
}

static int our_sensor_channel_get(const struct device *dev, enum sensor_channel chan, struct sensor_value *val)
{
    struct our_sensor_data *data = dev->data;

    val->val1 = data->state;
    val->val2 = 0;

    return 0;
}

/* CONECTAMOS API CON IMPLEMENTACIÓN */
static DEVICE_API(sensor, our_sensor_api) = {
    .sample_fetch = our_sensor_sample_fetch,
    .channel_get = our_sensor_channel_get,
};

static int our_sensor_init(const struct device *dev)
{  
    const struct our_sensor_config *config = dev->config;
    struct our_sensor_data *data = dev->data;

    if(!gpio_is_ready_dt(&config->pin)) {
        return -ENODEV;
    }
    gpio_pin_configure_dt(&config->pin, GPIO_OUTPUT_INACTIVE);
    if (IS_ENABLED(CONFIG_OUR_SENSOR_INIT_STATE)) {
        data->state = true;
    } else {
        data->state = false;
    }
    gpio_pin_set_dt(&config->pin, data->state);

    return 0;
}

#define OUR_SENSOR_DEFINE(inst)                         \
    static struct our_sensor_data data_##inst = {       \
        .state = false                                  \
    };                                                  \
    static struct our_sensor_config config_##inst = {   \
        .pin = GPIO_DT_SPEC_INST_GET(inst, pin_gpios),  \
    };                                                  \
                                                        \
    DEVICE_DT_INST_DEFINE(inst,                         \
                        our_sensor_init,                \
                        NULL,                           \
                        &data_##inst,                   \
                        &config_##inst,                 \
                        POST_KERNEL,                    \
                        CONFIG_APPLICATION_INIT_PRIORITY,\
                        &our_sensor_api);         

DT_INST_FOREACH_STATUS_OKAY(OUR_SENSOR_DEFINE)
