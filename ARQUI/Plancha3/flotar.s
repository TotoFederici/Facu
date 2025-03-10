.data
a: .float 1.4223, 5.555, 0.099, 0.1
b: .float 3.1415, 2.72, 1.414, 0.2
len: .byte 4

.text
.global main
main:
	movq len, %rcx
	leaq a, %rax
	leaq b, %rbx
	xorq %r15, %r15
bucle:
	movss (%rax, %r15, 4), %xmm0
	movss (%rbx, %r15, 4), %xmm1
	addss %xmm1, %xmm0
	movss %xmm0, (%rax, %r15, 4)
	incq %r15
	loop bucle

	ret