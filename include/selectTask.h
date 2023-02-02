/**
 * @file selectTask.h
 * @author Bastian Ruppert
 * @date 02 02 2023
 * @brief Kommunikations task auf select basis
 *
 */

#ifndef __selectTask_h__
#define __selectTask_h__

#include <stdint.h>

/**
 * @brief Init selectTask for UART Communication
 *
 * Inits the UART in peripSDR for board to board communication
 *
 * @returns TODO should return an error if something went wrong
 *
 */
extern void selectTask_init(void);

#endif /* include guard */