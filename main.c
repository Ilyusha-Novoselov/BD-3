#include <stdio.h>

#include "functions.h"

int main() {
    const char* login = "pmi-b1501";
    const char* password = "Dewfauj4";
    const char* schema = "pmib1501";

    connect_db(login, password);
    connect_schema(schema);

    int n;
    while(1) {
        printf("\nВведите номер задания:\n[1-5] - номера заданий\n0 - выход\n6 - сброс таблиц до начального состояния\n");
        scanf("%d", &n);
        printf("Результат:\n");
        switch(n) {
            case 0:
                printf("Завершение программы\n");
                return 0;
            case 1:
                task_1();
                break;
            case 2:
                task_2();
                break;
            case 6:
                table_rollback();
                break;
            default:
                printf("Неверный ввод номера задания\n");
                break;
        }
    }

    return 0;
}