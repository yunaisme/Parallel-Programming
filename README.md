# Parallel-Programming
MPI, MapReduce Program

--------------------------------

### MPI

1. Comm_1.c

>프로세스 0은 배열 A[10][10]의 각 원소를 초기화 한 후, MPI_Bcast()를 통해 다른 프로세스들에게 배열 A[10][10]의 값을 복사해준다. 프로세스 1은 대표로 자신의 배열 A[10][10]를 화면에 출력한다.
2. Comm_1.c
```
프로세스 0은 배열 A[10][10]의 각 원소를 초기화 한 후, MPI_Scatter를 통해 배열 A[10][10]의 값을 프로세스마다 2행씩 나누어 준다. 나머지 프로세스들은 받은 값을 배열 B[2][10]에 저장한다. 프로세스 3은 대표로 자신의 배열 B[2][10]을 화면에 출력한다.
```
3. Comm_1.c
```
프로세스 0은 배열 A를 초기화하고, 프로세스 1은 배열 B를 초기화한다. 프로세스 0은 배열 A의 3번 열을 프로세스 1에게 보내고, 프로세스 1은 받은 열을 배열 B의 4번 열에 저장한다. 프로레스 1은 배열 B의 2번 열을 프로세스 0에게 보내고, 프로세스 0은 받은 열을 배열 A의 4번 열에 저장한다. 프로세스 1은 배열 B를 화면에 출력한다.
```
4. CountOdd.c

5. HeatDistributionProblem.c - 벽난로 문제
```
방의 크기는 102x102이다. 가장자리 외벽을 제외한 내부의 크기는 100x100이다.
방의 외벽과 내부의 초기 온도는 0도이다. 외벽의 온도는 항상 0도이다.
벽난로는 방의 북쪽에 있으며, 항상 200도의 열을 낸다. (위치 R[0][40]~R[0][59] 지점)
방의 내부 (100x100)의 온도만 10,000 회 update 한다. (벽난로와 외벽의 온도는 고정)
방의 온도를 update 할 때는 배열 2개를 사용하지 않고, 원래 배열 상에서 그대로 (프로그램에서와 같이) update 한다.
한참 후의 방의 온도 계산이 끝나고 나면, 사용자가 지정하는 구역의 온도를 화면에 출력해준다. (계산 결과 확인용)
```
--------------------------------

### MapReduce
