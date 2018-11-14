#include<stdio.h>
#include<mpi.h>
#include<math.h>
int maximum(int a, int b){
	if(a>b) return a;
	return b;
}
int main(int argc,char ** argv){
	int my_rank,p,size,n,tag=0,dest=0;
	MPI_Status status;
	int sum=0,ans = 0;
	MPI_Init(&argc,&argv);
 
	MPI_Comm_rank(MPI_COMM_WORLD,&my_rank);
	MPI_Comm_size(MPI_COMM_WORLD,&p);
 
	if(my_rank==0){
		int i;
		scanf("%d",&n);
		int array[n];
		for(i=0;i<n;i++){
			scanf("%d",&array[i]);
		}
		//int avg = n/p;int i;
		for(i=0;i<p-1;i++){
			 MPI_Send(&n,1,MPI_INT,i+1,tag,MPI_COMM_WORLD);
			// MPI_Send(&avg,1,MPI_INT,i+1,tag,MPI_COMM_WORLD);
			MPI_Send(&array[i],1,MPI_INT,i+1,tag,MPI_COMM_WORLD);
//			 MPI_Send(&avg,1,MPI_INT,i+1,tag,MPI_COMM_WORLD);
		}
		ans = 0;
		for(i=1;i<p;i++){
                        MPI_Recv(&ans,1,MPI_INT,i,tag,MPI_COMM_WORLD,&status);
			printf("Result : %d\n",ans);
                }
 
	}
	else{
		int arri,ack,recv,j;
		MPI_Recv(&n,1,MPI_INT,dest,tag,MPI_COMM_WORLD,&status);
		MPI_Recv(&arri,1,MPI_INT,dest,tag,MPI_COMM_WORLD,&status);
 
		for(j=1;j<=n;j++){
			int i = my_rank-1;
			if(j&1){
				if(i%2==0 && i!=0){		
					MPI_Send(&arri,1,MPI_INT,i,tag,MPI_COMM_WORLD);
						MPI_Recv(&recv,1,MPI_INT,i,tag,MPI_COMM_WORLD,&status);
						arri = recv;
				}
				else {
					int ack_l=0;
					if((i&1)){
						if(n&1){
							MPI_Recv(&recv,1,MPI_INT,i+2,tag,MPI_COMM_WORLD,&status);
		                                       	int maxm = maximum(arri,recv);
		                                         MPI_Send(&maxm,1,MPI_INT,i+2,tag,MPI_COMM_WORLD);
							arri = arri>recv?recv:arri;
						}
						else if(i!=(n-1)){
							MPI_Recv(&recv,1,MPI_INT,i+2,tag,MPI_COMM_WORLD,&status);
		                                        int maxm = maximum(arri,recv);
		                                         MPI_Send(&maxm,1,MPI_INT,i+2,tag,MPI_COMM_WORLD);
							arri = arri>recv?recv:arri;
						}
					}
				}
			}
			else{
				if(i%2!=0){
                                MPI_Send(&arri,1,MPI_INT,i,tag,MPI_COMM_WORLD);
                                        MPI_Recv(&recv,1,MPI_INT,i,tag,MPI_COMM_WORLD,&status);
                                        arri = recv;
 
                       		 }
                       		 else {
                                int ack_l=0;
                                if((i%2==0)){
                                        if(n%2==0){
                                       		 MPI_Recv(&recv,1,MPI_INT,i+2,tag,MPI_COMM_WORLD,&status);
                                                int maxm = maximum(arri,recv);
                                                 MPI_Send(&maxm,1,MPI_INT,i+2,tag,MPI_COMM_WORLD);
						arri = arri>recv?recv:arri;
 
					 }
                                        else if(i!=(n-1))
                                                {//printf("%d \n",i);
						MPI_Recv(&recv,1,MPI_INT,i+2,tag,MPI_COMM_WORLD,&status);
                                                int maxm = maximum(arri,recv);
                                                 MPI_Send(&maxm,1,MPI_INT,i+2,tag,MPI_COMM_WORLD);
						arri = arri>recv?recv:arri;
                                        }
                                }
                       		 }
 
			}	
		}
		MPI_Send(&arri,1,MPI_INT,0,tag,MPI_COMM_WORLD);
	}
 
 
	MPI_Finalize();
 
return 0;
}
