.data
a: 	.quad 0x781fa8c9d034e77f

.text
.global main
main:
	movq a, %rax
	movq $64, %rcx
	movq $0, %rbx 

bucle:
	rol $1, %rax
	adcq $0, %rbx
	loop bucle
	movq %rbx, %rax

	leaq 
	ret