#include <stdio.h>
#include <cs50.h>

int GetCorrectInt();

int main(void) 
{

	int height = GetCorrectInt();
	int numHashes = 2;
	for (int i=0; i<height; i++) {
		for (int j=i; j<height-1; j++) {
			printf("%s", " ");
		}
		for (int k=0; k<numHashes; k++) {
			printf("%s", "#");
		}
		numHashes ++;
		
		printf("\n");
	}

}

int GetCorrectInt(void) 
{

	int height;
	do
	{
		printf("height: ");
		height = GetInt();
	}
	while (height < 0 || height > 23);
	return height;
}
