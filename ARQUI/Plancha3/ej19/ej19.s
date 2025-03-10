.data
a: .quad 0x7fffffff
b: .quad 1
format: .asciz "0x%x\n"
msg1: .asciz "Ejecutando foo1\n"
msg2: .asciz "Ejecutando foo2\n"
msg3: .asciz "0x%x 0x%x\n"

.text

foo1:
#------------prologo-------------
	pushq %rbp 
	movq %rsp, %rbp
#--------------------------------
	movq $msg1, %rdi
	pushq %rbp 
	call printf
	popq %rbp

	salq $31, %r13
	addq %r13, %r12 

	movq $format, %rdi
	movq %r12, %rsi
	pushq %rbp 
	call printf
	popq %rbp

	movq %r12, %rax
#------------epilogo-------------
	movq %rbp, %rsp
	popq %rbp
	ret
#--------------------------------

foo2:
#------------prologo-------------
	pushq %rbp 
	movq %rsp, %rbp
#--------------------------------
	movq $msg2, %rdi
	pushq %rbp 
	call printf
	popq %rbp

	addq %r13, %r12

	movq $format, %rdi
	movq %r12, %rsi
	pushq %rbp 
	call printf
	popq %rbp

	movq %r12, %rax
#------------epilogo-------------
	movq %rbp, %rsp
	popq %rbp
	ret
#--------------------------------


.global main
main:
	movq a, %r12
	movq b, %r13
	xorq %rax, %rax
	call foo2
	movq %rax, %rbx

	movq b, %r13
	xorq %rax, %rax
	call foo1

	movq $msg3, %rdi
	movq %rax, %rsi
	movq %rbx, %rdx
	call printf

	xorq %rax, %rax
	ret