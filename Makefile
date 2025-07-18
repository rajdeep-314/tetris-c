main = src/main.c
exe = tetris


# source code files (.c)
files = src/utils.c \
		src/tetris.c

# header files (.h)
headers = src/utils.h \
		  src/tetris.h


# compiler and compiler flags
cc = gcc
cflags = -Wall


# the main target
all: $(exe)

# building the executable
$(exe):		$(main) $(files) $(headers)
	$(cc) $(main) $(files) $(cflags) -o $(exe)

# running the executable
run:	$(exe)
	./$(exe)

# removing the executable
clean:
	rm -f $(exe)


.PHONY: all run clean

