#include <stdio.h>
#include "cful.h"

int isyoon(int); //윤년 적용 함수

int main()
{
	int year, month, day;
	int i, j, k;
	int sum = 0;
	int chk = 0;
	int basicyear[] = { 31,28,31,30,31,30,31,31,30,31,30,31 };

	printf("출력할 년, 월 입력 (year/month/day 형식):");
	scanf_s("%d/%d/%d", &year, &month, &day);

	if (isyoon(year))
	{
		chk = 1;
		basicyear[1]++;
	}
	else
		chk = 0;
	//윤달 확인

	sum = 365;
	for (i = 1; i < year; i++)
	{
		if (isyoon(i)) //윤달에 해당된다면 2월이 29일 이었기 때문에 하루 더해줌
			sum += 366;
		else
			sum += 365;
	} //0년부터 작년까지 며칠이었는지 세는 과정

	for (i = 0; i < month - 1; i++)
	{
		sum += basicyear[i];
	} //입력한 달까지 며칠이었는지 계산

	k = sum % 7 + 1; //1월 1일이 며칠이었는지 계산
	// k=sum%7만 할 경우에는 한 자리씩 앞으로 당겨지는 결과

	//출력
	printf("Sun\tMon\tTue\tWed\tThu\tFri\tSat\n");
	printf("===================================================== \n");

	for (j = 0; j < k; j++)
		printf("\t"); //시작 요일에 맞춰 정렬

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

int isyoon(int a) //윤년 판단하는 함수
{
	if ((a % 4 == 0) && !(a % 100 == 0) || (a % 400))
	{
		return 1;
	}
	else
		return 0;
}

