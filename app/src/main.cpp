/*
 * Copyright (c) 2016 Intel Corporation
 *
 * SPDX-License-Identifier: Apache-2.0
 */


#include <zephyr/kernel.h>
#include <zephyr/device.h>
#include <our_driver.h>
#include <stdio.h>


/* 1000 msec = 1 sec */
#define SLEEP_TIME_MS   1000

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
