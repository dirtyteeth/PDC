#include<stdio.h>
#include<mpi.h>
float fun(float x)
{
	return (x*x+1);
}
float calculate_partial_area(float a ,float b,int n)
{
     float h=(b-a)/n;
     float partial_sum=0;
     partial_sum=fun(a)+fun(b);

     for(int i=1;i<=n-1;i++)
     {
     	float x=a+i*h;
     	if(i%2==1)
     	{
     		partial_sum+=4*fun(x);
     	}
     	else
     	{
     		partial_sum+=2*fun(x);
     	}
     }
     partial_sum=(partial_sum*h)/3.0;

     return partial_sum;

}
int main(int argc,char **argv)
{
	int rank,size,tag1,tag2,tag3,tag4,dest,src;
	tag1=0,tag2=1,tag3=2,tag4=3;
	MPI_Status status;
	float L,U;
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
   		printf("Lower Bound :");
   		scanf("%f",&L);

   		printf("Upper Bound :");
   		scanf("%f",&U);

   		printf("Enter No of Block :");
   		scanf("%d",&N);

   		float step=(U-L)/size;

   		float l=L;
   		float u=L+step;
   		sum=0;
   		sum=calculate_partial_area(l,u,N);
   		printf("Partial Area claculated  by process %d :  %f to %f is %f\n",rank,l,u,sum );
   		for(dest=1;dest<size;dest++)
   		{
   			l=L+step*dest;
   			u=L+(dest+1)*step;
   			if(u>U)
   				u=U;

   			MPI_Send(&l,1,MPI_FLOAT,dest,tag1,MPI_COMM_WORLD);
   			MPI_Send(&u,1,MPI_FLOAT,dest,tag2,MPI_COMM_WORLD);
   			MPI_Send(&N,1,MPI_FLOAT,dest,tag3,MPI_COMM_WORLD);
   		}
   		float temp_sum;
   		for(dest=1;dest<size;dest++)
   		{
   			MPI_Recv(&temp_sum,1,MPI_FLOAT,dest,tag4,MPI_COMM_WORLD,&status);
   			sum+=temp_sum;
   		}

   		printf("Total Area claculated for range %f to %f is %f\n",L,U,sum );


   }
   else
   {
   	  src=0;
   	  MPI_Recv(&L,1,MPI_FLOAT,src,tag1,MPI_COMM_WORLD,&status);
   	  MPI_Recv(&U,1,MPI_FLOAT,src,tag2,MPI_COMM_WORLD,&status);
   	  MPI_Recv(&N,1,MPI_FLOAT,src,tag3,MPI_COMM_WORLD,&status);
   	  float temp_sum=calculate_partial_area(L,U,N);
   	  printf("Partial Area claculated  by process %d :  %f to %f is %f\n",rank,L,U,temp_sum );
   	  MPI_Send(&temp_sum,1,MPI_FLOAT,src,tag4,MPI_COMM_WORLD);
   }
   MPI_Finalize();

}