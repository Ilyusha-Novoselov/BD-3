/* Processed by ecpg (14.13 (Ubuntu 14.13-0ubuntu0.22.04.1)) */
/* These include files are added by the preprocessor */
#include <ecpglib.h>
#include <ecpgerrno.h>
#include <sqlca.h>
/* End of automatic include section */

#line 1 "functions.ec"
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
    /* exec sql begin declare section */ // Начало секции объявления переменных
        
        
        
    
#line 33 "functions.ec"
 const char * login = theLogin ;
 
#line 34 "functions.ec"
 const char * password = thePassword ;
 
#line 35 "functions.ec"
 const char * db = DB ;
/* exec sql end declare section */
#line 36 "functions.ec"
 // Конец секции объявления переменных

    { ECPGconnect(__LINE__, 0, db , login , password , NULL, 0); }
#line 38 "functions.ec"
 // Устанавливаем соединение с бд
    check_errors("Connect to db");
}

void connect_schema(const char* theSchema) {
    /* exec sql begin declare section */ // Начало секции объявления переменных
        
    
#line 44 "functions.ec"
 const char * schema = theSchema ;
/* exec sql end declare section */
#line 45 "functions.ec"
 // Конец секции объявления переменных

    { ECPGdo(__LINE__, 0, 1, NULL, 0, ECPGst_normal, "set search_path to $0", 
	ECPGt_char,&(schema),(long)0,(long)1,(1)*sizeof(char), 
	ECPGt_NO_INDICATOR, NULL , 0L, 0L, 0L, ECPGt_EOIT, ECPGt_EORT);}
#line 47 "functions.ec"
 // Устанавливаем соединение со схемой
    check_errors("Connect schema");
}

void disconnect_db() {
    { ECPGdisconnect(__LINE__, "CURRENT");}
#line 52 "functions.ec"
 // Отключение от базы данных
    check_errors("Disconnect from db");
    printf("Disconnected from the database successfully.\n");
}

