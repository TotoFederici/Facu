.text
.global main
main:
	MOV r8, #2

	MOV r4, #20
	MOV r5, #7
	MOV r6, #0
loop:
	AND r7, r5, #1
	cmp r7, #0
	ADDNE r6, r4
	SUBNE r5, #1
	MULEQ r6, r6, r8
	LSREQ r5, #1
	cmp r5, #1
	bNE loop

	ADD r6, r4
	bx lr