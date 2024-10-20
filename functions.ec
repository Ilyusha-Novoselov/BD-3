#include <stdlib.h>

#include "functions.h"

void print_errors(const char* theOperation) {
    fprintf(stderr, "Error code: {%ld} on %s\n", sqlca.sqlcode, theOperation);
    fprintf(stderr, "Message: %s\n", sqlca.sqlerrm.sqlerrmc);
}

void check_errors(const char* theOperation) {
    if (sqlca.sqlcode < 0) {
        print_errors(theOperation);
        exit(ERROR);
    }
}

int check_warnings(const char* theOperation) {
    // Если выполнилось с ошибкой
    if (sqlca.sqlcode < 0) {
        print_warnings(theOperation);
        return 1;
    }
    return 0;
}

void print_warnings(const char* theOperation) {
    fprintf(stderr, "Warning code: {%ld} on %s\n", sqlca.sqlcode, theOperation);
    fprintf(stderr, "Message: %s\n", sqlca.sqlerrm.sqlerrmc);
}

void connect_db(const char* theLogin, const char* thePassword) {
    exec sql begin declare section; // Начало секции объявления переменных
    const char* login = theLogin;
    const char* password = thePassword;
    const char* db = DB;
    exec sql end declare section; // Конец секции объявления переменных

    exec sql connect to :db user :login using :password; // Устанавливаем соединение с бд
    check_errors("Connect to db");
}

void connect_schema(const char* theSchema) {
    exec sql begin declare section; // Начало секции объявления переменных
    const char* schema = theSchema;
    exec sql end declare section; // Конец секции объявления переменных

    exec sql set search_path to :schema; // Устанавливаем соединение со схемой
    check_errors("Connect schema");
}

void disconnect_db() {
    exec sql disconnect; // Отключение от базы данных
    check_errors("Disconnect from db");
    printf("Disconnected from the database successfully.\n");
}

void table_rollback() {
    exec sql begin work; // Начало новой транзакции

    exec sql drop table if exists j cascade;

    exec sql create table j (
        n_izd character(6) primary key,
        name character(20),
        town character(20)
    );

    exec sql insert into j values
        ('J1', 'Жесткий диск', 'Париж'),
        ('J2', 'Перфоратор', 'Рим'),
        ('J3', 'Считыватель', 'Афины'),
        ('J4', 'Принтер', 'Афины'),
        ('J5', 'Флоппидиск-', 'Лондон'),
        ('J6', 'Терминал', 'Осло'),
        ('J7', 'Лента', 'Лондон');

    exec sql drop table if exists s cascade;

    exec sql create table s (
        n_post character(6) primary key,
        name character(20),
        reiting integer,
        town character(20)
    );

    exec sql insert into s values
        ('S1', 'Смит', 20, 'Лондон'),
        ('S2', 'Джонс', 10, 'Париж'),
        ('S3', 'Блейк', 30, 'Париж'),
        ('S4', 'Кларк', 20, 'Лондон'),
        ('S5', 'Адамс', 30, 'Афины');

    exec sql drop table if exists p cascade;

    exec sql create table p (
        n_det character(6) primary key,
        name character(20),
        cvet character(20),
        ves integer,
        town character(20)
    );

    exec sql insert into p values
        ('P1', 'Гайка', 'Красный', 12, 'Лондон'),
        ('P2', 'Болт', 'Зеленый', 17, 'Париж'),
        ('P3', 'Винт', 'Голубой', 17, 'Рим'),
        ('P4', 'Винт', 'Красный', 14, 'Лондон'),
        ('P5', 'Кулачок', 'Голубой', 12, 'Париж'),
        ('P6', 'Блюм', 'Красный', 19, 'Лондон');

    exec sql drop table if exists spj cascade;

    exec sql create table spj (
        n_post character(6),
        n_det character(6),
        n_izd character(6),
        kol integer
    );

    exec sql insert into spj values
        ('S1', 'P1', 'J1', 200),
        ('S1', 'P1', 'J4', 700),
        ('S2', 'P3', 'J1', 400),
        ('S2', 'P3', 'J2', 200),
        ('S2', 'P3', 'J3', 200),
        ('S2', 'P3', 'J4', 500),
        ('S2', 'P3', 'J5', 600),
        ('S2', 'P3', 'J6', 400),
        ('S2', 'P3', 'J7', 800),
        ('S2', 'P5', 'J2', 100),
        ('S3', 'P3', 'J1', 200),
        ('S3', 'P4', 'J2', 500),
        ('S4', 'P6', 'J3', 300),
        ('S4', 'P6', 'J7', 300),
        ('S5', 'P2', 'J2', 200),
        ('S5', 'P2', 'J4', 100),
        ('S5', 'P5', 'J5', 500),
        ('S5', 'P5', 'J7', 100),
        ('S5', 'P6', 'J2', 200),
        ('S5', 'P1', 'J4', 100),
        ('S5', 'P3', 'J4', 200),
        ('S5', 'P4', 'J4', 800),
        ('S5', 'P5', 'J4', 400),
        ('S5', 'P6', 'J4', 500);

    if(check_warnings("Table rollback")) {
        exec sql rollback work; // Откат транзакции
    }
    else {
        printf("Changed: %ld records\n", sqlca.sqlerrd[2]);
        exec sql commit work; // Завершение транзакции
    }
}


