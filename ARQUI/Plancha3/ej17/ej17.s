.data
format: .asciz "%ld\n"
formatHex: .asciz "0x%lx\n"
i: .quad 0xDEADBEEF

.text
.global main
main:
	movq $format, %rdi # El primer argumento es el formato.
	movq $1234, %rsi # El valor a imprimir.
	xorq %rax, %rax # Cantidad de valores de punto flotante.
	call printf

	# a)
	movq $format, %rdi
	movq %rsp, %rsi
	xorq %rax, %rax
	call printf

	# b)
	movq $formatHex, %rdi
	leaq format, %rsi
	xorq %rax, %rax
	call printf

	# c)
	movq $formatHex, %rdi
	leaq formatHex, %rsi
	xorq %rax, %rax
	call printf

	# d)
	movq $format, %rdi
	movq (%rsp), %rsi
	xorq %rax, %rax
	call printf

	# e)
	movq $format, %rdi
	movq 8(%rsp), %rsi
	xorq %rax, %rax
	call printf
	
	# f)
	movq $formatHex, %rdi
	movq i, %rsi
	xorq %rax, %rax
	call printf

	# g)
	movq $formatHex, %rdi
	leaq i, %rsi
	xorq %rax, %rax
	call printf

	ret