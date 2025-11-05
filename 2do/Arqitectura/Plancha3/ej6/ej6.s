.global main
main:
	// a)
	movl $1, %rax
	sall $31, %rax

	// b)
	movl $1, %rax
	sall $31, %rax
	movl $1, %rbx
	sall $15, %rbx
	orl %rax, %rbx

	// c)
	movl $-1, %rax
	movl $1, %rbx
	sall $8, %rbx
	andl %rax, %rbx

	// d)
	movl $0xaa, %rax
	movl $0xaa, %rbx
	sall $24, %rbx
	orl %rax, %rbx

	// e)
	movl $5, %rax
	sall $8, %rax

	// f)
	movl $-1, %rax
	movl $1, %rbx
	sall $8, %rbx
	notl %rbx
	andl %rax, %rbx

	// g)
	movl $0, %rax
	movl $1, %rbx
	subl %rbx, %rax

	// h)
	movl $0x80000000, %rax
	movl $0x80000000, %rbx
	addl %rax, %rbx

	ret