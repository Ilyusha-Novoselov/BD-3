#define DB "students@students.ami.nstu.ru"
#define ERROR 1

// Функции для проверки и вывода ошибок
void print_errors(const char* theOperation);
void check_errors(const char* theOperation);
// Функции для проверки и вывода предупреждений
int check_warnings(const char* theOperation);
void print_warnings(const char* theOperation);
// Функция для подключения к бд
void connect_db(const char* theLogin, const char* thePassword);
// Функция для подключения к схеме
void connect_schema(const char* theSchema);

// Функция для сброса таблиц
void table_rollback();
// Функции для выполнения заданий
void task_1();
void task_2();
void task_3();
void task_4();
void task_5();