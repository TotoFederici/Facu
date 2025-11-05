.data
	i: .word 4

.text
.global main
main:
	LDR r4, =i
	PUSH {lr}
	bl foo
	POP {lr}
	bx lr

foo:
	MOV r0, #4
	AND r0, r0, #1
	bx lr