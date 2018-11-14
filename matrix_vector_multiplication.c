#include<stdio.h>
#include<mpi.h>
#include<stdlib.h>

#define MAX 100

float vec[MAX];
float mat[MAX][MAX];
float arr[MAX];

int main(int argc,char **argv)
{
	int rank,size,tag1,tag2,tag3,dest,src;
	tag1=0,tag2=1,tag3=0;
	MPI_Status status;
	int N;
  float sum;

	// INITIALIZING MPI_WORLD

	MPI_Init(&argc,&argv);

	// Initializing rank to each process

	MPI_Comm_rank(MPI_COMM_WORLD,&rank);

	// Initilaizing no of process

	MPI_Comm_size(MPI_COMM_WORLD,&size);

   if(rank==0)
   {
   		N=size;

   		printf("Enter MAtrix %d X %d:\n",N,N);
      int i,j;
      for(int i=0;i<N;i++)
        for(int j=0;j<N;j++)
          scanf("%f",&mat[i][j]);

       printf("Enter Vector of size %d :\n",N);

       for(i=0;i<N;i++)
        scanf("%f",&vec[i]);


   		

   		sum=0;
      for(i=0;i<N;i++)
      {
        sum+=mat[rank][i]*vec[i];
      }


      printf("process %d ok : %f\n",rank,sum);
   		for(dest=1;dest<size;dest++)
   		{
   			MPI_Send(&mat[dest][0],N,MPI_FLOAT,dest,tag1,MPI_COMM_WORLD);
        MPI_Send(&vec,N,MPI_FLOAT,dest,tag3,MPI_COMM_WORLD);
   		}
   		for(dest=1;dest<size;dest++)
   		{
   			  MPI_Recv(&sum,1,MPI_FLOAT,dest,tag2,MPI_COMM_WORLD,&status);
   		   
         printf("process %d ok : %f\n",dest,sum);
   		}

   }
   else
   {
   	  src=0;
   	  MPI_Recv(&arr,size,MPI_FLOAT,src,tag1,MPI_COMM_WORLD,&status);
      MPI_Recv(&vec,size,MPI_FLOAT,src,tag3,MPI_COMM_WORLD,&status);
 	    sum=0;
      int i;
      for(i=0;i<size;i++)
      {
        sum+=arr[i]*vec[i];
      }
      
   	  MPI_Send(&sum,1,MPI_FLOAT,src,tag2,MPI_COMM_WORLD);
   }
   MPI_Finalize();

}