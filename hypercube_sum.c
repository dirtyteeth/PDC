#include<stdio.h>
#include<mpi.h>
#define MAX 100



int main(int argc,char **argv)
{
	int rank,size,val,N;
	MPI_Status status;

	// INITIALIZING MPI_WORLD

	MPI_Init(&argc,&argv);

	// Initializing rank to each process

	MPI_Comm_rank(MPI_COMM_WORLD,&rank);

	// Initilaizing no of process

	MPI_Comm_size(MPI_COMM_WORLD,&size);
	N=size;
	if(rank==0)
	{
		int arr[MAX];
		val=arr[rank];

		printf("Enter %d value to add:\n",N);
		for(int i=0;i<N;i++)
			scanf("%d",&arr[i]);

		for(int i=1;i<N;i++)
			MPI_Send(&arr[i],1,MPI_INT,i,0,MPI_COMM_WORLD);

		int d=N;
		while(d>0)
		{
			d=d/2;
			if(rank<d && rank+d<N)
			{
				int temp;
			  MPI_Recv(&temp,1,MPI_INT,rank+d,1,MPI_COMM_WORLD,&status);
			  val+=temp;
		    }
		}

		 printf("sum=%d\n",val );

	}
	else
	{
		MPI_Recv(&val,1,MPI_INT,0,0,MPI_COMM_WORLD,&status);
		printf("rank %d %d\n",rank,val);
		int d=N;
		while(d>0)
		{
			 d=d/2;
			if(rank>=d && rank<2*d)
			{	
				if(rank-d>=0)
				MPI_Send(&val,1,MPI_INT,rank-d,1,MPI_COMM_WORLD);
			}
			else
			{
				int temp;
				if(rank+d<N)
				{
				  MPI_Recv(&temp,1,MPI_INT,rank+d,1,MPI_COMM_WORLD,&status);
				  val+=temp;
			    }
			}
		}
	}


	MPI_Finalize();
}