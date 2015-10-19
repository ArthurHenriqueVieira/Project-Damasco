#include <stdio.h>
#include <math.h>

#define SIZE 20

int main(){
	char v[SIZE];
	int i, j;

	printf("Digite uma função:");
	
	fgets(v, SIZE, stdin);

	for(i=0; v[i] != '\0' && v[i] != '\n';  i++)
		printf("%c", v[i]);

    printf("\n");
	return 0;
}