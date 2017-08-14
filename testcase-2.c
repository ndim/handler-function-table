#include "testcase.h"
#include "handler-function-table.h"

TESTCASE("user defined handlers (_default and _bla)");

const char *handler_function_default(void) {
  return "user defined handler_function_default";
}

const char *handler_function_bla(void) {
  return "user defined handler_function_bla";
}
