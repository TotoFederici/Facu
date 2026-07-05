/* #include <stdio.h>
#include <stdlib.h>
int main(int argc, char *argv[]) {
    if (argc < 2){
        printf("La cantidad de argumentos es insuficiente\n");
} else {
    int suma=0;
        for (int i=1; i<argc; i++){
            suma = suma + atoi(argv[i]);
        }
        printf("Cantidad de argumentos: %d, suma de los argumentos: %d\n", argc, suma);
    }
    return 0;
} 
*/

.data
msg1: .asciz "La cantidad de argumentos es insuficiente\n"
msg2: .asciz "Cantidad de argumentos: %d, suma de los argumentos: %d\n"

.text
.global main
main:

#--------------------

    cmpq $2 , %rdi
    jl print

#--------------------

    movq $0 ,%r15
    movq %rdi, %r14
    decq %r14
    movq %rdi , %rcx
    decq %rcx

    movq $1, %rbx
    
#--------------------
etiqueta:   
#-----------------------

    movq (%rsi, %rbx, 8), %rdi
    incq %rbx

#-----------------------

    pushq %rbp
    pushq %rcx
    pushq %rsi

    call atoi

    popq %rsi
    popq %rcx
    popq %rbp

    addq %rax , %r15

#-----------------------

    loop etiqueta

#----------------------- #Variables para el printf final

    xorq %rax , %rax
    movq $msg2 , %rdi
    movq %r14 , %rsi
    movq %r15 , %rdx

#-----------------------
    call printf

    movq %r15, %rax

    ret

print:
    movq $msg1 , %rdi
    call printf
    ret 

