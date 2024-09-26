	.file	"kernel.c"
	.text
	.globl	fb
	.bss
	.align 8
	.type	fb, @object
	.size	fb, 8
fb:
	.zero	8
	.globl	psf1_font
	.align 8
	.type	psf1_font, @object
	.size	psf1_font, 8
psf1_font:
	.zero	8
	.section	.rodata
.LC0:
	.string	"Mb "
.LC1:
	.string	" "
.LC2:
	.string	"  "
.LC3:
	.string	"Free RAM:"
.LC4:
	.string	" KB "
.LC5:
	.string	"Used RAM:"
.LC6:
	.string	"Reserved RAM:"
.LC7:
	.string	"Total RAM:"
.LC8:
	.string	"Test securit h"
	.text
	.globl	kernel_main
	.type	kernel_main, @function
kernel_main:
.LFB0:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	pushq	%rbx
	subq	$136, %rsp
	.cfi_offset 3, -24
	movq	%rdi, -136(%rbp)
	movq	%fs:40, %rax
	movq	%rax, -24(%rbp)
	xorl	%eax, %eax
	movq	-136(%rbp), %rax
	movq	(%rax), %rax
	movq	%rax, fb(%rip)
	movq	-136(%rbp), %rax
	movq	8(%rax), %rax
	movq	%rax, psf1_font(%rip)
	movq	-136(%rbp), %rax
	movq	24(%rax), %rax
	movq	-136(%rbp), %rdx
	movq	32(%rdx), %rbx
	movl	$0, %edx
	divq	%rbx
	movq	%rax, -128(%rbp)
	movq	-136(%rbp), %rax
	movq	32(%rax), %rdx
	movq	-136(%rbp), %rax
	movq	16(%rax), %rax
	movq	-128(%rbp), %rcx
	movq	%rcx, %rsi
	movq	%rax, %rdi
	call	GetMemorySize@PLT
	shrq	$20, %rax
	movq	%rax, %rdi
	call	to_string@PLT
	movl	$65280, %esi
	movq	%rax, %rdi
	call	Print@PLT
	movl	$16777215, %esi
	leaq	.LC0(%rip), %rax
	movq	%rax, %rdi
	call	Print@PLT
	movq	-128(%rbp), %rax
	movq	%rax, %rdi
	call	to_string@PLT
	movl	$16777215, %esi
	movq	%rax, %rdi
	call	Print@PLT
	movl	$16777215, %esi
	leaq	.LC1(%rip), %rax
	movq	%rax, %rdi
	call	Print@PLT
	movq	-136(%rbp), %rax
	movq	32(%rax), %rax
	movq	%rax, %rdi
	call	to_string@PLT
	movl	$16777215, %esi
	movq	%rax, %rdi
	call	Print@PLT
	movl	$120, %esi
	movl	$50, %edi
	call	SetCursor@PLT
	movl	$0, %eax
	call	init_heap@PLT
	leaq	-112(%rbp), %rax
	movq	%rax, -120(%rbp)
	movq	-136(%rbp), %rax
	movq	32(%rax), %rcx
	movq	-136(%rbp), %rax
	movq	24(%rax), %rdx
	movq	-136(%rbp), %rax
	movq	16(%rax), %rsi
	movq	-120(%rbp), %rax
	movq	%rax, %rdi
	call	ReadEFIMemoryMap@PLT
	movq	-136(%rbp), %rax
	movq	24(%rax), %rax
	movq	%rax, %rdi
	call	to_string@PLT
	movl	$65280, %esi
	movq	%rax, %rdi
	call	Print@PLT
	movl	$65280, %esi
	leaq	.LC2(%rip), %rax
	movq	%rax, %rdi
	call	Print@PLT
	movq	-136(%rbp), %rax
	movq	32(%rax), %rax
	movq	%rax, %rdi
	call	to_string@PLT
	movl	$65280, %esi
	movq	%rax, %rdi
	call	Print@PLT
	movl	$16, %edi
	call	IncrementCursorY@PLT
	movl	$0, %edi
	call	SetCursorX@PLT
	movl	$16777215, %esi
	leaq	.LC3(%rip), %rax
	movq	%rax, %rdi
	call	Print@PLT
	movq	-120(%rbp), %rax
	movq	%rax, %rdi
	call	GetFreeRAM@PLT
	shrq	$20, %rax
	movq	%rax, %rdi
	call	to_string@PLT
	movl	$8421504, %esi
	movq	%rax, %rdi
	call	Print@PLT
	movl	$16777215, %esi
	leaq	.LC4(%rip), %rax
	movq	%rax, %rdi
	call	Print@PLT
	movl	$16, %edi
	call	IncrementCursorY@PLT
	movl	$0, %edi
	call	SetCursorX@PLT
	movl	$16777215, %esi
	leaq	.LC5(%rip), %rax
	movq	%rax, %rdi
	call	Print@PLT
	movq	-120(%rbp), %rax
	movq	%rax, %rdi
	call	GetUsedRAM@PLT
	shrq	$20, %rax
	movq	%rax, %rdi
	call	to_string@PLT
	movl	$8421504, %esi
	movq	%rax, %rdi
	call	Print@PLT
	movl	$16777215, %esi
	leaq	.LC4(%rip), %rax
	movq	%rax, %rdi
	call	Print@PLT
	movl	$16, %edi
	call	IncrementCursorY@PLT
	movl	$0, %edi
	call	SetCursorX@PLT
	movl	$16777215, %esi
	leaq	.LC6(%rip), %rax
	movq	%rax, %rdi
	call	Print@PLT
	movq	-120(%rbp), %rax
	movq	%rax, %rdi
	call	GetReservedRAM@PLT
	shrq	$20, %rax
	movq	%rax, %rdi
	call	to_string@PLT
	movl	$8421504, %esi
	movq	%rax, %rdi
	call	Print@PLT
	movl	$16777215, %esi
	leaq	.LC4(%rip), %rax
	movq	%rax, %rdi
	call	Print@PLT
	movl	$16, %edi
	call	IncrementCursorY@PLT
	movl	$0, %edi
	call	SetCursorX@PLT
	movl	$16777215, %esi
	leaq	.LC7(%rip), %rax
	movq	%rax, %rdi
	call	Print@PLT
	movq	-120(%rbp), %rax
	movq	%rax, %rdi
	call	GetReservedRAM@PLT
	movq	%rax, %rbx
	movq	-120(%rbp), %rax
	movq	%rax, %rdi
	call	GetFreeRAM@PLT
	addq	%rax, %rbx
	movq	-120(%rbp), %rax
	movq	%rax, %rdi
	call	GetUsedRAM@PLT
	addq	%rbx, %rax
	shrq	$20, %rax
	movq	%rax, %rdi
	call	to_string@PLT
	movl	$65535, %esi
	movq	%rax, %rdi
	call	Print@PLT
	movl	$16777215, %esi
	leaq	.LC4(%rip), %rax
	movq	%rax, %rdi
	call	Print@PLT
	movl	$16, %edi
	call	IncrementCursorY@PLT
	movl	$0, %edi
	call	SetCursorX@PLT
	movl	$16711680, %esi
	leaq	.LC8(%rip), %rax
	movq	%rax, %rdi
	call	Print@PLT
#APP
# 303 "./kernel/kernel.c" 1
	int3
# 0 "" 2
#NO_APP
.L2:
	jmp	.L2
	.cfi_endproc
.LFE0:
	.size	kernel_main, .-kernel_main
	.ident	"GCC: (Ubuntu 11.4.0-1ubuntu1~22.04) 11.4.0"
	.section	.note.GNU-stack,"",@progbits
	.section	.note.gnu.property,"a"
	.align 8
	.long	1f - 0f
	.long	4f - 1f
	.long	5
0:
	.string	"GNU"
1:
	.align 8
	.long	0xc0000002
	.long	3f - 2f
2:
	.long	0x3
3:
	.align 8
4:
