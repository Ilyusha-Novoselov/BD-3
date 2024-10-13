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
    /* exec sql begin declare section */
        
        
        
    
#line 32 "functions.ec"
 const char * login = theLogin ;
 
#line 33 "functions.ec"
 const char * password = thePassword ;
 
#line 34 "functions.ec"
 const char * db = DB ;
/* exec sql end declare section */
#line 35 "functions.ec"


    { ECPGconnect(__LINE__, 0, db , login , password , NULL, 0); }
#line 37 "functions.ec"

    check_errors("Connect to db");
}

void connect_schema(const char* theSchema) {
    /* exec sql begin declare section */
        
    
#line 43 "functions.ec"
 const char * schema = theSchema ;
/* exec sql end declare section */
#line 44 "functions.ec"


    { ECPGdo(__LINE__, 0, 1, NULL, 0, ECPGst_normal, "set search_path to $0", 
	ECPGt_char,&(schema),(long)0,(long)1,(1)*sizeof(char), 
	ECPGt_NO_INDICATOR, NULL , 0L, 0L, 0L, ECPGt_EOIT, ECPGt_EORT);}
#line 46 "functions.ec"

    check_errors("Connect schema");
}

void table_rollback() {
    { ECPGtrans(__LINE__, NULL, "begin work");}
#line 51 "functions.ec"


    { ECPGdo(__LINE__, 0, 1, NULL, 0, ECPGst_normal, "drop table if exists j cascade", ECPGt_EOIT, ECPGt_EORT);}
#line 53 "functions.ec"


    { ECPGdo(__LINE__, 0, 1, NULL, 0, ECPGst_normal, "create table j ( n_izd character ( 6 ) primary key , name character ( 20 ) , town character ( 20 ) )", ECPGt_EOIT, ECPGt_EORT);}
#line 59 "functions.ec"


    { ECPGdo(__LINE__, 0, 1, NULL, 0, ECPGst_normal, "insert into j values ( 'J1' , 'Жесткий диск' , 'Париж' ) , ( 'J2' , 'Перфоратор' , 'Рим' ) , ( 'J3' , 'Считыватель' , 'Афины' ) , ( 'J4' , 'Принтер' , 'Афины' ) , ( 'J5' , 'Флоппидиск-' , 'Лондон' ) , ( 'J6' , 'Терминал' , 'Осло' ) , ( 'J7' , 'Лента' , 'Лондон' )", ECPGt_EOIT, ECPGt_EORT);}
#line 68 "functions.ec"


    { ECPGdo(__LINE__, 0, 1, NULL, 0, ECPGst_normal, "drop table if exists s cascade", ECPGt_EOIT, ECPGt_EORT);}
#line 70 "functions.ec"


    { ECPGdo(__LINE__, 0, 1, NULL, 0, ECPGst_normal, "create table s ( n_post character ( 6 ) primary key , name character ( 20 ) , reiting integer , town character ( 20 ) )", ECPGt_EOIT, ECPGt_EORT);}
#line 77 "functions.ec"


    { ECPGdo(__LINE__, 0, 1, NULL, 0, ECPGst_normal, "insert into s values ( 'S1' , 'Смит' , 20 , 'Лондон' ) , ( 'S2' , 'Джонс' , 10 , 'Париж' ) , ( 'S3' , 'Блейк' , 30 , 'Париж' ) , ( 'S4' , 'Кларк' , 20 , 'Лондон' ) , ( 'S5' , 'Адамс' , 30 , 'Афины' )", ECPGt_EOIT, ECPGt_EORT);}
#line 84 "functions.ec"


    { ECPGdo(__LINE__, 0, 1, NULL, 0, ECPGst_normal, "drop table if exists p cascade", ECPGt_EOIT, ECPGt_EORT);}
#line 86 "functions.ec"


    { ECPGdo(__LINE__, 0, 1, NULL, 0, ECPGst_normal, "create table p ( n_det character ( 6 ) primary key , name character ( 20 ) , cvet character ( 20 ) , ves integer , town character ( 20 ) )", ECPGt_EOIT, ECPGt_EORT);}
#line 94 "functions.ec"


    { ECPGdo(__LINE__, 0, 1, NULL, 0, ECPGst_normal, "insert into p values ( 'P1' , 'Гайка' , 'Красный' , 12 , 'Лондон' ) , ( 'P2' , 'Болт' , 'Зеленый' , 17 , 'Париж' ) , ( 'P3' , 'Винт' , 'Голубой' , 17 , 'Рим' ) , ( 'P4' , 'Винт' , 'Красный' , 14 , 'Лондон' ) , ( 'P5' , 'Кулачок' , 'Голубой' , 12 , 'Париж' ) , ( 'P6' , 'Блюм' , 'Красный' , 19 , 'Лондон' )", ECPGt_EOIT, ECPGt_EORT);}
#line 102 "functions.ec"


    { ECPGdo(__LINE__, 0, 1, NULL, 0, ECPGst_normal, "drop table if exists spj cascade", ECPGt_EOIT, ECPGt_EORT);}
#line 104 "functions.ec"


    { ECPGdo(__LINE__, 0, 1, NULL, 0, ECPGst_normal, "create table spj ( n_post character ( 6 ) , n_det character ( 6 ) , n_izd character ( 6 ) , kol integer )", ECPGt_EOIT, ECPGt_EORT);}
#line 111 "functions.ec"


    { ECPGdo(__LINE__, 0, 1, NULL, 0, ECPGst_normal, "insert into spj values ( 'S1' , 'P1' , 'J1' , 200 ) , ( 'S1' , 'P1' , 'J4' , 700 ) , ( 'S2' , 'P3' , 'J1' , 400 ) , ( 'S2' , 'P3' , 'J2' , 200 ) , ( 'S2' , 'P3' , 'J3' , 200 ) , ( 'S2' , 'P3' , 'J4' , 500 ) , ( 'S2' , 'P3' , 'J5' , 600 ) , ( 'S2' , 'P3' , 'J6' , 400 ) , ( 'S2' , 'P3' , 'J7' , 800 ) , ( 'S2' , 'P5' , 'J2' , 100 ) , ( 'S3' , 'P3' , 'J1' , 200 ) , ( 'S3' , 'P4' , 'J2' , 500 ) , ( 'S4' , 'P6' , 'J3' , 300 ) , ( 'S4' , 'P6' , 'J7' , 300 ) , ( 'S5' , 'P2' , 'J2' , 200 ) , ( 'S5' , 'P2' , 'J4' , 100 ) , ( 'S5' , 'P5' , 'J5' , 500 ) , ( 'S5' , 'P5' , 'J7' , 100 ) , ( 'S5' , 'P6' , 'J2' , 200 ) , ( 'S5' , 'P1' , 'J4' , 100 ) , ( 'S5' , 'P3' , 'J4' , 200 ) , ( 'S5' , 'P4' , 'J4' , 800 ) , ( 'S5' , 'P5' , 'J4' , 400 ) , ( 'S5' , 'P6' , 'J4' , 500 )", ECPGt_EOIT, ECPGt_EORT);}
#line 137 "functions.ec"


    if(check_warnings("Table rollback")) {
        { ECPGtrans(__LINE__, NULL, "rollback work");}
#line 140 "functions.ec"

    }
    else {
        printf("Changed: %ld rows\n", sqlca.sqlerrd[2]);
        { ECPGtrans(__LINE__, NULL, "commit work");}
#line 144 "functions.ec"

    }
}


