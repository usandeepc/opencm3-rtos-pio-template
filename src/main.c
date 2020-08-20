#include <opencm3uart.h>
#include <FreeRTOS.h>
#include <task.h>
#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/gpio.h>
/*********************************************************************
 * Send characters to the UART, slowly
 *********************************************************************/
static void  task1(void *args __attribute__((unused))) {
	
	char rec_array[128];

	for (;;) {
			console_puts("Hi Please type Something !");
			console_gets(rec_array, 10);
			console_puts("\nYou entered : ");
			console_puts(rec_array);
			console_puts("\n");
	}
}
static void task2(void *args __attribute__((unused))){
	for (;;)
	{
		gpio_toggle(GPIOC,GPIO13);
		vTaskDelay(pdMS_TO_TICKS(500));
	}
	
}

/*********************************************************************
 * Main program
 *********************************************************************/
int
main(void) {

	rcc_clock_setup_in_hse_8mhz_out_72mhz(); // Blue pill

	// PC13:
	rcc_periph_clock_enable(RCC_GPIOC);
	gpio_set_mode(
		GPIOC,
                GPIO_MODE_OUTPUT_2_MHZ,
                GPIO_CNF_OUTPUT_PUSHPULL,
                GPIO13);

	uart_setup();

	xTaskCreate(task1,"task1",100,NULL,configMAX_PRIORITIES-1,NULL);
	xTaskCreate(task2,"task2",100,NULL,configMAX_PRIORITIES-1,NULL);
	vTaskStartScheduler();

	for (;;);
	return 0;
}

// End