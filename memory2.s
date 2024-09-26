	.file	"memory2.c"
	.text
	.globl	GetMemorySize
	.type	GetMemorySize, @function
GetMemorySize:
.LFB0:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movq	%rdi, -24(%rbp)
	movq	%rsi, -32(%rbp)
	movq	%rdx, -40(%rbp)
	movq	memory_size_bytes.0(%rip), %rax
	testq	%rax, %rax
	je	.L2
	movq	memory_size_bytes.0(%rip), %rax
	jmp	.L3
.L2:
	movl	$0, -12(%rbp)
	jmp	.L4
.L5:
	movl	-12(%rbp), %eax
	cltq
	imulq	-40(%rbp), %rax
	movq	%rax, %rdx
	movq	-24(%rbp), %rax
	addq	%rdx, %rax
	movq	%rax, -8(%rbp)
	movq	-8(%rbp), %rax
	movq	24(%rax), %rax
	salq	$12, %rax
	movq	%rax, %rdx
	movq	memory_size_bytes.0(%rip), %rax
	addq	%rdx, %rax
	movq	%rax, memory_size_bytes.0(%rip)
	addl	$1, -12(%rbp)
.L4:
	movl	-12(%rbp), %eax
	cltq
	cmpq	%rax, -32(%rbp)
	ja	.L5
	movq	memory_size_bytes.0(%rip), %rax
.L3:
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE0:
	.size	GetMemorySize, .-GetMemorySize
	.local	memory_size_bytes.0
	.comm	memory_size_bytes.0,8,8
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
