#include <stdio.h>
int main()
{
	int before = 0, after = 0, i = 0;
	char number[20];
	scanf_s("%s", &number, sizeof(number));
	while (number[i] != '.')
	{
		before = number[i] - '0' + before;
		i++;
	}
	i = i + 1;
	while (number[i] != '\0')
	{
		after = number[i] - '0' + after;
		i++;
	}
	if (before > after)
		printf("%d\n", before);
	if (after > before)
		printf("%d\n", after);
	if (before == after)
		printf("%d\n", before);
	return 0;
}