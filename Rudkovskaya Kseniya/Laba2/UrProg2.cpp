#include <cstdio>
#include <cmath>


int main()
{
	double x, e, sinX, element, rs;
	do
	{
		printf("Enter x:");
		rewind(stdin);
	} while (!scanf_s("%lf", &x));


	do
	{
		printf("Enter e:");
		rewind(stdin);
	} while (!scanf_s("%lf", &e));

	sinX = sin(x);
	printf("sin(x)=%lf\n", sinX);

	element = x;
	rs = 1 + e;

	double sum = 0.0;
	int i;
	for (i = 1; rs > e; i++)
	{
		sum += element;
		element *= (-1.0) * x * x / (2.0 * i) / (2.0 * i + 1.0);
		rs = fabs(sinX - sum);
	}

	printf("sum=%lf\n", sum);
	printf("When n=%d, the expression differs from the sin(x) by a given error", i - 1);

	return 0;