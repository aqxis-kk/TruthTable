SHELL=/bin/bash

MAKEFILES_IN_SUBDIR=$(wildcard */Makefile)
SUBDIR=$(dir $(MAKEFILES_IN_SUBDIR))

.PHONY: all clean $(SUBDIR)

all: $(SUBDIR)
clean: $(SUBDIR)

$(SUBDIR):
	$(MAKE) -C $@ $(MAKECMDGOALS)
