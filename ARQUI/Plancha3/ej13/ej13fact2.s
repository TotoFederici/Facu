
.global fact2
fact2:
    xorq %rdx ,%rdx
    movq $1, %rax

    cmpq $0, %rdi
    jz  base
    
    movq %rdi, %rcx

    etiqueta:

    imulq %rcx 

    loop etiqueta
    
base:
    retq



     