void table_rollback() {
    { ECPGtrans(__LINE__, NULL, "begin work");}
#line 58 "functions.ec"
 // Начало новой транзакции

    { ECPGdo(__LINE__, 0, 1, NULL, 0, ECPGst_normal, "drop table if exists j cascade", ECPGt_EOIT, ECPGt_EORT);}
#line 60 "functions.ec"


    { ECPGdo(__LINE__, 0, 1, NULL, 0, ECPGst_normal, "create table j ( n_izd character ( 6 ) primary key , name character ( 20 ) , town character ( 20 ) )", ECPGt_EOIT, ECPGt_EORT);}
#line 66 "functions.ec"


    { ECPGdo(__LINE__, 0, 1, NULL, 0, ECPGst_normal, "insert into j values ( 'J1' , 'Жесткий диск' , 'Париж' ) , ( 'J2' , 'Перфоратор' , 'Рим' ) , ( 'J3' , 'Считыватель' , 'Афины' ) , ( 'J4' , 'Принтер' , 'Афины' ) , ( 'J5' , 'Флоппидиск-' , 'Лондон' ) , ( 'J6' , 'Терминал' , 'Осло' ) , ( 'J7' , 'Лента' , 'Лондон' )", ECPGt_EOIT, ECPGt_EORT);}
#line 75 "functions.ec"


    { ECPGdo(__LINE__, 0, 1, NULL, 0, ECPGst_normal, "drop table if exists s cascade", ECPGt_EOIT, ECPGt_EORT);}
#line 77 "functions.ec"


    { ECPGdo(__LINE__, 0, 1, NULL, 0, ECPGst_normal, "create table s ( n_post character ( 6 ) primary key , name character ( 20 ) , reiting integer , town character ( 20 ) )", ECPGt_EOIT, ECPGt_EORT);}
#line 84 "functions.ec"


    { ECPGdo(__LINE__, 0, 1, NULL, 0, ECPGst_normal, "insert into s values ( 'S1' , 'Смит' , 20 , 'Лондон' ) , ( 'S2' , 'Джонс' , 10 , 'Париж' ) , ( 'S3' , 'Блейк' , 30 , 'Париж' ) , ( 'S4' , 'Кларк' , 20 , 'Лондон' ) , ( 'S5' , 'Адамс' , 30 , 'Афины' )", ECPGt_EOIT, ECPGt_EORT);}
#line 91 "functions.ec"


    { ECPGdo(__LINE__, 0, 1, NULL, 0, ECPGst_normal, "drop table if exists p cascade", ECPGt_EOIT, ECPGt_EORT);}
#line 93 "functions.ec"


    { ECPGdo(__LINE__, 0, 1, NULL, 0, ECPGst_normal, "create table p ( n_det character ( 6 ) primary key , name character ( 20 ) , cvet character ( 20 ) , ves integer , town character ( 20 ) )", ECPGt_EOIT, ECPGt_EORT);}
#line 101 "functions.ec"


    { ECPGdo(__LINE__, 0, 1, NULL, 0, ECPGst_normal, "insert into p values ( 'P1' , 'Гайка' , 'Красный' , 12 , 'Лондон' ) , ( 'P2' , 'Болт' , 'Зеленый' , 17 , 'Париж' ) , ( 'P3' , 'Винт' , 'Голубой' , 17 , 'Рим' ) , ( 'P4' , 'Винт' , 'Красный' , 14 , 'Лондон' ) , ( 'P5' , 'Кулачок' , 'Голубой' , 12 , 'Париж' ) , ( 'P6' , 'Блюм' , 'Красный' , 19 , 'Лондон' )", ECPGt_EOIT, ECPGt_EORT);}
#line 109 "functions.ec"


    { ECPGdo(__LINE__, 0, 1, NULL, 0, ECPGst_normal, "drop table if exists spj cascade", ECPGt_EOIT, ECPGt_EORT);}
#line 111 "functions.ec"


    { ECPGdo(__LINE__, 0, 1, NULL, 0, ECPGst_normal, "create table spj ( n_post character ( 6 ) , n_det character ( 6 ) , n_izd character ( 6 ) , kol integer )", ECPGt_EOIT, ECPGt_EORT);}
#line 118 "functions.ec"


    { ECPGdo(__LINE__, 0, 1, NULL, 0, ECPGst_normal, "insert into spj values ( 'S1' , 'P1' , 'J1' , 200 ) , ( 'S1' , 'P1' , 'J4' , 700 ) , ( 'S2' , 'P3' , 'J1' , 400 ) , ( 'S2' , 'P3' , 'J2' , 200 ) , ( 'S2' , 'P3' , 'J3' , 200 ) , ( 'S2' , 'P3' , 'J4' , 500 ) , ( 'S2' , 'P3' , 'J5' , 600 ) , ( 'S2' , 'P3' , 'J6' , 400 ) , ( 'S2' , 'P3' , 'J7' , 800 ) , ( 'S2' , 'P5' , 'J2' , 100 ) , ( 'S3' , 'P3' , 'J1' , 200 ) , ( 'S3' , 'P4' , 'J2' , 500 ) , ( 'S4' , 'P6' , 'J3' , 300 ) , ( 'S4' , 'P6' , 'J7' , 300 ) , ( 'S5' , 'P2' , 'J2' , 200 ) , ( 'S5' , 'P2' , 'J4' , 100 ) , ( 'S5' , 'P5' , 'J5' , 500 ) , ( 'S5' , 'P5' , 'J7' , 100 ) , ( 'S5' , 'P6' , 'J2' , 200 ) , ( 'S5' , 'P1' , 'J4' , 100 ) , ( 'S5' , 'P3' , 'J4' , 200 ) , ( 'S5' , 'P4' , 'J4' , 800 ) , ( 'S5' , 'P5' , 'J4' , 400 ) , ( 'S5' , 'P6' , 'J4' , 500 )", ECPGt_EOIT, ECPGt_EORT);}
#line 144 "functions.ec"


    if(check_warnings("Table rollback")) {
        { ECPGtrans(__LINE__, NULL, "rollback work");}
#line 147 "functions.ec"
 // Откат транзакции
    }
    else {
        printf("Changed: %ld records\n", sqlca.sqlerrd[2]);
        { ECPGtrans(__LINE__, NULL, "commit work");}
#line 151 "functions.ec"
 // Завершение транзакции
    }
}


