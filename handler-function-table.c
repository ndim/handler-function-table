#include "handler-function-table.h"

const char *handler_function_foo(void)
  __attribute__((weak, alias("__handler_function_default")));

const char *handler_function_bar(void)
  __attribute__((weak, alias("__handler_function_default")));

const char *handler_function_bla(void)
  __attribute__((weak, alias("__handler_function_default")));

const char *handler_function_meh(void)
  __attribute__((weak, alias("__handler_function_default")));

const handler_function_func handler_function_table_P[HANDLER_FUNCTION_TABLE_MAX] PROGMEM = {
  handler_function_foo,
  handler_function_bar,
  handler_function_bla,
  handler_function_meh
};

__attribute__((weak))
const char *handler_function_default(void)
{
  return "default handler_function_default";
}

#ifdef __AVR__

/* On AVR, avoid function stack frame and just jump to target */
__attribute__((naked))
const char *__handler_function_default(void)
{
  asm volatile("\n\t"
	       "jmp handler_function_default\n\t"
	       :::);
}

#else

const char *__handler_function_default(void)
{
  return handler_function_default();
}

#endif
