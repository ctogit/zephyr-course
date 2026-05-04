/*
 * Iomico l4-task1: crear una carpeta "boards" dentro de la raiz 
 * y copiar dentro de ella los archivos de la placa que se esté 
 * usando.Hay que editar los nombres de los archivos y contenido
 * según el nombre que le pongamos a la placa.
 * Antes de compilar hay que poner este comando en CMakeLists.txt
 * para no tener que decirle a zephyr dónde está la placa custom:
 * list(APPEND BOARD_ROOT ${CMAKE_CURRENT_SOURCE_DIR})
 * west build app -b cto_board_samv71/samv71q21 -p
 * En consola serie configurar según COM y 115200 baudios.
 */

#include <zephyr/kernel.h>
#include <stdio.h>

#define SLEEP_TIME_MS 1000

int main(void)
{
    while(1){
        printf("Hello World! %s\n", CONFIG_BOARD_TARGET);
        k_msleep(SLEEP_TIME_MS);
    }
	

	return 0;
}
