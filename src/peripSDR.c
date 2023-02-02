/*
perip_esp.c
*/

#include <string.h>
#include <netdb.h>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/event_groups.h"
#include "esp_system.h"
#include "esp_log.h"
#include "esp_vfs.h"
#include "esp_vfs_dev.h"
#include "driver/gpio.h"
#include "driver/uart.h"
#include "sewBoardSupport.h"

#include "peripSDR.h"

static const char *TAG = "peripSDR";

/* UART */
static int32_t uart_fd = -1;

int32_t peripSDR_init_HostUART(uint32_t baudrate)
{
    uart_config_t uart_config = {
        .baud_rate = baudrate,
        .data_bits = UART_DATA_8_BITS,
        .parity    = UART_PARITY_DISABLE,
        .stop_bits = UART_STOP_BITS_1,
        .flow_ctrl = UART_HW_FLOWCTRL_DISABLE,
        .source_clk = UART_SCLK_APB,
    };

    ESP_ERROR_CHECK(uart_set_pin(UART_HOST_NUM_X, UART_HOST_GPIO_TX, UART_HOST_GPIO_RX, UART_HOST_GPIO_RTS, UART_HOST_GPIO_CTS));// NOT uart2 default

    uart_driver_install(UART_HOST_NUM_X, 1024, 0, 0, NULL, 0);

    uart_param_config(UART_HOST_NUM_X, &uart_config);

    if ((uart_fd  = open("/dev/uart/1", O_RDWR /*| O_BLOCK*/)) == -1)
    {
        //flagStore_err(nFS_SOURCE_PERIP,errUART_HOST_OPEN_FD);
        ESP_LOGE(TAG, "%s Cannot open UART1", __FUNCTION__);
        close(uart_fd);
        uart_fd = -1;
        uart_driver_delete(UART_HOST_NUM_X);
    }

    //printf("uart should be ready fd: %i\n",(int)uart_fd);

    // We have a driver now installed so set up the read/write functions to use driver also.
    esp_vfs_dev_uart_use_driver(UART_HOST_NUM_X);

    return uart_fd;
}

int32_t peripSDR_get_HostUART(void)
{
    return uart_fd;
}

void peripSDR_send_HostUART(char * cmd, int len)
{
  int ret = 0;

  if(-1 != uart_fd)
  {
    ret=write(uart_fd,cmd,len);
    if(ret!=len)
    {
      ESP_LOGE(TAG, "%s error writing to  UART2", __FUNCTION__);
    }
  }
}
