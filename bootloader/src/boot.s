# https://www.gnu.org/software/grub/manual/multiboot/multiboot.html#Boot-sources

/* Declare constants for the multiboot header. */
.set ALIGN,    1<<0             /* align loaded modules on page boundaries */
.set MEMINFO,  1<<1             /* provide memory map */
.set FLAGS,    ALIGN | MEMINFO  /* this is the Multiboot 'flag' field */
.set MAGIC,    0x1BADB002       /* 'magic number' lets bootloader find the header */
.set CHECKSUM, -(MAGIC + FLAGS) /* checksum of above, to prove we are multiboot */
.set BOOTLOADER_MAGIC, 0x2BADB002

.section .multiboot
.align 4
.long MAGIC
.long FLAGS
.long CHECKSUM

.section .bss
.align 16
stack_bottom:
.skip 16384 # 16 KiB
stack_top:


.section .text
.global _start
.type _start, @function
_start:
    mov $stack_top, %esp     # Set up the stack pointer

    push %ebx                # Push Multiboot info pointer onto the stack

    push %eax                # Push Multiboot magic number onto the stack

    call kernel_main

	cli
1:	hlt
	jmp 1b

.size _start, . - _start
