.data
    a: .byte '1'
    b: .byte '2'
    c: .byte '3'
    d: .long '4'
    e: .byte '5'
    # f: .float 1.0
    # g: .double 2.0
    h: .long 6
    i: .long 7
    j: .long 8
.text
.global calculo
calculo:

#---tomamos variables de la pila
    popq %rbp

    xorq %rax, %rax
    xorq %r15, %r15
    xorq %r14, %r14
    popq %r15
    popq %r14
        
#------------------
    pushq %rbp
    
    movq %rsp, %rbp

    addq %rdi , %rax
    addq %rsi, %rax
    addq %rdx, %rax

    xorq %r12, %r12
    addq %r15, %r12
    addq %r14, %r12
    imulq %r12

    movq %rbp, %rsp
    popq %rbp

    ret

.global main
main:
#------------------------------------
    
#------------------------------------    
    xorq %rdi, %rdi
    xorq %rsi, %rsi
    xorq %rdx, %rdx
    xorq %rcx, %rcx
    xorq %r8, %r8
    xorq %r9, %r9
    xorq %r13, %r13
    xorq %r14, %r14

    movb a , %dil
    movb b , %sil
    movb c , %dl
    movb d , %cl
    movb e , %r8b 
    # movsd $f , %xmm1
    # movl $g ,%r8d
    movl h ,%r9d
    movl i ,%r15d
    movl j ,%r14d
    pushq %r14
    pushq %r15
    call calculo 
#------------------------------------
   
#------------------------------------
    ret