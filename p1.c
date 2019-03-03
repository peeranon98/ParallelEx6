#include <stdio.h>
#include <stdlib.h>
#include "mpi.h"
#define MAXPROCS 4
int main(int argc, char *argv[]) {
	int A[100];
	int B[25];
	srand(1234); /* Set random seed */
	for (int i=0; i < 100; i++)
		A[i] = rand()%1000; /* Set each element randomly to 0-999 */
	int myid,numprocs,total,gmin,gmax;
	int ids[MAXPROCS];
	MPI_Status status;
	MPI_Init(&argc,&argv);
	MPI_Comm_size(MPI_COMM_WORLD,&numprocs);
	MPI_Comm_rank(MPI_COMM_WORLD,&myid);
	MPI_Scatter((void *)A,25,MPI_INT,(void *)&B,25,MPI_INT,0,MPI_COMM_WORLD);
	int min =0;
	int max =0;
	int sum = 0;
	for(int k=0;k<25;k++){
		if(B[k]<min){
			min = B[k];
		}
		if(B[k]>max){
			max = B[k];
		}
		sum = sum+B[k];
	}
	printf("Local sum of %d is %d\n",myid,sum );
	printf("Local min of %d is %d\n",myid,min );
	printf("Local max of %d is %d\n",myid,max );
	MPI_Reduce(&sum,&total,1,MPI_INT,MPI_SUM,0,MPI_COMM_WORLD);
	MPI_Reduce(&min,&gmin,1,MPI_INT,MPI_MIN,0,MPI_COMM_WORLD);
	MPI_Reduce(&max,&gmax,1,MPI_INT,MPI_MAX,0,MPI_COMM_WORLD);
	if (myid == 0){
		printf("MPI\n");
		printf("Global SUM = %d\n",total);
		printf("Global MIN = %d\n",gmin);
		printf("Global MAX = %d\n",gmax);
	}
	MPI_Finalize();
}