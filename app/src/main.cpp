/*
 * Probando de usar las implementaciones que provee el driver custom creado (our_driver.h/.c)
 * referido a la clase 6 del curso de introducción a zephyr.
 */
#include <zephyr/kernel.h>
#include <zephyr/device.h>
#include <zephyr/drivers/sensor.h>
//#include <our_driver.h>
#include <stdio.h>

/* 1000 msec = 1 sec */
#define SLEEP_TIME_MS   250

const struct device *dev = DEVICE_DT_GET_ANY(our_sensor); //En el .dtsi está el nodo our,sensor y en C es our_sensor.

int main(void)
{
	struct sensor_value valor_recibido;

	if (!device_is_ready(dev)) {
		return 0;
	}

	while (1) {
		sensor_sample_fetch(dev); //tomo la muestra! (en este ejemplo hace el cambio de estado del led)
		sensor_channel_get(dev, SENSOR_CHAN_ALL, &valor_recibido); //paso la dir de memoria para que el driver escriba el valor_recibido
		printf("PIN state: %s\n", valor_recibido.val1 ? "ON" : "OFF");

		k_msleep(SLEEP_TIME_MS);
	}
	return 0;
}
