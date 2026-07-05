.data
	t: .float 1, 2, 3, 4, 5
	o: .float 2, 4, 6, 8, 10
	m: .float 0, 0, 0, 0, 0
	msg: .asciz "La suma de las componentes es %f\n"

.text
.global main
main:
	ldr r0, =t
	ldr r1, =o
	ldr r2, =m
	push {lr}
	bl suma
	pop {lr}

	push {lr}
	vcvt.f64.f32 d1, s0
	vmov r1, r2, d1
	ldr r0, =msg
	bl printf
	pop {lr}
	bx lr

suma:
	mov r3, #5
	mov r4, #0
	vmov.f32 s0, r4
	loop:
		vldr.f32 s1, [r0]
		add r0, #4
		vldr.f32 s2, [r1]
		add r1, #4
		vadd.f32 s3, s1, s2
		vstr.f32 s3, [r2]
		add r2, #4
		vadd.f32 s0, s0, s3
		add r4, #4
		sub r3, #1
		cmp r3, #0
		bNE loop
	bx lr