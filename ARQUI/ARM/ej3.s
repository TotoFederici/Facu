.data
	a: .word 0xbeefface

.text
.global main
main:
	ldr r3, =a
	ldrb r4, [r3]
	bx lr