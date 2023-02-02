#include "freertos/FreeRTOS.h"
#include "freertos/semphr.h"

#include "esp_system.h"
#include "esp_wifi.h"
#include "esp_log.h"
#include "errno.h"

#include <driver/uart.h>
//#include "lwip/err.h"
//#include "lwip/sockets.h"
//#include "lwip/sys.h"
//#include "lwip/inet.h"
//#include <lwip/netdb.h>

#include "peripSDR.h"
#include "sewBoardSupport.h"

static const char* TAG = "selectTask";

static void select_uart_task(void *pvParameters);

static void uart_data_ready(void);

static int fd_uart = 0;

void selectTask_init(void)
{
    fd_uart = peripSDR_init_HostUART(115200);
    xTaskCreate(select_uart_task,"uart_select",3072,NULL,5,NULL);
}

static fd_set rfds_uart_select;
static struct timeval tv_uart_select = {
        .tv_sec = 1,
        .tv_usec = 0,//85333
    };

static int isGreater(int basis, int neu)
{
    if(neu > basis)
    {
        return neu;
    }else{
        return basis;
    }
}

static void select_uart_task(void *param)
{
    int s;
    int fdmax;

    while(1)
    {
        FD_ZERO(&rfds_uart_select);
        FD_SET(fd_uart, &rfds_uart_select);

        fdmax = 0;
        fdmax = isGreater(fdmax,fd_uart);

        s = select(fdmax + 1, &rfds_uart_select, NULL, NULL, &tv_uart_select);

        if (s < 0) {
            ESP_LOGE(TAG, "select_uart_task select failed: errno %d", errno);
            //flagStore_err(nFS_SOURCE_SEW_SOCKET,errWIFISOCK_SELECT_ERROR);
        }else if (s == 0) {
        //ESP_LOGI(TAG, "select_uart_task Timeout has been reached and nothing has been received");
        }

        if (FD_ISSET(fd_uart, &rfds_uart_select))
        {
            uart_data_ready();
        }
    }//end while

    vTaskDelete(NULL);
}


static uint8_t uart_read_buffer[128+8];

static void uart_data_ready(void)
{
    int ret,i;

    ret = uart_read_bytes(UART_HOST_NUM_X,uart_read_buffer,sizeof(uart_read_buffer),0);

    if(ret<0)
    {
        //flagStore_err(nFS_SOURCE_PERIP,errUART_HOST_READ);
        ESP_LOGE(TAG, "%s(): falscher Alarm", __FUNCTION__);
    }
    else
    {
        for(i=0; i<ret;i++)
        {
            printf("%c",uart_read_buffer[i]);//printf chars from the other side
        }
        printf("\n");
    }
}