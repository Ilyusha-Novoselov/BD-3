#include <stdio.h>

#include "functions.h"

int main() {
    const char* login = "pmi-b1501";
    const char* password = "Dewfauj4";
    const char* schema = "pmib1501";

    connect_db(login, password);
    connect_schema(schema);

    int n = 1;
    while(n) {
        printf("\nВведите номер задания:\n[1-5] - номера заданий\n0 - выход\n6 - сброс таблиц до начального состояния\n");
        scanf("%d", &n);
        printf("Результат:\n\n");
        switch(n) {
            case 0:
                break;
            case 1:
                task_1();
                break;
            case 2:
                task_2();
                break;
            case 3:
                task_3();
                break;
            case 4:
                task_4();
                break;
            case 5:
                task_5();
                break;
            case 6:
                table_rollback();
                break;
            default:
                printf("Неверный ввод номера задания\n");
                break;
        }
    }

    disconnect_db();

    return 0;
}