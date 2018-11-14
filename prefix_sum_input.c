#include<stdio.h>
#include<mpi.h>
#include<stdlib.h>
#include<math.h>


int main(int argc,char **argv)
{
	int rank,size,tag1,tag2,tag3,dest,src;
	tag1=0,tag2=1,tag3=0;
	MPI_Status status;
  float sum;

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
   	
      printf("Enter array of size %d :\n",N);
      int i;
       for(i=0;i<N;i++)
        scanf("%f",&vec[i]);
   		for(dest=1;dest<size;dest++)
   		{
   			
        MPI_Send(&vec[dest],1,MPI_FLOAT,dest,tag1,MPI_COMM_WORLD);

   		}


      // loop
      sum=vec[rank];
      int k=1;
      while(k<N)
      {

         // printf("process %d sent value to %d : %f \n",rank,k,sum);
          MPI_Send(&sum,1,MPI_FLOAT,k,tag3,MPI_COMM_WORLD);
          k=k*2;
      }
      
      printf("process %d ok : %f\n",rank,sum);
   		for(dest=1;dest<size;dest++)
   		{
   			  MPI_Recv(&sum,1,MPI_FLOAT,dest,tag2,MPI_COMM_WORLD,&status);
   		   
          printf("process %d ok : %f\n",dest,sum);
   		}

   }
   else
   {
   	  src=0;
   	  MPI_Recv(&sum,1,MPI_FLOAT,src,tag1,MPI_COMM_WORLD,&status);
      float temp;
      int j=1;
      while(j<size)
      {
          int k=rank+j;
          if(k>=0 && k<size)
          {
           // printf("process %d sent value to %d : %f \n",rank,k,sum);
            MPI_Send(&sum,1,MPI_FLOAT,k,tag3,MPI_COMM_WORLD);
          }
          k=rank-j;
          if(k>=0 && k<size)
          {

             MPI_Recv(&temp,1,MPI_FLOAT,k,tag3,MPI_COMM_WORLD,&status);
             //printf("process %d received value from %d : %f \n",rank,k,temp);
             sum+=temp;
          }
          j=j*2;
      }
 	   
   	  MPI_Send(&sum,1,MPI_FLOAT,src,tag2,MPI_COMM_WORLD);
   }
   MPI_Finalize();

}