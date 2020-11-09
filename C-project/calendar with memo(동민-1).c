#include <stdio.h>
#include <string.h>
#include "cful.h"

void clear_buffer(void)//�Է¹��� ����
{
    while (getchar() != '\n');
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

void memo(file_name)
{
    FILE* stream = NULL;
    FILE* write = NULL;//����������������
    int mode, rewrite_line, line_count = 0;
    char str[50];
    char rewrite[50];//�����������幮�ڿ�
    char rewrite_file[20] = "rewrite.txt";


    while (1)
    {
        printf("� �۾��� �ϰڽ��ϱ�?(���� : 0, �Է� : 1, �б� : 2, ���� : 3)\n");
        printf("������ ������ ������ ���� �� �����ϴ�.��\n\n");

        do
        {
            printf("�Է� : ");
            scanf_s("%d", &mode);
        } while (mode < 0 || mode > 3);
        clear_buffer();

        if (mode == 0)
        {
            printf("����˴ϴ�...");
            break;
        }

        if (mode == 1)
        {
            printf("�Է� ���...\n\n");

            if (0 == fopen_s(&stream, file_name, "at"))
            {
                printf("�Է��ϼ���. 0�� �Է��ϸ� �����մϴ�.\n");
                while (1)
                {
                    printf("�Է� : ");
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

        if (mode == 2)
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

        if (mode == 3)
        {
            printf("���� ���...\n\n");

            if (0 == fopen_s(&stream, file_name, "rt"))
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
                            printf("������ ������ �Է��ϼ���: ");

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

            printf("������� ����...\n\n");
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

    k = (sum+1) % 7;//1�� 1���� ��ĥ�̾����� ���
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

void DateToArr(char** date_num, int date) //�Էµ� ���� ���ڿ��� �ٲ��ִ� �Լ� (���� ���ڿ���)
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

void make_filename(int year, int month, int day, char *date_txt)//�Է¹��� ��¥�� �迭�� ���ϸ����� ����
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
    
    printf("����� ��, �� �Է� (year/month/day ����):");
    scanf_s("%d/%d/%d", &year, &month, &day);

    make_filename(year, month, day, date_txt);
    calendar(year, month, day);
    memo(date_txt);

}