#include<stdio.h>
#include<mpi.h>
#define MAX 100

float x[MAX];
float y[MAX];
float calculate_L(float X ,int N,int k)
{
     float res=1;
     for(int i=0;i<N;i++)
     {
        if(i!=k)
        {
          res=res*(X-x[i])/(x[k]-x[i]);
        }
     }
     return res;

}
int main(int argc,char **argv)
{
	int rank,size,tag1,tag2,tag3,tag4,dest,src;
	tag1=0,tag2=1,tag3=2,tag4=3;
	MPI_Status status;
	float X,L,Y;
	float sum;

	// INITIALIZING MPI_WORLD

	MPI_Init(&argc,&argv);

	// Initializing rank to each process

	MPI_Comm_rank(MPI_COMM_WORLD,&rank);

	// Initilaizing no of process

	MPI_Comm_size(MPI_COMM_WORLD,&size);

   if(rank==0)
   {
   		printf("Enter %d value for x:",size);
      int i;
   	  for(i=0;i<size;i++)
        scanf("%f",&x[i]);

   		printf("Enter %d value for y:",size);
        for(i=0;i<size;i++)
          scanf("%f",&y[i]);

   		printf("Enter Value of x to calculate :");
   		scanf("%f",&X);

   		L=calculate_L(X,size,rank);
   		printf("L%d :  %f\n",rank,L );
   		for(dest=1;dest<size;dest++)
   		{

   			MPI_Send(&x[0],size,MPI_FLOAT,dest,tag1,MPI_COMM_WORLD);
   			MPI_Send(&y[0],size,MPI_FLOAT,dest,tag2,MPI_COMM_WORLD);
   			MPI_Send(&X,1,MPI_FLOAT,dest,tag3,MPI_COMM_WORLD);
   		}
   		float temp_sum;
      Y=y[rank];
      sum=L*Y;
   		for(dest=1;dest<size;dest++)
   		{
   			MPI_Recv(&temp_sum,1,MPI_FLOAT,dest,tag4,MPI_COMM_WORLD,&status);
   			sum+=temp_sum;
   		}

   		printf("value for the %f is %f",X,sum);


   }
   else
   {
   	  src=0;
   	  MPI_Recv(&x,size,MPI_FLOAT,src,tag1,MPI_COMM_WORLD,&status);
   	  MPI_Recv(&y,size,MPI_FLOAT,src,tag2,MPI_COMM_WORLD,&status);
   	  MPI_Recv(&X,1,MPI_FLOAT,src,tag3,MPI_COMM_WORLD,&status);
   	  L=calculate_L(X,size,rank);
      printf("L%d :  %f\n",rank,L );
      Y=y[rank];
      sum=L*Y;
   	  MPI_Send(&sum,1,MPI_FLOAT,src,tag4,MPI_COMM_WORLD);
   }
   MPI_Finalize();

}