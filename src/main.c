/* Blink Example

   This example code is in the Public Domain (or CC0 licensed, at your option.)

   Unless required by applicable law or agreed to in writing, this
   software is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
   CONDITIONS OF ANY KIND, either express or implied.
*/
#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "sdkconfig.h"
#include "esp_system.h"
#include "esp_event.h"
//#include "esp_spi_flash.h"
#include "esp_log.h"
#include "esp_console.h"
#include "esp_vfs_dev.h"
//#include "driver/uart.h"
#include "linenoise/linenoise.h"
//#include "nvs_flash.h"
//#include "esp_spiffs.h"

#include "cmdline.h"

static const char* TAG = "MAIN";

static int misccmds(int argc, char** argv);

const esp_console_cmd_t misc_cmd = {
  .command = "misc",
  .help = "misc <taskinfo>|<mycmd>\n",
  .hint  = NULL,
  .func = &misccmds,
};

static char tmpBuffer[512];

static int misccmds(int argc, char** argv)
{
  if(argc >= 2)
    {
        if(0==strcasecmp("taskinfo",argv[1]))
        {
            ESP_LOGI(TAG, "taskinfo not supported");
        //vTaskGetRunTimeStats(tmpBuffer);
        //ESP_LOGI(TAG, "\n%s",tmpBuffer);
        //vTaskList(tmpBuffer);
        //ESP_LOGI(TAG, "Task State Prio Stack Num\n%s",tmpBuffer);
      }
      else if(0==strcasecmp("mycmd",argv[1]))
      {
        printf("mycmd\n");
      }
    }
  else
    {
      ESP_LOGI(TAG, "%s",misc_cmd.help);
    }
  return 0;
}



#if 0
void app_main()
{

    while(1) {
        /* Blink off (output low) */
	printf("Turning off the LED\n");
        //gpio_set_level(BLINK_GPIO, 0);
        vTaskDelay(1000 / portTICK_PERIOD_MS);
        /* Blink on (output high) */
	printf("Turning on the LED\n");
        //gpio_set_level(BLINK_GPIO, 1);
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
}
#endif

void app_main()
{
   printf("Hallo\n");

  //Initialize NVS
  //esp_err_t ret = nvs_flash_init();
  //if (ret == ESP_ERR_NVS_NO_FREE_PAGES /*|| ret == ESP_ERR_NVS_NEW_VERSION_FOUND newer idf version than idf version in used adf*/) {
  //  ESP_ERROR_CHECK(nvs_flash_erase());
  //  ret = nvs_flash_init();
 // }
  //ESP_ERROR_CHECK(ret);

  //cmdline_init();

  //wifiSimple_register_cmds
  //ESP_ERROR_CHECK( esp_console_cmd_register(&wifi_cmd) );

  //misc_register_cmds
  ESP_ERROR_CHECK( esp_console_cmd_register(&misc_cmd) );

  //snd_register_cmds
  //ESP_ERROR_CHECK( esp_console_cmd_register(&snd_cmd) );

#if 1
    while(1) {
        /* Blink off (output low) */
	//printf("Turning off the LED\n");
        //gpio_set_level(BLINK_GPIO, 0);
        vTaskDelay(4000 / portTICK_PERIOD_MS);
        /* Blink on (output high) */
	printf("heartbeat\n");
        //gpio_set_level(BLINK_GPIO, 1);
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
#endif

#if 0
  /* Main loop */
  while(true) {
    /* Get a line using linenoise.
     * The line is returned when ENTER is pressed.
     */
    char* line = linenoise(cmdline_prompt);//cmdline_get_prompt());
    if (line == NULL) { /* Ignore empty lines */
      continue;
    }
    /* Add the command to the history */
    linenoiseHistoryAdd(line);

    /* Try to run the command */
    int ret;
    esp_err_t err = esp_console_run(line, &ret);
    if (err == ESP_ERR_NOT_FOUND) {
      printf("Unrecognized command\n");
    } else if (err == ESP_ERR_INVALID_ARG) {
      // command was empty
    } else if (err == ESP_OK && ret != ESP_OK) {
      printf("Command returned non-zero error code: 0x%x (0x%x)\n", ret,err);
    } else if (err != ESP_OK) {
      printf("Internal error: 0x%x\n",err);
    }
    /* linenoise allocates line buffer on the heap, so need to free it */
    linenoiseFree(line);
  }
 #endif

}
