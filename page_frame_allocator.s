	.file	"page_frame_allocator.c"
	.text
	.globl	freeMem
	.bss
	.align 8
	.type	freeMem, @object
	.size	freeMem, 8
freeMem:
	.zero	8
	.globl	reservedMem
	.align 8
	.type	reservedMem, @object
	.size	reservedMem, 8
reservedMem:
	.zero	8
	.globl	usedMem
	.align 8
	.type	usedMem, @object
	.size	usedMem, 8
usedMem:
	.zero	8
	.globl	initialized
	.type	initialized, @object
	.size	initialized, 1
initialized:
	.zero	1
	.text
	.globl	ReadEFIMemoryMap
	.type	ReadEFIMemoryMap, @function
ReadEFIMemoryMap:
.LFB0:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$96, %rsp
	movq	%rdi, -72(%rbp)
	movq	%rsi, -80(%rbp)
	movq	%rdx, -88(%rbp)
	movq	%rcx, -96(%rbp)
	movzbl	initialized(%rip), %eax
	testb	%al, %al
	jne	.L10
	movq	-88(%rbp), %rax
	movl	$0, %edx
	divq	-96(%rbp)
	movq	%rax, -40(%rbp)
	movq	$0, -56(%rbp)
	movq	$0, -48(%rbp)
	movl	$0, -64(%rbp)
	jmp	.L4
.L6:
	movl	-64(%rbp), %eax
	cltq
	imulq	-96(%rbp), %rax
	movq	%rax, %rdx
	movq	-80(%rbp), %rax
	addq	%rdx, %rax
	movq	%rax, -8(%rbp)
	movq	-8(%rbp), %rax
	movl	(%rax), %eax
	cmpl	$7, %eax
	jne	.L5
	movq	-8(%rbp), %rax
	movq	24(%rax), %rax
	salq	$12, %rax
	cmpq	%rax, -48(%rbp)
	jnb	.L5
	movq	-8(%rbp), %rax
	movq	8(%rax), %rax
	movq	%rax, -56(%rbp)
	movq	-8(%rbp), %rax
	movq	24(%rax), %rax
	salq	$12, %rax
	movq	%rax, -48(%rbp)
.L5:
	addl	$1, -64(%rbp)
.L4:
	movl	-64(%rbp), %eax
	cltq
	cmpq	%rax, -40(%rbp)
	ja	.L6
	movq	-96(%rbp), %rdx
	movq	-40(%rbp), %rcx
	movq	-80(%rbp), %rax
	movq	%rcx, %rsi
	movq	%rax, %rdi
	call	GetMemorySize@PLT
	movq	%rax, -32(%rbp)
	movq	-32(%rbp), %rax
	movq	%rax, freeMem(%rip)
	movq	-32(%rbp), %rax
	shrq	$15, %rax
	addq	$1, %rax
	movq	%rax, -24(%rbp)
	movq	-56(%rbp), %rdx
	movq	-24(%rbp), %rcx
	movq	-72(%rbp), %rax
	movq	%rcx, %rsi
	movq	%rax, %rdi
	call	InitBitmap
	movq	-72(%rbp), %rax
	movq	(%rax), %rax
	shrq	$12, %rax
	leaq	1(%rax), %rdx
	movq	-72(%rbp), %rcx
	movq	-72(%rbp), %rax
	movq	%rcx, %rsi
	movq	%rax, %rdi
	call	LockPages
	movl	$0, -60(%rbp)
	jmp	.L7
.L9:
	movl	-60(%rbp), %eax
	cltq
	imulq	-96(%rbp), %rax
	movq	%rax, %rdx
	movq	-80(%rbp), %rax
	addq	%rdx, %rax
	movq	%rax, -16(%rbp)
	movq	-16(%rbp), %rax
	movl	(%rax), %eax
	cmpl	$7, %eax
	je	.L8
	movq	-16(%rbp), %rax
	movq	24(%rax), %rdx
	movq	-16(%rbp), %rax
	movq	8(%rax), %rcx
	movq	-72(%rbp), %rax
	movq	%rcx, %rsi
	movq	%rax, %rdi
	call	ReservePages
.L8:
	addl	$1, -60(%rbp)
.L7:
	movl	-60(%rbp), %eax
	cltq
	cmpq	%rax, -40(%rbp)
	ja	.L9
	jmp	.L1
.L10:
	nop
.L1:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE0:
	.size	ReadEFIMemoryMap, .-ReadEFIMemoryMap
	.globl	InitBitmap
	.type	InitBitmap, @function
InitBitmap:
.LFB1:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$32, %rsp
	movq	%rdi, -8(%rbp)
	movq	%rsi, -16(%rbp)
	movq	%rdx, -24(%rbp)
	movq	-8(%rbp), %rax
	movq	-16(%rbp), %rdx
	movq	%rdx, (%rax)
	movq	-8(%rbp), %rax
	movq	-24(%rbp), %rdx
	movq	%rdx, 8(%rax)
	movq	-8(%rbp), %rax
	movq	(%rax), %rdx
	movq	-8(%rbp), %rax
	movq	8(%rax), %rax
	movl	$0, %esi
	movq	%rax, %rdi
	call	memset@PLT
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE1:
	.size	InitBitmap, .-InitBitmap
	.globl	FreePage
	.type	FreePage, @function