void task_1() {
    /* exec sql begin declare section */
     
    
#line 151 "functions.ec"
 int count ;
/* exec sql end declare section */
#line 152 "functions.ec"


    { ECPGtrans(__LINE__, NULL, "begin work");}
#line 154 "functions.ec"

    { ECPGdo(__LINE__, 0, 1, NULL, 0, ECPGst_normal, "select count ( distinct spj . n_det ) from spj join j on spj . n_izd = j . n_izd where j . town = 'Париж'", ECPGt_EOIT, 
	ECPGt_int,&(count),(long)1,(long)1,sizeof(int), 
	ECPGt_NO_INDICATOR, NULL , 0L, 0L, 0L, ECPGt_EORT);}
#line 158 "functions.ec"

    { ECPGtrans(__LINE__, NULL, "commit work");}
#line 159 "functions.ec"

    printf("Count: %d\n", count);
}

void task_2() {
    { ECPGtrans(__LINE__, NULL, "begin work");}
#line 164 "functions.ec"

    { ECPGdo(__LINE__, 0, 1, NULL, 0, ECPGst_normal, "update p set cvet = case when town = 'Рим' then ( select min ( cvet ) from p where town = 'Лондон' ) when town = 'Лондон' then ( select min ( cvet ) from p where town = 'Рим' ) else cvet end where town in ( 'Лондон' , 'Рим' )", ECPGt_EOIT, ECPGt_EORT);}
#line 171 "functions.ec"

    if(check_warnings("Task 2")) {
        { ECPGtrans(__LINE__, NULL, "rollback work");}
#line 173 "functions.ec"

    }
    else {
        printf("Changed: %ld rows\n", sqlca.sqlerrd[2]);
        { ECPGtrans(__LINE__, NULL, "commit work");}
#line 177 "functions.ec"

    }
}