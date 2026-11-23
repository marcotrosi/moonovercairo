.SILENT:
.PHONY: dirs clean status

DIR = obj lib
SRC = src/moc.c
OBJ = obj/moc.o
LIB = lib/moc.so

CC = gcc
CPKG = `pkg-config --cflags lua5.5` `pkg-config --cflags cairo`
CFLAGS = -fPIC -c -Wall -O2 $(CPKG)

LD = gcc
LDPKG = `pkg-config --libs lua5.5` `pkg-config --libs cairo`
LDFLAGS = -shared -fPIC -O $(LDPKG)

all: dirs $(LIB)

$(LIB): $(OBJ)
	$(LD) $(LDFLAGS) -o $(LIB) $(OBJ)

$(OBJ): $(SRC)
	$(CC) $(CFLAGS) -o $(OBJ) $(SRC)

dirs:
	mkdir -p $(DIR)

clean: 
	rm -rf $(DIR)

status:
	lua doc/status.lua

