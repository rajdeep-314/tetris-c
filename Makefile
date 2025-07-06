main = src/main.c
exe = tetris

tmain = src/test.c
texe = test-tetris


# source code files (.c)
files = src/screen.c \
		src/utils.c

# header files (.h)
headers = src/screen.h \
		  src/utils.h


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



# targets for testing
test:	$(texe)

$(texe):	$(tmain) $(files) $(headers)
	$(cc) $(tmain) $(files) $(cflags) -o $(texe)

test-run:	$(texe)
	./$(texe)

test-clean:
	rm -f $(texe)


.PHONY: test test-run test-clean

