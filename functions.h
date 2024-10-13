#define DB "students@students.ami.nstu.ru"
#define ERROR 1
#define WARNING 2

void print_errors(const char* theOperation);
void check_errors(const char* theOperation);
int check_warnings(const char* theOperation);
void print_warnings(const char* theOperation);
void connect_db(const char* theLogin, const char* thePassword);
void connect_schema(const char* theSchema);

void table_rollback();

void task_1();
void task_2();
void task_3();