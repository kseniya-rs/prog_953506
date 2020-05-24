#include <stdio.h>

int main()
{
	char str[100];
	int val1 = 0, val2 = 0, gran = 0, seredina = 0;	
	printf("Enter brackets");
	gets_s(str);
	for (int i = 0; str[i] != NULL; i++)
	{
		if (str[i] == '(') val1++;
		if (str[i] == ')') val2++;
	}
	if (val1 != val2 || val1 == 0)
	{
		puts("Error");
		return 0;
	}
	for (int i = 0; gran != val1; i++)
	{
		if (str[i] == '(' && gran == 0)
			gran += 1;
		else if (str[i] == '(' && gran == 1)
		{
			str[i] = '[';
			gran += 1;
		}
		else if (str[i] == '(' && gran > 1)
		{
			str[i] = '{';
			gran += 1;
		}
		seredina = i + 1;
	}
	for (int i = 0; gran != 1; i++)
	{
		if (str[i + seredina] == ')' && gran == 2)
		{
			str[i + seredina] = ']';
			gran -= 1;
		}
		else if (str[i + seredina] == ')' && gran > 2)
		{
			str[i + seredina] = '}';
			gran -= 1;
		}
	}
	puts(str);
	return 0;
}