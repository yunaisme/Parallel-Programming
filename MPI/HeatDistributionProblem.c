#include <stdio.h>
#include <mpi.h>

int main() {
	int my_rank, numprocs;
	double R[102][102] = { 0.0 };
	int m1, m2, n1, n2;
	MPI_Datatype columntype, columns;

	//벽난로의 온도(계속 유지)
	for (int i = 40; i < 60; i++)
		R[0][i] = 200.0;

	MPI_Init(NULL, NULL);
	MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
	MPI_Comm_size(MPI_COMM_WORLD, &numprocs);

	//배열의 한 열을 정의하는 타입 선언
	MPI_Type_vector(102, 1, 102, MPI_DOUBLE, &columntype);
	MPI_Type_commit(&columntype);

	//10000번 반복
	for (int i = 0; i < 10000; i++) {

		//온도 업데이트
		for (int j = 1; j <= 100; j++) {
			for (int k = 1 + my_rank * 100/numprocs ; k <= 100 / numprocs + my_rank * 100/numprocs ; k++){
				R[j][k] = 0.25 * ( R[j][k - 1] + R[j][k + 1] + R[j - 1][k] + R[j + 1][k] );
			}
		}

		//주변 온도를 양옆의 프로세스들에게 전달함
		if (my_rank == 0) { //가장 왼쪽에 있는 프로세스의 경우
			MPI_Send(&R[0][100 / numprocs], 1, columntype, my_rank+1, 5, MPI_COMM_WORLD);
			MPI_Recv(&R[0][100 / numprocs + 1], 1, columntype, my_rank+1, 5, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
		}
		else if (my_rank == numprocs - 1) { //가장 오른쪽에 있는 프로세스의 경우
			MPI_Send(&R[0][100 / numprocs * my_rank + 1], 1, columntype, my_rank-1, 5, MPI_COMM_WORLD);
			MPI_Recv(&R[0][100 / numprocs * my_rank ], 1, columntype, my_rank-1, 5, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
		}
		else { //가운데 있는 프로세스의 경우
			MPI_Send(&R[0][100 / numprocs * my_rank + 1], 1, columntype, my_rank-1, 5, MPI_COMM_WORLD);
			MPI_Recv(&R[0][100 / numprocs * my_rank], 1, columntype, my_rank-1, 5, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
			MPI_Send(&R[0][100 / numprocs + 100 / numprocs * my_rank], 1, columntype, my_rank+1, 5, MPI_COMM_WORLD);
			MPI_Recv(&R[0][100 / numprocs + 100 / numprocs * my_rank+1], 1, columntype, my_rank+1, 5, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
		}
	}

	//프로세스 하나가 담당하는 열들의 모음 데이터 타입 정의
	MPI_Type_vector(102, 100/numprocs, 102, MPI_DOUBLE, &columns);
	MPI_Type_commit(&columns);

	//프로세스 0에게 계산 결과 보내기
	if (my_rank != 0) {
		MPI_Send(&R[0][100 / numprocs * my_rank + 1], 1, columns, 0, 5, MPI_COMM_WORLD);
	}
	else {
		for (int i = 1; i < numprocs; i++) {
			MPI_Recv(&R[0][100 / numprocs * i + 1], 1, columns, i, 5, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
		}
	}

	//결과 테스트를 위한 구간 출력
	if (my_rank == 0) {
		printf("출력할 구간 (m1, m2, n1, n2) : ");
		scanf("%d %d %d %d", &m1, &m2, &n1, &n2);
		for (int i = m1; i <= m2; i++) { //방의 세로 구간
			for (int j = n1; j <= n2; j++)  //방의 가로 구간
				printf("%f ", R[i][j]);
			printf("\n");
		}
	}
	MPI_Finalize();
}
