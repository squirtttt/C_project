#include <stdio.h>
#include "cful.h"

int isyoon(int);
long totalday(int y, int m, int d); // ��¥ ��� �Լ�

int main()
{
	int year, month, day;
	int i, j, k;
	int sum = 0;
	int chk = 0;
	int basicyear[] = { 31,28,31,30,31,30,31,31,30,31,30,31 };
	long dates;
	int fy = 2020, fm = 8, fd = 30;
	int count; // ���� ���

	printf("����� ��, �� �Է� (year/month/day ����):");
	scanf_s("%d/%d/%d", &year, &month, &day);

	if (isyoon(year))
	{
		chk = 1;
		basicyear[1]++;
	}
	else
		chk = 0;
	//���� Ȯ��

	sum = 365;
	for (i = 1; i < year; i++)
	{
		if (isyoon(i)) //���޿� �ش�ȴٸ� 2���� 29�� �̾��� ������ �Ϸ� ������
			sum += 366;
		else
			sum += 365;
	} //0����� �۳���� ��ĥ�̾����� ���� ����

	for (i = 0; i < month - 1; i++)
	{
		sum += basicyear[i];
	} //�Է��� �ޱ��� ��ĥ�̾����� ���

	k = sum % 7; //1�� 1���� ��ĥ�̾����� ���
	// k=sum%7�� �� ��쿡�� �� �ڸ��� ������ ������� ���

	dates = totalday(year, month, day) - totalday(fy, fm, fd);
	count = dates / 7 + 1;

	printf("���� : %d ���� \n", count);

	//���
	printf("Sun\tMon\tTue\tWed\tThu\tFri\tSat\n");
	printf("===================================================== \n");

	for (j = 0; j < k; j++)
		printf("\t"); //���� ���Ͽ� ���� ����

	for (i = 1; i <= basicyear[month - 1]; i++)
	{

		if (i == day)
		{
			if (count % 2 == 0) // ¦���� �� ���
			{
				int r = 305, g = 40, b = 00;
				SET_COLOR(FOREGROUND, r, g, b);
				printf("%d\t", i, RESET);
			}
			else if (count%2 != 0) // Ȧ���� �� ���
			{
				int r = 300, g = 110, b = 130;
				SET_COLOR(FOREGROUND, r, g, b);
				printf("%d\t", i, RESET);
			}

		}
		else
		{
			if (count % 2 == 0) // ¦�� ���� ���
			{
				int r = 305, g = 40, b = 00;
				SET_COLOR(FOREGROUND, r, g, b);
				printf("%d\t", i, RESET);
			}
			else // Ȧ�� ���� ���
			{
				int r = 300, g = 110, b = 130;
				SET_COLOR(FOREGROUND, r, g, b);
				printf("%d\t", i, RESET);
			}
		}

		if (k == 6) {
			k = -1;
			printf("\n");
		}
		k++;

	}

	printf("\n");
}

long totalday(int y, int m, int d) // ��¥�� ����ϴ� �Լ�
{
	int months[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
	int i;
	long total = 0L;
	total = (y - 1) * 365L + (y - 1) / 4 - (y - 1) / 100 + (y - 1) / 400;
	if (!(y % 4) && y % 100 || !(y % 400))
		months[1]++;
	for (i = 0; i < m - 1; i++)
		total += months[i];
	total += d;
	return total;
}

int isyoon(int a) //���� �Ǵ��ϴ� �Լ�
{
	if ((a % 4 == 0) && !(a % 100 == 0) || (a % 400))
	{
		return 1;
	}
	else
		return 0;
}