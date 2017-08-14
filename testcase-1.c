#include "testcase.h"
#include "handler-function-table.h"

TESTCASE("all default handlers & dummy placeholders");

/* We keep some replacement strings and functions here to keep the
 * differences between the disassemblies to a minimum.
 */

__attribute__((used))
const char *handler_function_xxxxxxx(void) {
  return "replacement function with same size!!";
}

__attribute__((used))
const char *handler_function_xxx(void) {
  return "replacement function with same sz";
}
