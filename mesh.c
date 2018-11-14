#include<stdio.h>
#include<mpi.h>
int main(int argc, char **argv){
	int my_rank, p, tag=0;;
	MPI_Status status;
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD,&my_rank);
	MPI_Comm_size(MPI_COMM_WORLD, &p);
	int n=2;
	int a[2][2]={{1,2},{3,4}};
	int b[2][2]={{5,6},{7,8}};
	int c;
	if(my_rank==0){
		int k=1,i,j;
		for(i=0;i<n;i++){
			for(j=0;j<n;j++){
				MPI_Send(&a[i][j], 1, MPI_INT, k, tag, MPI_COMM_WORLD);
				MPI_Send(&b[i][j], 1, MPI_INT, k++, tag, MPI_COMM_WORLD);
			}
		}
		k=1;
		for(i=0;i<n;i++){
			for(j=0;j<n;j++){
				MPI_Recv(&c, 1, MPI_INT, k++, tag, MPI_COMM_WORLD, &status);
				printf("%d ", c);
			}
			putchar('\n');
		}
	}	
	else{
		int a,b,k;
		c=0;
		MPI_Recv(&a, 1, MPI_INT, 0, tag, MPI_COMM_WORLD, &status);
		MPI_Recv(&b, 1, MPI_INT, 0, tag, MPI_COMM_WORLD, &status);
		int i=(my_rank-1)/n;
		int j=(my_rank-1)%n;
		for(k=0;k<n-1;k++){
			if(i>k){
				MPI_Send(&a, 1, MPI_INT, i*n+((j-1+n)%n)+1,		tag, MPI_COMM_WORLD);
				MPI_Recv(&a, 1, MPI_INT, i*n+((j+1)%n)+1,		tag, MPI_COMM_WORLD, &status);
			}
			if(j>k){
				MPI_Send(&b, 1, MPI_INT, ((i-1+n)%n)*n+(j+1), 	tag, MPI_COMM_WORLD);
				MPI_Recv(&b, 1, MPI_INT, ((i+1)%n)*n+(j+1), 	tag, MPI_COMM_WORLD,&status);
			}
			//printf("%d a=%d b=%d\n", my_rank, a, b);
		}
		for(k=0;k<n;k++){
			c+=a*b;
			MPI_Send(&a, 1, MPI_INT, i*n+((j-1+n)%n)+1,		tag, MPI_COMM_WORLD);
			MPI_Recv(&a, 1, MPI_INT, i*n+((j+1)%n)+1,		tag, MPI_COMM_WORLD, &status);
 
			MPI_Send(&b, 1, MPI_INT, ((i-1+n)%n)*n+(j+1), 	tag, MPI_COMM_WORLD);
			MPI_Recv(&b, 1, MPI_INT, ((i+1)%n)*n+(j+1), 	tag, MPI_COMM_WORLD,&status);
			//printf("%d %d c=%d\n", my_rank, k+1, c);
		}
		MPI_Send(&c, 1, MPI_INT, 0, tag, MPI_COMM_WORLD);
	}
	MPI_Finalize();
	return 0;
}
