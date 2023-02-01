/*
  cmdline.h
 */

#ifndef __cmdline_h__
#define __cmdline_h__

/**
 * @file cmdline.h
 * @author Bastian Ruppert
 * @date 04 10 2018
 * @brief Definitionen für console commands
 *
 */

extern const char* cmdline_prompt;

/*! \brief init Funktion für die console Funktionalität
 *
 */
extern void cmdline_init_console(void);

/*! \brief Registriert die user commands
 *
 */
extern void cmdline_register(void);

/*! \brief cmdline init
 *
 */
extern void cmdline_init(void);

#endif /* __cmdline_h__ */
