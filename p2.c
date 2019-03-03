#include <stdio.h>
#include <stdlib.h>
#include "mpi.h"
#define MAXPROCS 4
int main(int argc, char *argv[]) {
	int A[100];
	int B[25];
	srand(1234); /* Set random seed */
	int myid,numprocs,total;
	int ids[MAXPROCS];
	int i;
	MPI_Status status;
	MPI_Init(&argc,&argv);
	MPI_Comm_size(MPI_COMM_WORLD,&numprocs);
	MPI_Comm_rank(MPI_COMM_WORLD,&myid);
	if(myid == 0){
		for (int i=0; i < 100; i++)
			A[i] = rand()%100; /* Set each element randomly to 0-99 */
		printf("Enter i: ");
		fflush(stdout);
		scanf("%d",&i);
	}
	MPI_Bcast(&i,1,MPI_INT,0,MPI_COMM_WORLD);
	MPI_Scatter((void *)A,25,MPI_INT,(void *)&B,25,MPI_INT,0,MPI_COMM_WORLD);
	int count =0;
	for(int k=0;k<25;k++){
		if(B[k]<i){
			count++;
		}
	}
	printf("Local count of %d is %d\n",myid,count);
	MPI_Reduce(&count,&total,1,MPI_INT,MPI_SUM,0,MPI_COMM_WORLD);
	if (myid == 0){
		printf("MPI\n");
		printf("Total count = %d\n",total);
	}
	MPI_Finalize();
}