void task_1() {
    exec sql begin declare section; // Начало секции объявления переменных
    int count = 0;
    exec sql end declare section; // Конец секции объявления переменных

    exec sql begin work; // Начало новой транзакции
    exec sql select count(distinct spj.n_det) into:count
             from spj
             where spj.n_post in (select distinct spj.n_post
                                 from spj
                                 join j on spj.n_izd = j.n_izd
                                 where j.town = 'Париж');
    if(check_warnings("Task 1")) {
        exec sql rollback work; // Откат транзакции
    }
    else {
        printf("Count: %d\n", count);
        exec sql commit work; // Завершение транзакции
    }   
}

void task_2() {
    exec sql begin work; // Начало новой транзакции
    exec sql update p
             set cvet = case 
                 when town = 'Рим' then (select min(cvet) from p where town = 'Лондон')
                 when town = 'Лондон' then (select min(cvet) from p where town = 'Рим')
                 else cvet
             end
             where town in ('Лондон', 'Рим');
    if(check_warnings("Task 2")) {
        exec sql rollback work; // Откат транзакции
    }
    else {
        printf("Changed: %ld records\n", sqlca.sqlerrd[2]);
        exec sql commit work; // Завершение транзакции
    }
}

void task_3() {
    int rows = 0;

    exec sql begin declare section; // Начало секции объявления переменных
    struct {
        char n_post[2 * 6 + 1];
        int kol;
        float avg_kol;
    } data;
    // Индикаторы для проверки NULL
    int kol_ind;
    exec sql end declare section; // Конец секции объявления переменных

    // Объявление курсора
    exec sql declare curs_1 cursor for 
        select spj.n_post, spj.kol, avg_rim.avg_kol
        from s
        join spj on s.n_post = spj.n_post
        join (select spj.n_post, avg(spj.kol) as avg_kol
            from spj
            join j on spj.n_izd = j.n_izd
            where j.town = 'Рим'
            group by spj.n_post) as avg_rim on s.n_post = avg_rim.n_post
        where spj.kol >= 3 * avg_rim.avg_kol;

    if (check_warnings("Task 3 => Declare cursor")) {
        return;
    }

    exec sql begin work; // Начало новой транзакции

    exec sql open curs_1; // Открытие курсора

    while (sqlca.sqlcode == 0) {
        // Извлечение следующей строки результата из открытого курсора
        exec sql fetch next curs_1 into :data.n_post, :data.kol:kol_ind, :data.avg_kol;

        if(!rows && sqlca.sqlcode == 100) {
            printf("Данных нет\n");
            break;
        }

        if (sqlca.sqlcode == 0) {
            if(!rows) {
                printf("Поставщик\tОбъем поставки\tСредний объем поставки\n");
            }
            rows++;
            // Проверка на NULL
            if(kol_ind < 0) {
                data.kol = 0;
            }
            printf("%s\t\t%d\t\t%f\n", data.n_post, data.kol, data.avg_kol);
        } else {
            if(sqlca.sqlcode < 0) {
                exec sql close curs_1;
                exec sql rollback work;
                return;
            }
        }
    }

    exec sql close curs_1; // Закрытие курсора
    exec sql commit work; // Завершение транзакции
}

