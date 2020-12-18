#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <mpi.h>

int main(void) {

	int p; //number of processes
	int my_rank; //my rank
	int worker_size; //size of worker's array

	int A[1000]; //for processor 0
	int B[1000]; //for each processor
	
	int result = 0; //final result
	int my_result = 0; //my result

	//Start up MPIe
	MPI_Init(NULL, NULL);

	//Get the number of processes
	MPI_Comm_size(MPI_COMM_WORLD, &p);

	//Compute size of worker's array
	worker_size = 1000 / p;
	//배열은 언제나 균등하게 프로세스들에게 배분될 수 있다고 가정

	//Get my rank among all the procsses
	MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);

	if (my_rank == 0) {
		//master가 할 일
		srand(time(NULL));
		for (int i = 0; i < 1000; i++) {
			A[i] = ( rand() % 1000 ) + 1;
		}
	}
	
	MPI_Scatter(A, worker_size, MPI_INT, B, worker_size, MPI_INT, 0, MPI_COMM_WORLD);

	for (int i = 0; i < worker_size; i++) {
		if (B[i] % 2 == 1) my_result += 1;
	}

	MPI_Reduce(&my_result, &result, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
	
	printf("Processor %d : Number of odd number in local is %d. \n", my_rank, my_result);

	//print result
	if (my_rank == 0) printf("\nTotal number of odd number is %d. \n", result);


	//Shut down MPI
	MPI_Finalize();
	return 0;

}
