#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CAR_NAME 20
#define MAX_CAR_LICENCE 50
#define MAX_CAR_YEAR 20

typedef struct l_car_infor{
    int index;
    char name[MAX_CAR_NAME];
    char licence[MAX_CAR_LICENCE];
    char year[MAX_CAR_YEAR];
    struct l_car_infor *next;
}car_infor;

car_infor *head, *tail;
int last_index;

void init_car_infor()
{
    car_infor *a;

    last_index = 0;

    while (head != NULL)
    {
        a = head;
        head = head->next;
        free(a);
    }
    head = tail = NULL;
}

void clearInputBuffer()
{

    while (getchar() != '\n');
}

int add_car_infor(car_infor data)
{
    car_infor *a;
    if (data.index == 0)
        return 0;

    if ((a = (car_infor *) malloc(sizeof(car_infor))) == NULL) {
        printf("[ 메모리가 부족!!! ]\n");
        return 0;
    }

    a->index = data.index;
    strcpy(a->name, data.name);
    strcpy(a->licence, data.licence);
    strcpy(a->year, data.year);
    a->next = NULL;

    if (tail == NULL)
        head = tail = a;
    else
    {
        tail->next = a;
        tail = a;
    }
    return 1;
}

void menu_add()
{
    car_infor data;
    data.index = last_index + 1;

    do {
        printf("[ 자동차 데이터 입력 ]\n");
        printf("1. 차종 이름 : ");
        gets(data.name);
        printf("2. 차량 번호 : ");
        gets(data.licence);
        printf("3. 차량 연식 : ");
        gets(data.year);
    } while (strlen(data.name) <= 0 || strlen(data.licence) <= 0 || strlen(data.year) <= 0);

    if (add_car_infor(data)) {
        printf("[ 추가 성공! ]\n\n");
        last_index++;
    }
    else
        printf("[  추가 실패!!! ]\n\n");
}

void show_car_infor(car_infor *data)
{
    printf("=========================\n");
    printf("1. 이름 : %s\n", data->name);
    printf("2. 차량 번호 : %s\n", data->licence);
    printf("3. 차량 연식 : %s\n", data->year);
    printf("=========================\n");
    printf("[ 아무 키나 누르세요. ] ");
    getch();
    printf("\n\n");
}

int search_name(char *name)
{
    car_infor *a;
    int num = 0;
    a = head;
    while (a != NULL) {
        if (strstr(a->name, name)) {
            show_car_infor(a);
            num++;
        }
        a = a->next;
    }
    return num;
}

int search_licence(char *licence)
{
    car_infor *a;
    int num = 0;
    a = head;
    while (a != NULL) {
        if (strstr(a->licence, licence)) {
            show_car_infor(a);
            num++;
        }
        a = a->next;
    }
    return num;
}

int search_year(char *year)
{
    car_infor *a;
    int num = 0;
    a = head;
    while (a != NULL) {
        if (strstr(a->year, year)) {
            show_car_infor(a);
            num++;
        }
        a = a->next;
    }
    return num;
}

void menu_search()
{
    int select;
    char buffer[50];
    int result;

    while (1) {
        do {
            select = 0;

            printf("===============\n");
            printf("   1. 이름\n");
            printf("   2. 차량 번호\n");
            printf("   3. 차량 연식\n");
            printf("   4. 종료\n");
            printf("===============\n");
            printf("# 검색 항목 선택 : ");
            scanf("%d", &select);
            clearInputBuffer();

            if( select == 0)
                printf("1~4번으로 다시 선택해 주세요\n\n");
        } while (select < 1 || select > 4);

        if (select == 1) {
            printf("# 찾을 이름 : ");
            gets(buffer);
            result = search_name(buffer);
        }
        else if (select == 2) {
            printf("# 찾을 차량 번호 : ");
            gets(buffer);
            result = search_licence(buffer);
        }
        else if (select == 3) {
            printf("# 찾을 차량 연식 : ");
            gets(buffer);
            result = search_year(buffer);
        }
        else if (select == 4)
        {
            printf("\n");
            return;
        }

        if (result)
            printf("# %d개 일치 항목 검색 완료!\n\n", result);
        else
            printf("# %s와(과) 일치하는 항목 없음!!!\n\n", buffer);
    }
}

void menu()
{
    int select;

    init_car_infor();

    while(1){
        do {
            printf("===============\n");
            printf("   1. 추 가\n");
            printf("   2. 검 색\n");
            printf("   3. 종 료\n");
            printf("===============\n");
            printf("# 기능 선택 : ");
            scanf("%d", &select);
            clearInputBuffer();
            printf("\n");
        } while (select < 1 || select > 3);

        switch (select)
        {
            case 1:
                menu_add();
                break;
            case 2:
                menu_search();
                break;
            case 3:
                return;
            default:
                break;
        }
    }
}


int main()
{
    menu();



    return 0;
}
