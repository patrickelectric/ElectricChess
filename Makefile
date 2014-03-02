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
CFLAGS  =`pkg-config --libs --cflags opencv` -Wall -lX11 -lstdc++ -Wno-write-strings
#for ddd
#CFLAGS  +=-mpreferred-stack-boundary=4 -mstackrealign -ggdb -g

all:
	$(CC) $^ $(C_SRC) -o $(OUTDIR)/main -I$(C_LIB) $(CFLAGS)
