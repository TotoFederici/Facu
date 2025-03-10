.data
	a: .float 2
	b: .float 2
	c: .float 3
	d: .float 1
	msg: .asciz "El determinante es: %f\n"

.text
.global main
main:
	ldr r0, =a
	ldr r1, =b
	ldr r2, =c
	ldr r3, =d
	vldr.f32 s0, [r0]
	vldr.f32 s1, [r1]
	vldr.f32 s2, [r2]
	vldr.f32 s3, [r3]
	
	push {lr}
	bl determinante
	pop {lr}

	push {lr}
	vcvt.f64.f32 d1, s0
	vmov r1, r2, d1
	ldr r0, =msg
	bl printf
	pop {lr}

	mov r0, #0
	bx lr

determinante:
	vmul.f32 s4,s0,s3
	vmul.f32 s5,s1,s2
	vsub.f32 s0,s4,s5
	bx lr