void task_1() {
    /* exec sql begin declare section */ // Начало секции объявления переменных
       
    
#line 158 "functions.ec"
 int count = 0 ;
/* exec sql end declare section */
#line 159 "functions.ec"
 // Конец секции объявления переменных

    { ECPGtrans(__LINE__, NULL, "begin work");}
#line 161 "functions.ec"
 // Начало новой транзакции
    { ECPGdo(__LINE__, 0, 1, NULL, 0, ECPGst_normal, "select count ( distinct spj . n_det ) from spj where spj . n_post in ( select distinct spj . n_post from spj join j on spj . n_izd = j . n_izd where j . town = 'Париж' )", ECPGt_EOIT, 
	ECPGt_int,&(count),(long)1,(long)1,sizeof(int), 
	ECPGt_NO_INDICATOR, NULL , 0L, 0L, 0L, ECPGt_EORT);}
#line 167 "functions.ec"

    if(check_warnings("Task 1")) {
        { ECPGtrans(__LINE__, NULL, "rollback work");}
#line 169 "functions.ec"
 // Откат транзакции
    }
    else {
        printf("Count: %d\n", count);
        { ECPGtrans(__LINE__, NULL, "commit work");}
#line 173 "functions.ec"
 // Завершение транзакции
    }   
}

void task_2() {
    { ECPGtrans(__LINE__, NULL, "begin work");}
#line 178 "functions.ec"
 // Начало новой транзакции
    { ECPGdo(__LINE__, 0, 1, NULL, 0, ECPGst_normal, "update p set cvet = case when town = 'Рим' then ( select min ( cvet ) from p where town = 'Лондон' ) when town = 'Лондон' then ( select min ( cvet ) from p where town = 'Рим' ) else cvet end where town in ( 'Лондон' , 'Рим' )", ECPGt_EOIT, ECPGt_EORT);}
#line 185 "functions.ec"

    if(check_warnings("Task 2")) {
        { ECPGtrans(__LINE__, NULL, "rollback work");}
#line 187 "functions.ec"
 // Откат транзакции
    }
    else {
        printf("Changed: %ld records\n", sqlca.sqlerrd[2]);
        { ECPGtrans(__LINE__, NULL, "commit work");}
#line 191 "functions.ec"
 // Завершение транзакции
    }
}