void task_4() {
    int rows = 0;

    exec sql begin declare section; // Начало секции объявления переменныхы
    char n_izd[2 * 6 + 1];
    exec sql end declare section; // Конец секции объявления переменных

    // Объявление курсора
    exec sql declare curs_2 cursor for 
        select j.n_izd
        from j
        except
        select distinct spj.n_izd
        from spj
        where spj.n_post in (select distinct spj.n_post
                            from spj
                            join p on spj.n_det = p.n_det
                            where p.cvet = 'Красный');

    if (check_warnings("Task 4 => Declare cursor")) {
        return;
    }

    exec sql begin work; // Начало новой транзакции
    exec sql open curs_2; // Открытие курсора

    while (sqlca.sqlcode == 0) {
        // Извлечение следующей строки результата из открытого курсора
        exec sql fetch next curs_2 into :n_izd;

        if(!rows && sqlca.sqlcode == 100) {
            printf("Данных нет\n");
            break;
        }

        if (sqlca.sqlcode == 0) {
            if(!rows) {
                printf("n_izd\n");
            }
            rows++;
            printf("%s\n", n_izd);
        } else {
            if(sqlca.sqlcode < 0) {
                exec sql close curs_2;
                exec sql rollback work;
                return;
            }
        }
    }

    exec sql close curs_2; // Закрытие курсора
    exec sql commit work; // Завершение транзакции
}

void task_5() {
    int rows = 0;

    exec sql begin declare section; // Начало секции объявления переменных
    struct {
        char n_izd[2 * 6 + 1];
        char name[2 * 20 + 1];
        char town[2 * 20 + 1];
    } j;
    // Индикаторы для проверки NULL
    int name_ind;
    int town_ind;
    exec sql end declare section; // Конец секции объявления переменных

    // Объявление курсора
    exec sql declare curs_3 cursor for 
        select *
        from j
        where j.n_izd in (select spj.n_izd
                        from spj
                        join p on p.n_det=spj.n_det
                        group by spj.n_izd
                        having min(p.ves) > 12);

    if (check_warnings("Task 5 => Declare cursor")) {
        return;
    }

    exec sql begin work; // Начало новой транзакции
    exec sql open curs_3; // Открытие курсора

    while (sqlca.sqlcode == 0) {
        // Извлечение следующей строки результата из открытого курсора
        exec sql fetch next curs_3 into :j.n_izd, :j.name:name_ind, :j.town:town_ind;

        if(!rows && sqlca.sqlcode == 100) {
            printf("Данных нет\n");
            break;
        }

        if (sqlca.sqlcode == 0) {
            if(!rows) {
                printf("n_izd\t\tname\t\t\ttown\n");
            }
            rows++;
            // Проверка на NULL
            if(name_ind < 0) {
                strcpy(j.name, "Пусто");
            }
            if(town_ind < 0) {
                strcpy(j.town, "Пусто");
            }
            printf("%s\t\t%s\t%s\n", j.n_izd, j.name, j.town);
        } else {
            if(sqlca.sqlcode < 0) {
                exec sql close curs_3;
                exec sql rollback work;
                return;
            }
        }
    }

    exec sql close curs_3; // Закрытие курсора
    exec sql commit work; // Завершение транзакции
}