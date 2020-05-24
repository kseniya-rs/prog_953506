#include <stdio.h>
#include <conio.h>

void Input() //Сообщение о запрашиваемых параметрах
{
	printf("Vvedite stoimost auto v Evrosouse\n");
	printf("God vipuska\n");
	printf("Ob'em dvigatelya (sm^3)\n");
	printf("Rasstoyanie progona\n");
}

int Proverka(float prise, int year, float engine, int run)
{
	int a = 0;
	if (prise <= 0)
		a += 1;
	if (year < 1900 || year > 2020)
		a += 1;
	if (engine < 1000)
		a += 1;
	if (run <= 0)
		a += 1;
	if (a > 0)
		return 0;
	else
		return 1;
}

float Customs(int year, float engine) //Вычисление цены растамаживания, зависящая от объема двигателя и «возраста» автомобиля
{
	if (2020 - year < 4)
	{
		return engine * 0.6;
	}
	else if (2020 - year > 3 && 2020 - year < 11)
	{
		if (engine < 2500)
			return engine * 0.35;
		else
			return engine * 0.6;
	}
	else if (2020 - year > 10 && 2020 - year < 14)
		return engine * 0.6;
	else
		return engine * 2;
}

void Output(float driving, float customs_clearance, float prise_rb)
{
	printf("Stoimost peregona = ");
	printf("%.2f", driving);
	printf("\nStoimost rastamazivaniya = ");
	printf("%.2f", customs_clearance);
	printf("\nCena v RB = ");
	printf("%.2f", prise_rb);
}

int main()
{
	int year, run, a;
	float prise, engine, driving, customs_clearance = 0, prise_rb;
	Input();
	scanf_s("%f", &prise);
	scanf_s("%i", &year);
	scanf_s("%f", &engine);
	scanf_s("%i", &run);
	a = Proverka(prise, year, engine, run);
	if (a == 0)
	{
		printf("\nError");
		return 0;
	}
	driving = run * 0.5;
	customs_clearance = Customs(year, engine);
	prise_rb = customs_clearance + prise;
	Output(driving, customs_clearance, prise_rb);
	return 0;
}