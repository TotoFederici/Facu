.data
    a: .long 1, 2, 3, 4
    g: .quad 0x1122334455667788
    msg: .asciz "Imprime %c\n"
.text
.global main
main:
    movq $0x7fffffffebc8, %rsp
    subq $8, %rsp # rsp = 0x7fffffffebc0
    movq $g, %rax # rax = 0x404028
    movl g+4, %eax # rax = 0x11223344
    movq $3, %rbx # rbx = 0x3
    movb a(,%rbx,4), %al # rax = 0x11223304
    leaq msg, %rdi # rdi = 0x404030
    movb (%rdi, %rbx, 2), %sil # sil = 0x65 
    xorl %eax, %eax # rax = 0x0
    call printf # rax = 0xa
    addq $8, %rsp # rsp = 0x7fffffffebc8
    ret
    
    
    # d) Imprimiria "Imprime e"
