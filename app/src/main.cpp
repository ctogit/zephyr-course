/*
 * l7-task2: se usa shell para habilitar/desabilitar el sample_fetch (toggle led)
 * con la api our_sensor (que extiende a api sensor oficial de zephyr). Se validan
 * argumentos del sub-comando blink para que solo se ingresen los valores y cantidades
 * correctas.
 * SENSOR
 * 		|_INFO
 * 		|_BLINK -> (ON/OFF) (50-1000)
 */

#include <zephyr/kernel.h>
#include <zephyr/device.h>
#include <zephyr/drivers/sensor.h>
#include <our_sensor.h>
#include <stdio.h>
#include <zephyr/shell/shell.h>

/* Variable global para compartir con el thread del shell y del main */
static int sleep_time_ms = 500;

//En el .dtsi está el nodo our,sensor y en C es our_sensor.
const struct device *dev = DEVICE_DT_GET_ANY(our_sensor); 

/* COMANDO RAIZ */
static int cmd_sensor(const struct shell *sh, size_t argc, char **argv) {
	ARG_UNUSED(argc);
	ARG_UNUSED(argv);
	shell_print(sh, "Hello from shell");
	return 0;
}

static int blink_subcmd(const struct shell *sh, size_t argc, char **argv) {
	ARG_UNUSED(argc);

	bool enable;
	int value = atoi(argv[2]);
	// Validamos argumentos: argv[0]: blink (fijo); argv[1]: on/off (variable);
	// argv[2]: ms
	if (value < 50 || value > 1000) {
		shell_error(sh, "Range: 50-1000 ms");
		return -EINVAL;
	}
	
	if(!strcmp(argv[1], "on")) {
		enable = true;
	}
	else if(!strcmp(argv[1], "off")) {
		enable = false;
	}
	else {
		shell_error(sh, "Invalid argument, use on/off");
		return -EINVAL;
	}
	
	sleep_time_ms = value;
	our_sensor_set_blink(dev, enable); 	
	shell_fprintf(sh, SHELL_INFO, "Blink: %s\n", enable ? "ON" : "OFF");
	return 0;
}

static int info_subcmd(const struct shell *sh, size_t argc, char **argv) {
	ARG_UNUSED(argc);
	ARG_UNUSED(argv);
	bool status = device_is_ready(dev);
	shell_fprintf(sh, SHELL_INFO, "Board: %s\n", CONFIG_BOARD_TARGET);
	shell_fprintf(sh, SHELL_INFO, "Device: %s\n", dev->name);
	shell_fprintf(sh, SHELL_INFO, "state: %s\n", status ? "Ready" : "Not ready");
	return 0;
}

int main(void)
{
	if (!device_is_ready(dev)) {
		return 0;
	}

	while (1) {
		sensor_sample_fetch(dev);
		k_msleep(sleep_time_ms);
	}
	return 0;
}

SHELL_STATIC_SUBCMD_SET_CREATE(
	sub_commands,
	SHELL_CMD(info, NULL, "Print board, device name and ready state", info_subcmd),
	SHELL_CMD_ARG(blink, NULL, "Enable/disable blink", blink_subcmd, 3, 0),
	SHELL_SUBCMD_SET_END
);

SHELL_CMD_REGISTER(sensor, &sub_commands, "Sensor root shell", cmd_sensor);
