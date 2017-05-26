CC=gcc
CFLAGS=-Wall -Wpedantic -std=gnu99 -fpic -shared
LFLAGS=-lm -lfreeimage -loipimgutil
NAME=curves

SRCDIR=src
BUILDDIR=bin
OIP_PLUGIN_DIR=/home/eero/projects/OIP/plugins/
OIPDIR=/home/eero/projects/OIP/src

INCLUDES=-I$(OIPDIR)/imgutil/ -I$(OIPDIR)/headers
LIBS=-L$(OIPDIR)/imgutil/bin/

compile: $(SRCDIR)/*.c
	mkdir -p $(BUILDDIR)
	$(CC) $(CFLAGS) $(SRCDIR)/*.c -o $(BUILDDIR)/lib$(NAME).so $(INCLUDES) $(LIBS) $(LFLAGS)

install:
	cp $(BUILDDIR)/lib$(NAME).so $(OIP_PLUGIN_DIR)
	
LOC:
	wc -l $(SRCDIR)/*.c
