#include<stdio.h>
#include<mpi.h>
#define MAX 10000

int ceiling(float x)
{
	float frac = x;
    while(frac<0) frac+=1;
    while(frac>=1) frac-=1;

    if(frac>0) return x-frac+1;
    else return x;
}

float array[MAX];
float array_recv[MAX];

int main(int argc, char **argv)
{
    int size, rank,tag1,tag2,tag3,no_of_element,avg_size;
    int src,dest;
    int no_send,no_recv;
    int total_sum;
    MPI_Status status;

    tag1=0,tag2=1,tag3=2;
    MPI_Init(&argc, &argv);


    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    
    if(rank==0)
    {
    	printf("master process rank=%d:\n",rank );

    	printf("Enter No of elements to  add :");
    	scanf("%d",&no_of_element);

    	printf("Emter %d elements :",no_of_element );

    	int cnt0;
    	for(cnt0=0;cnt0<no_of_element;cnt0++)
    	{
    		scanf("%f",&array[cnt0]);
    	}
        
        int start,end;
    	float n=(float)no_of_element/size;
    	avg_size=ceiling(n);

    	start=0;
    	end =(rank+1)*avg_size-1;

    	// calculating partial sum for master process
    	 total_sum=0;
    	 int i;
    	 for(i=start;i<=end;i++)
    	 {
    	 	total_sum+=array[i];
    	 }

    	printf("master has to calculate value form %d to %d \n",start,end );
    	for(dest=1;dest<size;dest++)
    	{

    	    
            start=dest*avg_size;

            end=(dest+1)*avg_size-1;

            if(end>=no_of_element)
            	end=no_of_element-1;


            int no_send=end-start+1;
            printf("%d has to calculate value form %d to %d \n",dest,start,end );

            // sending no of element to perfoem operation
    		MPI_Send(&no_send,1,MPI_INT,dest,tag1,MPI_COMM_WORLD);

    		// sending crosspomding size of values

    		MPI_Send(&array[start],no_send,MPI_INT,dest,tag2,MPI_COMM_WORLD);
    	}

    	printf("partial sum by master process is: %d \n",total_sum);

    	// receiving temproary sum from different process and adding to toatal sum
    	int temp_sum;
    	for(dest=1;dest<size;dest++)
    	{
    		MPI_Recv(&temp_sum,1,MPI_INT,dest,tag3,MPI_COMM_WORLD,&status);
    		total_sum+=temp_sum;
    	}

    	printf("Total sum by master process is: %d \n",total_sum);

    }
    else
    {
    	src=0;
    	// receiving size of array to calculate sum
    	MPI_Recv(&no_recv,1,MPI_INT,src,tag1,MPI_COMM_WORLD,&status);

    	printf("Received lenght for calculation by rank %d is %d \n",rank,no_recv);

    	// receiving crosspondig size value

    	MPI_Recv(&array_recv,no_recv,MPI_INT,src,tag2,MPI_COMM_WORLD,&status);

    	int tempsum=0;
    	int i;
    	for(i=0;i<no_recv;i++)
    	{
    		tempsum+=array_recv[i];
    	}
    	printf("partial sum by rank %d is: %d \n",rank,tempsum);

    	MPI_Send(&tempsum,1,MPI_INT,src,tag3,MPI_COMM_WORLD);
    }

    MPI_Finalize();
}

