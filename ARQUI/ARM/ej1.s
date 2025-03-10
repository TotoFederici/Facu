.data
	array: .word 1, 2, 3, 4, 5, 6, 7, 8, 9, 0

.text
.global main
main:
	ldr r2, =array
	MOV r1, #0

	ldr r3, [r2,#24]
	add r0, r3, r1

	ldr r3, [r2,#28]
	add r3, r1
	str r3, [r2,#32]

	bx lr