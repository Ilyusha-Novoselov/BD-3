COMPILER = /usr/bin/gcc # Компилятор
ECPG = /usr/bin/ecpg # Препроцессор для преобразования .ec в .c

PG_INCLUDE = /usr/include/postgresql # Заголовочные файлы для pgsql
PG_LIB = /usr/lib/postgresql/14/lib # Библиотеки для pgsql

CFLAGS = -I$(PG_INCLUDE) -Wall # Флаги для gcc (заголовочные файлы)
LDFLAGS = -L$(PG_LIB) # Флаги для линковщика (библиотеки)
LIBS = -lecpg -lecpg_compat # Используемые библиотеки

all: main
	./main

main: functions.c main.c
	$(COMPILER) functions.c main.c -o main $(CFLAGS) $(LDFLAGS) $(LIBS)

functions.c: functions.ec
	$(ECPG) functions.ec

clean:
	rm -f main functions.c
