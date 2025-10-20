#include <omp.h>
#include <stdio.h>

int main(){
    #pragma omp parallel
    {
        #pragma omp sections
        {
            #pragma omp section
            {
                printf("HOLA SOY EL THREAD %d (Seccion 0)\n", omp_get_thread_num());
            }

            #pragma omp section
            {
                printf("HOLA SOY EL THREAD %d (Seccion 1)\n", omp_get_thread_num());
            }

            #pragma omp section
            {
                printf("HOLA SOY EL THREAD %d (Seccion 2)\n", omp_get_thread_num());
            }

            #pragma omp section
            {
                printf("HOLA SOY EL THREAD %d (Seccion 3)\n", omp_get_thread_num());
            }

            #pragma omp section
            {
                printf("HOLA SOY EL THREAD %d (Seccion 4)\n", omp_get_thread_num());
            }

            #pragma omp section
            {
                printf("HOLA SOY EL THREAD %d (Seccion 5)\n", omp_get_thread_num());
            }

            #pragma omp section
            {
                printf("HOLA SOY EL THREAD %d (Seccion 6)\n", omp_get_thread_num());
            }

            #pragma omp section
            {
                printf("HOLA SOY EL THREAD %d (Seccion 7)\n", omp_get_thread_num());
            }

            #pragma omp section
            {
                printf("HOLA SOY EL THREAD %d (Seccion 8)\n", omp_get_thread_num());
            }

            #pragma omp section
            {
                printf("HOLA SOY EL THREAD %d (Seccion 9)\n", omp_get_thread_num());
            }

            #pragma omp section
            {
                printf("HOLA SOY EL THREAD %d (Seccion 10)\n", omp_get_thread_num());
            }

            #pragma omp section
            {
                printf("HOLA SOY EL THREAD %d (Seccion 11)\n", omp_get_thread_num());
            }

            #pragma omp section
            {
                printf("HOLA SOY EL THREAD %d (Seccion 12)\n", omp_get_thread_num());
            }
        }
    }
    return 0;
}