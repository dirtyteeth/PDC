
#include <stdio.h>
#include <mpi.h>




//---------------------------HELLO WORLD -----------------------------------------

/*

int main(int argc, char **argv) 
{
  
  MPI_Init(&argc, &argv);
  printf("Hello world\n"); 
     
  MPI_Finalize();
}

*/


//---------------------------------Identifying Process by its id/rank--------------------------------------


/*


int main(int argc, char **argv)
 {
    int size, rank;

    MPI_Init(&argc, &argv);

    // find out MY process ID, and how many processes were started. 

     MPI_Comm_rank(MPI_COMM_WORLD, &rank);
     MPI_Comm_size(MPI_COMM_WORLD, &size);

    printf("Hello world! I'm process %i out of %i processes\n", 
       rank, size);

    MPI_Finalize();
 }


*/

//-------------------------------------------------------------------------------------------------------------


// ****************************** Basic MPI communication routines*****************************************************

/*

	The syntax of MPI_Send is:

	int MPI_Send(void *data_to_send, int send_count, MPI_Datatype send_type, 
	      int destination_ID, int tag, MPI_COMM_WORLD ); 

	data_to_send: variable of a C type that corresponds to the send_type supplied below
	send_count: number of data elements to be sent (nonnegative int)
	send_type: datatype of the data to be sent (one of the MPI datatype handles)
	destination_ID: process ID of destination (int)
	tag: message tag (int)
	comm: communicator (handle)



	The syntax of MPI_Recv is:

	 MPI_Recv(void *received_data, int receive_count, MPI_Datatype receive_type, 
	      int sender_ID, int tag, MPI_COMM_WORLD, &status); 


	received_data: variable of a C type that corresponds to the receive_type supplied below
	receive_count: number of data elements expected (int)
	receive_type: datatype of the data to be received (one of the MPI datatype handles)
	sender_ID: process ID of the sending process (int)
	tag: message tag (int)
	comm: communicator (handle)
	status: status struct (MPI_Status)



*/

//**************************************************************************************************************************


///////////////////////////////////Basic structure of parallel algorithm///////////////////////////////////////////////


#include <stdio.h>
#include <mpi.h>


int main(int argc, char **argv)
{

   int rank, master, size;

   MPI_Status status;
   
   master = 0;

   /* Now replicate this process to create parallel processes.  */

      MPI_Init(&argc, &argv);

   /* find out MY process ID, and how many processes were started */

    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

   if(rank == root_process) {


      /* I must be the root process, so I will query the user
       * to determine how many numbers to sum.

       * initialize an array,

       * distribute a portion of the array to each child process,

       * and calculate the sum of the values in the segment assigned 
       * to the root process,

       * and, finally, I collect the partial sums from slave processes,
       * print them, and add them to the grand sum, and print it */
   }

   else {

      /* I must be slave process, so I must receive my array segment,

       * calculate the sum of my portion of the array,

       * and, finally, send my portion of the sum to the root process. */

   }

   /* Stop this process */

    MPI_Finalize();

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////


