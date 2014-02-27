# project directories
PRJDIR 		 := $(shell pwd)

OUTDIR       := $(PRJDIR)/bin

CODDIR       := $(PRJDIR)/code
LIBDIR       := $(CODDIR)/lib
SRCDIR       := $(CODDIR)/src

# C source files

#modules
C_SRC += $(SRCDIR)/main.cpp
C_LIB += $(LIBDIR)/
	
# Define programs and commands.
CC      = 	gcc

# compiler flags
CFLAGS  = 	-g -Wall -lX11 -lstdc++ `pkg-config --libs --cflags opencv`

all:
	$(CC) $^ $(C_SRC) -o $(OUTDIR)/main -I$(C_LIB) $(CFLAGS)
