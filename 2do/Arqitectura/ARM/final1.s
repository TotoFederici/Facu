.data
	a: .double 10, 11, 102, 18, 2020
	l: .word 5
	msg1: .asciz "El resultado es: %f\n"
	msg2: .asciz "Calculando el promedio...\n"

.text
.global main
main:
	ldr r0, =a
	ldr r1, =l
	ldr r1, [r1]
	push {lr}
	bl promedio
	pop {lr}

	push {lr}
	vmov r1, r2, d0
	ldr r0, =msg1
	bl printf
	pop {lr}
	bx lr

promedio:
	mov r4, r0
	mov r5, r1

	push {lr}
	ldr	r0, =msg2
	bl printf
	pop {lr}

	mov r0, #0
	vmov.f64 d1, r0, r0
	vmov s5, r5
	vcvt.f32.s32 s6, s5
	vcvt.f64.f32 d2, s6
	loop:
		vldr.f64 d1, [r4]
		vadd.f64 d0, d0, d1
		add r4, #8
		sub r5, #1
		cmp r5, #0
		bNE loop
	vdiv.f64 d0, d0, d2
	bx lr