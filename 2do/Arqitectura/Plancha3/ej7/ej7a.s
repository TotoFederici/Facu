.data
a:		.quad 0xffff44444444ffff 

.text
.global main
main:
	movq a, %rax
	rol $32, %rax
	ret