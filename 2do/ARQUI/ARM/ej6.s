.text
.global main
main:
	MOV r0, #0xD3, 2
	MVN r0, #0x0
	MVN r0, #0x1
	bx lr