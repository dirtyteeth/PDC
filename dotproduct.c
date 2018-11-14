#include "mpi.h"
#include<stdio.h>

int dot(int* x,int* y,int start,int end){
	int i,sum=0;
	for(i=start;i<=end;i++){
		sum+=x[i]*y[i];
	}
	return sum;
}

int main(int argc,char* argv[]){
	int p,n,dest=0,tag=0,src,sum,rank;
	int x[]={1,2,3,4,5,6};
	int y[]={1,2,3,4,5,6};
	n=6;
	MPI_Status status;
	MPI_Init(&argc,&argv);
	MPI_Comm_rank(MPI_COMM_WORLD,&rank);
	MPI_Comm_size(MPI_COMM_WORLD,&p);
	int gap=n/p;
	if(rank!=0){
		sum=0;
		int start=gap*rank;
		int end=start+gap-1;
		sum+=dot(x,y,start,end);
		printf("sum of product by process %d : %d\n",rank,sum);
		MPI_Send(&sum,sizeof(sum),MPI_INT,0,0,MPI_COMM_WORLD);
	}
	else{
		int res=0;
		res+=dot(x,y,rank,rank+gap-1);
		printf("sum of product by process %d : %d\n",rank,res);
		for(src=1;src<p;src++){
			MPI_Recv(&sum,sizeof(sum),MPI_INT,src,0,MPI_COMM_WORLD,&status);
			res+=sum;
		}
		printf("Dot product of two arrays : %d\n",res);
	}
	MPI_Finalize();
	return 0;
}
