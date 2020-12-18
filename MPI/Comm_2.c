#include <stdio.h>
#include <mpi.h>

int main() {
	int my_rank;
	int A[10][10];
	int B[2][10];

	MPI_Init(NULL, NULL);
	MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
	
	if (my_rank == 0) {
		for (int i = 0; i < 10; i++) {
			for (int j = 0; j < 10; j++) {
				A[i][j] = i * 10 + j;
			}
		}
	}

	MPI_Scatter(A, 20, MPI_INT, B, 20, MPI_INT, 0, MPI_COMM_WORLD);

	if (my_rank == 3) {
		for (int i = 0; i < 2; i++) {
			for (int j = 0; j < 10; j++) {
				printf("%2d ", B[i][j]);
			}
			printf("\n");
		}
	}
	MPI_Finalize();
}
