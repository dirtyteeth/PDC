#include<stdio.h>
#include<mpi.h>
int calculate(int a[],int n,int rank,int sub_n)
{
    int i=rank*sub_n;
    int l=0;
    int sum=0;
    while(l<sub_n && i<n)
    {
        sum+=a[i];
        i++;
        l++;
    }
    return sum;
}
int main(int argc, char *argv[])
{
    /* code */
    int myrank;
    int source;
    int dest;
    int p;
    int tag=0;
    int n=8;
    int a[8]={1,2,3,4,5,6,7,8};
    MPI_Status status;
    MPI_Init(&argc,&argv);
    MPI_Comm_rank(MPI_COMM_WORLD,&myrank);
    MPI_Comm_size(MPI_COMM_WORLD,&p);
    int sub_n=n/p;

    int sum=0;
    if(myrank!=0)
    {
        printf("rank %d ",myrank);
        //myrank--;
        dest=0;
        sum+=calculate(a,n,myrank,sub_n);
        printf("sum here %d \n",sum);
        MPI_Send(&sum,1,MPI_INT,dest,tag,MPI_COMM_WORLD);
    }
    else
    {
        int total=0;
        total+=calculate(a,n,0,sub_n);
        for(source=1;source<p;source++)
        {
            int temp=0;
            MPI_Recv(&temp,1,MPI_INT,source,tag,MPI_COMM_WORLD,&status);
            total+=temp;
        }
        printf("Total sum is: %d",total);

    }
    MPI_Finalize();
    return 0;
}
