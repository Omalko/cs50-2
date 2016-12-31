#include <stdio.h>
#include <cs50.h>

int GetCorrectFloat();
int convertFloatToInt();

int main(void) 
{

	int changeFloat = GetCorrectFloat();
	printf("%d", changeFloat);
	printf("\n");

}

int GetCorrectFloat(void) 
{

	float change;
	do
	{
		printf("How much change is owed?\n");
		change = GetFloat();
	}
	while (change < 0);

	int totalCoins = 0;
	
	int cents = (int)(change * 1000)/(10);
	// how many quarters?
	int numQuarters = cents / 25;
	totalCoins += numQuarters;
	int remainingAfterQuarters = cents - (numQuarters*25);
	//how many dimes?
	int numDimes = remainingAfterQuarters / 10;
	totalCoins += numDimes;
	int remainingAfterDimes = remainingAfterQuarters - (numDimes*10);
	//how many nickels?
	int numNickels = remainingAfterDimes / 5;
	totalCoins += numNickels;
	int numPennies = remainingAfterDimes - (numNickels*5);
	totalCoins += numPennies;
	return totalCoins;
	
}

