/*
 * l7: sobre la api sensor (sample_fetch y channel_get) extiendida con 
 * una implemetación propia (set_blink) se integra SHELL y se usa esa 
 * implementación propia para habilitar o deshabilitar el parpadeo del 
 * LED desde consola serie.
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
		
	//printf("PIN status: %s\n", valor_recibido.val1 ? "OFF" : "ON");
	shell_fprintf(sh, SHELL_INFO, "Valor: %s\n", valor_recibido.val1);
	return 0;
}

static int info_subcmd(const struct shell *sh, size_t argc, char **argv) {
	ARG_UNUSED(argc);
	ARG_UNUSED(argv);
	shell_print(sh, "Sensor LED commands");
	return 0;
}

int main(void)
{
	
	//int counter = 0;

	if (!device_is_ready(dev)) {
		return 0;
	}

	while (1) {
		// Esto no va más porque ahora lo hago desde SHELL!
		/*if (counter >= 0 && counter <= 10) {
			our_sensor_set_blink(dev, true);
		}
		else if(counter > 10 && counter <= 20) {
			our_sensor_set_blink(dev, false);
			if (counter >= 20)
				counter = 0;
		}*/
			
		//tomo la muestra! (en este ejemplo hace el cambio de estado del led)
		//sensor_sample_fetch(dev); 
		
		//paso la dir de memoria para que el driver escriba el valor_recibido
		//sensor_channel_get(dev, SENSOR_CHAN_ALL, &valor_recibido); 
		
		//printf("PIN status: %s\n", valor_recibido.val1 ? "OFF" : "ON");

		k_msleep(SLEEP_TIME_MS);

		//counter++;
	}
	return 0;
}

SHELL_STATIC_SUBCMD_SET_CREATE(
	sub_commands,
	SHELL_CMD(info, NULL, "Device name and ready state", info_subcmd),
	SHELL_CMD(fetch, NULL, "Sensor sample fetch: led", fetch_subcmd),
	SHELL_CMD(read, NULL, "Sensor channel get: led state", read_subcmd),
	SHELL_SUBCMD_SET_END
);

SHELL_CMD_REGISTER(sensor, &sub_commands, "Sensor root shell", cmd_sensor);
