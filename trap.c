#include<stdio.h>
#include<mpi.h>
float f(int x)
{
    float k = x*x*x;
    return k;
}
float help(float x[],int n,int sub_n,int rank)
{
    int i=rank*sub_n;
    int l=0;
    float sum=0;
    while(l<sub_n && i<n)
    {
        sum+=f(x[i]);
        i++;
        l++;
    }
    return sum;
}
int main(int argc, char  *argv[])
{
    int p,source,dist,myrank;
    float tag=0;
    float x[9]= {0,1,2,3,4,5,6,7,8};
    int n=8;
    int a=2;
    int b=4;
    MPI_Status status;
    MPI_Init(&argc,&argv);
    MPI_Comm_rank(MPI_COMM_WORLD,&myrank);
    MPI_Comm_size(MPI_COMM_WORLD,&p);
    int sub_n=n/p;
    float h=(float)(b-a)/n;
    if(myrank!=0)
    {
        float sum=help(x,n,sub_n,myrank);
        printf("%f \n",sum);
        MPI_Send(&sum,1,MPI_FLOAT,0,tag,MPI_COMM_WORLD);        
    }
    else
    {
        float total=0;
        total+=f(x[0])+(f(x[n])/2);
        //printf("%f \n",total);
        for(source=1;source<p;source++)
        {
            float sum=0;
            MPI_Recv(&sum,1,MPI_FLOAT,source,tag,MPI_COMM_WORLD,&status);
            //printf("%f \n",sum);
            total+=sum;
        }
        // printf("%f \n",total);
        // printf("%f \n",h);
        printf("%f ",(total*h));
    }
    MPI_Finalize();

    return 0;
}
