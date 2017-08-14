#ifndef __HANDLER_FUNCTION_TABLE_H__
#define __HANDLER_FUNCTION_TABLE_H__

#ifdef __AVR__
# include <avr/pgmspace.h>
#else
# define PROGMEM
#endif

typedef const char * (*handler_function_func)(void);

#define HANDLER_FUNCTION_TABLE_MAX 4

extern
const handler_function_func handler_function_table_P[HANDLER_FUNCTION_TABLE_MAX] PROGMEM;

#endif /* __HANDLER_FUNCTION_TABLE_H__ */
