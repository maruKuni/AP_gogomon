vpath %.c src
vpath %.exe bin

CC=clang
CFLAGS:=-g -Wall -Wextra

.PHONY: all clean

EXE:=$(addsuffix .exe,$(basename $(notdir $(wildcard src/*.c))))

$(EXE):%.exe: %.c
	$(CC) $(CFLAGS) $< -o bin/$@
all: $(EXE)
clean:
	-rm bin/*.exe
p:
	echo $(EXE)