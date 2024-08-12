# Define variables
CC = i686-elf-gcc

# Source files and object files
SRC = terminal/vga.c input/keyboard/keyboard.c graphics/framebuffer.c
OBJ = $(SRC:.c=.o)

# Compile the driver source files
all: $(OBJ)

%.o: %.c
	$(CC) -c $< -o $@ -ffreestanding -O2 -Wall -Wextra

# Clean up object files
clean:
	rm -f $(OBJ)