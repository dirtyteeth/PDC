#include<stdio.h>
#include<mpi.h>


int main(int argc,char **argv)
{
	int rank,size,tag1,tag2,tag3,dest,src;
	tag1=0,tag2=1,tag3=0;
	MPI_Status status;
    float sum,pow;

	// INITIALIZING MPI_WORLD

	MPI_Init(&argc,&argv);

	// Initializing rank to each process

	MPI_Comm_rank(MPI_COMM_WORLD,&rank);

	// Initilaizing no of process

	MPI_Comm_size(MPI_COMM_WORLD,&size);

   if(rank==0)
   {
	    int N=size;
	    float vec[N];
	   	
	    printf("Enter %d coffecient for polynomial of degree %d :\n",N-1,N-2);
	   int i;
      for(i=1;i<N;i++)
       scanf("%f",&vec[i]);

   		printf("Enter x to evaluate polynomial:\n");
   		scanf("%f",&pow);
   		int x=pow;
		for(dest=1;dest<N;dest++)
		{
     		MPI_Send(&vec[dest],1,MPI_FLOAT,dest,tag1,MPI_COMM_WORLD);
		}
   		int k=1;
   		 i=0;
   		while(k<N)
   		{
   			for(dest=1;dest<N;dest++)
   			{
   				if((dest-1)&(1<<i))
   				{ 

	                MPI_Send(&pow,1,MPI_FLOAT,dest,tag2,MPI_COMM_WORLD);
                }
   			}	
   			i++;
   			pow=pow*pow;
   			k=k*2;
   		}
    	float temp;
    	sum=0;
		for(dest=1;dest<N;dest++)
		{   
			  MPI_Recv(&temp,1,MPI_FLOAT,dest,tag3,MPI_COMM_WORLD,&status);
		   	  sum+=temp;
	          printf("process %d ok : %f\n",dest,temp);
		}

		printf("ploynomial evaluation for %d is %f\n",x,sum);

   }	
   else
   {
   	    src=0;
   	    MPI_Recv(&sum,1,MPI_FLOAT,src,tag1,MPI_COMM_WORLD,&status);

		int k=1;
		int i=0;
		while(k<size)
		{
			if((rank-1)&(1<<i))
			{
				MPI_Recv(&pow,1,MPI_FLOAT,src,tag2,MPI_COMM_WORLD,&status);
				sum=sum*pow;
			}
			k=k*2;
			i++;
		}
   	    MPI_Send(&sum,1,MPI_FLOAT,src,tag3,MPI_COMM_WORLD);
   }
   MPI_Finalize();

}