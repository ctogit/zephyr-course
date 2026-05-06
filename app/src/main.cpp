/*
 * Iomico l5-task1: crear una carpeta "boards" dentro de la raiz 
 * y copiar dentro de ella los archivos de la placa que se esté 
 * usando.Hay que editar los nombres de los archivos y contenido
 * según el nombre que le pongamos a la placa.
 * Antes de compilar hay que poner este comando en CMakeLists.txt
 * para no tener que decirle a zephyr dónde está la placa custom:
 * list(APPEND BOARD_ROOT ${CMAKE_CURRENT_SOURCE_DIR})
 * west build app -b cto_board_samv71/samv71q21 -p
 * En consola serie configurar según COM y 115200 baudios.
 * 
 * Iomico l5-task2: dentro de boards se creó otra placa con los
 * archivos mínimos requeridos. En esta placa se pueden editar el 
 * .dts para eliminar nodos que no se usan. 
 * Para compilar:
 * west build app -b my_cto_board/samv71q21
 * 
 * Dentro de la carpeta my_cto_board se creó archivo board.c y 
 * CMakeLists.txt para probar de ejecutar código antes de que
 * inicie el main y se jugó con diferentes niveles de kernel
 * (ver board.c).
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
