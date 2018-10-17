	.file	"foo.c"
	.section	.text.unlikely,"ax",@progbits
.LCOLDB0:
	.text
.LHOTB0:
	.p2align 4,,15
	.globl	foo
	.type	foo, @function
foo:
	movl	B(%rip), %eax
	addl	$1, %eax
	movl	%eax, A(%rip)
	movl	$0, B(%rip)
	ret
	.size	foo, .-foo
	.section	.text.unlikely
.LCOLDE0:
	.text
.LHOTE0:
	.comm	B,4,4
	.comm	A,4,4
	.ident	"GCC: (Ubuntu 5.4.0-6ubuntu1~16.04.10) 5.4.0 20160609"
	.section	.note.GNU-stack,"",@progbits
