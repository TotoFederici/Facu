#include <stdio.h>
#include <mpi.h>

//void main(int argc, char** argv){
    //    int num_proc, my_id;
    //    MPI_Init(&argc, &argv);
    //    MPI_Comm_rank(MPI_COMM_WORLD,&my_id);
    //    MPI_Comm_size(MPI_COMM_WORLD,&num_proc);
    //    printf("Hello world! I am process %d out of %d\n", my_id, num_proc);
    //    MPI_Finalize();
    //}
    
void main(int argc, char** argv){
    int rank, value;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD,&rank);
    if(rank == 0){
        printf("Enter a number to broadcast:\n");
        scanf("%d",&value);
    }
    else {
        printf("Process %d: Before MPI_Bcast, value is %d\n", rank, value);
    }
    MPI_Bcast(&value, 1, MPI_INT, 0, MPI_COMM_WORLD);
    printf("Process %d: After MPI_Bcast, value is %d\n", rank, value);
    MPI_Finalize();
}