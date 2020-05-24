#include <stdio.h>
#include <cctype>

int main()
{
	char str[100];
	printf("Enter text: ");
	gets_s(str);
	for (int i = 0; str[i] != NULL; i++)
	{
		printf("%c", str[i]);
		if ((str[i] == ',' || str[i] == ':' || str[i] == ';') && (str[i + 1] != ' '))
		{
			printf(" ");
		}
		if ((str[i] == '!' || str[i] == '?' || str[i] == '.'))
		{		
			if (islower(str[i+1]))				//Перевод в верхний регистр
				str[i+1] = toupper(str[i+1]);
			printf(" ");
		}
	}
	return 0;
}