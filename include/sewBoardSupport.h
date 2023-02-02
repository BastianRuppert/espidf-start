/**
 * @file sewBoardSupport.h
 * @author Bastian Ruppert
 * @date 28 07 2021
 * @brief Board support code for different boards/modules based on ESP32, ESP32-xx
 *
 */

#ifndef __SEW_BOARDSUPPORT_h__
#define __SEW_BOARDSUPPORT_h__

#include "driver/gpio.h"

/* ESP32 SDR-Module definitions */
//#ifdef CONFIG_IDF_TARGET_ESP32

/**
 *  UART Number used for Host controller communication
 */
#define UART_HOST_NUM_X UART_NUM_1

#define UART_HOST_GPIO_TX  GPIO_NUM_17
#define UART_HOST_GPIO_RX  GPIO_NUM_16
#define UART_HOST_GPIO_RTS -1
#define UART_HOST_GPIO_CTS -1

//#define GPIO_PC0 GPIO_NUM_23    //HP Taster; Doppelbelegung mit I2C SCL
//#define GPIO_PC1 GPIO_NUM_18    //LED gr; Doppelbelegung mit I2C SDA

//#endif
/* End ESP32 */

#endif /* end include guard */
