.data
list: .long 10,20,30,40,50,60,70,80,90,100
length: .byte 10
msg: .asciz "Max: %d, Min: %d, Promedio: %d\n"

.text
.global main

Suma_lista:
#------------prologo-------------
	pushq %rbp 
	movq %rsp, %rbp
#-------------------------------
	movq %rdi, %r12
	movl %esi, %r13d
	movl %edx, %r14d

	xorl %ebx, %ebx # en ebx se guarda la suma total
	xorq %rcx, %rcx
	movb length, %cl
bucle:
	movl -4(%r12, %rcx, 4), %r15d
	addl %r15d, %ebx

	cmp %r15d, %r13d
	cmovs %r15d, %r13d

	cmp %r14d, %r15d 
	cmovs %r15d, %r14d

	loop bucle
#------------epilogo-------------
	movq %rbp, %rsp
	popq %rbp
	ret
#--------------------------------


Calc_Promedio:
#------------prologo-------------
	pushq %rbp 
	movq %rsp, %rbp
#-------------------------------
	movq %rdi, %rax
	xorq %rbx, %rbx
	movb length, %bl
	xorq %rdx, %rdx
	divq %rbx
#------------epilogo-------------
	movq %rbp, %rsp
	popq %rbp
	ret
#--------------------------------

main: 
	leaq list, %rdi # rdi guarda la direccion de la lista
	movl (%rdi), %esi # rsi guardara el Max, se inicializa como el primer elemento de la lista
	movl (%rdi), %edx # rdx guardara el Min, se inicializa como el primer elemento de la lista
	xorq %rax, %rax
	call Suma_lista

	movl %ebx, %edi
	xorq %rax, %rax
	call Calc_Promedio

	# llamadad a printf
	lea msg, %rdi
	movl %r13d, %esi
	movl %r14d, %edx
	movl %eax, %ecx
	pushq %rbp 
	call printf
	popq %rbp
	ret