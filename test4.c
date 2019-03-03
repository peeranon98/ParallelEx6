#include <stdio.h>
#include <stdlib.h>
int main(int argc, char *argv[]) {
	srand(1234);
	int A[8][8],local_A[8][8];
	int sum=0;
	int total;
	int myid;
	int chunksize = 2;
	for (int i=0; i < 8; i++){
		for (int j=0;j<8;j++){
			A[i][j] = rand()%100; /* Set each element randomly to 0-99 */
			sum+=A[i][j];
		}	
	}
	printf("Sequential\n");
	printf("Total sum = %d\n",sum);
}