ifeq ($(MCU),)
TOOL_PREFIX =
arch_subdir = native
else
TOOL_PREFIX = avr-
arch_subdir = $(MCU)
endif

CC = $(TOOL_PREFIX)gcc
NM = $(TOOL_PREFIX)nm
OBJDUMP = $(TOOL_PREFIX)objdump
MKDIR_P = mkdir -p
SORT_U = sort -u

builddir = build/$(arch_subdir)/

EXECUTABLES =

CFLAGS =
LDFLAGS =

# -std=c11 does not have inline assembler, but our AVR optimization requires that
ifeq ($(MCU),)
CFLAGS += -std=c11
else
CFLAGS += -std=gnu11
endif

CFLAGS += -pedantic
CFLAGS += -Wall
CFLAGS += -Wextra
CFLAGS += -Werror
CFLAGS += -save-temps=obj
CFLAGS += -O
CFLAGS += -gstabs
CFLAGS += -Wa,-adhlns=$(@:.o=.lst)

ifeq ($(MCU),)
else
CFLAGS  += -mmcu=$(MCU)
LDFLAGS += -mmcu=$(MCU)
endif

LDFLAGS += -Wl,-Map=$(@:=.map),--cref

# Throw out unused data and functions at link time
# CFLAGS  += -fdata-sections -ffunction-sections
# LDFLAGS += -Wl,--gc-sections,--print-gc-sections

# More information on the linking process
# LDFLAGS += -Wl,--print-map
# LDFLAGS += -Wl,--trace
# LDFLAGS += -Wl,--stats

LDFLAGS += -Wl,--warn-common
LDFLAGS += -Wl,--fatal-warnings

.PHONY: all
all: all-local

EXECUTABLES += $(builddir)testcase-1a
$(builddir)testcase-1a: $(builddir)testcase-main.o $(builddir)testcase-1.o $(builddir)handler-function-table.o
	$(LINK.c) -o $@ $^

EXECUTABLES += $(builddir)testcase-1b
$(builddir)testcase-1b: $(builddir)testcase-main.o $(builddir)handler-function-table.o $(builddir)testcase-1.o
	$(LINK.c) -o $@ $^

EXECUTABLES += $(builddir)testcase-2a
$(builddir)testcase-2a: $(builddir)testcase-main.o $(builddir)testcase-2.o $(builddir)handler-function-table.o
	$(LINK.c) -o $@ $^

EXECUTABLES += $(builddir)testcase-2b
$(builddir)testcase-2b: $(builddir)testcase-main.o $(builddir)handler-function-table.o $(builddir)testcase-2.o
	$(LINK.c) -o $@ $^

EXECUTABLE_INFOS =

# Dump data from executable
EXECUTABLE_INFOS += data
$(builddir)%.data: $(builddir)%
	$(MKDIR_P) $(@D)
	$(OBJDUMP) -s $< > $@.tmp
	mv -f $@.tmp $@

# Dump data and code from executable
EXECUTABLE_INFOS += dump
$(builddir)%.dump: $(builddir)%
	$(MKDIR_P) $(@D)
	($(OBJDUMP) --section=.rodata -s $<; $(OBJDUMP) --section=.text -S $<) > $@.tmp
	mv -f $@.tmp $@

# Dump disassembly from executable
EXECUTABLE_INFOS += lss
$(builddir)%.lss: $(builddir)%
	$(MKDIR_P) $(@D)
	$(OBJDUMP) -h -S $< > $@.tmp
	mv -f $@.tmp $@

# Dump symbols from executable
EXECUTABLE_INFOS += sym
$(builddir)%.sym: $(builddir)%
	$(MKDIR_P) $(@D)
	$(NM) -n $< | $(SORT_U) > $@.tmp
	mv -f $@.tmp $@

# Dump symbols from executable
EXECUTABLE_INFOS += vsym
$(builddir)%.vsym: $(builddir)%
	$(MKDIR_P) $(@D)
	$(OBJDUMP) --syms $< | grep '^[0-9a-f]\{4,16\} ' | $(SORT_U) > $@.tmp
	mv -f $@.tmp $@

.PHONY: all-local
all-local: $(EXECUTABLES) $(foreach t,$(EXECUTABLES),$(foreach e,$(EXECUTABLE_INFOS),$(t).$(e)))

$(builddir)%.o: %.c
	$(MKDIR_P) $(@D)
	$(COMPILE.c) -o $@ -c $<

$(builddir)%.o.dep: %.c
	$(MKDIR_P) $(@D)
	$(COMPILE.c) -MM -MT "$(builddir)$*.o $(builddir)$@ " $< > $@.tmp
	mv -f $@.tmp $@

include $(foreach srcfile, $(wildcard *.c), $(builddir)$(srcfile:.c=.o.dep))

.PHONY: check-nm
check-nm: all-local
	@nm_exe() { echo ""; echo "$$1:"; }; $(NM) $(builddir)*.o; for exe in $(EXECUTABLES); do nm_exe "$$exe"; nm "$$exe" | grep -E '[a-zA-Z_]+_handler_[a-zA-Z_]+'; done

.PHONY: check
check: all-local check-nm
	@echo ""
	@for test in $(EXECUTABLES); do echo "######## $${test} ########"; $$(dirname "$${test}")/$$(basename "$${test}"); done

.PHONY: clean
clean:
	rm -rf build
	rm -f *~
