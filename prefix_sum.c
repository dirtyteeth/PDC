#include<stdio.h>
#include<math.h>
#include<mpi.h>

int main(int argc,char * argv[])
{
	int p,myrank,source,dest;
	int a[8]={1,2,3,4,5,6,7,8};
	int tag=0;
	int n=8;
	MPI_Status status;
	MPI_Init(&argc,&argv);
	MPI_Comm_rank(MPI_COMM_WORLD,&myrank);
	MPI_Comm_size(MPI_COMM_WORLD,&p);
	int k=1;
	while(k<n)
	{
	   int send_i=myrank+k;
	   if(send_i<n)
	   MPI_Send(&a[myrank],1,MPI_INT,send_i,tag,MPI_COMM_WORLD);
	   int rec_i=myrank-k;
	   if(rec_i>=0)
	   {
	   		int temp;
	   		MPI_Recv(&temp,1,MPI_INT,rec_i,tag,MPI_COMM_WORLD,&status);
	   		a[myrank]+=temp;
	   }
	   k=k*2;
	}
	printf("%d %d\n",myrank,a[myrank]);
	MPI_Finalize();
	
}