.data
.align 16
a: .float 1.4223, 5.555, 0.099, 0.1, 2.72, 3.1415, 0.2, 1.414, 5.555
.align 16
b: .float 3.1415, 2.72, 1.414, 0.2, 1.4223, 5.555, 0.099, 0.1, 0.099
        # 4.5638, 8.275, 1.513, 0.3, 4.1423, 8.6970, 0.299, 1.514, 5.654
len: .byte 9

.text
.global main
main:
	xorq %rdx, %rdx
	xorps %xmm1, %xmm1
	movq len, %rax
	movq $0x4, %r15
	divq %r15
	movq %rax, %rcx

	leaq a, %rax
	leaq b, %rbx
	xorq %r15, %r15
	jmp bucle1
ret_bucle1:
	cmp $0x0, %rdx
	jnz no_mult
ret:
	ret

bucle1:
	movaps (%rax, %r15, 4), %xmm0
	movaps (%rbx, %r15, 4), %xmm1
	addps %xmm1, %xmm0
	movaps %xmm0, (%rax, %r15, 4)
	addq $0x4, %r15
	loop bucle1
	jmp ret_bucle1

no_mult:
	movq %rdx, %rcx
bucle2:
	movss (%rax, %r15, 4), %xmm0
	movss (%rbx, %r15, 4), %xmm1
	addss %xmm1, %xmm0
	movss %xmm0, (%rax, %r15, 4)
	incq %r15
	loop bucle2
	jmp ret