/*
 cmdline.c
*/

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"
#include "esp_console.h"
#include "esp_system.h"
#include "esp_sleep.h"
//#include "driver/rtc_io.h"
#include "argtable3/argtable3.h"
#include "esp_console.h"
#include "esp_vfs_dev.h"
#include "driver/uart.h"
#include "linenoise/linenoise.h"

#include "cmdline.h"

static int infoI = 0;

/* Prompt to be printed before each line.
 * This can be customized, made dynamic, etc.
 */
const char* cmdline_prompt = LOG_COLOR_I "sew> " LOG_RESET_COLOR;

static int info(int argc, char** argv)
{
  infoI++;
  printf("info Text aus der info Funktion %i\n",infoI);
  return 0;
}

static void register_info(void)
{
  const esp_console_cmd_t cmd = {
    .command = "info",
    .help = "zeigt einen Infotext",
    .hint = NULL,
    .func = &info,
  };
  ESP_ERROR_CHECK( esp_console_cmd_register(&cmd) );
}

/** 'restart' command restarts the program */

static int restart(int argc, char** argv)
{
  ESP_LOGI(__func__, "Restarting");
  esp_restart();
}

static void register_restart()
{
  const esp_console_cmd_t cmd = {
    .command = "restart",
    .help = "Restart the program",
    .hint = NULL,
    .func = &restart,
  };
  ESP_ERROR_CHECK( esp_console_cmd_register(&cmd) );
}

void cmdline_register(void)
{
  esp_console_register_help_command();
  register_info();
  register_restart();
}

void cmdline_init_console(void)
{
    /* Disable buffering on stdin and stdout */
    setvbuf(stdin, NULL, _IONBF, 0);
    setvbuf(stdout, NULL, _IONBF, 0);

    /* Install UART driver for interrupt-driven reads and writes */
    ESP_ERROR_CHECK( uart_driver_install(CONFIG_ESP_CONSOLE_UART_NUM,
            256, 0, 0, NULL, 0) );

    /* Tell VFS to use UART driver */
    esp_vfs_dev_uart_use_driver(CONFIG_ESP_CONSOLE_UART_NUM);

    /* Initialize the console */
    esp_console_config_t console_config = {
      .max_cmdline_args = 8,
            .max_cmdline_length = 256,
#if CONFIG_LOG_COLORS
            .hint_color = atoi(LOG_COLOR_CYAN)
#endif
    };
    ESP_ERROR_CHECK( esp_console_init(&console_config) );

    /* Configure linenoise line completion library */
    /* Enable multiline editing. If not set, long commands will scroll within
     * single line.
     */
    linenoiseSetMultiLine(1);

    /* Tell linenoise where to get command completions and hints */
    linenoiseSetCompletionCallback(&esp_console_get_completion);
    linenoiseSetHintsCallback((linenoiseHintsCallback*) &esp_console_get_hint);

    /* Set command history size */
    linenoiseHistorySetMaxLen(100);
}

void cmdline_init(void)
{
  cmdline_init_console();

  /* register commands */
  cmdline_register();

  /* Figure out if the terminal supports escape sequences */
  int probe_status = linenoiseProbe();
  if (probe_status) { /* zero indicates success */
    printf("\n"
           "Your terminal application does not support escape sequences.\n"
           "Line editing and history features are disabled.\n"
           "On Windows, try using Putty instead.\n");
    linenoiseSetDumbMode(1);
#if CONFIG_LOG_COLORS
    /* Since the terminal doesn't support escape sequences,
     * don't use color codes in the prompt.
     */
    cmdline_prompt = "esp32> ";
#endif //CONFIG_LOG_COLORS
  }
}
