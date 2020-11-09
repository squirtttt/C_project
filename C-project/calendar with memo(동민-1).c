#include <stdio.h>
#include <string.h>
#include "cful.h"

void clear_buffer(void)//입력버퍼 제거
{
    while (getchar() != '\n');
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

void memo(file_name)
{
    FILE* stream = NULL;
    FILE* write = NULL;//수정내용저장파일
    int mode, rewrite_line, line_count = 0;
    char str[50];
    char rewrite[50];//수정내용저장문자열
    char rewrite_file[20] = "rewrite.txt";


    while (1)
    {
        printf("어떤 작업을 하겠습니까?(종료 : 0, 입력 : 1, 읽기 : 2, 수정 : 3)\n");
        printf("※주의 파일이 없으면 읽을 수 없습니다.※\n\n");

        do
        {
            printf("입력 : ");
            scanf_s("%d", &mode);
        } while (mode < 0 || mode > 3);
        clear_buffer();

        if (mode == 0)
        {
            printf("종료됩니다...");
            break;
        }

        if (mode == 1)
        {
            printf("입력 모드...\n\n");

            if (0 == fopen_s(&stream, file_name, "at"))
            {
                printf("입력하세요. 0을 입력하면 종료합니다.\n");
                while (1)
                {
                    printf("입력 : ");
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

        if (mode == 2)
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

        if (mode == 3)
        {
            printf("수정 모드...\n\n");

            if (0 == fopen_s(&stream, file_name, "rt"))
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
            if (0 == fopen_s(&stream, file_name, "rt"))
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

                            fgets(rewrite, sizeof(rewrite), stdin);
                            fputs(rewrite, write);
                            continue;

                        }
                        fputs(str, write);
                    }
                    fclose(write);
                    fclose(stream);

                }
            }
            if (0 == fopen_s(&stream, file_name, "wt"))
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

void calendar(year, month, day)
{
    int i, j, k;
    int sum = 0;
    int chk = 0;
    int basicyear[] = { 31,28,31,30,31,30,31,31,30,31,30,31 };

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

    k = (sum+1) % 7;//1월 1일이 며칠이었는지 계산
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
            printf("%d\t", i, RESET);
            SET_COLOR(FOREGROUND, 255, 255, 255);
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

void DateToArr(char** date_num, int date) //입력된 수를 문자열로 바꿔주는 함수 (같은 문자열에)
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

void make_filename(int year, int month, int day, char *date_txt)//입력받은 날짜를 배열에 파일명으로 저장
{
    char cyear[20], cmonth[20], cday[20];
    char txt[5] = ".txt";
    
    DateToArr(cyear, year);
    DateToArr(cmonth, month);
    DateToArr(cday, day);

    strcpy_s(date_txt, 20, cyear);
    strcat_s(date_txt, 20, cmonth);
    strcat_s(date_txt, 20, cday);
    strcat_s(date_txt, 20, txt);
    
}

int main(void)
{
    int year, month, day;
    char date_txt[20];
    
    printf("출력할 년, 월 입력 (year/month/day 형식):");
    scanf_s("%d/%d/%d", &year, &month, &day);

    make_filename(year, month, day, date_txt);
    calendar(year, month, day);
    memo(date_txt);

}