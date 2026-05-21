#include <zephyr/init.h>
#include <zephyr/kernel.h>
#include <stdio.h>

#define SLEEP_TIME_MS 2000

static int board_my_cto_board_init(void) 
{
    /* Some function to run before boot */
    k_msleep(SLEEP_TIME_MS);
    printf("INITIALIZING MY_CTO_BOARD...\n");
    k_msleep(SLEEP_TIME_MS);
    printf("iomico zephyr course - lesson 7 (Shell integration)\n");
    k_msleep(SLEEP_TIME_MS);

    return 0;
}
/* 
* Notas kernel level:
* PRE_KERNEL_1: no arrancó la consola serie.
* PRE_KERNEL_2: la consola muestra un msg de error de zephyr (MPU FAULT, ZEPHYR FATAL ERROR 20)
* POST_KERNEL: funciona ok, se cuela un "Booting Zephyr OS build v4.4.0" al medio.
* APPLICATION: funciona mejor (Booting Zephyr..., Initializaing..., HelloWorld)
* SMP: igual que el anterior (aunque no se si se configuró bien) 
*/
SYS_INIT(board_my_cto_board_init, POST_KERNEL, CONFIG_KERNEL_INIT_PRIORITY_DEFAULT);