#include <stdio.h>
#include <cs50.h>
#include <string.h>

int main(void)
{
	string name = GetString();
	for (int i=0; i<strlen(name); i++)
	{
		int char_as_int = (int) name[i];
		if (char_as_int >= 65 && char_as_int <= 90)
		{
			printf("%c", name[i]);
		}
	}
	printf("\n");
}
