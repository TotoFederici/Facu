.data
msg: .asciz "Cantidad de argumentos ingresados: %ld. La suma es %ld.\n"
msg1: .asciz "Ingrese al menos un argumento\n"

.text
.global main
main:
	movq %rdi, %r15
	cmp $1, %r15
	jz no_args
	dec %r15
	
	call suma

	movq $msg, %rdi
	movq %r15, %rsi
	movq %r14, %rdx

	pushq %rbp 
	call printf
	popq %rbp
	ret
no_args:
	movq $msg1, %rdi
	pushq %rbp 
	call printf
	popq %rbp
	ret

suma:
#------------prologo-------------
	pushq %rbp 
	movq %rsp, %rbp
#--------------------------------
	movq %rdi, %rcx
	dec %rcx
	movq $1, %rbx
	xorq %r14, %r14

bucle:
	movq (%rsi, %rbx, 8), %rdi
	inc %rbx
	xorq %rax, %rax

	pushq %rbp 
	pushq %rsi
	pushq %rcx
	call atoi
	popq %rcx
	popq %rsi
	popq %rbp

	imul %rax
	addq %rax, %r14

	loop bucle
#------------epilogo-------------
	movq %rbp, %rsp
	popq %rbp
	ret
#--------------------------------