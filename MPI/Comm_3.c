#include <stdio.h>
#include <mpi.h>

int main() {
	int my_rank;
	int A[5][5] = { 0 };
	int B[5][5] = { 0 };
	MPI_Datatype columntype;

	MPI_Init(NULL, NULL);
	MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
	
	if (my_rank == 0) {
		for (int i = 0; i < 5; i++) {
			for (int j = 0; j < 5; j++) {
				A[i][j] = i * 5 + j;
			}
		}
	}
	if (my_rank == 1) {
		for (int i = 0; i < 5; i++) {
			for (int j = 0; j < 5; j++) {
				B[i][j] = i * 5 + j + 50;
			}
		}
	}
	MPI_Type_vector(5, 1, 5, MPI_INT, &columntype);
	MPI_Type_commit(&columntype);
	if (my_rank == 0) {
		MPI_Send(&A[0][3], 1, columntype, 1, 5, MPI_COMM_WORLD);
		MPI_Recv(&A[0][4], 1, columntype, 1, 5, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
	}
	if (my_rank == 1) {
		MPI_Send(&B[0][2], 1, columntype, 0, 5, MPI_COMM_WORLD);
		MPI_Recv(&B[0][4], 1, columntype, 0, 5, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
	}
	if (my_rank == 1) {
		for (int i = 0; i < 5; i++) {
			for (int j = 0; j < 5; j++) {
				printf("%2d ", B[i][j]);
			}
			printf("\n");
		}
	}
	MPI_Finalize();
}
