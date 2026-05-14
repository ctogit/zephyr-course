/*
 * Probando de usar las implementaciones que provee el driver custom creado (our_driver.h/.c)
 * referido a la clase 6 del curso de introducción a zephyr.
 */
#include <zephyr/kernel.h>
#include <zephyr/device.h>
#include <our_driver.h>
#include <stdio.h>

/* 1000 msec = 1 sec */
#define SLEEP_TIME_MS   250

const struct device *dev = DEVICE_DT_GET_ANY(our_driver);

int main(void)
{
	bool state = false;

	if (!device_is_ready(dev)) {
		return 0;
	}

	while (1) {
        state = !state;
		our_driver_set_state(dev, state);
		
		printf("PIN state: %s\n", state ? "ON" : "OFF");

		k_msleep(SLEEP_TIME_MS);
	}
	return 0;
}
