.data
	a: .word 1, 2, 3, 4
	b: .word 5, 6, 7, 8
	l: .word 4
	msg: .asciz "La suma de los arreglos es %d\n"

.text
.global main
main:
	MOV r0, #0
	LDR r1, =a
	LDR r2, =b
	LDR r3, =l
	LDR r3, [r3]
	PUSH {lr}
	bl suma
	POP {lr}

	PUSH {lr}
	MOV r1, r0
	LDR r0, =msg
	bl printf 
	POP {lr}

	bx lr

suma:	# r0 = result, r1 = a, r2 = b, r3 = l
	CMP r3, #0
	bxEQ lr
	MOV r4, #0
	loop:
		LDR r5, [r1,r4]
		LDR r6, [r2,r4]
		ADD r0, r5
		ADD r0, r6
		SUB r3, #1
		ADD r4, #4
		CMP r3, #0
		bNE loop
	bx lr