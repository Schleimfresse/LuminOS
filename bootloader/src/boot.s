
/* Declare constants for the multiboot header. */
.set ALIGN,    1<<0             /* align loaded modules on page boundaries */
.set MEMINFO,  1<<1             /* provide memory map */
.set FLAGS,    ALIGN | MEMINFO  /* this is the Multiboot 'flag' field */
.set MULTIBOOT2_HEADER_MAGIC, 0xe85250d6
.set CHECKSUM, -(MULTIBOOT2_HEADER_MAGIC + FLAGS) /* checksum of above, to prove we are multiboot */
.set MULTIBOOT_HEADER_TAG_FRAMEBUFFER,  5
.set MULTIBOOT_ARCHITECTURE_I386, 0
.set MULTIBOOT_HEADER_TAG_OPTIONAL, 1
.set MULTIBOOT_HEADER_TAG_END, 0

.section .bss
.align 16
stack_bottom:
.skip 16384 # 16 KiB
stack_top:


.section .multiboot
.align 4

/* Multiboot2 Header */
multiboot_header:
    .long MULTIBOOT2_HEADER_MAGIC               /* Magic number */
    .long MULTIBOOT_ARCHITECTURE_I386           /* Architecture */
    .long multiboot_header_end - multiboot_header /* Header length */
    .long -(MULTIBOOT2_HEADER_MAGIC + MULTIBOOT_ARCHITECTURE_I386 + (multiboot_header_end - multiboot_header)) /* Checksum */

    /* Framebuffer Tag */
#framebuffer_tag_start:
    #.short MULTIBOOT_HEADER_TAG_FRAMEBUFFER     /* Tag type for framebuffer */
    #.short MULTIBOOT_HEADER_TAG_OPTIONAL        /* Tag optional flag */
    #.long framebuffer_tag_end - framebuffer_tag_start /* Tag length */
   # .long 1024                                  /* Framebuffer width */
  #  .long 768                                   /* Framebuffer height */
 #   .long 16                                   /* Bits per pixel */
#framebuffer_tag_end:

    /* End Tag */
  #  .short MULTIBOOT_HEADER_TAG_END             /* End tag type */
 #   .short 0                                    /* End tag optional flag */
#    .long 8                                     /* End tag length */

multiboot_header_end:

.text
.global  start, _start
start:
_start:

    jmp multiboot_entry

	cli
1:	hlt
	jmp 1b

multiboot_entry:

    mov $stack_top, %esp     # Set up the stack pointer

    push %ebx                # Push Multiboot info pointer onto the stack

    push %eax                # Push Multiboot magic number onto the stack

    call kernel_main


.size _start, . - _start
