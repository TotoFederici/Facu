.text
.global main
main:
	MOV r2, #0x29, 22
	MOV r2, #0xF6, 30
	MOV r2, #0x5D, 22
	MOV r2,	#0x66, 26
	MVN r2, #0xFF
	MVN r2, #0x0
	bx lr