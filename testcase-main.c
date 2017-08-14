#include <stdint.h>
#include <stdio.h>

#include "testcase.h"
#include "handler-function-table.h"

int main()
{
  printf("%s: test case \"%s\"\n", testcase_file, testcase_name);
  for (unsigned int i=0; i < HANDLER_FUNCTION_TABLE_MAX; ++i) {
#ifdef __AVR__
    const uint16_t addr = pgm_read_word_near(handler_function_table_P[i]);
    const handler_function_func func = (handler_function_func) addr;
#else
    const handler_function_func func = handler_function_table_P[i];
#endif
    const char *const msg = func();
    printf("  %u %s\n", i, msg);
  }
  return 0;
}
