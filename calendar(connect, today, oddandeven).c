#include <stdio.h>
#include <string.h>
#include <time.h>
#include "cful.h"

void DateToArr(char* date_num, int date);
void clear_buffer(void);
void memo(char* file_name);
void Calendar(int year, int month, int day);
long totalday(int y, int m, int d);
int isyoon(int a);
void TodayMemo(void);

int main(void)
{
    int year, month, day;
    char date[20];
    char date_num[20] = { 0 }, year_num[20] = { 0 }, mon_num[20] = { 0 }, day_num[20] = { 0 }, txt[5] = ".txt";

    printf("출력할 년, 월 입력 (year/month/day 형식):");
    scanf_s("%d/%d/%d", &year, &month, &day);

    DateToArr(year_num, year); //여기서부터가 문자열을 저장하기 위한 부분
    DateToArr(mon_num, month);
    DateToArr(day_num, day);

    strcpy_s(date_num, sizeof(date_num), year_num);
    strcat_s(date_num, sizeof(date_num), mon_num);
    strcat_s(date_num, sizeof(date_num), day_num);
    strcat_s(date_num, sizeof(date_num), txt);

    TodayMemo();

    printf("\n=================================================================================================================\n");

    Calendar(year, month, day);

    printf("\n=================================================================================================================\n");

    fflush(stdout); //만약을 위해 출력 버퍼 비우기

    memo(date_num);

    return 0;

}

void DateToArr(char* date_num, int date) //입력된 수를 문자열로 바꿔주는 함수 (같은 문자열에)
{
    int num, temp, i = 0;
    char str[20];
    num = 1000;


    while (num > date)
        num = num / 10;
    if (date < 10)
    {
        str[i] = '0';
        i++;
    }
    while (num >= 1)
    {
        temp = date / num;
        str[i] = (char)(temp + 48);
        date = date % num;
        num = num / 10;
        i++;
    }
    str[i] = '\0';
    strcpy_s(date_num, 20, str);

    return;
}


void clear_buffer(void)     //버퍼 제거
{
    while (getchar() != '\n');
    return;
}

void memo(char* file_name)
{
    FILE* stream = NULL;
    FILE* write = NULL;     //수정용 파일 포인터
    int mode, rewrite_line, line_count = 0;
    char str[50];
    char rewrite[50];       //수정 내용 저장 문자열
    char rewrite_file[15] = "rewrite.txt";    //수정용 임시 파일


    while (1)
    {
        printf("어떤 작업모드를 택하겠습니까?(종료 : 0, 입력 : 1, 읽기 : 2, 수정 : 3)\n");
        printf("※주의 파일이 없으면 읽을 수 없습니다.※\n\n");

        do
        {
            printf("모드 입력 : ");
            scanf_s("%d", &mode);
        } while (mode < 0 || mode > 3);
        clear_buffer();

        if (mode == 0)
        {
            printf("종료됩니다...");
            break;
        }

        if (mode == 1)      //파일에 내용 입력
        {
            printf("입력 모드...\n\n");

            if (0 == fopen_s(&stream, file_name, "at"))
            {
                printf("내용을 입력하세요. 제일 처음에 0이 입력되면 종료됩니다.\n"); // 맨 앞자리가 0으로 입력되면 실행 되나 안 되나
                while (1)
                {
                    printf("일정을 입력하세요 : ");
                    fgets(str, sizeof(str), stdin);
                    if (48 == (int)str[0])
                    {
                        printf("입력모드 종료...\n\n");
                        break;
                    }
                    else
                        fputs(str, stream);
                }
                fclose(stream);
            }
        }

        if (mode == 2)      //파일의 내용 출력
        {
            printf("출력 모드...\n\n");

            if (0 == fopen_s(&stream, file_name, "rt"))
            {
                line_count = 0;
                while (fgets(str, sizeof(str), stream) != NULL)
                {
                    line_count++;
                    printf("[%d]번째 줄 : %s", line_count, str);
                }

                printf("\n출력모드 종료...\n\n");
                fclose(stream);
            }
        }

        if (mode == 3)      //파일의 내용을 출력 후에 수정 내용을 입력받음
        {
            printf("수정 모드...\n\n");

            if (0 == fopen_s(&stream, file_name, "rt"))     //파일 내용 출력
            {
                line_count = 0;
                while (fgets(str, sizeof(str), stream) != NULL)
                {
                    line_count++;
                    printf("[%d]번째 줄 : %s", line_count, str);
                }

                printf("수정하실 줄의 번호를 입력하세요: ");
                scanf_s("%d", &rewrite_line);
                clear_buffer();
                fclose(stream);
            }
            if (0 == fopen_s(&stream, file_name, "rt"))     //파일의 내용을 수정 -> 임시 파일에 저장
            {
                if (0 == fopen_s(&write, rewrite_file, "wt"))
                {

                    line_count = 0;
                    while (fgets(str, sizeof(str), stream) != NULL)
                    {
                        line_count++;
                        if (line_count == rewrite_line)
                        {
                            printf("수정할 내용을 입력하세요: ");

                            fgets(rewrite, sizeof(rewrite), stdin);     //수정할 줄이 되면 내용을 입력받고 임시파일에 저장
                            fputs(rewrite, write);
                            continue;

                        }
                        fputs(str, write);      //원본 파일의 내용을 임시 파일에 저장
                    }
                    fclose(write);
                    fclose(stream);

                }
            }
            if (0 == fopen_s(&stream, file_name, "wt"))     //임시 파일 내용 -> 원래 파일에 내용 저장
            {
                if (0 == fopen_s(&write, rewrite_file, "rt"))
                {
                    while (fgets(str, sizeof(str), write) != NULL)
                    {
                        fputs(str, stream);
                    }
                    fclose(write);
                }
                fclose(stream);
            }
            printf("수정모드 종료...\n\n");
        }


    }

    return;
}

