#include <stdio.h>
#include <cs50.h>

int GetCorrectInt();

int main(void) 
{

	int height = GetCorrectInt();
	printf("okay, height is %d", height);

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
