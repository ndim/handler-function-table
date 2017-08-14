handler-function-table: Link-time read-only function pointer table in GCC
=========================================================================

This answers the question in
https://stackoverflow.com/questions/19845635/implementing-a-compile-time-read-only-function-pointer-table-in-gcc
and implements a compile time (or rather: link time) read only
function pointer table in gcc using weak symbols.

This makes it possible to place that table in what `avr-libc` calls
`PROGMEM`.


Usage
-----

To clean up all generated files:

    make clean

To build all test cases for AVR:

    make MCU=atmega644p

To build all test cases natively and run them:

    make check

To compare the disassembly of some generated executables:

    diff -u build/native/testcase-{1a,2a}.dump
    diff -u build/atmega644p/testcase-{1a,2a}.dump


Open Issues
-----------

2. A typo in the function name of an overriding function will result
   in the override not happening WITHOUT compiler warnings or errors.

   `avr-libc` solves that issue by defining macros for all vectors
   which map identifiers onto vector numbers, and uses those numbers
   in the table instead of the user visible identifiers. This can
   cause a compilation error when a typo in the name of an ISR handler
   happens.


Solved Issues
-------------

1. Even though the assembly instructions emitted by gcc appear to use
   the same pattern of `.weak` and `.set` assembly directives as
   `avr-libc` uses in `crt1/gcrt1.S` to define `__vectors`,
   `__bad_interrupt`, and `__vector_default`, we cannot override the
   default handler in our implementation.

   Solution: We were missing the non-weak `__function_handler_default`
   function which then calls the weakly defined
   `function_handler_default` function. In `crt1/gcrt1.S` can do the
   indirection step by just jumping to the weakly defined
   `__vector_default` function, but calling the weakly defined
   function works just as well.