void Calendar(int year, int month, int day)
{
    int i, j, k;
    int sum = 0;
    int chk = 0;
    int basicyear[] = { 31,28,31,30,31,30,31,31,30,31,30,31 };
    long dates;
    int fy = 2020, fm = 8, fd = 30;
    int count; // 주차 계산

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

    k = (sum + 1) % 7; //1월 1일이 며칠이었는지 계산
    // k=sum%7만 할 경우에는 한 자리씩 앞으로 당겨지는 결과

    dates = totalday(year, month, day) - totalday(fy, fm, fd);
    count = dates / 7 + 1;

    printf("\n주차 : %d 주차 \n\n", count);

    //출력
    printf("Sun\tMon\tTue\tWed\tThu\tFri\tSat\n");
    printf("===================================================== \n");

    for (j = 0; j < k; j++)
        printf("\t"); //시작 요일에 맞춰 정렬

    for (i = 1; i <= basicyear[month - 1]; i++)
    {

        if (i == day)
        {
            int r = 255, g = 40, b = 00;
            SET_COLOR(FOREGROUND, r, g, b);
            printf("%d\t", i, RESET);
        }
        else
        {
            int r = 255, g = 255, b = 255;
            SET_COLOR(FOREGROUND, r, g, b);
            printf("%d\t", i, RESET);
        }

        if (k == 6) {
            k = -1;
            printf("\n");
        }
        k++;

    }
    printf("\n");

    return;
}

long totalday(int y, int m, int d) // 날짜수 계산하는 함수
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

int isyoon(int a) //윤년 판단하는 함수
{
    if ((a % 4 == 0) && !(a % 100 == 0) || (a % 400))
    {
        return 1;
    }
    else
        return 0;
}

void TodayMemo(void)
{
    FILE* stream = NULL;
    time_t now = time(NULL);
    struct tm date;
    char date_num[20] = { 0 }, year_num[20] = { 0 }, mon_num[20] = { 0 }, day_num[20] = { 0 }, txt[5] = ".txt", str[50];
    int line_count;

    localtime_s(&date, &now);

    printf("now : %d-%d-%d\n", date.tm_year + 1900, date.tm_mon + 1, date.tm_mday); // 날짜를 출력하는 부분

    DateToArr(year_num, date.tm_year + 1900); //여기서부터가 문자열을 저장하기 위한 부분
    DateToArr(mon_num, date.tm_mon + 1);
    DateToArr(day_num, date.tm_mday);

    strcpy_s(date_num, sizeof(date_num), year_num);
    strcat_s(date_num, sizeof(date_num), mon_num);
    strcat_s(date_num, sizeof(date_num), day_num);
    strcat_s(date_num, sizeof(date_num), txt);

    printf("오늘의 일정 출력...\n\n");

    if (0 == fopen_s(&stream, date_num, "rt"))
    {
        line_count = 0;
        while (fgets(str, sizeof(str), stream) != NULL)
        {
            line_count++;
            printf("[%d]번째 줄 : %s", line_count, str);
        }

        printf("\n출력모드 종료...\n\n");
        fclose(stream);
    }
    else
        printf("오늘의 일정 없음!");

    return;
}