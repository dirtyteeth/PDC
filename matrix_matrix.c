#include<stdio.h>
#include<mpi.h>
#define MAX 100

int matrix1[MAX][MAX];
int matrix2[MAX][MAX];

int main(int argc, char ** argv){
int rank, size, tag1, tag2, tag3, tag4, tag5, tag6;
int row1, col1, row2, col2;

tag1 = 1, tag2 = 2, tag3 = 3;
tag4 = 4, tag5 = 5, tag6 = 6;

MPI_Status status;
MPI_Init(&argc, &argv);

MPI_Comm_size(MPI_COMM_WORLD, &size);
MPI_Comm_rank(MPI_COMM_WORLD, &rank);

if(rank == 0){
	printf("Enter the row and column of first and second matrix\n");
	scanf("%d %d %d %d", &row1, &col1, &row2, &col2);
	
	printf("Enter the matrix1\n");
	for(int i = 0; i < row1; i++){
		for(int j = 0; j < col1; j++){
			scanf("%d",&matrix1[i][j]);}}
	
	printf("Enter the matrix2\n"); 
	for(int i = 0; i < row2; i++){
		for(int j = 0; j < col2; j++){
			scanf("%d",&matrix2[i][j]);}}

	for(int dest = 1; dest < size; dest++){	
		MPI_Send(&col1,1, MPI_INT, dest, tag1, MPI_COMM_WORLD);
		MPI_Send(&row2,1, MPI_INT, dest, tag2, MPI_COMM_WORLD);
		MPI_Send(&col2,1, MPI_INT, dest, tag3, MPI_COMM_WORLD);
		MPI_Send(&matrix1[dest], col1, MPI_INT, dest, tag4, MPI_COMM_WORLD);
		int tot = row2*col2;
		for(int i = 0; i < row2; i++){
			MPI_Send(&matrix2[i][0], col2, MPI_INT, dest, tag5, MPI_COMM_WORLD);}
	}
	printf("Result:\n");
	for(int i = 0; i < col2; i++){
		int ans = 0;
		for(int j = 0; j < col1; j++){
			ans += matrix1[0][j]*matrix2[j][i];}
		printf("%d ", ans);}
	printf("\n");
	for(int src = 1; src < size; src++){
		int arr[col2];
		MPI_Recv(&arr, col2, MPI_INT, src, tag6, MPI_COMM_WORLD, &status);
		for(int i = 0; i < col2; i++) printf("%d ", arr[i]);
		printf("\n");}
	}
	else{
		MPI_Recv(&col1, 1, MPI_INT, 0, tag1, MPI_COMM_WORLD, &status);
		MPI_Recv(&row2, 1, MPI_INT, 0, tag2, MPI_COMM_WORLD, &status);
		MPI_Recv(&col2, 1, MPI_INT, 0, tag3, MPI_COMM_WORLD, &status);
		int arr[col1];
		MPI_Recv(&arr, col1, MPI_INT, 0, tag4, MPI_COMM_WORLD, &status);
		int mat[col2];
		for(int i = 0; i < row2; i++){
			MPI_Recv(&mat, col2, MPI_INT, 0, tag5, MPI_COMM_WORLD, &status);
			for(int j = 0; j < col2; j++) matrix2[i][j] = mat[j];}
	
		int res[col2];
		for(int i = 0; i < col2; i++){
			int ans = 0;
			for(int j = 0; j < col1; j++){
			ans += arr[j]*matrix2[j][i];}
			res[i] = ans;}
		MPI_Send(&res, col2, MPI_INT, 0, tag6, MPI_COMM_WORLD);
	}
	MPI_Finalize();
return 0;
}