FreePage:
.LFB2:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$32, %rsp
	movq	%rdi, -24(%rbp)
	movq	%rsi, -32(%rbp)
	movq	-32(%rbp), %rax
	shrq	$12, %rax
	movq	%rax, -8(%rbp)
	movq	-24(%rbp), %rax
	movq	-8(%rbp), %rdx
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	Bitmap_Get@PLT
	xorl	$1, %eax
	testb	%al, %al
	jne	.L15
	movq	-24(%rbp), %rax
	movq	-8(%rbp), %rcx
	movl	$0, %edx
	movq	%rcx, %rsi
	movq	%rax, %rdi
	call	Bitmap_Set@PLT
	movq	freeMem(%rip), %rax
	addq	$4096, %rax
	movq	%rax, freeMem(%rip)
	movq	usedMem(%rip), %rax
	subq	$4096, %rax
	movq	%rax, usedMem(%rip)
	jmp	.L12
.L15:
	nop
.L12:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2:
	.size	FreePage, .-FreePage
	.globl	FreePages
	.type	FreePages, @function
FreePages:
.LFB3:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$48, %rsp
	movq	%rdi, -24(%rbp)
	movq	%rsi, -32(%rbp)
	movq	%rdx, -40(%rbp)
	movl	$0, -4(%rbp)
	jmp	.L17
