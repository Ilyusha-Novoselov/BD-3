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
    exec sql begin declare section;
    const char* login = theLogin;
    const char* password = thePassword;
    const char* db = DB;
    exec sql end declare section;

    exec sql connect to :db user :login using :password;
    check_errors("Connect to db");
}

void connect_schema(const char* theSchema) {
    exec sql begin declare section;
    const char* schema = theSchema;
    exec sql end declare section;

    exec sql set search_path to :schema;
    check_errors("Connect schema");
}

void table_rollback() {
    exec sql begin work;

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
        exec sql rollback work;
    }
    else {
        printf("Changed: %ld rows\n", sqlca.sqlerrd[2]);
        exec sql commit work;
    }
}


void task_1() {
    exec sql begin declare section;
    int count;
    exec sql end declare section;

    exec sql begin work;
    exec sql select count(distinct spj.n_det) into :count
             from spj
             join j on spj.n_izd = j.n_izd
             where j.town = 'Париж';
    exec sql commit work;
    printf("Count: %d\n", count);
}

void task_2() {
    exec sql begin work;
    exec sql update p
             set cvet = case 
                 when town = 'Рим' then (select min(cvet) from p where town = 'Лондон')
                 when town = 'Лондон' then (select min(cvet) from p where town = 'Рим')
                 else cvet
             end
             where town in ('Лондон', 'Рим');
    if(check_warnings("Task 2")) {
        exec sql rollback work;
    }
    else {
        printf("Changed: %ld rows\n", sqlca.sqlerrd[2]);
        exec sql commit work;
    }
}

void task_3() {
    int rows = 0;

    exec sql begin declare section;
    struct {
        char n_post[2 * 6 + 1];
        int kol;
        float avg_kol;
    } data;
    exec sql end declare section;

    if (check_warnings("Declared")) {
        return;
    }

    exec sql begin work;
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
    exec sql open curs_1;

    if (check_warnings("Open cursor")) {
        return;
    }

    exec sql fetch next curs_1 into :data.n_post, :data.kol, :data.avg_kol;
    if (sqlca.sqlcode == 0) {
        rows++;
        printf("Поставщик\tОбъем поставки\tСредний объем поставки\n");
        printf("%s\t\t%d\t\t%f\n", data.n_post, data.kol, data.avg_kol);
    }

    while (sqlca.sqlcode == 0) {
        exec sql fetch next curs_1 into :data.n_post, :data.kol, :data.avg_kol;

        if (sqlca.sqlcode == 0) {
            rows++;
            printf("%s\t\t%d\t\t%f\n", data.n_post, data.kol, data.avg_kol);
        }
    }

    exec sql close curs_1;

    if(check_warnings("Task 3")) {
        exec sql rollback work;
    }
    else {
        exec sql commit work;
    }
}

void task_4() {
    int rows = 0;

    exec sql begin declare section;
    char n_izd[2 * 6 + 1];
    exec sql end declare section;

    if (check_warnings("Declared")) {
        return;
    }

    exec sql begin work;
    exec sql declare curs_2 cursor for
        select j.n_izd
        from j
        except
        select spj.n_izd
        from spj
        join p on spj.n_det = p.n_det
        where p.cvet = 'Красный';
    exec sql open curs_2;

    if (check_warnings("Open cursor")) {
        return;
    }

    exec sql fetch next curs_2 into :n_izd;
    if (sqlca.sqlcode == 0) {
        rows++;
        printf("n_izd\n");
        printf("%s\n", n_izd);
    }

    while (sqlca.sqlcode == 0) {
        exec sql fetch next curs_2 into :n_izd;

        if (sqlca.sqlcode == 0) {
            rows++;
            printf("%s\n", n_izd);
        }
    }

    exec sql close curs_2;

    if(check_warnings("Task 4")) {
        exec sql rollback work;
    }
    else {
        exec sql commit work;
    }
}