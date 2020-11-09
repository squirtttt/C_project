#include <stdio.h>
#include "cful.h"

int isyoon(int); //���� ���� �Լ�

int main()
{
	int year, month, day;
	int i, j, k;
	int sum = 0;
	int chk = 0;
	int basicyear[] = { 31,28,31,30,31,30,31,31,30,31,30,31 };

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

	k = sum % 7 + 1; //1�� 1���� ��ĥ�̾����� ���
	// k=sum%7�� �� ��쿡�� �� �ڸ��� ������ ������� ���

	//���
	printf("Sun\tMon\tTue\tWed\tThu\tFri\tSat\n");
	printf("===================================================== \n");

	for (j = 0; j < k; j++)
		printf("\t"); //���� ���Ͽ� ���� ����

	for (i = 1; i <= basicyear[month - 1]; i++)
	{
		if (i == day)
		{
			int r = 255, g = 040, b = 000;
			SET_COLOR(FOREGROUND, r, g, b);
			printf("%d\n", i, RESET);
		}
		else
			printf("%d\t", i);
		if (k == 6) {
			k = -1;
			printf("\n");
		}
		k++;


	}
	printf("\n");
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

