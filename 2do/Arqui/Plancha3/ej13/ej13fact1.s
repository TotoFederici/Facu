

.global fact1
fact1:
    xorq %rdx, %rdx
    movq $1, %rax
comp:
    cmpq $1 , %rdi
    jng etiqueta
    imulq %rdi
    decq %rdi

    jmp comp

etiqueta:
    retq