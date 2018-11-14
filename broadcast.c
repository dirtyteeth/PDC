#include<stdio.h>
#include<mpi.h>
#define MAX 100

int arr[MAX];

int main(int argc,char **argv)
{
	int rank,size,local=0,global=0,N;

	// INITIALIZING MPI_WORLD

	MPI_Init(&argc,&argv);

	// Initializing rank to each process

	MPI_Comm_rank(MPI_COMM_WORLD,&rank);

	// Initilaizing no of process

	MPI_Comm_size(MPI_COMM_WORLD,&size);
	N=size;
	if(rank==0)
	{
		
		printf("Enter %d value to add:\n",N);
		for(int i=0;i<N;i++)
			scanf("%d",&arr[i]);
		global=0;
	

	}
	MPI_Bcast(&arr,N,MPI_INT,0,MPI_COMM_WORLD);
	local=arr[rank];
	MPI_Reduce(&local,&global,1,MPI_INT,MPI_SUM,0,MPI_COMM_WORLD);
	if(rank==0)
	{
		printf("sum=%d \n",global);
	}

	MPI_Finalize();
}