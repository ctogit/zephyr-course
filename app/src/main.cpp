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

static int cmd_demo_salute(const struct shell *sh, size_t argc, char **argv) {
	ARG_UNUSED(argc);
	ARG_UNUSED(argv);
	shell_print(sh, "Hello from shell");
	return 0;
}

static int hi_subcmd(const struct shell *sh, size_t argc, char **argv) {
	ARG_UNUSED(argc);
	ARG_UNUSED(argv);
	shell_print(sh, "Hi there");
	return 0;
}

static int bu_subcmd(const struct shell *sh, size_t argc, char **argv) {
	ARG_UNUSED(argc);
	ARG_UNUSED(argv);
	shell_print(sh, "Buenas pibe");
	return 0;
}

static int noblink_subcmd(const struct shell *sh, size_t argc, char **argv) {
	ARG_UNUSED(argc);
	ARG_UNUSED(argv);
	shell_print(sh, "Parpadeo LED -> OFF");
	our_sensor_set_blink(dev, false);
	return 0;
}

static int blink_subcmd(const struct shell *sh, size_t argc, char **argv) {
	ARG_UNUSED(argc);
	ARG_UNUSED(argv);
	shell_print(sh, "Parpadeo LED ->  ON");
	our_sensor_set_blink(dev, true);
	return 0;
}

int main(void)
{
	struct sensor_value valor_recibido;
	int counter = 0;

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
		sensor_sample_fetch(dev); 
		
		//paso la dir de memoria para que el driver escriba el valor_recibido
		sensor_channel_get(dev, SENSOR_CHAN_ALL, &valor_recibido); 
		
		//printf("PIN status: %s\n", valor_recibido.val1 ? "OFF" : "ON");

		k_msleep(SLEEP_TIME_MS);

		counter++;
	}
	return 0;
}

SHELL_STATIC_SUBCMD_SET_CREATE(
	sub_commands,
	SHELL_CMD(hi, NULL, "Gringou salute", hi_subcmd),
	SHELL_CMD(buenas, NULL, "Saludo argento", bu_subcmd),
	SHELL_CMD(noblink, NULL, "Parpadeo LED off", noblink_subcmd),
	SHELL_CMD(blink, NULL, "Parpadeo LED on", blink_subcmd),
	SHELL_SUBCMD_SET_END
);

SHELL_CMD_REGISTER(demo, &sub_commands, "Hello message", cmd_demo_salute);