void task_3() {
    int rows = 0;

    /* exec sql begin declare section */ // Начало секции объявления переменных
     
             
         
         
     
    // Индикаторы для проверки NULL
     
    
#line 203 "functions.ec"
 struct { 
#line 200 "functions.ec"
 char n_post [ 2 * 6 + 1 ] ;
 
#line 201 "functions.ec"
 int kol ;
 
#line 202 "functions.ec"
 float avg_kol ;
 } data ;
 
#line 205 "functions.ec"
 int kol_ind ;
/* exec sql end declare section */
#line 206 "functions.ec"
 // Конец секции объявления переменных

    // Объявление курсора
    /* declare curs_1 cursor for select spj . n_post , spj . kol , avg_rim . avg_kol from s join spj on s . n_post = spj . n_post join ( select spj . n_post , avg ( spj . kol ) as avg_kol from spj join j on spj . n_izd = j . n_izd where j . town = 'Рим' group by spj . n_post ) as avg_rim on s . n_post = avg_rim . n_post where spj . kol >= 3 * avg_rim . avg_kol */
#line 218 "functions.ec"


    if (check_warnings("Task 3 => Declare cursor")) {
        return;
    }

    { ECPGtrans(__LINE__, NULL, "begin work");}
#line 224 "functions.ec"
 // Начало новой транзакции

    { ECPGdo(__LINE__, 0, 1, NULL, 0, ECPGst_normal, "declare curs_1 cursor for select spj . n_post , spj . kol , avg_rim . avg_kol from s join spj on s . n_post = spj . n_post join ( select spj . n_post , avg ( spj . kol ) as avg_kol from spj join j on spj . n_izd = j . n_izd where j . town = 'Рим' group by spj . n_post ) as avg_rim on s . n_post = avg_rim . n_post where spj . kol >= 3 * avg_rim . avg_kol", ECPGt_EOIT, ECPGt_EORT);}
#line 226 "functions.ec"
 // Открытие курсора

    while (sqlca.sqlcode == 0) {
        // Извлечение следующей строки результата из открытого курсора
        { ECPGdo(__LINE__, 0, 1, NULL, 0, ECPGst_normal, "fetch next curs_1", ECPGt_EOIT, 
	ECPGt_char,(data.n_post),(long)2 * 6 + 1,(long)1,(2 * 6 + 1)*sizeof(char), 
	ECPGt_NO_INDICATOR, NULL , 0L, 0L, 0L, 
	ECPGt_int,&(data.kol),(long)1,(long)1,sizeof(int), 
	ECPGt_int,&(kol_ind),(long)1,(long)1,sizeof(int), 
	ECPGt_float,&(data.avg_kol),(long)1,(long)1,sizeof(float), 
	ECPGt_NO_INDICATOR, NULL , 0L, 0L, 0L, ECPGt_EORT);}
#line 230 "functions.ec"


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
                { ECPGdo(__LINE__, 0, 1, NULL, 0, ECPGst_normal, "close curs_1", ECPGt_EOIT, ECPGt_EORT);}
#line 249 "functions.ec"

                { ECPGtrans(__LINE__, NULL, "rollback work");}
#line 250 "functions.ec"

                return;
            }
        }
    }

    { ECPGdo(__LINE__, 0, 1, NULL, 0, ECPGst_normal, "close curs_1", ECPGt_EOIT, ECPGt_EORT);}
#line 256 "functions.ec"
 // Закрытие курсора
    { ECPGtrans(__LINE__, NULL, "commit work");}
#line 257 "functions.ec"
 // Завершение транзакции
}

void task_4() {
    int rows = 0;

    /* exec sql begin declare section */ // Начало секции объявления переменныхы
         
    
#line 264 "functions.ec"
 char n_izd [ 2 * 6 + 1 ] ;
/* exec sql end declare section */
#line 265 "functions.ec"
 // Конец секции объявления переменных

    // Объявление курсора
    /* declare curs_2 cursor for select j . n_izd from j except select distinct spj . n_izd from spj where spj . n_post in ( select distinct spj . n_post from spj join p on spj . n_det = p . n_det where p . cvet = 'Красный' ) */
#line 277 "functions.ec"


    if (check_warnings("Task 4 => Declare cursor")) {
        return;
    }

    { ECPGtrans(__LINE__, NULL, "begin work");}
#line 283 "functions.ec"
 // Начало новой транзакции
    { ECPGdo(__LINE__, 0, 1, NULL, 0, ECPGst_normal, "declare curs_2 cursor for select j . n_izd from j except select distinct spj . n_izd from spj where spj . n_post in ( select distinct spj . n_post from spj join p on spj . n_det = p . n_det where p . cvet = 'Красный' )", ECPGt_EOIT, ECPGt_EORT);}
#line 284 "functions.ec"
 // Открытие курсора

    while (sqlca.sqlcode == 0) {
        // Извлечение следующей строки результата из открытого курсора
        { ECPGdo(__LINE__, 0, 1, NULL, 0, ECPGst_normal, "fetch next curs_2", ECPGt_EOIT, 
	ECPGt_char,(n_izd),(long)2 * 6 + 1,(long)1,(2 * 6 + 1)*sizeof(char), 
	ECPGt_NO_INDICATOR, NULL , 0L, 0L, 0L, ECPGt_EORT);}
#line 288 "functions.ec"


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
                { ECPGdo(__LINE__, 0, 1, NULL, 0, ECPGst_normal, "close curs_2", ECPGt_EOIT, ECPGt_EORT);}
#line 303 "functions.ec"

                { ECPGtrans(__LINE__, NULL, "rollback work");}
#line 304 "functions.ec"

                return;
            }
        }
    }

    { ECPGdo(__LINE__, 0, 1, NULL, 0, ECPGst_normal, "close curs_2", ECPGt_EOIT, ECPGt_EORT);}
