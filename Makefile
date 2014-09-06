GCC_BIN = g++
GCC_OPTIONS = -std=gnu++11
LIBRARIES = -lglfw

# Support comiling on non-linux
OS := $(shell uname)
ifeq ($(OS), Darwin)  # Mac
  GCC_BIN = gcc-4.9
  LIBRARIES = -lglfw3
endif

GCC = $(GCC_BIN) $(GCC_OPTIONS) $(LIBRARIES)

# TODO makefile is recompiling when nothing's changing

default:
	$(GCC) -o city_gen main.cc
	# TODO use different rules/targets
	$(GCC) -o test_bldg test_bldg.cc grid.cc bldg_gen.cc
