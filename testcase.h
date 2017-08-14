#ifndef __TESTCASE_H__
#define __TESTCASE_H__

#define TESTCASE(DESCR)			      \
  const char *const testcase_file = __FILE__; \
  const char *const testcase_name = (DESCR)

extern
const char *const testcase_file;

extern
const char *const testcase_name;

#endif /* __TESTCASE_H__ */
