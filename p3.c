#include <stdio.h>
#include <stdlib.h>
#include "mpi.h"
int main(int argc, char *argv[]) {
	srand(1234);
	int A[100], B[100],C[100],int a[25],b[25];
	int myid;
	MPI_Status status;
	MPI_Init(&argc,&argv);
	MPI_Comm_rank(MPI_COMM_WORLD,&myid);
	if(myid == 0){
		for (int i=0; i < 100; i++){
			A[i] = rand()%100; /* Set each element randomly to 0-99 */
			B[i] = rand()%100;
		}
	}
	MPI_Scatter((void *)A,25,MPI_INT,(void *)a,25,MPI_INT,0,MPI_COMM_WORLD);
	MPI_Scatter((void *)B,25,MPI_INT,(void *)b,25,MPI_INT,0,MPI_COMM_WORLD);
	for(int k=0;k<25;k++){
		a[k]+=b[k];
	}
	MPI_Gather((void *)a,25,MPI_INT,(void *)C,25,MPI_INT,0,MPI_COMM_WORLD);
	if (myid == 0){
		printf("A:\n");
		for(int a = 0;a<10;a++){
			for(int b=0;b<10;b++){
				printf("%d ",A[10*a+b]);
			}
			printf("\n");
		}
		printf("B:\n");
		for(int a = 0;a<10;a++){
			for(int b=0;b<10;b++){
				printf("%d ",B[10*a+b]);
			}
			printf("\n");
		}
		printf("C:\n");
		for(int a = 0;a<10;a++){
			for(int b=0;b<10;b++){
				printf("%d ",C[10*a+b]);
			}
			printf("\n");
		}
	}
	MPI_Finalize();
}