#line 310 "functions.ec"
 // Закрытие курсора
    { ECPGtrans(__LINE__, NULL, "commit work");}
#line 311 "functions.ec"
 // Завершение транзакции
}

void task_5() {
    int rows = 0;

    /* exec sql begin declare section */ // Начало секции объявления переменных
     
             
             
             
     
    // Индикаторы для проверки NULL
     
     
    
#line 322 "functions.ec"
 struct { 
#line 319 "functions.ec"
 char n_izd [ 2 * 6 + 1 ] ;
 
#line 320 "functions.ec"
 char name [ 2 * 20 + 1 ] ;
 
#line 321 "functions.ec"
 char town [ 2 * 20 + 1 ] ;
 } j ;
 
#line 324 "functions.ec"
 int name_ind ;
 
#line 325 "functions.ec"
 int town_ind ;
/* exec sql end declare section */
#line 326 "functions.ec"
 // Конец секции объявления переменных

    // Объявление курсора
    /* declare curs_3 cursor for select * from j where j . n_izd in ( select spj . n_izd from spj join p on p . n_det = spj . n_det group by spj . n_izd having min ( p . ves ) > 12 ) */
#line 336 "functions.ec"


    if (check_warnings("Task 5 => Declare cursor")) {
        return;
    }

    { ECPGtrans(__LINE__, NULL, "begin work");}
#line 342 "functions.ec"
 // Начало новой транзакции
    { ECPGdo(__LINE__, 0, 1, NULL, 0, ECPGst_normal, "declare curs_3 cursor for select * from j where j . n_izd in ( select spj . n_izd from spj join p on p . n_det = spj . n_det group by spj . n_izd having min ( p . ves ) > 12 )", ECPGt_EOIT, ECPGt_EORT);}
#line 343 "functions.ec"
 // Открытие курсора

    while (sqlca.sqlcode == 0) {
        // Извлечение следующей строки результата из открытого курсора
        { ECPGdo(__LINE__, 0, 1, NULL, 0, ECPGst_normal, "fetch next curs_3", ECPGt_EOIT, 
	ECPGt_char,(j.n_izd),(long)2 * 6 + 1,(long)1,(2 * 6 + 1)*sizeof(char), 
	ECPGt_NO_INDICATOR, NULL , 0L, 0L, 0L, 
	ECPGt_char,(j.name),(long)2 * 20 + 1,(long)1,(2 * 20 + 1)*sizeof(char), 
	ECPGt_int,&(name_ind),(long)1,(long)1,sizeof(int), 
	ECPGt_char,(j.town),(long)2 * 20 + 1,(long)1,(2 * 20 + 1)*sizeof(char), 
	ECPGt_int,&(town_ind),(long)1,(long)1,sizeof(int), ECPGt_EORT);}
#line 347 "functions.ec"


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
                strcpy(j.name, "NULL");
            }
            if(town_ind < 0) {
                strcpy(j.town, "NULL");
            }
            printf("%s\t\t%s\t%s\n", j.n_izd, j.name, j.town);
        } else {
            if(sqlca.sqlcode < 0) {
                { ECPGdo(__LINE__, 0, 1, NULL, 0, ECPGst_normal, "close curs_3", ECPGt_EOIT, ECPGt_EORT);}
#line 369 "functions.ec"

                { ECPGtrans(__LINE__, NULL, "rollback work");}
#line 370 "functions.ec"

                return;
            }
        }
    }

    { ECPGdo(__LINE__, 0, 1, NULL, 0, ECPGst_normal, "close curs_3", ECPGt_EOIT, ECPGt_EORT);}
#line 376 "functions.ec"
 // Закрытие курсора
    { ECPGtrans(__LINE__, NULL, "commit work");}
#line 377 "functions.ec"
 // Завершение транзакции
}