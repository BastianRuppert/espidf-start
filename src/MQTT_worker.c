#include <string.h>
#include "freertos/FreeRTOS.h"
#include "freertos/semphr.h"

#include "esp_system.h"
#include "esp_log.h"
#include "esp_console.h"

#include "sewBoardSupport.h"
#include "MQTT_worker.h"


static const char* TAG = "MQTT worker";

/* Block for ms. */
const TickType_t xDelay = 2000 / portTICK_PERIOD_MS;
static int verbose = 0;


static int mqtt_worker_cmds(int argc, char** argv);
static void MQTT_worker_task(void *param);


const esp_console_cmd_t mqtt_worker_cmd = {
  .command = "mqtt",
  .help = "mqtt <verbose> | <run>\n",
  .hint  = NULL,
  .func = &mqtt_worker_cmds,
};

static int mqtt_worker_cmds(int argc, char** argv)
{
  if(argc >= 2)
    {
      if(0==strcasecmp("verbose",argv[1]))
        {
            if(1==verbose)
            {
                verbose = 0;
            }
            else
            {
                verbose = 1;
            }
          ESP_LOGI(TAG,"verbose = %i",verbose);
        }
      else if(0==strcasecmp("run",argv[1]))
      {;
        ESP_LOGI(TAG, "do something in the future");
      }
    }
  else
    {
      ESP_LOGI(TAG, "%s",mqtt_worker_cmd.help);
    }
  return 0;
}

void workerMQTT_init(void)
{

    /* register own misc_cmd`s */
    ESP_ERROR_CHECK( esp_console_cmd_register(&mqtt_worker_cmd) );

    xTaskCreate(MQTT_worker_task,"MQTT_worker_task",3072,NULL,5,NULL);
}

static void MQTT_worker_task(void *param)
{
    int counter = 0;

    while(1)
    {
        if(1==verbose)
        {
            ESP_LOGI(TAG,"task cnt\t%i",counter);
        }

        counter++;
        vTaskDelay( xDelay );
    }//end while

    vTaskDelete(NULL);
}
