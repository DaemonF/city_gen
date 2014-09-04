GCC_BIN = gcc
GCC_OPTIONS = -std=gnu++11
LIBRARIES = -lglfw

# Support comiling on non-linux
OS := $(shell uname)
ifeq ($(OS), Darwin)  # Mac
  GCC_BIN = gcc-4.9
  LIBRARIES = -lglfw3
endif

GCC = $(GCC_BIN) $(GCC_OPTIONS) $(LIBRARIES)


default:
	$(GCC) -o city_gen main.cc
