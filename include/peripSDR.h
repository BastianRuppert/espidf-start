/**
 * @file peripSDR.h
 * @author Bastian Ruppert
 * @date 03 09 2020
 * @brief Peripherie des ESP32
 *
 */

#ifndef __peripSDR_h__
#define __peripSDR_h__

#include <stdint.h>

/**
 * @brief Init UART for sdr_esp interface to host-controller
 *
 * @param baudrate Baudrate for this UART communication
 *
 * @returns the file descriptor for uart2 to use in select
 *
 */
extern int32_t peripSDR_init_HostUART(uint32_t baudrate);

/**
 * @brief get Host UART file descriptor pointer
 *
 * @returns pointer to uart file descriptor
 */
extern int32_t peripSDR_get_HostUART(void);

/**
 * @brief send data to uart2
 *
 * @param cmd Pointer to data to send
 * @param len data length
 */
extern void peripSDR_send_HostUART(char * cmd, int len);

#endif /* include guard */