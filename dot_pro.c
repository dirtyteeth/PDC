#include<stdio.h>
#include<mpi.h>
int help(int a[],int b[],int n,int sub_n,int rank)
{
    int i=rank*sub_n;
    int l=0;
    int sum=0;
    while(l<sub_n && i<n)
    {
        sum+=(a[i]*b[i]);
        i++;
        l++;
    }
    return sum;
}
int main(int argc, char  *argv[])
{
    /* code */
    int myrank,p,source,dest;
    int a[8]={1,2,3,4,5,6,7,8};
    int b[8]={1,2,3,4,5,6,7,8};
    int tag=0;
    int n=8;
    MPI_Status status;
    MPI_Init(&argc,&argv);
    MPI_Comm_rank(MPI_COMM_WORLD,&myrank);
    MPI_Comm_size(MPI_COMM_WORLD,&p);
    int sub_n=n/p;
    if(myrank!=0)
    {
        printf("%d ",myrank);
        int sum=help(a,b,n,sub_n,myrank);
        printf("%d \n",sum);
        MPI_Send(&sum,1,MPI_INT,0,tag,MPI_COMM_WORLD);
    }
    else
    {
        int total=0;
        total+=help(a,b,n,sub_n,0);
        for(source=1;source<p;source++)
        {
            int sum=0;
            MPI_Recv(&sum,1,MPI_INT,source,tag,MPI_COMM_WORLD,&status);
            total+=sum;
        }
        printf("Dot product %d",total);
    }
    MPI_Finalize();
    return 0;
}
