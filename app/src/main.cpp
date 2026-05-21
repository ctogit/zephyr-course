/*
 * l7-task1: sobre la api sensor (sample_fetch y channel_get) se integra 
 * SHELL y se crea comando raiz sensor y los siguientes subcomandos:
 * - leer: imprime información de la placa, driver y estado.
 * - fetch: muestrear el sensor (toggle led) - API SENSOR.
 * - read: leer la muestra - API SENSOR.
 */

#include <zephyr/kernel.h>
#include <zephyr/device.h>
#include <zephyr/drivers/sensor.h>
#include <our_sensor.h>
#include <stdio.h>
#include <zephyr/shell/shell.h>

/* 1000 msec = 1 sec */
#define SLEEP_TIME_MS   100

//En el .dtsi está el nodo our,sensor y en C es our_sensor.
const struct device *dev = DEVICE_DT_GET_ANY(our_sensor); 

static int cmd_sensor(const struct shell *sh, size_t argc, char **argv) {
	ARG_UNUSED(argc);
	ARG_UNUSED(argv);
	shell_print(sh, "Hello from shell");
	return 0;
}

static int fetch_subcmd(const struct shell *sh, size_t argc, char **argv) {
	ARG_UNUSED(argc);
	ARG_UNUSED(argv);
	sensor_sample_fetch(dev);
	shell_print(sh, "Sensor sample fetch command");
	return 0;
}

static int read_subcmd(const struct shell *sh, size_t argc, char **argv) {
	struct sensor_value valor_recibido;
	ARG_UNUSED(argc);
	ARG_UNUSED(argv);

	sensor_channel_get(dev, SENSOR_CHAN_ALL, &valor_recibido); 	
	shell_fprintf(sh, SHELL_INFO, "Valor: %s\n", valor_recibido.val1 ? "ON" : "OFF");
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

		k_msleep(SLEEP_TIME_MS);

	}
	return 0;
}

SHELL_STATIC_SUBCMD_SET_CREATE(
	sub_commands,
	SHELL_CMD(info, NULL, "Print board, device name and ready state", info_subcmd),
	SHELL_CMD(fetch, NULL, "Sensor sample fetch: led", fetch_subcmd),
	SHELL_CMD(read, NULL, "Sensor channel get: led state", read_subcmd),
	SHELL_SUBCMD_SET_END
);

SHELL_CMD_REGISTER(sensor, &sub_commands, "Sensor root shell", cmd_sensor);
