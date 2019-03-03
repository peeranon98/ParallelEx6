#include <stdio.h>
#include <stdlib.h>
#include "mpi.h"
int main(int argc, char *argv[]) {
	srand(1234);
	int A[8][8],local_A[8][8];
	int sum=0;
	int total;
	int myid;
	int chunksize = 2;
	MPI_Status status;
	MPI_Init(&argc,&argv);
	MPI_Comm_rank(MPI_COMM_WORLD,&myid);
	if(myid == 0){
		for (int i=0; i < 8; i++){
			for (int j=0;j<8;j++){
				A[i][j] = rand()%100; /* Set each element randomly to 0-99 */
			}	
		}
	}
	MPI_Scatter(A,8*chunksize,MPI_INT,local_A,8*chunksize,MPI_INT,0,MPI_COMM_WORLD);
	for(int k=0;k<chunksize;k++){
		for(int l=0;l<8;l++){
			sum+=local_A[k][l];
		}
	}
	MPI_Reduce(&sum,&total,1,MPI_INT,MPI_SUM,0,MPI_COMM_WORLD);
	if (myid == 0){
		printf("MPI\n");
		printf("Total sum = %d\n",total );
	}
	MPI_Finalize();
}