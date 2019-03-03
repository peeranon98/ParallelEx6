#include <stdio.h>
#include <stdlib.h>
#define MAXPROCS 4
int main(int argc, char *argv[]) {
	int A[100];
	int B[25];
	int max = 0;
	int min = 0;
	int sum=0;
	srand(1234); /* Set random seed */
	for (int i=0; i < 100; i++){
		A[i] = rand()%1000; /* Set each element randomly to 0-999 */
		if (A[i]<min){
			min=A[i];
		}
		if (A[i]>max){
			max=A[i];
		}
		sum = sum+A[i];
	}
	printf("Sequential\n");
	printf("SUM %d\n",sum);
	printf("MIN %d\n",min);	
	printf("MAX %d\n",max);			

}