SHELL=/bin/bash

CC=gcc
CFLAGS=-O2 -Wall -Wextra
CPPFLAGS=-Ilib `pkg-config --cflags gtk4`
LDFLAGS=-Llib
LDLIBS=-lgx `pkg-config --libs gtk4`

.PHONY: all clean

all: test
clean:
	$(RM) test

test: src/bool_operator.o src/bool_expression.o src/bool_expression_token.o
