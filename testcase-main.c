#include <stdint.h>
#include <stdio.h>

#include "testcase.h"
#include "handler-function-table.h"

static handler_function_func get_func(unsigned int i);

#ifdef __AVR__

static handler_function_func get_func(unsigned int i)
{
  const uint16_t addr = pgm_read_word_near(handler_function_table_P[i]);
  return (handler_function_func) addr;
}

#else /* !defined(__AVR__) */

static handler_function_func get_func(unsigned int i)
{
  return handler_function_table_P[i];
}

#endif /* defined(__AVR__) / !defined(__AVR__) */

int main()
{
  printf("%s: test case \"%s\"\n", testcase_file, testcase_name);
  for (unsigned int i=0; i < HANDLER_FUNCTION_TABLE_MAX; ++i) {
    const handler_function_func func = get_func(i);
    const char *const msg = func();
    printf("  %u %s\n", i, msg);
  }
  return 0;
}