.L18:
	movl	-4(%rbp), %eax
	sall	$12, %eax
	movslq	%eax, %rdx
	movq	-32(%rbp), %rax
	addq	%rdx, %rax
	movq	%rax, %rdx
	movq	-24(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	FreePage
	addl	$1, -4(%rbp)
.L17:
	movl	-4(%rbp), %eax
	cltq
	cmpq	%rax, -40(%rbp)
	ja	.L18
	nop
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE3:
	.size	FreePages, .-FreePages
	.globl	LockPage
	.type	LockPage, @function
LockPage:
.LFB4:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$32, %rsp
	movq	%rdi, -24(%rbp)
	movq	%rsi, -32(%rbp)
	movq	-32(%rbp), %rax
	shrq	$12, %rax
	movq	%rax, -8(%rbp)
	movq	-24(%rbp), %rax
	movq	-8(%rbp), %rdx
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	Bitmap_Get@PLT
	testb	%al, %al
	jne	.L22
	movq	-24(%rbp), %rax
	movq	-8(%rbp), %rcx
	movl	$1, %edx
	movq	%rcx, %rsi
	movq	%rax, %rdi
	call	Bitmap_Set@PLT
	movq	freeMem(%rip), %rax
	subq	$4096, %rax
	movq	%rax, freeMem(%rip)
	movq	usedMem(%rip), %rax
	addq	$4096, %rax
	movq	%rax, usedMem(%rip)
	jmp	.L19
.L22:
	nop
.L19:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE4:
	.size	LockPage, .-LockPage
	.globl	LockPages
	.type	LockPages, @function
LockPages:
.LFB5:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$48, %rsp
	movq	%rdi, -24(%rbp)
	movq	%rsi, -32(%rbp)
	movq	%rdx, -40(%rbp)
	movl	$0, -4(%rbp)
	jmp	.L24
.L25:
	movl	-4(%rbp), %eax
	sall	$12, %eax
	movslq	%eax, %rdx
	movq	-32(%rbp), %rax
	addq	%rdx, %rax
	movq	%rax, %rdx
	movq	-24(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	LockPage
	addl	$1, -4(%rbp)
.L24:
	movl	-4(%rbp), %eax
	cltq
	cmpq	%rax, -40(%rbp)
	ja	.L25
	nop
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE5:
	.size	LockPages, .-LockPages
	.globl	UnreservePage
	.type	UnreservePage, @function
UnreservePage:
.LFB6:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$32, %rsp
	movq	%rdi, -24(%rbp)
	movq	%rsi, -32(%rbp)
	movq	-32(%rbp), %rax
	shrq	$12, %rax
	movq	%rax, -8(%rbp)
	movq	-24(%rbp), %rax
	movq	-8(%rbp), %rdx
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	Bitmap_Get@PLT
	xorl	$1, %eax
	testb	%al, %al
	jne	.L29
	movq	-24(%rbp), %rax
	movq	-8(%rbp), %rcx
	movl	$0, %edx
	movq	%rcx, %rsi
	movq	%rax, %rdi
	call	Bitmap_Set@PLT
	movq	freeMem(%rip), %rax
	addq	$4096, %rax
	movq	%rax, freeMem(%rip)
	movq	reservedMem(%rip), %rax
	subq	$4096, %rax
	movq	%rax, reservedMem(%rip)
	jmp	.L26
.L29:
	nop
.L26:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE6:
	.size	UnreservePage, .-UnreservePage
	.globl	UnreservePages
	.type	UnreservePages, @function
UnreservePages:
.LFB7:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$48, %rsp
	movq	%rdi, -24(%rbp)
	movq	%rsi, -32(%rbp)
	movq	%rdx, -40(%rbp)
	movl	$0, -4(%rbp)
	jmp	.L31
.L32:
	movl	-4(%rbp), %eax
	sall	$12, %eax
	movslq	%eax, %rdx
	movq	-32(%rbp), %rax
	addq	%rdx, %rax
	movq	%rax, %rdx
	movq	-24(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	UnreservePage
	addl	$1, -4(%rbp)
.L31:
	movl	-4(%rbp), %eax
	cltq
	cmpq	%rax, -40(%rbp)
	ja	.L32
	nop
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE7:
	.size	UnreservePages, .-UnreservePages
	.globl	ReservePages
	.type	ReservePages, @function
ReservePages:
.LFB8:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$48, %rsp
	movq	%rdi, -24(%rbp)
	movq	%rsi, -32(%rbp)
	movq	%rdx, -40(%rbp)
	movl	$0, -4(%rbp)
	jmp	.L34
.L35:
	movl	-4(%rbp), %eax
	sall	$12, %eax
	movslq	%eax, %rdx
	movq	-32(%rbp), %rax
	addq	%rdx, %rax
	movq	%rax, %rdx
	movq	-24(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	ReservePage
	addl	$1, -4(%rbp)
.L34:
	movl	-4(%rbp), %eax
	cltq
	cmpq	%rax, -40(%rbp)
	ja	.L35
	nop
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE8:
	.size	ReservePages, .-ReservePages
	.globl	ReservePage
	.type	ReservePage, @function
ReservePage:
.LFB9:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$32, %rsp
	movq	%rdi, -24(%rbp)
	movq	%rsi, -32(%rbp)
	movq	-32(%rbp), %rax
	shrq	$12, %rax
	movq	%rax, -8(%rbp)
	movq	-24(%rbp), %rax
	movq	-8(%rbp), %rdx
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	Bitmap_Get@PLT
	testb	%al, %al
	jne	.L39
	movq	-24(%rbp), %rax
	movq	-8(%rbp), %rcx
	movl	$1, %edx
	movq	%rcx, %rsi
	movq	%rax, %rdi
	call	Bitmap_Set@PLT
	movq	freeMem(%rip), %rax
	subq	$4096, %rax
	movq	%rax, freeMem(%rip)
	movq	reservedMem(%rip), %rax
	addq	$4096, %rax
	movq	%rax, reservedMem(%rip)
	jmp	.L36
.L39:
	nop
.L36:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE9:
	.size	ReservePage, .-ReservePage
	.globl	GetFreeRAM
	.type	GetFreeRAM, @function
GetFreeRAM:
.LFB10:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movq	%rdi, -8(%rbp)
	movq	freeMem(%rip), %rax
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE10:
	.size	GetFreeRAM, .-GetFreeRAM
	.globl	GetUsedRAM
	.type	GetUsedRAM, @function
GetUsedRAM:
.LFB11:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movq	%rdi, -8(%rbp)
	movq	usedMem(%rip), %rax
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE11:
	.size	GetUsedRAM, .-GetUsedRAM
	.globl	GetReservedRAM
	.type	GetReservedRAM, @function
GetReservedRAM:
.LFB12:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movq	%rdi, -8(%rbp)
	movq	reservedMem(%rip), %rax
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE12:
	.size	GetReservedRAM, .-GetReservedRAM
	.globl	InitPageFrameAllocator
	.type	InitPageFrameAllocator, @function
InitPageFrameAllocator:
.LFB13:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movq	%rdi, -8(%rbp)
	movq	%rsi, -16(%rbp)
	movq	%rdx, -24(%rbp)
	movq	%rcx, -32(%rbp)
	movq	-8(%rbp), %rax
	leaq	ReadEFIMemoryMap(%rip), %rdx
	movq	%rdx, 16(%rax)
	movq	-8(%rbp), %rax
	leaq	FreePage(%rip), %rdx
	movq	%rdx, 24(%rax)
	movq	-8(%rbp), %rax
	leaq	FreePages(%rip), %rdx
	movq	%rdx, 32(%rax)
	movq	-8(%rbp), %rax
	leaq	LockPage(%rip), %rdx
	movq	%rdx, 40(%rax)
	movq	-8(%rbp), %rax
	leaq	LockPages(%rip), %rdx
	movq	%rdx, 48(%rax)
	movq	-8(%rbp), %rax
	leaq	GetFreeRAM(%rip), %rdx
	movq	%rdx, 64(%rax)
	movq	-8(%rbp), %rax
	leaq	GetUsedRAM(%rip), %rdx
	movq	%rdx, 72(%rax)
	movq	-8(%rbp), %rax
	leaq	GetReservedRAM(%rip), %rdx
	movq	%rdx, 80(%rax)
	movq	-8(%rbp), %rax
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE13:
	.size	InitPageFrameAllocator, .-InitPageFrameAllocator
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
