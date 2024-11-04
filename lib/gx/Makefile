SHELL=/bin/bash

CC=gcc
CFLAGS=-O3 -Wall -Wextra
CPPFLAGS=-I. -I.. `pkg-config --cflags gtk4`
LDLIBS= `pkg-config --libs gtk4`

AR=ar
ARFLAGS=rc

OUTPUT_DIR=../
TARGET_NAMES=libgx.a

SRC=$(wildcard gx_internal/*.c)
TARGETS=$(addprefix $(OUTPUT_DIR), $(TARGET_NAMES))

.PHONY: all clean

all: $(TARGETS)

clean:
	$(RM) $(wildcard *.o) $(TARGETS)

$(OUTPUT_DIR)$(TARGET_NAMES): $(OUTPUT_DIR)$(TARGET_NAMES)($(SRC:.c=.o))
