# Define variables
CC = i686-elf-gcc

# Source files and object files
SRC = multiboot_info.c
OBJ = $(SRC:.c=.o)

# Compile the driver source files
all: $(OBJ)

%.o: %.c
	$(CC) -c $< -o $@ -ffreestanding -O2 -Wall -Wextra

# Clean up object files
clean:
	rm -f $(OBJ)