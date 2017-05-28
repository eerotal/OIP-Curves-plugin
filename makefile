# Set some compilation options.
CC=gcc
CFLAGS=-Wall -Wpedantic -std=gnu99 -fpic -shared
LFLAGS=-lm -lfreeimage -loipimgutil
NAME=curves

# Check whether the build-config file exists.
ifeq ($(wildcard build-config),)
$(error No build-config file found! Please run config-build-env.sh first)
endif

# Include the build-config file.
include build-config

SRCDIR=src
BINDIR=bin
OIP_PLUGIN_DIR=$(OIPDIR)/plugins

INCLUDES=-I$(OIPDIR)/src/imgutil/ -I$(OIPDIR)/src/headers
LIBS=-L$(OIPDIR)/src/imgutil/bin/

compile: $(SRCDIR)/*.c
	mkdir -p $(BINDIR)
	$(CC) $(CFLAGS) $(SRCDIR)/*.c -o $(BINDIR)/lib$(NAME).so $(INCLUDES) $(LIBS) $(LFLAGS)

install:
	cp $(BINDIR)/lib$(NAME).so $(OIP_PLUGIN_DIR)

clean:
	rm -rf $(BINDIR)

clean-hard: clean
	rm -f build-config
	
LOC:
	wc -l $(SRCDIR)/*.c
