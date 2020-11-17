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

    printf("����� ��, �� �Է� (year/month/day ����):");
    scanf_s("%d/%d/%d", &year, &month, &day);

    DateToArr(year_num, year); //���⼭���Ͱ� ���ڿ��� �����ϱ� ���� �κ�
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

    fflush(stdout); //������ ���� ��� ���� ����

    memo(date_num);

    return 0;

}

void DateToArr(char* date_num, int date) //�Էµ� ���� ���ڿ��� �ٲ��ִ� �Լ� (���� ���ڿ���)
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


void clear_buffer(void)     //���� ����
{
    while (getchar() != '\n');
    return;
}

void memo(char* file_name)
{
    FILE* stream = NULL;
    FILE* write = NULL;     //������ ���� ������
    int mode, rewrite_line, line_count = 0;
    char str[50];
    char rewrite[50];       //���� ���� ���� ���ڿ�
    char rewrite_file[15] = "rewrite.txt";    //������ �ӽ� ����


    while (1)
    {
        printf("� �۾���带 ���ϰڽ��ϱ�?(���� : 0, �Է� : 1, �б� : 2, ���� : 3)\n");
        printf("������ ������ ������ ���� �� �����ϴ�.��\n\n");

        do
        {
            printf("��� �Է� : ");
            scanf_s("%d", &mode);
        } while (mode < 0 || mode > 3);
        clear_buffer();

        if (mode == 0)
        {
            printf("����˴ϴ�...");
            break;
        }

        if (mode == 1)      //���Ͽ� ���� �Է�
        {
            printf("�Է� ���...\n\n");

            if (0 == fopen_s(&stream, file_name, "at"))
            {
                printf("������ �Է��ϼ���. ���� ó���� 0�� �ԷµǸ� ����˴ϴ�.\n"); // �� ���ڸ��� 0���� �ԷµǸ� ���� �ǳ� �� �ǳ�
                while (1)
                {
                    printf("������ �Է��ϼ��� : ");
                    fgets(str, sizeof(str), stdin);
                    if (48 == (int)str[0])
                    {
                        printf("�Է¸�� ����...\n\n");
                        break;
                    }
                    else
                        fputs(str, stream);
                }
                fclose(stream);
            }
        }

        if (mode == 2)      //������ ���� ���
        {
            printf("��� ���...\n\n");

            if (0 == fopen_s(&stream, file_name, "rt"))
            {
                line_count = 0;
                while (fgets(str, sizeof(str), stream) != NULL)
                {
                    line_count++;
                    printf("[%d]��° �� : %s", line_count, str);
                }

                printf("\n��¸�� ����...\n\n");
                fclose(stream);
            }
        }

        if (mode == 3)      //������ ������ ��� �Ŀ� ���� ������ �Է¹���
        {
            printf("���� ���...\n\n");

            if (0 == fopen_s(&stream, file_name, "rt"))     //���� ���� ���
            {
                line_count = 0;
                while (fgets(str, sizeof(str), stream) != NULL)
                {
                    line_count++;
                    printf("[%d]��° �� : %s", line_count, str);
                }

                printf("�����Ͻ� ���� ��ȣ�� �Է��ϼ���: ");
                scanf_s("%d", &rewrite_line);
                clear_buffer();
                fclose(stream);
            }
            if (0 == fopen_s(&stream, file_name, "rt"))     //������ ������ ���� -> �ӽ� ���Ͽ� ����
            {
                if (0 == fopen_s(&write, rewrite_file, "wt"))
                {

                    line_count = 0;
                    while (fgets(str, sizeof(str), stream) != NULL)
                    {
                        line_count++;
                        if (line_count == rewrite_line)
                        {
                            printf("������ ������ �Է��ϼ���: ");

                            fgets(rewrite, sizeof(rewrite), stdin);     //������ ���� �Ǹ� ������ �Է¹ް� �ӽ����Ͽ� ����
                            fputs(rewrite, write);
                            continue;

                        }
                        fputs(str, write);      //���� ������ ������ �ӽ� ���Ͽ� ����
                    }
                    fclose(write);
                    fclose(stream);

                }
            }
            if (0 == fopen_s(&stream, file_name, "wt"))     //�ӽ� ���� ���� -> ���� ���Ͽ� ���� ����
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
            printf("������� ����...\n\n");
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
    int count; // ���� ���

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

    k = (sum + 1) % 7; //1�� 1���� ��ĥ�̾����� ���
    // k=sum%7�� �� ��쿡�� �� �ڸ��� ������ ������� ���

    dates = totalday(year, month, day) - totalday(fy, fm, fd);
    count = dates / 7 + 1;

    printf("\n���� : %d ���� \n\n", count);

    //���
    printf("Sun\tMon\tTue\tWed\tThu\tFri\tSat\n");
    printf("===================================================== \n");

    for (j = 0; j < k; j++)
        printf("\t"); //���� ���Ͽ� ���� ����

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

void TodayMemo(void)
{
    FILE* stream = NULL;
    time_t now = time(NULL);
    struct tm date;
    char date_num[20] = { 0 }, year_num[20] = { 0 }, mon_num[20] = { 0 }, day_num[20] = { 0 }, txt[5] = ".txt", str[50];
    int line_count;

    localtime_s(&date, &now);

    printf("now : %d-%d-%d\n", date.tm_year + 1900, date.tm_mon + 1, date.tm_mday); // ��¥�� ����ϴ� �κ�

    DateToArr(year_num, date.tm_year + 1900); //���⼭���Ͱ� ���ڿ��� �����ϱ� ���� �κ�
    DateToArr(mon_num, date.tm_mon + 1);
    DateToArr(day_num, date.tm_mday);

    strcpy_s(date_num, sizeof(date_num), year_num);
    strcat_s(date_num, sizeof(date_num), mon_num);
    strcat_s(date_num, sizeof(date_num), day_num);
    strcat_s(date_num, sizeof(date_num), txt);

    printf("������ ���� ���...\n\n");

    if (0 == fopen_s(&stream, date_num, "rt"))
    {
        line_count = 0;
        while (fgets(str, sizeof(str), stream) != NULL)
        {
            line_count++;
            printf("[%d]��° �� : %s", line_count, str);
        }

        printf("\n��¸�� ����...\n\n");
        fclose(stream);
    }
    else
        printf("������ ���� ����!");

    return;
}