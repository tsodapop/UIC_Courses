	.section	__TEXT,__text,regular,pure_instructions
	.macosx_version_min 10, 13
	.globl	_main                   ## -- Begin function main
	.p2align	4, 0x90
_main:                                  ## @main
	.cfi_startproc
## BB#0:
	pushq	%rbp
Lcfi0:
	.cfi_def_cfa_offset 16
Lcfi1:
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
Lcfi2:
	.cfi_def_cfa_register %rbp
	subq	$32, %rsp
	movabsq	$5817882423726, %rax    ## imm = 0x54A94D0B1AE
	movl	$0, -4(%rbp)
	movl	$0, -8(%rbp)
	movq	%rax, -16(%rbp)
LBB0_1:                                 ## =>This Inner Loop Header: Depth=1
	movslq	-8(%rbp), %rax
	movq	-16(%rbp), %rcx
	andq	$1, %rcx
	xorq	%rcx, %rax
	movl	%eax, %edx
	movl	%edx, -8(%rbp)
	movq	-16(%rbp), %rax
	shrq	$1, %rax
	movq	%rax, -16(%rbp)
## BB#2:                                ##   in Loop: Header=BB0_1 Depth=1
	cmpq	$0, -16(%rbp)
	jne	LBB0_1
## BB#3:
	leaq	L_.str(%rip), %rdi
	movl	-8(%rbp), %esi
	movb	$0, %al
	callq	_printf
	xorl	%esi, %esi
	movl	%eax, -20(%rbp)         ## 4-byte Spill
	movl	%esi, %eax
	addq	$32, %rsp
	popq	%rbp
	retq
	.cfi_endproc
                                        ## -- End function
	.section	__TEXT,__cstring,cstring_literals
L_.str:                                 ## @.str
	.asciz	"ans %d\n"


.subsections_via_symbols
