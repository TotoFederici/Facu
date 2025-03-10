.data
a:		.byte 1, 2, 3, 4, 5
len:	.byte 5

.text
.global main
main:
	leaq a, %rax
	movq len, %rcx
	xorq %rbx, %rbx # Se inicializa rbx = 0, se utiliza para el direccionamiento de memoria
	jmp bucle_push
ret1:
	movq len, %rcx
	xorq %rbx, %rbx
	jmp bucle_pop
ret2:
	ret

bucle_push:
	movb (%rax, %rbx), %dl
	movzbw %dl, %dx
	pushw %dx
	incq %rbx
	loop bucle_push
	jmp ret1
	
bucle_pop:
	popw %dx
	movb %dl, (%rax, %rbx)
	incq %rbx
	loop bucle_pop
	jmp ret2