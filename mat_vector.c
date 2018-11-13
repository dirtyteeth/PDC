#include<stdio.h>
#include<mpi.h>
int help(int a[],int k[],int n,int sub_n,int rank)
{
    int sum=0;
    int i=rank*sub_n;
    int l=0;
    while(l<sub_n && i<n)
    {
        sum+=(a[i]*k[l]);
        i++;
        l++;
    }
    return sum;
}
int main(int argc, char *argv[])
{
    int p,source,dist,myrank;
    int tag=0;
    int a[6]={1,2,3,1,5,6};
    int k[3]={1,1,1};
    int n=6;
    MPI_Status status;
    MPI_Init(&argc,&argv);
    MPI_Comm_rank(MPI_COMM_WORLD,&myrank);
    MPI_Comm_size(MPI_COMM_WORLD,&p);
    int sub_n=n/p;
    if(myrank!=0)
    {
        int sum=help(a,k,n,sub_n,myrank);
        //printf("%d  %d \n",myrank,sum);
        MPI_Send(&sum,1,MPI_INT,0,tag,MPI_COMM_WORLD);
    }
    else
    {
        int tk = help(a,k,n,sub_n,0);
        printf("%d  %d \n",myrank,tk);
        for(source=1;source<p;source++)
        {
            int sum=0;
            MPI_Recv(&sum,1,MPI_INT,source,tag,MPI_COMM_WORLD,&status);
            printf("%d  %d \n",source,sum);
        }
    }
    MPI_Finalize();
    return 0;
}
