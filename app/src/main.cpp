/*
 * Probando de usar las implementaciones que provee el driver custom creado (our_sensor.h/.c)
 * referido a la clase 6 del curso de introducción a zephyr.
 */
#include <zephyr/kernel.h>
#include <zephyr/device.h>
#include <zephyr/drivers/sensor.h>
#include <our_sensor.h>
#include <stdio.h>

/* 1000 msec = 1 sec */
#define SLEEP_TIME_MS   250

//En el .dtsi está el nodo our,sensor y en C es our_sensor.
const struct device *dev = DEVICE_DT_GET_ANY(our_sensor); 

int main(void)
{
	struct sensor_value valor_recibido;
	int counter = 0;

	if (!device_is_ready(dev)) {
		return 0;
	}

	while (1) {
		// Con mi api modifico algo en la api de Sensor.
		if (counter > 9) {
			our_sensor_set_blink(dev, false);
			counter = 0;
		}
		else
			our_sensor_set_blink(dev, true);

		//tomo la muestra! (en este ejemplo hace el cambio de estado del led)
		sensor_sample_fetch(dev); 
		
		//paso la dir de memoria para que el driver escriba el valor_recibido
		sensor_channel_get(dev, SENSOR_CHAN_ALL, &valor_recibido); 
		
		printf("PIN state: %s\n", valor_recibido.val1 ? "ON" : "OFF");

		k_msleep(SLEEP_TIME_MS);
			counter++;
	}
	return 0;
}
